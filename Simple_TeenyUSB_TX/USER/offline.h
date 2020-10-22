/*
 * @Descripttion: 
 * @version: 
 * @Author: Kevincoooool
 * @Date: 2020-07-18 12:37:28
 * @LastEditors: Kevincoooool
 * @LastEditTime: 2020-08-21 20:10:15
 * @FilePath: \Simple_TeenyUSB\USER\offline.h
 */
#ifndef __OFFLINE_HID_H__
#define __OFFLINE_HID_H__

#include "stm32f1xx.h"
void Display_BIN(void);
void Select_BIN(void);
void Display_FLM(void);
void Select_FLM(void);
uint8_t FLASH_SWD(uint8_t *File);
uint8_t usbd_hid_process_offline(void);

#endif  /* __USBD_HID_H_ */
