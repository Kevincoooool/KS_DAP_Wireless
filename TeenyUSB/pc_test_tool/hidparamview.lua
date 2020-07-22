-- hidparamview.lua
-- 创建一个HID参数设置界面。self.hid为参数所对应的HID实例
-- 可以通过self.hid.readyReady信号来读取HID数据
-- 向HID写数据，self.hid:write({1,2,3,4,5,6,7,8,9,10})
--[[
   hidParamView = HIDParamView()
   hidParamView.hid.readyRead = function()
       data = hidParamView.hid:readAll()
       -- process hid data here
       ...
       -- write data back
       hidParamView.hid:write(data)
   end
--]]
class "HIDParamView"(QFrame)

function HIDParamView:__init(vid,pid)
    QFrame.__init(self)
    self.windowTitle = tr("HID Viewer")
    self.vid = vid or 0
    self.pid = pid or 0
    self.hid = QUsbHid(self)
    self.hid.isOpen = false
    self.deviceList = QComboBox()
    self.vid = QLineEdit(string.format("%x",self.vid)){ inputMask = "HHHH"}
    self.pid = QLineEdit(string.format("%x",self.pid)){ inputMask = "HHHH"}
    self.btnOpen = QPushButton(tr("Open"))
    self.btnRefresh = QPushButton(tr("Refresh"))
    self.layout = QVBoxLayout{
        QHBoxLayout{
            QLabel("VID: 0x"), self.vid,
            QLabel("PID: 0x"), self.pid,self.btnRefresh,
        },
        QHBoxLayout{ self.deviceList, self.btnOpen, strech = "1,0",
        },
    }
    
    self.btnRefresh.clicked = function()
        local vid = tonumber( "0x".. self.vid.text ) or 0
        local pid = tonumber( "0x".. self.pid.text ) or 0
        devices = QUsbHid.enumDevices(vid, pid)
        self.deviceList:clear()
        for k,v in pairs(devices) do
            self.deviceList:addItem(v.friendName, v)
        end
    end
    
    self.btnOpen.clicked = function()
        local path = self.deviceList:itemData(self.deviceList.currentIndex).path
        if self.hid.isOpen then
            self.hid:close()
            self.btnOpen.text = tr("Open")
            self.hid.isOpen = false
        else
            self.hid.path = path
            self.hid.isOpen = self.hid:open()
            if self.hid.isOpen then
                self.btnOpen.text = tr("Close")
                log(tr("Open").. " " .. path .. "  "..tr("success"))
                log("inputReportLength", self.hid.caps.inputReportLength)
                log("outputReportLength", self.hid.caps.outputReportLength)
                log("featureReportLength", self.hid.caps.featureReportLength)
            else
                log(self.hid.errorString)
                log(tr("Open").. " " .. path .. "  ".. tr("fail"))
            end
        end
    end
end