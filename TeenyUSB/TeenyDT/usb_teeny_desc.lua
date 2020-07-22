-- usb_teeny_desc.lua
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

require("usb_cdc_acm")
require("usb_hid")
require("usb_wcid20")

local epTypeStr = {
    [Control] =  "CONTROL",
    [ISO] = "ISO",
    [Interrupt] = "INTERRUPT",
    [Bulk] = "BULK",
}

function collecEpInfo(parent, maxEp, info)
    info = info or {}
    info.maxUsedEp = info.maxUsedEp or 0
    info.maxOutSize = info.maxOutSize or 0
    info.outEpNum = info.outEpNum or 0
    info.controlEpNum = info.controlEpNum or 1
    for i=0,maxEp do
        info[i] = info[i] or {}
    end
    if parent.content.bDescriptorType == ENDPOINT_DESCRIPTOR_TYPE then
        local epAddr = parent.content.bEndpointAddress & 0x7f
        local isIn = (parent.content.bEndpointAddress & 0x80) == 0x80
        local ep = info[epAddr]
        if not ep then
            warning("Endpoint " .. epAddr .. " is big than MAX ep, ignore it")
            return
        end

        if parent.content.bmAttributes == Control then
            if ep.in_size or ep.out_size then
            else
                info.controlEpNum = info.controlEpNum + 1
            end
        end

        ep.hasDoubleBuffer = ep.hasDoubleBuffer or parent.content.hasDoubleBuffer or (parent.content.bmAttributes == ISO)
        if info.maxUsedEp < epAddr then info.maxUsedEp = epAddr end
        if isIn then
            if ep.in_size then
                warning("Endpoint IN " .. epAddr .. " already used, the last one take effect")
            end
            ep.in_size = parent.content.wMaxPacketSize
            ep.in_type = epTypeStr[parent.content.bmAttributes]
        else
            if ep.out_size then
                warning("Endpoint OUT " .. epAddr .. " already used, the last one take effect")
            elseif parent.content.bmAttributes ~= Control then
                info.outEpNum = info.outEpNum + 1
            end
            ep.out_size = parent.content.wMaxPacketSize
            ep.out_type = epTypeStr[parent.content.bmAttributes]
            if info.maxOutSize < ep.out_size then info.maxOutSize = ep.out_size end
        end
    else
        for i,mybeEp in ipairs(parent.children) do
            collecEpInfo(mybeEp, maxEp, info)
        end
    end
    return info
end


local function init_ep_for_fs_core(dev, epInfo)
    local genCode = BeginGenCode(dev)
    local r = ""
    r = r .. genCode({}, [[
///////////////////////////////////////////////
//// Endpoint define for STM32 FS Core
///////////////////////////////////////////////

#ifdef $(PREFIX)BTABLE_ADDRESS
#undef $(PREFIX)BTABLE_ADDRESS
#endif
#define $(PREFIX)BTABLE_ADDRESS                                 (0)
#define $(PREFIX)EP_BUF_DESC_TABLE_SIZE                         (8)
// PMA buffer reserved for buffer description table
#define $(PREFIX)USB_BUF_START                                  ($(PREFIX)EP_BUF_DESC_TABLE_SIZE * $(PREFIX)EP_NUM)

]])

