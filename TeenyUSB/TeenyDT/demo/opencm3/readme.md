WinUSB DEMO for LibOpenCM3
==============
基于libopencm3的WinUSB DEMO。在Win8.1及以后的系统中，即插即用，不需要驱动和inf文件。此DEMO将IN端点收到的数据+1后再通过OUT端点发回电脑。

USB描述符和初始化代码通过TeenyDT自动生成。

Simple echo back DEMO for WinUSB

For OS later than Win8.1, there is no driver and no inf file required.

There descriptor and libopencm3 usb init code is generate by TeenyDT.

## 如何生成工程 How to Make

make OPENCM3_DIR=" your libopencm3 path "

在命令行中将 OPENCM3_DIR 设置为你电脑上libopencm3库所在的路径。

编译前确保libopencm3正确编译并生成的对应的库文件。比如stm32f3 disco开发板需要libopencm3_stm32f3.a 。

before make, ensure the board related lib file is generated. e.g. stm32f3 disco need libopencm3_stm32f3.a




