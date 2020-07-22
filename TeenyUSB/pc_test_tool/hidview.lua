-- hidview.lua
-- 
dofile("hidparamview.lua")
class "HIDView"(QFrame)

function HIDView:__init(vid,pid)
    QFrame.__init(self)
    self.windowTitle = tr("HID View")
    self.param = HIDParamView(vid,pid)
    self.btnSend = QPushButton(tr("Send"))
    self.btnClear = QPushButton(tr("Clear"))
    self.sendEdit = QHexEdit{ readonly = false, overwriteMode = false}
    self.recvEdit = QHexEdit { readonly = true, overwriteMode = false }
    self.layout = QVBoxLayout{
        self.param,
        QHBoxLayout{QLabel(tr("Send data")), self.btnSend,QLabel(), strech = "0,0,1"},
        self.sendEdit,
        QHBoxLayout{QLabel(tr("Recv data")), self.btnClear,QLabel(), strech = "0,0,1"},
        self.recvEdit,
    }
    self.btnSend.clicked = function()
        local reportID = 0
        r = self.param.hid:writeData(reportID, self.sendEdit.data)
        if r ~= self.param.hid.caps.outputReportLength then
            log(r, self.param.hid.errorString)
        end
    end
    self.btnClear.clicked = function()
        self.recvEdit:clear()
    end
    self.param.hid.readyRead = function()
        r = self.param.hid:readAll()
        self.recvEdit:append(r)
        self.recvEdit:scrollToEnd()
    end
end