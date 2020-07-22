-- usb_opencm3_desc.lua
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
require("usb_teeny_desc")

local function fv(desc,field)
    local r = fieldValue(desc, field)
    if type(r) == "string" then return r end
    local s = fieldSize(field)
    if s <= 4 then s = s * 2
    else return "Not support"
    end
    return string.format("0x%0"..s.."x", tonumber(r))
end

local desc_filter = {
    [DEVICE_DESCRIPTOR_TYPE] = function (s)
        s = s:gsub("bMaxPacketSize", "bMaxPacketSize0")
        s = s:gsub("iSerial", "iSerialNumber")
        return s
    end,
}

local function filter(desc, s)
    local f1 = desc_filter[desc.content.bDescriptorType]
    if f1 then
        s = f1(s)
    end
    s = s:gsub("USB_([A-Z]+)_DESCRIPTOR_TYPE", "USB_DT_%1")
    s = s:gsub("USB_DT_IAD", "USB_DT_INTERFACE_ASSOCIATION")
    return s
end

local function output_desc_filed(desc)
    local r = ""
    for i,v in ipairs(desc.layout) do
        r = r .. "." .. v .. " = " .. fv(desc,v) .. ",\n"
    end
    return filter(desc, r)
end


local function makeItf(dev, itf, cfg)
    local r = ""
    local genCode = BeginGenCode(dev)
    local epData = ""
    local extData = ""
    local extLength = 0
    local CFG = cfg.content.bConfigurationValue
    local IFN = itf.content.bInterfaceNumber
    for k, mayEp in ipairs(itf.children) do
        if mayEp.content.bDescriptorType == ENDPOINT_DESCRIPTOR_TYPE then
            epData = epData .. genCode({ 
                BODY =  Ident( output_desc_filed(mayEp), "    " ) },
                "  {\n$(BODY)  },\n")
        else
            extLength = extLength + fieldValue(mayEp, "bLength")
            extData = extData .. descToString(mayEp)
        end
    end
    r = r .. genCode({BODY=epData, CFG = CFG, IFN = IFN},[[
static const struct usb_endpoint_descriptor $(PREFIX)config$(CFG)_itf$(IFN)_endpoints[] = {
$(BODY)
};

]])
    if extLength>0 then
    r = r .. genCode({BODY= Ident(extData, "  "), SIZE = extLength, CFG = CFG, IFN = IFN},[[
#define $(PREFIX)config$(CFG)_itf$(IFN)_extra_size ($(SIZE))
static const uint8_t $(PREFIX)config$(CFG)_itf$(IFN)_extra[$(SIZE)] = {
$(BODY)
};

]])
    end
    r = r .. genCode({BODY = Ident(output_desc_filed(itf), "    "), CFG = CFG, IFN = IFN,
        EP = #epData>0 and genCode({CFG = CFG, IFN = IFN}, "$(PREFIX)config$(CFG)_itf$(IFN)_endpoints") or "NULL", 
        EXT = extLength>0 and genCode({CFG = CFG, IFN = IFN}, "$(PREFIX)config$(CFG)_itf$(IFN)_extra") or "NULL",
        EXTLEN = extLength,
    },[[
static const struct usb_interface_descriptor $(PREFIX)config$(CFG)_itf$(IFN) = {
$(BODY)
    .endpoint = $(EP),
    .extra = $(EXT),
    .extralen = $(EXTLEN),
};
]])
    return r
end

