-- usb_desc_core.lua
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

--[[ 
 USB descriptor base class, all other descriptors are generate by Descriptor
 example:
 Create a Device descriptor class
 local DeviceDescriptorClass = Descriptor {
          -- field              default value, DUMMY means must filled by user
        {   bLength            = DUMMY                    },
        {   bDescriptorType    = DEVICE_DESCRIPTOR_TYPE   },
        {   bcdUSB             = 0x200                    },
        {   bDeviceClass       = 0                        },
        {   bDeviceSubClass    = 0                        },
        {   bDeviceProtocol    = 0                        },
        {   bMaxPacketSize     = 8                        },
        {   idVendor           = 0x0483                   },
        {   idProduct          = 0x3748                   },
        {   bcdDevice          = 0x100                    },
        {   iManufacture       = 0                        },
        {   iProduct           = 0                        },
        {   iSerial            = 0                        },
        {   bNumConfigurations = 1                        },
    }
    
  Create a real device descriptor

  local deviceDescriptor = DeviceDescriptorClass {
    bcdUSB = 0x110,
    idVendor = 0x1234,
    idProduct = 0x5678,
    strManufacture = "Test Manufacture",
    strProduct = "Test Product",
    strSerial = "Test Serial",
  }
 
  print( tostring(deviceDescriptor) )

]]

SIMPLE = SIMPLE or false
VERBOSE = VERBOSE or false

DEVICE_DESCRIPTOR_TYPE           =   SIMPLE and 0x01 or "USB_DEVICE_DESCRIPTOR_TYPE"
CONFIGURATION_DESCRIPTOR_TYPE    =   SIMPLE and 0x02 or "USB_CONFIGURATION_DESCRIPTOR_TYPE"
STRING_DESCRIPTOR_TYPE           =   SIMPLE and 0x03 or "USB_STRING_DESCRIPTOR_TYPE"
INTERFACE_DESCRIPTOR_TYPE        =   SIMPLE and 0x04 or "USB_INTERFACE_DESCRIPTOR_TYPE"
ENDPOINT_DESCRIPTOR_TYPE         =   SIMPLE and 0x05 or "USB_ENDPOINT_DESCRIPTOR_TYPE"
IAD_DESCRIPTOR_TYPE              =   SIMPLE and 0x0B or "USB_IAD_DESCRIPTOR_TYPE"
BOS_DESCRIPTOR_TYPE              =   sIMPLE and 0x0f or "USB_DESC_TYPE_BOS"
DUMMY = {}
function info(...)
    if not VERBOSE then return end
    io.write("Info: ", ...)
    io.write("\n")
end
function warning(...)
    io.write("Warning: ", ...)
    io.write("\n")
end


function splitU16(v)
    return v&0xff, v>>8
end
function splitU32(v)
    return v & 0xff, (v>>8)&0xff, (v>>16)&0xff, (v>>24)&0xff
end


local comment_col = 50
local fmt = string.format

