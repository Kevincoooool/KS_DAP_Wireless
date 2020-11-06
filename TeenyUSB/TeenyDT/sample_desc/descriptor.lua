--[[
Descripttion : 
version      : 
Author       : Kevincoooool
Date         : 2020-09-14 20:38:37
LastEditors  : Kevincoooool
LastEditTime : 2020-10-26 14:27:34
FilePath     : \stm32f103demof:\Github\TeenyUSB\TeenyDT\sample_desc\descriptor.lua
--]]
local s = arg[1]:find("[^/\\]+$")
local sep = arg[1]:sub(s,s)
local p = arg[1]:sub(1, s-1) .. "?.lua"
package.path = package.path .. ";".. p

local desc_list = {
    -- { File = "composite_desc",     Description = "Composite"        },
    -- { File = "cdc_acm_desc",       Description = "CDC ACM"          },
    -- { File = "cdc_acm5_desc",      Description = "CDC ACM5"         },
    -- { File = "cdc_rndis_desc",     Description = "CDC RNDIS"        },
    -- { File = "winusb_desc",        Description = "WinUSB"           },
    -- { File = "winusb20_desc",      Description = "WinUSB20"         },
    -- { File = "hid_user_desc",      Description = "User HID"         },
    -- { File = "hid_kb_desc",        Description = "HID Keyboard"     },
    -- { File = "hid_mouse_desc",     Description = "HID Mouse"        },
    -- { File = "msc_desc",           Description = "Mass storage"     },
    -- { File = "daplinkv1_desc",     Description = "DAPLink V1"       },
    { File = "daplinkv2_desc",     Description = "DAPLink V2"       },
    -- { File = "multi_config_desc",  Description = "Multi Config"     },
    -- { File = "simplest_desc",      Description = "Simplest"         },
}

local descriptors = {}
for i,v in ipairs(desc_list) do
    descriptors[#descriptors+1] = require(v.File)
end

return descriptors
