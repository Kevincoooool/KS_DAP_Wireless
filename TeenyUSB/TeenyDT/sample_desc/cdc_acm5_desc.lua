return Device {
    strManufacturer = "TeenyUSB",
    strProduct = "TeenyUSB CDC5 DEMO",
    strSerial = "TUSB123456",
    idVendor = 0x0483,
    idProduct = 0x0011,
    prefix = "CDC_ACM5",
    Config {
        CDC_ACM{
            EndPoint(IN(8),  Interrupt, 16),
            EndPoint(IN(1), BulkDouble, 32),
            EndPoint(OUT(1),  BulkDouble, 32),
        },
        CDC_ACM{
            EndPoint(IN(9),  Interrupt, 16),
            EndPoint(IN(2), BulkDouble, 32),
            EndPoint(OUT(2),  BulkDouble, 32),
        },
        CDC_ACM{
            EndPoint(IN(10),  Interrupt, 16),
            EndPoint(IN(3), BulkDouble, 32),
            EndPoint(OUT(3),  BulkDouble, 32),
        },
        CDC_ACM{
            EndPoint(IN(11),  Interrupt, 16),
            EndPoint(IN(4), BulkDouble, 32),
            EndPoint(OUT(4),  BulkDouble, 32),
        },
        CDC_ACM{
            EndPoint(IN(12),  Interrupt, 16),
            EndPoint(IN(5), BulkDouble, 32),
            EndPoint(OUT(5),  BulkDouble, 32),
        },
   }
}