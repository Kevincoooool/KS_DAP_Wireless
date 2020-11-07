/*
 * @Descripttion: 
 * @version: 
 * @Author: Kevincoooool
 * @Date: 2020-07-18 12:37:28
 * @LastEditors  : Kevincoooool
 * @LastEditTime : 2020-10-30 19:23:09
 * @FilePath     : \Simple_TeenyUSB_TX\USER\online.h
 */
#ifndef __ONLINE_HID_H__
#define __ONLINE_HID_H__

#include "include.h"
uint8_t usbd_hid_process(void);
uint8_t usbd_winusb_process_online(void);
uint8_t usbd_hid_process_online(void);
void HID_ProcessCommand(uint8_t *request, uint8_t *response);
void HID_GetOutReport(uint8_t *EpBuf, uint32_t len);
void HID_SetInReport(void);
void WINUSB_GetOutReport(uint8_t *EpBuf, uint32_t len);
void WINUSB_SetInReport(void);

#endif  /* __USBD_HID_H_ */
