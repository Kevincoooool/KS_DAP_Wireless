-- cdcview.lua
class "CDCView"(QFrame)

function CDCView:__init(vid,pid)
    QFrame.__init(self)
    self.windowTitle = tr("CDC View")
    self.btnRefresh = QPushButton(tr("Refresh"))
    self.portList = QComboBox()
    
    self.baudList = QComboBox{ minW = 80, QSerialPort.ValidBaudRate(), editable = true }
    self.baudList.lineEdit.inputMask = "00000000"
    self.btnOpen = QPushButton(tr("Open"))
    self.btnSend = QPushButton(tr("Send"))
    self.btnClear = QPushButton(tr("Clear"))
    self.sendEdit = QHexEdit{ readonly = false, overwriteMode = false}
    self.recvEdit = QHexEdit { readonly = true, overwriteMode = false }
    self.serial = QSerialPort(self)
    self.serial.flowControl = QSerialPort.FLOW_OFF
    self.baudList.currentIndex = self.serial.baudRate
    
    self.layout = QVBoxLayout{
        QHBoxLayout{ self.portList, self.btnRefresh, QLabel(tr("BaudRate:")), self.baudList, self.btnOpen, strech = "1,0,0,0",},
        QHBoxLayout{QLabel(tr("Send data")), self.btnSend,QLabel(), strech = "0,0,1"},
        self.sendEdit,
        QHBoxLayout{QLabel(tr("Recv data")), self.btnClear,QLabel(), strech = "0,0,1"},
        self.recvEdit,
    }
    
    self.btnRefresh.clicked = function()
        self.portList:clear()
        local ports = QSerialPort.enumPort()
        for i,v in ipairs(ports) do
            self.portList:addItem(v.portName, v)
        end
    end
    
    self.baudList.editTextChanged = function(text)
        local idx = self.baudList:findText(text)
        if idx > 0 and idx < QSerialPort.BAUDLAST then
            self.serial:setBaudRate(idx)
        else
            local bd = tonumber(text)
            if bd then
                self.serial:setBaudRate(bd)
            end
        end
    end
    
    self.btnOpen.clicked = function ()
        if self.serial.isOpen then
            self.serial:close()
            self.btnOpen.text = tr("Open")
        else
            i = self.portList.currentIndex
            portInfo = self.portList:itemData(i)
            local name = portInfo.portName
            if name then
            logEdit:append("open: " .. name .. " with setting: " .. self.serial.settingString)
            self.serial.portName = name
            res = self.serial:open()
            if res then
                self.btnOpen.text = tr("Close")
                logEdit:append("Success ...")
            else
                logEdit:append("Fail:  " .. self.serial.errorString)
            end
            end
        end
    end
    
    self.btnSend.clicked = function()
        local r = self.serial:write(self.sendEdit.data)
    end
    self.btnClear.clicked = function()
        self.recvEdit:clear()
    end
    self.serial.readyRead = function()
        local r = self.serial:readAll()
        self.recvEdit:append(r)
        self.recvEdit:scrollToEnd()
    end
    
    self.btnRefresh.clicked()
end