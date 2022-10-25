/**
   
   Código fuente basado en usbd_keyboard de sAPI, adaptado a un Gamepad
   
   Autor: Calderón Sergio
   Fecha: 24 de octubre de 2022

**/

// Cabecera del archivo
#include "usbd_gamepad.h"


/*****************************************************************************
 * Public types/enumerations/variables
 ****************************************************************************/
 
extern const uint8_t Gamepad_ReportDescriptor[];      // definido en usb_gamepad_hid_desc.c
extern const uint16_t Gamepad_ReportDescSize;         // definido en usb_gamepad_hid_desc.c
 

/*****************************************************************************
 * Private functions
 ****************************************************************************/

static ErrorCode_t Gamepad_GetReport(USBD_HANDLE_T hHid, USB_SETUP_PACKET *pSetup, uint8_t * *pBuffer, uint16_t *plength){
   // TODO
   
   return LPC_OK;
}

static ErrorCode_t Gamepad_SetReport(USBD_HANDLE_T hHid, USB_SETUP_PACKET *pSetup, uint8_t * *pBuffer, uint16_t length){
   // TODO
   
   return LPC_OK;
}

// Manejador de interrupciones
static ErrorCode_t Gamepad_EpIN_Hdlr(USBD_HANDLE_T hUsb, void *data, uint32_t event){
   // TODO
   
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
   
   // Se devuelve estado resultado de la inicialización
   return ret;
}


void usbDeviceGamepadTasks(void){
   
}