function Generate_LibOpenCM3_desc(dev)
    local r = ""
    local genCode = BeginGenCode(dev)
    r = r .. genCode({BODY = Ident( output_desc_filed(dev), "    " ) },[[
#include "opencm3_usb_init.h"
#include "trace.h"
#include "string.h"

#ifndef NULL
#define NULL 0
#endif

#ifndef WEAK
#define WEAK
#endif

#ifndef __ALIGN_BEGIN
#define __ALIGN_BEGIN
#endif

#ifndef __ALIGN_END
#define __ALIGN_END
#endif

#define ER_DEBUG
#ifdef ER_DEBUG
#include <stdio.h>
#define ER_DPRINTF(fmt, ...) \
	do { printf(fmt, ## __VA_ARGS__); } while (0)
#else
#define ER_DPRINTF(fmt, ...) \
	do { } while (0)
#endif

struct usb_endpoint_init{
    uint8_t addr;
    uint8_t type;
    uint16_t size;
    void (*cb)(usbd_device *, uint8_t);
};

typedef const uint8_t* desc_t;

static const struct usb_device_descriptor $(PREFIX)dev_desc = {
$(BODY)};
]])

    local cfg_data = ""
    local ep_init_data = ""
    for i,cfg in ipairs(dev.children) do
        local CFG = cfg.content.bConfigurationValue
        local itf_data = ""
        for j, if_or_iad in ipairs(cfg.children) do
            if if_or_iad.content.bDescriptorType == IAD_DESCRIPTOR_TYPE then
                local ASN = fieldValue(if_or_iad, "bFirstInterface")
                r = r .. genCode({BODY = Ident(output_desc_filed(if_or_iad), "   "), CFG = CFG, ASN = ASN},[[
static const struct usb_iface_assoc_descriptor $(PREFIX)config$(CFG)_assoc$(ASN) = {
$(BODY)};
]])
                for _k, itf in ipairs(if_or_iad.children) do
                    local IFN = itf.content.bInterfaceNumber
                    r = r .. makeItf(dev, itf, cfg)
                    itf_data = itf_data .. genCode({CFG = CFG, ASN = ASN, IFN = IFN},
                    "  {\n    .num_altsetting = 1,\n    .altsetting = &$(PREFIX)config$(CFG)_itf$(IFN),\n")
                    if IFN == ASN then
                        itf_data = itf_data .. genCode({CFG = CFG, ASN = ASN, IFN = IFN},
                        "    .iface_assoc = &$(PREFIX)config$(CFG)_assoc$(ASN),\n")
                    end
                    itf_data = itf_data .. "  },\n"
                end
            else
                local IFN = if_or_iad.content.bInterfaceNumber
                r = r .. makeItf(dev, if_or_iad, cfg)
                itf_data = itf_data .. genCode({CFG = CFG, IFN = IFN},
                    "  {\n    .num_altsetting = 1,\n    .altsetting = &$(PREFIX)config$(CFG)_itf$(IFN),\n  },\n")
            end
        end
        r = r .. genCode({BODY = itf_data, CFG = CFG}, [[
static const struct usb_interface $(PREFIX)config$(CFG)_interfaces[] = {
$(BODY)};
]])
        cfg_data = cfg_data .. genCode({BODY = Ident(output_desc_filed(cfg), "    "), CFG=CFG }, [[  {
$(BODY)
    .interface = $(PREFIX)config$(CFG)_interfaces,
  },
]])
        local epInfo = collecEpInfo(cfg, 16)
        local epCnt = 0
        local epInit = ""
        for i=1,epInfo.maxUsedEp do
            local ep = epInfo[i]
            if ep.in_size then
                epInit = epInit .. string.format("    { .addr = 0x%02x, .type = USB_ENDPOINT_ATTR_%s, .size = %d, .cb = NULL },\n",
                    i | 0x80, ep.in_type, ep.in_size)
                epCnt = epCnt + 1
            end
            if ep.out_size then
                epInit = epInit .. string.format("    { .addr = 0x%02x, .type = USB_ENDPOINT_ATTR_%s, .size = %d, .cb = NULL },\n",
                    i & 0x7f, ep.out_type, ep.out_size)
                epCnt = epCnt + 1
            end
        end
        r = r .. genCode({BODY = epInit, CFG=CFG, SIZE = epCnt},[[
#define $(PREFIX)config$(CFG)_ep_count        ($(SIZE))
static const struct usb_endpoint_init $(PREFIX)config$(CFG)_ep_init[$(SIZE)] = {
$(BODY)};
]])
        ep_init_data = ep_init_data .. genCode({BODY = epInit, CFG=CFG, SIZE = epCnt}, [[
  {
    .len = $(PREFIX)config$(CFG)_ep_count,
    .ep_inits = $(PREFIX)config$(CFG)_ep_init,
  },
]])
    end
    r = r .. genCode({BODY = cfg_data},[[
static const struct usb_config_descriptor $(PREFIX)config[] = {
$(BODY)};
]])


    local strs = '    "'..table.concat(dev.strings, '",\n    "')..'"\n'

    local extraDesc = ""

    for i, v in ipairs(dev.extDesc) do
        if type(v.handler) == "function" then
            extraDesc = extraDesc .. v.handler(dev, v)
        else
            error("unknown extra descriptor type " .. tostring(v.type))
        end
    end

    r = r .. genCode({BODY = strs, EPINIT = ep_init_data, EXTDESC = filter(dev,extraDesc) }, [[
/////////////////////////////////////////////
// String descriptors
/////////////////////////////////////////////

static const char * $(PREFIX)usb_strings[] = {
$(BODY)};

/////////////////////////////////////////////
// Extra descriptors
/////////////////////////////////////////////
#if defined(HAS_WCID_20)
#define HIBYTE(v)    ( (uint8_t)((v)>>8))
#define LOBYTE(v)    ( (uint8_t)((v)&0xff))
#define USB_DESC_TYPE_BOS    0x0f
#endif

$(EXTDESC)

/////////////////////////////////////////////
// USB init code
/////////////////////////////////////////////

const struct {
    int len;
    const struct usb_endpoint_init* ep_inits;
}$(PREFIX)ep_init_map[] = {
$(EPINIT)};

#define ARR_SIZE(x)   (sizeof(x)/sizeof((x)[0]))

static ep_cb_t $(PREFIX)ep_in_handler;
static ep_cb_t $(PREFIX)ep_out_handler;

static enum usbd_request_return_codes $(PREFIX)WCID_control_request(usbd_device *usbd_dev,
	struct usb_setup_data *req,
	uint8_t **buf,
	uint16_t *len,
    usbd_control_complete_callback *complete);

static void $(PREFIX)set_config(usbd_device *usbd_dev, uint16_t wValue)
{
    ER_DPRINTF("set cfg %d\n", wValue);
    if(wValue && wValue <= ARR_SIZE($(PREFIX)ep_init_map) ){
        int len = $(PREFIX)ep_init_map[wValue-1].len;
        const struct usb_endpoint_init* ep_inits = $(PREFIX)ep_init_map[wValue-1].ep_inits;
        for(int i=0;i<len;i++){
            usbd_ep_setup(usbd_dev, ep_inits[i].addr, ep_inits[i].type, ep_inits[i].size,
                ep_inits[i].cb ? ep_inits[i].cb : ( 
                ep_inits[i].addr & 0x80 ? $(PREFIX)ep_in_handler : $(PREFIX)ep_out_handler ) );
        }
    }else{
        ER_DPRINTF("set configuration unknown: %d\n", wValue);
    }
}

#ifndef USB_DT_BOS
#define USB_DT_BOS  0x0f
#endif

#if defined(HAS_WCID) || defined(HAS_WCID_20)

static int usb_descriptor_type(uint16_t wValue)
{
	return wValue >> 8;
}

#if defined(HAS_WCID)
static int usb_descriptor_index(uint16_t wValue)
{
	return wValue & 0xFF;
}
#endif

#endif

#ifndef MIN
#define MIN(a,b)   ((a)<(b)?(a):(b))
#endif

static enum usbd_request_return_codes $(PREFIX)WCID_control_request(usbd_device *usbd_dev,
	struct usb_setup_data *req,
	uint8_t **buf,
	uint16_t *len,
    usbd_control_complete_callback *complete)
{
    (void) usbd_dev;
    (void) complete;
#if defined(HAS_WCID)
    if(req->bRequest == USB_REQ_GET_DESCRIPTOR 
    && usb_descriptor_type(req->wValue) == USB_DT_STRING
    && usb_descriptor_index(req->wValue) == 0xee){
        #if defined(WCID_STRING_DESCRIPTOR_MSOS_SIZE)
        *len = MIN(*len, WCID_STRING_DESCRIPTOR_MSOS_SIZE);
        memcpy(*buf, WCID_StringDescriptor_MSOS, *len);
        return USBD_REQ_HANDLED;
        #endif
    }else if( (req->bmRequestType & USB_REQ_TYPE_TYPE) == USB_REQ_TYPE_VENDOR
    &&   req->bRequest == WCID_VENDOR_CODE ){
        if(req->wIndex == 4){
            #if defined($(PREFIX)WCID_DESCRIPTOR_SIZE)
            *len = MIN(*len, $(PREFIX)WCID_DESCRIPTOR_SIZE);
            memcpy(*buf, $(PREFIX)WCIDDescriptor, *len);
            return USBD_REQ_HANDLED;
            #endif
        }
        #if defined($(PREFIX)WCID_PROPERTIES_SIZE)
        else if(req->wIndex == 5 && req->wValue < $(PREFIX)WCID_PROPERTIES_SIZE ){
            desc_t desc = $(PREFIX)WCIDProperties[req->wValue];
            if(desc){
                uint16_t tlen = desc[0] + (desc[1]<<8) + (desc[2]<<16) + (desc[3]<<24);
                *len = MIN(*len, tlen);
                memcpy(*buf, desc, *len);
                return USBD_REQ_HANDLED;
            }
        }
        #endif
    }
#endif

#if defined(HAS_WCID_20)
    if(req->bRequest == USB_REQ_GET_DESCRIPTOR 
    && usb_descriptor_type(req->wValue) == USB_DT_BOS){
        #if defined( $(PREFIX)WCID_BOS_SIZE )
        *len = MIN(*len, $(PREFIX)WCID_BOS_SIZE);
        memcpy(*buf, $(PREFIX)WCIDBOS, *len);
        return USBD_REQ_HANDLED;
        #endif
    }else if((req->bmRequestType & USB_REQ_TYPE_TYPE) == USB_REQ_TYPE_VENDOR
    &&   req->bRequest == WCID_VENDOR_CODE
    &&   req->wIndex == 7 ){
        #if defined( $(PREFIX)WCID_DESC_SET_SIZE )
        *len = MIN(*len, $(PREFIX)WCID_DESC_SET_SIZE);
        memcpy(*buf, $(PREFIX)WCIDDescriptorSet, *len);
        return USBD_REQ_HANDLED;
        #endif
    }
#endif
    return USBD_REQ_NEXT_CALLBACK;
}


static uint8_t $(PREFIX)control_buffer[1024];
usbd_device * $(PREFIX)usb_init(const usbd_driver *driver, 
    ep_cb_t ep_in_cb,
    ep_cb_t ep_out_cb)
{
    usbd_device *dev = usbd_init(driver, &$(PREFIX)dev_desc, $(PREFIX)config,
    $(PREFIX)usb_strings, ARR_SIZE($(PREFIX)usb_strings),
    $(PREFIX)control_buffer, sizeof($(PREFIX)control_buffer));

    $(PREFIX)ep_in_handler = ep_in_cb;
    $(PREFIX)ep_out_handler = ep_out_cb;

    // TODO
    // WCID_control_request may register after set configuration
    // But the WCID feature in Windows will request something before set configuration
    // So register the control request for WCID here, after set configuartion it will be clear
    usbd_register_control_callback(
            dev,
            0,
            0,
            $(PREFIX)WCID_control_request);

    usbd_register_set_config_callback(dev, $(PREFIX)set_config);
    return dev;
}

]])

    return r
end


function Generate_LibOpenCM3_header(dev, maxEp, maxMem)
    local genCode = BeginGenCode(dev)

    local extDefine = ""
    local hasWCID = false
    for i,v in ipairs(dev.extDesc) do
        if isWCID(v) then
            hasWCID = true
        elseif v.handler then
            extDefine = extDefine .. v.handler(dev, v, true)
        end
    end

    if hasWCID then
        hasWCID = dev.content.bcdUSB > 0x200 and "HAS_WCID_20" or "HAS_WCID"
        extDefine = extDefine .. genCode({WCID = hasWCID},[[
// Enable WCID related code
#define  $(WCID)

#ifndef WCID_VENDOR_CODE
#define  WCID_VENDOR_CODE       0x17
extern const uint8_t WCID_StringDescriptor_MSOS[];
#endif

]])
    end


    return genCode({EXTDEF = filter(dev, extDefine) },[[
#ifndef __$(PREFIX)OPENCM3_USB_INIT_H__
#define __$(PREFIX)OPENCM3_USB_INIT_H__

#include <libopencm3/usb/usbd.h>

typedef void (*ep_cb_t)(usbd_device *usbd_dev, uint8_t ep);


/**
 * 
*/
usbd_device *$(PREFIX)usb_init(
        const usbd_driver *driver,
        ep_cb_t ep_in_cb,
        ep_cb_t ep_out_cb);

#ifndef opencm3_usb_init
#define opencm3_usb_init $(PREFIX)usb_init
#endif

// Extra define
$(EXTDEF)
#endif  // #ifndef __$(PREFIX)OPENCM3_USB_INIT_H__
]])
end