/*
 * Name   :  teeny_usb_desc.c
 * Author :  admin@xtoolbox.org
 * Date   :  2020-07-21 09:58:11

 * Desc   :  This file is auto generate by the TeenyDT
 *           Visit http://dt.tusb.org for more info
 */

/*
  Input source name:  descriptor.lua
  
  Content type is lua script:
  ------------- lua script begin ------------
local s = arg[1]:find("[^/\\]+$")
local sep = arg[1]:sub(s,s)
local p = arg[1]:sub(1, s-1) .. "?.lua"
package.path = package.path .. ";".. p

local desc_list = {
    { File = "composite_desc",     Description = "Composite"        },
    { File = "cdc_acm_desc",       Description = "CDC ACM"          },
    { File = "cdc_acm5_desc",      Description = "CDC ACM5"         },
    { File = "cdc_rndis_desc",     Description = "CDC RNDIS"        },
    { File = "winusb_desc",        Description = "WinUSB"           },
    { File = "winusb20_desc",      Description = "WinUSB20"         },
    { File = "hid_user_desc",      Description = "User HID"         },
    { File = "hid_kb_desc",        Description = "HID Keyboard"     },
    { File = "hid_mouse_desc",     Description = "HID Mouse"        },
    { File = "msc_desc",           Description = "Mass storage"     },
    { File = "daplinkv1_desc",     Description = "DAPLink V1"       },
    { File = "daplinkv2_desc",     Description = "DAPLink V2"       },
    { File = "multi_config_desc",  Description = "Multi Config"     },
    { File = "simplest_desc",      Description = "Simplest"         },
}

local descriptors = {}
for i,v in ipairs(desc_list) do
    descriptors[#descriptors+1] = require(v.File)
end

return descriptors


  ------------- lua script end   ------------
 */
/////////////////////////////////////////
//// Device 0
/////////////////////////////////////////
#include "teeny_usb.h"

#define  COMP_DEVICE_DESCRIPTOR_SIZE  (18)
__ALIGN_BEGIN  const uint8_t COMP_DeviceDescriptor [18] __ALIGN_END = {
  ///////////////////////////////////////
  /// device descriptor
  ///////////////////////////////////////
  0x12,                                             /* bLength */
  USB_DEVICE_DESCRIPTOR_TYPE,                       /* bDescriptorType */
  0x00, 0x02,                                       /* bcdUSB */
  0xef,                                             /* bDeviceClass */
  0x02,                                             /* bDeviceSubClass */
  0x01,                                             /* bDeviceProtocol */
  0x40,                                             /* bMaxPacketSize */
  0x83, 0x04,                                       /* idVendor */
  0x11, 0x00,                                       /* idProduct */
  0x00, 0x01,                                       /* bcdDevice */
  0x01,                                             /* iManufacturer */
  0x02,                                             /* iProduct */
  0x03,                                             /* iSerial */
  0x01,                                             /* bNumConfigurations */
};
#define  COMP_CONFIG_DESCRIPTOR_SIZE  (153)
__ALIGN_BEGIN  const uint8_t COMP_ConfigDescriptor [153] __ALIGN_END = {
  ///////////////////////////////////////
  /// config descriptor
  ///////////////////////////////////////
  0x09,                                             /* bLength */
  USB_CONFIGURATION_DESCRIPTOR_TYPE,                /* bDescriptorType */
  0x99, 0x00,                                       /* wTotalLength */
  0x05,                                             /* bNumInterfaces */
  0x01,                                             /* bConfigurationValue */
  0x00,                                             /* iConfiguration */
  0x80,                                             /* bmAttributes */
  0x64,                                             /* bMaxPower */
  
  ///////////////////////////////////////
  /// interface descriptor
  ///////////////////////////////////////
  0x09,                                             /* bLength */
  USB_INTERFACE_DESCRIPTOR_TYPE,                    /* bDescriptorType */
  0x00,                                             /* bInterfaceNumber */
  0x00,                                             /* bAlternateSetting */
  0x02,                                             /* bNumEndpoints */
  0x03,                                             /* bInterfaceClass */
  0x00,                                             /* bInterfaceSubClass */
  0x00,                                             /* bInterfaceProtocol */
  0x00,                                             /* iInterface */
  
  ///////////////////////////////////////
  /// hid descriptor
  ///////////////////////////////////////
  0x09,                                             /* bLength */
  0x21,                                             /* bDescriptorType */
  0x11, 0x01,                                       /* bcdHID */
  0x00,                                             /* bCountryCode */
  0x01,                                             /* bNumDescriptors */
  0x22,                                             /* bDescriptorType1 */
  0x18, 0x00,                                       /* wDescriptorLength1 */
  
  ///////////////////////////////////////
  /// endpoint descriptor
  ///////////////////////////////////////
  0x07,                                             /* bLength */
  USB_ENDPOINT_DESCRIPTOR_TYPE,                     /* bDescriptorType */
  0x82,                                             /* bEndpointAddress */
  0x03,                                             /* bmAttributes */
  0x10, 0x00,                                       /* wMaxPacketSize */
  0x01,                                             /* bInterval */
  
  ///////////////////////////////////////
  /// endpoint descriptor
  ///////////////////////////////////////
  0x07,                                             /* bLength */
  USB_ENDPOINT_DESCRIPTOR_TYPE,                     /* bDescriptorType */
  0x02,                                             /* bEndpointAddress */
  0x03,                                             /* bmAttributes */
  0x10, 0x00,                                       /* wMaxPacketSize */
  0x01,                                             /* bInterval */
  
  ///////////////////////////////////////
  /// interface association descriptor
  ///////////////////////////////////////
  0x08,                                             /* bLength */
  USB_IAD_DESCRIPTOR_TYPE,                          /* bDescriptorType */
  0x01,                                             /* bFirstInterface */
  0x02,                                             /* bInterfaceCount */
  0x02,                                             /* bFunctionClass */
  0x02,                                             /* bFunctionSubClass */
  0x01,                                             /* bFunctionProtocol */
  0x00,                                             /* iFunction */
  
  ///////////////////////////////////////
  /// interface descriptor
  ///////////////////////////////////////
  0x09,                                             /* bLength */
  USB_INTERFACE_DESCRIPTOR_TYPE,                    /* bDescriptorType */
  0x01,                                             /* bInterfaceNumber */
  0x00,                                             /* bAlternateSetting */
  0x01,                                             /* bNumEndpoints */
  0x02,                                             /* bInterfaceClass */
  0x02,                                             /* bInterfaceSubClass */
  0x01,                                             /* bInterfaceProtocol */
  0x00,                                             /* iInterface */
  
  ///////////////////////////////////////
  /// cdc acm header descriptor
  ///////////////////////////////////////
  0x05,                                             /* bLength */
  0x24,                                             /* bDescriptorType */
  0x00,                                             /* bDescriptorSubtype */
  0x10, 0x01,                                       /* bcdCDC */
  
  ///////////////////////////////////////
  /// cdc acm call management descriptor
  ///////////////////////////////////////
  0x05,                                             /* bLength */
  0x24,                                             /* bDescriptorType */
  0x01,                                             /* bDescriptorSubtype */
  0x00,                                             /* bmCapabilities */
  0x01,                                             /* bDataInterface */
  
  ///////////////////////////////////////
  /// cdc acm descriptor
  ///////////////////////////////////////
  0x04,                                             /* bLength */
  0x24,                                             /* bDescriptorType */
  0x02,                                             /* bDescriptorSubtype */
  0x02,                                             /* bmCapabilities */
  
  ///////////////////////////////////////
  /// cdc acm union descriptor
  ///////////////////////////////////////
  0x05,                                             /* bLength */
  0x24,                                             /* bDescriptorType */
  0x06,                                             /* bDescriptorSubtype */
  0x00,                                             /* bMasterInterface */
  0x01,                                             /* bSlaveInterface0 */
  
  ///////////////////////////////////////
  /// endpoint descriptor
  ///////////////////////////////////////
  0x07,                                             /* bLength */
  USB_ENDPOINT_DESCRIPTOR_TYPE,                     /* bDescriptorType */
  0x88,                                             /* bEndpointAddress */
  0x03,                                             /* bmAttributes */
  0x10, 0x00,                                       /* wMaxPacketSize */
  0x01,                                             /* bInterval */
  
  ///////////////////////////////////////
  /// interface descriptor
  ///////////////////////////////////////
  0x09,                                             /* bLength */
  USB_INTERFACE_DESCRIPTOR_TYPE,                    /* bDescriptorType */
  0x02,                                             /* bInterfaceNumber */
  0x00,                                             /* bAlternateSetting */
  0x02,                                             /* bNumEndpoints */
  0x0a,                                             /* bInterfaceClass */
  0x00,                                             /* bInterfaceSubClass */
  0x00,                                             /* bInterfaceProtocol */
  0x00,                                             /* iInterface */
  
  ///////////////////////////////////////
  /// endpoint descriptor
  ///////////////////////////////////////
  0x07,                                             /* bLength */
  USB_ENDPOINT_DESCRIPTOR_TYPE,                     /* bDescriptorType */
  0x81,                                             /* bEndpointAddress */
  0x02,                                             /* bmAttributes */
  0x20, 0x00,                                       /* wMaxPacketSize */
  0x01,                                             /* bInterval */
  
  ///////////////////////////////////////
  /// endpoint descriptor
  ///////////////////////////////////////
  0x07,                                             /* bLength */
  USB_ENDPOINT_DESCRIPTOR_TYPE,                     /* bDescriptorType */
  0x01,                                             /* bEndpointAddress */
  0x02,                                             /* bmAttributes */
  0x20, 0x00,                                       /* wMaxPacketSize */
  0x01,                                             /* bInterval */
  
  ///////////////////////////////////////
  /// interface descriptor
  ///////////////////////////////////////
  0x09,                                             /* bLength */
  USB_INTERFACE_DESCRIPTOR_TYPE,                    /* bDescriptorType */
  0x03,                                             /* bInterfaceNumber */
  0x00,                                             /* bAlternateSetting */
  0x02,                                             /* bNumEndpoints */
  0xff,                                             /* bInterfaceClass */
  0xff,                                             /* bInterfaceSubClass */
  0x00,                                             /* bInterfaceProtocol */
  0x04,                                             /* iInterface */
  
  ///////////////////////////////////////
  /// endpoint descriptor
  ///////////////////////////////////////
  0x07,                                             /* bLength */
  USB_ENDPOINT_DESCRIPTOR_TYPE,                     /* bDescriptorType */
  0x83,                                             /* bEndpointAddress */
  0x02,                                             /* bmAttributes */
  0x20, 0x00,                                       /* wMaxPacketSize */
  0x01,                                             /* bInterval */
  
  ///////////////////////////////////////
  /// endpoint descriptor
  ///////////////////////////////////////
  0x07,                                             /* bLength */
  USB_ENDPOINT_DESCRIPTOR_TYPE,                     /* bDescriptorType */
  0x03,                                             /* bEndpointAddress */
  0x02,                                             /* bmAttributes */
  0x20, 0x00,                                       /* wMaxPacketSize */
  0x01,                                             /* bInterval */
  
  ///////////////////////////////////////
  /// interface descriptor
  ///////////////////////////////////////
  0x09,                                             /* bLength */
  USB_INTERFACE_DESCRIPTOR_TYPE,                    /* bDescriptorType */
  0x04,                                             /* bInterfaceNumber */
  0x00,                                             /* bAlternateSetting */
  0x02,                                             /* bNumEndpoints */
  0x08,                                             /* bInterfaceClass */
  0x06,                                             /* bInterfaceSubClass */
  0x50,                                             /* bInterfaceProtocol */
  0x00,                                             /* iInterface */
  
  ///////////////////////////////////////
  /// endpoint descriptor
  ///////////////////////////////////////
  0x07,                                             /* bLength */
  USB_ENDPOINT_DESCRIPTOR_TYPE,                     /* bDescriptorType */
  0x84,                                             /* bEndpointAddress */
  0x02,                                             /* bmAttributes */
  0x40, 0x00,                                       /* wMaxPacketSize */
  0x01,                                             /* bInterval */
  
  ///////////////////////////////////////
  /// endpoint descriptor
  ///////////////////////////////////////
  0x07,                                             /* bLength */
  USB_ENDPOINT_DESCRIPTOR_TYPE,                     /* bDescriptorType */
  0x04,                                             /* bEndpointAddress */
  0x02,                                             /* bmAttributes */
  0x40, 0x00,                                       /* wMaxPacketSize */
  0x01,                                             /* bInterval */
};
#define  COMP_STRING_DESCRIPTOR0_STR   "\x09\x04"
#define  COMP_STRING_DESCRIPTOR0_SIZE  (4)
WEAK __ALIGN_BEGIN  const uint8_t COMP_StringDescriptor0 [4] __ALIGN_END = {
  0x04,                                         /* bLength */
  USB_STRING_DESCRIPTOR_TYPE,                   /* bDescriptorType */
  0x09, 0x04,                                   /* wLangID0 */
};
#define  COMP_STRING_DESCRIPTOR1_STR   "TeenyUSB"
#define  COMP_STRING_DESCRIPTOR1_SIZE   (18)
WEAK __ALIGN_BEGIN  const uint8_t COMP_StringDescriptor1 [18] __ALIGN_END = {
  0x12,                                             /* bLength */
  USB_STRING_DESCRIPTOR_TYPE,                       /* bDescriptorType */
  'T', 0x00,                                        /* wcChar0 */
  'e', 0x00,                                        /* wcChar1 */
  'e', 0x00,                                        /* wcChar2 */
  'n', 0x00,                                        /* wcChar3 */
  'y', 0x00,                                        /* wcChar4 */
  'U', 0x00,                                        /* wcChar5 */
  'S', 0x00,                                        /* wcChar6 */
  'B', 0x00,                                        /* wcChar7 */
};
#define  COMP_STRING_DESCRIPTOR2_STR   "TeenyUSB Composite DEMO"
#define  COMP_STRING_DESCRIPTOR2_SIZE   (48)
WEAK __ALIGN_BEGIN  const uint8_t COMP_StringDescriptor2 [48] __ALIGN_END = {
  0x30,                                             /* bLength */
  USB_STRING_DESCRIPTOR_TYPE,                       /* bDescriptorType */
  'T', 0x00,                                        /* wcChar0 */
  'e', 0x00,                                        /* wcChar1 */
  'e', 0x00,                                        /* wcChar2 */
  'n', 0x00,                                        /* wcChar3 */
  'y', 0x00,                                        /* wcChar4 */
  'U', 0x00,                                        /* wcChar5 */
  'S', 0x00,                                        /* wcChar6 */
  'B', 0x00,                                        /* wcChar7 */
  ' ', 0x00,                                        /* wcChar8 */
  'C', 0x00,                                        /* wcChar9 */
  'o', 0x00,                                        /* wcChar10 */
  'm', 0x00,                                        /* wcChar11 */
  'p', 0x00,                                        /* wcChar12 */
  'o', 0x00,                                        /* wcChar13 */
  's', 0x00,                                        /* wcChar14 */
  'i', 0x00,                                        /* wcChar15 */
  't', 0x00,                                        /* wcChar16 */
  'e', 0x00,                                        /* wcChar17 */
  ' ', 0x00,                                        /* wcChar18 */
  'D', 0x00,                                        /* wcChar19 */
  'E', 0x00,                                        /* wcChar20 */
  'M', 0x00,                                        /* wcChar21 */
  'O', 0x00,                                        /* wcChar22 */
};
#define  COMP_STRING_DESCRIPTOR3_STR   "TUSB123456"
#define  COMP_STRING_DESCRIPTOR3_SIZE   (22)
WEAK __ALIGN_BEGIN  const uint8_t COMP_StringDescriptor3 [22] __ALIGN_END = {
  0x16,                                             /* bLength */
  USB_STRING_DESCRIPTOR_TYPE,                       /* bDescriptorType */
  'T', 0x00,                                        /* wcChar0 */
  'U', 0x00,                                        /* wcChar1 */
  'S', 0x00,                                        /* wcChar2 */
  'B', 0x00,                                        /* wcChar3 */
  '1', 0x00,                                        /* wcChar4 */
  '2', 0x00,                                        /* wcChar5 */
  '3', 0x00,                                        /* wcChar6 */
  '4', 0x00,                                        /* wcChar7 */
  '5', 0x00,                                        /* wcChar8 */
  '6', 0x00,                                        /* wcChar9 */
};
#define  COMP_STRING_DESCRIPTOR4_STR   "TeenyUSB WinUSB"
#define  COMP_STRING_DESCRIPTOR4_SIZE   (32)
WEAK __ALIGN_BEGIN  const uint8_t COMP_StringDescriptor4 [32] __ALIGN_END = {
  0x20,                                             /* bLength */
  USB_STRING_DESCRIPTOR_TYPE,                       /* bDescriptorType */
  'T', 0x00,                                        /* wcChar0 */
  'e', 0x00,                                        /* wcChar1 */
  'e', 0x00,                                        /* wcChar2 */
  'n', 0x00,                                        /* wcChar3 */
  'y', 0x00,                                        /* wcChar4 */
  'U', 0x00,                                        /* wcChar5 */
  'S', 0x00,                                        /* wcChar6 */
  'B', 0x00,                                        /* wcChar7 */
  ' ', 0x00,                                        /* wcChar8 */
  'W', 0x00,                                        /* wcChar9 */
  'i', 0x00,                                        /* wcChar10 */
  'n', 0x00,                                        /* wcChar11 */
  'U', 0x00,                                        /* wcChar12 */
  'S', 0x00,                                        /* wcChar13 */
  'B', 0x00,                                        /* wcChar14 */
};
#define COMP_STRING_COUNT    (5)
const uint8_t* const COMP_StringDescriptors[5] = {
  COMP_StringDescriptor0,
  COMP_StringDescriptor1,
  COMP_StringDescriptor2,
  COMP_StringDescriptor3,
  COMP_StringDescriptor4,
};
#define COMP_REPORT_DESCRIPTOR_SIZE_IF0  (24)
WEAK __ALIGN_BEGIN const uint8_t COMP_ReportDescriptor_if0[COMP_REPORT_DESCRIPTOR_SIZE_IF0] __ALIGN_END = {
        // report descriptor for general input/output
        0x06, 0x00, 0xFF,  // Usage Page (Vendor Defined 0xFF00)
        0x09, 0x01,        // Usage (0x01)
        0xA1, 0x01,        // Collection (Application)
        0x09, 0x02,        //   Usage (0x02)
        0x15, 0x00,        //   Logical Minimum (0)
        0x25, 0xFF,        //   Logical Maximum (255)
        0x75, 0x08,        //   Report Size (8)
        0x95, 0x10,        //   Report Count (16)
        0x81, 0x02,        //   Input (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position)
        0x09, 0x03,        //   Usage (0x03)
        0x91, 0x02,        //   Output (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position,Non-volatile)
        0xC0               // End Collection
    };


//////////////////////////////////////////////////////
///// WCID descripors
//////////////////////////////////////////////////////
#if defined(HAS_WCID)

// Define WCID os string descriptor 
#ifndef WCID_MSOS_STRING
#define WCID_MSOS_STRING
#define WCID_STRING_DESCRIPTOR_MSOS_STR          "MSFT100"
#define WCID_STRING_DESCRIPTOR_MSOS_SIZE          (18)
WEAK __ALIGN_BEGIN const uint8_t  WCID_StringDescriptor_MSOS [18] __ALIGN_END = {
  ///////////////////////////////////////
  /// MS OS string descriptor
  ///////////////////////////////////////
  0x12,                                             /* bLength */
  USB_STRING_DESCRIPTOR_TYPE,                       /* bDescriptorType */
  /* MSFT100 */
  'M', 0x00, 'S', 0x00, 'F', 0x00, 'T', 0x00,       /* wcChar_7 */
  '1', 0x00, '0', 0x00, '0', 0x00,                  /* wcChar_7 */
  WCID_VENDOR_CODE,                                 /* bVendorCode */
  0x00,                                             /* bReserved */
};

#endif // WCID_MSOS_STRING
#define  COMP_IF3_WCID_PROPERTIES_SIZE  (142)
WEAK __ALIGN_BEGIN const uint8_t COMP_IF3_WCIDProperties [142] __ALIGN_END = {
  ///////////////////////////////////////
  /// WCID property descriptor
  ///////////////////////////////////////
  0x8e, 0x00, 0x00, 0x00,                           /* dwLength */
  0x00, 0x01,                                       /* bcdVersion */
  0x05, 0x00,                                       /* wIndex */
  0x01, 0x00,                                       /* wCount */
  
  ///////////////////////////////////////
  /// registry propter descriptor
  ///////////////////////////////////////
  0x84, 0x00, 0x00, 0x00,                           /* dwSize */
  0x01, 0x00, 0x00, 0x00,                           /* dwPropertyDataType */
  0x28, 0x00,                                       /* wPropertyNameLength */
  /* DeviceInterfaceGUID */
  'D', 0x00, 'e', 0x00, 'v', 0x00, 'i', 0x00,       /* wcName_20 */
  'c', 0x00, 'e', 0x00, 'I', 0x00, 'n', 0x00,       /* wcName_20 */
  't', 0x00, 'e', 0x00, 'r', 0x00, 'f', 0x00,       /* wcName_20 */
  'a', 0x00, 'c', 0x00, 'e', 0x00, 'G', 0x00,       /* wcName_20 */
  'U', 0x00, 'I', 0x00, 'D', 0x00, 0x00, 0x00,      /* wcName_20 */
  0x4e, 0x00, 0x00, 0x00,                           /* dwPropertyDataLength */
  /* {1D4B2365-4749-48EA-B38A-7C6FDDDD7E26} */
  '{', 0x00, '1', 0x00, 'D', 0x00, '4', 0x00,       /* wcData_39 */
  'B', 0x00, '2', 0x00, '3', 0x00, '6', 0x00,       /* wcData_39 */
  '5', 0x00, '-', 0x00, '4', 0x00, '7', 0x00,       /* wcData_39 */
  '4', 0x00, '9', 0x00, '-', 0x00, '4', 0x00,       /* wcData_39 */
  '8', 0x00, 'E', 0x00, 'A', 0x00, '-', 0x00,       /* wcData_39 */
  'B', 0x00, '3', 0x00, '8', 0x00, 'A', 0x00,       /* wcData_39 */
  '-', 0x00, '7', 0x00, 'C', 0x00, '6', 0x00,       /* wcData_39 */
  'F', 0x00, 'D', 0x00, 'D', 0x00, 'D', 0x00,       /* wcData_39 */
  'D', 0x00, '7', 0x00, 'E', 0x00, '2', 0x00,       /* wcData_39 */
  '6', 0x00, '}', 0x00, 0x00, 0x00,                 /* wcData_39 */
};
#define  COMP_WCID_DESCRIPTOR_SIZE  (40)
WEAK __ALIGN_BEGIN const uint8_t COMP_WCIDDescriptor [40] __ALIGN_END = {
  ///////////////////////////////////////
  /// WCID descriptor
  ///////////////////////////////////////
  0x28, 0x00, 0x00, 0x00,                           /* dwLength */
  0x00, 0x01,                                       /* bcdVersion */
  0x04, 0x00,                                       /* wIndex */
  0x01,                                             /* bCount */
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,         /* bReserved_7 */
  
  ///////////////////////////////////////
  /// WCID function descriptor
  ///////////////////////////////////////
  0x03,                                             /* bFirstInterfaceNumber */
  0x01,                                             /* bReserved */
  /* WINUSB */
  'W', 'I', 'N', 'U', 'S', 'B', 0x00, 0x00,         /* cCID_8 */
  /*  */
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,   /* cSubCID_8 */
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00,               /* bReserved_6 */
};
#define COMP_WCID_PROPERTIES_SIZE (5)
WEAK __ALIGN_BEGIN const desc_t COMP_WCIDProperties[ COMP_WCID_PROPERTIES_SIZE ] __ALIGN_END = {
  0,    // No WCID in Interface 0
  0,    // No WCID in Interface 1
  0,    // No WCID in Interface 2
  COMP_IF3_WCIDProperties,
  0,    // No WCID in Interface 4
};
#endif    // #if defined(HAS_WCID)


COMP_TXEP_MAX_SIZE
COMP_RXEP_MAX_SIZE
//  Device descriptors
const tusb_descriptors COMP_descriptors = {
  .device = COMP_DeviceDescriptor,
  .config = COMP_ConfigDescriptor,
  .strings = COMP_StringDescriptors,
  .string_cnt = COMP_STRING_COUNT,
#if defined(HAS_WCID)
#if defined(COMP_WCID_DESCRIPTOR_SIZE)
  .wcid_desc = COMP_WCIDDescriptor,
#else
  .wcid_desc = 0,
#endif // COMP_WCID_DESCRIPTOR_SIZE)

#if defined(COMP_WCID_PROPERTIES_SIZE)
  .wcid_properties = COMP_WCIDProperties,
#else
  .wcid_properties = 0,
#endif // COMP_WCID_PROPERTIES_SIZE

#endif // HAS_WCID

#if defined(HAS_WCID_20)
#if defined(COMP_WCID_BOS_SIZE)
  .wcid_bos = COMP_WCIDBOS,
#else
  .wcid_bos = 0,  
#endif // COMP_WCID_BOS_SIZE)

#if defined(COMP_WCID_DESC_SET_SIZE)
  .wcid_desc_set = COMP_WCIDDescriptorSet,
#else
  .wcid_desc_set = 0,  
#endif // COMP_WCID_DESC_SET_SIZE


#endif // HAS_WCID_20
};
/////////////////////////////////////////
//// Device 1
/////////////////////////////////////////
#include "teeny_usb.h"

