/*
 * @Descripttion: 
 * @version: 
 * @Author: Kevincoooool
 * @Date: 2020-08-21 20:10:56
 * @LastEditors: Kevincoooool
 * @LastEditTime: 2020-08-21 21:16:18
 * @FilePath: \Simple_TeenyUSB\USER\wireless_tx.h
 */
#ifndef __WIRELESS_TX_H__
#define __WIRELESS_TX_H__

#include "stm32f1xx.h"
/*
    无线发射端流程
    1、USB收到HID的数据
    2、把HID收到的数据通过SPI发出NRF
    3、等待SPI回复这一包数据的回复
    4、收到SPI回复的数据
    5、将SPI收到的数据通过HID发出
    */
enum
{
    wait_hid_data,
    nrf_send,
    wait_nrf_reply,
    get_nrf_data,
    seng_hid_data
};
uint8_t usbd_hid_process_wireless_tx(void);
#endif
