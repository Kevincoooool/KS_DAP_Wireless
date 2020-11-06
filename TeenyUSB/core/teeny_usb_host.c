/*       
 *         _______                    _    _  _____ ____  
 *        |__   __|                  | |  | |/ ____|  _ \ 
 *           | | ___  ___ _ __  _   _| |  | | (___ | |_) |
 *           | |/ _ \/ _ \ '_ \| | | | |  | |\___ \|  _ < 
 *           | |  __/  __/ | | | |_| | |__| |____) | |_) |
 *           |_|\___|\___|_| |_|\__, |\____/|_____/|____/ 
 *                               __/ |                    
 *                              |___/                     
 *
 * TeenyUSB - light weight usb stack for micro controllers
 * 
 * Copyright (c) 2020 XToolBox  - admin@xtoolbox.org
 *                         www.tusb.org
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include "teeny_usb_host.h"
#include "teeny_usb_osal.h"
#include "teeny_usb_util.h"

int tusb_open_host(tusb_host_t* host, const tusb_hardware_param_t* driver_param)
{ 
    host->periodic_queue = 0;
    host->periodic_pending = 0;
    int res = tusb_host_drv_open(&host->host_drv, driver_param, host);
    host->last_frame = tusb_host_get_frame_number(host);
    return res;
}

WEAK int tusb_host_port_changed(tusb_host_driver_t* drv, int port, host_port_state_t new_state)
{
    tusb_host_t* host = (tusb_host_t*)tusb_host_drv_get_context(drv);
    (void)host;
    TUSB_LOGD("Host port changed, port: %d, state: %d\n", port, new_state);
    return 0;
}

WEAK int tusb_host_sof_event(tusb_host_driver_t* drv)
{
    tusb_host_t* host = (tusb_host_t*)tusb_host_drv_get_context(drv);
    (void)host;
    return 0;
}

WEAK int tusb_host_channel_event(tusb_host_driver_t* drv, int ch_num, int ch_state)
{
    tusb_host_t* host = (tusb_host_t*)tusb_host_drv_get_context(drv);
    (void)host;
    TUSB_LOGD("Host channel event, channel: %d, state: %d\n", ch_num, ch_state);
    return 0;
}

WEAK int tusb_host_transfer_done(tusb_host_driver_t* drv, tusbh_transfer_t* transfer)
{
    tusb_host_t* host = (tusb_host_t*)tusb_host_drv_get_context(drv);
    (void)host;
    TUSB_LOGD("Host transfer done\n");
    return 0;
}