#define  CDC_ACM_DEVICE_DESCRIPTOR_SIZE  (18)
__ALIGN_BEGIN  const uint8_t CDC_ACM_DeviceDescriptor [18] __ALIGN_END = {
  ///////////////////////////////////////
  /// device descriptor
  ///////////////////////////////////////
  0x12,                                             /* bLength */
  USB_DEVICE_DESCRIPTOR_TYPE,                       /* bDescriptorType */
  0x00, 0x02,                                       /* bcdUSB */
  0xef,                                             /* bDeviceClass */
  0x02,                                             /* bDeviceSubClass */
  0x01,                                             /* bDeviceProtocol */
  0x40,                                             /* bMaxPacketSize */
  0x83, 0x04,                                       /* idVendor */
  0x11, 0x00,                                       /* idProduct */
  0x00, 0x01,                                       /* bcdDevice */
  0x01,                                             /* iManufacturer */
  0x02,                                             /* iProduct */
  0x03,                                             /* iSerial */
  0x01,                                             /* bNumConfigurations */
};
#define  CDC_ACM_CONFIG_DESCRIPTOR_SIZE  (75)
__ALIGN_BEGIN  const uint8_t CDC_ACM_ConfigDescriptor [75] __ALIGN_END = {
  ///////////////////////////////////////
  /// config descriptor
  ///////////////////////////////////////
  0x09,                                             /* bLength */
  USB_CONFIGURATION_DESCRIPTOR_TYPE,                /* bDescriptorType */
  0x4b, 0x00,                                       /* wTotalLength */
  0x02,                                             /* bNumInterfaces */
  0x01,                                             /* bConfigurationValue */
  0x00,                                             /* iConfiguration */
  0x80,                                             /* bmAttributes */
  0x64,                                             /* bMaxPower */
  
  ///////////////////////////////////////
  /// interface association descriptor
  ///////////////////////////////////////
  0x08,                                             /* bLength */
  USB_IAD_DESCRIPTOR_TYPE,                          /* bDescriptorType */
  0x00,                                             /* bFirstInterface */
  0x02,                                             /* bInterfaceCount */
  0x02,                                             /* bFunctionClass */
  0x02,                                             /* bFunctionSubClass */
  0x01,                                             /* bFunctionProtocol */
  0x00,                                             /* iFunction */
  
  ///////////////////////////////////////
  /// interface descriptor
  ///////////////////////////////////////
  0x09,                                             /* bLength */
  USB_INTERFACE_DESCRIPTOR_TYPE,                    /* bDescriptorType */
  0x00,                                             /* bInterfaceNumber */
  0x00,                                             /* bAlternateSetting */
  0x01,                                             /* bNumEndpoints */
  0x02,                                             /* bInterfaceClass */
  0x02,                                             /* bInterfaceSubClass */
  0x01,                                             /* bInterfaceProtocol */
  0x00,                                             /* iInterface */
  
  ///////////////////////////////////////
  /// cdc acm header descriptor
  ///////////////////////////////////////
  0x05,                                             /* bLength */
  0x24,                                             /* bDescriptorType */
  0x00,                                             /* bDescriptorSubtype */
  0x10, 0x01,                                       /* bcdCDC */
  
  ///////////////////////////////////////
  /// cdc acm call management descriptor
  ///////////////////////////////////////
  0x05,                                             /* bLength */
  0x24,                                             /* bDescriptorType */
  0x01,                                             /* bDescriptorSubtype */
  0x00,                                             /* bmCapabilities */
  0x01,                                             /* bDataInterface */
  
  ///////////////////////////////////////
  /// cdc acm descriptor
  ///////////////////////////////////////
  0x04,                                             /* bLength */
  0x24,                                             /* bDescriptorType */
  0x02,                                             /* bDescriptorSubtype */
  0x02,                                             /* bmCapabilities */
  
  ///////////////////////////////////////
  /// cdc acm union descriptor
  ///////////////////////////////////////
  0x05,                                             /* bLength */
  0x24,                                             /* bDescriptorType */
  0x06,                                             /* bDescriptorSubtype */
  0x00,                                             /* bMasterInterface */
  0x01,                                             /* bSlaveInterface0 */
  
  ///////////////////////////////////////
  /// endpoint descriptor
  ///////////////////////////////////////
  0x07,                                             /* bLength */
  USB_ENDPOINT_DESCRIPTOR_TYPE,                     /* bDescriptorType */
  0x88,                                             /* bEndpointAddress */
  0x03,                                             /* bmAttributes */
  0x10, 0x00,                                       /* wMaxPacketSize */
  0x01,                                             /* bInterval */
  
  ///////////////////////////////////////
  /// interface descriptor
  ///////////////////////////////////////
  0x09,                                             /* bLength */
  USB_INTERFACE_DESCRIPTOR_TYPE,                    /* bDescriptorType */
  0x01,                                             /* bInterfaceNumber */
  0x00,                                             /* bAlternateSetting */
  0x02,                                             /* bNumEndpoints */
  0x0a,                                             /* bInterfaceClass */
  0x00,                                             /* bInterfaceSubClass */
  0x00,                                             /* bInterfaceProtocol */
  0x00,                                             /* iInterface */
  
  ///////////////////////////////////////
  /// endpoint descriptor
  ///////////////////////////////////////
  0x07,                                             /* bLength */
  USB_ENDPOINT_DESCRIPTOR_TYPE,                     /* bDescriptorType */
  0x81,                                             /* bEndpointAddress */
  0x02,                                             /* bmAttributes */
  0x20, 0x00,                                       /* wMaxPacketSize */
  0x01,                                             /* bInterval */
  
  ///////////////////////////////////////
  /// endpoint descriptor
  ///////////////////////////////////////
  0x07,                                             /* bLength */
  USB_ENDPOINT_DESCRIPTOR_TYPE,                     /* bDescriptorType */
  0x01,                                             /* bEndpointAddress */
  0x02,                                             /* bmAttributes */
  0x20, 0x00,                                       /* wMaxPacketSize */
  0x01,                                             /* bInterval */
};
#define  CDC_ACM_STRING_DESCRIPTOR0_STR   "\x09\x04"
#define  CDC_ACM_STRING_DESCRIPTOR0_SIZE  (4)
WEAK __ALIGN_BEGIN  const uint8_t CDC_ACM_StringDescriptor0 [4] __ALIGN_END = {
  0x04,                                         /* bLength */
  USB_STRING_DESCRIPTOR_TYPE,                   /* bDescriptorType */
  0x09, 0x04,                                   /* wLangID0 */
};
#define  CDC_ACM_STRING_DESCRIPTOR1_STR   "TeenyUSB"
#define  CDC_ACM_STRING_DESCRIPTOR1_SIZE   (18)
WEAK __ALIGN_BEGIN  const uint8_t CDC_ACM_StringDescriptor1 [18] __ALIGN_END = {
  0x12,                                             /* bLength */
  USB_STRING_DESCRIPTOR_TYPE,                       /* bDescriptorType */
  'T', 0x00,                                        /* wcChar0 */
  'e', 0x00,                                        /* wcChar1 */
  'e', 0x00,                                        /* wcChar2 */
  'n', 0x00,                                        /* wcChar3 */
  'y', 0x00,                                        /* wcChar4 */
  'U', 0x00,                                        /* wcChar5 */
  'S', 0x00,                                        /* wcChar6 */
  'B', 0x00,                                        /* wcChar7 */
};
#define  CDC_ACM_STRING_DESCRIPTOR2_STR   "TeenyUSB CDC DEMO"
#define  CDC_ACM_STRING_DESCRIPTOR2_SIZE   (36)
WEAK __ALIGN_BEGIN  const uint8_t CDC_ACM_StringDescriptor2 [36] __ALIGN_END = {
  0x24,                                             /* bLength */
  USB_STRING_DESCRIPTOR_TYPE,                       /* bDescriptorType */
  'T', 0x00,                                        /* wcChar0 */
  'e', 0x00,                                        /* wcChar1 */
  'e', 0x00,                                        /* wcChar2 */
  'n', 0x00,                                        /* wcChar3 */
  'y', 0x00,                                        /* wcChar4 */
  'U', 0x00,                                        /* wcChar5 */
  'S', 0x00,                                        /* wcChar6 */
  'B', 0x00,                                        /* wcChar7 */
  ' ', 0x00,                                        /* wcChar8 */
  'C', 0x00,                                        /* wcChar9 */
  'D', 0x00,                                        /* wcChar10 */
  'C', 0x00,                                        /* wcChar11 */
  ' ', 0x00,                                        /* wcChar12 */
  'D', 0x00,                                        /* wcChar13 */
  'E', 0x00,                                        /* wcChar14 */
  'M', 0x00,                                        /* wcChar15 */
  'O', 0x00,                                        /* wcChar16 */
};
#define  CDC_ACM_STRING_DESCRIPTOR3_STR   "TUSB123456"
#define  CDC_ACM_STRING_DESCRIPTOR3_SIZE   (22)
WEAK __ALIGN_BEGIN  const uint8_t CDC_ACM_StringDescriptor3 [22] __ALIGN_END = {
  0x16,                                             /* bLength */
  USB_STRING_DESCRIPTOR_TYPE,                       /* bDescriptorType */
  'T', 0x00,                                        /* wcChar0 */
  'U', 0x00,                                        /* wcChar1 */
  'S', 0x00,                                        /* wcChar2 */
  'B', 0x00,                                        /* wcChar3 */
  '1', 0x00,                                        /* wcChar4 */
  '2', 0x00,                                        /* wcChar5 */
  '3', 0x00,                                        /* wcChar6 */
  '4', 0x00,                                        /* wcChar7 */
  '5', 0x00,                                        /* wcChar8 */
  '6', 0x00,                                        /* wcChar9 */
};
#define CDC_ACM_STRING_COUNT    (4)
const uint8_t* const CDC_ACM_StringDescriptors[4] = {
  CDC_ACM_StringDescriptor0,
  CDC_ACM_StringDescriptor1,
  CDC_ACM_StringDescriptor2,
  CDC_ACM_StringDescriptor3,
};


CDC_ACM_TXEP_MAX_SIZE
CDC_ACM_RXEP_MAX_SIZE
//  Device descriptors
const tusb_descriptors CDC_ACM_descriptors = {
  .device = CDC_ACM_DeviceDescriptor,
  .config = CDC_ACM_ConfigDescriptor,
  .strings = CDC_ACM_StringDescriptors,
  .string_cnt = CDC_ACM_STRING_COUNT,
#if defined(HAS_WCID)
#if defined(CDC_ACM_WCID_DESCRIPTOR_SIZE)
  .wcid_desc = CDC_ACM_WCIDDescriptor,
#else
  .wcid_desc = 0,
#endif // CDC_ACM_WCID_DESCRIPTOR_SIZE)

#if defined(CDC_ACM_WCID_PROPERTIES_SIZE)
  .wcid_properties = CDC_ACM_WCIDProperties,
#else
  .wcid_properties = 0,
#endif // CDC_ACM_WCID_PROPERTIES_SIZE

#endif // HAS_WCID

#if defined(HAS_WCID_20)
#if defined(CDC_ACM_WCID_BOS_SIZE)
  .wcid_bos = CDC_ACM_WCIDBOS,
#else
  .wcid_bos = 0,  
#endif // CDC_ACM_WCID_BOS_SIZE)

#if defined(CDC_ACM_WCID_DESC_SET_SIZE)
  .wcid_desc_set = CDC_ACM_WCIDDescriptorSet,
#else
  .wcid_desc_set = 0,  
#endif // CDC_ACM_WCID_DESC_SET_SIZE


#endif // HAS_WCID_20
};
/////////////////////////////////////////
//// Device 2
/////////////////////////////////////////
#include "teeny_usb.h"

#define  CDC_ACM5_DEVICE_DESCRIPTOR_SIZE  (18)
__ALIGN_BEGIN  const uint8_t CDC_ACM5_DeviceDescriptor [18] __ALIGN_END = {
  ///////////////////////////////////////
  /// device descriptor
  ///////////////////////////////////////
  0x12,                                             /* bLength */
  USB_DEVICE_DESCRIPTOR_TYPE,                       /* bDescriptorType */
  0x00, 0x02,                                       /* bcdUSB */
  0xef,                                             /* bDeviceClass */
  0x02,                                             /* bDeviceSubClass */
  0x01,                                             /* bDeviceProtocol */
  0x40,                                             /* bMaxPacketSize */
  0x83, 0x04,                                       /* idVendor */
  0x11, 0x00,                                       /* idProduct */
  0x00, 0x01,                                       /* bcdDevice */
  0x01,                                             /* iManufacturer */
  0x02,                                             /* iProduct */
  0x03,                                             /* iSerial */
  0x01,                                             /* bNumConfigurations */
};
#define  CDC_ACM5_CONFIG_DESCRIPTOR_SIZE  (339)
__ALIGN_BEGIN  const uint8_t CDC_ACM5_ConfigDescriptor [339] __ALIGN_END = {
  ///////////////////////////////////////
  /// config descriptor
  ///////////////////////////////////////
  0x09,                                             /* bLength */
  USB_CONFIGURATION_DESCRIPTOR_TYPE,                /* bDescriptorType */
  0x53, 0x01,                                       /* wTotalLength */
  0x0a,                                             /* bNumInterfaces */
  0x01,                                             /* bConfigurationValue */
  0x00,                                             /* iConfiguration */
  0x80,                                             /* bmAttributes */
  0x64,                                             /* bMaxPower */
  
  ///////////////////////////////////////
  /// interface association descriptor
  ///////////////////////////////////////
  0x08,                                             /* bLength */
  USB_IAD_DESCRIPTOR_TYPE,                          /* bDescriptorType */
  0x00,                                             /* bFirstInterface */
  0x02,                                             /* bInterfaceCount */
  0x02,                                             /* bFunctionClass */
  0x02,                                             /* bFunctionSubClass */
  0x01,                                             /* bFunctionProtocol */
  0x00,                                             /* iFunction */
  
  ///////////////////////////////////////
  /// interface descriptor
  ///////////////////////////////////////
  0x09,                                             /* bLength */
  USB_INTERFACE_DESCRIPTOR_TYPE,                    /* bDescriptorType */
  0x00,                                             /* bInterfaceNumber */
  0x00,                                             /* bAlternateSetting */
  0x01,                                             /* bNumEndpoints */
  0x02,                                             /* bInterfaceClass */
  0x02,                                             /* bInterfaceSubClass */
  0x01,                                             /* bInterfaceProtocol */
  0x00,                                             /* iInterface */
  
  ///////////////////////////////////////
  /// cdc acm header descriptor
  ///////////////////////////////////////
  0x05,                                             /* bLength */
  0x24,                                             /* bDescriptorType */
  0x00,                                             /* bDescriptorSubtype */
  0x10, 0x01,                                       /* bcdCDC */
  
  ///////////////////////////////////////
  /// cdc acm call management descriptor
  ///////////////////////////////////////
  0x05,                                             /* bLength */
  0x24,                                             /* bDescriptorType */
  0x01,                                             /* bDescriptorSubtype */
  0x00,                                             /* bmCapabilities */
  0x01,                                             /* bDataInterface */
  
  ///////////////////////////////////////
  /// cdc acm descriptor
  ///////////////////////////////////////
  0x04,                                             /* bLength */
  0x24,                                             /* bDescriptorType */
  0x02,                                             /* bDescriptorSubtype */
  0x02,                                             /* bmCapabilities */
  
  ///////////////////////////////////////
  /// cdc acm union descriptor
  ///////////////////////////////////////
  0x05,                                             /* bLength */
  0x24,                                             /* bDescriptorType */
  0x06,                                             /* bDescriptorSubtype */
  0x00,                                             /* bMasterInterface */
  0x01,                                             /* bSlaveInterface0 */
  
  ///////////////////////////////////////
  /// endpoint descriptor
  ///////////////////////////////////////
  0x07,                                             /* bLength */
  USB_ENDPOINT_DESCRIPTOR_TYPE,                     /* bDescriptorType */
  0x88,                                             /* bEndpointAddress */
  0x03,                                             /* bmAttributes */
  0x10, 0x00,                                       /* wMaxPacketSize */
  0x01,                                             /* bInterval */
  
  ///////////////////////////////////////
  /// interface descriptor
  ///////////////////////////////////////
  0x09,                                             /* bLength */
  USB_INTERFACE_DESCRIPTOR_TYPE,                    /* bDescriptorType */
  0x01,                                             /* bInterfaceNumber */
  0x00,                                             /* bAlternateSetting */
  0x02,                                             /* bNumEndpoints */
  0x0a,                                             /* bInterfaceClass */
  0x00,                                             /* bInterfaceSubClass */
  0x00,                                             /* bInterfaceProtocol */
  0x00,                                             /* iInterface */
  
  ///////////////////////////////////////
  /// endpoint descriptor
  ///////////////////////////////////////
  0x07,                                             /* bLength */
  USB_ENDPOINT_DESCRIPTOR_TYPE,                     /* bDescriptorType */
  0x81,                                             /* bEndpointAddress */
  0x02,                                             /* bmAttributes */
  0x20, 0x00,                                       /* wMaxPacketSize */
  0x01,                                             /* bInterval */
  
  ///////////////////////////////////////
  /// endpoint descriptor
  ///////////////////////////////////////
  0x07,                                             /* bLength */
  USB_ENDPOINT_DESCRIPTOR_TYPE,                     /* bDescriptorType */
  0x01,                                             /* bEndpointAddress */
  0x02,                                             /* bmAttributes */
  0x20, 0x00,                                       /* wMaxPacketSize */
  0x01,                                             /* bInterval */
  
  ///////////////////////////////////////
  /// interface association descriptor
  ///////////////////////////////////////
  0x08,                                             /* bLength */
  USB_IAD_DESCRIPTOR_TYPE,                          /* bDescriptorType */
  0x02,                                             /* bFirstInterface */
  0x02,                                             /* bInterfaceCount */
  0x02,                                             /* bFunctionClass */
  0x02,                                             /* bFunctionSubClass */
  0x01,                                             /* bFunctionProtocol */
  0x00,                                             /* iFunction */
  
  ///////////////////////////////////////
  /// interface descriptor
  ///////////////////////////////////////
  0x09,                                             /* bLength */
  USB_INTERFACE_DESCRIPTOR_TYPE,                    /* bDescriptorType */
  0x02,                                             /* bInterfaceNumber */
  0x00,                                             /* bAlternateSetting */
  0x01,                                             /* bNumEndpoints */
  0x02,                                             /* bInterfaceClass */
  0x02,                                             /* bInterfaceSubClass */
  0x01,                                             /* bInterfaceProtocol */
  0x00,                                             /* iInterface */
  
  ///////////////////////////////////////
  /// cdc acm header descriptor
  ///////////////////////////////////////
  0x05,                                             /* bLength */
  0x24,                                             /* bDescriptorType */
  0x00,                                             /* bDescriptorSubtype */
  0x10, 0x01,                                       /* bcdCDC */
  
  ///////////////////////////////////////
  /// cdc acm call management descriptor
  ///////////////////////////////////////
  0x05,                                             /* bLength */
  0x24,                                             /* bDescriptorType */
  0x01,                                             /* bDescriptorSubtype */
  0x00,                                             /* bmCapabilities */
  0x01,                                             /* bDataInterface */
  
  ///////////////////////////////////////
  /// cdc acm descriptor
  ///////////////////////////////////////
  0x04,                                             /* bLength */
  0x24,                                             /* bDescriptorType */
  0x02,                                             /* bDescriptorSubtype */
  0x02,                                             /* bmCapabilities */
  
  ///////////////////////////////////////
  /// cdc acm union descriptor
  ///////////////////////////////////////
  0x05,                                             /* bLength */
  0x24,                                             /* bDescriptorType */
  0x06,                                             /* bDescriptorSubtype */
  0x00,                                             /* bMasterInterface */
  0x01,                                             /* bSlaveInterface0 */
  
  ///////////////////////////////////////
  /// endpoint descriptor
  ///////////////////////////////////////
  0x07,                                             /* bLength */
  USB_ENDPOINT_DESCRIPTOR_TYPE,                     /* bDescriptorType */
  0x89,                                             /* bEndpointAddress */
  0x03,                                             /* bmAttributes */
  0x10, 0x00,                                       /* wMaxPacketSize */
  0x01,                                             /* bInterval */
  
  ///////////////////////////////////////
  /// interface descriptor
  ///////////////////////////////////////
  0x09,                                             /* bLength */
  USB_INTERFACE_DESCRIPTOR_TYPE,                    /* bDescriptorType */
  0x03,                                             /* bInterfaceNumber */
  0x00,                                             /* bAlternateSetting */
  0x02,                                             /* bNumEndpoints */
  0x0a,                                             /* bInterfaceClass */
  0x00,                                             /* bInterfaceSubClass */
  0x00,                                             /* bInterfaceProtocol */
  0x00,                                             /* iInterface */
  
  ///////////////////////////////////////
  /// endpoint descriptor
  ///////////////////////////////////////
  0x07,                                             /* bLength */
  USB_ENDPOINT_DESCRIPTOR_TYPE,                     /* bDescriptorType */
  0x82,                                             /* bEndpointAddress */
  0x02,                                             /* bmAttributes */
  0x20, 0x00,                                       /* wMaxPacketSize */
  0x01,                                             /* bInterval */
  
  ///////////////////////////////////////
  /// endpoint descriptor
  ///////////////////////////////////////
  0x07,                                             /* bLength */
  USB_ENDPOINT_DESCRIPTOR_TYPE,                     /* bDescriptorType */
  0x02,                                             /* bEndpointAddress */
  0x02,                                             /* bmAttributes */
  0x20, 0x00,                                       /* wMaxPacketSize */
  0x01,                                             /* bInterval */
  
  ///////////////////////////////////////
  /// interface association descriptor
  ///////////////////////////////////////
  0x08,                                             /* bLength */
  USB_IAD_DESCRIPTOR_TYPE,                          /* bDescriptorType */
  0x04,                                             /* bFirstInterface */
  0x02,                                             /* bInterfaceCount */
  0x02,                                             /* bFunctionClass */
  0x02,                                             /* bFunctionSubClass */
  0x01,                                             /* bFunctionProtocol */
  0x00,                                             /* iFunction */
  
  ///////////////////////////////////////
  /// interface descriptor
  ///////////////////////////////////////
  0x09,                                             /* bLength */
  USB_INTERFACE_DESCRIPTOR_TYPE,                    /* bDescriptorType */
  0x04,                                             /* bInterfaceNumber */
  0x00,                                             /* bAlternateSetting */
  0x01,                                             /* bNumEndpoints */
  0x02,                                             /* bInterfaceClass */
  0x02,                                             /* bInterfaceSubClass */
  0x01,                                             /* bInterfaceProtocol */
  0x00,                                             /* iInterface */
  
  ///////////////////////////////////////
  /// cdc acm header descriptor
  ///////////////////////////////////////
  0x05,                                             /* bLength */
  0x24,                                             /* bDescriptorType */
  0x00,                                             /* bDescriptorSubtype */
  0x10, 0x01,                                       /* bcdCDC */
  
  ///////////////////////////////////////
  /// cdc acm call management descriptor
  ///////////////////////////////////////
  0x05,                                             /* bLength */
  0x24,                                             /* bDescriptorType */
  0x01,                                             /* bDescriptorSubtype */
  0x00,                                             /* bmCapabilities */
  0x01,                                             /* bDataInterface */
  
  ///////////////////////////////////////
  /// cdc acm descriptor
  ///////////////////////////////////////
  0x04,                                             /* bLength */
  0x24,                                             /* bDescriptorType */
  0x02,                                             /* bDescriptorSubtype */
  0x02,                                             /* bmCapabilities */
  
  ///////////////////////////////////////
  /// cdc acm union descriptor
  ///////////////////////////////////////
  0x05,                                             /* bLength */
  0x24,                                             /* bDescriptorType */
  0x06,                                             /* bDescriptorSubtype */
  0x00,                                             /* bMasterInterface */
  0x01,                                             /* bSlaveInterface0 */
  
  ///////////////////////////////////////
  /// endpoint descriptor
  ///////////////////////////////////////
  0x07,                                             /* bLength */
  USB_ENDPOINT_DESCRIPTOR_TYPE,                     /* bDescriptorType */
  0x8a,                                             /* bEndpointAddress */
  0x03,                                             /* bmAttributes */
  0x10, 0x00,                                       /* wMaxPacketSize */
  0x01,                                             /* bInterval */
  
  ///////////////////////////////////////
  /// interface descriptor
  ///////////////////////////////////////
  0x09,                                             /* bLength */
  USB_INTERFACE_DESCRIPTOR_TYPE,                    /* bDescriptorType */
  0x05,                                             /* bInterfaceNumber */
  0x00,                                             /* bAlternateSetting */
  0x02,                                             /* bNumEndpoints */
  0x0a,                                             /* bInterfaceClass */
  0x00,                                             /* bInterfaceSubClass */
  0x00,                                             /* bInterfaceProtocol */
  0x00,                                             /* iInterface */
  
  ///////////////////////////////////////
  /// endpoint descriptor
  ///////////////////////////////////////
  0x07,                                             /* bLength */
  USB_ENDPOINT_DESCRIPTOR_TYPE,                     /* bDescriptorType */
  0x83,                                             /* bEndpointAddress */
  0x02,                                             /* bmAttributes */
  0x20, 0x00,                                       /* wMaxPacketSize */
  0x01,                                             /* bInterval */
  
  ///////////////////////////////////////
  /// endpoint descriptor
  ///////////////////////////////////////
  0x07,                                             /* bLength */
  USB_ENDPOINT_DESCRIPTOR_TYPE,                     /* bDescriptorType */
  0x03,                                             /* bEndpointAddress */
  0x02,                                             /* bmAttributes */
  0x20, 0x00,                                       /* wMaxPacketSize */
  0x01,                                             /* bInterval */
  
  ///////////////////////////////////////
  /// interface association descriptor
  ///////////////////////////////////////
  0x08,                                             /* bLength */
  USB_IAD_DESCRIPTOR_TYPE,                          /* bDescriptorType */
  0x06,                                             /* bFirstInterface */
  0x02,                                             /* bInterfaceCount */
  0x02,                                             /* bFunctionClass */
  0x02,                                             /* bFunctionSubClass */
  0x01,                                             /* bFunctionProtocol */
  0x00,                                             /* iFunction */
  
  ///////////////////////////////////////
  /// interface descriptor
  ///////////////////////////////////////
  0x09,                                             /* bLength */
  USB_INTERFACE_DESCRIPTOR_TYPE,                    /* bDescriptorType */
  0x06,                                             /* bInterfaceNumber */
  0x00,                                             /* bAlternateSetting */
  0x01,                                             /* bNumEndpoints */
  0x02,                                             /* bInterfaceClass */
  0x02,                                             /* bInterfaceSubClass */
  0x01,                                             /* bInterfaceProtocol */
  0x00,                                             /* iInterface */
  
  ///////////////////////////////////////
  /// cdc acm header descriptor
  ///////////////////////////////////////
  0x05,                                             /* bLength */
  0x24,                                             /* bDescriptorType */
  0x00,                                             /* bDescriptorSubtype */
  0x10, 0x01,                                       /* bcdCDC */
  
  ///////////////////////////////////////
  /// cdc acm call management descriptor
  ///////////////////////////////////////
  0x05,                                             /* bLength */
  0x24,                                             /* bDescriptorType */
  0x01,                                             /* bDescriptorSubtype */
  0x00,                                             /* bmCapabilities */
  0x01,                                             /* bDataInterface */
  
  ///////////////////////////////////////
  /// cdc acm descriptor
  ///////////////////////////////////////
  0x04,                                             /* bLength */
  0x24,                                             /* bDescriptorType */
  0x02,                                             /* bDescriptorSubtype */
  0x02,                                             /* bmCapabilities */
  
  ///////////////////////////////////////
  /// cdc acm union descriptor
  ///////////////////////////////////////
  0x05,                                             /* bLength */
  0x24,                                             /* bDescriptorType */
  0x06,                                             /* bDescriptorSubtype */
  0x00,                                             /* bMasterInterface */
  0x01,                                             /* bSlaveInterface0 */
  
  ///////////////////////////////////////
  /// endpoint descriptor
  ///////////////////////////////////////
  0x07,                                             /* bLength */
  USB_ENDPOINT_DESCRIPTOR_TYPE,                     /* bDescriptorType */
  0x8b,                                             /* bEndpointAddress */
  0x03,                                             /* bmAttributes */
  0x10, 0x00,                                       /* wMaxPacketSize */
  0x01,                                             /* bInterval */
  
  ///////////////////////////////////////
  /// interface descriptor
  ///////////////////////////////////////
  0x09,                                             /* bLength */
  USB_INTERFACE_DESCRIPTOR_TYPE,                    /* bDescriptorType */
  0x07,                                             /* bInterfaceNumber */
  0x00,                                             /* bAlternateSetting */
  0x02,                                             /* bNumEndpoints */
  0x0a,                                             /* bInterfaceClass */
  0x00,                                             /* bInterfaceSubClass */
  0x00,                                             /* bInterfaceProtocol */
  0x00,                                             /* iInterface */
  
  ///////////////////////////////////////
  /// endpoint descriptor
  ///////////////////////////////////////
  0x07,                                             /* bLength */
  USB_ENDPOINT_DESCRIPTOR_TYPE,                     /* bDescriptorType */
  0x84,                                             /* bEndpointAddress */
  0x02,                                             /* bmAttributes */
  0x20, 0x00,                                       /* wMaxPacketSize */
  0x01,                                             /* bInterval */
  
  ///////////////////////////////////////
  /// endpoint descriptor
  ///////////////////////////////////////
  0x07,                                             /* bLength */
  USB_ENDPOINT_DESCRIPTOR_TYPE,                     /* bDescriptorType */
  0x04,                                             /* bEndpointAddress */
  0x02,                                             /* bmAttributes */
  0x20, 0x00,                                       /* wMaxPacketSize */
  0x01,                                             /* bInterval */
  
  ///////////////////////////////////////
  /// interface association descriptor
  ///////////////////////////////////////
  0x08,                                             /* bLength */
  USB_IAD_DESCRIPTOR_TYPE,                          /* bDescriptorType */
  0x08,                                             /* bFirstInterface */
  0x02,                                             /* bInterfaceCount */
  0x02,                                             /* bFunctionClass */
  0x02,                                             /* bFunctionSubClass */
  0x01,                                             /* bFunctionProtocol */
  0x00,                                             /* iFunction */
  
  ///////////////////////////////////////
  /// interface descriptor
  ///////////////////////////////////////
  0x09,                                             /* bLength */
  USB_INTERFACE_DESCRIPTOR_TYPE,                    /* bDescriptorType */
  0x08,                                             /* bInterfaceNumber */
  0x00,                                             /* bAlternateSetting */
  0x01,                                             /* bNumEndpoints */
  0x02,                                             /* bInterfaceClass */
  0x02,                                             /* bInterfaceSubClass */
  0x01,                                             /* bInterfaceProtocol */
  0x00,                                             /* iInterface */
  
  ///////////////////////////////////////
  /// cdc acm header descriptor
  ///////////////////////////////////////
  0x05,                                             /* bLength */
  0x24,                                             /* bDescriptorType */
  0x00,                                             /* bDescriptorSubtype */
  0x10, 0x01,                                       /* bcdCDC */
  
  ///////////////////////////////////////
  /// cdc acm call management descriptor
  ///////////////////////////////////////
  0x05,                                             /* bLength */
  0x24,                                             /* bDescriptorType */
  0x01,                                             /* bDescriptorSubtype */
  0x00,                                             /* bmCapabilities */
  0x01,                                             /* bDataInterface */
  
  ///////////////////////////////////////
  /// cdc acm descriptor
  ///////////////////////////////////////
  0x04,                                             /* bLength */
  0x24,                                             /* bDescriptorType */
  0x02,                                             /* bDescriptorSubtype */
  0x02,                                             /* bmCapabilities */
  
  ///////////////////////////////////////
  /// cdc acm union descriptor
  ///////////////////////////////////////
  0x05,                                             /* bLength */
  0x24,                                             /* bDescriptorType */
  0x06,                                             /* bDescriptorSubtype */
  0x00,                                             /* bMasterInterface */
  0x01,                                             /* bSlaveInterface0 */
  
  ///////////////////////////////////////
  /// endpoint descriptor
  ///////////////////////////////////////
  0x07,                                             /* bLength */
  USB_ENDPOINT_DESCRIPTOR_TYPE,                     /* bDescriptorType */
  0x8c,                                             /* bEndpointAddress */
  0x03,                                             /* bmAttributes */
  0x10, 0x00,                                       /* wMaxPacketSize */
  0x01,                                             /* bInterval */
  
  ///////////////////////////////////////
  /// interface descriptor
  ///////////////////////////////////////
  0x09,                                             /* bLength */
  USB_INTERFACE_DESCRIPTOR_TYPE,                    /* bDescriptorType */
  0x09,                                             /* bInterfaceNumber */
  0x00,                                             /* bAlternateSetting */
  0x02,                                             /* bNumEndpoints */
  0x0a,                                             /* bInterfaceClass */
  0x00,                                             /* bInterfaceSubClass */
  0x00,                                             /* bInterfaceProtocol */
  0x00,                                             /* iInterface */
  
  ///////////////////////////////////////
  /// endpoint descriptor
  ///////////////////////////////////////
  0x07,                                             /* bLength */
  USB_ENDPOINT_DESCRIPTOR_TYPE,                     /* bDescriptorType */
  0x85,                                             /* bEndpointAddress */
  0x02,                                             /* bmAttributes */
  0x20, 0x00,                                       /* wMaxPacketSize */
  0x01,                                             /* bInterval */
  
  ///////////////////////////////////////
  /// endpoint descriptor
  ///////////////////////////////////////
  0x07,                                             /* bLength */
  USB_ENDPOINT_DESCRIPTOR_TYPE,                     /* bDescriptorType */
  0x05,                                             /* bEndpointAddress */
  0x02,                                             /* bmAttributes */
  0x20, 0x00,                                       /* wMaxPacketSize */
  0x01,                                             /* bInterval */
};
#define  CDC_ACM5_STRING_DESCRIPTOR0_STR   "\x09\x04"
#define  CDC_ACM5_STRING_DESCRIPTOR0_SIZE  (4)
WEAK __ALIGN_BEGIN  const uint8_t CDC_ACM5_StringDescriptor0 [4] __ALIGN_END = {
  0x04,                                         /* bLength */
  USB_STRING_DESCRIPTOR_TYPE,                   /* bDescriptorType */
  0x09, 0x04,                                   /* wLangID0 */
};
#define  CDC_ACM5_STRING_DESCRIPTOR1_STR   "TeenyUSB"
#define  CDC_ACM5_STRING_DESCRIPTOR1_SIZE   (18)
WEAK __ALIGN_BEGIN  const uint8_t CDC_ACM5_StringDescriptor1 [18] __ALIGN_END = {
  0x12,                                             /* bLength */
  USB_STRING_DESCRIPTOR_TYPE,                       /* bDescriptorType */
  'T', 0x00,                                        /* wcChar0 */
  'e', 0x00,                                        /* wcChar1 */
  'e', 0x00,                                        /* wcChar2 */
  'n', 0x00,                                        /* wcChar3 */
  'y', 0x00,                                        /* wcChar4 */
  'U', 0x00,                                        /* wcChar5 */
  'S', 0x00,                                        /* wcChar6 */
  'B', 0x00,                                        /* wcChar7 */
};
#define  CDC_ACM5_STRING_DESCRIPTOR2_STR   "TeenyUSB CDC5 DEMO"
#define  CDC_ACM5_STRING_DESCRIPTOR2_SIZE   (38)
WEAK __ALIGN_BEGIN  const uint8_t CDC_ACM5_StringDescriptor2 [38] __ALIGN_END = {
  0x26,                                             /* bLength */
  USB_STRING_DESCRIPTOR_TYPE,                       /* bDescriptorType */
  'T', 0x00,                                        /* wcChar0 */
  'e', 0x00,                                        /* wcChar1 */
  'e', 0x00,                                        /* wcChar2 */
  'n', 0x00,                                        /* wcChar3 */
  'y', 0x00,                                        /* wcChar4 */
  'U', 0x00,                                        /* wcChar5 */
  'S', 0x00,                                        /* wcChar6 */
  'B', 0x00,                                        /* wcChar7 */
  ' ', 0x00,                                        /* wcChar8 */
  'C', 0x00,                                        /* wcChar9 */
  'D', 0x00,                                        /* wcChar10 */
  'C', 0x00,                                        /* wcChar11 */
  '5', 0x00,                                        /* wcChar12 */
  ' ', 0x00,                                        /* wcChar13 */
  'D', 0x00,                                        /* wcChar14 */
  'E', 0x00,                                        /* wcChar15 */
  'M', 0x00,                                        /* wcChar16 */
  'O', 0x00,                                        /* wcChar17 */
};
#define  CDC_ACM5_STRING_DESCRIPTOR3_STR   "TUSB123456"
#define  CDC_ACM5_STRING_DESCRIPTOR3_SIZE   (22)
WEAK __ALIGN_BEGIN  const uint8_t CDC_ACM5_StringDescriptor3 [22] __ALIGN_END = {
  0x16,                                             /* bLength */
  USB_STRING_DESCRIPTOR_TYPE,                       /* bDescriptorType */
  'T', 0x00,                                        /* wcChar0 */
  'U', 0x00,                                        /* wcChar1 */
  'S', 0x00,                                        /* wcChar2 */
  'B', 0x00,                                        /* wcChar3 */
  '1', 0x00,                                        /* wcChar4 */
  '2', 0x00,                                        /* wcChar5 */
  '3', 0x00,                                        /* wcChar6 */
  '4', 0x00,                                        /* wcChar7 */
  '5', 0x00,                                        /* wcChar8 */
  '6', 0x00,                                        /* wcChar9 */
};
#define CDC_ACM5_STRING_COUNT    (4)
const uint8_t* const CDC_ACM5_StringDescriptors[4] = {
  CDC_ACM5_StringDescriptor0,
  CDC_ACM5_StringDescriptor1,
  CDC_ACM5_StringDescriptor2,
  CDC_ACM5_StringDescriptor3,
};


