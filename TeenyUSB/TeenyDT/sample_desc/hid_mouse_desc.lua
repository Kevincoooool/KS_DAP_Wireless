return Device {
    strManufacturer = "TeenyUSB",
    strProduct = "TeenyUSB Boot Mouse DEMO",
    strSerial = "TUSB123456",
    idVendor = 0x0483,
    idProduct = 0x0011,
    prefix = "MOUSE",
    Config {
        USB_HID{
            isBoot = true,   -- same as bInterfaceSubClass = 1
            isMouse = true,  -- same as bInterfaceProtocol = 2
            extDesc = HID_BootMouse(), -- same as report = xxx
            EndPoint(IN(1),  Interrupt, 8),
            EndPoint(OUT(1), Interrupt, 8),
       }
   }
}