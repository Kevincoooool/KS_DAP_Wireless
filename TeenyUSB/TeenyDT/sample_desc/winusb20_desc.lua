return Device {
    strManufacturer = "TeenyUSB",
    strProduct = "TeenyUSB WinUSB DEMO",
    strSerial = "TUSB123456",
    idVendor = 0x0483,
    idProduct = 0x0011,
    bcdUSB = 0x210, -- Set to 0x210 to use the MS2.0 WCID
    prefix = "WINUSB20",
    Config {
        Interface{
            WCID=WinUSB,
            strInterface = "TeenyUSB WinUSB 0",
            GUID="{1D4B2365-4749-48EA-B38A-7C6FDDDD7E26}",
            EndPoint(IN(1),  BulkDouble, 32),
            EndPoint(OUT(1), BulkDouble, 32),
        },
        Interface{
            -- another way to set the WinUSB interface GUID
            extDesc = WinUSB("{1D4B2365-4749-48EA-B38A-7C6FDDDD7E26}"),
            strInterface = "TeenyUSB WinUSB 1",
            EndPoint(IN(2),  BulkDouble, 32),
            EndPoint(OUT(2), BulkDouble, 32),
        },
        Interface{
            extDesc = WinUSB("{1D4B2365-4749-48EA-B38A-7C6FDDDD7E26}"),
            strInterface = "TeenyUSB WinUSB 1",
            EndPoint(IN(3),  BulkDouble, 32),
            EndPoint(OUT(3), BulkDouble, 32),
        },
   }
}