local function collectData(desc, ident, cnt, init)
    local count = 0
    local res = init or ""
    local t = ""
    return function(s)
        if not s then
            if #t > 0 then
                t = t .. string.rep(" ", comment_col - #t - ident)
                t = t .. "/* " .. desc .. " */\n"
                res = res .. t
            end
            return res
        end

        count = count + cnt
        t = t .. s
        if count >= 8 then
            t = t .. string.rep(" ", comment_col - #t - ident)
            t = t .. "/* " .. desc .. " */\n"
            res = res .. t
            t = ""
            count = 0
        end
    end
end

function output8(v, desc, ident, cnt)
    local cc = collectData(desc, ident or 0, 1)
    if cnt then
        for i=1,cnt do
            cc(fmt("0x%02x, ", v[i] or 0))
        end
        return cc()
    else
        local r = fmt("0x%02x, ",v)
        if SIMPLE then return r end
        return cc(r) or cc()
    end
end

function output16(v, desc, ident, cnt)
    local cc = collectData(desc, ident or 0, 2)
    if cnt then
        for i=1,cnt do
            local l,h = splitU16(v[i] or 0)
            cc(fmt("0x%02x, 0x%02x, ", l, h))
        end
        return cc()
    else
        local l,h = splitU16(v)
        local r = fmt("0x%02x, 0x%02x, ", l, h)
        if SIMPLE then return r end
        return cc(r) or cc()
    end
end

function output32(v, desc, ident, cnt)
    local cc = collectData(desc, ident or 0, 4)
    if cnt then
        for i=1,cnt do
            local l,h,hl,hh = splitU32(v[i] or 0)
            cc(fmt("0x%02x, 0x%02x, 0x%02x, 0x%02x, ", l, h, hl, hh))
        end
        return cc()
    else
        local l,h,hl,hh = splitU32(v)
        local r = fmt("0x%02x, 0x%02x, 0x%02x, 0x%02x, ", l, h, hl, hh)
        if SIMPLE then return r end
        return cc(r) or cc()
    end
end

function outputChar(v, desc, ident, cnt)
    local init = nil
    if cnt then
        init = v
        while init:byte(#init) == 0 and #init > 0 do
            init = init:sub(1, #init - 1)
        end
        init = "/* " .. init .. " */\n"
    end
    local cc = collectData(desc, ident or 0, 1, init)
    if cnt then
        local res = ""
        for i=1,cnt do
            local ch = v:byte(i) or 0
            if ch>=0x20 and ch<=0x7f then
                cc(fmt("'%s', ", string.char(ch)))
            else
                cc(fmt("0x%02x, ", ch))
            end
        end
        return cc()
    else
        local r = ""
        if v>=0x20 and v<=0x7f then
            r = r .. fmt("'%s', ", string.char(v))
        else
            r = r .. fmt("0x%02x, ", v)
        end
        if SIMPLE then return r end
        return cc(r) or cc()
    end
end

function outputWChar(v, desc, ident, cnt)
    local init = nil
    if cnt then
        init = v
        while init:byte(#init) == 0 and #init > 0 do
            init = init:sub(1, #init - 1)
        end
        init = "/* " .. init .. " */\n"
    end
    local cc = collectData(desc, ident or 0, 2, init)
    if cnt then
        local i = 1
        for j=1,cnt do
            local l = v:byte(i) or 0
            i = i + 1
            local h = 0
            if l > 0x7f then
                h = v:byte(i) or 0
                i = i + 1
            end
            if h == 0 and l>=0x20 and l<=0x7f then
                cc(fmt("'%s', 0x%02x, ", string.char(l), h))
            else
                cc(fmt("0x%02x, 0x%02x, ", l, h))
            end
        end
        return cc()
    else
        local r = ""
        local l,h = splitU16(v)
        if h == 0 and l>=0x20 and l<=0x7f then
            r = r .. fmt("'%s', 0x%02x, ", string.char(l), h)
        else
            r = r .. fmt("0x%02x, 0x%02x, ", l, h)
        end
        if SIMPLE then return r end
        return cc(r) or cc()
    end
end

fieldSize = nil
-- String means the value is a macro define
function outputString(v, desc, ident)
    ident = ident or 0
    if fieldSize(desc) == 2 then
        v = "LO_BYTE("..v.."), HI_BYTE(" .. v .. ")"
    end
    if SIMPLE then return v .. ", " end
    return v ..','.. string.rep(" ", comment_col - #v - 1 - ident) .. "/* " .. desc .. " */\n"
end

local field_prefix_table = {
    b = output8,
    bm = output8,
    i = output8,
    id = output16,
    w = output16,
    bcd = output16,
    wc = outputWChar,
    c = outputChar,
    dw = output32,
}

function fieldPrefix(field)
    local pre = string.find(field, "[A-Z]")
    local post = nil
    if pre and pre>1 then
        post = field:sub(pre)
        pre = field:sub(1,pre-1)
    end
    --if not pre then error("unknown prefix of field \"" .. field .. '"') end
    return pre, post
end

function fieldValue(desc, field)
    local f = desc.content[field]
    if type(f) == "function" then
        return f(desc, field)
    end
    return f
end

fieldSize = function(field)
    local pre = fieldPrefix(field)
    local cnt = 1
    if field:find("_[0-9]+") then
        local s = field:find("_[0-9]+")
        cnt = tonumber(field:sub(s+1))
        assert("Fail to get data length of field: " .. tostring(field))
    end
    if field_prefix_table[pre] == output16 then return 2*cnt end
    if field_prefix_table[pre] == outputWChar then return 2*cnt end
    if field_prefix_table[pre] == output8 then return 1*cnt end
    if field_prefix_table[pre] == output32 then return 4*cnt end
    if field_prefix_table[pre] == outputChar then return 1*cnt end
    error("unknown field size " .. tostring(filed))
    return -1
end

function outputField(desc, field)
    local ident = ""-- desc.ident or "    "
    local pre = fieldPrefix(field)
    local cnt = field:find("_[0-9]+")
    if cnt and cnt>1 then
        cnt = tonumber(field:sub(cnt+1))
    end
    local output = field_prefix_table[pre]
    if not output then error("Unknown prefix " .. tostring(pre) .. " of field " .. tostring(field)) end
    -- output string field, output direct
    if not cnt and type(desc.content[field]) == "string" then return outputString(desc.content[field],field,#ident, cnt) end
    -- output function field, evalute it then output
    if type(desc.content[field]) == "function" then return output(desc.content[field](desc, field),field,#ident, cnt) end
    -- output number field
    return output(desc.content[field],field,#ident, cnt)
end

-- descriptor init function, bind to __call meta method
local function descInit(desc, param)
    if param.varData then
        for i,v in ipairs(param.varData) do
            for name, value in pairs(v) do
                desc.layout[#desc.layout+1] = name
                desc[name] = value
                desc.paramLength = desc.paramLength + fieldSize(name)
                break
            end
        end
    end
    for k,v in pairs(desc.default) do
        if param[k] then
            desc.default[k] = param[k]
        end
    end
    desc.bLength = desc.headerLength + desc.paramLength
    
    for i,v in ipairs(param) do
        desc[i] = v
    end
    -- copy strings in param to descriptor
    for k,v in pairs(param) do
        local pre,post = fieldPrefix(k)
        local field = "i" .. tostring(post)
        -- field prefix is strXXX, and iXXX exist in the layout
        if pre == "str" and desc.default[field] then
            desc[k] = v
        end
    end
    return desc
end

function descToString(desc, hasChild, noName)
    local r = ""
    if not noName then
        r = r .. "///////////////////////////////////////\n"
        r = r .. "/// " .. desc.name .. "\n"
        r = r .. "///////////////////////////////////////\n"
    end
    for i,v in ipairs(desc.layout) do
        r = r .. outputField(desc, v)
    end
    if hasChild then
        for i,v in ipairs(desc.children) do
            r = r .. "\n"
            .. descToString(v, hasChild, noName)
        end
    end
    return r
end

-- descriptor to string, bind to __tostring meta method
local function printFields(desc)
    print("///////////////////////////////////////")
    print("/// " ..desc.name)
    print("///////////////////////////////////////")
    local r = ""
    for i,v in ipairs(desc.layout) do
        r = r .. outputField(desc, v)
    end
    print(r)
    for i,v in ipairs(desc.children) do
        print("\n")
        printFields(v)
    end
end

function printDesc(desc)
    printFields(desc)

    if desc.extDesc and #desc.extDesc > 0 then
        print("///////////////////////////////////////")
        print("//// extra descriptors ")
        print("///////////////////////////////////////")
        for i, v in ipairs(desc.extDesc) do
            print("type: " .. v.type .. "  interface " .. v.interface.content.bInterfaceNumber)
        end
    end

    if desc.strings and #desc.strings > 0 then
        print("///////////////////////////////////////")
        print("//// Strings")
        print("///////////////////////////////////////")
        for i,v in ipairs(desc.strings) do
            print("/// string " .. i .. "  " .. v)
            printDesc(StringDescriptor(v))
        end
    end
    print("")
end

function CreateDescriptor(descLayout, initParam, descName)
    local desc = {}
    desc.layout = {}
    desc.headerLength = 0
    desc.paramLength = 0
    desc.content = {}
    desc.children = {}
    desc.strings = {}
    desc.name = descName
    for i,v in ipairs(descLayout) do
        for field, value in pairs(v) do
            -- set content to default value
            if value ~= DUMMY then
                desc.content[field] = value
            end

            -- set content to param set value
            if initParam[field] then
                desc.content[field] = initParam[field]
            end

            -- try if it is a string
            local pre, post = fieldPrefix(field)
            if pre == "i" and initParam["str"..post] then
                local strContent = initParam["str"..post]
                if not desc.strings[strContent] then
                    desc.strings[#desc.strings+1] = strContent
                    desc.strings[strContent] = #desc.strings
                end
                -- the string index will calculate later
                desc.content[field] = function(desc, field)  return desc.strings[strContent] end
            end
            assert( field=="bLength" or desc.content[field], tostring(field) .. " in " .. tostring(descName) .. " not set")
            desc.layout[i] = field
            desc.headerLength = desc.headerLength + fieldSize(field)
            break
        end
    end

    -- append var data to descriptor
    if initParam.varData then
        for i,v in ipairs(initParam.varData) do
            for name, value in pairs(v) do
                desc.layout[#desc.layout+1] = name
                desc.content[name] = value
                desc.paramLength = desc.paramLength + fieldSize(name)
                break
            end
        end
    end
    desc.content.bLength = desc.headerLength + desc.paramLength

    local childString = nil
    for i,v in ipairs(initParam) do
        desc.children[#desc.children+1] = v
        if not childString then
            childString = v.strings
        else
            for is, iv in ipairs(v.strings) do
                if not childString[iv] then
                    childString[#childString+1] = iv
                    childString[iv] = #childString
                end
            end
            v.strings = childString
        end
    end
    if childString then
        for is, iv in ipairs(desc.strings) do
            table.insert(childString, is, iv)
        end
        for is, iv in ipairs(childString) do
            childString[iv] = is
        end
        desc.strings = childString
    end

    desc.prefix = initParam.prefix
    return desc
end

local subPatten = "%$%((%w+)%)"
local nl = [[

]]
function Ident(data, space)
    space = space or "  "
    local last = ""
    if data:sub(#data) == "\n" then
        data = data:sub(1,#data-1)
        last = "\n"
    end
    return space .. string.gsub(data, nl, nl .. space) .. last
end

function BeginGenCode(dev)
    dev = dev or {}
    local prefix = dev.prefix or ""
    if prefix:sub(#prefix) ~= "_" and #prefix > 0 then
        prefix = prefix .. "_"
    end
    return function(subs, text)
        subs.PREFIX = subs.PREFIX or prefix
        if not text then
            text = subs.text
        end
        local r = string.gsub(text, subPatten, subs)
        return r
    end
end
