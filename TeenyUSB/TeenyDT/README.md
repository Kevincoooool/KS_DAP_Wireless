TeenyDT
=============
使用lua开发的USB描述符生成工具。生成的描述符可以用在[TeenyUSB](https://github.com/xtoolbox/TeenyUSB)协议栈和[libopencm3](https://github.com/libopencm3/libopencm3)的USB协议栈，在线试用[线路1](http://dt.tusb.org)，[线路2](http://dt1.tusb.org)。

lua based USB descriptor generator for TeenyUSB and LibOpenCM3, Try it online, [Site1](http://dt.tusb.org), [Site2](http://dt1.tusb.org).

需要[lua5.3](https://sourceforge.net/projects/luabinaries/files/5.3.4/)，require [lua5.3](https://sourceforge.net/projects/luabinaries/files/5.3.4/)

老版本带UI和驱动生成的TeenyDT在[这里](https://github.com/xtoolbox/archive_TeenyUSB/tree/master/TeenyDT)，Old TeenyDT with GUI and driver generator is moved to [here](https://github.com/xtoolbox/archive_TeenyUSB/tree/master/TeenyDT).

## 生成描述符
```shell
lua gen_descriptor.lua <lua_desc_path> [-maxep=7] [-maxmem=512] [-mode=opencm3]
   <lua_desc_path>       path of the lua format descriptor
   -maxep                max endpoint number
   -maxmem               USB memory size
   -mode                 descriptor format, default TeenyUSB, can be set to opencm3
```

### 参数说明

| Paramter      | Description        |
|---------------|------------------------------------------------------------|
|lua_desc_path  |lua格式的USB描述符路径，生成的描述也在此路径下。|
|-maxep         |指定最大的端点号，超出此端点号的端点在生成时会被忽略。 |
|-maxmem        |指定USB的内存，当需要的内存超此值时，会报错。 |
|-mode          |指定生成的描述符格式,默认为TeenyUSB格式。设置为opencm3时生成libopencm3格式的描述符。 |

## lua格式描述符/ lua format descriptor

```lua
return Device {
    strManufacturer = "TeenyUSB",
    strProduct = "TeenyUSB Composite DEMO",
    strSerial = "TUSB123456",
    idVendor = 0x0483,
    idProduct = 0x0011,
    prefix = "COMP",
    Config {
        USB_HID{
            -- Set the Endpoint in a simple way
            ReadEp = EndPoint(IN(2),  Interrupt, 16),
            -- Set the Endpoint in a complex way
            WriteEp = EndPoint{
                bEndpointAddress = OUT(2),
                bmAttributes = Interrupt, -- valid attrs: Interrupt/Bulk/BulkDouble/ISO/Control
                wMaxPacketSize = 16,
                bInterval = 1,
            },
            report = HID_InOut(16),
        },
        -- set the CDC ACM in a simple way
        CDC_ACM{
            EndPoint(IN(8),  Interrupt, 16),
            EndPoint(IN(1), BulkDouble, 32),
            EndPoint(OUT(1),  BulkDouble, 32),
        },
        Interface{
            WCID=WinUSB,
            strInterface = "TeenyUSB WinUSB",
            GUID="{1D4B2365-4749-48EA-B38A-7C6FDDDD7E26}",
            -- Double buffer will disabled, because the IN/OUT use same Ep
            EndPoint(IN(3),  BulkDouble, 32),
            EndPoint(OUT(3), BulkDouble, 32),
        },
        Interface{
            bInterfaceClass = 0x08,        -- MSC
            bInterfaceSubClass = 0x06,     -- SCSI
            bInterfaceProtocol = 0x50,     -- BOT
            -- Double buffer will enabled
            EndPoint(IN(4),  BulkDouble, 64),
            EndPoint(OUT(5), BulkDouble, 64),
        },
   }
}
```

## STM32 USB参数表   Table for STM32 USB Core

| Device Type      | Max Ep No. |  USB Memory  |
|------------------|------------|--------------|
|STM32F0xx_FS      |   7  |  1024   |
|STM32F10x_FS      |   7  |  512    |
|STM32F10x_OTG_FS  |   3  |  1280   |
|STM32F2xx_OTG_FS  |   3  |  1280   |
|STM32F2xx_OTG_HS  |   5  |  4096   |
|STM32F303_BC_FS   |   7  |  512    |
|STM32F373x_FS     |   7  |  512    |
|STM32F303_DE_FS   |   7  |  1024   |
|STM32F4xx_OTG_FS  |   3  |  1280   |
|STM32F4xx_OTG_HS  |   5  |  4096   |
|STM32F7xx_OTG_FS  |   5  |  1280   |
|STM32F7xx_OTG_HS  |   8  |  4096   |
|STM32H7xx_OTG_FS  |   8  |  1280   |
|STM32H7xx_OTG_HS  |   8  |  4096   |