CDC_ACM5_TXEP_MAX_SIZE
CDC_ACM5_RXEP_MAX_SIZE
//  Device descriptors
const tusb_descriptors CDC_ACM5_descriptors = {
  .device = CDC_ACM5_DeviceDescriptor,
  .config = CDC_ACM5_ConfigDescriptor,
  .strings = CDC_ACM5_StringDescriptors,
  .string_cnt = CDC_ACM5_STRING_COUNT,
#if defined(HAS_WCID)
#if defined(CDC_ACM5_WCID_DESCRIPTOR_SIZE)
  .wcid_desc = CDC_ACM5_WCIDDescriptor,
#else
  .wcid_desc = 0,
#endif // CDC_ACM5_WCID_DESCRIPTOR_SIZE)

#if defined(CDC_ACM5_WCID_PROPERTIES_SIZE)
  .wcid_properties = CDC_ACM5_WCIDProperties,
#else
  .wcid_properties = 0,
#endif // CDC_ACM5_WCID_PROPERTIES_SIZE

#endif // HAS_WCID

#if defined(HAS_WCID_20)
#if defined(CDC_ACM5_WCID_BOS_SIZE)
  .wcid_bos = CDC_ACM5_WCIDBOS,
#else
  .wcid_bos = 0,  
#endif // CDC_ACM5_WCID_BOS_SIZE)

#if defined(CDC_ACM5_WCID_DESC_SET_SIZE)
  .wcid_desc_set = CDC_ACM5_WCIDDescriptorSet,
#else
  .wcid_desc_set = 0,  
#endif // CDC_ACM5_WCID_DESC_SET_SIZE


#endif // HAS_WCID_20
};
/////////////////////////////////////////
//// Device 3
/////////////////////////////////////////
#include "teeny_usb.h"

#define  CDC_RNDIS_DEVICE_DESCRIPTOR_SIZE  (18)
__ALIGN_BEGIN  const uint8_t CDC_RNDIS_DeviceDescriptor [18] __ALIGN_END = {
  ///////////////////////////////////////
  /// device descriptor
  ///////////////////////////////////////
  0x12,                                             /* bLength */
  USB_DEVICE_DESCRIPTOR_TYPE,                       /* bDescriptorType */
  0x00, 0x02,                                       /* bcdUSB */
  0xef,                                             /* bDeviceClass */
  0x02,                                             /* bDeviceSubClass */
  0x01,                                             /* bDeviceProtocol */
  0x40,                                             /* bMaxPacketSize */
  0x83, 0x04,                                       /* idVendor */
  0x11, 0x00,                                       /* idProduct */
  0x00, 0x01,                                       /* bcdDevice */
  0x01,                                             /* iManufacturer */
  0x02,                                             /* iProduct */
  0x03,                                             /* iSerial */
  0x01,                                             /* bNumConfigurations */
};
#define  CDC_RNDIS_CONFIG_DESCRIPTOR_SIZE  (75)
__ALIGN_BEGIN  const uint8_t CDC_RNDIS_ConfigDescriptor [75] __ALIGN_END = {
  ///////////////////////////////////////
  /// config descriptor
  ///////////////////////////////////////
  0x09,                                             /* bLength */
  USB_CONFIGURATION_DESCRIPTOR_TYPE,                /* bDescriptorType */
  0x4b, 0x00,                                       /* wTotalLength */
  0x02,                                             /* bNumInterfaces */
  0x01,                                             /* bConfigurationValue */
  0x00,                                             /* iConfiguration */
  0x80,                                             /* bmAttributes */
  0x64,                                             /* bMaxPower */
  
  ///////////////////////////////////////
  /// interface association descriptor
  ///////////////////////////////////////
  0x08,                                             /* bLength */
  USB_IAD_DESCRIPTOR_TYPE,                          /* bDescriptorType */
  0x00,                                             /* bFirstInterface */
  0x02,                                             /* bInterfaceCount */
  0x02,                                             /* bFunctionClass */
  0x02,                                             /* bFunctionSubClass */
  0xff,                                             /* bFunctionProtocol */
  0x00,                                             /* iFunction */
  
  ///////////////////////////////////////
  /// interface descriptor
  ///////////////////////////////////////
  0x09,                                             /* bLength */
  USB_INTERFACE_DESCRIPTOR_TYPE,                    /* bDescriptorType */
  0x00,                                             /* bInterfaceNumber */
  0x00,                                             /* bAlternateSetting */
  0x01,                                             /* bNumEndpoints */
  0x02,                                             /* bInterfaceClass */
  0x02,                                             /* bInterfaceSubClass */
  0xff,                                             /* bInterfaceProtocol */
  0x00,                                             /* iInterface */
  
  ///////////////////////////////////////
  /// cdc acm header descriptor
  ///////////////////////////////////////
  0x05,                                             /* bLength */
  0x24,                                             /* bDescriptorType */
  0x00,                                             /* bDescriptorSubtype */
  0x10, 0x01,                                       /* bcdCDC */
  
  ///////////////////////////////////////
  /// cdc acm call management descriptor
  ///////////////////////////////////////
  0x05,                                             /* bLength */
  0x24,                                             /* bDescriptorType */
  0x01,                                             /* bDescriptorSubtype */
  0x00,                                             /* bmCapabilities */
  0x01,                                             /* bDataInterface */
  
  ///////////////////////////////////////
  /// cdc acm descriptor
  ///////////////////////////////////////
  0x04,                                             /* bLength */
  0x24,                                             /* bDescriptorType */
  0x02,                                             /* bDescriptorSubtype */
  0x02,                                             /* bmCapabilities */
  
  ///////////////////////////////////////
  /// cdc acm union descriptor
  ///////////////////////////////////////
  0x05,                                             /* bLength */
  0x24,                                             /* bDescriptorType */
  0x06,                                             /* bDescriptorSubtype */
  0x00,                                             /* bMasterInterface */
  0x01,                                             /* bSlaveInterface0 */
  
  ///////////////////////////////////////
  /// endpoint descriptor
  ///////////////////////////////////////
  0x07,                                             /* bLength */
  USB_ENDPOINT_DESCRIPTOR_TYPE,                     /* bDescriptorType */
  0x83,                                             /* bEndpointAddress */
  0x03,                                             /* bmAttributes */
  0x10, 0x00,                                       /* wMaxPacketSize */
  0x01,                                             /* bInterval */
  
  ///////////////////////////////////////
  /// interface descriptor
  ///////////////////////////////////////
  0x09,                                             /* bLength */
  USB_INTERFACE_DESCRIPTOR_TYPE,                    /* bDescriptorType */
  0x01,                                             /* bInterfaceNumber */
  0x00,                                             /* bAlternateSetting */
  0x02,                                             /* bNumEndpoints */
  0x0a,                                             /* bInterfaceClass */
  0x00,                                             /* bInterfaceSubClass */
  0x00,                                             /* bInterfaceProtocol */
  0x00,                                             /* iInterface */
  
  ///////////////////////////////////////
  /// endpoint descriptor
  ///////////////////////////////////////
  0x07,                                             /* bLength */
  USB_ENDPOINT_DESCRIPTOR_TYPE,                     /* bDescriptorType */
  0x81,                                             /* bEndpointAddress */
  0x02,                                             /* bmAttributes */
  0x40, 0x00,                                       /* wMaxPacketSize */
  0x01,                                             /* bInterval */
  
  ///////////////////////////////////////
  /// endpoint descriptor
  ///////////////////////////////////////
  0x07,                                             /* bLength */
  USB_ENDPOINT_DESCRIPTOR_TYPE,                     /* bDescriptorType */
  0x01,                                             /* bEndpointAddress */
  0x02,                                             /* bmAttributes */
  0x40, 0x00,                                       /* wMaxPacketSize */
  0x01,                                             /* bInterval */
};
#define  CDC_RNDIS_STRING_DESCRIPTOR0_STR   "\x09\x04"
#define  CDC_RNDIS_STRING_DESCRIPTOR0_SIZE  (4)
WEAK __ALIGN_BEGIN  const uint8_t CDC_RNDIS_StringDescriptor0 [4] __ALIGN_END = {
  0x04,                                         /* bLength */
  USB_STRING_DESCRIPTOR_TYPE,                   /* bDescriptorType */
  0x09, 0x04,                                   /* wLangID0 */
};
#define  CDC_RNDIS_STRING_DESCRIPTOR1_STR   "TeenyUSB"
#define  CDC_RNDIS_STRING_DESCRIPTOR1_SIZE   (18)
WEAK __ALIGN_BEGIN  const uint8_t CDC_RNDIS_StringDescriptor1 [18] __ALIGN_END = {
  0x12,                                             /* bLength */
  USB_STRING_DESCRIPTOR_TYPE,                       /* bDescriptorType */
  'T', 0x00,                                        /* wcChar0 */
  'e', 0x00,                                        /* wcChar1 */
  'e', 0x00,                                        /* wcChar2 */
  'n', 0x00,                                        /* wcChar3 */
  'y', 0x00,                                        /* wcChar4 */
  'U', 0x00,                                        /* wcChar5 */
  'S', 0x00,                                        /* wcChar6 */
  'B', 0x00,                                        /* wcChar7 */
};
#define  CDC_RNDIS_STRING_DESCRIPTOR2_STR   "TeenyUSB RNDIS DEMO"
#define  CDC_RNDIS_STRING_DESCRIPTOR2_SIZE   (40)
WEAK __ALIGN_BEGIN  const uint8_t CDC_RNDIS_StringDescriptor2 [40] __ALIGN_END = {
  0x28,                                             /* bLength */
  USB_STRING_DESCRIPTOR_TYPE,                       /* bDescriptorType */
  'T', 0x00,                                        /* wcChar0 */
  'e', 0x00,                                        /* wcChar1 */
  'e', 0x00,                                        /* wcChar2 */
  'n', 0x00,                                        /* wcChar3 */
  'y', 0x00,                                        /* wcChar4 */
  'U', 0x00,                                        /* wcChar5 */
  'S', 0x00,                                        /* wcChar6 */
  'B', 0x00,                                        /* wcChar7 */
  ' ', 0x00,                                        /* wcChar8 */
  'R', 0x00,                                        /* wcChar9 */
  'N', 0x00,                                        /* wcChar10 */
  'D', 0x00,                                        /* wcChar11 */
  'I', 0x00,                                        /* wcChar12 */
  'S', 0x00,                                        /* wcChar13 */
  ' ', 0x00,                                        /* wcChar14 */
  'D', 0x00,                                        /* wcChar15 */
  'E', 0x00,                                        /* wcChar16 */
  'M', 0x00,                                        /* wcChar17 */
  'O', 0x00,                                        /* wcChar18 */
};
#define  CDC_RNDIS_STRING_DESCRIPTOR3_STR   "TUSB123456"
#define  CDC_RNDIS_STRING_DESCRIPTOR3_SIZE   (22)
WEAK __ALIGN_BEGIN  const uint8_t CDC_RNDIS_StringDescriptor3 [22] __ALIGN_END = {
  0x16,                                             /* bLength */
  USB_STRING_DESCRIPTOR_TYPE,                       /* bDescriptorType */
  'T', 0x00,                                        /* wcChar0 */
  'U', 0x00,                                        /* wcChar1 */
  'S', 0x00,                                        /* wcChar2 */
  'B', 0x00,                                        /* wcChar3 */
  '1', 0x00,                                        /* wcChar4 */
  '2', 0x00,                                        /* wcChar5 */
  '3', 0x00,                                        /* wcChar6 */
  '4', 0x00,                                        /* wcChar7 */
  '5', 0x00,                                        /* wcChar8 */
  '6', 0x00,                                        /* wcChar9 */
};
#define CDC_RNDIS_STRING_COUNT    (4)
const uint8_t* const CDC_RNDIS_StringDescriptors[4] = {
  CDC_RNDIS_StringDescriptor0,
  CDC_RNDIS_StringDescriptor1,
  CDC_RNDIS_StringDescriptor2,
  CDC_RNDIS_StringDescriptor3,
};

//////////////////////////////////////////////////////
///// WCID descripors
//////////////////////////////////////////////////////
#if defined(HAS_WCID)

// Define WCID os string descriptor 
#ifndef WCID_MSOS_STRING
#define WCID_MSOS_STRING
#define WCID_STRING_DESCRIPTOR_MSOS_STR          "MSFT100"
#define WCID_STRING_DESCRIPTOR_MSOS_SIZE          (18)
WEAK __ALIGN_BEGIN const uint8_t  WCID_StringDescriptor_MSOS [18] __ALIGN_END = {
  ///////////////////////////////////////
  /// MS OS string descriptor
  ///////////////////////////////////////
  0x12,                                             /* bLength */
  USB_STRING_DESCRIPTOR_TYPE,                       /* bDescriptorType */
  /* MSFT100 */
  'M', 0x00, 'S', 0x00, 'F', 0x00, 'T', 0x00,       /* wcChar_7 */
  '1', 0x00, '0', 0x00, '0', 0x00,                  /* wcChar_7 */
  WCID_VENDOR_CODE,                                 /* bVendorCode */
  0x00,                                             /* bReserved */
};

#endif // WCID_MSOS_STRING
#define  CDC_RNDIS_WCID_DESCRIPTOR_SIZE  (40)
WEAK __ALIGN_BEGIN const uint8_t CDC_RNDIS_WCIDDescriptor [40] __ALIGN_END = {
  ///////////////////////////////////////
  /// WCID descriptor
  ///////////////////////////////////////
  0x28, 0x00, 0x00, 0x00,                           /* dwLength */
  0x00, 0x01,                                       /* bcdVersion */
  0x04, 0x00,                                       /* wIndex */
  0x01,                                             /* bCount */
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,         /* bReserved_7 */
  
  ///////////////////////////////////////
  /// WCID function descriptor
  ///////////////////////////////////////
  0x00,                                             /* bFirstInterfaceNumber */
  0x01,                                             /* bReserved */
  /* RNDIS */
  'R', 'N', 'D', 'I', 'S', 0x00, 0x00, 0x00,        /* cCID_8 */
  /* 5162001 */
  '5', '1', '6', '2', '0', '0', '1', 0x00,          /* cSubCID_8 */
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00,               /* bReserved_6 */
};
#define CDC_RNDIS_WCID_PROPERTIES_SIZE (2)
WEAK __ALIGN_BEGIN const desc_t CDC_RNDIS_WCIDProperties[ CDC_RNDIS_WCID_PROPERTIES_SIZE ] __ALIGN_END = {
  0,    // No WCID in Interface 0
  0,    // No WCID in Interface 1
};
#endif    // #if defined(HAS_WCID)


CDC_RNDIS_TXEP_MAX_SIZE
CDC_RNDIS_RXEP_MAX_SIZE
//  Device descriptors
const tusb_descriptors CDC_RNDIS_descriptors = {
  .device = CDC_RNDIS_DeviceDescriptor,
  .config = CDC_RNDIS_ConfigDescriptor,
  .strings = CDC_RNDIS_StringDescriptors,
  .string_cnt = CDC_RNDIS_STRING_COUNT,
#if defined(HAS_WCID)
#if defined(CDC_RNDIS_WCID_DESCRIPTOR_SIZE)
  .wcid_desc = CDC_RNDIS_WCIDDescriptor,
#else
  .wcid_desc = 0,
#endif // CDC_RNDIS_WCID_DESCRIPTOR_SIZE)

#if defined(CDC_RNDIS_WCID_PROPERTIES_SIZE)
  .wcid_properties = CDC_RNDIS_WCIDProperties,
#else
  .wcid_properties = 0,
#endif // CDC_RNDIS_WCID_PROPERTIES_SIZE

#endif // HAS_WCID

#if defined(HAS_WCID_20)
#if defined(CDC_RNDIS_WCID_BOS_SIZE)
  .wcid_bos = CDC_RNDIS_WCIDBOS,
#else
  .wcid_bos = 0,  
#endif // CDC_RNDIS_WCID_BOS_SIZE)

#if defined(CDC_RNDIS_WCID_DESC_SET_SIZE)
  .wcid_desc_set = CDC_RNDIS_WCIDDescriptorSet,
#else
  .wcid_desc_set = 0,  
#endif // CDC_RNDIS_WCID_DESC_SET_SIZE


#endif // HAS_WCID_20
};
/////////////////////////////////////////
//// Device 4
/////////////////////////////////////////
#include "teeny_usb.h"

#define  WINUSB_DEVICE_DESCRIPTOR_SIZE  (18)
__ALIGN_BEGIN  const uint8_t WINUSB_DeviceDescriptor [18] __ALIGN_END = {
  ///////////////////////////////////////
  /// device descriptor
  ///////////////////////////////////////
  0x12,                                             /* bLength */
  USB_DEVICE_DESCRIPTOR_TYPE,                       /* bDescriptorType */
  0x00, 0x02,                                       /* bcdUSB */
  0x00,                                             /* bDeviceClass */
  0x00,                                             /* bDeviceSubClass */
  0x00,                                             /* bDeviceProtocol */
  0x40,                                             /* bMaxPacketSize */
  0x83, 0x04,                                       /* idVendor */
  0x11, 0x00,                                       /* idProduct */
  0x00, 0x01,                                       /* bcdDevice */
  0x01,                                             /* iManufacturer */
  0x02,                                             /* iProduct */
  0x03,                                             /* iSerial */
  0x01,                                             /* bNumConfigurations */
};
#define  WINUSB_CONFIG_DESCRIPTOR_SIZE  (78)
__ALIGN_BEGIN  const uint8_t WINUSB_ConfigDescriptor [78] __ALIGN_END = {
  ///////////////////////////////////////
  /// config descriptor
  ///////////////////////////////////////
  0x09,                                             /* bLength */
  USB_CONFIGURATION_DESCRIPTOR_TYPE,                /* bDescriptorType */
  0x4e, 0x00,                                       /* wTotalLength */
  0x03,                                             /* bNumInterfaces */
  0x01,                                             /* bConfigurationValue */
  0x00,                                             /* iConfiguration */
  0x80,                                             /* bmAttributes */
  0x64,                                             /* bMaxPower */
  
  ///////////////////////////////////////
  /// interface descriptor
  ///////////////////////////////////////
  0x09,                                             /* bLength */
  USB_INTERFACE_DESCRIPTOR_TYPE,                    /* bDescriptorType */
  0x00,                                             /* bInterfaceNumber */
  0x00,                                             /* bAlternateSetting */
  0x02,                                             /* bNumEndpoints */
  0xff,                                             /* bInterfaceClass */
  0xff,                                             /* bInterfaceSubClass */
  0x00,                                             /* bInterfaceProtocol */
  0x04,                                             /* iInterface */
  
  ///////////////////////////////////////
  /// endpoint descriptor
  ///////////////////////////////////////
  0x07,                                             /* bLength */
  USB_ENDPOINT_DESCRIPTOR_TYPE,                     /* bDescriptorType */
  0x81,                                             /* bEndpointAddress */
  0x02,                                             /* bmAttributes */
  0x20, 0x00,                                       /* wMaxPacketSize */
  0x01,                                             /* bInterval */
  
  ///////////////////////////////////////
  /// endpoint descriptor
  ///////////////////////////////////////
  0x07,                                             /* bLength */
  USB_ENDPOINT_DESCRIPTOR_TYPE,                     /* bDescriptorType */
  0x01,                                             /* bEndpointAddress */
  0x02,                                             /* bmAttributes */
  0x20, 0x00,                                       /* wMaxPacketSize */
  0x01,                                             /* bInterval */
  
  ///////////////////////////////////////
  /// interface descriptor
  ///////////////////////////////////////
  0x09,                                             /* bLength */
  USB_INTERFACE_DESCRIPTOR_TYPE,                    /* bDescriptorType */
  0x01,                                             /* bInterfaceNumber */
  0x00,                                             /* bAlternateSetting */
  0x02,                                             /* bNumEndpoints */
  0xff,                                             /* bInterfaceClass */
  0xff,                                             /* bInterfaceSubClass */
  0x00,                                             /* bInterfaceProtocol */
  0x05,                                             /* iInterface */
  
  ///////////////////////////////////////
  /// endpoint descriptor
  ///////////////////////////////////////
  0x07,                                             /* bLength */
  USB_ENDPOINT_DESCRIPTOR_TYPE,                     /* bDescriptorType */
  0x82,                                             /* bEndpointAddress */
  0x02,                                             /* bmAttributes */
  0x20, 0x00,                                       /* wMaxPacketSize */
  0x01,                                             /* bInterval */
  
  ///////////////////////////////////////
  /// endpoint descriptor
  ///////////////////////////////////////
  0x07,                                             /* bLength */
  USB_ENDPOINT_DESCRIPTOR_TYPE,                     /* bDescriptorType */
  0x02,                                             /* bEndpointAddress */
  0x02,                                             /* bmAttributes */
  0x20, 0x00,                                       /* wMaxPacketSize */
  0x01,                                             /* bInterval */
  
  ///////////////////////////////////////
  /// interface descriptor
  ///////////////////////////////////////
  0x09,                                             /* bLength */
  USB_INTERFACE_DESCRIPTOR_TYPE,                    /* bDescriptorType */
  0x02,                                             /* bInterfaceNumber */
  0x00,                                             /* bAlternateSetting */
  0x02,                                             /* bNumEndpoints */
  0xff,                                             /* bInterfaceClass */
  0xff,                                             /* bInterfaceSubClass */
  0x00,                                             /* bInterfaceProtocol */
  0x05,                                             /* iInterface */
  
  ///////////////////////////////////////
  /// endpoint descriptor
  ///////////////////////////////////////
  0x07,                                             /* bLength */
  USB_ENDPOINT_DESCRIPTOR_TYPE,                     /* bDescriptorType */
  0x83,                                             /* bEndpointAddress */
  0x02,                                             /* bmAttributes */
  0x20, 0x00,                                       /* wMaxPacketSize */
  0x01,                                             /* bInterval */
  
  ///////////////////////////////////////
  /// endpoint descriptor
  ///////////////////////////////////////
  0x07,                                             /* bLength */
  USB_ENDPOINT_DESCRIPTOR_TYPE,                     /* bDescriptorType */
  0x03,                                             /* bEndpointAddress */
  0x02,                                             /* bmAttributes */
  0x20, 0x00,                                       /* wMaxPacketSize */
  0x01,                                             /* bInterval */
};
#define  WINUSB_STRING_DESCRIPTOR0_STR   "\x09\x04"
#define  WINUSB_STRING_DESCRIPTOR0_SIZE  (4)
WEAK __ALIGN_BEGIN  const uint8_t WINUSB_StringDescriptor0 [4] __ALIGN_END = {
  0x04,                                         /* bLength */
  USB_STRING_DESCRIPTOR_TYPE,                   /* bDescriptorType */
  0x09, 0x04,                                   /* wLangID0 */
};
#define  WINUSB_STRING_DESCRIPTOR1_STR   "TeenyUSB"
#define  WINUSB_STRING_DESCRIPTOR1_SIZE   (18)
WEAK __ALIGN_BEGIN  const uint8_t WINUSB_StringDescriptor1 [18] __ALIGN_END = {
  0x12,                                             /* bLength */
  USB_STRING_DESCRIPTOR_TYPE,                       /* bDescriptorType */
  'T', 0x00,                                        /* wcChar0 */
  'e', 0x00,                                        /* wcChar1 */
  'e', 0x00,                                        /* wcChar2 */
  'n', 0x00,                                        /* wcChar3 */
  'y', 0x00,                                        /* wcChar4 */
  'U', 0x00,                                        /* wcChar5 */
  'S', 0x00,                                        /* wcChar6 */
  'B', 0x00,                                        /* wcChar7 */
};
#define  WINUSB_STRING_DESCRIPTOR2_STR   "TeenyUSB WinUSB DEMO"
#define  WINUSB_STRING_DESCRIPTOR2_SIZE   (42)
WEAK __ALIGN_BEGIN  const uint8_t WINUSB_StringDescriptor2 [42] __ALIGN_END = {
  0x2a,                                             /* bLength */
  USB_STRING_DESCRIPTOR_TYPE,                       /* bDescriptorType */
  'T', 0x00,                                        /* wcChar0 */
  'e', 0x00,                                        /* wcChar1 */
  'e', 0x00,                                        /* wcChar2 */
  'n', 0x00,                                        /* wcChar3 */
  'y', 0x00,                                        /* wcChar4 */
  'U', 0x00,                                        /* wcChar5 */
  'S', 0x00,                                        /* wcChar6 */
  'B', 0x00,                                        /* wcChar7 */
  ' ', 0x00,                                        /* wcChar8 */
  'W', 0x00,                                        /* wcChar9 */
  'i', 0x00,                                        /* wcChar10 */
  'n', 0x00,                                        /* wcChar11 */
  'U', 0x00,                                        /* wcChar12 */
  'S', 0x00,                                        /* wcChar13 */
  'B', 0x00,                                        /* wcChar14 */
  ' ', 0x00,                                        /* wcChar15 */
  'D', 0x00,                                        /* wcChar16 */
  'E', 0x00,                                        /* wcChar17 */
  'M', 0x00,                                        /* wcChar18 */
  'O', 0x00,                                        /* wcChar19 */
};
#define  WINUSB_STRING_DESCRIPTOR3_STR   "TUSB123456"
#define  WINUSB_STRING_DESCRIPTOR3_SIZE   (22)
WEAK __ALIGN_BEGIN  const uint8_t WINUSB_StringDescriptor3 [22] __ALIGN_END = {
  0x16,                                             /* bLength */
  USB_STRING_DESCRIPTOR_TYPE,                       /* bDescriptorType */
  'T', 0x00,                                        /* wcChar0 */
  'U', 0x00,                                        /* wcChar1 */
  'S', 0x00,                                        /* wcChar2 */
  'B', 0x00,                                        /* wcChar3 */
  '1', 0x00,                                        /* wcChar4 */
  '2', 0x00,                                        /* wcChar5 */
  '3', 0x00,                                        /* wcChar6 */
  '4', 0x00,                                        /* wcChar7 */
  '5', 0x00,                                        /* wcChar8 */
  '6', 0x00,                                        /* wcChar9 */
};
#define  WINUSB_STRING_DESCRIPTOR4_STR   "TeenyUSB WinUSB 0"
#define  WINUSB_STRING_DESCRIPTOR4_SIZE   (36)
WEAK __ALIGN_BEGIN  const uint8_t WINUSB_StringDescriptor4 [36] __ALIGN_END = {
  0x24,                                             /* bLength */
  USB_STRING_DESCRIPTOR_TYPE,                       /* bDescriptorType */
  'T', 0x00,                                        /* wcChar0 */
  'e', 0x00,                                        /* wcChar1 */
  'e', 0x00,                                        /* wcChar2 */
  'n', 0x00,                                        /* wcChar3 */
  'y', 0x00,                                        /* wcChar4 */
  'U', 0x00,                                        /* wcChar5 */
  'S', 0x00,                                        /* wcChar6 */
  'B', 0x00,                                        /* wcChar7 */
  ' ', 0x00,                                        /* wcChar8 */
  'W', 0x00,                                        /* wcChar9 */
  'i', 0x00,                                        /* wcChar10 */
  'n', 0x00,                                        /* wcChar11 */
  'U', 0x00,                                        /* wcChar12 */
  'S', 0x00,                                        /* wcChar13 */
  'B', 0x00,                                        /* wcChar14 */
  ' ', 0x00,                                        /* wcChar15 */
  '0', 0x00,                                        /* wcChar16 */
};
#define  WINUSB_STRING_DESCRIPTOR5_STR   "TeenyUSB WinUSB 1"
#define  WINUSB_STRING_DESCRIPTOR5_SIZE   (36)
WEAK __ALIGN_BEGIN  const uint8_t WINUSB_StringDescriptor5 [36] __ALIGN_END = {
  0x24,                                             /* bLength */
  USB_STRING_DESCRIPTOR_TYPE,                       /* bDescriptorType */
  'T', 0x00,                                        /* wcChar0 */
  'e', 0x00,                                        /* wcChar1 */
  'e', 0x00,                                        /* wcChar2 */
  'n', 0x00,                                        /* wcChar3 */
  'y', 0x00,                                        /* wcChar4 */
  'U', 0x00,                                        /* wcChar5 */
  'S', 0x00,                                        /* wcChar6 */
  'B', 0x00,                                        /* wcChar7 */
  ' ', 0x00,                                        /* wcChar8 */
  'W', 0x00,                                        /* wcChar9 */
  'i', 0x00,                                        /* wcChar10 */
  'n', 0x00,                                        /* wcChar11 */
  'U', 0x00,                                        /* wcChar12 */
  'S', 0x00,                                        /* wcChar13 */
  'B', 0x00,                                        /* wcChar14 */
  ' ', 0x00,                                        /* wcChar15 */
  '1', 0x00,                                        /* wcChar16 */
};
#define WINUSB_STRING_COUNT    (6)
const uint8_t* const WINUSB_StringDescriptors[6] = {
  WINUSB_StringDescriptor0,
  WINUSB_StringDescriptor1,
  WINUSB_StringDescriptor2,
  WINUSB_StringDescriptor3,
  WINUSB_StringDescriptor4,
  WINUSB_StringDescriptor5,
};

