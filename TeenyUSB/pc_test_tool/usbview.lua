-- usbview.lua
local fmt = string.format
class "USBDataView"(QFrame)
function USBDataView:__init()
    QFrame.__init(self)
    self.tabInput = QTabWidget()
    self.tabOutput = QTabWidget()
    
    self.layout = QVBoxLayout{
        QLabel("Output end points"),
        self.tabOutput,
        QLabel("Input end points"),
        self.tabInput,
        
    }
end

function USBDataView:setDevice(dev)
    self.usb = dev
    self.epMap = {}
    
    self.tabInput:clear()
    for i,v in ipairs(dev.readEndpoints) do
        local t = QFrame(self)
        t.btnClear = QPushButton(tr("Clear"))
        t.dataEdit = QHexEdit { readonly = true, overwriteMode = false }
        t.epAddr = v.addr
        t.btnClear.clicked = function()
           t.dataEdit:clear()
        end
        t.layout = QVBoxLayout{
            QHBoxLayout{t.btnClear, QLabel(), strech = "0,1"},
            t.dataEdit,
        }
        self.epMap[v.addr] = t
        self.tabInput:addTab(t, fmt("EP: %02x", v.addr))
    end
    
    self.tabOutput:clear()
    for i,v in ipairs(dev.writeEndpoints) do
        local t = QFrame(self)
        t.btnSend = QPushButton(tr("Send"))
        t.dataEdit = QHexEdit { readonly = false, overwriteMode = false }
        t.epAddr = v.addr
        t.btnSend.clicked = function()
            log("Send " .. #t.dataEdit.data .. " bytes data to ep " .. t.epAddr)
            local r = self.usb:write(t.epAddr, t.dataEdit.data)
            log("Result = " .. r)
        end
        t.layout = QVBoxLayout{
            QHBoxLayout{t.btnSend, QLabel(), strech = "0,1"},
            t.dataEdit,
        }
        self.epMap[v.addr] = t
        self.tabOutput:addTab(t, fmt("EP: %02x", v.addr))
    end
   
    self.usb.epDataReady = function(ep, data)
        --log("Got "..#data .. " bytes data from ep ".. ep)
        local t = self.epMap[ep]
        if t then
            t.dataEdit:append(data)
            t.dataEdit:scrollToEnd()
        else
            log("Unknown process data from " .. fmt("ep: %02x", ep))
        end
    end
end



class "USBView"(QFrame)

function USBView:__init(vid,pid)
    QFrame.__init(self)
    self.windowTitle = tr("USB View")
    vid = vid or 0
    pid = pid or 0
    self.usb = QLibUsb(self)
    self.usb.isOpen = false
    self.deviceList = QComboBox()
    self.vid = QLineEdit(string.format("%x",vid)){ inputMask = "HHHH"}
    self.pid = QLineEdit(string.format("%x",pid)){ inputMask = "HHHH"}
    self.btnOpen = QPushButton(tr("Open"))
    self.btnRefresh = QPushButton(tr("Refresh"))
    self.dataView = USBDataView(self)
    self.layout = QVBoxLayout{
        QHBoxLayout{
            QLabel("VID: 0x"), self.vid,
            QLabel("PID: 0x"), self.pid,self.btnRefresh,
        },
        QHBoxLayout{ self.deviceList, self.btnOpen, strech = "1,0",},
        self.dataView
    }
    
    self.btnRefresh.clicked = function()
        local vid = tonumber( "0x".. self.vid.text ) or 0
        local pid = tonumber( "0x".. self.pid.text ) or 0
        devices = QLibUsb.enumDevices(vid, pid)
        self.deviceList:clear()
        for k,v in pairs(devices) do
            self.deviceList:addItem(v.path, v)
        end
    end
    
    self.btnOpen.clicked = function()
        local info = self.deviceList:itemData(self.deviceList.currentIndex)
        local path = info.path
        if self.usb.isOpen then
            self.usb:close()
            self.btnOpen.text = tr("Open")
            self.usb.isOpen = false
        else
            self.usb.path = path
            self.usb.isOpen = self.usb:open(info)
            if self.usb.isOpen then
                self.btnOpen.text = tr("Close")
                log(tr("Open").. " " .. path .. "  "..tr("success"))
                self.dataView:setDevice(self.usb)
                _G.theUsb = self.usb
            else
                log(self.usb.lastErrorString)
                log(tr("Open").. " " .. path .. "  ".. tr("fail"))
            end
        end
    end
end