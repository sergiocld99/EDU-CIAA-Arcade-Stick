/**
   
   DESCRIPTORES ESPECIFICADOS PARA USB HID TIPO GAMEPAD
      - USB_DeviceDescriptor 
      - USB_StringDescriptor 
      - USB_FsConfigDescriptor (Full Speed)
      - USB_HsConfigDescriptor (High Speed)
      - USB_DeviceQualifier
   
   Código fuente basado en usbd_keyboard_hid_desc del ejemplo sAPI
   Adaptación realizada mediante la especificación de TinyUSB para Gamepad
   
   Fuente Microchip 2004: https://WW1.MICROCHIP.COM/DOWNLOADS/EN/APPNOTES/TB054SC.ZIP
   
   Autor: Calderón Sergio
   Fecha: 24 de octubre de 2022

**/

// Includes
#include "lpc_app_usbd_cfg.h"
#include "usbd_gamepad.h"

// Elección de implementación (DEBUG)
#define HID_GAMEPAD_SIMPLE_VERSION

// Macros no definidas en sAPI (importado de TinyUSB)
#define HID_PHYSICAL_MAX_N(x, n)                         HID_REPORT_ITEM(x, 4, 1, n)
#define HID_REPORT_ITEM(data, tag, type, size)           (((tag) << 4) | ((type) << 2) | (size)) HID_REPORT_DATA_##size(data)
#define HID_REPORT_DATA_2(data)                          , U16_TO_U8S_LE(data)
#define U16_TO_U8S_LE(_u16)                              TU_U16_LOW(_u16), TU_U16_HIGH(_u16)
#define TU_U16_HIGH(_u16)                                ((uint8_t) (((_u16) >> 8) & 0x00ff))
#define TU_U16_LOW(_u16)                                 ((uint8_t) ((_u16) & 0x00ff))


// -------------------- PARTE A: DESCRIPTOR PARA STRUCT USB_HID_REPORT_T ------------------

// Elección de implementación (XY & 6-buttons vs XYZ & 32-buttons)
#ifdef HID_GAMEPAD_SIMPLE_VERSION
   const uint8_t Gamepad_ReportDescriptor[] = {
      HID_UsagePage(HID_USAGE_PAGE_GENERIC),
      HID_Usage(HID_USAGE_GENERIC_GAMEPAD),
      HID_Collection(HID_Application),
      HID_UsagePage( HID_USAGE_PAGE_GENERIC ),
      HID_Usage( HID_USAGE_GENERIC_X ),
      HID_Usage( HID_USAGE_GENERIC_Y ),
      HID_LogicalMin(0),
      HID_LogicalMax(255),
      HID_ReportCount(2),
      HID_ReportSize(8),
      HID_Input(HID_Data | HID_Variable | HID_Absolute),
      // Mapeo de los 6 pulsadores
      HID_UsagePage( HID_USAGE_PAGE_BUTTON ),
      HID_UsageMin(1),
      HID_UsageMax(6),
      HID_LogicalMin(0),
      HID_LogicalMax(1),
      HID_ReportCount(6),
      HID_ReportSize(1),
      HID_Input(HID_Data | HID_Variable | HID_Absolute),
      // 2 bits reservados para futuros pulsadores
      HID_ReportCount(1),
      HID_ReportSize(2),
      HID_Input(HID_Constant), 
      HID_EndCollection
   };
