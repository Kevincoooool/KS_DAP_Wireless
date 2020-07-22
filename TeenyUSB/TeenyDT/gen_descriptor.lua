-- gen_descriptor.lua
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
require("usb_wcid")
require("usb_wcid20")
require("usb_teeny_desc")
require("usb_opencm3_desc")

local function usage()
    print("usage:")
    print("  lua usb_gen_desc.lua <inFile> [-maxep=<max ep number>] [-maxmem=<memory size in bytes>]")
    print("    inFile  - Input usb descriptor define file name")
    print("    -maxep  - max end point number")
    print("    -maxmem - max valid memory for USB core")
end

function input_name()
    local name = "<NONE>"
    string.gsub(arg[1], "([%w_%.]+)$", function(n)
        name = n
    end)
    return name
end

function MakeHeader(outFile, inFile, body)
    local genCode = BeginGenCode({})
    return genCode({
        OUTNAME = outFile,
        INNAME = inFile,
        DATE = os.date("%Y-%m-%d %H:%M:%S"),
        BODY = body,
    },[[
/*
 * Name   :  $(OUTNAME)
 * Author :  admin@xtoolbox.org
 * Date   :  $(DATE)

 * Desc   :  This file is auto generate by the TeenyDT
 *           Visit http://dt.tusb.org for more info
 */

/*
  Input source name:  $(INNAME)
  
  Content type is lua script:
  ------------- lua script begin ------------
$(BODY)

  ------------- lua script end   ------------
 */
]])
end

if not arg or #arg < 1 then
    usage()
    return
end

local MAX_EP = 7
local MAX_MEM = 1024
local inputName = arg[1]

function get_args(cmds)
    local r = {}
    for i,opt in ipairs(cmds) do
        string.gsub(opt:lower(), "%-([^=]+)=(.+)", function(k,v)
            r[k] = v
        end)
    end
    return r
end

local opts = get_args(arg)
MAX_EP = tonumber(opts.maxep) or MAX_EP
MAX_MEM = tonumber(opts.maxmem) or MAX_MEM
local mode = opts.mode

--print(tostring(mode))

local f = io.open(arg[1], "r")
assert(f,"Fail to open <"..arg[1]..">")

local s = f:read("*a")
f:close()

local desc = load(s)()

local c_name = 'teeny_usb_desc.c'
local h_name = 'teeny_usb_init.h'
local c_gen = Generate_TeenyUSB_desc
local h_gen = Generate_TeenyUSB_header
if mode and mode:sub(1,1) == "o" then
    c_name = 'opencm3_usb_init.c'
    h_name = 'opencm3_usb_init.h'
    c_gen = Generate_LibOpenCM3_desc
    h_gen = Generate_LibOpenCM3_header
end

local body = string.gsub(inputName, "([%w_%.]+)$", c_name)
local header = string.gsub(inputName, "([%w_%.]+)$", h_name)

local dummy = {
    write = function() end,
    close = function() end,
}
local c_file = dummy
local h_file = dummy
if not nofile then
    c_file = io.open(body, "w+")
    h_file = io.open(header, "w+")
end

c_file:write(  MakeHeader( c_name, input_name(), s) )
h_file:write(  MakeHeader( h_name, input_name(), s) )

if desc.content then
    c_file:write(c_gen(desc))
    h_file:write(h_gen(desc, MAX_EP, MAX_MEM))
else
    for i,v in ipairs(desc) do
        c_file:write("/////////////////////////////////////////\n")
        c_file:write("//// Device ",i-1,"\n")
        c_file:write("/////////////////////////////////////////\n")
        c_file:write(c_gen(v))

        h_file:write("/////////////////////////////////////////\n")
        h_file:write("//// Device ",i-1,"\n")
        h_file:write("/////////////////////////////////////////\n")
        h_file:write(h_gen(v, MAX_EP, MAX_MEM))
    end
end

c_file:close()
h_file:close()

