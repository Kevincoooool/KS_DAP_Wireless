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