#else
   const uint8_t Gamepad_ReportDescriptor[] = {
      HID_UsagePage(HID_USAGE_PAGE_GENERIC), 
      HID_Usage(HID_USAGE_GENERIC_GAMEPAD),
      HID_Collection(HID_Application),
      HID_UsagePage( HID_USAGE_PAGE_GENERIC ),
      HID_Usage( HID_USAGE_GENERIC_X ),
      HID_Usage( HID_USAGE_GENERIC_Y ) ,
      HID_Usage( HID_USAGE_GENERIC_Z ) ,
      HID_Usage( HID_USAGE_GENERIC_RZ ) ,
      HID_Usage( HID_USAGE_GENERIC_RX ) ,
      HID_Usage( HID_USAGE_GENERIC_RY ) ,
      HID_LogicalMin( -127 ),
      HID_LogicalMax( 127 ),
      HID_ReportCount(6),
      HID_ReportSize(8),
      HID_Input(HID_Data | HID_Variable | HID_Relative),
      // Mapeo de 8-bit DPad / Hat
      HID_UsagePage( HID_USAGE_PAGE_GENERIC ),
      HID_Usage( HID_USAGE_GENERIC_HATSWITCH ),
      HID_LogicalMin( 1 ),
      HID_LogicalMax( 8 ),
      HID_PhysicalMin(0),
      HID_PHYSICAL_MAX_N(315, 2),
      HID_ReportCount(1),
      HID_ReportSize(8),
      HID_Input(HID_Data | HID_Variable | HID_Absolute),
      // Mapeo de los 6 pulsadores
      HID_UsagePage( HID_USAGE_PAGE_BUTTON ),
      HID_UsageMin(1),
      HID_UsageMax(6),
      HID_LogicalMin(0),
      HID_LogicalMax(1),
      HID_ReportCount(6),
      HID_ReportSize(1),
      HID_Input(HID_Data | HID_Variable | HID_Absolute),
      // 2 bits reservados para futuros pulsadores
      HID_ReportCount(1),
      HID_ReportSize(2),
      HID_Input(HID_Constant), 
      HID_EndCollection,
   };
#endif

// Tamaño del descriptor de reportes
const uint16_t Gamepad_ReportDescSize = sizeof(Gamepad_ReportDescriptor);


// ------------------- PARTE B: DESCRIPTORES PARA STRUCT USB_CORE_DESCS_T -----------------

ALIGNED(4) const uint8_t USB_DeviceDescriptor[] = {
   USB_DEVICE_DESC_SIZE,         /* bLength: sizeof(USB_DEVICE_DESCRIPTOR) */
   USB_DEVICE_DESCRIPTOR_TYPE,   /* bDescriptorType: 1 */
   WBVAL(0x0200),                /* bcdUSB: 2.00 */
   0x00,                         /* bDeviceClass */
   0x00,                         /* bDeviceSubClass */
   0x00,                         /* bDeviceProtocol */
   USB_MAX_PACKET0,              /* bMaxPacketSize0: 64 (prohibido cambiar) */
   WBVAL(0x1FC9),                /* idVendor */
   WBVAL(0x0086),                /* idProduct */
   WBVAL(0x0100),                /* bcdDevice */
   0x01,                         /* iManufacturer */
   0x02,                         /* iProduct */
   0x03,                         /* iSerialNumber */
   0x01                          /* bNumConfigurations */
};


const uint8_t USB_StringDescriptor[] = {
   /* Index 0x00: LANGID Codes */
   0x04,							      /* bLength */
   USB_STRING_DESCRIPTOR_TYPE,   /* bDescriptorType: 3 */
   WBVAL(0x0409),					   /* wLANGID  0x0409 = US English*/
   /* Index 0x01: Manufacturer */
   (18 * 2 + 2),					   /* bLength (18 Char + Type + length) */
   USB_STRING_DESCRIPTOR_TYPE,   /* bDescriptorType: 3 */
   'N', 0,
   'X', 0,
   'P', 0,
   ' ', 0,
   'S', 0,
   'e', 0,
   'm', 0,
   'i', 0,
   'c', 0,
   'o', 0,
   'n', 0,
   'd', 0,
   'u', 0,
   'c', 0,
   't', 0,
   'o', 0,
   'r', 0,
   's', 0,
   /* Index 0x02: Product */
   (16 * 2 + 2),					   /* bLength (16 Char + Type + length) */
   USB_STRING_DESCRIPTOR_TYPE,   /* bDescriptorType */
   'L', 0,
   'P', 0,
   'C', 0,
   '1', 0,
   '8', 0,
   'x', 0,
   'x', 0,
   ' ', 0,
   'G', 0,
   'A', 0,
   'M', 0,
   'E', 0,
   'P', 0,
   'A', 0,
   'D', 0,
   ' ', 0,
   /* Index 0x03: Serial Number */
   (13 * 2 + 2),					   /* bLength (13 Char + Type + length) */
   USB_STRING_DESCRIPTOR_TYPE,   /* bDescriptorType: 3 */
   'A', 0,
   'B', 0,
   'C', 0,
   'D', 0,
   '1', 0,
   '2', 0,
   '3', 0,
   '4', 0,
   '5', 0,
   '6', 0,
   '7', 0,
   '8', 0,
   '9', 0,
   /* Index 0x04: Interface 0, Alternate Setting 0 */
   (12 * 2 + 2),					   /* bLength (12 Char + Type + length) */
   USB_STRING_DESCRIPTOR_TYPE,   /* bDescriptorType: 3 */
   'H', 0,
   'I', 0,
   'D', 0,
   ' ', 0,
   'G', 0,
   'A', 0,
   'M', 0,
   'E', 0,
   'P', 0,
   'A', 0,
   'D', 0,
   ' ', 0,
};


