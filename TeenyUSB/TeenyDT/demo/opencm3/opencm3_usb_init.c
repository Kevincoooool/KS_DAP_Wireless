/*
 * Name   :  opencm3_usb_init.c
 * Author :  admin@xtoolbox.org
 * Date   :  2019-10-27 16:53:46

 * Desc   :  This file is auto generate by the TeenyDT
 *           Visit https://github.com/xtoolbox/TeenyDT for more info
 */

/*
  Input source name:  demo_desc.lua
  
  Content type is lua script:
  ------------- lua script begin ------------
return Device {
    strManufacturer = "TeenyDT",
    strProduct = "TeenyDT OpenCM3 DEMO",
    strSerial = "TUSB123456",
    idVendor = 0x0483,
    idProduct = 0x1001,
    bcdUSB = 0x200, -- set the bcdUSB to 0x210 to use the MS 2.0 style
    prefix = "DEMO",
    Config {
        Interface{
            WCID=WinUSB,
            strInterface = "TeenyUSB WinUSB",
            GUID="{1D4B2365-4749-48EA-B38A-7C6FDDDD7E26}",
            EndPoint(IN(1),  BulkDouble, 64),
            EndPoint(OUT(1), BulkDouble, 64),
        },
   }
}


  ------------- lua script end   ------------
 */
#include "opencm3_usb_init.h"
#include "trace.h"
#include "string.h"

#ifndef NULL
#define NULL 0
#endif

#ifndef WEAK
#define WEAK
#endif

#ifndef __ALIGN_BEGIN
#define __ALIGN_BEGIN
#endif

#ifndef __ALIGN_END
#define __ALIGN_END
#endif