local offset = 0
local txMaxSize = ""
local rxMaxSize = ""
local epMaxSizeType = "uint8_t"
local fsEpInit = ""
for i=0,epInfo.maxUsedEp do
    local ep = epInfo[i]
    local doDouble = false
    if ep.hasDoubleBuffer then
        if ep.in_size and ep.out_size then
            warning("Endpoint " .. i .. ", double buffer feature will be disable")
        else
            doDouble = true
        end
    end

    r = r .. genCode({
        EP = i,
        RXOFF = offset,
        TXOFF = offset + (ep.out_size or 0),
        RXSIZE = ep.out_size or 0,
        TXSIZE = ep.in_size or 0,
        RXTYPE = ep.out_type or "Invalid",
        TXTYPE = ep.in_type or "Invalid",
        EPTYPE = ep.in_type or ep.out_type or "Invalid",
        DBOFF0 = offset,
        DBOFF1 = offset + (ep.out_size or ep.in_size or 0),
    },[[
// EndPoints $(EP) defines
#define $(PREFIX)EP$(EP)_RX_SIZE                                    ($(RXSIZE))
#define $(PREFIX)EP$(EP)_RX_ADDR                                    ($(PREFIX)USB_BUF_START + ($(RXOFF)))
#define $(PREFIX)EP$(EP)_TX_SIZE                                    ($(TXSIZE))
#define $(PREFIX)EP$(EP)_TX_ADDR                                    ($(PREFIX)USB_BUF_START + ($(TXOFF)))
#define $(PREFIX)EP$(EP)_RX_TYPE                                    USB_EP_$(RXTYPE)
#define $(PREFIX)EP$(EP)_TX_TYPE                                    USB_EP_$(TXTYPE)

#define $(PREFIX)EP$(EP)_TYPE                                       USB_EP_$(EPTYPE)
#define $(PREFIX)EP$(EP)_TX0_ADDR                                   ($(PREFIX)USB_BUF_START + ($(DBOFF0)))
#define $(PREFIX)EP$(EP)_TX1_ADDR                                   ($(PREFIX)USB_BUF_START + ($(DBOFF1)))
#define $(PREFIX)EP$(EP)_RX0_ADDR                                   ($(PREFIX)USB_BUF_START + ($(DBOFF0)))
#define $(PREFIX)EP$(EP)_RX1_ADDR                                   ($(PREFIX)USB_BUF_START + ($(DBOFF1)))

]])
    local mul = 1
    if doDouble then
        mul = 2
    end
    offset = offset + (ep.out_size or 0)*mul + (ep.in_size or 0)*mul
    txMaxSize = txMaxSize .. (ep.in_size and genCode({EP=i}, "$(PREFIX)EP$(EP)_TX_SIZE, ") or "0, ")
    rxMaxSize = rxMaxSize .. (ep.out_size and genCode({EP=i}, "$(PREFIX)EP$(EP)_RX_SIZE, ") or "0, ")
    if ep.in_size and ep.in_size > 255 then epMaxSizeType = "uint16_t" end
    if ep.out_size and ep.out_size > 255 then epMaxSizeType = "uint16_t" end

    local src = "/* Init ep$(EP) */ \\\n"

    if doDouble then
        epInfo.hasDoubleBuffer = true
        --fsInit = fsInit .. genCode
        if ep.in_size then
            src = src .. [[INIT_EP_TxDouble(dev, PCD_ENDP$(EP), $(PREFIX)EP$(EP)_TYPE);     \
SET_DOUBLE_ADDR(dev, PCD_ENDP$(EP), $(PREFIX)EP$(EP)_TX0_ADDR, $(PREFIX)EP$(EP)_TX1_ADDR);  \
SET_DBL_TX_CNT(dev, PCD_ENDP$(EP), 0);     \
]]
        else
            src = src .. [[INIT_EP_RxDouble(dev, PCD_ENDP$(EP), $(PREFIX)EP$(EP)_TYPE);     \
SET_DOUBLE_ADDR(dev, PCD_ENDP$(EP), $(PREFIX)EP$(EP)_RX0_ADDR, $(PREFIX)EP$(EP)_RX1_ADDR);  \
SET_DBL_RX_CNT(dev, PCD_ENDP$(EP), $(PREFIX)EP$(EP)_RX_SIZE);     \
]]
        end
    else
        if ep.in_size and ep.out_size then
            src = src ..[[INIT_EP_BiDirection(dev, PCD_ENDP$(EP), $(PREFIX)EP$(EP)_TYPE);  \
SET_TX_ADDR(dev, PCD_ENDP$(EP), $(PREFIX)EP$(EP)_TX_ADDR);  \
SET_RX_ADDR(dev, PCD_ENDP$(EP), $(PREFIX)EP$(EP)_RX_ADDR);  \
SET_RX_CNT(dev, PCD_ENDP$(EP), $(PREFIX)EP$(EP)_RX_SIZE);  \
]]
        elseif ep.in_size then
            src = src ..[[INIT_EP_TxOnly(dev, PCD_ENDP$(EP), $(PREFIX)EP$(EP)_TYPE);  \
SET_TX_ADDR(dev, PCD_ENDP$(EP), $(PREFIX)EP$(EP)_TX_ADDR);  \
]]
        elseif ep.out_size then
            src = src ..[[INIT_EP_RxOnly(dev, PCD_ENDP$(EP), $(PREFIX)EP$(EP)_TYPE);  \
SET_RX_ADDR(dev, PCD_ENDP$(EP), $(PREFIX)EP$(EP)_RX_ADDR);  \
SET_RX_CNT(dev, PCD_ENDP$(EP), $(PREFIX)EP$(EP)_RX_SIZE);  \
]]
        end
    end

    fsEpInit = fsEpInit .. genCode({EP = i}, src)

