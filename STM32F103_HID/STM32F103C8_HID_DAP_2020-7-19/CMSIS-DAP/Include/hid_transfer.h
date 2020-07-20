/*
 * @Descripttion: 
 * @version: 
 * @Author: Kevincoooool
 * @Date: 2020-07-18 12:37:28
 * @LastEditors: Kevincoooool
 * @LastEditTime: 2020-07-18 14:16:17
 * @FilePath: \ANO_Remoter\ANO_Remoter\hid_transfer.h
 */
#ifndef __USBD_HID_H__
#define __USBD_HID_H__

#include "main.h"

uint8_t usbd_hid_process(void);
void HID_ProcessCommand(uint8_t *request, uint8_t *response);
void HID_GetOutReport(uint8_t *EpBuf, uint32_t len);
void HID_SetInReport(void);

#endif  /* __USBD_HID_H_ */
