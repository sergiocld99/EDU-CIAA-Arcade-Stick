/*============================================================================
 * Licencia:
 * Autor: Calder�n Sergio
 * Fecha: 24 de octubre de 2022
 *===========================================================================*/

#ifndef _USBD_GAMEPAD_H_
   #define _USBD_GAMEPAD_H_

   /*==================[inclusiones]============================================*/
   
   #include "sapi_datatypes.h"
   #include "lpc_app_usbd_cfg.h"
   
   #include <string.h>     // memset
   

   /*==================[macros]=================================================*/
   
   
   /*==================[tipos de datos declarados por el usuario]===============*/
   

   /*==================[declaraciones de datos externos]========================*/


   /*==================[declaraciones de funciones p�blicas]====================*/
   
   ErrorCode_t usbDeviceGamepadInit(
      USBD_HANDLE_T hUsb, 
      USB_INTERFACE_DESCRIPTOR *pIntfDesc, 
      uint32_t *mem_base, 
      uint32_t *mem_size
   );
   
   void usbDeviceGamepadTasks(void);
   void usbDeviceGamepadPress(uint8_t);
   
#endif