//////////////////////////////////////////////////////
///// WCID descripors
//////////////////////////////////////////////////////
#if defined(HAS_WCID)

// Define WCID os string descriptor 
#ifndef WCID_MSOS_STRING
#define WCID_MSOS_STRING
#define WCID_STRING_DESCRIPTOR_MSOS_STR          "MSFT100"
#define WCID_STRING_DESCRIPTOR_MSOS_SIZE          (18)
WEAK __ALIGN_BEGIN const uint8_t  WCID_StringDescriptor_MSOS [18] __ALIGN_END = {
  ///////////////////////////////////////
  /// MS OS string descriptor
  ///////////////////////////////////////
  0x12,                                             /* bLength */
  USB_STRING_DESCRIPTOR_TYPE,                       /* bDescriptorType */
  /* MSFT100 */
  'M', 0x00, 'S', 0x00, 'F', 0x00, 'T', 0x00,       /* wcChar_7 */
  '1', 0x00, '0', 0x00, '0', 0x00,                  /* wcChar_7 */
  WCID_VENDOR_CODE,                                 /* bVendorCode */
  0x00,                                             /* bReserved */
};

#endif // WCID_MSOS_STRING
#define  WINUSB_IF0_WCID_PROPERTIES_SIZE  (142)
WEAK __ALIGN_BEGIN const uint8_t WINUSB_IF0_WCIDProperties [142] __ALIGN_END = {
  ///////////////////////////////////////
  /// WCID property descriptor
  ///////////////////////////////////////
  0x8e, 0x00, 0x00, 0x00,                           /* dwLength */
  0x00, 0x01,                                       /* bcdVersion */
  0x05, 0x00,                                       /* wIndex */
  0x01, 0x00,                                       /* wCount */
  
  ///////////////////////////////////////
  /// registry propter descriptor
  ///////////////////////////////////////
  0x84, 0x00, 0x00, 0x00,                           /* dwSize */
  0x01, 0x00, 0x00, 0x00,                           /* dwPropertyDataType */
  0x28, 0x00,                                       /* wPropertyNameLength */
  /* DeviceInterfaceGUID */
  'D', 0x00, 'e', 0x00, 'v', 0x00, 'i', 0x00,       /* wcName_20 */
  'c', 0x00, 'e', 0x00, 'I', 0x00, 'n', 0x00,       /* wcName_20 */
  't', 0x00, 'e', 0x00, 'r', 0x00, 'f', 0x00,       /* wcName_20 */
  'a', 0x00, 'c', 0x00, 'e', 0x00, 'G', 0x00,       /* wcName_20 */
  'U', 0x00, 'I', 0x00, 'D', 0x00, 0x00, 0x00,      /* wcName_20 */
  0x4e, 0x00, 0x00, 0x00,                           /* dwPropertyDataLength */
  /* {1D4B2365-4749-48EA-B38A-7C6FDDDD7E26} */
  '{', 0x00, '1', 0x00, 'D', 0x00, '4', 0x00,       /* wcData_39 */
  'B', 0x00, '2', 0x00, '3', 0x00, '6', 0x00,       /* wcData_39 */
  '5', 0x00, '-', 0x00, '4', 0x00, '7', 0x00,       /* wcData_39 */
  '4', 0x00, '9', 0x00, '-', 0x00, '4', 0x00,       /* wcData_39 */
  '8', 0x00, 'E', 0x00, 'A', 0x00, '-', 0x00,       /* wcData_39 */
  'B', 0x00, '3', 0x00, '8', 0x00, 'A', 0x00,       /* wcData_39 */
  '-', 0x00, '7', 0x00, 'C', 0x00, '6', 0x00,       /* wcData_39 */
  'F', 0x00, 'D', 0x00, 'D', 0x00, 'D', 0x00,       /* wcData_39 */
  'D', 0x00, '7', 0x00, 'E', 0x00, '2', 0x00,       /* wcData_39 */
  '6', 0x00, '}', 0x00, 0x00, 0x00,                 /* wcData_39 */
};
#define  WINUSB_IF1_WCID_PROPERTIES_SIZE  (142)
WEAK __ALIGN_BEGIN const uint8_t WINUSB_IF1_WCIDProperties [142] __ALIGN_END = {
  ///////////////////////////////////////
  /// WCID property descriptor
  ///////////////////////////////////////
  0x8e, 0x00, 0x00, 0x00,                           /* dwLength */
  0x00, 0x01,                                       /* bcdVersion */
  0x05, 0x00,                                       /* wIndex */
  0x01, 0x00,                                       /* wCount */
  
  ///////////////////////////////////////
  /// registry propter descriptor
  ///////////////////////////////////////
  0x84, 0x00, 0x00, 0x00,                           /* dwSize */
  0x01, 0x00, 0x00, 0x00,                           /* dwPropertyDataType */
  0x28, 0x00,                                       /* wPropertyNameLength */
  /* DeviceInterfaceGUID */
  'D', 0x00, 'e', 0x00, 'v', 0x00, 'i', 0x00,       /* wcName_20 */
  'c', 0x00, 'e', 0x00, 'I', 0x00, 'n', 0x00,       /* wcName_20 */
  't', 0x00, 'e', 0x00, 'r', 0x00, 'f', 0x00,       /* wcName_20 */
  'a', 0x00, 'c', 0x00, 'e', 0x00, 'G', 0x00,       /* wcName_20 */
  'U', 0x00, 'I', 0x00, 'D', 0x00, 0x00, 0x00,      /* wcName_20 */
  0x4e, 0x00, 0x00, 0x00,                           /* dwPropertyDataLength */
  /* {1D4B2365-4749-48EA-B38A-7C6FDDDD7E26} */
  '{', 0x00, '1', 0x00, 'D', 0x00, '4', 0x00,       /* wcData_39 */
  'B', 0x00, '2', 0x00, '3', 0x00, '6', 0x00,       /* wcData_39 */
  '5', 0x00, '-', 0x00, '4', 0x00, '7', 0x00,       /* wcData_39 */
  '4', 0x00, '9', 0x00, '-', 0x00, '4', 0x00,       /* wcData_39 */
  '8', 0x00, 'E', 0x00, 'A', 0x00, '-', 0x00,       /* wcData_39 */
  'B', 0x00, '3', 0x00, '8', 0x00, 'A', 0x00,       /* wcData_39 */
  '-', 0x00, '7', 0x00, 'C', 0x00, '6', 0x00,       /* wcData_39 */
  'F', 0x00, 'D', 0x00, 'D', 0x00, 'D', 0x00,       /* wcData_39 */
  'D', 0x00, '7', 0x00, 'E', 0x00, '2', 0x00,       /* wcData_39 */
  '6', 0x00, '}', 0x00, 0x00, 0x00,                 /* wcData_39 */
};
#define  WINUSB_IF2_WCID_PROPERTIES_SIZE  (142)
WEAK __ALIGN_BEGIN const uint8_t WINUSB_IF2_WCIDProperties [142] __ALIGN_END = {
  ///////////////////////////////////////
  /// WCID property descriptor
  ///////////////////////////////////////
  0x8e, 0x00, 0x00, 0x00,                           /* dwLength */
  0x00, 0x01,                                       /* bcdVersion */
  0x05, 0x00,                                       /* wIndex */
  0x01, 0x00,                                       /* wCount */
  
  ///////////////////////////////////////
  /// registry propter descriptor
  ///////////////////////////////////////
  0x84, 0x00, 0x00, 0x00,                           /* dwSize */
  0x01, 0x00, 0x00, 0x00,                           /* dwPropertyDataType */
  0x28, 0x00,                                       /* wPropertyNameLength */
  /* DeviceInterfaceGUID */
  'D', 0x00, 'e', 0x00, 'v', 0x00, 'i', 0x00,       /* wcName_20 */
  'c', 0x00, 'e', 0x00, 'I', 0x00, 'n', 0x00,       /* wcName_20 */
  't', 0x00, 'e', 0x00, 'r', 0x00, 'f', 0x00,       /* wcName_20 */
  'a', 0x00, 'c', 0x00, 'e', 0x00, 'G', 0x00,       /* wcName_20 */
  'U', 0x00, 'I', 0x00, 'D', 0x00, 0x00, 0x00,      /* wcName_20 */
  0x4e, 0x00, 0x00, 0x00,                           /* dwPropertyDataLength */
  /* {1D4B2365-4749-48EA-B38A-7C6FDDDD7E26} */
  '{', 0x00, '1', 0x00, 'D', 0x00, '4', 0x00,       /* wcData_39 */
  'B', 0x00, '2', 0x00, '3', 0x00, '6', 0x00,       /* wcData_39 */
  '5', 0x00, '-', 0x00, '4', 0x00, '7', 0x00,       /* wcData_39 */
  '4', 0x00, '9', 0x00, '-', 0x00, '4', 0x00,       /* wcData_39 */
  '8', 0x00, 'E', 0x00, 'A', 0x00, '-', 0x00,       /* wcData_39 */
  'B', 0x00, '3', 0x00, '8', 0x00, 'A', 0x00,       /* wcData_39 */
  '-', 0x00, '7', 0x00, 'C', 0x00, '6', 0x00,       /* wcData_39 */
  'F', 0x00, 'D', 0x00, 'D', 0x00, 'D', 0x00,       /* wcData_39 */
  'D', 0x00, '7', 0x00, 'E', 0x00, '2', 0x00,       /* wcData_39 */
  '6', 0x00, '}', 0x00, 0x00, 0x00,                 /* wcData_39 */
};
#define  WINUSB_WCID_DESCRIPTOR_SIZE  (88)
WEAK __ALIGN_BEGIN const uint8_t WINUSB_WCIDDescriptor [88] __ALIGN_END = {
  ///////////////////////////////////////
  /// WCID descriptor
  ///////////////////////////////////////
  0x58, 0x00, 0x00, 0x00,                           /* dwLength */
  0x00, 0x01,                                       /* bcdVersion */
  0x04, 0x00,                                       /* wIndex */
  0x03,                                             /* bCount */
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,         /* bReserved_7 */
  
  ///////////////////////////////////////
  /// WCID function descriptor
  ///////////////////////////////////////
  0x00,                                             /* bFirstInterfaceNumber */
  0x01,                                             /* bReserved */
  /* WINUSB */
  'W', 'I', 'N', 'U', 'S', 'B', 0x00, 0x00,         /* cCID_8 */
  /*  */
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,   /* cSubCID_8 */
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00,               /* bReserved_6 */
  
  ///////////////////////////////////////
  /// WCID function descriptor
  ///////////////////////////////////////
  0x01,                                             /* bFirstInterfaceNumber */
  0x01,                                             /* bReserved */
  /* WINUSB */
  'W', 'I', 'N', 'U', 'S', 'B', 0x00, 0x00,         /* cCID_8 */
  /*  */
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,   /* cSubCID_8 */
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00,               /* bReserved_6 */
  
  ///////////////////////////////////////
  /// WCID function descriptor
  ///////////////////////////////////////
  0x02,                                             /* bFirstInterfaceNumber */
  0x01,                                             /* bReserved */
  /* WINUSB */
  'W', 'I', 'N', 'U', 'S', 'B', 0x00, 0x00,         /* cCID_8 */
  /*  */
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,   /* cSubCID_8 */
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00,               /* bReserved_6 */
};
#define WINUSB_WCID_PROPERTIES_SIZE (3)
WEAK __ALIGN_BEGIN const desc_t WINUSB_WCIDProperties[ WINUSB_WCID_PROPERTIES_SIZE ] __ALIGN_END = {
  WINUSB_IF0_WCIDProperties,
  WINUSB_IF1_WCIDProperties,
  WINUSB_IF2_WCIDProperties,
};
#endif    // #if defined(HAS_WCID)


WINUSB_TXEP_MAX_SIZE
WINUSB_RXEP_MAX_SIZE
//  Device descriptors
const tusb_descriptors WINUSB_descriptors = {
  .device = WINUSB_DeviceDescriptor,
  .config = WINUSB_ConfigDescriptor,
  .strings = WINUSB_StringDescriptors,
  .string_cnt = WINUSB_STRING_COUNT,
#if defined(HAS_WCID)
#if defined(WINUSB_WCID_DESCRIPTOR_SIZE)
  .wcid_desc = WINUSB_WCIDDescriptor,
#else
  .wcid_desc = 0,
#endif // WINUSB_WCID_DESCRIPTOR_SIZE)

#if defined(WINUSB_WCID_PROPERTIES_SIZE)
  .wcid_properties = WINUSB_WCIDProperties,
#else
  .wcid_properties = 0,
#endif // WINUSB_WCID_PROPERTIES_SIZE

#endif // HAS_WCID

#if defined(HAS_WCID_20)
#if defined(WINUSB_WCID_BOS_SIZE)
  .wcid_bos = WINUSB_WCIDBOS,
#else
  .wcid_bos = 0,  
#endif // WINUSB_WCID_BOS_SIZE)

#if defined(WINUSB_WCID_DESC_SET_SIZE)
  .wcid_desc_set = WINUSB_WCIDDescriptorSet,
#else
  .wcid_desc_set = 0,  
#endif // WINUSB_WCID_DESC_SET_SIZE


#endif // HAS_WCID_20
};
/////////////////////////////////////////
//// Device 5
/////////////////////////////////////////
#include "teeny_usb.h"

#define  WINUSB20_DEVICE_DESCRIPTOR_SIZE  (18)
__ALIGN_BEGIN  const uint8_t WINUSB20_DeviceDescriptor [18] __ALIGN_END = {
  ///////////////////////////////////////
  /// device descriptor
  ///////////////////////////////////////
  0x12,                                             /* bLength */
  USB_DEVICE_DESCRIPTOR_TYPE,                       /* bDescriptorType */
  0x10, 0x02,                                       /* bcdUSB */
  0x00,                                             /* bDeviceClass */
  0x00,                                             /* bDeviceSubClass */
  0x00,                                             /* bDeviceProtocol */
  0x40,                                             /* bMaxPacketSize */
  0x83, 0x04,                                       /* idVendor */
  0x11, 0x00,                                       /* idProduct */
  0x00, 0x01,                                       /* bcdDevice */
  0x01,                                             /* iManufacturer */
  0x02,                                             /* iProduct */
  0x03,                                             /* iSerial */
  0x01,                                             /* bNumConfigurations */
};
#define  WINUSB20_CONFIG_DESCRIPTOR_SIZE  (78)
__ALIGN_BEGIN  const uint8_t WINUSB20_ConfigDescriptor [78] __ALIGN_END = {
  ///////////////////////////////////////
  /// config descriptor
  ///////////////////////////////////////
  0x09,                                             /* bLength */
  USB_CONFIGURATION_DESCRIPTOR_TYPE,                /* bDescriptorType */
  0x4e, 0x00,                                       /* wTotalLength */
  0x03,                                             /* bNumInterfaces */
  0x01,                                             /* bConfigurationValue */
  0x00,                                             /* iConfiguration */
  0x80,                                             /* bmAttributes */
  0x64,                                             /* bMaxPower */
  
  ///////////////////////////////////////
  /// interface descriptor
  ///////////////////////////////////////
  0x09,                                             /* bLength */
  USB_INTERFACE_DESCRIPTOR_TYPE,                    /* bDescriptorType */
  0x00,                                             /* bInterfaceNumber */
  0x00,                                             /* bAlternateSetting */
  0x02,                                             /* bNumEndpoints */
  0xff,                                             /* bInterfaceClass */
  0xff,                                             /* bInterfaceSubClass */
  0x00,                                             /* bInterfaceProtocol */
  0x04,                                             /* iInterface */
  
  ///////////////////////////////////////
  /// endpoint descriptor
  ///////////////////////////////////////
  0x07,                                             /* bLength */
  USB_ENDPOINT_DESCRIPTOR_TYPE,                     /* bDescriptorType */
  0x81,                                             /* bEndpointAddress */
  0x02,                                             /* bmAttributes */
  0x20, 0x00,                                       /* wMaxPacketSize */
  0x01,                                             /* bInterval */
  
  ///////////////////////////////////////
  /// endpoint descriptor
  ///////////////////////////////////////
  0x07,                                             /* bLength */
  USB_ENDPOINT_DESCRIPTOR_TYPE,                     /* bDescriptorType */
  0x01,                                             /* bEndpointAddress */
  0x02,                                             /* bmAttributes */
  0x20, 0x00,                                       /* wMaxPacketSize */
  0x01,                                             /* bInterval */
  
  ///////////////////////////////////////
  /// interface descriptor
  ///////////////////////////////////////
  0x09,                                             /* bLength */
  USB_INTERFACE_DESCRIPTOR_TYPE,                    /* bDescriptorType */
  0x01,                                             /* bInterfaceNumber */
  0x00,                                             /* bAlternateSetting */
  0x02,                                             /* bNumEndpoints */
  0xff,                                             /* bInterfaceClass */
  0xff,                                             /* bInterfaceSubClass */
  0x00,                                             /* bInterfaceProtocol */
  0x05,                                             /* iInterface */
  
  ///////////////////////////////////////
  /// endpoint descriptor
  ///////////////////////////////////////
  0x07,                                             /* bLength */
  USB_ENDPOINT_DESCRIPTOR_TYPE,                     /* bDescriptorType */
  0x82,                                             /* bEndpointAddress */
  0x02,                                             /* bmAttributes */
  0x20, 0x00,                                       /* wMaxPacketSize */
  0x01,                                             /* bInterval */
  
  ///////////////////////////////////////
  /// endpoint descriptor
  ///////////////////////////////////////
  0x07,                                             /* bLength */
  USB_ENDPOINT_DESCRIPTOR_TYPE,                     /* bDescriptorType */
  0x02,                                             /* bEndpointAddress */
  0x02,                                             /* bmAttributes */
  0x20, 0x00,                                       /* wMaxPacketSize */
  0x01,                                             /* bInterval */
  
  ///////////////////////////////////////
  /// interface descriptor
  ///////////////////////////////////////
  0x09,                                             /* bLength */
  USB_INTERFACE_DESCRIPTOR_TYPE,                    /* bDescriptorType */
  0x02,                                             /* bInterfaceNumber */
  0x00,                                             /* bAlternateSetting */
  0x02,                                             /* bNumEndpoints */
  0xff,                                             /* bInterfaceClass */
  0xff,                                             /* bInterfaceSubClass */
  0x00,                                             /* bInterfaceProtocol */
  0x05,                                             /* iInterface */
  
  ///////////////////////////////////////
  /// endpoint descriptor
  ///////////////////////////////////////
  0x07,                                             /* bLength */
  USB_ENDPOINT_DESCRIPTOR_TYPE,                     /* bDescriptorType */
  0x83,                                             /* bEndpointAddress */
  0x02,                                             /* bmAttributes */
  0x20, 0x00,                                       /* wMaxPacketSize */
  0x01,                                             /* bInterval */
  
  ///////////////////////////////////////
  /// endpoint descriptor
  ///////////////////////////////////////
  0x07,                                             /* bLength */
  USB_ENDPOINT_DESCRIPTOR_TYPE,                     /* bDescriptorType */
  0x03,                                             /* bEndpointAddress */
  0x02,                                             /* bmAttributes */
  0x20, 0x00,                                       /* wMaxPacketSize */
  0x01,                                             /* bInterval */
};
#define  WINUSB20_STRING_DESCRIPTOR0_STR   "\x09\x04"
#define  WINUSB20_STRING_DESCRIPTOR0_SIZE  (4)
WEAK __ALIGN_BEGIN  const uint8_t WINUSB20_StringDescriptor0 [4] __ALIGN_END = {
  0x04,                                         /* bLength */
  USB_STRING_DESCRIPTOR_TYPE,                   /* bDescriptorType */
  0x09, 0x04,                                   /* wLangID0 */
};
#define  WINUSB20_STRING_DESCRIPTOR1_STR   "TeenyUSB"
#define  WINUSB20_STRING_DESCRIPTOR1_SIZE   (18)
WEAK __ALIGN_BEGIN  const uint8_t WINUSB20_StringDescriptor1 [18] __ALIGN_END = {
  0x12,                                             /* bLength */
  USB_STRING_DESCRIPTOR_TYPE,                       /* bDescriptorType */
  'T', 0x00,                                        /* wcChar0 */
  'e', 0x00,                                        /* wcChar1 */
  'e', 0x00,                                        /* wcChar2 */
  'n', 0x00,                                        /* wcChar3 */
  'y', 0x00,                                        /* wcChar4 */
  'U', 0x00,                                        /* wcChar5 */
  'S', 0x00,                                        /* wcChar6 */
  'B', 0x00,                                        /* wcChar7 */
};
#define  WINUSB20_STRING_DESCRIPTOR2_STR   "TeenyUSB WinUSB DEMO"
#define  WINUSB20_STRING_DESCRIPTOR2_SIZE   (42)
WEAK __ALIGN_BEGIN  const uint8_t WINUSB20_StringDescriptor2 [42] __ALIGN_END = {
  0x2a,                                             /* bLength */
  USB_STRING_DESCRIPTOR_TYPE,                       /* bDescriptorType */
  'T', 0x00,                                        /* wcChar0 */
  'e', 0x00,                                        /* wcChar1 */
  'e', 0x00,                                        /* wcChar2 */
  'n', 0x00,                                        /* wcChar3 */
  'y', 0x00,                                        /* wcChar4 */
  'U', 0x00,                                        /* wcChar5 */
  'S', 0x00,                                        /* wcChar6 */
  'B', 0x00,                                        /* wcChar7 */
  ' ', 0x00,                                        /* wcChar8 */
  'W', 0x00,                                        /* wcChar9 */
  'i', 0x00,                                        /* wcChar10 */
  'n', 0x00,                                        /* wcChar11 */
  'U', 0x00,                                        /* wcChar12 */
  'S', 0x00,                                        /* wcChar13 */
  'B', 0x00,                                        /* wcChar14 */
  ' ', 0x00,                                        /* wcChar15 */
  'D', 0x00,                                        /* wcChar16 */
  'E', 0x00,                                        /* wcChar17 */
  'M', 0x00,                                        /* wcChar18 */
  'O', 0x00,                                        /* wcChar19 */
};
#define  WINUSB20_STRING_DESCRIPTOR3_STR   "TUSB123456"
#define  WINUSB20_STRING_DESCRIPTOR3_SIZE   (22)
WEAK __ALIGN_BEGIN  const uint8_t WINUSB20_StringDescriptor3 [22] __ALIGN_END = {
  0x16,                                             /* bLength */
  USB_STRING_DESCRIPTOR_TYPE,                       /* bDescriptorType */
  'T', 0x00,                                        /* wcChar0 */
  'U', 0x00,                                        /* wcChar1 */
  'S', 0x00,                                        /* wcChar2 */
  'B', 0x00,                                        /* wcChar3 */
  '1', 0x00,                                        /* wcChar4 */
  '2', 0x00,                                        /* wcChar5 */
  '3', 0x00,                                        /* wcChar6 */
  '4', 0x00,                                        /* wcChar7 */
  '5', 0x00,                                        /* wcChar8 */
  '6', 0x00,                                        /* wcChar9 */
};
#define  WINUSB20_STRING_DESCRIPTOR4_STR   "TeenyUSB WinUSB 0"
#define  WINUSB20_STRING_DESCRIPTOR4_SIZE   (36)
WEAK __ALIGN_BEGIN  const uint8_t WINUSB20_StringDescriptor4 [36] __ALIGN_END = {
  0x24,                                             /* bLength */
  USB_STRING_DESCRIPTOR_TYPE,                       /* bDescriptorType */
  'T', 0x00,                                        /* wcChar0 */
  'e', 0x00,                                        /* wcChar1 */
  'e', 0x00,                                        /* wcChar2 */
  'n', 0x00,                                        /* wcChar3 */
  'y', 0x00,                                        /* wcChar4 */
  'U', 0x00,                                        /* wcChar5 */
  'S', 0x00,                                        /* wcChar6 */
  'B', 0x00,                                        /* wcChar7 */
  ' ', 0x00,                                        /* wcChar8 */
  'W', 0x00,                                        /* wcChar9 */
  'i', 0x00,                                        /* wcChar10 */
  'n', 0x00,                                        /* wcChar11 */
  'U', 0x00,                                        /* wcChar12 */
  'S', 0x00,                                        /* wcChar13 */
  'B', 0x00,                                        /* wcChar14 */
  ' ', 0x00,                                        /* wcChar15 */
  '0', 0x00,                                        /* wcChar16 */
};
#define  WINUSB20_STRING_DESCRIPTOR5_STR   "TeenyUSB WinUSB 1"
#define  WINUSB20_STRING_DESCRIPTOR5_SIZE   (36)
WEAK __ALIGN_BEGIN  const uint8_t WINUSB20_StringDescriptor5 [36] __ALIGN_END = {
  0x24,                                             /* bLength */
  USB_STRING_DESCRIPTOR_TYPE,                       /* bDescriptorType */
  'T', 0x00,                                        /* wcChar0 */
  'e', 0x00,                                        /* wcChar1 */
  'e', 0x00,                                        /* wcChar2 */
  'n', 0x00,                                        /* wcChar3 */
  'y', 0x00,                                        /* wcChar4 */
  'U', 0x00,                                        /* wcChar5 */
  'S', 0x00,                                        /* wcChar6 */
  'B', 0x00,                                        /* wcChar7 */
  ' ', 0x00,                                        /* wcChar8 */
  'W', 0x00,                                        /* wcChar9 */
  'i', 0x00,                                        /* wcChar10 */
  'n', 0x00,                                        /* wcChar11 */
  'U', 0x00,                                        /* wcChar12 */
  'S', 0x00,                                        /* wcChar13 */
  'B', 0x00,                                        /* wcChar14 */
  ' ', 0x00,                                        /* wcChar15 */
  '1', 0x00,                                        /* wcChar16 */
};
#define WINUSB20_STRING_COUNT    (6)
const uint8_t* const WINUSB20_StringDescriptors[6] = {
  WINUSB20_StringDescriptor0,
  WINUSB20_StringDescriptor1,
  WINUSB20_StringDescriptor2,
  WINUSB20_StringDescriptor3,
  WINUSB20_StringDescriptor4,
  WINUSB20_StringDescriptor5,
};
//////////////////////////////////////////////////////
///// WCID 2.0 descripors
/////////////////////////////////////////////////////
#if defined(HAS_WCID_20)

