/*
 * @Descripttion: 
 * @version: 
 * @Author: Kevincoooool
 * @Date: 2020-08-04 20:32:30
 * @LastEditors: Kevincoooool
 * @LastEditTime: 2020-08-21 21:42:53
 * @FilePath: \Simple_TeenyUSB\USER\main.c
 */
#include "bsp_spi.h"
#include "hid_transfer.h"
#include "teeny_usb.h"
#include "tusbd_cdc_rndis.h"
#include "board_config.h"
#include "tusb_cdc.h"
#include "teeny_usb.h"
#include "tusbd_user.h"
#include "tusbd_hid.h"
#include "tusbd_cdc.h"
#include "tusbd_msc.h"
#include "DAP.h"
#include "usart.h"
#include "include.h"
extern uint8_t MYUSB_Request[64 + 1];  // Request  Buffer
extern uint8_t MYUSB_Response[64 + 1]; // Response Buffer
extern uint8_t dealing_data;
extern int hid_len, cdc_len;
extern uint8_t cdc_buf[32];
extern tusb_cdc_device_t cdc_dev;
extern tusb_msc_device_t msc_dev;
extern tusb_device_config_t device_config;
uint8_t NRF_OK = 1;
uint8_t NRF_SEND[32] = {0};
void Delay20ms(void) //@33.000MHz
{
        uint8_t i, j, k;

        __NOP();
        __NOP();
        i = 10;
        j = 130;
        k = 254;
        do
        {
                do
                {
                        while (--k)
                                ;
                } while (--j);
        } while (--i);
}
int main(void)
{
        tusb_device_t *dev = tusb_get_device(TEST_APP_USB_CORE);
        tusb_set_device_config(dev, &device_config);
        tusb_open_device(dev);
        DAP_SPI_Init();
        DAP_Setup();
        MX_USART1_UART_Init();
        MX_USART2_UART_Init();
        NRF_OK = NRF_Check();
        if (NRF_OK == 0)
        {
                NRF_Init(MODEL_RX2, 51);
        }
        while (1)
        {
//		Delay20ms();
//		HAL_Delay(10);
//		NRF_SEND[10]++;
//		if (NRF_SEND[10]>15)
//			NRF_SEND[10] = 0;
//		NRF_TxPacket(NRF_SEND, 32);
#if !ONLINE
                NRF_Check_Event(); //检测遥控数据
                if (NRF_Connect() == 0)
                {
                }
#endif
#if !WIRELESS_RX
                if (hid_len)
                {
#if ONLINE
                        usbd_hid_process_online();
#elif WIRELESS_TX
                        usbd_hid_process_wireless_tx();
#endif
                }
#elif WIRELESS_RX
                usbd_hid_process_wireless_rx();
#endif
                if (cdc_len)
                {

                        tusb_cdc_device_send(&cdc_dev, cdc_buf, cdc_len);
                        cdc_len = 0;
                }

//                tusb_msc_device_loop(&msc_dev);
        }
}