end

if offset > epInfo.maxMem then
    warning("Memory is too small for FS core, require " .. offset .. " bytes, provide " .. epInfo.maxMem .. " bytes")
end

r = r .. genCode({TXMAX = txMaxSize, RXMAX = rxMaxSize, SIZET=epMaxSizeType, FSEPINIT = Ident(fsEpInit, "    ")},[[

// EndPoint max packed sizes
extern const $(SIZET) $(PREFIX)txEpMaxSize[];
#define $(PREFIX)TXEP_MAX_SIZE                                  \
const $(SIZET) $(PREFIX)txEpMaxSize[] = \
{ $(TXMAX) };
extern const $(SIZET) $(PREFIX)rxEpMaxSize[];
#define $(PREFIX)RXEP_MAX_SIZE                                  \
const $(SIZET) $(PREFIX)rxEpMaxSize[] = \
{ $(RXMAX) };

// EndPoints init function for USB FS core
#define $(PREFIX)TUSB_INIT_EP_FS(dev) \
  do{\
$(FSEPINIT)}while(0)

]])

    return r
end

function init_ep_for_otg_core(dev, epInfo, coreType, maxMem, rxSize)
    local genCode = BeginGenCode(dev)
    local r = ""
    local sumIn = 0
    for i=0, epInfo.maxUsedEp do
        sumIn = sumIn + (epInfo[i].in_size or 0)
    end
    local remain = maxMem - rxSize
    local mul = math.floor(remain/sumIn)
    if remain < sumIn then
        warning("Remain FIFO("..remain..") is smaller than EP packet size("..sumIn..")")
        mul = 1
    end
    -- I don't know why the max count of fifo should <= 7 * EpMaxPacket
    -- But it seems the STM32F7xx can be large than 7
    if mul > 7 then mul = 7 end
    r = r .. genCode({RXSIZE = rxSize, CORE = coreType,
            SUMIN = sumIn,  REMAIN = remain, MUL = mul,
        }, [[

///////////////////////////////////////////////
//// Endpoint define for STM32 OTG $(CORE) Core
///////////////////////////////////////////////
#define $(PREFIX)OTG_RX_FIFO_SIZE_$(CORE)                            ($(RXSIZE))
#define $(PREFIX)OTG_RX_FIFO_ADDR_$(CORE)                            (0)
// Sum of IN ep max packet size is $(SUMIN)
// Remain Fifo size is $(REMAIN) in bytes, Rx Used $(RXSIZE) bytes 

// TODO:
// I don't know why the max count of TX fifo should <= (7 * EpMaxPacket)
// But it seems the STM32F7xx can be large than (7 * EpMaxPacket)
]])
    local offset = rxSize
    local otgEpInit= ""
    for i=0, epInfo.maxUsedEp do
        local ep = epInfo[i]
        if ep.in_size or ep.out_size then
            otgEpInit = otgEpInit .. "/* Init Ep"..i.."  */\\\n"
        end

        if ep.in_size then
            r = r .. genCode({EP = i, ADDR = offset, MUL = mul, CORE = coreType},[[
#define $(PREFIX)EP$(EP)_TX_FIFO_ADDR_$(CORE)                            ($(ADDR))
#define $(PREFIX)EP$(EP)_TX_FIFO_SIZE_$(CORE)                            ($(PREFIX)EP$(EP)_TX_SIZE * $(MUL))
]])
            offset = offset + ep.in_size * mul
            otgEpInit = otgEpInit .. genCode({CORE = coreType, EP = i},[[
INIT_EP_Tx(dev, PCD_ENDP$(EP), $(PREFIX)EP$(EP)_TX_TYPE, $(PREFIX)EP$(EP)_TX_SIZE);  \
SET_TX_FIFO(dev, PCD_ENDP$(EP), $(PREFIX)EP$(EP)_TX_FIFO_ADDR_$(CORE), $(PREFIX)EP$(EP)_TX_FIFO_SIZE_$(CORE));  \
]])
        end
        if ep.out_size then
            otgEpInit = otgEpInit .. genCode({CORE = coreType, EP = i},[[
INIT_EP_Rx(dev, PCD_ENDP$(EP), $(PREFIX)EP$(EP)_RX_TYPE, $(PREFIX)EP$(EP)_RX_SIZE); \
]])
        end
    end
    r = r .. genCode({CORE = coreType, BODY = Ident(otgEpInit, "      ")},[[
// EndPoints init function for USB OTG core
#if defined(USB_OTG_$(CORE))
#define $(PREFIX)TUSB_INIT_EP_OTG_$(CORE)(dev) \
  do{\
    if(GetUSB(dev) == USB_OTG_$(CORE)) { \
      SET_RX_FIFO(dev, $(PREFIX)OTG_RX_FIFO_ADDR_$(CORE), $(PREFIX)OTG_RX_FIFO_SIZE_$(CORE));  \
$(BODY)    }\
  }while(0)

#else  // #if defined(USB_OTG_$(CORE))
#define $(PREFIX)TUSB_INIT_EP_OTG_$(CORE)(dev) 
    
#endif  // #if defined(USB_OTG_$(CORE))
]])
    return r
