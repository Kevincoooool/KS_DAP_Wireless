/*
 * @Descripttion: 
 * @version: 
 * @Author: Kevincoooool
 * @Date: 2020-08-21 20:10:56
 * @LastEditors: Kevincoooool
 * @LastEditTime: 2020-08-21 21:24:41
 * @FilePath: \Simple_TeenyUSB\USER\wireless_rx.h
 */
#ifndef __WIRELESS_RX_H__
#define __WIRELESS_RX_H__

#include "stm32f1xx.h"
/*
    无线接收端流程
    1、SPI收到NRF2401的数据
    2、把SPI收到的数据传给DAP_ProcessCommand处理
    3、处理完成的结果通过SPI发出NRF
    4、完成、等待下一包处理
    */
enum
{
    wait_dap_tx_data,
    dap_deal_1,
    wait_nrf_data_2,
    dap_deal_2,
    wait_nrf_data_3,
    dap_deal_3,
    get_dap_reponse,
    seng_nrf_data
};
uint8_t usbd_hid_process_wireless_rx(void);
#endif  
