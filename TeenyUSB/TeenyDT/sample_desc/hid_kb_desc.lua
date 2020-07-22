return Device {
    strManufacturer = "TeenyUSB",
    strProduct = "TeenyUSB Boot Keyboard DEMO",
    strSerial = "TUSB123456",
    idVendor = 0x0483,
    idProduct = 0x0011,
    prefix = "KB",
    Config {
        USB_HID{
            isBoot = true, -- same as bInterfaceSubClass = 1
            isKey = true,  -- same as bInterfaceProtocol = 1
            report = HID_BootKeyBoard(),
            EndPoint(IN(1),  Interrupt, 8),
            EndPoint(OUT(1), Interrupt, 8),
       }
   }
}