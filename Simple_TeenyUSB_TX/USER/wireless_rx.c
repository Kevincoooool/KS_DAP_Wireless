/*
 * @Descripttion: 
 * @version: 
 * @Author: Kevincoooool
 * @Date: 2020-07-18 12:35:23
 * @LastEditors: Kevincoooool
 * @LastEditTime: 2020-08-23 10:39:48
 * @FilePath: \Simple_TeenyUSB_TX\USER\wireless_rx.c
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
#include "wireless_rx.h"
extern tusb_hid_device_t hid_dev;
extern uint8_t MYUSB_Request[DAP_PACKET_SIZE + 1];  // Request  Buffer
extern uint8_t MYUSB_Response[DAP_PACKET_SIZE + 1]; // Response Buffer
extern uint8_t dealing_data;
uint8_t state_w_rx = wait_nrf_data_1;
uint8_t RX_ONE[32] = {0};
uint8_t RX_TWO[32] = {0};
uint8_t RX_THREE[32] = {0};
uint8_t TX_ONE[32] = {0};
uint8_t TX_TWO[32] = {0};
uint8_t TX_TWO[32] = {0};
uint8_t usbd_hid_process_wireless_rx(void)
{

#if WIRELESS_RX
    /*
    无线接收端流程
    1、SPI收到NRF2401的数据
    2、把SPI收到的数据传给DAP_ProcessCommand处理
    3、处理完成的结果通过SPI发出NRF
    4、完成、等待下一包处理
    */
    switch (state_w_rx)
    {
    case wait_nrf_data_1:
        if (NRF_GETDATA)
        {
            NRF_GETDATA = 0;
            memcpy(RX_ONE, NRF24L01_2_RXDATA, 32);
            state_w_rx = dap_deal_1;
        }
        break;
    case dap_deal_1:

        for (uint8_t i = 0; i < 30; i++)
        {
            MYUSB_Request[i] = RX_ONE[i];
        }
        state_w_rx = wait_nrf_data_2;
        break;
    case wait_nrf_data_2:
        if (NRF_GETDATA)
        {
            NRF_GETDATA = 0;
            memcpy(RX_TWO, NRF24L01_2_RXDATA, 30);
            state_w_rx = dap_deal_2;
        }
        break;
    case dap_deal_2:

        for (uint8_t i = 0; i < 30; i++)
        {
            MYUSB_Request[i + 30] = RX_TWO[i];
        }
        state_w_rx = wait_nrf_data_3;
        break;
    case wait_nrf_data_3:
        if (NRF_GETDATA)
        {
            NRF_GETDATA = 0;
            memcpy(RX_TWO, NRF24L01_2_RXDATA, 30);
            state_w_rx = dap_deal_3;
        }
        break;
    case dap_deal_3:

        for (uint8_t i = 0; i < 5; i++)
        {
            MYUSB_Request[i + 60] = RX_TWO[i];
        }
        state_w_rx = get_dap_reponse;
        break;
    case get_dap_reponse:
        DAP_ProcessCommand(MYUSB_Request, MYUSB_Response);
        state_w_rx = seng_nrf_data;
        break;
    case seng_nrf_data:
        for (uint8_t i = 0; i < 30; i++)
        {
            TX_ONE[i] = MYUSB_Response[i];
        }
        NRF_TxPacket(TX_ONE, 30);
        Delay20ms();
        for (uint8_t j = 0; j < 30; j++)
        {
            TX_TWO[j] = MYUSB_Response[j + 30];
        }
        NRF_TxPacket(TX_TWO, 30);
        Delay20ms();
        for (uint8_t j = 0; j < 30; j++)
        {
            TX_TWO[j] = MYUSB_Response[j + 60];
        }
        NRF_TxPacket(TX_TWO, 5);
        Delay20ms();
        state_w_rx = wait_nrf_data_1;
        //        dealing_data = 0;
        break;

    default:
        break;
    }

#endif
    return 0;
}
