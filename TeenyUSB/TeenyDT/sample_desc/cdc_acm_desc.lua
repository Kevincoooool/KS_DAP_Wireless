return Device {
    strManufacturer = "TeenyUSB",
    strProduct = "TeenyUSB CDC DEMO",
    strSerial = "TUSB123456",
    idVendor = 0x0483,
    idProduct = 0x0011,
    prefix = "CDC_ACM",
    Config {
        -- here expand the CDC_ACM to a IAD with 2 interfaces
        IAD{
            Interface{
                bInterfaceClass = 2,
                bInterfaceSubClass = 2,
                bInterfaceProtocol = 1,
                Function{   bDescriptorSubtype = 0,
                    name = "cdc acm header descriptor",
                    varData = {
                        {bcdCDC = 0x110},
                    }
                },
                Function{   bDescriptorSubtype = 1,
                    name = "cdc acm call management descriptor",
                    varData = {
                        {bmCapabilities = 0x00},
                        {bDataInterface = 0x01},
                    }
                },
                Function{   bDescriptorSubtype = 2,
                    name = "cdc acm descriptor",
                    varData = {
                        {bmCapabilities = 0x02},
                    }
                },
                Function{   bDescriptorSubtype = 6,
                    name = "cdc acm union descriptor",
                    varData = {
                        {bMasterInterface = 0x00},
                        {bSlaveInterface0 = 0x01},
                    }
                },
                EndPoint(IN(8),  Interrupt, 16),
            },
            Interface{
                bInterfaceClass = 0x0a,
                bInterfaceSubClass = 0,
                bInterfaceProtocol = 0,
                -- EndPoint(IN(1), BulkDouble, 32),
                EndPoint{ -- expand the ep attributes
                    bEndpointAddress = 0x81, -- same as IN(1)
                    bmAttributes = BulkDouble,
                    wMaxPacketSize = 32,
                    bInterval = 1
                },
                EndPoint(OUT(1),  BulkDouble, 32),
            },
        }
   }
}