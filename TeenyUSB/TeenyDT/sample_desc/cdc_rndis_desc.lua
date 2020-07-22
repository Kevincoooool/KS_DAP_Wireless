return Device {
    strManufacturer = "TeenyUSB",
    strProduct = "TeenyUSB RNDIS DEMO",
    strSerial = "TUSB123456",
    idVendor = 0x0483,
    idProduct = 0x0011,
    prefix = "CDC_RNDIS",
    Config {
        CDC_ACM{
                bInterfaceProtocol = 0xff,
                extDesc = RNDIS("5162001"),
                EndPoint(IN(3),  Interrupt, 16),
                EndPoint(IN(1), BulkDouble, 64),
                EndPoint(OUT(1),  BulkDouble, 64),
        },
   }
}