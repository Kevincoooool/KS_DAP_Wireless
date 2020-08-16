/*
 * Copyright (C) 2019-2020 Zach Lee.
 *
 * Licensed under the MIT License, you may not use this file except in
 * compliance with the License.
 *
 * MIT License:
 *
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 * ----------------------------------------------------------------------
 *
 * $Date:        11. August 2019
 * $Revision:    V0.0.0
 *
 * Project:      CMSIS-DAP Examples STM32F103
 * Title:        rl_usb.h CMSIS-DAP Wrap module for STM32
 *
 *---------------------------------------------------------------------------*/
#ifndef _RL_USB_H_
#define _RL_USB_H_

/**
  * This header file originally belongs to Keil MDK.
  * I put some defination about USB into this fake file.
  * Zach Lee
  */

//     <o.0..15>Maximum Input Report Size (in bytes) <1-65535>
//     <i>Allocates memory and configures 'len' value for USBD_HID0_GetReport
//     <i>and USBD_HID_GetReportTrigger
#define USBD_HID0_IN_REPORT_MAX_SZ                64

//     <o.0..15>Maximum Output Report Size (in bytes) <1-65535>
//     <i>Allocates memory and configures 'len' value for USBD_HID0_SetReport
//     <i>when rtype=HID_REPORT_OUTPUT.
#define USBD_HID0_OUT_REPORT_MAX_SZ               64

void USBD_Initialize(int);
void USBD_Connect(int);
int USBD_Configured(int);
void USBD_HID_GetReportTrigger(int, int, void *, int);

#define HID_REPORT_INPUT            0x81
#define HID_REPORT_OUTPUT           0x91
#define HID_REPORT_FEATURE          0xB1

#define USBD_HID_REQ_EP_CTRL        0x01
#define USBD_HID_REQ_PERIOD_UPDATE  0x02
#define USBD_HID_REQ_EP_INT         0x03



#endif
