return Device {
    strManufacturer = "TeenyUSB",
    strProduct = "TeenyUSB CMSIS-DAP V2",
    strSerial = "TUSB123456HS",
    idVendor = 0x0d28,
    idProduct = 0x0204,
    bcdUSB = 0x200,
    prefix = "DAPV2",
    Config {
        Interface{
            strInterface = "CMSIS-DAP v2",
            -- DAP link GUID
            extDesc=WinUSB("{CDB3B5AD-293B-4663-AA36-1AAE46463776}"),
            bInterfaceClass = 0xff,
            bInterfaceSubClass = 0x00,
            -- Unknown issue, On Win10
            -- if bcdUSB is 0x210, and High speed port used
            -- the max packet size must not small than 512, 
            -- DO NOT change the Endpoint sequence, PyOCD will check it
            EndPoint(OUT(1),  Bulk, 512),
            EndPoint(IN(2), Bulk, 512),
        },
   }
}