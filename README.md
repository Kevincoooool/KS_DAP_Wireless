<!--
 * @Descripttion : 
 * @version      : 
 * @Author       : Kevincoooool
 * @Date         : 2020-10-17 08:12:49
 * @LastEditors  : Kevincoooool
 * @LastEditTime : 2021-02-02 14:01:58
 * @FilePath     : \Github\KS_DAP_Wireless\README.md
-->

| KS无线DAP下载器 | 欢迎Star、项目不会停下、持续更新中 |
| ----------------- | -------- |

* 高速DAP下载器+脱机烧录 [成品众筹](https://item.taobao.com/item.htm?spm=a1z09.8149145.0.0.a8aa5af8fyXiHK&id=610773587113&_u=7kjj862d27d)
* 使用Altium Designer 20画的PCB
* 源码包含了有线模式、无线发射模式、无线接收模式和脱机烧录模式
* 源码来源：USB部分是TeenyUSB HID+MSC+CDC,SWD部分是XVIN1987开源的SWD下载器
* 整合为了HID+MSC+CDC+FATFS+W25Q+OLED的系统
* 没有W25Q的兄弟们记得把初始化去掉
* 脱机模式可选下载算法和下载文件
* 主控芯片：STM32F103C8T6 可更换其他ST芯片使用的HAL库，可直接替换
* 无线通信芯片：ESP8266  考虑更换为ESP32-S2（目前测试S2的HID+MSC+CDC已经调通，增加DAP中。。）
* 11-3 ESP32S2的DAP下载器已经调通，下载速度达到了HID的瓶颈32KB/S，下一步增加TCP
* 8266通信采用TCP通信，RTOS版本源码不知为何速度只有2KB/S，NONOS版本速度可达6KB/S
* DIY QQ交流群：554150925
[成品众筹](https://item.taobao.com/item.htm?id=630871236329)

## Pic:
<img src="https://whycan.com/files/members/4115/1.png" height="500px" width="800px" title="正面" style="display:inherit;"/> 
<img src="https://whycan.com/files/members/4115/2.png" height="500px" width="800px" title="反面" style="display:inherit;"/> 
<img src="https://whycan.com/files/members/4115/3.png" height="500px" width="800px" title="反面" style="display:inherit;"/> 
<img src="https://whycan.com/files/members/4115/4.png" height="500px" width="800px" title="反面" style="display:inherit;"/> 

## 捐赠
| 支付宝 | 微信支付 |
| ------ | --------- |
| <img src="https://whycan.com/files/members/4115/alipay.png" height="200px" width="164px" title="支付宝" style="display:inherit;"/> | <img src="https://whycan.com/files/members/4115/wechat.png" height="200px" width="164px" title="微信支付" style="display:inherit;"/> |


> 另外强调一下，本仓库的项目是**GPL协议**，不支持任何形式的私自产品化（当然大家自己DIY是没有任何问题的，这里只是防止有人借我的名义坑大家）
