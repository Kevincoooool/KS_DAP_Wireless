function tr(x) return x end
function log(...)
    local r = ""
    for i,v in ipairs({...}) do
        r = r .. tostring(v) .. " "
    end
end
require("cdcview")
require("hidview")
require("usbview")

local subWindow = mdiArea:addSubWindow(USBView(0x0483))
subWindow:show()
subWindow.w = 600
subWindow.h = 500

subWindow = mdiArea:addSubWindow(HIDView(0x0483))
subWindow:show()
subWindow.x = 600 + 20
subWindow.w = 600
subWindow.h = 500


mainWindow:menuBar(){
    QMenu("Test Tools(&T)"){
        QAction("USB View(&U)"){
            triggered = function()
                mdiArea:addSubWindow(USBView(0x0483)):showMaximized()
            end, QKeySequence("Ctrl+U"),
        },
        QAction("CDC View(&D)"){
            triggered = function()
                mdiArea:addSubWindow(CDCView()):showMaximized()
            end, QKeySequence("Ctrl+D"),
        },
        QAction("HID View(&H)"){
            triggered = function()
                mdiArea:addSubWindow(HIDView(0x0483)):showMaximized()
            end, QKeySequence("Ctrl+H"),
        },
    }
}