#define ER_DEBUG
#ifdef ER_DEBUG
#include <stdio.h>
#define ER_DPRINTF(fmt, ...) \
	do { printf(fmt, ## __VA_ARGS__); } while (0)
#else
#define ER_DPRINTF(fmt, ...) \
	do { } while (0)
#endif

struct usb_endpoint_init{
    uint8_t addr;
    uint8_t type;
    uint16_t size;
    void (*cb)(usbd_device *, uint8_t);
};

typedef const uint8_t* desc_t;

static const struct usb_device_descriptor DEMO_dev_desc = {
    .bLength = 0x12,
    .bDescriptorType = USB_DT_DEVICE,
    .bcdUSB = 0x0200,
    .bDeviceClass = 0x00,
    .bDeviceSubClass = 0x00,
    .bDeviceProtocol = 0x00,
    .bMaxPacketSize0 = 0x40,
    .idVendor = 0x0483,
    .idProduct = 0x1001,
    .bcdDevice = 0x0100,
    .iManufacturer = 0x01,
    .iProduct = 0x02,
    .iSerialNumber = 0x03,
    .bNumConfigurations = 0x01,
};
static const struct usb_endpoint_descriptor DEMO_config1_itf0_endpoints[] = {
  {
    .bLength = 0x07,
    .bDescriptorType = USB_DT_ENDPOINT,
    .bEndpointAddress = 0x81,
    .bmAttributes = 0x02,
    .wMaxPacketSize = 0x0040,
    .bInterval = 0x01,
  },
  {
    .bLength = 0x07,
    .bDescriptorType = USB_DT_ENDPOINT,
    .bEndpointAddress = 0x01,
    .bmAttributes = 0x02,
    .wMaxPacketSize = 0x0040,
    .bInterval = 0x01,
  },

};

static const struct usb_interface_descriptor DEMO_config1_itf0 = {
    .bLength = 0x09,
    .bDescriptorType = USB_DT_INTERFACE,
    .bInterfaceNumber = 0x00,
    .bAlternateSetting = 0x00,
    .bNumEndpoints = 0x02,
    .bInterfaceClass = 0xff,
    .bInterfaceSubClass = 0xff,
    .bInterfaceProtocol = 0x00,
    .iInterface = 0x04,

    .endpoint = DEMO_config1_itf0_endpoints,
    .extra = NULL,
    .extralen = 0,
};
static const struct usb_interface DEMO_config1_interfaces[] = {
  {
    .num_altsetting = 1,
    .altsetting = &DEMO_config1_itf0,
  },
};
#define DEMO_config1_ep_count        (2)
static const struct usb_endpoint_init DEMO_config1_ep_init[2] = {
    { .addr = 0x81, .type = USB_ENDPOINT_ATTR_BULK, .size = 64, .cb = NULL },
    { .addr = 0x01, .type = USB_ENDPOINT_ATTR_BULK, .size = 64, .cb = NULL },
};
static const struct usb_config_descriptor DEMO_config[] = {
  {
    .bLength = 0x09,
    .bDescriptorType = USB_DT_CONFIGURATION,
    .wTotalLength = 0x0020,
    .bNumInterfaces = 0x01,
    .bConfigurationValue = 0x01,
    .iConfiguration = 0x00,
    .bmAttributes = 0x80,
    .bMaxPower = 0x64,

    .interface = DEMO_config1_interfaces,
  },
};
/////////////////////////////////////////////
// String descriptors
/////////////////////////////////////////////

static const char * DEMO_usb_strings[] = {
    "TeenyDT",
    "TeenyDT OpenCM3 DEMO",
    "TUSB123456",
    "TeenyUSB WinUSB"
};

/////////////////////////////////////////////
// Extra descriptors
/////////////////////////////////////////////
#if defined(HAS_WCID_20)
#define HIBYTE(v)    ( (uint8_t)((v)>>8))
#define LOBYTE(v)    ( (uint8_t)((v)&0xff))
#define USB_DESC_TYPE_BOS    0x0f
#endif


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
  USB_DT_STRING,                       /* bDescriptorType */
  /* MSFT100 */
  'M', 0x00, 'S', 0x00, 'F', 0x00, 'T', 0x00,       /* wcChar_7 */
  '1', 0x00, '0', 0x00, '0', 0x00,                  /* wcChar_7 */
  WCID_VENDOR_CODE,                                 /* bVendorCode */
  0x00,                                             /* bReserved */
};

#endif // WCID_MSOS_STRING
#define  DEMO_IF0_WCID_PROPERTIES_SIZE  (142)
WEAK __ALIGN_BEGIN const uint8_t DEMO_IF0_WCIDProperties [142] __ALIGN_END = {
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
#define  DEMO_WCID_DESCRIPTOR_SIZE  (40)
WEAK __ALIGN_BEGIN const uint8_t DEMO_WCIDDescriptor [40] __ALIGN_END = {
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
#define DEMO_WCID_PROPERTIES_SIZE (1)
WEAK __ALIGN_BEGIN const desc_t DEMO_WCIDProperties[ DEMO_WCID_PROPERTIES_SIZE ] __ALIGN_END = {
  DEMO_IF0_WCIDProperties,
};
#endif    // #if defined(HAS_WCID)


/////////////////////////////////////////////
// USB init code
/////////////////////////////////////////////

const struct {
    int len;
    const struct usb_endpoint_init* ep_inits;
}DEMO_ep_init_map[] = {
  {
    .len = DEMO_config1_ep_count,
    .ep_inits = DEMO_config1_ep_init,
  },
};

#define ARR_SIZE(x)   (sizeof(x)/sizeof((x)[0]))

static ep_cb_t DEMO_ep_in_handler;
static ep_cb_t DEMO_ep_out_handler;

static enum usbd_request_return_codes DEMO_WCID_control_request(usbd_device *usbd_dev,
	struct usb_setup_data *req,
	uint8_t **buf,
	uint16_t *len,
    usbd_control_complete_callback *complete);

static void DEMO_set_config(usbd_device *usbd_dev, uint16_t wValue)
{
    ER_DPRINTF("set cfg %d\n", wValue);
    if(wValue && wValue <= ARR_SIZE(DEMO_ep_init_map) ){
        int len = DEMO_ep_init_map[wValue-1].len;
        const struct usb_endpoint_init* ep_inits = DEMO_ep_init_map[wValue-1].ep_inits;
        for(int i=0;i<len;i++){
            usbd_ep_setup(usbd_dev, ep_inits[i].addr, ep_inits[i].type, ep_inits[i].size,
                ep_inits[i].cb ? ep_inits[i].cb : ( 
                ep_inits[i].addr & 0x80 ? DEMO_ep_in_handler : DEMO_ep_out_handler ) );
        }
    }else{
        ER_DPRINTF("set configuration unknown: %d\n", wValue);
    }
}

#ifndef USB_DT_BOS
#define USB_DT_BOS  0x0f
#endif

#if defined(HAS_WCID) || defined(HAS_WCID_20)

static int usb_descriptor_type(uint16_t wValue)
{
	return wValue >> 8;
}

#if defined(HAS_WCID)
static int usb_descriptor_index(uint16_t wValue)
{
	return wValue & 0xFF;
}
#endif

#endif

#ifndef MIN
#define MIN(a,b)   ((a)<(b)?(a):(b))
#endif

static enum usbd_request_return_codes DEMO_WCID_control_request(usbd_device *usbd_dev,
	struct usb_setup_data *req,
	uint8_t **buf,
	uint16_t *len,
    usbd_control_complete_callback *complete)
{
    (void) usbd_dev;
    (void) complete;
#if defined(HAS_WCID)
    if(req->bRequest == USB_REQ_GET_DESCRIPTOR 
    && usb_descriptor_type(req->wValue) == USB_DT_STRING
    && usb_descriptor_index(req->wValue) == 0xee){
        #if defined(WCID_STRING_DESCRIPTOR_MSOS_SIZE)
        *len = MIN(*len, WCID_STRING_DESCRIPTOR_MSOS_SIZE);
        memcpy(*buf, WCID_StringDescriptor_MSOS, *len);
        return USBD_REQ_HANDLED;
        #endif
    }else if( (req->bmRequestType & USB_REQ_TYPE_TYPE) == USB_REQ_TYPE_VENDOR
    &&   req->bRequest == WCID_VENDOR_CODE ){
        if(req->wIndex == 4){
            #if defined(DEMO_WCID_DESCRIPTOR_SIZE)
            *len = MIN(*len, DEMO_WCID_DESCRIPTOR_SIZE);
            memcpy(*buf, DEMO_WCIDDescriptor, *len);
            return USBD_REQ_HANDLED;
            #endif
        }
        #if defined(DEMO_WCID_PROPERTIES_SIZE)
        else if(req->wIndex == 5 && req->wValue < DEMO_WCID_PROPERTIES_SIZE ){
            desc_t desc = DEMO_WCIDProperties[req->wValue];
            if(desc){
                uint16_t tlen = desc[0] + (desc[1]<<8) + (desc[2]<<16) + (desc[3]<<24);
                *len = MIN(*len, tlen);
                memcpy(*buf, desc, *len);
                return USBD_REQ_HANDLED;
            }
        }
        #endif
    }
#endif

#if defined(HAS_WCID_20)
    if(req->bRequest == USB_REQ_GET_DESCRIPTOR 
    && usb_descriptor_type(req->wValue) == USB_DT_BOS){
        #if defined( DEMO_WCID_BOS_SIZE )
        *len = MIN(*len, DEMO_WCID_BOS_SIZE);
        memcpy(*buf, DEMO_WCIDBOS, *len);
        return USBD_REQ_HANDLED;
        #endif
    }else if((req->bmRequestType & USB_REQ_TYPE_TYPE) == USB_REQ_TYPE_VENDOR
    &&   req->bRequest == WCID_VENDOR_CODE
    &&   req->wIndex == 7 ){
        #if defined( DEMO_WCID_DESC_SET_SIZE )
        *len = MIN(*len, DEMO_WCID_DESC_SET_SIZE);
        memcpy(*buf, DEMO_WCIDDescriptorSet, *len);
        return USBD_REQ_HANDLED;
        #endif
    }
#endif
    return USBD_REQ_NEXT_CALLBACK;
}


static uint8_t DEMO_control_buffer[1024];
usbd_device * DEMO_usb_init(const usbd_driver *driver, 
    ep_cb_t ep_in_cb,
    ep_cb_t ep_out_cb)
{
    usbd_device *dev = usbd_init(driver, &DEMO_dev_desc, DEMO_config,
    DEMO_usb_strings, ARR_SIZE(DEMO_usb_strings),
    DEMO_control_buffer, sizeof(DEMO_control_buffer));

    DEMO_ep_in_handler = ep_in_cb;
    DEMO_ep_out_handler = ep_out_cb;

    // TODO
    // WCID_control_request may register after set configuration
    // But the WCID feature in Windows will request something before set configuration
    // So register the control request for WCID here, after set configuartion it will be clear
    usbd_register_control_callback(
            dev,
            0,
            0,
            DEMO_WCID_control_request);

    usbd_register_set_config_callback(dev, DEMO_set_config);
    return dev;
}

