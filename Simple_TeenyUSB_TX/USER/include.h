/*
 * @Descripttion: 
 * @version: 
 * @Author: Kevincoooool
 * @Date: 2020-08-20 11:51:46
 * @LastEditors  : Kevincoooool
 * @LastEditTime : 2020-12-01 19:05:39
 * @FilePath     : \Simple_TeenyUSB_TX\USER\include.h
 */
#ifndef _INCLUDE_H
#define _INCLUDE_H
#include "bsp_nrf2401.h"
#include "bsp_spi.h"
#include "wireless_rx.h"
#include "wireless_tx.h"
#include "online.h"
#include "offline.h"
#include "w25qxx.h"
#include "oled.h"
#include "string.h"
#include "swd_host.h"
#include "SWD_flash.h"
#include "SWD_opt.h"
#include "button.h"
#include "bsp_button.h"
#include "tusb_cdc.h"
#include "tusbd_user.h"
#include "tusbd_hid.h"
#include "tusbd_cdc.h"
#include "tusbd_msc.h"
#include "teeny_usb.h"
#include "tusbd_cdc_rndis.h"
#include "board_config.h"
#include "flash_blob.h"
#include "usart.h"
#include "show.h"
#include "ff.h"		/* FatFs configurations and declarations */
#include "diskio.h" /* Declarations of low level disk I/O functions */
#include "gpio.h"
#include "string.h"
#include "oledfont.h"
#include "oled.h"
#include "stm32f1xx.h"
#include "DAP_config.h"
#include "hex2bin.h"
#include "lcd_menu.h"
#define ONLINE          1
#define WIRELESS_TX     0
#define WIRELESS_RX     0
#define OFFLINE         0

enum
{
	MODE_SET_NORMAL = 0,
	MODE_SET_ONLINE,
	MODE_SET_OFFLINE,
	MODE_SET_ALGO,
	MODE_SET_FILE,
	MODE_SET_WIRELESS,
	MODE_SET_TX,
	MODE_SET_RX,
};

enum
{
	SHOW_MENU = 0,
	SHOW_FLM,
	SHOW_BIN,
	SHOW_AUTO,
	SHOW_ONLINE,
	SHOW_OFFLINE,
	SHOW_WIRELESS,
	SHOW_WL_TX,
	SHOW_WL_RX,

};
extern volatile uint8_t rx_len;
extern volatile uint8_t recv_end_flag;
extern uint8_t  rx_buffer[100];
extern char      BUFFER_SIZE;

#endif


