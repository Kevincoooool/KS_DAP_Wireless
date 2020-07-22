-- usb_hid.lua
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


function HIDDescriptor(param)
    local varData = {}
    local numDesc = #param
    local extDesc = {}
    for i,v in ipairs(param) do
        local t = {}
        t["bDescriptorType"..i] = 0x22
        varData[#varData+1] = t
        t = {}
        t["wDescriptorLength"..i] = #v.data
        varData[#varData+1] = t
        extDesc = appendExt(extDesc, v)
    end
    
    local desc = CreateDescriptor({
        {bLength              = DUMMY                        },
        {bDescriptorType      = 0x21                         },
        {bcdHID               = 0x111                        },
        {bCountryCode         = 0                            },
        {bNumDescriptors      = numDesc                      },
    }, {varData = varData}, "hid descriptor")
    desc.extDesc = extDesc
    return desc
end

local TAG = "HID: "

function HID_BuildReport(str)
    str = string.gsub(str, "//", "--")
    local r = load( "return { ".. str .. "}")() or {0}
    r.text = string.gsub(str, "%-%-", "//")
    return {
        data =  r,
        type = "HIDReport",
        handler = MakeHID,
    }
end

function HID_InOut(size)
    local str = string.format("0x95, 0x%02x,", size)
    local r = [[
        -- report descriptor for general input/output
        0x06, 0x00, 0xFF,  -- Usage Page (Vendor Defined 0xFF00)
        0x09, 0x01,        -- Usage (0x01)
        0xA1, 0x01,        -- Collection (Application)
        0x09, 0x02,        --   Usage (0x02)
        0x15, 0x00,        --   Logical Minimum (0)
        0x25, 0xFF,        --   Logical Maximum (255)
        0x75, 0x08,        --   Report Size (8)
        ]]..str..
                 [[        --   Report Count (]]..tostring(size)..[[)
        0x81, 0x02,        --   Input (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position)
        0x09, 0x03,        --   Usage (0x03)
        0x91, 0x02,        --   Output (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position,Non-volatile)
        0xC0               -- End Collection
    ]]
    return HID_BuildReport(r)
end

function HID_BootKeyBoard()
    local r = [[
        --  Boot keyboad report descriptor
        0x05, 0x01,     -- USAGE_PAGE (Generic Desktop)
        0x09, 0x06,     -- USAGE (Keyboard)
        0xa1, 0x01,     -- COLLECTION (Application)
        0x05, 0x07,     --   USAGE_PAGE (Keyboard)
        0x19, 0xe0,     --   USAGE_MINIMUM (Keyboard LeftControl)
        0x29, 0xe7,     --   USAGE_MAXIMUM (Keyboard Right GUI)
        0x15, 0x00,     --   LOGICAL_MINIMUM (0)
        0x25, 0x01,     --   LOGICAL_MAXIMUM (1)
        0x75, 0x01,     --   REPORT_SIZE (1)
        0x95, 0x08,     --   REPORT_COUNT (8)
        0x81, 0x02,     --   INPUT (Data,Var,Abs)
        0x95, 0x01,     --   REPORT_COUNT (1)
        0x75, 0x08,     --   REPORT_SIZE (8)
        0x81, 0x03,     --   INPUT (Cnst,Var,Abs)
        0x95, 0x05,     --   REPORT_COUNT (5)
        0x75, 0x01,     --   REPORT_SIZE (1)
        0x05, 0x08,     --   USAGE_PAGE (LEDs)
        0x19, 0x01,     --   USAGE_MINIMUM (Num Lock)
        0x29, 0x05,     --   USAGE_MAXIMUM (Kana)
        0x91, 0x02,     --   OUTPUT (Data,Var,Abs)
        0x95, 0x01,     --   REPORT_COUNT (1)
        0x75, 0x03,     --   REPORT_SIZE (3)
        0x91, 0x03,     --   OUTPUT (Cnst,Var,Abs)
        0x95, 0x06,     --   REPORT_COUNT (6)
        0x75, 0x08,     --   REPORT_SIZE (8)
        0x15, 0x00,     --   LOGICAL_MINIMUM (0)
        0x25, 0x65,     --   LOGICAL_MAXIMUM (101)
        0x05, 0x07,     --   USAGE_PAGE (Keyboard)
        0x19, 0x00,     --   USAGE_MINIMUM (Reserved (no event indicated))
        0x29, 0x65,     --   USAGE_MAXIMUM (Keyboard Application)
        0x81, 0x00,     --   INPUT (Data,Ary,Abs)
        0xc0            -- END_COLLECTION
    ]]
    return HID_BuildReport(r) 
end
function HID_BootMouse()
    local r = [[
        --  Boot Mouse report descriptor
        0x05, 0x01,     -- USAGE_PAGE (Generic Desktop)
        0x09, 0x02,     -- USAGE (Mouse)
        0xa1, 0x01,     -- COLLECTION (Application)
        0x09, 0x01,     --   USAGE (Pointer)
        0xa1, 0x00,     --   COLLECTION (Physical)
        0x05, 0x09,     --     USAGE_PAGE (Button)
        0x19, 0x01,     --     USAGE_MINIMUM (Button 1)
        0x29, 0x03,     --     USAGE_MAXIMUM (Button 3)
        0x15, 0x00,     --     LOGICAL_MINIMUM (0)
        0x25, 0x01,     --     LOGICAL_MAXIMUM (1)
        0x95, 0x03,     --     REPORT_COUNT (3)
        0x75, 0x01,     --     REPORT_SIZE (1)
        0x81, 0x02,     --     INPUT (Data,Var,Abs)
        0x95, 0x01,     --     REPORT_COUNT (1)
        0x75, 0x05,     --     REPORT_SIZE (5)
        0x81, 0x03,     --     INPUT (Cnst,Var,Abs)
        0x05, 0x01,     --     USAGE_PAGE (Generic Desktop)
        0x09, 0x30,     --     USAGE (X)
        0x09, 0x31,     --     USAGE (Y)
        0x15, 0x81,     --     LOGICAL_MINIMUM (-127)
        0x25, 0x7f,     --     LOGICAL_MAXIMUM (127)
        0x75, 0x08,     --     REPORT_SIZE (8)
        0x95, 0x02,     --     REPORT_COUNT (2)
        0x81, 0x06,     --     INPUT (Data,Var,Rel)
        0xc0,           --   END_COLLECTION
        0xc0            -- END_COLLECTION
    ]]
    return HID_BuildReport(r)
end
function HID_ReportTemp()
local r = [[
    -- Temaple report
    0x06, 0x00, 0xFF,  -- Usage Page (Vendor Defined 0xFF00)
    0x09, 0x01,        -- Usage (0x01)
    0xA1, 0x01,        -- Collection (Application)
    0x09, 0x02,        --   Usage (0x02)
    0x15, 0x00,        --   Logical Minimum (0)
    0x25, 0xFF,        --   Logical Maximum (255)
    0x75, 0x08,        --   Report Size (8)
    0x95, 0x40,        --   Report Count (64)
    0x81, 0x02,        --   Input (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position)
    0x09, 0x03,        --   Usage (0x03)
    0x91, 0x02,        --   Output (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position,Non-volatile)
    0xC0               -- End Collection
]]
    return HID_BuildReport(r)
end

function USB_HID(param)
    local ReadEp = param.ep_in or param.ReadEp
    if not ReadEp then
        if param[1] and (param[1].content.bEndpointAddress & 0x80) == 0x80 then
            ReadEp = param[1]
        elseif param[2] and (param[2].content.bEndpointAddress & 0x80) == 0x80 then
            ReadEp = param[2]
        end
    end
    assert(ReadEp, "HID must have one IN endpoint")
    local WriteEp = param.ep_out or param.WriteEp
    if not WriteEp then
        if param[1] and (param[1].content.bEndpointAddress & 0x80) == 0x00 then
            WriteEp = param[1]
        elseif param[2] and (param[2].content.bEndpointAddress & 0x80) == 0x00 then
            WriteEp = param[2]
        end
    end
    local ext = {}
    ext = appendExt(ext, param.extDesc)
    ext = appendExt(ext, param.report)
    ext = appendExt(ext, param.physical)
    local Hid = Interface{
        bInterfaceClass = param.bInterfaceClass or 3,
        bInterfaceSubClass = param.bInterfaceSubClass or (param.isBoot and 1 or 0),
        bInterfaceProtocol = param.bInterfaceProtocol or (param.isKey and 1 or (param.isMouse and 2 or 0)),
        HIDDescriptor(ext),
        ReadEp,
        WriteEp,
    }
    return Hid
end

local function HidHexData(data)
    local r = ""
    for i=1,#data do
        r = r .. string.format("0x%02x, ", data[i] & 0xff)
        if i % 8 == 0 then r = r .. "\n" end
    end
    if r:sub(#r) ~= "\n" then r = r .. "\n" end
    return r
end

function MakeHID(dev, extDesc, header)
    local genCode = BeginGenCode(dev)
    if extDesc.type == "HIDReport" then
        local src = header and [[
#define $(PREFIX)REPORT_DESCRIPTOR_SIZE_IF$(ID)  ($(SIZE))
extern const uint8_t $(PREFIX)ReportDescriptor_if$(ID)[$(PREFIX)REPORT_DESCRIPTOR_SIZE_IF$(ID)];

]] or [[
#define $(PREFIX)REPORT_DESCRIPTOR_SIZE_IF$(ID)  ($(SIZE))
WEAK __ALIGN_BEGIN const uint8_t $(PREFIX)ReportDescriptor_if$(ID)[$(PREFIX)REPORT_DESCRIPTOR_SIZE_IF$(ID)] __ALIGN_END = {
$(BODY)};

]]
        return genCode({
            SIZE = #extDesc.data,
            BODY = extDesc.data.text or Ident( HidHexData(extDesc.data ) ),
            ID = extDesc.interface.content.bInterfaceNumber,
        },src)
    end
    return ""
end

