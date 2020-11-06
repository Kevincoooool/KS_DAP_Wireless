--[[
Descripttion : 
version      : 
Author       : Kevincoooool
Date         : 2020-10-31 11:38:04
LastEditors  : Kevincoooool
LastEditTime : 2020-11-05 21:44:18
FilePath     : \TeenyUSB\sample\custom_bulkf103\custom_bulk_desc.lua
--]]
return Device {
    strManufacturer = "KSDIY",
    strProduct = "KSDIY CMSIS-DAP Bulk",
    strSerial = "TUSB123456",
    idVendor = 0x0483,
    idProduct = 0x0001,
    prefix = "COMP",
    Config {
        Interface{
            WCID=WinUSB,
            GUID="{1D4B2365-4749-48EA-B38A-7C6FDDDD7E26}",
            EndPoint(IN(1),  BulkDouble, 64),
            EndPoint(OUT(2), BulkDouble, 64),
		},
		CDC_ACM{
            EndPoint(IN(5),  Interrupt, 16),
            EndPoint(IN(3), BulkDouble, 32),
            EndPoint(OUT(3),  BulkDouble, 32),
		},
		Interface{
            bInterfaceClass = 0x08,        -- MSC
            bInterfaceSubClass = 0x06,     -- SCSI
            bInterfaceProtocol = 0x50,     -- BOT
            EndPoint(IN(4),  BulkDouble, 64),
            EndPoint(OUT(4), BulkDouble, 64),
        },
   },
}