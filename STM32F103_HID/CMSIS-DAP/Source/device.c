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
 * Title:        device.c CMSIS-DAP Wrap module for STM32
 *
 *---------------------------------------------------------------------------*/

#include "rl_usb.h"
#include "device.h"
extern USBD_HandleTypeDef hUsbDeviceFS;
/**
  * Replace USB Middleware of Keil MDK
  */

/**
  * @brief  I use USB Middleware from STMicro. The func "MX_USB_DEVICE_Init"
  *         is used to initialize the USB device peripheral.
  * @param  n: Unused
  */
void USBD_Initialize(int n)
{
  (void)n;

  /**
    * I inserted the call of USBD_HID0_Initialize/USBD_HID0_Uninitialize
    * into usbd_custom_hid_if.c. Please refer:
    *
    * line 179  @ usbd_custom_hid_if.c
    * line 191  @ usbd_custom_hid_if.c
    */
  /* USBD_HID0_Initialize(); */
  return;
}
void USBD_Connect(int n)
{
  (void)n;

  return;
}
int USBD_Configured(int n)
{
  (void)n;

  return (hUsbDeviceFS.dev_state == USBD_STATE_CONFIGURED ? 1:0);
}

