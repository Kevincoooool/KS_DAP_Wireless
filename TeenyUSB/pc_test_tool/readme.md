# TeenyUSB PC端测试工具 (Teeny PC Tool)

基于XToolbox的USB测试工具，XToolbox是一个在lua中绑定Qt的项目，项目源代码在[这里](https://github.com/xtoolbox/qtlua)。

XToolbox is a lua Qt binder, source code is [here](https://github.com/xtoolbox/qtlua).

## 使用方法

运行XToolbox.exe，填入需要测试的设备VID和PID，点击Refresh按钮，选择需要测试的设备后点击Open。

USB View窗口中可以测试所有libusb支持的设备，HID View窗口中可以测试自定义的HID设备。

点击Send按钮发送数据，点击Clear按钮清除接收到的数据。

## 工具预览

![pc_tool_ui](pc_tool_ui.png)

