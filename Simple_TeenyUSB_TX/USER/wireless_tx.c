/*
 * @Descripttion: 
 * @version: 
 * @Author: Kevincoooool
 * @Date: 2020-07-18 12:35:23
 * @LastEditors: Kevincoooool
 * @LastEditTime: 2020-08-21 21:28:59
 * @FilePath: \Simple_TeenyUSB\USER\wireless_tx.c
 */
/***************************************************************/
#include "DAP_Config.h"
#include "DAP_Common.h"
#include "DAP.h"
#include "hid_transfer.h"
#include "include.h"
#include "teeny_usb.h"
#include "tusbd_user.h"
#include "tusbd_hid.h"
#include "tusbd_cdc.h"
#include "tusbd_msc.h"
#include "wireless_tx.h"
extern tusb_hid_device_t hid_dev;
extern tusb_cdc_device_t cdc_dev;
extern uint8_t MYUSB_Request[DAP_PACKET_SIZE + 1];  // Request  Buffer
extern uint8_t MYUSB_Response[DAP_PACKET_SIZE + 1]; // Response Buffer
extern uint8_t dealing_data;
uint8_t state_w_tx = wait_hid_data;
uint8_t TX_ONE[32] = {0};
uint8_t TX_TWO[32] = {0};
uint8_t RX_ONE[32] = {0};
uint8_t RX_TWO[32] = {0};
uint8_t usbd_hid_process_wireless_tx(void)
{

#if WIRELESS_TX
    /*
    无线发射端流程
    1、USB收到HID的数据
    2、把HID收到的数据通过SPI发出NRF
    3、等待SPI回复这一包数据的回复
    4、收到SPI回复的数据
    5、将SPI收到的数据通过HID发出
    */
    switch (state_w_tx)
    {
    case wait_hid_data:
        if (dealing_data)
        {
            state_w_tx = nrf_send;
        }
        break;
    case nrf_send:
        for (uint8_t i = 0; i < 30; i++)
        {
            TX_ONE[i] = MYUSB_Request[i];
        }
        NRF_TxPacket(TX_ONE, 30);
        Delay20ms();
        for (uint8_t i = 0; i < 30; i++)
        {
            TX_TWO[i] = MYUSB_Request[i + 30];
        }
        NRF_TxPacket(TX_TWO, 30);
        Delay20ms();
        for (uint8_t i = 0; i < 5; i++)
        {
            TX_TWO[i] = MYUSB_Request[i + 60];
        }
        NRF_TxPacket(TX_TWO, 5);
        Delay20ms();
        state_w_tx = wait_nrf_reply_1;

        break;
    case wait_nrf_reply_1:
        if (NRF_GETDATA)
        {
            memcpy(RX_ONE, NRF24L01_2_RXDATA, 30);
            NRF_GETDATA = 0;
            state_w_tx = get_nrf_data_1;
        }
        break;
    case get_nrf_data_1:

        for (uint8_t i = 0; i < 30; i++)
        {
            MYUSB_Response[i] = RX_ONE[i];
        }
        state_w_tx = wait_nrf_reply_2;
        break;
    case wait_nrf_reply_2:
        if (NRF_GETDATA)
        {
            memcpy(RX_TWO, NRF24L01_2_RXDATA, 30);
            NRF_GETDATA = 0;
            state_w_tx = get_nrf_data_2;
        }
        break;
    case get_nrf_data_2:

        for (uint8_t j = 0; j < 30; j++)
        {
            MYUSB_Response[j + 30] = RX_TWO[j];
        }
        state_w_tx = seng_hid_data;
        break;
    case wait_nrf_reply_3:
        if (NRF_GETDATA)
        {
            memcpy(RX_TWO, NRF24L01_2_RXDATA, 5);
            NRF_GETDATA = 0;
            state_w_tx = get_nrf_data_3;
        }
        break;
    case get_nrf_data_3:

        for (uint8_t j = 0; j < 5; j++)
        {
            MYUSB_Response[j + 60] = RX_TWO[j];
        }
        state_w_tx = seng_hid_data;
        break;
    case seng_hid_data:
        tusb_hid_device_send(&hid_dev, MYUSB_Response, DAP_PACKET_SIZE);
        state_w_tx = wait_hid_data;
        break;

    default:
        break;
    }

    // if (dealing_data)
    // {
    //     // DAP_ProcessCommand(MYUSB_Request, MYUSB_Response);
    //     // tusb_hid_device_send(&hid_dev, MYUSB_Response, DAP_PACKET_SIZE);
    //     NRF_TxPacket(MYUSB_Request, DAP_PACKET_SIZE);

    //     dealing_data = 0;

    //     return 1;
    // }
#endif
    return 0;
}
