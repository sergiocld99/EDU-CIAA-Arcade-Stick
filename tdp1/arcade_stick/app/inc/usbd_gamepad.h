/*============================================================================
 * Licencia:
 * Autor: Calderón Sergio
 * Fecha: 24 de octubre de 2022
 *===========================================================================*/

#ifndef _USBD_GAMEPAD_H_
   #define _USBD_GAMEPAD_H_

   /*==================[inclusiones]============================================*/
   
   #include "sapi_datatypes.h"
   #include "lpc_app_usbd_cfg.h"
   
   #include <string.h>     // memset
   

   /*==================[macros]=================================================*/
   
   // Endpoints
   #define HID_EP_IN       0x81
   // #define HID_EP_OUT      0x01
   
   // Reportes
   #define GAMEPAD_REPORT_SIZE                           8
   #define HID_GAMEPAD_CLEAR_REPORT(x)                   memset(x, 0, 8);
   #define HID_GAMEPAD_REPORT_SET_VALUE(x, val)          x[2] = (uint8_t) val;
   
   
   /*==================[tipos de datos declarados por el usuario]===============*/
   

   /*==================[declaraciones de datos externos]========================*/

   extern const uint8_t Gamepad_ReportDescriptor[];      // definido en usb_gamepad_hid_desc.c
   extern const uint16_t Gamepad_ReportDescSize;         // definido en usb_gamepad_hid_desc.c

   /*==================[declaraciones de funciones públicas]====================*/
   
   ErrorCode_t usbDeviceGamepadInit(
      USBD_HANDLE_T hUsb, 
      USB_INTERFACE_DESCRIPTOR *pIntfDesc, 
      uint32_t *mem_base, 
      uint32_t *mem_size
   );
   
   void usbDeviceGamepadTasks(void);
   void usbDeviceGamepadPress(uint8_t);
   bool_t usbDeviceGamepadCheckCallbackSet(callBackFuncPtr_t checkCallback);
   
#endif