### KS无线DAP下载器
* 使用Altium Designer 20画的PCB
* 源码包含了有线模式、无线发射模式、无线接收模式和脱机烧录模式
* 源码来源：USB部分是TeenyUSB HID+MSC+CDC,SWD部分是XIVN1987开源的SWD下载器
* 整合为了HID+MSC+CDC+FATFS+W25Q+OLED的系统
* 脱机模式可选下载算法和下载文件
* 主控芯片：STM32F103C8T6 可更换STM32F072C8T6 使用的HAL库，可直接替换
* 无线通信芯片：ESP8266  考虑更换为ESP32-S2（目前测试S2的USB坑太多）
* 通信采用TCP通信，RTOS版本源码不知为何速度只有2KB/S，NONOS版本速度可达6KB/S
* DIY QQ交流群：554150925
