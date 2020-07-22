-- usb_wcid.lua
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

require("usb_desc_base")

function MSOSString(vendorCode)
     vendorCode = vendorCode or 1
     local desc = CreateDescriptor({
          { bLength         =  DUMMY                     },
          { bDescriptorType =  STRING_DESCRIPTOR_TYPE    },
          { wcChar_7        =  "MSFT100"                 },
          { bVendorCode     = vendorCode                 },
          { bReserved       = 0                          },
     }, {varData = varData}, "MS OS string descriptor")
     return desc
 end

function WCIDFunction(bInterface, CID, subCID)
     CID = CID or ""
     subCID = subCID or ""
     assert(#CID<9, "Compatible ID too long  >> " .. CID)
     assert(#subCID<9, "sub Compatible ID too long  >> " .. subCID)
     CID = CID .. string.rep("\x00", 8-#CID)
     subCID = subCID .. string.rep("\x00", 8-#subCID)

     local desc = CreateDescriptor({
          {bFirstInterfaceNumber   =  bInterface        },
          {bReserved               =  1                 },
          {cCID_8                   = CID                },
          {cSubCID_8                = subCID             },
          {bReserved_6              = ""                 },
     }, {}, "WCID function descriptor")
     return desc
end


function WCIDDescriptor(param)
     local desc = CreateDescriptor({
          {dwLength      =  TotalLength       },
          {bcdVersion    =  0x100             },
          {wIndex        =  4                 },
          {bCount        =  #param            },
          {bReserved_7   = ""                 },
     }, param, "WCID descriptor")
     return desc
end



REG_SZ                   = 1
REG_EXPAND_SZ            = 2
REG_BINARY               = 3
REG_DWORD_LITTLE_ENDIAN  = 4
REG_DWORD_BIG_ENDIAN     = 5
REG_LINK                 = 6
REG_MULTI_SZ             = 7


function uniLength(str)
     local r = 0
     local i = 1
     while i<=#str do
          if str:byte(i) < 0x80 then
               r = r + 2
               i = i + 1
          else
               i = i + 2
               r = r + 2
          end
     end
     return r
end

function RegProptery(type, name, data)
     local nameLen = uniLength(name)
     local dataLen = uniLength(data)

     local desc = CreateDescriptor({
          { dwSize              = TotalLength        },
          { dwPropertyDataType  = type               },
          { wPropertyNameLength = nameLen            },
          { ["wcName_" .. (nameLen/2 | 0)]  = name   },
          { dwPropertyDataLength = dataLen           },
          { ["wcData_" .. (dataLen/2 | 0)]  = data   },
     }, {}, "registry propter descriptor")
     return desc
end


function RegSZ(name, data)
     assert(type(data) == "string", "Reg SZ data must be string")
     if name:byte(#name) ~= 0 then
          name = name .. "\x00"
     end

     if data:byte(#data) ~= 0 then
          data = data .. "\x00"
     end
     return RegProptery(REG_SZ, name , data)
end

function RegMultiSZ(name, data)
     local r = ""
     assert(type(data) == "table", "Reg Multi SZ data must be string")
     if name:byte(#name) ~= 0 then
          name = name .. "\x00"
     end
     for i,v in ipairs(data) do
          assert(type(v) == "string", "Reg SZ data must be string")
          if v:byte(#v) ~= 0 then
               v = v .. "\x00"
          end
          r = r .. v
     end
     r = r .. "\x00"
     return RegProptery(REG_MULTI_SZ, name , r)
end

function WCIDRegValue(name, data)
     if type(data) == "table" then
          return RegMultiSZ(name ,data)
     else
          return RegSZ(name, data)
     end
end

function WCIDProperty(param)
     local desc = CreateDescriptor({
          {dwLength   = TotalLength   },
          {bcdVersion = 0x100         },
          {wIndex     =  0x05         },
          {wCount     = #param        },
     }, param, "WCID property descriptor")
     return desc
end

function isWCID(v)
     return v.type == "WinUSB" or v.type == "RNDIS"
end

function MakeWinUSB(dev, extDesc)
     local min = 0xff
     for i,v in ipairs(dev.extDesc) do
          if isWCID(v) and v.interface.content.bInterfaceNumber < min then
               min = v.interface.content.bInterfaceNumber
          end
     end
     if extDesc.interface.content.bInterfaceNumber == min then
          -- this is the first WinUSB interface, output them
          assert(dev.content.bcdUSB>= 0x200, "WinUSB require USB version >= 2.00")
          if dev.content.bcdUSB > 0x200 then
               return OutputWinUSB20Info(dev)
          end
          return OutputWinUSBInfo(dev)
     end
     return ""
end

function WinUSB(guid)
     return {
          type = "WinUSB",
          data = guid,
          handler = MakeWinUSB,
     }
end

function RNDIS(subCID)
    return {
          type = "RNDIS",
          handler = MakeWinUSB,
          subCID = subCID,
     }
end

function GetWinUSBInterface(dev)
     local r = {}
     for i=1,dev.children[1].content.bNumInterfaces do
          r[i] = {}
     end
     for i,v in ipairs(dev.extDesc) do
          if isWCID(v) then
               r[v.interface.content.bInterfaceNumber + 1] = v
          end
     end
     return r
end

function OutputWinUSBInfo(dev)
     local r = ""
     local genCode = BeginGenCode(dev)
     r = r .. genCode({
          BODY = Ident(  descToString(MSOSString("WCID_VENDOR_CODE")) )
     },[[

//////////////////////////////////////////////////////
///// WCID descripors
//////////////////////////////////////////////////////
#if defined(HAS_WCID)

// Define WCID os string descriptor 
#ifndef WCID_MSOS_STRING
#define WCID_MSOS_STRING
#define WCID_STRING_DESCRIPTOR_MSOS_STR          "MSFT100"
#define WCID_STRING_DESCRIPTOR_MSOS_SIZE          (18)
WEAK __ALIGN_BEGIN const uint8_t  WCID_StringDescriptor_MSOS [18] __ALIGN_END = {
$(BODY)};

#endif // WCID_MSOS_STRING
]])

     local funcs = {}
     local properties = ""
     local ifs = GetWinUSBInterface(dev)
     for i,v in ipairs(ifs) do
          if v.type == "WinUSB" then
               funcs[#funcs+1] = WCIDFunction(v.interface.content.bInterfaceNumber, "WINUSB")
               local prop = WCIDProperty{ WCIDRegValue("DeviceInterfaceGUID", v.data or "{1D4B2365-4749-48EA-B38A-7C6FDDDD7E26}"), }
               r = r .. genCode({
                    SIZE = fieldValue(prop, "dwLength"),
                    ID = (i-1),
                    BODY = Ident( descToString(prop, true) )
               }, [[
#define  $(PREFIX)IF$(ID)_WCID_PROPERTIES_SIZE  ($(SIZE))
WEAK __ALIGN_BEGIN const uint8_t $(PREFIX)IF$(ID)_WCIDProperties [$(SIZE)] __ALIGN_END = {
$(BODY)};
]])
               properties = properties .. genCode({ID = (i-1),}, "$(PREFIX)IF$(ID)_WCIDProperties,\n")
          elseif v.type == "RNDIS" then
               funcs[#funcs+1] = WCIDFunction(v.interface.content.bInterfaceNumber, "RNDIS", v.subCID)
               properties = properties .. "0,    // No WCID in Interface " ..(i-1) .."\n"
          else
               properties = properties .. "0,    // No WCID in Interface " ..(i-1) .."\n"
          end
     end

     local wcidDesc = WCIDDescriptor(funcs)
     r = r .. genCode({
          SIZE = fieldValue(wcidDesc, "dwLength"),
          BODY = Ident( descToString(wcidDesc, true) )
     },[[
#define  $(PREFIX)WCID_DESCRIPTOR_SIZE  ($(SIZE))
WEAK __ALIGN_BEGIN const uint8_t $(PREFIX)WCIDDescriptor [$(SIZE)] __ALIGN_END = {
$(BODY)};
]])
     r = r .. genCode({
          SIZE = #ifs,
          BODY = Ident( properties )
     },[[
#define $(PREFIX)WCID_PROPERTIES_SIZE ($(SIZE))
WEAK __ALIGN_BEGIN const desc_t $(PREFIX)WCIDProperties[ $(PREFIX)WCID_PROPERTIES_SIZE ] __ALIGN_END = {
$(BODY)};
]])

r = r .. [[
#endif    // #if defined(HAS_WCID)
]]
     return r
end