#define  WINUSB20_WCID_DESC_SET_SIZE  (490)
WEAK __ALIGN_BEGIN const uint8_t WINUSB20_WCIDDescriptorSet [490] __ALIGN_END = {
  ///////////////////////////////////////
  /// WCID20 descriptor set descriptor
  ///////////////////////////////////////
  0x0a, 0x00,                                       /* wLength */
  0x00, 0x00,                                       /* wDescriptorType */
  0x00, 0x00, 0x03, 0x06,                           /* dwWindowsVersion */
  0xea, 0x01,                                       /* wDescriptorSetTotalLength */
  
  ///////////////////////////////////////
  /// WCID20 function subset descriptor
  ///////////////////////////////////////
  0x08, 0x00,                                       /* wLength */
  0x02, 0x00,                                       /* wDescriptorType */
  0x00,                                             /* bFirstInterface */
  0x00,                                             /* bReserved */
  0xa0, 0x00,                                       /* wSubsetLength */
  
  ///////////////////////////////////////
  /// WCID20 compatible ID descriptor
  ///////////////////////////////////////
  0x14, 0x00,                                       /* wLength */
  0x03, 0x00,                                       /* wDescriptorType */
  /* WINUSB */
  'W', 'I', 'N', 'U', 'S', 'B', 0x00, 0x00,         /* cCID_8 */
  /*  */
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,   /* cSubCID_8 */
  
  ///////////////////////////////////////
  /// WCID20 registry property descriptor
  ///////////////////////////////////////
  0x84, 0x00,                                       /* wLength */
  0x04, 0x00,                                       /* wDescriptorType */
  0x07, 0x00,                                       /* wPropertyDataType */
  0x2a, 0x00,                                       /* wPropertyNameLength */
  /* DeviceInterfaceGUIDs */
  'D', 0x00, 'e', 0x00, 'v', 0x00, 'i', 0x00,       /* wcPropertyName_21 */
  'c', 0x00, 'e', 0x00, 'I', 0x00, 'n', 0x00,       /* wcPropertyName_21 */
  't', 0x00, 'e', 0x00, 'r', 0x00, 'f', 0x00,       /* wcPropertyName_21 */
  'a', 0x00, 'c', 0x00, 'e', 0x00, 'G', 0x00,       /* wcPropertyName_21 */
  'U', 0x00, 'I', 0x00, 'D', 0x00, 's', 0x00,       /* wcPropertyName_21 */
  0x00, 0x00,                                       /* wcPropertyName_21 */
  0x50, 0x00,                                       /* wPropertyDataLength */
  /* {1D4B2365-4749-48EA-B38A-7C6FDDDD7E26} */
  '{', 0x00, '1', 0x00, 'D', 0x00, '4', 0x00,       /* wcPropertyData_40 */
  'B', 0x00, '2', 0x00, '3', 0x00, '6', 0x00,       /* wcPropertyData_40 */
  '5', 0x00, '-', 0x00, '4', 0x00, '7', 0x00,       /* wcPropertyData_40 */
  '4', 0x00, '9', 0x00, '-', 0x00, '4', 0x00,       /* wcPropertyData_40 */
  '8', 0x00, 'E', 0x00, 'A', 0x00, '-', 0x00,       /* wcPropertyData_40 */
  'B', 0x00, '3', 0x00, '8', 0x00, 'A', 0x00,       /* wcPropertyData_40 */
  '-', 0x00, '7', 0x00, 'C', 0x00, '6', 0x00,       /* wcPropertyData_40 */
  'F', 0x00, 'D', 0x00, 'D', 0x00, 'D', 0x00,       /* wcPropertyData_40 */
  'D', 0x00, '7', 0x00, 'E', 0x00, '2', 0x00,       /* wcPropertyData_40 */
  '6', 0x00, '}', 0x00, 0x00, 0x00, 0x00, 0x00,     /* wcPropertyData_40 */
  
  ///////////////////////////////////////
  /// WCID20 function subset descriptor
  ///////////////////////////////////////
  0x08, 0x00,                                       /* wLength */
  0x02, 0x00,                                       /* wDescriptorType */
  0x01,                                             /* bFirstInterface */
  0x00,                                             /* bReserved */
  0xa0, 0x00,                                       /* wSubsetLength */
  
  ///////////////////////////////////////
  /// WCID20 compatible ID descriptor
  ///////////////////////////////////////
  0x14, 0x00,                                       /* wLength */
  0x03, 0x00,                                       /* wDescriptorType */
  /* WINUSB */
  'W', 'I', 'N', 'U', 'S', 'B', 0x00, 0x00,         /* cCID_8 */
  /*  */
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,   /* cSubCID_8 */
  
  ///////////////////////////////////////
  /// WCID20 registry property descriptor
  ///////////////////////////////////////
  0x84, 0x00,                                       /* wLength */
  0x04, 0x00,                                       /* wDescriptorType */
  0x07, 0x00,                                       /* wPropertyDataType */
  0x2a, 0x00,                                       /* wPropertyNameLength */
  /* DeviceInterfaceGUIDs */
  'D', 0x00, 'e', 0x00, 'v', 0x00, 'i', 0x00,       /* wcPropertyName_21 */
  'c', 0x00, 'e', 0x00, 'I', 0x00, 'n', 0x00,       /* wcPropertyName_21 */
  't', 0x00, 'e', 0x00, 'r', 0x00, 'f', 0x00,       /* wcPropertyName_21 */
  'a', 0x00, 'c', 0x00, 'e', 0x00, 'G', 0x00,       /* wcPropertyName_21 */
  'U', 0x00, 'I', 0x00, 'D', 0x00, 's', 0x00,       /* wcPropertyName_21 */
  0x00, 0x00,                                       /* wcPropertyName_21 */
  0x50, 0x00,                                       /* wPropertyDataLength */
  /* {1D4B2365-4749-48EA-B38A-7C6FDDDD7E26} */
  '{', 0x00, '1', 0x00, 'D', 0x00, '4', 0x00,       /* wcPropertyData_40 */
  'B', 0x00, '2', 0x00, '3', 0x00, '6', 0x00,       /* wcPropertyData_40 */
  '5', 0x00, '-', 0x00, '4', 0x00, '7', 0x00,       /* wcPropertyData_40 */
  '4', 0x00, '9', 0x00, '-', 0x00, '4', 0x00,       /* wcPropertyData_40 */
  '8', 0x00, 'E', 0x00, 'A', 0x00, '-', 0x00,       /* wcPropertyData_40 */
  'B', 0x00, '3', 0x00, '8', 0x00, 'A', 0x00,       /* wcPropertyData_40 */
  '-', 0x00, '7', 0x00, 'C', 0x00, '6', 0x00,       /* wcPropertyData_40 */
  'F', 0x00, 'D', 0x00, 'D', 0x00, 'D', 0x00,       /* wcPropertyData_40 */
  'D', 0x00, '7', 0x00, 'E', 0x00, '2', 0x00,       /* wcPropertyData_40 */
  '6', 0x00, '}', 0x00, 0x00, 0x00, 0x00, 0x00,     /* wcPropertyData_40 */
  
  ///////////////////////////////////////
  /// WCID20 function subset descriptor
  ///////////////////////////////////////
  0x08, 0x00,                                       /* wLength */
  0x02, 0x00,                                       /* wDescriptorType */
  0x02,                                             /* bFirstInterface */
  0x00,                                             /* bReserved */
  0xa0, 0x00,                                       /* wSubsetLength */
  
  ///////////////////////////////////////
  /// WCID20 compatible ID descriptor
  ///////////////////////////////////////
  0x14, 0x00,                                       /* wLength */
  0x03, 0x00,                                       /* wDescriptorType */
  /* WINUSB */
  'W', 'I', 'N', 'U', 'S', 'B', 0x00, 0x00,         /* cCID_8 */
  /*  */
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,   /* cSubCID_8 */
  
  ///////////////////////////////////////
  /// WCID20 registry property descriptor
  ///////////////////////////////////////
  0x84, 0x00,                                       /* wLength */
  0x04, 0x00,                                       /* wDescriptorType */
  0x07, 0x00,                                       /* wPropertyDataType */
  0x2a, 0x00,                                       /* wPropertyNameLength */
  /* DeviceInterfaceGUIDs */
  'D', 0x00, 'e', 0x00, 'v', 0x00, 'i', 0x00,       /* wcPropertyName_21 */
  'c', 0x00, 'e', 0x00, 'I', 0x00, 'n', 0x00,       /* wcPropertyName_21 */
  't', 0x00, 'e', 0x00, 'r', 0x00, 'f', 0x00,       /* wcPropertyName_21 */
  'a', 0x00, 'c', 0x00, 'e', 0x00, 'G', 0x00,       /* wcPropertyName_21 */
  'U', 0x00, 'I', 0x00, 'D', 0x00, 's', 0x00,       /* wcPropertyName_21 */
  0x00, 0x00,                                       /* wcPropertyName_21 */
  0x50, 0x00,                                       /* wPropertyDataLength */
  /* {1D4B2365-4749-48EA-B38A-7C6FDDDD7E26} */
  '{', 0x00, '1', 0x00, 'D', 0x00, '4', 0x00,       /* wcPropertyData_40 */
  'B', 0x00, '2', 0x00, '3', 0x00, '6', 0x00,       /* wcPropertyData_40 */
  '5', 0x00, '-', 0x00, '4', 0x00, '7', 0x00,       /* wcPropertyData_40 */
  '4', 0x00, '9', 0x00, '-', 0x00, '4', 0x00,       /* wcPropertyData_40 */
  '8', 0x00, 'E', 0x00, 'A', 0x00, '-', 0x00,       /* wcPropertyData_40 */
  'B', 0x00, '3', 0x00, '8', 0x00, 'A', 0x00,       /* wcPropertyData_40 */
  '-', 0x00, '7', 0x00, 'C', 0x00, '6', 0x00,       /* wcPropertyData_40 */
  'F', 0x00, 'D', 0x00, 'D', 0x00, 'D', 0x00,       /* wcPropertyData_40 */
  'D', 0x00, '7', 0x00, 'E', 0x00, '2', 0x00,       /* wcPropertyData_40 */
  '6', 0x00, '}', 0x00, 0x00, 0x00, 0x00, 0x00,     /* wcPropertyData_40 */
};
#define  WINUSB20_WCID_BOS_SIZE  (33)
WEAK __ALIGN_BEGIN const uint8_t WINUSB20_WCIDBOS [33] __ALIGN_END = {
  ///////////////////////////////////////
  /// WCID20 BOS descriptor
  ///////////////////////////////////////
  0x05,                                             /* bLength */
  USB_DESC_TYPE_BOS,                                /* bDescriptorType */
  0x21, 0x00,                                       /* wTotalLength */
  0x01,                                             /* bNumDeviceCaps */
  
  ///////////////////////////////////////
  /// WCID20 device capability descriptor
  ///////////////////////////////////////
  0x1c,                                             /* bLength */
  0x10,                                             /* bDescriptorType */
  0x05,                                             /* bDevCapabilityType */
  0x00,                                             /* bReserved */
  0xdf, 0x60, 0xdd, 0xd8, 0x89, 0x45, 0xc7, 0x4c,   /* bPlatformCapabilityUUID_16 */
  0x9c, 0xd2, 0x65, 0x9d, 0x9e, 0x64, 0x8a, 0x9f,   /* bPlatformCapabilityUUID_16 */
  0x00, 0x00, 0x03, 0x06,                           /* dwWindowsVersion */
  LOBYTE(WINUSB20_WCID_DESC_SET_SIZE), HIBYTE(WINUSB20_WCID_DESC_SET_SIZE),/* wDescriptorSetTotalLength */
  WCID_VENDOR_CODE,                                 /* bVendorCode */
  0x00,                                             /* bAltEnumCode */
};


#endif    // #if defined(HAS_WCID_20)


WINUSB20_TXEP_MAX_SIZE
WINUSB20_RXEP_MAX_SIZE
//  Device descriptors
const tusb_descriptors WINUSB20_descriptors = {
  .device = WINUSB20_DeviceDescriptor,
  .config = WINUSB20_ConfigDescriptor,
  .strings = WINUSB20_StringDescriptors,
  .string_cnt = WINUSB20_STRING_COUNT,
#if defined(HAS_WCID)
#if defined(WINUSB20_WCID_DESCRIPTOR_SIZE)
  .wcid_desc = WINUSB20_WCIDDescriptor,
#else
  .wcid_desc = 0,
#endif // WINUSB20_WCID_DESCRIPTOR_SIZE)

#if defined(WINUSB20_WCID_PROPERTIES_SIZE)
  .wcid_properties = WINUSB20_WCIDProperties,
#else
  .wcid_properties = 0,
#endif // WINUSB20_WCID_PROPERTIES_SIZE

#endif // HAS_WCID

#if defined(HAS_WCID_20)
#if defined(WINUSB20_WCID_BOS_SIZE)
  .wcid_bos = WINUSB20_WCIDBOS,
#else
  .wcid_bos = 0,  
#endif // WINUSB20_WCID_BOS_SIZE)

#if defined(WINUSB20_WCID_DESC_SET_SIZE)
  .wcid_desc_set = WINUSB20_WCIDDescriptorSet,
#else
  .wcid_desc_set = 0,  
#endif // WINUSB20_WCID_DESC_SET_SIZE


#endif // HAS_WCID_20
};
/////////////////////////////////////////
//// Device 6
/////////////////////////////////////////
#include "teeny_usb.h"

#define  USER_HID_DEVICE_DESCRIPTOR_SIZE  (18)
__ALIGN_BEGIN  const uint8_t USER_HID_DeviceDescriptor [18] __ALIGN_END = {
  ///////////////////////////////////////
  /// device descriptor
  ///////////////////////////////////////
  0x12,                                             /* bLength */
  USB_DEVICE_DESCRIPTOR_TYPE,                       /* bDescriptorType */
  0x10, 0x02,                                       /* bcdUSB */
  0x00,                                             /* bDeviceClass */
  0x00,                                             /* bDeviceSubClass */
  0x00,                                             /* bDeviceProtocol */
  0x40,                                             /* bMaxPacketSize */
  0x83, 0x04,                                       /* idVendor */
  0x11, 0x00,                                       /* idProduct */
  0x00, 0x01,                                       /* bcdDevice */
  0x01,                                             /* iManufacturer */
  0x02,                                             /* iProduct */
  0x03,                                             /* iSerial */
  0x01,                                             /* bNumConfigurations */
};
#define  USER_HID_CONFIG_DESCRIPTOR_SIZE  (41)
__ALIGN_BEGIN  const uint8_t USER_HID_ConfigDescriptor [41] __ALIGN_END = {
  ///////////////////////////////////////
  /// config descriptor
  ///////////////////////////////////////
  0x09,                                             /* bLength */
  USB_CONFIGURATION_DESCRIPTOR_TYPE,                /* bDescriptorType */
  0x29, 0x00,                                       /* wTotalLength */
  0x01,                                             /* bNumInterfaces */
  0x01,                                             /* bConfigurationValue */
  0x00,                                             /* iConfiguration */
  0x80,                                             /* bmAttributes */
  0x64,                                             /* bMaxPower */
  
  ///////////////////////////////////////
  /// interface descriptor
  ///////////////////////////////////////
  0x09,                                             /* bLength */
  USB_INTERFACE_DESCRIPTOR_TYPE,                    /* bDescriptorType */
  0x00,                                             /* bInterfaceNumber */
  0x00,                                             /* bAlternateSetting */
  0x02,                                             /* bNumEndpoints */
  0x03,                                             /* bInterfaceClass */
  0x00,                                             /* bInterfaceSubClass */
  0x00,                                             /* bInterfaceProtocol */
  0x00,                                             /* iInterface */
  
  ///////////////////////////////////////
  /// hid descriptor
  ///////////////////////////////////////
  0x09,                                             /* bLength */
  0x21,                                             /* bDescriptorType */
  0x11, 0x01,                                       /* bcdHID */
  0x00,                                             /* bCountryCode */
  0x01,                                             /* bNumDescriptors */
  0x22,                                             /* bDescriptorType1 */
  0x18, 0x00,                                       /* wDescriptorLength1 */
  
  ///////////////////////////////////////
  /// endpoint descriptor
  ///////////////////////////////////////
  0x07,                                             /* bLength */
  USB_ENDPOINT_DESCRIPTOR_TYPE,                     /* bDescriptorType */
  0x81,                                             /* bEndpointAddress */
  0x03,                                             /* bmAttributes */
  0x40, 0x00,                                       /* wMaxPacketSize */
  0x01,                                             /* bInterval */
  
  ///////////////////////////////////////
  /// endpoint descriptor
  ///////////////////////////////////////
  0x07,                                             /* bLength */
  USB_ENDPOINT_DESCRIPTOR_TYPE,                     /* bDescriptorType */
  0x01,                                             /* bEndpointAddress */
  0x03,                                             /* bmAttributes */
  0x40, 0x00,                                       /* wMaxPacketSize */
  0x01,                                             /* bInterval */
};
#define  USER_HID_STRING_DESCRIPTOR0_STR   "\x09\x04"
#define  USER_HID_STRING_DESCRIPTOR0_SIZE  (4)
WEAK __ALIGN_BEGIN  const uint8_t USER_HID_StringDescriptor0 [4] __ALIGN_END = {
  0x04,                                         /* bLength */
  USB_STRING_DESCRIPTOR_TYPE,                   /* bDescriptorType */
  0x09, 0x04,                                   /* wLangID0 */
};
#define  USER_HID_STRING_DESCRIPTOR1_STR   "TeenyUSB"
#define  USER_HID_STRING_DESCRIPTOR1_SIZE   (18)
WEAK __ALIGN_BEGIN  const uint8_t USER_HID_StringDescriptor1 [18] __ALIGN_END = {
  0x12,                                             /* bLength */
  USB_STRING_DESCRIPTOR_TYPE,                       /* bDescriptorType */
  'T', 0x00,                                        /* wcChar0 */
  'e', 0x00,                                        /* wcChar1 */
  'e', 0x00,                                        /* wcChar2 */
  'n', 0x00,                                        /* wcChar3 */
  'y', 0x00,                                        /* wcChar4 */
  'U', 0x00,                                        /* wcChar5 */
  'S', 0x00,                                        /* wcChar6 */
  'B', 0x00,                                        /* wcChar7 */
};
#define  USER_HID_STRING_DESCRIPTOR2_STR   "TeenyUSB User HID DEMO"
#define  USER_HID_STRING_DESCRIPTOR2_SIZE   (46)
WEAK __ALIGN_BEGIN  const uint8_t USER_HID_StringDescriptor2 [46] __ALIGN_END = {
  0x2e,                                             /* bLength */
  USB_STRING_DESCRIPTOR_TYPE,                       /* bDescriptorType */
  'T', 0x00,                                        /* wcChar0 */
  'e', 0x00,                                        /* wcChar1 */
  'e', 0x00,                                        /* wcChar2 */
  'n', 0x00,                                        /* wcChar3 */
  'y', 0x00,                                        /* wcChar4 */
  'U', 0x00,                                        /* wcChar5 */
  'S', 0x00,                                        /* wcChar6 */
  'B', 0x00,                                        /* wcChar7 */
  ' ', 0x00,                                        /* wcChar8 */
  'U', 0x00,                                        /* wcChar9 */
  's', 0x00,                                        /* wcChar10 */
  'e', 0x00,                                        /* wcChar11 */
  'r', 0x00,                                        /* wcChar12 */
  ' ', 0x00,                                        /* wcChar13 */
  'H', 0x00,                                        /* wcChar14 */
  'I', 0x00,                                        /* wcChar15 */
  'D', 0x00,                                        /* wcChar16 */
  ' ', 0x00,                                        /* wcChar17 */
  'D', 0x00,                                        /* wcChar18 */
  'E', 0x00,                                        /* wcChar19 */
  'M', 0x00,                                        /* wcChar20 */
  'O', 0x00,                                        /* wcChar21 */
};
#define  USER_HID_STRING_DESCRIPTOR3_STR   "TUSB123456"
#define  USER_HID_STRING_DESCRIPTOR3_SIZE   (22)
WEAK __ALIGN_BEGIN  const uint8_t USER_HID_StringDescriptor3 [22] __ALIGN_END = {
  0x16,                                             /* bLength */
  USB_STRING_DESCRIPTOR_TYPE,                       /* bDescriptorType */
  'T', 0x00,                                        /* wcChar0 */
  'U', 0x00,                                        /* wcChar1 */
  'S', 0x00,                                        /* wcChar2 */
  'B', 0x00,                                        /* wcChar3 */
  '1', 0x00,                                        /* wcChar4 */
  '2', 0x00,                                        /* wcChar5 */
  '3', 0x00,                                        /* wcChar6 */
  '4', 0x00,                                        /* wcChar7 */
  '5', 0x00,                                        /* wcChar8 */
  '6', 0x00,                                        /* wcChar9 */
};
#define USER_HID_STRING_COUNT    (4)
const uint8_t* const USER_HID_StringDescriptors[4] = {
  USER_HID_StringDescriptor0,
  USER_HID_StringDescriptor1,
  USER_HID_StringDescriptor2,
  USER_HID_StringDescriptor3,
};
#define USER_HID_REPORT_DESCRIPTOR_SIZE_IF0  (24)
WEAK __ALIGN_BEGIN const uint8_t USER_HID_ReportDescriptor_if0[USER_HID_REPORT_DESCRIPTOR_SIZE_IF0] __ALIGN_END = {
        // report descriptor for general input/output
        0x06, 0x00, 0xFF,  // Usage Page (Vendor Defined 0xFF00)
        0x09, 0x01,        // Usage (0x01)
        0xA1, 0x01,        // Collection (Application)
        0x09, 0x02,        //   Usage (0x02)
        0x15, 0x00,        //   Logical Minimum (0)
        0x25, 0xFF,        //   Logical Maximum (255)
        0x75, 0x08,        //   Report Size (8)
        0x95, 0x40,        //   Report Count (64)
        0x81, 0x02,        //   Input (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position)
        0x09, 0x03,        //   Usage (0x03)
        0x91, 0x02,        //   Output (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position,Non-volatile)
        0xC0               // End Collection
};



USER_HID_TXEP_MAX_SIZE
USER_HID_RXEP_MAX_SIZE
//  Device descriptors
const tusb_descriptors USER_HID_descriptors = {
  .device = USER_HID_DeviceDescriptor,
  .config = USER_HID_ConfigDescriptor,
  .strings = USER_HID_StringDescriptors,
  .string_cnt = USER_HID_STRING_COUNT,
#if defined(HAS_WCID)
#if defined(USER_HID_WCID_DESCRIPTOR_SIZE)
  .wcid_desc = USER_HID_WCIDDescriptor,
#else
  .wcid_desc = 0,
#endif // USER_HID_WCID_DESCRIPTOR_SIZE)

#if defined(USER_HID_WCID_PROPERTIES_SIZE)
  .wcid_properties = USER_HID_WCIDProperties,
#else
  .wcid_properties = 0,
#endif // USER_HID_WCID_PROPERTIES_SIZE

#endif // HAS_WCID

#if defined(HAS_WCID_20)
#if defined(USER_HID_WCID_BOS_SIZE)
  .wcid_bos = USER_HID_WCIDBOS,
#else
  .wcid_bos = 0,  
#endif // USER_HID_WCID_BOS_SIZE)

#if defined(USER_HID_WCID_DESC_SET_SIZE)
  .wcid_desc_set = USER_HID_WCIDDescriptorSet,
#else
  .wcid_desc_set = 0,  
#endif // USER_HID_WCID_DESC_SET_SIZE


#endif // HAS_WCID_20
};
/////////////////////////////////////////
//// Device 7
/////////////////////////////////////////
#include "teeny_usb.h"

#define  KB_DEVICE_DESCRIPTOR_SIZE  (18)
__ALIGN_BEGIN  const uint8_t KB_DeviceDescriptor [18] __ALIGN_END = {
  ///////////////////////////////////////
  /// device descriptor
  ///////////////////////////////////////
  0x12,                                             /* bLength */
  USB_DEVICE_DESCRIPTOR_TYPE,                       /* bDescriptorType */
  0x00, 0x02,                                       /* bcdUSB */
  0x00,                                             /* bDeviceClass */
  0x00,                                             /* bDeviceSubClass */
  0x00,                                             /* bDeviceProtocol */
  0x40,                                             /* bMaxPacketSize */
  0x83, 0x04,                                       /* idVendor */
  0x11, 0x00,                                       /* idProduct */
  0x00, 0x01,                                       /* bcdDevice */
  0x01,                                             /* iManufacturer */
  0x02,                                             /* iProduct */
  0x03,                                             /* iSerial */
  0x01,                                             /* bNumConfigurations */
};
#define  KB_CONFIG_DESCRIPTOR_SIZE  (41)
__ALIGN_BEGIN  const uint8_t KB_ConfigDescriptor [41] __ALIGN_END = {
  ///////////////////////////////////////
  /// config descriptor
  ///////////////////////////////////////
  0x09,                                             /* bLength */
  USB_CONFIGURATION_DESCRIPTOR_TYPE,                /* bDescriptorType */
  0x29, 0x00,                                       /* wTotalLength */
  0x01,                                             /* bNumInterfaces */
  0x01,                                             /* bConfigurationValue */
  0x00,                                             /* iConfiguration */
  0x80,                                             /* bmAttributes */
  0x64,                                             /* bMaxPower */
  
  ///////////////////////////////////////
  /// interface descriptor
  ///////////////////////////////////////
  0x09,                                             /* bLength */
  USB_INTERFACE_DESCRIPTOR_TYPE,                    /* bDescriptorType */
  0x00,                                             /* bInterfaceNumber */
  0x00,                                             /* bAlternateSetting */
  0x02,                                             /* bNumEndpoints */
  0x03,                                             /* bInterfaceClass */
  0x01,                                             /* bInterfaceSubClass */
  0x01,                                             /* bInterfaceProtocol */
  0x00,                                             /* iInterface */
  
  ///////////////////////////////////////
  /// hid descriptor
  ///////////////////////////////////////
  0x09,                                             /* bLength */
  0x21,                                             /* bDescriptorType */
  0x11, 0x01,                                       /* bcdHID */
  0x00,                                             /* bCountryCode */
  0x01,                                             /* bNumDescriptors */
  0x22,                                             /* bDescriptorType1 */
  0x3f, 0x00,                                       /* wDescriptorLength1 */
  
  ///////////////////////////////////////
  /// endpoint descriptor
  ///////////////////////////////////////
  0x07,                                             /* bLength */
  USB_ENDPOINT_DESCRIPTOR_TYPE,                     /* bDescriptorType */
  0x81,                                             /* bEndpointAddress */
  0x03,                                             /* bmAttributes */
  0x08, 0x00,                                       /* wMaxPacketSize */
  0x01,                                             /* bInterval */
  
  ///////////////////////////////////////
  /// endpoint descriptor
  ///////////////////////////////////////
  0x07,                                             /* bLength */
  USB_ENDPOINT_DESCRIPTOR_TYPE,                     /* bDescriptorType */
  0x01,                                             /* bEndpointAddress */
  0x03,                                             /* bmAttributes */
  0x08, 0x00,                                       /* wMaxPacketSize */
  0x01,                                             /* bInterval */
};
#define  KB_STRING_DESCRIPTOR0_STR   "\x09\x04"
#define  KB_STRING_DESCRIPTOR0_SIZE  (4)
WEAK __ALIGN_BEGIN  const uint8_t KB_StringDescriptor0 [4] __ALIGN_END = {
  0x04,                                         /* bLength */
  USB_STRING_DESCRIPTOR_TYPE,                   /* bDescriptorType */
  0x09, 0x04,                                   /* wLangID0 */
};
#define  KB_STRING_DESCRIPTOR1_STR   "TeenyUSB"
#define  KB_STRING_DESCRIPTOR1_SIZE   (18)
WEAK __ALIGN_BEGIN  const uint8_t KB_StringDescriptor1 [18] __ALIGN_END = {
  0x12,                                             /* bLength */
  USB_STRING_DESCRIPTOR_TYPE,                       /* bDescriptorType */
  'T', 0x00,                                        /* wcChar0 */
  'e', 0x00,                                        /* wcChar1 */
  'e', 0x00,                                        /* wcChar2 */
  'n', 0x00,                                        /* wcChar3 */
  'y', 0x00,                                        /* wcChar4 */
  'U', 0x00,                                        /* wcChar5 */
  'S', 0x00,                                        /* wcChar6 */
  'B', 0x00,                                        /* wcChar7 */
};
#define  KB_STRING_DESCRIPTOR2_STR   "TeenyUSB Boot Keyboard DEMO"
#define  KB_STRING_DESCRIPTOR2_SIZE   (56)
WEAK __ALIGN_BEGIN  const uint8_t KB_StringDescriptor2 [56] __ALIGN_END = {
  0x38,                                             /* bLength */
  USB_STRING_DESCRIPTOR_TYPE,                       /* bDescriptorType */
  'T', 0x00,                                        /* wcChar0 */
  'e', 0x00,                                        /* wcChar1 */
  'e', 0x00,                                        /* wcChar2 */
  'n', 0x00,                                        /* wcChar3 */
  'y', 0x00,                                        /* wcChar4 */
  'U', 0x00,                                        /* wcChar5 */
  'S', 0x00,                                        /* wcChar6 */
  'B', 0x00,                                        /* wcChar7 */
  ' ', 0x00,                                        /* wcChar8 */
  'B', 0x00,                                        /* wcChar9 */
  'o', 0x00,                                        /* wcChar10 */
  'o', 0x00,                                        /* wcChar11 */
  't', 0x00,                                        /* wcChar12 */
  ' ', 0x00,                                        /* wcChar13 */
  'K', 0x00,                                        /* wcChar14 */
  'e', 0x00,                                        /* wcChar15 */
  'y', 0x00,                                        /* wcChar16 */
  'b', 0x00,                                        /* wcChar17 */
  'o', 0x00,                                        /* wcChar18 */
  'a', 0x00,                                        /* wcChar19 */
  'r', 0x00,                                        /* wcChar20 */
  'd', 0x00,                                        /* wcChar21 */
  ' ', 0x00,                                        /* wcChar22 */
  'D', 0x00,                                        /* wcChar23 */
  'E', 0x00,                                        /* wcChar24 */
  'M', 0x00,                                        /* wcChar25 */
  'O', 0x00,                                        /* wcChar26 */
};
#define  KB_STRING_DESCRIPTOR3_STR   "TUSB123456"
#define  KB_STRING_DESCRIPTOR3_SIZE   (22)
WEAK __ALIGN_BEGIN  const uint8_t KB_StringDescriptor3 [22] __ALIGN_END = {
  0x16,                                             /* bLength */
  USB_STRING_DESCRIPTOR_TYPE,                       /* bDescriptorType */
  'T', 0x00,                                        /* wcChar0 */
  'U', 0x00,                                        /* wcChar1 */
  'S', 0x00,                                        /* wcChar2 */
  'B', 0x00,                                        /* wcChar3 */
  '1', 0x00,                                        /* wcChar4 */
  '2', 0x00,                                        /* wcChar5 */
  '3', 0x00,                                        /* wcChar6 */
  '4', 0x00,                                        /* wcChar7 */
  '5', 0x00,                                        /* wcChar8 */
  '6', 0x00,                                        /* wcChar9 */
};
#define KB_STRING_COUNT    (4)
const uint8_t* const KB_StringDescriptors[4] = {
  KB_StringDescriptor0,
  KB_StringDescriptor1,
  KB_StringDescriptor2,
  KB_StringDescriptor3,
};
#define KB_REPORT_DESCRIPTOR_SIZE_IF0  (63)
WEAK __ALIGN_BEGIN const uint8_t KB_ReportDescriptor_if0[KB_REPORT_DESCRIPTOR_SIZE_IF0] __ALIGN_END = {
        //  Boot keyboad report descriptor
        0x05, 0x01,     // USAGE_PAGE (Generic Desktop)
        0x09, 0x06,     // USAGE (Keyboard)
        0xa1, 0x01,     // COLLECTION (Application)
        0x05, 0x07,     //   USAGE_PAGE (Keyboard)
        0x19, 0xe0,     //   USAGE_MINIMUM (Keyboard LeftControl)
        0x29, 0xe7,     //   USAGE_MAXIMUM (Keyboard Right GUI)
        0x15, 0x00,     //   LOGICAL_MINIMUM (0)
        0x25, 0x01,     //   LOGICAL_MAXIMUM (1)
        0x75, 0x01,     //   REPORT_SIZE (1)
        0x95, 0x08,     //   REPORT_COUNT (8)
        0x81, 0x02,     //   INPUT (Data,Var,Abs)
        0x95, 0x01,     //   REPORT_COUNT (1)
        0x75, 0x08,     //   REPORT_SIZE (8)
        0x81, 0x03,     //   INPUT (Cnst,Var,Abs)
        0x95, 0x05,     //   REPORT_COUNT (5)
        0x75, 0x01,     //   REPORT_SIZE (1)
        0x05, 0x08,     //   USAGE_PAGE (LEDs)
        0x19, 0x01,     //   USAGE_MINIMUM (Num Lock)
        0x29, 0x05,     //   USAGE_MAXIMUM (Kana)
        0x91, 0x02,     //   OUTPUT (Data,Var,Abs)
        0x95, 0x01,     //   REPORT_COUNT (1)
        0x75, 0x03,     //   REPORT_SIZE (3)
        0x91, 0x03,     //   OUTPUT (Cnst,Var,Abs)
        0x95, 0x06,     //   REPORT_COUNT (6)
        0x75, 0x08,     //   REPORT_SIZE (8)
        0x15, 0x00,     //   LOGICAL_MINIMUM (0)
        0x25, 0x65,     //   LOGICAL_MAXIMUM (101)
        0x05, 0x07,     //   USAGE_PAGE (Keyboard)
        0x19, 0x00,     //   USAGE_MINIMUM (Reserved (no event indicated))
        0x29, 0x65,     //   USAGE_MAXIMUM (Keyboard Application)
        0x81, 0x00,     //   INPUT (Data,Ary,Abs)
        0xc0            // END_COLLECTION
    };



