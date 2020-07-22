-- usb_desc_base.lua
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

require("usb_desc_core")

function appendExt(ext1, ext2)
    if ext2 then
        if ext2[1] then
            for i,v in ipairs(ext2) do
                ext1[#ext1+1] = v
            end
        elseif ext2.type then
            ext1[#ext1+1] = ext2
        end
    end
    return ext1
end

function Device(param)
    local desc = CreateDescriptor( {
       -- field               default value
        {bLength            = DUMMY                    },
        {bDescriptorType    = DEVICE_DESCRIPTOR_TYPE   },
        {bcdUSB             = 0x200                    },
        {bDeviceClass       = 0                        },
        {bDeviceSubClass    = 0                        },
        {bDeviceProtocol    = 0                        },
        {bMaxPacketSize     = 64                       },
        {idVendor           = 0x2017                   },
        {idProduct          = 0x0924                   },
        {bcdDevice          = 0x100                    },
        {iManufacturer      = 0                        },
        {iProduct           = 0                        },
        {iSerial            = 0                        },
        {bNumConfigurations = #param                   },
    }, param, "device descriptor")
    desc.extDesc = {}
    for i,v in ipairs(desc.children) do
        v.content.bConfigurationValue = i
        if v.content.bNumIAD > 0 then
            desc.content.bDeviceClass = 0xef
            desc.content.bDeviceSubClass = 0x02
            desc.content.bDeviceProtocol = 0x01
        end
        appendExt(desc.extDesc, v.extDesc)
    end
    return desc
end

function TotalLength(desc, field)
    local r = desc.content.bLength
    for i,v in ipairs(desc.children) do
        local l = fieldValue(v, "dwTotalLength")
               or fieldValue(v, "wTotalLength")
               or fieldValue(v, "wLength")
               or fieldValue(v, "bLength")
        assert(l, "There is not length field in " .. tostring(v.name))
        r = r + l
    end
    return r
end

function Config(param)
    local attr = 0x80
    -- parse the attr from the given param
    if param.SelfPower then attr = attr + 0x40 end
    if param.RemoteWakeup then attr = attr + 0x20 end
    if param.bmAttributes then attr = param.bmAttributes end
    local desc = CreateDescriptor({
        {bLength           = DUMMY                     },
        {bDescriptorType   = CONFIGURATION_DESCRIPTOR_TYPE },
        {wTotalLength      = TotalLength               },
        {bNumInterfaces    = 0xff                      },
        {bConfigurationValue = 1                       },
        {iConfiguration    = 0                         },
        {bmAttributes      = attr                      },
        {bMaxPower         = 100                       }, 
    }, param, "config descriptor")

    local ifCount = 0
    local iadCount = 0
    local extDesc = {}
    for i,v in ipairs(desc.children) do
        assert(v.content.bDescriptorType == INTERFACE_DESCRIPTOR_TYPE
         or    v.content.bDescriptorType == IAD_DESCRIPTOR_TYPE, "must be interface or IAD")
        if v.content.bDescriptorType == IAD_DESCRIPTOR_TYPE then
            iadCount = iadCount + 1
            for j,w in ipairs(v.children) do
                w.content.bInterfaceNumber = ifCount
                appendExt(extDesc, w.extDesc)
                ifCount = ifCount + 1
            end
        else
            v.content.bInterfaceNumber = ifCount
            appendExt(extDesc, v.extDesc)
            ifCount = ifCount + 1
        end
    end
    desc.content.bNumInterfaces = ifCount
    desc.content.bNumIAD = iadCount
    desc.extDesc = extDesc
    return desc
end

function Interface(param)
    local epCnt = 0
    local epLength = 0 
    for i,v in ipairs(param) do
        if v.content.bDescriptorType == ENDPOINT_DESCRIPTOR_TYPE then
            epCnt = epCnt + 1
        end
        epLength = epLength + v.content.bLength
    end
    local desc = CreateDescriptor({
        {bLength                  = DUMMY                        },
        {bDescriptorType          = INTERFACE_DESCRIPTOR_TYPE    }, 
        {bInterfaceNumber         = 0xff                         }, -- assigned by the config parser
        {bAlternateSetting        = 0                            },
        {bNumEndpoints            = epCnt                        },
        {bInterfaceClass          = 0xff                         },
        {bInterfaceSubClass       = 0xff                         },
        {bInterfaceProtocol       = 0                            },
        {iInterface               = 0                            },
    }, param , "interface descriptor")
    desc.content.wTotalLength = TotalLength
    desc.extDesc = appendExt({}, param.extDesc)
    if param.WCID then
        desc.extDesc = appendExt(desc.extDesc, param.WCID(param.GUID))
    end
    for i,v in ipairs(param) do
        if v.extDesc then
            desc.extDesc = appendExt(desc.extDesc, v.extDesc)
        end
    end
    
    for i,v in ipairs(desc.extDesc) do
        v.interface = desc
    end
    return desc
end

local function GetFirstInterface(desc, field)
    assert(#desc.children>0, "children is less than 1")
    return desc.children[1].content.bInterfaceNumber
end

function IAD(param)
    assert(#param >= 2, "IAD need at least 2 interface")
    local intFirst = param[1]
    local intLast = param[#param]
    local desc = CreateDescriptor( {
                {bLength                = DUMMY                          },
                {bDescriptorType        = IAD_DESCRIPTOR_TYPE            },
                {bFirstInterface        = GetFirstInterface              },
                {bInterfaceCount        = #param                         },
                {bFunctionClass         = intFirst.content.bInterfaceClass       },
                {bFunctionSubClass      = intFirst.content.bInterfaceSubClass    },
                {bFunctionProtocol      = intFirst.content.bInterfaceProtocol    },
                {iFunction              = 0                              },
    }, param, "interface association descriptor")
    desc.content.wTotalLength = TotalLength
    return desc
end


function Function(param)
    local desc = CreateDescriptor({
        {bLength              = DUMMY                        },
        {bDescriptorType      = 0x24                         },
        {bDescriptorSubtype   = DUMMY                        },
    }, param, "function descriptor" )
    if param.name then
        desc.name = param.name
    end
    return desc
end



BulkDouble = 4
Bulk = 2
Interrupt = 3
ISO = 1
Control = 0
function IN(ep)
    return ((ep & 0x7f) | 0x80)
end
function OUT(ep)
    return ep & 0x7f
end

function EndPoint(param, attr, size, interval)
    if attr then
        return EndPoint{
            bEndpointAddress = param,
            bmAttributes = attr,
            wMaxPacketSize = size,
            bInterval = interval,
        }
    end
    
    local doubleBuffer = false
    if param.bmAttributes == BulkDouble then
        param.bmAttributes = Bulk
        doubleBuffer = true
    end
    
    local desc = CreateDescriptor({
        {bLength              = DUMMY                        },
        {bDescriptorType      = ENDPOINT_DESCRIPTOR_TYPE     }, 
        {bEndpointAddress     = DUMMY                        },
        {bmAttributes         = DUMMY                        },
        {wMaxPacketSize       = 64                           },
        {bInterval            = 1                            },
    },param , "endpoint descriptor")
    desc.content.hasDoubleBuffer = doubleBuffer
    return desc
end

function StringDescriptor(str)
    local varData = {}
    local i = 1
    if utf8.len(str) then
        for p,c in utf8.codes(str) do
            varData[#varData+1] = {
                ["wcChar"..(i-1)] = c
            }
            i = i + 1
        end
    else
        while i<=#str do
            if str:byte(i)>0x7f and i<#str then
                varData[#varData+1] = {
                    ["wcChar"..(i-1)] = str:byte(i) | (str:byte(i+1)<<8)
                }
                i = i + 1
            else
                varData[#varData+1] = {
                    ["wcChar"..(i-1)] = str:byte(i)
                }
            end
            i = i + 1
        end
    end
    local desc = CreateDescriptor({
        {bLength              = DUMMY                        },
        {bDescriptorType      = STRING_DESCRIPTOR_TYPE       }, 
    }, {varData = varData} , "string descriptor")
    desc.content.string = str
    return desc
end
