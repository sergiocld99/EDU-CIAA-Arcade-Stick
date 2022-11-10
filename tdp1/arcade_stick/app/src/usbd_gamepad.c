/**
   
   Código fuente basado en usbd_keyboard de sAPI, adaptado a un Gamepad
   
   Autor: Calderón Sergio
   Fecha: 24 de octubre de 2022

**/

// Cabecera del archivo
#include "usbd_gamepad.h"
#include "usbd_keyboard_endpoints.h"
#include "sapi_board.h"

// Macros
#define GAMEPAD_REPORT_SIZE 8

#define HID_GAMEPAD_CLEAR_REPORT(x)                   memset(x, 0, 8);
#define HID_GAMEPAD_REPORT_SET_XCOR(x, val)           x[0] = (int8_t) val;
#define HID_GAMEPAD_REPORT_SET_YCOR(x, val)           x[1] = (int8_t) val;
#define HID_GAMEPAD_REPORT_SET_HAT(x, val)            x[4] = (uint8_t) val;
#define HID_GAMEPAD_REPORT_SET_VALUE(x, val)          x[7] = (uint8_t) val;

/*****************************************************************************
 * Public types/enumerations/variables
 ****************************************************************************/
 
extern const uint8_t Gamepad_ReportDescriptor[];      // definido en usb_gamepad_hid_desc.c
extern const uint16_t Gamepad_ReportDescSize;         // definido en usb_gamepad_hid_desc.c

typedef struct {
	USBD_HANDLE_T hUsb;	                  /*!< Handle to USB stack. */
	uint8_t report[GAMEPAD_REPORT_SIZE];	/*!< Last report data  */
	uint8_t tx_busy;	                     /*!< Flag indicating whether a report is pending in endpoint queue. */
} Gamepad_Ctrl_T;

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

static Gamepad_Ctrl_T g_gamePad;
callBackFuncPtr_t gamepadCheckFunction = NULL;

/*****************************************************************************
 * Private functions
 ****************************************************************************/

static void Gamepad_UpdateReport(){
   HID_GAMEPAD_CLEAR_REPORT(&g_gamePad.report[0]);
   
   // Board_LED_Toggle(3);

   // Execute Tick Hook function if pointer is not NULL
   if (gamepadCheckFunction != NULL) {
      (* gamepadCheckFunction )( NULL );
   }
}

static ErrorCode_t Gamepad_GetReport(USBD_HANDLE_T hHid, USB_SETUP_PACKET *pSetup, uint8_t * *pBuffer, uint16_t *plength){
   
   // Board_LED_Toggle(5);
   
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

static ErrorCode_t Gamepad_SetReport(USBD_HANDLE_T hHid, USB_SETUP_PACKET *pSetup, uint8_t * *pBuffer, uint16_t length){
   // TODO
   // Board_LED_Toggle(3);
   
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
}


/*****************************************************************************
 * Public functions
 ****************************************************************************/

ErrorCode_t usbDeviceGamepadInit(USBD_HANDLE_T hUsb, USB_INTERFACE_DESCRIPTOR *pIntfDesc, uint32_t *mem_base, uint32_t *mem_size){
   USBD_HID_INIT_PARAM_T hid_param;
   USB_HID_REPORT_T reports_data[1];
   ErrorCode_t ret = LPC_OK;
   
   // Configurar parámetros HID
   memset((void *) &hid_param, 0, sizeof(USBD_HID_INIT_PARAM_T));
   hid_param.max_reports = 1;
   hid_param.mem_base = *mem_base;
   hid_param.mem_size = *mem_size;
   hid_param.intf_desc = (uint8_t *) pIntfDesc;
   
   // Funciones definidas para Gamepad
   // Se debe respetar el prototipo según usbd_hiduser.h (de sAPI)
   hid_param.HID_GetReport = Gamepad_GetReport;
   hid_param.HID_SetReport = Gamepad_SetReport;
   hid_param.HID_EpIn_Hdlr = Gamepad_EpIN_Hdlr;
   
   // Inicializar reports_data
   reports_data[0].len = Gamepad_ReportDescSize;
   reports_data[0].idle_time = 0;
   reports_data[0].desc = (uint8_t *) &Gamepad_ReportDescriptor[0];
   hid_param.report_data = reports_data;
   
   // Fin de inicialización con USBD API
   ret = USBD_API->hid->init(hUsb, &hid_param);
   
   // Actualizar parámetros por referencia de memoria
   *mem_base = hid_param.mem_base;
   *mem_size = hid_param.mem_size;
   
   g_gamePad.hUsb = hUsb;
   g_gamePad.tx_busy = 0;
   
   // Se devuelve estado resultado de la inicialización
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
         // Board_LED_Toggle(1);
      }
   } else {
      // Si no está configurado, marcar como no ocupado
      g_gamePad.tx_busy = 0;
   }
}

void usbDeviceGamepadPress(uint8_t key)
{
   HID_GAMEPAD_REPORT_SET_VALUE(g_gamePad.report, key);
   // Board_LED_Toggle(7);
}

void usbDeviceGamepadMove(int8_t value, uint8_t axis)
{
   if (value > -28 && value < 28) return;
   
   if (axis == 0) {
      HID_GAMEPAD_REPORT_SET_XCOR(g_gamePad.report, value);
   } else {
      HID_GAMEPAD_REPORT_SET_YCOR(g_gamePad.report, value);
   }
}

void usbDeviceGamepadHat(uint8_t pressed){
   HID_GAMEPAD_REPORT_SET_HAT(g_gamePad.report, pressed);
}

// Gamepad function to check in my device for pressed buttons
bool_t usbDeviceGamepadCheckCallbackSet(callBackFuncPtr_t checkCallback){
   bool_t retVal = TRUE;
   
   // Si la funcion de callback recibida no es nula, asignarla para los siguientes updates
   if( checkCallback != NULL ) gamepadCheckFunction = checkCallback;
   else retVal = FALSE;
   
   return retVal;
}