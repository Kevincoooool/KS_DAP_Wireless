/*
 * Name   :  opencm3_usb_init.h
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
#ifndef __OPENCM3_USB_INIT_H__
#define __OPENCM3_USB_INIT_H__

#include <libopencm3/usb/usbd.h>

typedef void (*ep_cb_t)(usbd_device *usbd_dev, uint8_t ep);


/**
 * 
*/
usbd_device *DEMO_usb_init(
        const usbd_driver *driver,
        ep_cb_t ep_in_cb,
        ep_cb_t ep_out_cb);

#ifndef opencm3_usb_init
#define opencm3_usb_init DEMO_usb_init
#endif

// Extra define
// Enable WCID related code
#define  HAS_WCID

#ifndef WCID_VENDOR_CODE
#define  WCID_VENDOR_CODE       0x17
extern const uint8_t WCID_StringDescriptor_MSOS[];
#endif


#endif