ALIGNED(4) uint8_t USB_FsConfigDescriptor[] = {
   /* Configuration 1 */
   USB_CONFIGURATION_DESC_SIZE,                /* bLength: sizeof(USB_CONFIGURATION_DESCRIPTOR) */
   USB_CONFIGURATION_DESCRIPTOR_TYPE,          /* bDescriptorType: 2 */
   WBVAL(                                      /* wTotalLength */
      USB_CONFIGURATION_DESC_SIZE   +
      USB_INTERFACE_DESC_SIZE     +
      HID_DESC_SIZE               +
      USB_ENDPOINT_DESC_SIZE
      ),
   0x01,                                       /* bNumInterfaces: 1 (ok) */
   0x01,                                       /* bConfigurationValue: 1 (ok) */
   0x00,                                       /* iConfiguration */
   USB_CONFIG_SELF_POWERED,                    /* bmAttributes: 0xC0 */
   USB_CONFIG_POWER_MA(2),                     /* bMaxPower: 2/2 = 1 */

   /* Interface 0, Alternate Setting 0, HID Class */
   USB_INTERFACE_DESC_SIZE,                    /* bLength: sizeof(USB_INTERFACE_DESCRIPTOR) */
   USB_INTERFACE_DESCRIPTOR_TYPE,              /* bDescriptorType: 4 */
   0x00,                                       /* bInterfaceNumber: 0 (ok) */
   0x00,                                       /* bAlternateSetting: 0 (ok) */
   0x01,                                       /* bNumEndpoints: 1 (ok) */
   USB_DEVICE_CLASS_HUMAN_INTERFACE,           /* bInterfaceClass: 3 (HID, ok) */
   HID_SUBCLASS_BOOT,                          /* bInterfaceSubClass */
   HID_PROTOCOL_NONE,                          /* bInterfaceProtocol: 0 (ok) */
   0x04,                                       /* iInterface */
   /* HID Class Descriptor */
   /* HID_DESC_OFFSET = 0x0012 */
   HID_DESC_SIZE,                              /* bLength: sizeof(HID_DESCRIPTOR) */
   HID_HID_DESCRIPTOR_TYPE,                    /* bDescriptorType: 21 */
   WBVAL(0x0111),                              /* bcdHID : 1.11*/
   0x00,                                       /* bCountryCode */
   0x01,                                       /* bNumDescriptors */
   HID_REPORT_DESCRIPTOR_TYPE,                 /* bDescriptorType: 22 */
   WBVAL(sizeof(Gamepad_ReportDescriptor)),    /* wDescriptorLength */
   /* Endpoint, HID Interrupt In */
   USB_ENDPOINT_DESC_SIZE,                     /* bLength: sizeof(USB_ENDPOINT_DESCRIPTOR) */
   USB_ENDPOINT_DESCRIPTOR_TYPE,               /* bDescriptorType: 5 */
   HID_EP_IN,                                  /* bEndpointAddress: 0x81 (Input Number 1, ok) */
   USB_ENDPOINT_TYPE_INTERRUPT,                /* bmAttributes: 3 (interrupt, ok) */
   WBVAL(0x0008),                              /* wMaxPacketSize (8 bytes = 64) */
   0x0A,                                       /* bInterval (polling cada 10 ms, ok) */
   /* Terminator */
   0                                           /* bLength */
};


