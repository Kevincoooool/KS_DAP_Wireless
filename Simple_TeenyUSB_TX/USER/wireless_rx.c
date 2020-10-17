/*
 * @Descripttion: 
 * @version: 
 * @Author: Kevincoooool
 * @Date: 2020-07-18 12:35:23
 * @LastEditors  : Kevincoooool
 * @LastEditTime : 2020-10-15 12:27:15
 * @FilePath     : \Simple_TeenyUSB_TX\USER\wireless_rx.c
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
static uint8_t CalcCheck(uint8_t *buffer, uint8_t len);
static uint8_t SumCheck(uint8_t *buffer, uint8_t len);
extern UART_HandleTypeDef huart1;
extern UART_HandleTypeDef huart2;
extern tusb_hid_device_t hid_dev;
extern uint8_t MYUSB_Request[DAP_PACKET_SIZE];  // Request  Buffer
extern uint8_t MYUSB_Response[DAP_PACKET_SIZE]; // Response Buffer
extern uint8_t dealing_data;
uint8_t In_MYUSB_Request[DAP_PACKET_SIZE + 3];   // Request  Buffer
uint8_t Out_MYUSB_Response[DAP_PACKET_SIZE + 3]; // Response Buffer
uint8_t state_w_rx = wait_dap_tx_data;

uint8_t usbd_hid_process_wireless_rx(void)
{

#if WIRELESS_RX
    /*
    无线接收端流程
    1、收到发射端传来的数据
    2、把数据传给DAP_ProcessCommand处理
    3、处理完成的结果发出
    4、完成、等待下一包处理
    */
    switch (state_w_rx)
    {
    case wait_dap_tx_data:
        if (recv_end_flag == 1 && !dealing_data)
        {
            dealing_data = 1;

            memcpy(MYUSB_Request, rx_buffer, DAP_PACKET_SIZE);
            //            for (uint8_t i = 1; i < 65; i++)
            //            {
            //                MYUSB_Request[i - 1] = In_MYUSB_Request[i];
            //            }
            //            if (In_MYUSB_Request[0] == 0xAA && In_MYUSB_Request[66] == 0xFB && SumCheck(MYUSB_Request, 65) == In_MYUSB_Request[65])
            //            {
            //                state_w_rx = get_dap_reponse;
            //            }
            //            else
            //            {
            //                memcpy(MYUSB_Response, MYUSB_Request, DAP_PACKET_SIZE);
            //                state_w_rx = get_dap_reponse;
            //            }
            state_w_rx = get_dap_reponse;
            rx_len = 0;        //清除计数
            recv_end_flag = 0; //清除接收结束标志位
        }
        else
        {
            state_w_rx = wait_dap_tx_data;
        }
        break;
    case get_dap_reponse:
        memset(MYUSB_Response, 0, 65);
        DAP_ProcessCommand(MYUSB_Request, MYUSB_Response);
        state_w_rx = seng_nrf_data;
        break;
    case seng_nrf_data:
        //        Out_MYUSB_Response[0] = 0xAA;
        //        Out_MYUSB_Response[65] = SumCheck(MYUSB_Response, 65);
        //        Out_MYUSB_Response[66] = 0xFB;
        //        for (uint8_t i = 1; i < 65; i++)
        //        {
        //            Out_MYUSB_Response[i] = MYUSB_Response[i - 1];
        //        }
        while (HAL_UART_Transmit(&huart1, MYUSB_Response, DAP_PACKET_SIZE, 1000) != HAL_OK)
            ;
        HAL_UART_Receive_DMA(&huart1, rx_buffer, BUFFER_SIZE);
        state_w_rx = wait_dap_tx_data;
        //memset(MYUSB_Request, 0, 65);
        dealing_data = 0;
        break;

    default:
        break;
    }

#endif
    return 0;
}

// uint8_t usbd_hid_process_wireless_rx(void)
// {

// #if WIRELESS_RX
//     /*
//     无线接收端流程
//     1、收到发射端传来的数据
//     2、把数据传给DAP_ProcessCommand处理
//     3、处理完成的结果发出
//     4、完成、等待下一包处理
//     */
//     switch (state_w_rx)
//     {
//     case wait_dap_tx_data:
//         if (recv_end_flag == 1 && !dealing_data)
//         {
//             dealing_data = 1;
//             memcpy(MYUSB_Request, rx_buffer, rx_len);
//             rx_len = 0;        //清除计数
//             recv_end_flag = 0; //清除接收结束标志位
//             state_w_rx = get_dap_reponse;
//         }
//         else
//         {
//             state_w_rx = wait_dap_tx_data;
//         }
//         break;
//     case get_dap_reponse:
//         memset(MYUSB_Response, 0, 65);
//         DAP_ProcessCommand(MYUSB_Request, MYUSB_Response);
//         state_w_rx = seng_nrf_data;
//         break;
//     case seng_nrf_data:
//         HAL_UART_Transmit(&huart1, MYUSB_Response, DAP_PACKET_SIZE, 1000);
//         HAL_UART_Receive_DMA(&huart1, rx_buffer, BUFFER_SIZE);
//         state_w_rx = wait_dap_tx_data;
//         dealing_data = 0;
//         break;

//     default:
//         break;
//     }

// #endif
//     return 0;
// }
//static uint8_t CalcCheck(uint8_t *buffer, uint8_t len)
//{
//    int i, result;

//    for (result = buffer[0], i = 1; i < len; i++)
//    {
//        result ^= buffer[i];
//    }
//    return result;
//}
//static uint8_t SumCheck(uint8_t *buffer, uint8_t len)
//{
//    int i;
//    uint8_t sum;
//    for (sum = buffer[0], i = 1; i < len; i++)
//    {
//        sum += buffer[i];
//    }
//    return sum;
//}
