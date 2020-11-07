/*
 * Name   :  teeny_usb_desc.h
 * Author :  admin@xtoolbox.org
 * Date   :  2020-11-07 21:01:06

 * Desc   :  This file is auto generate by the TeenyDT
 *           Visit http://dt.tusb.org for more info
 */

/*
  Input source name:  composite_desc.lua
  
  Content type is lua script:
  ------------- lua script begin ------------
--[[
Descripttion : 
version      : 
Author       : Kevincoooool
Date         : 2020-10-31 11:38:04
LastEditors  : Kevincoooool
LastEditTime : 2020-11-07 21:01:04
FilePath     : \TeenyUSB\sample\composite_h7\composite_desc.lua
--]]
return Device {
    strManufacturer = "TeenyUSB",
    strProduct = "TeenyUSB CMSIS-DAP DEMO",
    strSerial = "TUSB123456",
    idVendor = 0x0483,
    idProduct = 0x0011,
    prefix = "COMP",
    Config {
        USB_HID{
            ReadEp = EndPoint(IN(2),  Interrupt, 64),
            WriteEp = EndPoint(OUT(2), Interrupt, 64),
            report = HID_InOut(64),
        },
        CDC_ACM{
            EndPoint(IN(5),  Interrupt, 16),
            EndPoint(IN(3), BulkDouble, 32),
            EndPoint(OUT(3),  BulkDouble, 32),
		},
        Interface{
			strInterface = "CMSIS-DAP v2",
            -- DAP link GUID
			extDesc=WinUSB("{CDB3B5AD-293B-4663-AA36-1AAE46463776}"),
			bInterfaceClass = 0xff,
            bInterfaceSubClass = 0xff,
            EndPoint(IN(1),  BulkDouble, 64),
            EndPoint(OUT(1), BulkDouble, 64),
        },
        Interface{
            bInterfaceClass = 0x08,        -- MSC
            bInterfaceSubClass = 0x06,     -- SCSI
            bInterfaceProtocol = 0x50,     -- BOT
            EndPoint(IN(4),  BulkDouble, 64),
            EndPoint(OUT(4), BulkDouble, 64),
        },
   }
}

  ------------- lua script end   ------------
 */
#ifndef __COMP_TEENY_USB_DESC_H__
#define __COMP_TEENY_USB_DESC_H__

#include "teeny_usb_device.h"
extern const tusb_descriptors_t COMP_descriptors;
#endif