end

-- generate descriptor header for teeny usb
function Generate_TeenyUSB_header(dev, maxEp, maxMem)
    if not maxEp then warning("Max endpoint number not set, default to 5") end
    if not maxMem then warning("Max USB memory not set, default to 512") end
    maxEp = maxEp or 5
    maxMem = maxMem or 512
    local genCode = BeginGenCode(dev)
    local epInfo = collecEpInfo(dev, maxEp)
    epInfo[0] = {
        in_size = dev.content.bMaxPacketSize,
        out_size = dev.content.bMaxPacketSize,
        in_type = "CONTROL",
        out_type = "CONTROL",
    }
    epInfo.maxMem = maxMem
    local r = ""
    local pwr = (dev.children[1].content.bmAttributes & 0x40) ~= 0 
    pwr = pwr and "USB_CONFIG_SELF_POWERED" or "0"
    local rmt = (dev.children[1].content.bmAttributes & 0x20) ~= 0 
    rmt = rmt and "USB_CONFIG_REMOTE_WAKEUP" or "0"
    r = r .. genCode({
        VID = string.format("0x%04x", dev.content.idVendor),
        PID = string.format("0x%04x", dev.content.idProduct),
        STRSIZE = #dev.strings + 1,
        MAXEP = epInfo.maxUsedEp,
        STATUS =  pwr .. " | " .. rmt,
    }, [[
#ifndef __$(PREFIX)TEENY_USB_INIT_H__
#define __$(PREFIX)TEENY_USB_INIT_H__
// forward declare the tusb_descriptors struct
typedef struct _tusb_descriptors tusb_descriptors;

#define $(PREFIX)VID                                            $(VID)
#define $(PREFIX)PID                                            $(PID)
#define $(PREFIX)STRING_COUNT                                   ($(STRSIZE))

// device.bmAttributes & 0x40   USB_CONFIG_SELF_POWERED
// device.bmAttributes & 0x20   USB_CONFIG_REMOTE_WAKEUP
#define $(PREFIX)DEV_STATUS                                    ($(STATUS))


// Endpoint usage:
#define $(PREFIX)MAX_EP                                         ($(MAXEP))
#define $(PREFIX)EP_NUM                                         ($(PREFIX)MAX_EP + 1)

]])
    r = r .. init_ep_for_fs_core(dev, epInfo)

    epInfo.calcRxFifo = epInfo.controlEpNum * 5 + 8 + (epInfo.maxOutSize/4 + 1) + epInfo.outEpNum * 2 + 1
    epInfo.calcRxFifo = math.floor(epInfo.calcRxFifo)
    r = r .. genCode(epInfo,[[
///////////////////////////////////////////////
//// Endpoint define for STM32 OTG Core
///////////////////////////////////////////////
#define $(PREFIX)OTG_MAX_OUT_SIZE                               ($(maxOutSize))
#define $(PREFIX)OTG_CONTROL_EP_NUM                             ($(controlEpNum))
#define $(PREFIX)OTG_OUT_EP_NUM                                 ($(outEpNum))
// RX FIFO size / 4 > (CONTROL_EP_NUM * 5 + 8) +  (MAX_OUT_SIZE / 4 + 1) + (OUT_EP_NUM*2) + 1 = $(calcRxFifo)
]])
    local calcRxFifo = epInfo.calcRxFifo * 4

    r = r .. init_ep_for_otg_core(dev, epInfo, "FS", 1280, calcRxFifo < 256 and 256 or calcRxFifo)
    r = r .. init_ep_for_otg_core(dev, epInfo, "HS", 4096, calcRxFifo < 512 and 512 or calcRxFifo)

    r = r .. genCode({},[[
#define $(PREFIX)TUSB_INIT_EP_OTG(dev) \
  do{\
    $(PREFIX)TUSB_INIT_EP_OTG_FS(dev); \
    $(PREFIX)TUSB_INIT_EP_OTG_HS(dev); \
  }while(0)


#if defined(USB)
#define $(PREFIX)TUSB_INIT_EP(dev) $(PREFIX)TUSB_INIT_EP_FS(dev)

// Teeny USB device init function for FS core
#define $(PREFIX)TUSB_INIT_DEVICE(dev) \
  do{\
    /* Init device features */       \
    memset(&dev->addr, 0, TUSB_DEVICE_SIZE);    \
    dev->status = $(PREFIX)DEV_STATUS;         \
    dev->rx_max_size = $(PREFIX)rxEpMaxSize;         \
    dev->tx_max_size = $(PREFIX)txEpMaxSize;         \
    dev->descriptors = &$(PREFIX)descriptors;         \
  }while(0)

#endif

#if defined(USB_OTG_FS) || defined(USB_OTG_HS)
#define $(PREFIX)TUSB_INIT_EP(dev) $(PREFIX)TUSB_INIT_EP_OTG(dev)

// Teeny USB device init function for OTG core
#define $(PREFIX)TUSB_INIT_DEVICE(dev) \
  do{\
    /* Init device features */       \
    memset(&dev->addr, 0, TUSB_DEVICE_SIZE);    \
    dev->status = $(PREFIX)DEV_STATUS;         \
    dev->descriptors = &$(PREFIX)descriptors;         \
  }while(0)

#endif

#define $(PREFIX)TUSB_INIT(dev) \
  do{\
    $(PREFIX)TUSB_INIT_EP(dev);   \
    $(PREFIX)TUSB_INIT_DEVICE(dev);   \
  }while(0)

// Get End Point count
#ifndef  EP_NUM
#define  EP_NUM 1
#endif
#if $(PREFIX)EP_NUM > EP_NUM
#undef   EP_NUM
#define  EP_NUM  $(PREFIX)EP_NUM
#endif

]])

    if epInfo.hasDoubleBuffer then
        r = r .. genCode({},[[
// Enable double buffer related code
#define  HAS_DOUBLE_BUFFER

]])
    end

    r = r .. genCode({},[[
extern const uint8_t* const $(PREFIX)StringDescriptors[$(PREFIX)STRING_COUNT];
extern const tusb_descriptors $(PREFIX)descriptors;

]])
    local hasWCID = false
    for i,v in ipairs(dev.extDesc) do
        if isWCID(v) then
            hasWCID = true
        elseif v.handler then
            r = r .. v.handler(dev, v, true)
        end
    end

    if hasWCID then
        hasWCID = dev.content.bcdUSB > 0x200 and "HAS_WCID_20" or "HAS_WCID"
        r = r .. genCode({WCID = hasWCID},[[
// Enable WCID related code
#define  $(WCID)

#ifndef WCID_VENDOR_CODE
#define  WCID_VENDOR_CODE       0x17
extern const uint8_t WCID_StringDescriptor_MSOS[];
#endif

]])
    end
    r = r .. genCode({},"\n#endif   // #ifndef __$(PREFIX)TEENY_USB_INIT_H__\n")
    return r