KB_TXEP_MAX_SIZE
KB_RXEP_MAX_SIZE
//  Device descriptors
const tusb_descriptors KB_descriptors = {
  .device = KB_DeviceDescriptor,
  .config = KB_ConfigDescriptor,
  .strings = KB_StringDescriptors,
  .string_cnt = KB_STRING_COUNT,
#if defined(HAS_WCID)
#if defined(KB_WCID_DESCRIPTOR_SIZE)
  .wcid_desc = KB_WCIDDescriptor,
#else
  .wcid_desc = 0,
#endif // KB_WCID_DESCRIPTOR_SIZE)

#if defined(KB_WCID_PROPERTIES_SIZE)
  .wcid_properties = KB_WCIDProperties,
#else
  .wcid_properties = 0,
#endif // KB_WCID_PROPERTIES_SIZE

#endif // HAS_WCID

#if defined(HAS_WCID_20)
#if defined(KB_WCID_BOS_SIZE)
  .wcid_bos = KB_WCIDBOS,
#else
  .wcid_bos = 0,  
#endif // KB_WCID_BOS_SIZE)

#if defined(KB_WCID_DESC_SET_SIZE)
  .wcid_desc_set = KB_WCIDDescriptorSet,
#else
  .wcid_desc_set = 0,  
#endif // KB_WCID_DESC_SET_SIZE


#endif // HAS_WCID_20
};
/////////////////////////////////////////
//// Device 8
/////////////////////////////////////////
#include "teeny_usb.h"

#define  MOUSE_DEVICE_DESCRIPTOR_SIZE  (18)
__ALIGN_BEGIN  const uint8_t MOUSE_DeviceDescriptor [18] __ALIGN_END = {
  ///////////////////////////////////////
  /// device descriptor
  ///////////////////////////////////////
  0x12,                                             /* bLength */
  USB_DEVICE_DESCRIPTOR_TYPE,                       /* bDescriptorType */
  0x00, 0x02,                                       /* bcdUSB */
  0x00,                                             /* bDeviceClass */
  0x00,                                             /* bDeviceSubClass */
  0x00,                                             /* bDeviceProtocol */
  0x40,                                             /* bMaxPacketSize */
  0x83, 0x04,                                       /* idVendor */
  0x11, 0x00,                                       /* idProduct */
  0x00, 0x01,                                       /* bcdDevice */
  0x01,                                             /* iManufacturer */
  0x02,                                             /* iProduct */
  0x03,                                             /* iSerial */
  0x01,                                             /* bNumConfigurations */
};
#define  MOUSE_CONFIG_DESCRIPTOR_SIZE  (41)
__ALIGN_BEGIN  const uint8_t MOUSE_ConfigDescriptor [41] __ALIGN_END = {
  ///////////////////////////////////////
  /// config descriptor
  ///////////////////////////////////////
  0x09,                                             /* bLength */
  USB_CONFIGURATION_DESCRIPTOR_TYPE,                /* bDescriptorType */
  0x29, 0x00,                                       /* wTotalLength */
  0x01,                                             /* bNumInterfaces */
  0x01,                                             /* bConfigurationValue */
  0x00,                                             /* iConfiguration */
  0x80,                                             /* bmAttributes */
  0x64,                                             /* bMaxPower */
  
  ///////////////////////////////////////
  /// interface descriptor
  ///////////////////////////////////////
  0x09,                                             /* bLength */
  USB_INTERFACE_DESCRIPTOR_TYPE,                    /* bDescriptorType */
  0x00,                                             /* bInterfaceNumber */
  0x00,                                             /* bAlternateSetting */
  0x02,                                             /* bNumEndpoints */
  0x03,                                             /* bInterfaceClass */
  0x01,                                             /* bInterfaceSubClass */
  0x02,                                             /* bInterfaceProtocol */
  0x00,                                             /* iInterface */
  
  ///////////////////////////////////////
  /// hid descriptor
  ///////////////////////////////////////
  0x09,                                             /* bLength */
  0x21,                                             /* bDescriptorType */
  0x11, 0x01,                                       /* bcdHID */
  0x00,                                             /* bCountryCode */
  0x01,                                             /* bNumDescriptors */
  0x22,                                             /* bDescriptorType1 */
  0x32, 0x00,                                       /* wDescriptorLength1 */
  
  ///////////////////////////////////////
  /// endpoint descriptor
  ///////////////////////////////////////
  0x07,                                             /* bLength */
  USB_ENDPOINT_DESCRIPTOR_TYPE,                     /* bDescriptorType */
  0x81,                                             /* bEndpointAddress */
  0x03,                                             /* bmAttributes */
  0x08, 0x00,                                       /* wMaxPacketSize */
  0x01,                                             /* bInterval */
  
  ///////////////////////////////////////
  /// endpoint descriptor
  ///////////////////////////////////////
  0x07,                                             /* bLength */
  USB_ENDPOINT_DESCRIPTOR_TYPE,                     /* bDescriptorType */
  0x01,                                             /* bEndpointAddress */
  0x03,                                             /* bmAttributes */
  0x08, 0x00,                                       /* wMaxPacketSize */
  0x01,                                             /* bInterval */
};
#define  MOUSE_STRING_DESCRIPTOR0_STR   "\x09\x04"
#define  MOUSE_STRING_DESCRIPTOR0_SIZE  (4)
WEAK __ALIGN_BEGIN  const uint8_t MOUSE_StringDescriptor0 [4] __ALIGN_END = {
  0x04,                                         /* bLength */
  USB_STRING_DESCRIPTOR_TYPE,                   /* bDescriptorType */
  0x09, 0x04,                                   /* wLangID0 */
};
#define  MOUSE_STRING_DESCRIPTOR1_STR   "TeenyUSB"
#define  MOUSE_STRING_DESCRIPTOR1_SIZE   (18)
WEAK __ALIGN_BEGIN  const uint8_t MOUSE_StringDescriptor1 [18] __ALIGN_END = {
  0x12,                                             /* bLength */
  USB_STRING_DESCRIPTOR_TYPE,                       /* bDescriptorType */
  'T', 0x00,                                        /* wcChar0 */
  'e', 0x00,                                        /* wcChar1 */
  'e', 0x00,                                        /* wcChar2 */
  'n', 0x00,                                        /* wcChar3 */
  'y', 0x00,                                        /* wcChar4 */
  'U', 0x00,                                        /* wcChar5 */
  'S', 0x00,                                        /* wcChar6 */
  'B', 0x00,                                        /* wcChar7 */
};
#define  MOUSE_STRING_DESCRIPTOR2_STR   "TeenyUSB Boot Mouse DEMO"
#define  MOUSE_STRING_DESCRIPTOR2_SIZE   (50)
WEAK __ALIGN_BEGIN  const uint8_t MOUSE_StringDescriptor2 [50] __ALIGN_END = {
  0x32,                                             /* bLength */
  USB_STRING_DESCRIPTOR_TYPE,                       /* bDescriptorType */
  'T', 0x00,                                        /* wcChar0 */
  'e', 0x00,                                        /* wcChar1 */
  'e', 0x00,                                        /* wcChar2 */
  'n', 0x00,                                        /* wcChar3 */
  'y', 0x00,                                        /* wcChar4 */
  'U', 0x00,                                        /* wcChar5 */
  'S', 0x00,                                        /* wcChar6 */
  'B', 0x00,                                        /* wcChar7 */
  ' ', 0x00,                                        /* wcChar8 */
  'B', 0x00,                                        /* wcChar9 */
  'o', 0x00,                                        /* wcChar10 */
  'o', 0x00,                                        /* wcChar11 */
  't', 0x00,                                        /* wcChar12 */
  ' ', 0x00,                                        /* wcChar13 */
  'M', 0x00,                                        /* wcChar14 */
  'o', 0x00,                                        /* wcChar15 */
  'u', 0x00,                                        /* wcChar16 */
  's', 0x00,                                        /* wcChar17 */
  'e', 0x00,                                        /* wcChar18 */
  ' ', 0x00,                                        /* wcChar19 */
  'D', 0x00,                                        /* wcChar20 */
  'E', 0x00,                                        /* wcChar21 */
  'M', 0x00,                                        /* wcChar22 */
  'O', 0x00,                                        /* wcChar23 */
};
#define  MOUSE_STRING_DESCRIPTOR3_STR   "TUSB123456"
#define  MOUSE_STRING_DESCRIPTOR3_SIZE   (22)
WEAK __ALIGN_BEGIN  const uint8_t MOUSE_StringDescriptor3 [22] __ALIGN_END = {
  0x16,                                             /* bLength */
  USB_STRING_DESCRIPTOR_TYPE,                       /* bDescriptorType */
  'T', 0x00,                                        /* wcChar0 */
  'U', 0x00,                                        /* wcChar1 */
  'S', 0x00,                                        /* wcChar2 */
  'B', 0x00,                                        /* wcChar3 */
  '1', 0x00,                                        /* wcChar4 */
  '2', 0x00,                                        /* wcChar5 */
  '3', 0x00,                                        /* wcChar6 */
  '4', 0x00,                                        /* wcChar7 */
  '5', 0x00,                                        /* wcChar8 */
  '6', 0x00,                                        /* wcChar9 */
};
#define MOUSE_STRING_COUNT    (4)
const uint8_t* const MOUSE_StringDescriptors[4] = {
  MOUSE_StringDescriptor0,
  MOUSE_StringDescriptor1,
  MOUSE_StringDescriptor2,
  MOUSE_StringDescriptor3,
};
#define MOUSE_REPORT_DESCRIPTOR_SIZE_IF0  (50)
WEAK __ALIGN_BEGIN const uint8_t MOUSE_ReportDescriptor_if0[MOUSE_REPORT_DESCRIPTOR_SIZE_IF0] __ALIGN_END = {
        //  Boot Mouse report descriptor
        0x05, 0x01,     // USAGE_PAGE (Generic Desktop)
        0x09, 0x02,     // USAGE (Mouse)
        0xa1, 0x01,     // COLLECTION (Application)
        0x09, 0x01,     //   USAGE (Pointer)
        0xa1, 0x00,     //   COLLECTION (Physical)
        0x05, 0x09,     //     USAGE_PAGE (Button)
        0x19, 0x01,     //     USAGE_MINIMUM (Button 1)
        0x29, 0x03,     //     USAGE_MAXIMUM (Button 3)
        0x15, 0x00,     //     LOGICAL_MINIMUM (0)
        0x25, 0x01,     //     LOGICAL_MAXIMUM (1)
        0x95, 0x03,     //     REPORT_COUNT (3)
        0x75, 0x01,     //     REPORT_SIZE (1)
        0x81, 0x02,     //     INPUT (Data,Var,Abs)
        0x95, 0x01,     //     REPORT_COUNT (1)
        0x75, 0x05,     //     REPORT_SIZE (5)
        0x81, 0x03,     //     INPUT (Cnst,Var,Abs)
        0x05, 0x01,     //     USAGE_PAGE (Generic Desktop)
        0x09, 0x30,     //     USAGE (X)
        0x09, 0x31,     //     USAGE (Y)
        0x15, 0x81,     //     LOGICAL_MINIMUM (-127)
        0x25, 0x7f,     //     LOGICAL_MAXIMUM (127)
        0x75, 0x08,     //     REPORT_SIZE (8)
        0x95, 0x02,     //     REPORT_COUNT (2)
        0x81, 0x06,     //     INPUT (Data,Var,Rel)
        0xc0,           //   END_COLLECTION
        0xc0            // END_COLLECTION
    };



MOUSE_TXEP_MAX_SIZE
MOUSE_RXEP_MAX_SIZE
//  Device descriptors
const tusb_descriptors MOUSE_descriptors = {
  .device = MOUSE_DeviceDescriptor,
  .config = MOUSE_ConfigDescriptor,
  .strings = MOUSE_StringDescriptors,
  .string_cnt = MOUSE_STRING_COUNT,
#if defined(HAS_WCID)
#if defined(MOUSE_WCID_DESCRIPTOR_SIZE)
  .wcid_desc = MOUSE_WCIDDescriptor,
#else
  .wcid_desc = 0,
#endif // MOUSE_WCID_DESCRIPTOR_SIZE)

#if defined(MOUSE_WCID_PROPERTIES_SIZE)
  .wcid_properties = MOUSE_WCIDProperties,
#else
  .wcid_properties = 0,
#endif // MOUSE_WCID_PROPERTIES_SIZE

#endif // HAS_WCID

#if defined(HAS_WCID_20)
#if defined(MOUSE_WCID_BOS_SIZE)
  .wcid_bos = MOUSE_WCIDBOS,
#else
  .wcid_bos = 0,  
#endif // MOUSE_WCID_BOS_SIZE)

#if defined(MOUSE_WCID_DESC_SET_SIZE)
  .wcid_desc_set = MOUSE_WCIDDescriptorSet,
#else
  .wcid_desc_set = 0,  
#endif // MOUSE_WCID_DESC_SET_SIZE


#endif // HAS_WCID_20
};
/////////////////////////////////////////
//// Device 9
/////////////////////////////////////////
#include "teeny_usb.h"

#define  MSC_DEVICE_DESCRIPTOR_SIZE  (18)
__ALIGN_BEGIN  const uint8_t MSC_DeviceDescriptor [18] __ALIGN_END = {
  ///////////////////////////////////////
  /// device descriptor
  ///////////////////////////////////////
  0x12,                                             /* bLength */
  USB_DEVICE_DESCRIPTOR_TYPE,                       /* bDescriptorType */
  0x00, 0x02,                                       /* bcdUSB */
  0x00,                                             /* bDeviceClass */
  0x00,                                             /* bDeviceSubClass */
  0x00,                                             /* bDeviceProtocol */
  0x40,                                             /* bMaxPacketSize */
  0x83, 0x04,                                       /* idVendor */
  0x11, 0x00,                                       /* idProduct */
  0x00, 0x01,                                       /* bcdDevice */
  0x01,                                             /* iManufacturer */
  0x02,                                             /* iProduct */
  0x03,                                             /* iSerial */
  0x01,                                             /* bNumConfigurations */
};
#define  MSC_CONFIG_DESCRIPTOR_SIZE  (32)
__ALIGN_BEGIN  const uint8_t MSC_ConfigDescriptor [32] __ALIGN_END = {
  ///////////////////////////////////////
  /// config descriptor
  ///////////////////////////////////////
  0x09,                                             /* bLength */
  USB_CONFIGURATION_DESCRIPTOR_TYPE,                /* bDescriptorType */
  0x20, 0x00,                                       /* wTotalLength */
  0x01,                                             /* bNumInterfaces */
  0x01,                                             /* bConfigurationValue */
  0x00,                                             /* iConfiguration */
  0x80,                                             /* bmAttributes */
  0x64,                                             /* bMaxPower */
  
  ///////////////////////////////////////
  /// interface descriptor
  ///////////////////////////////////////
  0x09,                                             /* bLength */
  USB_INTERFACE_DESCRIPTOR_TYPE,                    /* bDescriptorType */
  0x00,                                             /* bInterfaceNumber */
  0x00,                                             /* bAlternateSetting */
  0x02,                                             /* bNumEndpoints */
  0x08,                                             /* bInterfaceClass */
  0x06,                                             /* bInterfaceSubClass */
  0x50,                                             /* bInterfaceProtocol */
  0x00,                                             /* iInterface */
  
  ///////////////////////////////////////
  /// endpoint descriptor
  ///////////////////////////////////////
  0x07,                                             /* bLength */
  USB_ENDPOINT_DESCRIPTOR_TYPE,                     /* bDescriptorType */
  0x81,                                             /* bEndpointAddress */
  0x02,                                             /* bmAttributes */
  0x40, 0x00,                                       /* wMaxPacketSize */
  0x01,                                             /* bInterval */
  
  ///////////////////////////////////////
  /// endpoint descriptor
  ///////////////////////////////////////
  0x07,                                             /* bLength */
  USB_ENDPOINT_DESCRIPTOR_TYPE,                     /* bDescriptorType */
  0x02,                                             /* bEndpointAddress */
  0x02,                                             /* bmAttributes */
  0x40, 0x00,                                       /* wMaxPacketSize */
  0x01,                                             /* bInterval */
};
#define  MSC_STRING_DESCRIPTOR0_STR   "\x09\x04"
#define  MSC_STRING_DESCRIPTOR0_SIZE  (4)
WEAK __ALIGN_BEGIN  const uint8_t MSC_StringDescriptor0 [4] __ALIGN_END = {
  0x04,                                         /* bLength */
  USB_STRING_DESCRIPTOR_TYPE,                   /* bDescriptorType */
  0x09, 0x04,                                   /* wLangID0 */
};
#define  MSC_STRING_DESCRIPTOR1_STR   "TeenyUSB"
#define  MSC_STRING_DESCRIPTOR1_SIZE   (18)
WEAK __ALIGN_BEGIN  const uint8_t MSC_StringDescriptor1 [18] __ALIGN_END = {
  0x12,                                             /* bLength */
  USB_STRING_DESCRIPTOR_TYPE,                       /* bDescriptorType */
  'T', 0x00,                                        /* wcChar0 */
  'e', 0x00,                                        /* wcChar1 */
  'e', 0x00,                                        /* wcChar2 */
  'n', 0x00,                                        /* wcChar3 */
  'y', 0x00,                                        /* wcChar4 */
  'U', 0x00,                                        /* wcChar5 */
  'S', 0x00,                                        /* wcChar6 */
  'B', 0x00,                                        /* wcChar7 */
};
#define  MSC_STRING_DESCRIPTOR2_STR   "TeenyUSB MSC DEMO"
#define  MSC_STRING_DESCRIPTOR2_SIZE   (36)
WEAK __ALIGN_BEGIN  const uint8_t MSC_StringDescriptor2 [36] __ALIGN_END = {
  0x24,                                             /* bLength */
  USB_STRING_DESCRIPTOR_TYPE,                       /* bDescriptorType */
  'T', 0x00,                                        /* wcChar0 */
  'e', 0x00,                                        /* wcChar1 */
  'e', 0x00,                                        /* wcChar2 */
  'n', 0x00,                                        /* wcChar3 */
  'y', 0x00,                                        /* wcChar4 */
  'U', 0x00,                                        /* wcChar5 */
  'S', 0x00,                                        /* wcChar6 */
  'B', 0x00,                                        /* wcChar7 */
  ' ', 0x00,                                        /* wcChar8 */
  'M', 0x00,                                        /* wcChar9 */
  'S', 0x00,                                        /* wcChar10 */
  'C', 0x00,                                        /* wcChar11 */
  ' ', 0x00,                                        /* wcChar12 */
  'D', 0x00,                                        /* wcChar13 */
  'E', 0x00,                                        /* wcChar14 */
  'M', 0x00,                                        /* wcChar15 */
  'O', 0x00,                                        /* wcChar16 */
};
#define  MSC_STRING_DESCRIPTOR3_STR   "TUSB123456"
#define  MSC_STRING_DESCRIPTOR3_SIZE   (22)
WEAK __ALIGN_BEGIN  const uint8_t MSC_StringDescriptor3 [22] __ALIGN_END = {
  0x16,                                             /* bLength */
  USB_STRING_DESCRIPTOR_TYPE,                       /* bDescriptorType */
  'T', 0x00,                                        /* wcChar0 */
  'U', 0x00,                                        /* wcChar1 */
  'S', 0x00,                                        /* wcChar2 */
  'B', 0x00,                                        /* wcChar3 */
  '1', 0x00,                                        /* wcChar4 */
  '2', 0x00,                                        /* wcChar5 */
  '3', 0x00,                                        /* wcChar6 */
  '4', 0x00,                                        /* wcChar7 */
  '5', 0x00,                                        /* wcChar8 */
  '6', 0x00,                                        /* wcChar9 */
};
#define MSC_STRING_COUNT    (4)
const uint8_t* const MSC_StringDescriptors[4] = {
  MSC_StringDescriptor0,
  MSC_StringDescriptor1,
  MSC_StringDescriptor2,
  MSC_StringDescriptor3,
};


MSC_TXEP_MAX_SIZE
MSC_RXEP_MAX_SIZE
//  Device descriptors
const tusb_descriptors MSC_descriptors = {
  .device = MSC_DeviceDescriptor,
  .config = MSC_ConfigDescriptor,
  .strings = MSC_StringDescriptors,
  .string_cnt = MSC_STRING_COUNT,
#if defined(HAS_WCID)
#if defined(MSC_WCID_DESCRIPTOR_SIZE)
  .wcid_desc = MSC_WCIDDescriptor,
#else
  .wcid_desc = 0,
#endif // MSC_WCID_DESCRIPTOR_SIZE)

#if defined(MSC_WCID_PROPERTIES_SIZE)
  .wcid_properties = MSC_WCIDProperties,
#else
  .wcid_properties = 0,
#endif // MSC_WCID_PROPERTIES_SIZE

#endif // HAS_WCID

#if defined(HAS_WCID_20)
#if defined(MSC_WCID_BOS_SIZE)
  .wcid_bos = MSC_WCIDBOS,
#else
  .wcid_bos = 0,  
#endif // MSC_WCID_BOS_SIZE)

#if defined(MSC_WCID_DESC_SET_SIZE)
  .wcid_desc_set = MSC_WCIDDescriptorSet,
#else
  .wcid_desc_set = 0,  
#endif // MSC_WCID_DESC_SET_SIZE


#endif // HAS_WCID_20
};
/////////////////////////////////////////
//// Device 10
/////////////////////////////////////////
#include "teeny_usb.h"

