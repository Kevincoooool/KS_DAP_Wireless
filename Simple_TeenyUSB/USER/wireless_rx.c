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
extern tusb_hid_device_t hid_dev;
extern uint8_t MYUSB_Request[DAP_PACKET_SIZE + 1];  // Request  Buffer
extern uint8_t MYUSB_Response[DAP_PACKET_SIZE + 1]; // Response Buffer
extern uint8_t dealing_data;
uint8_t state_w_rx = wait_nrf_data;
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
    case wait_nrf_data:
        if (NRF_GETDATA)
        {
            state_w_rx = dap_deal;
        }
        break;
    case dap_deal:
        memcpy(MYUSB_Request, NRF24L01_2_RXDATA, DAP_PACKET_SIZE);
        
        state_w_rx = get_dap_reponse;
        break;
    case get_dap_reponse:
        DAP_ProcessCommand(MYUSB_Request, MYUSB_Response);
        break;
    case seng_nrf_data:
        NRF_TxPacket(MYUSB_Response, DAP_PACKET_SIZE);
        state_w_rx = wait_nrf_data;
        dealing_data = 0;
        break;

    default:
        break;
    }

#endif
    return 0;
}
