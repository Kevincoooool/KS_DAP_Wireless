/*
 * @Descripttion: 
 * @version: 
 * @Author: Kevincoooool
 * @Date: 2020-08-04 20:32:30
 * @LastEditors: Kevincoooool
 * @LastEditTime: 2020-08-19 21:44:06
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
extern int hid_len, cdc_len;
extern uint8_t cdc_buf[32];
extern tusb_cdc_device_t cdc_dev;
extern tusb_msc_device_t msc_dev;
extern tusb_device_config_t device_config;
int main(void)
{
    tusb_device_t *dev = tusb_get_device(TEST_APP_USB_CORE);
    tusb_set_device_config(dev, &device_config);
    tusb_open_device(dev);
    DAP_SPI_Init();
    DAP_Setup();
	MX_USART1_UART_Init();
	MX_USART2_UART_Init();
    while (1)
    {
        if (hid_len)
        {
            usbd_hid_process();
        }

        if (cdc_len)
        {

            tusb_cdc_device_send(&cdc_dev, cdc_buf, cdc_len);
            cdc_len = 0;
        }

        tusb_msc_device_loop(&msc_dev);
    }
}
