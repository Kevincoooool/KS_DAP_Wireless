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
 * Title:        device.h CMSIS-DAP Wrap module for STM32
 *
 *---------------------------------------------------------------------------*/
#ifndef _DEVICE_H_
#define _DEVICE_H_

/**
  * The file device.h will be included into DAP_config.h. Please refer:
  *
  * line 60   @ DAP_config.h
  */

/* Include the headers generated with STM32CubeMX */
#include "main.h"
#include "stm32f1xx.h"
#include "stm32f103xb.h"
#include "system_stm32f1xx.h"
#include "stm32f1xx_hal.h"
//#include "usbd_customhid.h"

/**
  * @brief  The hardware initialize routine. Derived from the source code
  *         which was generated with STM32CubeMX.
  * @param  None
  * @retval None
  */
void DEVICE_Init(void);

/* Private defines -----------------------------------------------------------*/
#define LED_CONNECTED_Pin   GPIO_PIN_13
#define LED_GPIO_Port       GPIOC

#endif