ALIGNED(4) uint8_t USB_HsConfigDescriptor[] = {
   /* Configuration 1 */
   USB_CONFIGURATION_DESC_SIZE,                /* bLength: sizeof(USB_CONFIGURATION_DESCRIPTOR) */
   USB_CONFIGURATION_DESCRIPTOR_TYPE,          /* bDescriptorType: 2 */
   WBVAL(                                      /* wTotalLength */
      USB_CONFIGURATION_DESC_SIZE +
      USB_INTERFACE_DESC_SIZE     +
      HID_DESC_SIZE               +
      USB_ENDPOINT_DESC_SIZE
      ),
   0x01,                                       /* bNumInterfaces */
   0x01,                                       /* bConfigurationValue */
   0x00,                                       /* iConfiguration */
   USB_CONFIG_SELF_POWERED,                    /* bmAttributes: 0xC0 */
   USB_CONFIG_POWER_MA(2),                     /* bMaxPower: 1 */

   /* Interface 0, Alternate Setting 0, HID Class */
   USB_INTERFACE_DESC_SIZE,                    /* bLength: sizeof(USB_INTERFACE_DESCRIPTOR) */
   USB_INTERFACE_DESCRIPTOR_TYPE,              /* bDescriptorType: 4 */
   0x00,                                       /* bInterfaceNumber */
   0x00,                                       /* bAlternateSetting */
   0x01,                                       /* bNumEndpoints */
   USB_DEVICE_CLASS_HUMAN_INTERFACE,           /* bInterfaceClass: 3 (HID) */
   HID_SUBCLASS_BOOT,                          /* bInterfaceSubClass: 1 */
   HID_PROTOCOL_NONE,                          /* bInterfaceProtocol: 0 (caso GamePad) */
   0x04,                                       /* iInterface */
   /* HID Class Descriptor */
   /* HID_DESC_OFFSET = 0x0012 */
   HID_DESC_SIZE,                              /* bLength: sizeof(HID_DESCRIPTOR) */
   HID_HID_DESCRIPTOR_TYPE,                    /* bDescriptorType: 21 */
   WBVAL(0x0111),                              /* bcdHID : 1.11*/
   0x00,                                       /* bCountryCode */
   0x01,                                       /* bNumDescriptors */
   HID_REPORT_DESCRIPTOR_TYPE,                 /* bDescriptorType: 22 */
   WBVAL(sizeof(Gamepad_ReportDescriptor)),    /* wDescriptorLength */
   /* Endpoint, HID Interrupt In */
   USB_ENDPOINT_DESC_SIZE,                     /* bLength: sizeof(USB_ENDPOINT_DESCRIPTOR) */
   USB_ENDPOINT_DESCRIPTOR_TYPE,               /* bDescriptorType: 5 */
   HID_EP_IN,                                  /* bEndpointAddress: 0x81 (Input Number 1) */
   USB_ENDPOINT_TYPE_INTERRUPT,                /* bmAttributes: 3 */
   WBVAL(0x0008),                              /* wMaxPacketSize */
   0x08,                                       /* bInterval */
   /* Terminator */
   0                                           /* bLength */
};


ALIGNED(4) const uint8_t USB_DeviceQualifier[] = {
   USB_DEVICE_QUALI_SIZE,                  /* bLength: sizeof */
   USB_DEVICE_QUALIFIER_DESCRIPTOR_TYPE,   /* bDescriptorType: 6 */
   WBVAL(0x0200),                          /* bcdUSB: 2.00 */
   0x00,                                   /* bDeviceClass */
   0x00,                                   /* bDeviceSubClass */
   0x00,                                   /* bDeviceProtocol */
   USB_MAX_PACKET0,                        /* bMaxPacketSize0: 64 (prohibido cambiar) */
   0x01,                                   /* bNumOtherSpeedConfigurations */
   0x00                                    /* bReserved */
};