#define  DAPV1_DEVICE_DESCRIPTOR_SIZE  (18)
__ALIGN_BEGIN  const uint8_t DAPV1_DeviceDescriptor [18] __ALIGN_END = {
  ///////////////////////////////////////
  /// device descriptor
  ///////////////////////////////////////
  0x12,                                             /* bLength */
  USB_DEVICE_DESCRIPTOR_TYPE,                       /* bDescriptorType */
  0x00, 0x02,                                       /* bcdUSB */
  0x00,                                             /* bDeviceClass */
  0x00,                                             /* bDeviceSubClass */
  0x00,                                             /* bDeviceProtocol */
  0x40,                                             /* bMaxPacketSize */
  0x28, 0x0d,                                       /* idVendor */
  0x04, 0x02,                                       /* idProduct */
  0x00, 0x01,                                       /* bcdDevice */
  0x01,                                             /* iManufacturer */
  0x02,                                             /* iProduct */
  0x03,                                             /* iSerial */
  0x01,                                             /* bNumConfigurations */
};
#define  DAPV1_CONFIG_DESCRIPTOR_SIZE  (41)
__ALIGN_BEGIN  const uint8_t DAPV1_ConfigDescriptor [41] __ALIGN_END = {
  ///////////////////////////////////////
  /// config descriptor
  ///////////////////////////////////////
  0x09,                                             /* bLength */
  USB_CONFIGURATION_DESCRIPTOR_TYPE,                /* bDescriptorType */
  0x29, 0x00,                                       /* wTotalLength */
  0x01,                                             /* bNumInterfaces */
  0x01,                                             /* bConfigurationValue */
  0x00,                                             /* iConfiguration */
  0x80,                                             /* bmAttributes */
  0x64,                                             /* bMaxPower */
  
  ///////////////////////////////////////
  /// interface descriptor
  ///////////////////////////////////////
  0x09,                                             /* bLength */
  USB_INTERFACE_DESCRIPTOR_TYPE,                    /* bDescriptorType */
  0x00,                                             /* bInterfaceNumber */
  0x00,                                             /* bAlternateSetting */
  0x02,                                             /* bNumEndpoints */
  0x03,                                             /* bInterfaceClass */
  0x00,                                             /* bInterfaceSubClass */
  0x00,                                             /* bInterfaceProtocol */
  0x00,                                             /* iInterface */
  
  ///////////////////////////////////////
  /// hid descriptor
  ///////////////////////////////////////
  0x09,                                             /* bLength */
  0x21,                                             /* bDescriptorType */
  0x11, 0x01,                                       /* bcdHID */
  0x00,                                             /* bCountryCode */
  0x01,                                             /* bNumDescriptors */
  0x22,                                             /* bDescriptorType1 */
  0x21, 0x00,                                       /* wDescriptorLength1 */
  
  ///////////////////////////////////////
  /// endpoint descriptor
  ///////////////////////////////////////
  0x07,                                             /* bLength */
  USB_ENDPOINT_DESCRIPTOR_TYPE,                     /* bDescriptorType */
  0x82,                                             /* bEndpointAddress */
  0x03,                                             /* bmAttributes */
  0x40, 0x00,                                       /* wMaxPacketSize */
  0x01,                                             /* bInterval */
  
  ///////////////////////////////////////
  /// endpoint descriptor
  ///////////////////////////////////////
  0x07,                                             /* bLength */
  USB_ENDPOINT_DESCRIPTOR_TYPE,                     /* bDescriptorType */
  0x01,                                             /* bEndpointAddress */
  0x03,                                             /* bmAttributes */
  0x40, 0x00,                                       /* wMaxPacketSize */
  0x01,                                             /* bInterval */
};
#define  DAPV1_STRING_DESCRIPTOR0_STR   "\x09\x04"
#define  DAPV1_STRING_DESCRIPTOR0_SIZE  (4)
WEAK __ALIGN_BEGIN  const uint8_t DAPV1_StringDescriptor0 [4] __ALIGN_END = {
  0x04,                                         /* bLength */
  USB_STRING_DESCRIPTOR_TYPE,                   /* bDescriptorType */
  0x09, 0x04,                                   /* wLangID0 */
};
#define  DAPV1_STRING_DESCRIPTOR1_STR   "TeenyUSB"
#define  DAPV1_STRING_DESCRIPTOR1_SIZE   (18)
WEAK __ALIGN_BEGIN  const uint8_t DAPV1_StringDescriptor1 [18] __ALIGN_END = {
  0x12,                                             /* bLength */
  USB_STRING_DESCRIPTOR_TYPE,                       /* bDescriptorType */
  'T', 0x00,                                        /* wcChar0 */
  'e', 0x00,                                        /* wcChar1 */
  'e', 0x00,                                        /* wcChar2 */
  'n', 0x00,                                        /* wcChar3 */
  'y', 0x00,                                        /* wcChar4 */
  'U', 0x00,                                        /* wcChar5 */
  'S', 0x00,                                        /* wcChar6 */
  'B', 0x00,                                        /* wcChar7 */
};
#define  DAPV1_STRING_DESCRIPTOR2_STR   "TeenyUSB CMSIS-DAP V1"
#define  DAPV1_STRING_DESCRIPTOR2_SIZE   (44)
WEAK __ALIGN_BEGIN  const uint8_t DAPV1_StringDescriptor2 [44] __ALIGN_END = {
  0x2c,                                             /* bLength */
  USB_STRING_DESCRIPTOR_TYPE,                       /* bDescriptorType */
  'T', 0x00,                                        /* wcChar0 */
  'e', 0x00,                                        /* wcChar1 */
  'e', 0x00,                                        /* wcChar2 */
  'n', 0x00,                                        /* wcChar3 */
  'y', 0x00,                                        /* wcChar4 */
  'U', 0x00,                                        /* wcChar5 */
  'S', 0x00,                                        /* wcChar6 */
  'B', 0x00,                                        /* wcChar7 */
  ' ', 0x00,                                        /* wcChar8 */
  'C', 0x00,                                        /* wcChar9 */
  'M', 0x00,                                        /* wcChar10 */
  'S', 0x00,                                        /* wcChar11 */
  'I', 0x00,                                        /* wcChar12 */
  'S', 0x00,                                        /* wcChar13 */
  '-', 0x00,                                        /* wcChar14 */
  'D', 0x00,                                        /* wcChar15 */
  'A', 0x00,                                        /* wcChar16 */
  'P', 0x00,                                        /* wcChar17 */
  ' ', 0x00,                                        /* wcChar18 */
  'V', 0x00,                                        /* wcChar19 */
  '1', 0x00,                                        /* wcChar20 */
};
#define  DAPV1_STRING_DESCRIPTOR3_STR   "TUSB123456FS"
#define  DAPV1_STRING_DESCRIPTOR3_SIZE   (26)
WEAK __ALIGN_BEGIN  const uint8_t DAPV1_StringDescriptor3 [26] __ALIGN_END = {
  0x1a,                                             /* bLength */
  USB_STRING_DESCRIPTOR_TYPE,                       /* bDescriptorType */
  'T', 0x00,                                        /* wcChar0 */
  'U', 0x00,                                        /* wcChar1 */
  'S', 0x00,                                        /* wcChar2 */
  'B', 0x00,                                        /* wcChar3 */
  '1', 0x00,                                        /* wcChar4 */
  '2', 0x00,                                        /* wcChar5 */
  '3', 0x00,                                        /* wcChar6 */
  '4', 0x00,                                        /* wcChar7 */
  '5', 0x00,                                        /* wcChar8 */
  '6', 0x00,                                        /* wcChar9 */
  'F', 0x00,                                        /* wcChar10 */
  'S', 0x00,                                        /* wcChar11 */
};
#define DAPV1_STRING_COUNT    (4)
const uint8_t* const DAPV1_StringDescriptors[4] = {
  DAPV1_StringDescriptor0,
  DAPV1_StringDescriptor1,
  DAPV1_StringDescriptor2,
  DAPV1_StringDescriptor3,
};
#define DAPV1_REPORT_DESCRIPTOR_SIZE_IF0  (33)
WEAK __ALIGN_BEGIN const uint8_t DAPV1_ReportDescriptor_if0[DAPV1_REPORT_DESCRIPTOR_SIZE_IF0] __ALIGN_END = {
// report descriptor for general input/output
  0x06, 0x00, 0xFF,  // Usage Page (Vendor Defined 0xFF00)
  0x09, 0x01,        // Usage (0x01)
  0xA1, 0x01,        // Collection (Application)
  0x09, 0x01,        //   Usage (0x01)
  0x15, 0x00,        //   Logical Minimum (0)
  0x26, 0xFF, 0x00,  //   Logical Maximum (255)
  0x75, 0x08,        //   Report Size (8)
  0x95, 0x40,        //   Report Count 64
  0x81, 0x02,        //   Input (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position)
  0x95, 0x40,        //   Report Count 64
  0x09, 0x01,        //   Usage (0x01)
  0x91, 0x02,        //   Output (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position,Non-volatile)
  0x95, 0x01,        //   Report Count 1
  0x09, 0x01,        //   Usage (0x01)
  0xB1, 0x02,        //   Feature (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position,Non-volatile)
  0xC0               // End Collection
};



DAPV1_TXEP_MAX_SIZE
DAPV1_RXEP_MAX_SIZE
//  Device descriptors
const tusb_descriptors DAPV1_descriptors = {
  .device = DAPV1_DeviceDescriptor,
  .config = DAPV1_ConfigDescriptor,
  .strings = DAPV1_StringDescriptors,
  .string_cnt = DAPV1_STRING_COUNT,
#if defined(HAS_WCID)
#if defined(DAPV1_WCID_DESCRIPTOR_SIZE)
  .wcid_desc = DAPV1_WCIDDescriptor,
#else
  .wcid_desc = 0,
#endif // DAPV1_WCID_DESCRIPTOR_SIZE)

#if defined(DAPV1_WCID_PROPERTIES_SIZE)
  .wcid_properties = DAPV1_WCIDProperties,
#else
  .wcid_properties = 0,
#endif // DAPV1_WCID_PROPERTIES_SIZE

#endif // HAS_WCID

#if defined(HAS_WCID_20)
#if defined(DAPV1_WCID_BOS_SIZE)
  .wcid_bos = DAPV1_WCIDBOS,
#else
  .wcid_bos = 0,  
#endif // DAPV1_WCID_BOS_SIZE)

#if defined(DAPV1_WCID_DESC_SET_SIZE)
  .wcid_desc_set = DAPV1_WCIDDescriptorSet,
#else
  .wcid_desc_set = 0,  
#endif // DAPV1_WCID_DESC_SET_SIZE


#endif // HAS_WCID_20
};
/////////////////////////////////////////
//// Device 11
/////////////////////////////////////////
#include "teeny_usb.h"

#define  DAPV2_DEVICE_DESCRIPTOR_SIZE  (18)
__ALIGN_BEGIN  const uint8_t DAPV2_DeviceDescriptor [18] __ALIGN_END = {
  ///////////////////////////////////////
  /// device descriptor
  ///////////////////////////////////////
  0x12,                                             /* bLength */
  USB_DEVICE_DESCRIPTOR_TYPE,                       /* bDescriptorType */
  0x00, 0x02,                                       /* bcdUSB */
  0x00,                                             /* bDeviceClass */
  0x00,                                             /* bDeviceSubClass */
  0x00,                                             /* bDeviceProtocol */
  0x40,                                             /* bMaxPacketSize */
  0x28, 0x0d,                                       /* idVendor */
  0x04, 0x02,                                       /* idProduct */
  0x00, 0x01,                                       /* bcdDevice */
  0x01,                                             /* iManufacturer */
  0x02,                                             /* iProduct */
  0x03,                                             /* iSerial */
  0x01,                                             /* bNumConfigurations */
};
#define  DAPV2_CONFIG_DESCRIPTOR_SIZE  (32)
__ALIGN_BEGIN  const uint8_t DAPV2_ConfigDescriptor [32] __ALIGN_END = {
  ///////////////////////////////////////
  /// config descriptor
  ///////////////////////////////////////
  0x09,                                             /* bLength */
  USB_CONFIGURATION_DESCRIPTOR_TYPE,                /* bDescriptorType */
  0x20, 0x00,                                       /* wTotalLength */
  0x01,                                             /* bNumInterfaces */
  0x01,                                             /* bConfigurationValue */
  0x00,                                             /* iConfiguration */
  0x80,                                             /* bmAttributes */
  0x64,                                             /* bMaxPower */
  
  ///////////////////////////////////////
  /// interface descriptor
  ///////////////////////////////////////
  0x09,                                             /* bLength */
  USB_INTERFACE_DESCRIPTOR_TYPE,                    /* bDescriptorType */
  0x00,                                             /* bInterfaceNumber */
  0x00,                                             /* bAlternateSetting */
  0x02,                                             /* bNumEndpoints */
  0xff,                                             /* bInterfaceClass */
  0x00,                                             /* bInterfaceSubClass */
  0x00,                                             /* bInterfaceProtocol */
  0x04,                                             /* iInterface */
  
  ///////////////////////////////////////
  /// endpoint descriptor
  ///////////////////////////////////////
  0x07,                                             /* bLength */
  USB_ENDPOINT_DESCRIPTOR_TYPE,                     /* bDescriptorType */
  0x01,                                             /* bEndpointAddress */
  0x02,                                             /* bmAttributes */
  0x00, 0x02,                                       /* wMaxPacketSize */
  0x01,                                             /* bInterval */
  
  ///////////////////////////////////////
  /// endpoint descriptor
  ///////////////////////////////////////
  0x07,                                             /* bLength */
  USB_ENDPOINT_DESCRIPTOR_TYPE,                     /* bDescriptorType */
  0x82,                                             /* bEndpointAddress */
  0x02,                                             /* bmAttributes */
  0x00, 0x02,                                       /* wMaxPacketSize */
  0x01,                                             /* bInterval */
};
#define  DAPV2_STRING_DESCRIPTOR0_STR   "\x09\x04"
#define  DAPV2_STRING_DESCRIPTOR0_SIZE  (4)
WEAK __ALIGN_BEGIN  const uint8_t DAPV2_StringDescriptor0 [4] __ALIGN_END = {
  0x04,                                         /* bLength */
  USB_STRING_DESCRIPTOR_TYPE,                   /* bDescriptorType */
  0x09, 0x04,                                   /* wLangID0 */
};
#define  DAPV2_STRING_DESCRIPTOR1_STR   "TeenyUSB"
#define  DAPV2_STRING_DESCRIPTOR1_SIZE   (18)
WEAK __ALIGN_BEGIN  const uint8_t DAPV2_StringDescriptor1 [18] __ALIGN_END = {
  0x12,                                             /* bLength */
  USB_STRING_DESCRIPTOR_TYPE,                       /* bDescriptorType */
  'T', 0x00,                                        /* wcChar0 */
  'e', 0x00,                                        /* wcChar1 */
  'e', 0x00,                                        /* wcChar2 */
  'n', 0x00,                                        /* wcChar3 */
  'y', 0x00,                                        /* wcChar4 */
  'U', 0x00,                                        /* wcChar5 */
  'S', 0x00,                                        /* wcChar6 */
  'B', 0x00,                                        /* wcChar7 */
};
#define  DAPV2_STRING_DESCRIPTOR2_STR   "TeenyUSB CMSIS-DAP V2"
#define  DAPV2_STRING_DESCRIPTOR2_SIZE   (44)
WEAK __ALIGN_BEGIN  const uint8_t DAPV2_StringDescriptor2 [44] __ALIGN_END = {
  0x2c,                                             /* bLength */
  USB_STRING_DESCRIPTOR_TYPE,                       /* bDescriptorType */
  'T', 0x00,                                        /* wcChar0 */
  'e', 0x00,                                        /* wcChar1 */
  'e', 0x00,                                        /* wcChar2 */
  'n', 0x00,                                        /* wcChar3 */
  'y', 0x00,                                        /* wcChar4 */
  'U', 0x00,                                        /* wcChar5 */
  'S', 0x00,                                        /* wcChar6 */
  'B', 0x00,                                        /* wcChar7 */
  ' ', 0x00,                                        /* wcChar8 */
  'C', 0x00,                                        /* wcChar9 */
  'M', 0x00,                                        /* wcChar10 */
  'S', 0x00,                                        /* wcChar11 */
  'I', 0x00,                                        /* wcChar12 */
  'S', 0x00,                                        /* wcChar13 */
  '-', 0x00,                                        /* wcChar14 */
  'D', 0x00,                                        /* wcChar15 */
  'A', 0x00,                                        /* wcChar16 */
  'P', 0x00,                                        /* wcChar17 */
  ' ', 0x00,                                        /* wcChar18 */
  'V', 0x00,                                        /* wcChar19 */
  '2', 0x00,                                        /* wcChar20 */
};
#define  DAPV2_STRING_DESCRIPTOR3_STR   "TUSB123456HS"
#define  DAPV2_STRING_DESCRIPTOR3_SIZE   (26)
WEAK __ALIGN_BEGIN  const uint8_t DAPV2_StringDescriptor3 [26] __ALIGN_END = {
  0x1a,                                             /* bLength */
  USB_STRING_DESCRIPTOR_TYPE,                       /* bDescriptorType */
  'T', 0x00,                                        /* wcChar0 */
  'U', 0x00,                                        /* wcChar1 */
  'S', 0x00,                                        /* wcChar2 */
  'B', 0x00,                                        /* wcChar3 */
  '1', 0x00,                                        /* wcChar4 */
  '2', 0x00,                                        /* wcChar5 */
  '3', 0x00,                                        /* wcChar6 */
  '4', 0x00,                                        /* wcChar7 */
  '5', 0x00,                                        /* wcChar8 */
  '6', 0x00,                                        /* wcChar9 */
  'H', 0x00,                                        /* wcChar10 */
  'S', 0x00,                                        /* wcChar11 */
};
#define  DAPV2_STRING_DESCRIPTOR4_STR   "CMSIS-DAP v2"
#define  DAPV2_STRING_DESCRIPTOR4_SIZE   (26)
WEAK __ALIGN_BEGIN  const uint8_t DAPV2_StringDescriptor4 [26] __ALIGN_END = {
  0x1a,                                             /* bLength */
  USB_STRING_DESCRIPTOR_TYPE,                       /* bDescriptorType */
  'C', 0x00,                                        /* wcChar0 */
  'M', 0x00,                                        /* wcChar1 */
  'S', 0x00,                                        /* wcChar2 */
  'I', 0x00,                                        /* wcChar3 */
  'S', 0x00,                                        /* wcChar4 */
  '-', 0x00,                                        /* wcChar5 */
  'D', 0x00,                                        /* wcChar6 */
  'A', 0x00,                                        /* wcChar7 */
  'P', 0x00,                                        /* wcChar8 */
  ' ', 0x00,                                        /* wcChar9 */
  'v', 0x00,                                        /* wcChar10 */
  '2', 0x00,                                        /* wcChar11 */
};
#define DAPV2_STRING_COUNT    (5)
const uint8_t* const DAPV2_StringDescriptors[5] = {
  DAPV2_StringDescriptor0,
  DAPV2_StringDescriptor1,
  DAPV2_StringDescriptor2,
  DAPV2_StringDescriptor3,
  DAPV2_StringDescriptor4,
};

//////////////////////////////////////////////////////
///// WCID descripors
//////////////////////////////////////////////////////
#if defined(HAS_WCID)

// Define WCID os string descriptor 
#ifndef WCID_MSOS_STRING
#define WCID_MSOS_STRING
#define WCID_STRING_DESCRIPTOR_MSOS_STR          "MSFT100"
#define WCID_STRING_DESCRIPTOR_MSOS_SIZE          (18)
WEAK __ALIGN_BEGIN const uint8_t  WCID_StringDescriptor_MSOS [18] __ALIGN_END = {
  ///////////////////////////////////////
  /// MS OS string descriptor
  ///////////////////////////////////////
  0x12,                                             /* bLength */
  USB_STRING_DESCRIPTOR_TYPE,                       /* bDescriptorType */
  /* MSFT100 */
  'M', 0x00, 'S', 0x00, 'F', 0x00, 'T', 0x00,       /* wcChar_7 */
  '1', 0x00, '0', 0x00, '0', 0x00,                  /* wcChar_7 */
  WCID_VENDOR_CODE,                                 /* bVendorCode */
  0x00,                                             /* bReserved */
};

#endif // WCID_MSOS_STRING
#define  DAPV2_IF0_WCID_PROPERTIES_SIZE  (142)
WEAK __ALIGN_BEGIN const uint8_t DAPV2_IF0_WCIDProperties [142] __ALIGN_END = {
  ///////////////////////////////////////
  /// WCID property descriptor
  ///////////////////////////////////////
  0x8e, 0x00, 0x00, 0x00,                           /* dwLength */
  0x00, 0x01,                                       /* bcdVersion */
  0x05, 0x00,                                       /* wIndex */
  0x01, 0x00,                                       /* wCount */
  
  ///////////////////////////////////////
  /// registry propter descriptor
  ///////////////////////////////////////
  0x84, 0x00, 0x00, 0x00,                           /* dwSize */
  0x01, 0x00, 0x00, 0x00,                           /* dwPropertyDataType */
  0x28, 0x00,                                       /* wPropertyNameLength */
  /* DeviceInterfaceGUID */
  'D', 0x00, 'e', 0x00, 'v', 0x00, 'i', 0x00,       /* wcName_20 */
  'c', 0x00, 'e', 0x00, 'I', 0x00, 'n', 0x00,       /* wcName_20 */
  't', 0x00, 'e', 0x00, 'r', 0x00, 'f', 0x00,       /* wcName_20 */
  'a', 0x00, 'c', 0x00, 'e', 0x00, 'G', 0x00,       /* wcName_20 */
  'U', 0x00, 'I', 0x00, 'D', 0x00, 0x00, 0x00,      /* wcName_20 */
  0x4e, 0x00, 0x00, 0x00,                           /* dwPropertyDataLength */
  /* {CDB3B5AD-293B-4663-AA36-1AAE46463776} */
  '{', 0x00, 'C', 0x00, 'D', 0x00, 'B', 0x00,       /* wcData_39 */
  '3', 0x00, 'B', 0x00, '5', 0x00, 'A', 0x00,       /* wcData_39 */
  'D', 0x00, '-', 0x00, '2', 0x00, '9', 0x00,       /* wcData_39 */
  '3', 0x00, 'B', 0x00, '-', 0x00, '4', 0x00,       /* wcData_39 */
  '6', 0x00, '6', 0x00, '3', 0x00, '-', 0x00,       /* wcData_39 */
  'A', 0x00, 'A', 0x00, '3', 0x00, '6', 0x00,       /* wcData_39 */
  '-', 0x00, '1', 0x00, 'A', 0x00, 'A', 0x00,       /* wcData_39 */
  'E', 0x00, '4', 0x00, '6', 0x00, '4', 0x00,       /* wcData_39 */
  '6', 0x00, '3', 0x00, '7', 0x00, '7', 0x00,       /* wcData_39 */
  '6', 0x00, '}', 0x00, 0x00, 0x00,                 /* wcData_39 */
};
#define  DAPV2_WCID_DESCRIPTOR_SIZE  (40)
WEAK __ALIGN_BEGIN const uint8_t DAPV2_WCIDDescriptor [40] __ALIGN_END = {
  ///////////////////////////////////////
  /// WCID descriptor
  ///////////////////////////////////////
  0x28, 0x00, 0x00, 0x00,                           /* dwLength */
  0x00, 0x01,                                       /* bcdVersion */
  0x04, 0x00,                                       /* wIndex */
  0x01,                                             /* bCount */
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,         /* bReserved_7 */
  
  ///////////////////////////////////////
  /// WCID function descriptor
  ///////////////////////////////////////
  0x00,                                             /* bFirstInterfaceNumber */
  0x01,                                             /* bReserved */
  /* WINUSB */
  'W', 'I', 'N', 'U', 'S', 'B', 0x00, 0x00,         /* cCID_8 */
  /*  */
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,   /* cSubCID_8 */
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00,               /* bReserved_6 */
};
#define DAPV2_WCID_PROPERTIES_SIZE (1)
WEAK __ALIGN_BEGIN const desc_t DAPV2_WCIDProperties[ DAPV2_WCID_PROPERTIES_SIZE ] __ALIGN_END = {
  DAPV2_IF0_WCIDProperties,
};
#endif    // #if defined(HAS_WCID)


DAPV2_TXEP_MAX_SIZE
DAPV2_RXEP_MAX_SIZE
//  Device descriptors
const tusb_descriptors DAPV2_descriptors = {
  .device = DAPV2_DeviceDescriptor,
  .config = DAPV2_ConfigDescriptor,
  .strings = DAPV2_StringDescriptors,
  .string_cnt = DAPV2_STRING_COUNT,
#if defined(HAS_WCID)
#if defined(DAPV2_WCID_DESCRIPTOR_SIZE)
  .wcid_desc = DAPV2_WCIDDescriptor,
#else
  .wcid_desc = 0,
#endif // DAPV2_WCID_DESCRIPTOR_SIZE)

#if defined(DAPV2_WCID_PROPERTIES_SIZE)
  .wcid_properties = DAPV2_WCIDProperties,
#else
  .wcid_properties = 0,
#endif // DAPV2_WCID_PROPERTIES_SIZE

#endif // HAS_WCID

#if defined(HAS_WCID_20)
#if defined(DAPV2_WCID_BOS_SIZE)
  .wcid_bos = DAPV2_WCIDBOS,
#else
  .wcid_bos = 0,  
#endif // DAPV2_WCID_BOS_SIZE)

#if defined(DAPV2_WCID_DESC_SET_SIZE)
  .wcid_desc_set = DAPV2_WCIDDescriptorSet,
#else
  .wcid_desc_set = 0,  
#endif // DAPV2_WCID_DESC_SET_SIZE


#endif // HAS_WCID_20
};
/////////////////////////////////////////
//// Device 12
/////////////////////////////////////////
#include "teeny_usb.h"

