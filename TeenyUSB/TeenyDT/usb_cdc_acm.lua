-- usb_cdc_acm.lua
--  _______                    _____ _______ 
-- |__   __|                  |  __ \__   __|
--    | | ___  ___ _ __  _   _| |  | | | |   
--    | |/ _ \/ _ \ '_ \| | | | |  | | | |   
--    | |  __/  __/ | | | |_| | |__| | | |   
--    |_|\___|\___|_| |_|\__, |_____/  |_|   
--                        __/ |              
--                       |___/               
--
-- TeenyDT - GUI and command line tool to generate USB descriptors and drivers
-- 
-- Copyright (c) 2019 XToolBox  - admin@xtoolbox.org
--                         www.tusb.org
-- 
-- Permission is hereby granted, free of charge, to any person obtaining a copy
-- of this software and associated documentation files (the "Software"), to deal
-- in the Software without restriction, including without limitation the rights
-- to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
-- copies of the Software, and to permit persons to whom the Software is
-- furnished to do so, subject to the following conditions:
-- 
-- The above copyright notice and this permission notice shall be included in all
-- copies or substantial portions of the Software.
-- 
-- THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
-- IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
-- FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
-- AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
-- LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
-- OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
-- SOFTWARE.

require("usb_desc_base")
local TAG = "CDC_ACM"
function CDC_ACM(param)
    local Ctrl, Data
    local CtrlEp = param.ep_ctrl or param.CtrlEp or param[1]
    local ReadEp = param.ep_in or param.ReadEp or param[2]
    local WriteEp = param.ep_out or param.WriteEp or param[3]
    assert(CtrlEp, TAG .. "Control endpoint not set")
    assert(ReadEp, TAG .. "Data read endpoint not set")
    assert(ReadEp, TAG .. "Data write endpoint not set")
    assert(CtrlEp.content.bmAttributes == Interrupt, TAG .. "Control endpoint type must be interrupt")
    assert((CtrlEp.content.bEndpointAddress & 0x80) == 0x80, TAG .. "Control endpoint direction must be in")
    assert(ReadEp.content.bmAttributes == Bulk, TAG .. "Data read endpoint type must be Bulk")
    assert((ReadEp.content.bEndpointAddress & 0x80) == 0x80, TAG .. "Data read endpoint direction must be in")
    assert(WriteEp.content.bmAttributes == Bulk, TAG .. "Data write endpoint type must be Bulk")
    assert((WriteEp.content.bEndpointAddress & 0x80) == 0x00, TAG .. "Data write endpoint direction must be out")
    Ctrl = Interface{
        bInterfaceClass = param.bInterfaceClass or 2,
        bInterfaceSubClass = param.bInterfaceSubClass or 2,
        bInterfaceProtocol = param.bInterfaceProtocol or 1,
        extDesc = param.extDesc,
        Function{   bDescriptorSubtype = 0,
                    name = "cdc acm header descriptor",
                    varData = {
                        {bcdCDC = 0x110},
                    }
                },
        Function{   bDescriptorSubtype = 1,
                    name = "cdc acm call management descriptor",
                    varData = {
                        {bmCapabilities = 0x00},
                        {bDataInterface = 0x01},
                    }
                },
        Function{   bDescriptorSubtype = 2,
                    name = "cdc acm descriptor",
                    varData = {
                        {bmCapabilities = param.bmCapabilities or 0x02},
                    }
                },
        Function{   bDescriptorSubtype = 6,
                    name = "cdc acm union descriptor",
                    varData = {
                        {bMasterInterface = 0x00},
                        {bSlaveInterface0 = 0x01},
                    }
                },
        param.CtrlEp or param[1],
    }
    
    Data = Interface{
        bInterfaceClass = 0x0a,
        bInterfaceSubClass = 0,
        bInterfaceProtocol = 0,
        param.ReadEp or param[2],
        param.WriteEp or param[3],
    }
    return IAD{
        strFunction = param.strFunction,
        Ctrl,
        Data
    }
end
