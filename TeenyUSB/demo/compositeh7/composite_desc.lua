--[[
Descripttion : 
version      : 
Author       : Kevincoooool
Date         : 2020-10-31 15:03:32
LastEditors  : Kevincoooool
LastEditTime : 2020-11-05 20:55:23
FilePath     : \TeenyUSB\demo\compositeh7\composite_desc.lua
--]]
return Device {
    strManufacturer = "KSDIY",
    strProduct = "KSDIY CMSIS-DAP DEMO",
    strSerial = "996-996-996",
    idVendor = 0x0483,
    idProduct = 0x0011,
    prefix = "COMP",
    Config {
        USB_HID{
            ReadEp = EndPoint(IN(2),  Interrupt, 16),
            WriteEp = EndPoint(OUT(2), Interrupt, 16),
            report = HID_InOut(64),
        },
        CDC_ACM{
            EndPoint(IN(8),  Interrupt, 16),
            EndPoint(IN(1), BulkDouble, 32),
            EndPoint(OUT(1),  BulkDouble, 32),
        },
        Interface{
            WCID=WinUSB,
            strInterface = "CMSIS-DAP WinUSB",
            GUID="{1D4B2365-4749-48EA-B38A-7C6FDDDD7E26}",
            EndPoint(IN(3),  BulkDouble, 64),
            EndPoint(OUT(3), BulkDouble, 64),
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