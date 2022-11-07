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
   
   #define BYTE_PULSADORES    7
   
   
   /*==================[tipos de datos declarados por el usuario]===============*/
   

   /*==================[declaraciones de datos externos]========================*/


   /*==================[declaraciones de funciones públicas]====================*/
   
   ErrorCode_t usbDeviceGamepadInit(
      USBD_HANDLE_T hUsb, 
      USB_INTERFACE_DESCRIPTOR *pIntfDesc, 
      uint32_t *mem_base, 
      uint32_t *mem_size
   );
   
   uint8_t usbDeviceGamepadTasks(void);
   void usbDeviceGamepadPress(uint8_t);
   bool_t usbDeviceGamepadCheckCallbackSet(callBackFuncPtr_t checkCallback);
   
#endif