#define  MULCFG_DEVICE_DESCRIPTOR_SIZE  (18)
__ALIGN_BEGIN  const uint8_t MULCFG_DeviceDescriptor [18] __ALIGN_END = {
  ///////////////////////////////////////
  /// device descriptor
  ///////////////////////////////////////
  0x12,                                             /* bLength */
  USB_DEVICE_DESCRIPTOR_TYPE,                       /* bDescriptorType */
  0x00, 0x02,                                       /* bcdUSB */
  0xef,                                             /* bDeviceClass */
  0x02,                                             /* bDeviceSubClass */
  0x01,                                             /* bDeviceProtocol */
  0x40,                                             /* bMaxPacketSize */
  0x83, 0x04,                                       /* idVendor */
  0x11, 0x00,                                       /* idProduct */
  0x00, 0x01,                                       /* bcdDevice */
  0x01,                                             /* iManufacturer */
  0x02,                                             /* iProduct */
  0x03,                                             /* iSerial */
  0x02,                                             /* bNumConfigurations */
};
#define  MULCFG_CONFIG0_DESCRIPTOR_SIZE  (153)
__ALIGN_BEGIN  const uint8_t MULCFG_ConfigDescriptor0 [153] __ALIGN_END = {
  ///////////////////////////////////////
  /// config descriptor
  ///////////////////////////////////////
  0x09,                                             /* bLength */
  USB_CONFIGURATION_DESCRIPTOR_TYPE,                /* bDescriptorType */
  0x99, 0x00,                                       /* wTotalLength */
  0x05,                                             /* bNumInterfaces */
  0x01,                                             /* bConfigurationValue */
  0x00,                                             /* iConfiguration */
  0x80,                                             /* bmAttributes */
  0x64,                                             /* bMaxPower */
  
  ///////////////////////////////////////
  /// interface descriptor
  ///////////////////////////////////////
  0x09,                                             /* bLength */
  USB_INTERFACE_DESCRIPTOR_TYPE,                    /* bDescriptorType */
  0x00,                                             /* bInterfaceNumber */
  0x00,                                             /* bAlternateSetting */
  0x02,                                             /* bNumEndpoints */
  0x03,                                             /* bInterfaceClass */
  0x00,                                             /* bInterfaceSubClass */
  0x00,                                             /* bInterfaceProtocol */
  0x00,                                             /* iInterface */
  
  ///////////////////////////////////////
  /// hid descriptor
  ///////////////////////////////////////
  0x09,                                             /* bLength */
  0x21,                                             /* bDescriptorType */
  0x11, 0x01,                                       /* bcdHID */
  0x00,                                             /* bCountryCode */
  0x01,                                             /* bNumDescriptors */
  0x22,                                             /* bDescriptorType1 */
  0x18, 0x00,                                       /* wDescriptorLength1 */
  
  ///////////////////////////////////////
  /// endpoint descriptor
  ///////////////////////////////////////
  0x07,                                             /* bLength */
  USB_ENDPOINT_DESCRIPTOR_TYPE,                     /* bDescriptorType */
  0x82,                                             /* bEndpointAddress */
  0x03,                                             /* bmAttributes */
  0x10, 0x00,                                       /* wMaxPacketSize */
  0x01,                                             /* bInterval */
  
  ///////////////////////////////////////
  /// endpoint descriptor
  ///////////////////////////////////////
  0x07,                                             /* bLength */
  USB_ENDPOINT_DESCRIPTOR_TYPE,                     /* bDescriptorType */
  0x02,                                             /* bEndpointAddress */
  0x03,                                             /* bmAttributes */
  0x10, 0x00,                                       /* wMaxPacketSize */
  0x01,                                             /* bInterval */
  
  ///////////////////////////////////////
  /// interface association descriptor
  ///////////////////////////////////////
  0x08,                                             /* bLength */
  USB_IAD_DESCRIPTOR_TYPE,                          /* bDescriptorType */
  0x01,                                             /* bFirstInterface */
  0x02,                                             /* bInterfaceCount */
  0x02,                                             /* bFunctionClass */
  0x02,                                             /* bFunctionSubClass */
  0x01,                                             /* bFunctionProtocol */
  0x00,                                             /* iFunction */
  
  ///////////////////////////////////////
  /// interface descriptor
  ///////////////////////////////////////
  0x09,                                             /* bLength */
  USB_INTERFACE_DESCRIPTOR_TYPE,                    /* bDescriptorType */
  0x01,                                             /* bInterfaceNumber */
  0x00,                                             /* bAlternateSetting */
  0x01,                                             /* bNumEndpoints */
  0x02,                                             /* bInterfaceClass */
  0x02,                                             /* bInterfaceSubClass */
  0x01,                                             /* bInterfaceProtocol */
  0x00,                                             /* iInterface */
  
  ///////////////////////////////////////
  /// cdc acm header descriptor
  ///////////////////////////////////////
  0x05,                                             /* bLength */
  0x24,                                             /* bDescriptorType */
  0x00,                                             /* bDescriptorSubtype */
  0x10, 0x01,                                       /* bcdCDC */
  
  ///////////////////////////////////////
  /// cdc acm call management descriptor
  ///////////////////////////////////////
  0x05,                                             /* bLength */
  0x24,                                             /* bDescriptorType */
  0x01,                                             /* bDescriptorSubtype */
  0x00,                                             /* bmCapabilities */
  0x01,                                             /* bDataInterface */
  
  ///////////////////////////////////////
  /// cdc acm descriptor
  ///////////////////////////////////////
  0x04,                                             /* bLength */
  0x24,                                             /* bDescriptorType */
  0x02,                                             /* bDescriptorSubtype */
  0x02,                                             /* bmCapabilities */
  
  ///////////////////////////////////////
  /// cdc acm union descriptor
  ///////////////////////////////////////
  0x05,                                             /* bLength */
  0x24,                                             /* bDescriptorType */
  0x06,                                             /* bDescriptorSubtype */
  0x00,                                             /* bMasterInterface */
  0x01,                                             /* bSlaveInterface0 */
  
  ///////////////////////////////////////
  /// endpoint descriptor
  ///////////////////////////////////////
  0x07,                                             /* bLength */
  USB_ENDPOINT_DESCRIPTOR_TYPE,                     /* bDescriptorType */
  0x88,                                             /* bEndpointAddress */
  0x03,                                             /* bmAttributes */
  0x10, 0x00,                                       /* wMaxPacketSize */
  0x01,                                             /* bInterval */
  
  ///////////////////////////////////////
  /// interface descriptor
  ///////////////////////////////////////
  0x09,                                             /* bLength */
  USB_INTERFACE_DESCRIPTOR_TYPE,                    /* bDescriptorType */
  0x02,                                             /* bInterfaceNumber */
  0x00,                                             /* bAlternateSetting */
  0x02,                                             /* bNumEndpoints */
  0x0a,                                             /* bInterfaceClass */
  0x00,                                             /* bInterfaceSubClass */
  0x00,                                             /* bInterfaceProtocol */
  0x00,                                             /* iInterface */
  
  ///////////////////////////////////////
  /// endpoint descriptor
  ///////////////////////////////////////
  0x07,                                             /* bLength */
  USB_ENDPOINT_DESCRIPTOR_TYPE,                     /* bDescriptorType */
  0x81,                                             /* bEndpointAddress */
  0x02,                                             /* bmAttributes */
  0x20, 0x00,                                       /* wMaxPacketSize */
  0x01,                                             /* bInterval */
  
  ///////////////////////////////////////
  /// endpoint descriptor
  ///////////////////////////////////////
  0x07,                                             /* bLength */
  USB_ENDPOINT_DESCRIPTOR_TYPE,                     /* bDescriptorType */
  0x01,                                             /* bEndpointAddress */
  0x02,                                             /* bmAttributes */
  0x20, 0x00,                                       /* wMaxPacketSize */
  0x01,                                             /* bInterval */
  
  ///////////////////////////////////////
  /// interface descriptor
  ///////////////////////////////////////
  0x09,                                             /* bLength */
  USB_INTERFACE_DESCRIPTOR_TYPE,                    /* bDescriptorType */
  0x03,                                             /* bInterfaceNumber */
  0x00,                                             /* bAlternateSetting */
  0x02,                                             /* bNumEndpoints */
  0xff,                                             /* bInterfaceClass */
  0xff,                                             /* bInterfaceSubClass */
  0x00,                                             /* bInterfaceProtocol */
  0x04,                                             /* iInterface */
  
  ///////////////////////////////////////
  /// endpoint descriptor
  ///////////////////////////////////////
  0x07,                                             /* bLength */
  USB_ENDPOINT_DESCRIPTOR_TYPE,                     /* bDescriptorType */
  0x83,                                             /* bEndpointAddress */
  0x02,                                             /* bmAttributes */
  0x20, 0x00,                                       /* wMaxPacketSize */
  0x01,                                             /* bInterval */
  
  ///////////////////////////////////////
  /// endpoint descriptor
  ///////////////////////////////////////
  0x07,                                             /* bLength */
  USB_ENDPOINT_DESCRIPTOR_TYPE,                     /* bDescriptorType */
  0x03,                                             /* bEndpointAddress */
  0x02,                                             /* bmAttributes */
  0x20, 0x00,                                       /* wMaxPacketSize */
  0x01,                                             /* bInterval */
  
  ///////////////////////////////////////
  /// interface descriptor
  ///////////////////////////////////////
  0x09,                                             /* bLength */
  USB_INTERFACE_DESCRIPTOR_TYPE,                    /* bDescriptorType */
  0x04,                                             /* bInterfaceNumber */
  0x00,                                             /* bAlternateSetting */
  0x02,                                             /* bNumEndpoints */
  0x08,                                             /* bInterfaceClass */
  0x06,                                             /* bInterfaceSubClass */
  0x50,                                             /* bInterfaceProtocol */
  0x00,                                             /* iInterface */
  
  ///////////////////////////////////////
  /// endpoint descriptor
  ///////////////////////////////////////
  0x07,                                             /* bLength */
  USB_ENDPOINT_DESCRIPTOR_TYPE,                     /* bDescriptorType */
  0x84,                                             /* bEndpointAddress */
  0x02,                                             /* bmAttributes */
  0x40, 0x00,                                       /* wMaxPacketSize */
  0x01,                                             /* bInterval */
  
  ///////////////////////////////////////
  /// endpoint descriptor
  ///////////////////////////////////////
  0x07,                                             /* bLength */
  USB_ENDPOINT_DESCRIPTOR_TYPE,                     /* bDescriptorType */
  0x04,                                             /* bEndpointAddress */
  0x02,                                             /* bmAttributes */
  0x40, 0x00,                                       /* wMaxPacketSize */
  0x01,                                             /* bInterval */
};
#define  MULCFG_CONFIG1_DESCRIPTOR_SIZE  (87)
__ALIGN_BEGIN  const uint8_t MULCFG_ConfigDescriptor1 [87] __ALIGN_END = {
  ///////////////////////////////////////
  /// config descriptor
  ///////////////////////////////////////
  0x09,                                             /* bLength */
  USB_CONFIGURATION_DESCRIPTOR_TYPE,                /* bDescriptorType */
  0x57, 0x00,                                       /* wTotalLength */
  0x03,                                             /* bNumInterfaces */
  0x02,                                             /* bConfigurationValue */
  0x00,                                             /* iConfiguration */
  0x80,                                             /* bmAttributes */
  0x64,                                             /* bMaxPower */
  
  ///////////////////////////////////////
  /// interface descriptor
  ///////////////////////////////////////
  0x09,                                             /* bLength */
  USB_INTERFACE_DESCRIPTOR_TYPE,                    /* bDescriptorType */
  0x00,                                             /* bInterfaceNumber */
  0x00,                                             /* bAlternateSetting */
  0x02,                                             /* bNumEndpoints */
  0xff,                                             /* bInterfaceClass */
  0xff,                                             /* bInterfaceSubClass */
  0x00,                                             /* bInterfaceProtocol */
  0x00,                                             /* iInterface */
  
  ///////////////////////////////////////
  /// endpoint descriptor
  ///////////////////////////////////////
  0x07,                                             /* bLength */
  USB_ENDPOINT_DESCRIPTOR_TYPE,                     /* bDescriptorType */
  0x81,                                             /* bEndpointAddress */
  0x02,                                             /* bmAttributes */
  0x20, 0x00,                                       /* wMaxPacketSize */
  0x01,                                             /* bInterval */
  
  ///////////////////////////////////////
  /// endpoint descriptor
  ///////////////////////////////////////
  0x07,                                             /* bLength */
  USB_ENDPOINT_DESCRIPTOR_TYPE,                     /* bDescriptorType */
  0x01,                                             /* bEndpointAddress */
  0x02,                                             /* bmAttributes */
  0x20, 0x00,                                       /* wMaxPacketSize */
  0x01,                                             /* bInterval */
  
  ///////////////////////////////////////
  /// interface descriptor
  ///////////////////////////////////////
  0x09,                                             /* bLength */
  USB_INTERFACE_DESCRIPTOR_TYPE,                    /* bDescriptorType */
  0x01,                                             /* bInterfaceNumber */
  0x00,                                             /* bAlternateSetting */
  0x02,                                             /* bNumEndpoints */
  0x08,                                             /* bInterfaceClass */
  0x06,                                             /* bInterfaceSubClass */
  0x50,                                             /* bInterfaceProtocol */
  0x00,                                             /* iInterface */
  
  ///////////////////////////////////////
  /// endpoint descriptor
  ///////////////////////////////////////
  0x07,                                             /* bLength */
  USB_ENDPOINT_DESCRIPTOR_TYPE,                     /* bDescriptorType */
  0x82,                                             /* bEndpointAddress */
  0x02,                                             /* bmAttributes */
  0x40, 0x00,                                       /* wMaxPacketSize */
  0x01,                                             /* bInterval */
  
  ///////////////////////////////////////
  /// endpoint descriptor
  ///////////////////////////////////////
  0x07,                                             /* bLength */
  USB_ENDPOINT_DESCRIPTOR_TYPE,                     /* bDescriptorType */
  0x02,                                             /* bEndpointAddress */
  0x02,                                             /* bmAttributes */
  0x40, 0x00,                                       /* wMaxPacketSize */
  0x01,                                             /* bInterval */
  
  ///////////////////////////////////////
  /// interface descriptor
  ///////////////////////////////////////
  0x09,                                             /* bLength */
  USB_INTERFACE_DESCRIPTOR_TYPE,                    /* bDescriptorType */
  0x02,                                             /* bInterfaceNumber */
  0x00,                                             /* bAlternateSetting */
  0x02,                                             /* bNumEndpoints */
  0x03,                                             /* bInterfaceClass */
  0x00,                                             /* bInterfaceSubClass */
  0x00,                                             /* bInterfaceProtocol */
  0x00,                                             /* iInterface */
  
  ///////////////////////////////////////
  /// hid descriptor
  ///////////////////////////////////////
  0x09,                                             /* bLength */
  0x21,                                             /* bDescriptorType */
  0x11, 0x01,                                       /* bcdHID */
  0x00,                                             /* bCountryCode */
  0x01,                                             /* bNumDescriptors */
  0x22,                                             /* bDescriptorType1 */
  0x18, 0x00,                                       /* wDescriptorLength1 */
  
  ///////////////////////////////////////
  /// endpoint descriptor
  ///////////////////////////////////////
  0x07,                                             /* bLength */
  USB_ENDPOINT_DESCRIPTOR_TYPE,                     /* bDescriptorType */
  0x83,                                             /* bEndpointAddress */
  0x03,                                             /* bmAttributes */
  0x10, 0x00,                                       /* wMaxPacketSize */
  0x01,                                             /* bInterval */
  
  ///////////////////////////////////////
  /// endpoint descriptor
  ///////////////////////////////////////
  0x07,                                             /* bLength */
  USB_ENDPOINT_DESCRIPTOR_TYPE,                     /* bDescriptorType */
  0x03,                                             /* bEndpointAddress */
  0x03,                                             /* bmAttributes */
  0x10, 0x00,                                       /* wMaxPacketSize */
  0x01,                                             /* bInterval */
};
#define  MULCFG_STRING_DESCRIPTOR0_STR   "\x09\x04"
#define  MULCFG_STRING_DESCRIPTOR0_SIZE  (4)
WEAK __ALIGN_BEGIN  const uint8_t MULCFG_StringDescriptor0 [4] __ALIGN_END = {
  0x04,                                         /* bLength */
  USB_STRING_DESCRIPTOR_TYPE,                   /* bDescriptorType */
  0x09, 0x04,                                   /* wLangID0 */
};
#define  MULCFG_STRING_DESCRIPTOR1_STR   "TeenyDT"
#define  MULCFG_STRING_DESCRIPTOR1_SIZE   (16)
WEAK __ALIGN_BEGIN  const uint8_t MULCFG_StringDescriptor1 [16] __ALIGN_END = {
  0x10,                                             /* bLength */
  USB_STRING_DESCRIPTOR_TYPE,                       /* bDescriptorType */
  'T', 0x00,                                        /* wcChar0 */
  'e', 0x00,                                        /* wcChar1 */
  'e', 0x00,                                        /* wcChar2 */
  'n', 0x00,                                        /* wcChar3 */
  'y', 0x00,                                        /* wcChar4 */
  'D', 0x00,                                        /* wcChar5 */
  'T', 0x00,                                        /* wcChar6 */
};
#define  MULCFG_STRING_DESCRIPTOR2_STR   "TeenyDT Multi Config DEMO"
#define  MULCFG_STRING_DESCRIPTOR2_SIZE   (52)
WEAK __ALIGN_BEGIN  const uint8_t MULCFG_StringDescriptor2 [52] __ALIGN_END = {
  0x34,                                             /* bLength */
  USB_STRING_DESCRIPTOR_TYPE,                       /* bDescriptorType */
  'T', 0x00,                                        /* wcChar0 */
  'e', 0x00,                                        /* wcChar1 */
  'e', 0x00,                                        /* wcChar2 */
  'n', 0x00,                                        /* wcChar3 */
  'y', 0x00,                                        /* wcChar4 */
  'D', 0x00,                                        /* wcChar5 */
  'T', 0x00,                                        /* wcChar6 */
  ' ', 0x00,                                        /* wcChar7 */
  'M', 0x00,                                        /* wcChar8 */
  'u', 0x00,                                        /* wcChar9 */
  'l', 0x00,                                        /* wcChar10 */
  't', 0x00,                                        /* wcChar11 */
  'i', 0x00,                                        /* wcChar12 */
  ' ', 0x00,                                        /* wcChar13 */
  'C', 0x00,                                        /* wcChar14 */
  'o', 0x00,                                        /* wcChar15 */
  'n', 0x00,                                        /* wcChar16 */
  'f', 0x00,                                        /* wcChar17 */
  'i', 0x00,                                        /* wcChar18 */
  'g', 0x00,                                        /* wcChar19 */
  ' ', 0x00,                                        /* wcChar20 */
  'D', 0x00,                                        /* wcChar21 */
  'E', 0x00,                                        /* wcChar22 */
  'M', 0x00,                                        /* wcChar23 */
  'O', 0x00,                                        /* wcChar24 */
};
#define  MULCFG_STRING_DESCRIPTOR3_STR   "TUSB123456"
#define  MULCFG_STRING_DESCRIPTOR3_SIZE   (22)
WEAK __ALIGN_BEGIN  const uint8_t MULCFG_StringDescriptor3 [22] __ALIGN_END = {
  0x16,                                             /* bLength */
  USB_STRING_DESCRIPTOR_TYPE,                       /* bDescriptorType */
  'T', 0x00,                                        /* wcChar0 */
  'U', 0x00,                                        /* wcChar1 */
  'S', 0x00,                                        /* wcChar2 */
  'B', 0x00,                                        /* wcChar3 */
  '1', 0x00,                                        /* wcChar4 */
  '2', 0x00,                                        /* wcChar5 */
  '3', 0x00,                                        /* wcChar6 */
  '4', 0x00,                                        /* wcChar7 */
  '5', 0x00,                                        /* wcChar8 */
  '6', 0x00,                                        /* wcChar9 */
};
#define  MULCFG_STRING_DESCRIPTOR4_STR   "TeenyUSB WinUSB"
#define  MULCFG_STRING_DESCRIPTOR4_SIZE   (32)
WEAK __ALIGN_BEGIN  const uint8_t MULCFG_StringDescriptor4 [32] __ALIGN_END = {
  0x20,                                             /* bLength */
  USB_STRING_DESCRIPTOR_TYPE,                       /* bDescriptorType */
  'T', 0x00,                                        /* wcChar0 */
  'e', 0x00,                                        /* wcChar1 */
  'e', 0x00,                                        /* wcChar2 */
  'n', 0x00,                                        /* wcChar3 */
  'y', 0x00,                                        /* wcChar4 */
  'U', 0x00,                                        /* wcChar5 */
  'S', 0x00,                                        /* wcChar6 */
  'B', 0x00,                                        /* wcChar7 */
  ' ', 0x00,                                        /* wcChar8 */
  'W', 0x00,                                        /* wcChar9 */
  'i', 0x00,                                        /* wcChar10 */
  'n', 0x00,                                        /* wcChar11 */
  'U', 0x00,                                        /* wcChar12 */
  'S', 0x00,                                        /* wcChar13 */
  'B', 0x00,                                        /* wcChar14 */
};
#define MULCFG_STRING_COUNT    (5)
const uint8_t* const MULCFG_StringDescriptors[5] = {
  MULCFG_StringDescriptor0,
  MULCFG_StringDescriptor1,
  MULCFG_StringDescriptor2,
  MULCFG_StringDescriptor3,
  MULCFG_StringDescriptor4,
};
#define MULCFG_REPORT_DESCRIPTOR_SIZE_IF0  (24)
WEAK __ALIGN_BEGIN const uint8_t MULCFG_ReportDescriptor_if0[MULCFG_REPORT_DESCRIPTOR_SIZE_IF0] __ALIGN_END = {
        // report descriptor for general input/output
        0x06, 0x00, 0xFF,  // Usage Page (Vendor Defined 0xFF00)
        0x09, 0x01,        // Usage (0x01)
        0xA1, 0x01,        // Collection (Application)
        0x09, 0x02,        //   Usage (0x02)
        0x15, 0x00,        //   Logical Minimum (0)
        0x25, 0xFF,        //   Logical Maximum (255)
        0x75, 0x08,        //   Report Size (8)
        0x95, 0x10,        //   Report Count (16)
        0x81, 0x02,        //   Input (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position)
        0x09, 0x03,        //   Usage (0x03)
        0x91, 0x02,        //   Output (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position,Non-volatile)
        0xC0               // End Collection
    };


//////////////////////////////////////////////////////
///// WCID descripors
//////////////////////////////////////////////////////
#if defined(HAS_WCID)

// Define WCID os string descriptor 
#ifndef WCID_MSOS_STRING
#define WCID_MSOS_STRING
#define WCID_STRING_DESCRIPTOR_MSOS_STR          "MSFT100"
#define WCID_STRING_DESCRIPTOR_MSOS_SIZE          (18)
WEAK __ALIGN_BEGIN const uint8_t  WCID_StringDescriptor_MSOS [18] __ALIGN_END = {
  ///////////////////////////////////////
  /// MS OS string descriptor
  ///////////////////////////////////////
  0x12,                                             /* bLength */
  USB_STRING_DESCRIPTOR_TYPE,                       /* bDescriptorType */
  /* MSFT100 */
  'M', 0x00, 'S', 0x00, 'F', 0x00, 'T', 0x00,       /* wcChar_7 */
  '1', 0x00, '0', 0x00, '0', 0x00,                  /* wcChar_7 */
  WCID_VENDOR_CODE,                                 /* bVendorCode */
  0x00,                                             /* bReserved */
};

#endif // WCID_MSOS_STRING
#define  MULCFG_IF0_WCID_PROPERTIES_SIZE  (142)
WEAK __ALIGN_BEGIN const uint8_t MULCFG_IF0_WCIDProperties [142] __ALIGN_END = {
  ///////////////////////////////////////
  /// WCID property descriptor
  ///////////////////////////////////////
  0x8e, 0x00, 0x00, 0x00,                           /* dwLength */
  0x00, 0x01,                                       /* bcdVersion */
  0x05, 0x00,                                       /* wIndex */
  0x01, 0x00,                                       /* wCount */
  
  ///////////////////////////////////////
  /// registry propter descriptor
  ///////////////////////////////////////
  0x84, 0x00, 0x00, 0x00,                           /* dwSize */
  0x01, 0x00, 0x00, 0x00,                           /* dwPropertyDataType */
  0x28, 0x00,                                       /* wPropertyNameLength */
  /* DeviceInterfaceGUID */
  'D', 0x00, 'e', 0x00, 'v', 0x00, 'i', 0x00,       /* wcName_20 */
  'c', 0x00, 'e', 0x00, 'I', 0x00, 'n', 0x00,       /* wcName_20 */
  't', 0x00, 'e', 0x00, 'r', 0x00, 'f', 0x00,       /* wcName_20 */
  'a', 0x00, 'c', 0x00, 'e', 0x00, 'G', 0x00,       /* wcName_20 */
  'U', 0x00, 'I', 0x00, 'D', 0x00, 0x00, 0x00,      /* wcName_20 */
  0x4e, 0x00, 0x00, 0x00,                           /* dwPropertyDataLength */
  /* {1D4B2365-4749-48EA-B38A-7C6FDDDD7E26} */
  '{', 0x00, '1', 0x00, 'D', 0x00, '4', 0x00,       /* wcData_39 */
  'B', 0x00, '2', 0x00, '3', 0x00, '6', 0x00,       /* wcData_39 */
  '5', 0x00, '-', 0x00, '4', 0x00, '7', 0x00,       /* wcData_39 */
  '4', 0x00, '9', 0x00, '-', 0x00, '4', 0x00,       /* wcData_39 */
  '8', 0x00, 'E', 0x00, 'A', 0x00, '-', 0x00,       /* wcData_39 */
  'B', 0x00, '3', 0x00, '8', 0x00, 'A', 0x00,       /* wcData_39 */
  '-', 0x00, '7', 0x00, 'C', 0x00, '6', 0x00,       /* wcData_39 */
  'F', 0x00, 'D', 0x00, 'D', 0x00, 'D', 0x00,       /* wcData_39 */
  'D', 0x00, '7', 0x00, 'E', 0x00, '2', 0x00,       /* wcData_39 */
  '6', 0x00, '}', 0x00, 0x00, 0x00,                 /* wcData_39 */
};
#define  MULCFG_IF3_WCID_PROPERTIES_SIZE  (142)
WEAK __ALIGN_BEGIN const uint8_t MULCFG_IF3_WCIDProperties [142] __ALIGN_END = {
  ///////////////////////////////////////
  /// WCID property descriptor
  ///////////////////////////////////////
  0x8e, 0x00, 0x00, 0x00,                           /* dwLength */
  0x00, 0x01,                                       /* bcdVersion */
  0x05, 0x00,                                       /* wIndex */
  0x01, 0x00,                                       /* wCount */
  
  ///////////////////////////////////////
  /// registry propter descriptor
  ///////////////////////////////////////
  0x84, 0x00, 0x00, 0x00,                           /* dwSize */
  0x01, 0x00, 0x00, 0x00,                           /* dwPropertyDataType */
  0x28, 0x00,                                       /* wPropertyNameLength */
  /* DeviceInterfaceGUID */
  'D', 0x00, 'e', 0x00, 'v', 0x00, 'i', 0x00,       /* wcName_20 */
  'c', 0x00, 'e', 0x00, 'I', 0x00, 'n', 0x00,       /* wcName_20 */
  't', 0x00, 'e', 0x00, 'r', 0x00, 'f', 0x00,       /* wcName_20 */
  'a', 0x00, 'c', 0x00, 'e', 0x00, 'G', 0x00,       /* wcName_20 */
  'U', 0x00, 'I', 0x00, 'D', 0x00, 0x00, 0x00,      /* wcName_20 */
  0x4e, 0x00, 0x00, 0x00,                           /* dwPropertyDataLength */
  /* {1D4B2365-4749-48EA-B38A-7C6FDDDD7E26} */
  '{', 0x00, '1', 0x00, 'D', 0x00, '4', 0x00,       /* wcData_39 */
  'B', 0x00, '2', 0x00, '3', 0x00, '6', 0x00,       /* wcData_39 */
  '5', 0x00, '-', 0x00, '4', 0x00, '7', 0x00,       /* wcData_39 */
  '4', 0x00, '9', 0x00, '-', 0x00, '4', 0x00,       /* wcData_39 */
  '8', 0x00, 'E', 0x00, 'A', 0x00, '-', 0x00,       /* wcData_39 */
  'B', 0x00, '3', 0x00, '8', 0x00, 'A', 0x00,       /* wcData_39 */
  '-', 0x00, '7', 0x00, 'C', 0x00, '6', 0x00,       /* wcData_39 */
  'F', 0x00, 'D', 0x00, 'D', 0x00, 'D', 0x00,       /* wcData_39 */
  'D', 0x00, '7', 0x00, 'E', 0x00, '2', 0x00,       /* wcData_39 */
  '6', 0x00, '}', 0x00, 0x00, 0x00,                 /* wcData_39 */
};
#define  MULCFG_WCID_DESCRIPTOR_SIZE  (64)
WEAK __ALIGN_BEGIN const uint8_t MULCFG_WCIDDescriptor [64] __ALIGN_END = {
  ///////////////////////////////////////
  /// WCID descriptor
  ///////////////////////////////////////
  0x40, 0x00, 0x00, 0x00,                           /* dwLength */
  0x00, 0x01,                                       /* bcdVersion */
  0x04, 0x00,                                       /* wIndex */
  0x02,                                             /* bCount */
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,         /* bReserved_7 */
  
  ///////////////////////////////////////
  /// WCID function descriptor
  ///////////////////////////////////////
  0x00,                                             /* bFirstInterfaceNumber */
  0x01,                                             /* bReserved */
  /* WINUSB */
  'W', 'I', 'N', 'U', 'S', 'B', 0x00, 0x00,         /* cCID_8 */
  /*  */
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,   /* cSubCID_8 */
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00,               /* bReserved_6 */
  
  ///////////////////////////////////////
  /// WCID function descriptor
  ///////////////////////////////////////
  0x03,                                             /* bFirstInterfaceNumber */
  0x01,                                             /* bReserved */
  /* WINUSB */
  'W', 'I', 'N', 'U', 'S', 'B', 0x00, 0x00,         /* cCID_8 */
  /*  */
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,   /* cSubCID_8 */
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00,               /* bReserved_6 */
};
#define MULCFG_WCID_PROPERTIES_SIZE (5)
WEAK __ALIGN_BEGIN const desc_t MULCFG_WCIDProperties[ MULCFG_WCID_PROPERTIES_SIZE ] __ALIGN_END = {
  MULCFG_IF0_WCIDProperties,
  0,    // No WCID in Interface 1
  0,    // No WCID in Interface 2
  MULCFG_IF3_WCIDProperties,
  0,    // No WCID in Interface 4
};
#endif    // #if defined(HAS_WCID)
#define MULCFG_REPORT_DESCRIPTOR_SIZE_IF2  (24)
WEAK __ALIGN_BEGIN const uint8_t MULCFG_ReportDescriptor_if2[MULCFG_REPORT_DESCRIPTOR_SIZE_IF2] __ALIGN_END = {
        // report descriptor for general input/output
        0x06, 0x00, 0xFF,  // Usage Page (Vendor Defined 0xFF00)
        0x09, 0x01,        // Usage (0x01)
        0xA1, 0x01,        // Collection (Application)
        0x09, 0x02,        //   Usage (0x02)
        0x15, 0x00,        //   Logical Minimum (0)
        0x25, 0xFF,        //   Logical Maximum (255)
        0x75, 0x08,        //   Report Size (8)
        0x95, 0x10,        //   Report Count (16)
        0x81, 0x02,        //   Input (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position)
        0x09, 0x03,        //   Usage (0x03)
        0x91, 0x02,        //   Output (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position,Non-volatile)
        0xC0               // End Collection
    };



MULCFG_TXEP_MAX_SIZE
MULCFG_RXEP_MAX_SIZE
//  Device descriptors
const tusb_descriptors MULCFG_descriptors = {
  .device = MULCFG_DeviceDescriptor,
  .config = MULCFG_ConfigDescriptor,
  .strings = MULCFG_StringDescriptors,
  .string_cnt = MULCFG_STRING_COUNT,
#if defined(HAS_WCID)
#if defined(MULCFG_WCID_DESCRIPTOR_SIZE)
  .wcid_desc = MULCFG_WCIDDescriptor,
#else
  .wcid_desc = 0,
#endif // MULCFG_WCID_DESCRIPTOR_SIZE)

#if defined(MULCFG_WCID_PROPERTIES_SIZE)
  .wcid_properties = MULCFG_WCIDProperties,
#else
  .wcid_properties = 0,
#endif // MULCFG_WCID_PROPERTIES_SIZE

#endif // HAS_WCID

#if defined(HAS_WCID_20)
#if defined(MULCFG_WCID_BOS_SIZE)
  .wcid_bos = MULCFG_WCIDBOS,
#else
  .wcid_bos = 0,  
#endif // MULCFG_WCID_BOS_SIZE)

#if defined(MULCFG_WCID_DESC_SET_SIZE)
  .wcid_desc_set = MULCFG_WCIDDescriptorSet,
#else
  .wcid_desc_set = 0,  
#endif // MULCFG_WCID_DESC_SET_SIZE


#endif // HAS_WCID_20
};
/////////////////////////////////////////
//// Device 13
/////////////////////////////////////////
#include "teeny_usb.h"

#define  DEVICE_DESCRIPTOR_SIZE  (18)
__ALIGN_BEGIN  const uint8_t DeviceDescriptor [18] __ALIGN_END = {
  ///////////////////////////////////////
  /// device descriptor
  ///////////////////////////////////////
  0x12,                                             /* bLength */
  USB_DEVICE_DESCRIPTOR_TYPE,                       /* bDescriptorType */
  0x00, 0x02,                                       /* bcdUSB */
  0x00,                                             /* bDeviceClass */
  0x00,                                             /* bDeviceSubClass */
  0x00,                                             /* bDeviceProtocol */
  0x40,                                             /* bMaxPacketSize */
  0x17, 0x20,                                       /* idVendor */
  0x24, 0x09,                                       /* idProduct */
  0x00, 0x01,                                       /* bcdDevice */
  0x00,                                             /* iManufacturer */
  0x00,                                             /* iProduct */
  0x00,                                             /* iSerial */
  0x01,                                             /* bNumConfigurations */
};
#define  CONFIG_DESCRIPTOR_SIZE  (18)
__ALIGN_BEGIN  const uint8_t ConfigDescriptor [18] __ALIGN_END = {
  ///////////////////////////////////////
  /// config descriptor
  ///////////////////////////////////////
  0x09,                                             /* bLength */
  USB_CONFIGURATION_DESCRIPTOR_TYPE,                /* bDescriptorType */
  0x12, 0x00,                                       /* wTotalLength */
  0x01,                                             /* bNumInterfaces */
  0x01,                                             /* bConfigurationValue */
  0x00,                                             /* iConfiguration */
  0x80,                                             /* bmAttributes */
  0x64,                                             /* bMaxPower */
  
  ///////////////////////////////////////
  /// interface descriptor
  ///////////////////////////////////////
  0x09,                                             /* bLength */
  USB_INTERFACE_DESCRIPTOR_TYPE,                    /* bDescriptorType */
  0x00,                                             /* bInterfaceNumber */
  0x00,                                             /* bAlternateSetting */
  0x00,                                             /* bNumEndpoints */
  0xff,                                             /* bInterfaceClass */
  0xff,                                             /* bInterfaceSubClass */
  0x00,                                             /* bInterfaceProtocol */
  0x00,                                             /* iInterface */
};
#define  STRING_DESCRIPTOR0_STR   "\x09\x04"
#define  STRING_DESCRIPTOR0_SIZE  (4)
WEAK __ALIGN_BEGIN  const uint8_t StringDescriptor0 [4] __ALIGN_END = {
  0x04,                                         /* bLength */
  USB_STRING_DESCRIPTOR_TYPE,                   /* bDescriptorType */
  0x09, 0x04,                                   /* wLangID0 */
};
#define STRING_COUNT    (1)
const uint8_t* const StringDescriptors[1] = {
  StringDescriptor0,
};


TXEP_MAX_SIZE
RXEP_MAX_SIZE
//  Device descriptors
const tusb_descriptors descriptors = {
  .device = DeviceDescriptor,
  .config = ConfigDescriptor,
  .strings = StringDescriptors,
  .string_cnt = STRING_COUNT,
#if defined(HAS_WCID)
#if defined(WCID_DESCRIPTOR_SIZE)
  .wcid_desc = WCIDDescriptor,
#else
  .wcid_desc = 0,
#endif // WCID_DESCRIPTOR_SIZE)

#if defined(WCID_PROPERTIES_SIZE)
  .wcid_properties = WCIDProperties,
#else
  .wcid_properties = 0,
#endif // WCID_PROPERTIES_SIZE

#endif // HAS_WCID

#if defined(HAS_WCID_20)
#if defined(WCID_BOS_SIZE)
  .wcid_bos = WCIDBOS,
#else
  .wcid_bos = 0,  
#endif // WCID_BOS_SIZE)

#if defined(WCID_DESC_SET_SIZE)
  .wcid_desc_set = WCIDDescriptorSet,
#else
  .wcid_desc_set = 0,  
#endif // WCID_DESC_SET_SIZE


#endif // HAS_WCID_20
};
