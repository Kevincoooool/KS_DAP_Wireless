/*
 * @Descripttion: 
 * @version: 
 * @Author: Kevincoooool
 * @Date: 2020-07-18 12:35:23
 * @LastEditors: Kevincoooool
 * @LastEditTime: 2020-08-21 21:39:23
 * @FilePath: \Simple_TeenyUSB\USER\wireless_rx.c
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
extern UART_HandleTypeDef huart1;
extern UART_HandleTypeDef huart2;
extern tusb_hid_device_t hid_dev;
extern uint8_t MYUSB_Request[DAP_PACKET_SIZE + 1];  // Request  Buffer
extern uint8_t MYUSB_Response[DAP_PACKET_SIZE + 1]; // Response Buffer
extern uint8_t dealing_data;
uint8_t state_w_rx = wait_nrf_data_1;
uint8_t RX_ONE[32] = {0};
uint8_t RX_TWO[32] = {0};
uint8_t RX_THREE[5] = {0};
uint8_t TX_ONE[32] = {0};
uint8_t TX_TWO[32] = {0};
uint8_t TX_THREE[5] = {0};
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
        // if (NRF_GETDATA)
        // {
        //     NRF_GETDATA = 0;
        //     memcpy(RX_ONE, NRF24L01_2_RXDATA, 32);
        //     state_w_rx = dap_deal_1;
        // }

        if (recv_end_flag == 1)
        {

            memcpy(MYUSB_Request, rx_buffer, rx_len);
            rx_len = 0; //清除计数

            recv_end_flag = 0; //清除接收结束标志位
            state_w_rx = get_dap_reponse;
        }
        else
        {
            state_w_rx = wait_nrf_data_1;
        }

        break;
    case dap_deal_1:

        for (uint8_t i = 0; i < 32; i++)
        {
            MYUSB_Request[i] = RX_ONE[i];
        }
        state_w_rx = wait_nrf_data_2;
        break;
    case wait_nrf_data_2:
        if (NRF_GETDATA)
        {
            NRF_GETDATA = 0;
            memcpy(RX_TWO, NRF24L01_2_RXDATA, 32);
            state_w_rx = dap_deal_2;
        }
        break;
    case dap_deal_2:

        for (uint8_t i = 0; i < 32; i++)
        {
            MYUSB_Request[i + 32] = RX_TWO[i];
        }
        state_w_rx = get_dap_reponse;
        break;
    // case wait_nrf_data_3:
    //     if (NRF_GETDATA)
    //     {
    //         NRF_GETDATA = 0;
    //         memcpy(RX_THREE, NRF24L01_2_RXDATA, 30);
    //         state_w_rx = dap_deal_3;
    //     }
    //     break;
    // case dap_deal_3:

    //     for (uint8_t i = 0; i < 5; i++)
    //     {
    //         MYUSB_Request[i + 32] = RX_THREE[i];
    //     }
    //     state_w_rx = get_dap_reponse;
    //     break;
    case get_dap_reponse:

        memset(MYUSB_Response, 0, 64);
        DAP_ProcessCommand(MYUSB_Request, MYUSB_Response);
        //	memset(MYUSB_Request,0,64);
        state_w_rx = seng_nrf_data;
        break;
    case seng_nrf_data:
        // for (uint8_t i = 0; i < 32; i++)
        // {
        //     TX_ONE[i] = MYUSB_Response[i];
        // }
        // NRF_TxPacket(TX_ONE, 32);
        // Delay20ms();

        // for (uint8_t j = 0; j < 32; j++)
        // {
        //     TX_TWO[j] = MYUSB_Response[j + 32];
        // }
        // NRF_TxPacket(TX_TWO, 32);
        // Delay20ms();
        HAL_UART_Transmit(&huart1, MYUSB_Response, DAP_PACKET_SIZE, 100);
        // for (uint8_t j = 0; j < 30; j++)
        // {
        //     TX_THREE[j] = MYUSB_Response[j + 60];
        // }
        // NRF_TxPacket(TX_THREE, 5);
        // Delay20ms();
        HAL_UART_Receive_DMA(&huart1, rx_buffer, BUFFER_SIZE);
        state_w_rx = wait_nrf_data_1;
        //        dealing_data = 0;
        break;

    default:
        break;
    }

#endif
    return 0;
}
