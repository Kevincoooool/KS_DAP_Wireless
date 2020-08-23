/*
 * @Descripttion: 
 * @version: 
 * @Author: Kevincoooool
 * @Date: 2020-08-21 20:10:56
 * @LastEditors: Kevincoooool
 * @LastEditTime: 2020-08-23 10:40:28
 * @FilePath: \Simple_TeenyUSB_RX\USER\wireless_tx.h
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
    wait_nrf_reply_1,
    get_nrf_data_1,
    wait_nrf_reply_2,
    get_nrf_data_2,
    wait_nrf_reply_3,
    get_nrf_data_3,
    seng_hid_data
};
uint8_t usbd_hid_process_wireless_tx(void);
#endif
