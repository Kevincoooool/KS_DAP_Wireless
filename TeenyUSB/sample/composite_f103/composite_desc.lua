
return Device {
    strManufacturer = "TeenyUSB",
    strProduct = "TeenyUSB CMSIS-DAP DEMO",
    strSerial = "TUSB123456",
    idVendor = 0x0483,
    idProduct = 0x0011,
    prefix = "COMP",
    Config {
        USB_HID{
            ReadEp = EndPoint(IN(2),  Interrupt, 16),
            WriteEp = EndPoint(OUT(2), Interrupt, 16),
            report = HID_InOut(16),
        },
        CDC_ACM{
            EndPoint(IN(5),  Interrupt, 16),
            EndPoint(IN(1), BulkDouble, 32),
            EndPoint(OUT(1),  BulkDouble, 32),
        },
        Interface{
			strInterface = "CMSIS-DAP v2",
            -- DAP link GUID
            extDesc=WinUSB("{CDB3B5AD-293B-4663-AA36-1AAE46463776}"),
            -- bInterfaceClass = 0xff,
            -- bInterfaceSubClass = 0x00,
            -- Unknown issue, On Win10
            -- if bcdUSB is 0x210, and High speed port used
            -- the max packet size must not small than 512, 
            -- DO NOT change the Endpoint sequence, PyOCD will check it
            EndPoint(OUT(3),  Bulk, 64),
            EndPoint(IN(3), Bulk, 64),
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