end




-- generate descriptor for teeny usb
function Generate_TeenyUSB_desc(dev)
    local r = [[
#include "teeny_usb.h"

]]
    local genCode = BeginGenCode(dev)
    r = r .. genCode({
        SIZE = fieldValue(dev, "bLength"),
        BODY = Ident(descToString(dev)) }, [[
#define  $(PREFIX)DEVICE_DESCRIPTOR_SIZE  ($(SIZE))
__ALIGN_BEGIN  const uint8_t $(PREFIX)DeviceDescriptor [$(SIZE)] __ALIGN_END = {
$(BODY)};
]])

-- generate config descriptor
    for i,v in ipairs(dev.children) do
        r = r .. genCode({
            SIZE = fieldValue(v, "wTotalLength"), 
            BODY = Ident(descToString(v, true)),
            ID = #dev.children > 1 and (i-1) or ""}, [[
#define  $(PREFIX)CONFIG$(ID)_DESCRIPTOR_SIZE  ($(SIZE))
__ALIGN_BEGIN  const uint8_t $(PREFIX)ConfigDescriptor$(ID) [$(SIZE)] __ALIGN_END = {
$(BODY)};
]])
    end
-- generate string descriptors
    local strDef = genCode({}, "$(PREFIX)StringDescriptor0,\n")
    r = r .. genCode({SIZE=4}, [[
#define  $(PREFIX)STRING_DESCRIPTOR0_STR   "\x09\x04"
#define  $(PREFIX)STRING_DESCRIPTOR0_SIZE  ($(SIZE))
WEAK __ALIGN_BEGIN  const uint8_t $(PREFIX)StringDescriptor0 [$(SIZE)] __ALIGN_END = {
  0x04,                                         /* bLength */
  USB_STRING_DESCRIPTOR_TYPE,                   /* bDescriptorType */
  0x09, 0x04,                                   /* wLangID0 */
};
]])

    
    for i,v in ipairs(dev.strings) do
        local desc = StringDescriptor(v)
        r = r .. genCode({
            SIZE = fieldValue(desc, "bLength"),
            BODY = Ident (descToString(desc, false, true)) ,
            ID = i,
            STR = v},[[
#define  $(PREFIX)STRING_DESCRIPTOR$(ID)_STR   "$(STR)"
#define  $(PREFIX)STRING_DESCRIPTOR$(ID)_SIZE   ($(SIZE))
WEAK __ALIGN_BEGIN  const uint8_t $(PREFIX)StringDescriptor$(ID) [$(SIZE)] __ALIGN_END = {
$(BODY)};
]])
        strDef = strDef .. genCode({ID=i}, "$(PREFIX)StringDescriptor$(ID),\n")
    end
    r = r .. genCode({SIZE = #dev.strings + 1, BODY = Ident(strDef) }, [[
#define $(PREFIX)STRING_COUNT    ($(SIZE))
const uint8_t* const $(PREFIX)StringDescriptors[$(SIZE)] = {
$(BODY)};
]])
    -- find ext descriptors
    for i, v in ipairs(dev.extDesc) do
        if type(v.handler) == "function" then
            r = r .. v.handler(dev, v)
        else
            error("unknown extra descriptor type " .. tostring(v.type))
        end
    end


    r = r .. genCode({},[[


$(PREFIX)TXEP_MAX_SIZE
$(PREFIX)RXEP_MAX_SIZE
//  Device descriptors
const tusb_descriptors $(PREFIX)descriptors = {
  .device = $(PREFIX)DeviceDescriptor,
  .config = $(PREFIX)ConfigDescriptor,
  .strings = $(PREFIX)StringDescriptors,
  .string_cnt = $(PREFIX)STRING_COUNT,
#if defined(HAS_WCID)
#if defined($(PREFIX)WCID_DESCRIPTOR_SIZE)
  .wcid_desc = $(PREFIX)WCIDDescriptor,
#else
  .wcid_desc = 0,
#endif // $(PREFIX)WCID_DESCRIPTOR_SIZE)

#if defined($(PREFIX)WCID_PROPERTIES_SIZE)
  .wcid_properties = $(PREFIX)WCIDProperties,
#else
  .wcid_properties = 0,
#endif // $(PREFIX)WCID_PROPERTIES_SIZE

#endif // HAS_WCID

#if defined(HAS_WCID_20)
#if defined($(PREFIX)WCID_BOS_SIZE)
  .wcid_bos = $(PREFIX)WCIDBOS,
#else
  .wcid_bos = 0,  
#endif // $(PREFIX)WCID_BOS_SIZE)

#if defined($(PREFIX)WCID_DESC_SET_SIZE)
  .wcid_desc_set = $(PREFIX)WCIDDescriptorSet,
#else
  .wcid_desc_set = 0,  
#endif // $(PREFIX)WCID_DESC_SET_SIZE


#endif // HAS_WCID_20
};
]])
    return r
end