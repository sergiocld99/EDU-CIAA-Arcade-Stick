/**
   
   Codigo fuente basado en usbd_keyboard de sAPI, adaptado a un Gamepad
   
   Autor: Calderon Sergio
   Fecha: 24 de octubre de 2022

**/

// Cabecera del archivo
#include "usbd_gamepad.h"
// #include "usbd_keyboard_endpoints.h"
#include "sapi_board.h"

/*****************************************************************************
 * Public types/enumerations/variables
 ****************************************************************************/

callBackFuncPtr_t gamepadCheckFunction = NULL;

/// HID Gamepad Protocol Report.
typedef struct TU_ATTR_PACKED
{
   int8_t  x;         ///< Delta x  movement of left analog-stick
   int8_t  y;         ///< Delta y  movement of left analog-stick
   int8_t  z;         ///< Delta z  movement of right analog-joystick
   int8_t  rz;        ///< Delta Rz movement of right analog-joystick
   int8_t  rx;        ///< Delta Rx movement of analog left trigger
   int8_t  ry;        ///< Delta Ry movement of analog right trigger
   uint8_t hat;       ///< Buttons mask for currently pressed buttons in the DPad/hat
   uint32_t buttons;  ///< Buttons mask for currently pressed buttons
} hid_gamepad_report_t;

/*****************************************************************************
 * Private types/enumerations/variables
 ****************************************************************************/

typedef struct {
	USBD_HANDLE_T hUsb;	                  /*!< Handle to USB stack. */
	uint8_t report[GAMEPAD_REPORT_SIZE];	/*!< Last report data  */
	uint8_t tx_busy;	                     /*!< Flag indicating whether a report is pending in endpoint queue. */
} Gamepad_Ctrl_T;

static Gamepad_Ctrl_T g_gamePad;


/*****************************************************************************
 * Private functions
 ****************************************************************************/

static void Gamepad_UpdateReport(){
   
   HID_GAMEPAD_CLEAR_REPORT(&g_gamePad.report[0]);

   // Execute Tick Hook function if pointer is not NULL
   if (gamepadCheckFunction != NULL) {
      (* gamepadCheckFunction )( NULL );
   }
}

/* HID Get Report Request Callback. Called automatically on HID Get Report Request */
static ErrorCode_t Gamepad_GetReport(USBD_HANDLE_T hHid, USB_SETUP_PACKET *pSetup, uint8_t * *pBuffer, uint16_t *plength){
   
   /* ReportID = SetupPacket.wValue.WB.L; */
	switch (pSetup->wValue.WB.H) {

      case HID_REPORT_INPUT:
         Gamepad_UpdateReport();
         memcpy(*pBuffer, &g_gamePad.report[0], GAMEPAD_REPORT_SIZE);
         *plength = GAMEPAD_REPORT_SIZE;
      break;

      case HID_REPORT_OUTPUT:				/* Not Supported */
      case HID_REPORT_FEATURE:			/* Not Supported */
         return ERR_USBD_STALL;
	}

	return LPC_OK;
}

/* HID Set Report Request Callback. Called automatically on HID Set Report Request */
static ErrorCode_t Gamepad_SetReport(USBD_HANDLE_T hHid, USB_SETUP_PACKET *pSetup, uint8_t * *pBuffer, uint16_t length){
   // TODO
   
   return LPC_OK;
}

// Manejador de interrupciones
static ErrorCode_t Gamepad_EpIN_Hdlr(USBD_HANDLE_T hUsb, void *data, uint32_t event){
   
   switch (event) {
      case USB_EVT_IN:
         g_gamePad.tx_busy = 0;
         break;
   }
   
   return LPC_OK;
   
   return LPC_OK;
}


/*****************************************************************************
 * Public functions
 ****************************************************************************/

ErrorCode_t usbDeviceGamepadInit(USBD_HANDLE_T hUsb, USB_INTERFACE_DESCRIPTOR *pIntfDesc, uint32_t *mem_base, uint32_t *mem_size){
   USBD_HID_INIT_PARAM_T hid_param;
   USB_HID_REPORT_T reports_data[1];
   ErrorCode_t ret = LPC_OK;
   
   // Configurar parametros HID
   memset((void *) &hid_param, 0, sizeof(USBD_HID_INIT_PARAM_T));
   hid_param.max_reports = 1;
   hid_param.mem_base = *mem_base;
   hid_param.mem_size = *mem_size;
   hid_param.intf_desc = (uint8_t *) pIntfDesc;
   
   // Funciones definidas para Gamepad
   // Se debe respetar el prototipo segï¿½n usbd_hiduser.h (de sAPI)
   hid_param.HID_GetReport = Gamepad_GetReport;
   hid_param.HID_SetReport = Gamepad_SetReport;
   hid_param.HID_EpIn_Hdlr = Gamepad_EpIN_Hdlr;
   
   // Cargar parametros de reporte
   reports_data[0].len = Gamepad_ReportDescSize;
   reports_data[0].idle_time = 0;
   reports_data[0].desc = (uint8_t *) &Gamepad_ReportDescriptor[0];
   hid_param.report_data = reports_data;
   
   // Inicializar HID a partir de manejador y parametros
   ret = USBD_API->hid->init(hUsb, &hid_param);
   
   // Actualizar los parametros de memoria de USBD API
   *mem_base = hid_param.mem_base;
   *mem_size = hid_param.mem_size;
   
   g_gamePad.hUsb = hUsb;
   g_gamePad.tx_busy = 0;
   
   // Se devuelve estado resultado de la inicializacion
   return ret;
}


void usbDeviceGamepadTasks(void){
   
   // Primero nos aseguramos que el dispositivo esté configurado
   if (USB_IsConfigured(g_gamePad.hUsb)){
      
      // Enviar datos de reporte si esta libre
      if (g_gamePad.tx_busy == 0){
         g_gamePad.tx_busy = 1;      // marcar como ocupado
         Gamepad_UpdateReport();                // cargar reporte
         USBD_API->hw->WriteEP(g_gamePad.hUsb, HID_EP_IN, &g_gamePad.report[0], GAMEPAD_REPORT_SIZE);
      }
   } else {
      // Si no está configurado, marcar como no ocupado
      g_gamePad.tx_busy = 0;
   }
}

void usbDeviceGamepadPress( uint8_t key )
{
   HID_GAMEPAD_REPORT_SET_VALUE(g_gamePad.report, key);
}

// Gamepad function to check in my device for pressed buttons
bool_t usbDeviceGamepadCheckCallbackSet(callBackFuncPtr_t checkCallback){
   bool_t retVal = TRUE;
   
   // Si la funcion de callback recibida no es nula, asignarla para los siguientes updates
   if( checkCallback != NULL ) gamepadCheckFunction = checkCallback;
   else retVal = FALSE;
   
   return retVal;
}