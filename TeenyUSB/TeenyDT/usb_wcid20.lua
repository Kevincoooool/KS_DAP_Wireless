-- usb_wcid20.lua
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
     Windows compatible ID related descriptors
     visit https://github.com/xtoolbox/TeenyUSB/wiki/WCID-Device for more info
--]]

require("usb_wcid")

local WIN8_1   = 0x06030000

function WCID20DeviceCapDescriptor(param)
    local uuid = param.uuid or  {0xDF, 0x60, 0xDD, 0xD8,
    0x89, 0x45, 0xC7, 0x4C,
    0x9C, 0xD2, 0x65, 0x9D,
    0x9E, 0x64, 0x8A, 0x9F,}
    local desc = CreateDescriptor({
        { bLength            = DUMMY         },
        { bDescriptorType    = 0x10          },
        { bDevCapabilityType = 0x05          },
        { bReserved          = 0x00          },
        { bPlatformCapabilityUUID_16 = uuid  },
        { dwWindowsVersion   = WIN8_1        },
        { wDescriptorSetTotalLength = 0      },
        { bVendorCode  = 1                   },
        { bAltEnumCode = 0                   },
    },param, "WCID20 device capability descriptor")
    return desc
end

function WCID20BOSDescriptor(param)
    local desc = CreateDescriptor({
        { bLength          = DUMMY               },
        { bDescriptorType  = BOS_DESCRIPTOR_TYPE },
        { wTotalLength     = TotalLength         },
        { bNumDeviceCaps   = #param              },
    }, param, "WCID20 BOS descriptor")
    return desc
end

function WCID20CompatibleID(CID, subCID)
    CID = CID or "WINUSB"
    subCID = subCID or ""
    assert(#CID<9, "Compatible ID too long  >> " .. CID)
    assert(#subCID<9, "sub Compatible ID too long  >> " .. subCID)
    CID = CID .. string.rep("\x00", 8-#CID)
    subCID = subCID .. string.rep("\x00", 8-#subCID)

    local desc = CreateDescriptor({
        { wLength          = TotalLength         },
        { wDescriptorType  = 3                   },
        { cCID_8           = CID                 },
        { cSubCID_8        = subCID              },
    }, {}, "WCID20 compatible ID descriptor")
    return desc
end


function WCID20RegValue(name, data)
    local dType = REG_SZ
    if name:byte(#name) ~= 0 then
        name = name .. "\x00"
    end
    if type(data) == "table" then
        dType = REG_MULTI_SZ
        local t = ""
        for i,v in ipairs(data) do
            assert(type(v) == "string")
            if v:byte(#v) ~= 0 then
                v = v .. "\x00"
            end
            t = t .. v
        end
        data = t .. "\x00"
    elseif type(data) == "string" then
        if data:byte(#data) ~= 0 then
            data = data .. "\x00"
        end
    end

    local nameLen = uniLength(name)
    local dataLen = uniLength(data)
    local nameField = "wcPropertyName_" .. (nameLen/2 | 0)
    local dataField = "wcPropertyData_" .. (dataLen/2 | 0)

    local desc = CreateDescriptor({
        { wLength              = TotalLength   },
        { wDescriptorType      = 4             },
        { wPropertyDataType    = dType         },
        { wPropertyNameLength  = nameLen       },
        { [nameField]          = name          },
        { wPropertyDataLength  = dataLen       },
        { [dataField]          = data          }
    }, {}, "WCID20 registry property descriptor")
    return desc
end

function WCID20FunctionSubset(param)
    local desc = CreateDescriptor({
        { wLength          = 0                    },
        { wDescriptorType  = 2                    },
        { bFirstInterface  = param.interface or 0 },
        { bReserved        =  0                   },
        { wSubsetLength    = TotalLength          },
    }, param, "WCID20 function subset descriptor")
    desc.content.wLength = desc.content.bLength
    desc.content.wTotalLength = TotalLength
    return desc
end

function WCID20DescriptorSet(param)
    local desc = CreateDescriptor({
        { wLength                    = 0           },
        { wDescriptorType            = 0           },
        { dwWindowsVersion           = WIN8_1      },
        { wDescriptorSetTotalLength  = TotalLength },

    },param, "WCID20 descriptor set descriptor")
    desc.content.wLength = desc.content.bLength
    return desc
end


function OutputWinUSB20Info(dev)
    local r = [[
//////////////////////////////////////////////////////
///// WCID 2.0 descripors
/////////////////////////////////////////////////////
#if defined(HAS_WCID_20)

]]
    local genCode = BeginGenCode(dev)
    local ifs = GetWinUSBInterface(dev)
    local data = {}
    for i,v in ipairs(ifs) do
        if #ifs > 1 then
            if v.type == "WinUSB" then
                data[#data+1] = WCID20FunctionSubset{
                    interface = v.interface.content.bInterfaceNumber,
                    WCID20CompatibleID("WINUSB"),
                    WCID20RegValue("DeviceInterfaceGUIDs", {v.data}),
                }
            elseif v.type == "RNDIS" then
                data[#data+1] = WCID20FunctionSubset{
                    interface = v.interface.content.bInterfaceNumber,
                    WCID20CompatibleID("RNDIS", v.subCID),
                }
            end
        else
            if v.type == "RNDIS" then
                data = {
                    WCID20CompatibleID("RNDIS", v.subCID),
                }

            else
                data = {
                    WCID20CompatibleID("WINUSB"),
                    WCID20RegValue("DeviceInterfaceGUIDs", {v.data}),
                }
            end
        end
    end
    local set = WCID20DescriptorSet(data)
    r = r .. genCode({
        SIZE = fieldValue(set, "wDescriptorSetTotalLength"),
        BODY = Ident( descToString(set, true) )
    },[[
#define  $(PREFIX)WCID_DESC_SET_SIZE  ($(SIZE))
WEAK __ALIGN_BEGIN const uint8_t $(PREFIX)WCIDDescriptorSet [$(SIZE)] __ALIGN_END = {
$(BODY)};
]])

    local bos = WCID20BOSDescriptor{
        WCID20DeviceCapDescriptor{
            bVendorCode = "WCID_VENDOR_CODE",
            wDescriptorSetTotalLength = genCode({}, "$(PREFIX)WCID_DESC_SET_SIZE")
        }
    }

    r = r .. genCode({
        SIZE = fieldValue(bos, "wTotalLength"),
        BODY = Ident( descToString(bos, true) )
    },[[
#define  $(PREFIX)WCID_BOS_SIZE  ($(SIZE))
WEAK __ALIGN_BEGIN const uint8_t $(PREFIX)WCIDBOS [$(SIZE)] __ALIGN_END = {
$(BODY)};


#endif    // #if defined(HAS_WCID_20)
]])

    return r
end