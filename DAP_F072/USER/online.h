/*
 * @Descripttion: 
 * @version: 
 * @Author: Kevincoooool
 * @Date: 2020-07-18 12:37:28
 * @LastEditors: Kevincoooool
 * @LastEditTime: 2020-08-21 20:09:33
 * @FilePath: \Simple_TeenyUSB\USER\online.h
 */
#ifndef __ONLINE_HID_H__
#define __ONLINE_HID_H__

#include "stm32f0xx.h"


uint8_t usbd_hid_process_online(void);
void HID_ProcessCommand(uint8_t *request, uint8_t *response);
void HID_GetOutReport(uint8_t *EpBuf, uint32_t len);
void HID_SetInReport(void);

#endif  /* __USBD_HID_H_ */
