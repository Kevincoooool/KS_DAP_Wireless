/*
* @Descripttion: 
* @version: 
* @Author: Kevincoooool
* @Date: 2020-08-04 20:32:30
 * @LastEditors  : Kevincoooool
 * @LastEditTime : 2020-10-18 17:51:37
 * @FilePath     : \Simple_TeenyUSB_TX\USER\main.c
*/
#include "include.h"
#include "teeny_usb.h"
#include "teeny_usb_desc.h"
#include "teeny_usb_util.h"
#include "string.h"
#include "tusb_platform_stm32.h"
#include "board_config.h"

#include "tusbd_user.h"
#include "tusbd_hid.h"
#include "tusbd_cdc.h"
#include "tusbd_msc.h"
#include "DAP.h"
extern tusb_device_t g_dev;
void Work_State(void);
/***********************文件系统使用定义************************/
FIL fnew; /* file objects */
FILINFO FileInfo;
DIR DirInfo;
FATFS fs; /* Work area (file system object) for logical drives */
FRESULT Res;
UINT br, bw;		  /* File R/W count */
BYTE work[FF_MAX_SS]; /* Work area (larger is better for processing time) */
extern uint8_t MYUSB_Request[64 + 1];
extern uint8_t MYUSB_Response[64 + 1];
extern int hid_len, cdc_len,user_len;
extern uint8_t cdc_buf[64],hid_buf[];
extern uint8_t user_buf[];
extern tusb_hid_device_t hid_dev;
extern tusb_cdc_device_t cdc_dev;
extern tusb_msc_device_t msc_dev;
extern tusb_msc_device_t user_dev;
extern tusb_device_config_t device_config;
extern uint8_t button_num;
uint8_t NRF_OK = 1;
uint8_t In_MYUSB_Response[64 + 3]; // Request  Buffer
uint8_t Out_MYUSB_Request[64 + 3]; // Response Buffer
extern uint8_t dealing_data;
extern int8_t file_name, name_cnt;
extern char Name_Buffer[20][20];

int main(void)
{
	uint8_t RES_FS = 0;
//	HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq() / 1000); //使用HAL_Delay才初始化
//	DAP_SPI_Init();
	DAP_Setup();
//	OLED_Init();
//	OLED_Clear(); //清空OLED屏幕
  // Device configured, ready to work
//	tusb_device_t *dev = tusb_get_device(TEST_APP_USB_CORE);
//	tusb_set_device_config(dev, &device_config);
//	tusb_open_device(dev);
//	MX_USART1_UART_Init();
//	MX_USART2_UART_Init();
//	W25QXX_Init();
//	algo_init();
//	RES_FS = f_mount(&fs, "", 1);

//	if (RES_FS == FR_OK) /* 打开文件夹目录成功，目录信息已经在dir结构体中保存 */
//	{
////		f_mkfs("", 0, work, sizeof(work));
//		OLED_ShowString(0, Y4, "Fatfs Success..", 8, 1);
//		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_14, GPIO_PIN_SET);
//	}
//	else if (RES_FS == FR_NO_FILESYSTEM) //如果是新芯片还没有文件系统
//	{
//		OLED_ShowString(0, Y4, "Fatfs Format..", 12, 1);
//		f_mkfs("", 0, work, sizeof(work));
//		OLED_ShowString(0, Y4, "Format Finished", 12, 1);
//		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_14, GPIO_PIN_SET);
//	}
//	else
//	{
//		OLED_ShowString(0, Y4, "Fatfs Failed..", 12, 1);
//		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_14, GPIO_PIN_RESET);
//	}
//	//先读取一次文件到文件列表
//	if (f_opendir(&DirInfo, (const TCHAR *)"0:") == FR_OK) /* 打开文件夹目录成功，目录信息已经在dir结构体中保存 */
//	{
//		f_readdir(&DirInfo, &FileInfo);
//		while (f_readdir(&DirInfo, &FileInfo) == FR_OK) /* 读文件信息到文件状态结构体中 */
//		{
//			if (!FileInfo.fname[0])
//				break;
//			strcpy(Name_Buffer[name_cnt], FileInfo.fname);
//			name_cnt++;
//		}
//	}
	SetDescriptor(&g_dev, &COMP_descriptors);
	tusb_set_device_config(&g_dev, &device_config);
	tusb_open_device(&g_dev, TUSB_DEFAULT_DEV_PARAM);
	while(!g_dev.config){
	  // wait device ready
	}
//	HAL_Delay(500);
	Button_Init();
GPIO_InitTypeDef GPIO_InitStruct = {0};
__HAL_RCC_GPIOB_CLK_ENABLE();
//  HAL_GPIO_WritePin(JTAG_TCK_GPIO_Port, JTAG_TCK_Pin, GPIO_PIN_SET);
//  HAL_GPIO_WritePin(JTAG_TMS_GPIO_Port, JTAG_TMS_Pin, GPIO_PIN_SET);
//  HAL_GPIO_WritePin(JTAG_TDI_GPIO_Port, JTAG_TDI_Pin, GPIO_PIN_SET);
//  HAL_GPIO_WritePin(JTAG_nTRST_GPIO_Port, JTAG_nTRST_Pin, GPIO_PIN_SET);
//  HAL_GPIO_WritePin(JTAG_nRESET_GPIO_Port, JTAG_nRESET_Pin, GPIO_PIN_SET);
  GPIOB->BSRR = JTAG_TCK_Pin|JTAG_TMS_Pin|JTAG_TDI_Pin|JTAG_nTRST_Pin|JTAG_nRESET_Pin;

  /*Configure GPIO pins : JTAG_TCK_Pin JTAG_TMS_Pin JTAG_TDI_Pin */
  GPIO_InitStruct.Pin = JTAG_TCK_Pin|JTAG_TMS_Pin|JTAG_TDI_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
	while (1)
	{
//		GPIOB->ODR = 1<<11;
//        GPIOB->ODR = 0<<11;
//		GPIOB->ODR = 1<<11;
//        GPIOB->ODR = 0<<11;
//		GPIOB->BSRR = JTAG_TCK_Pin;
//		GPIOB->BSRR = JTAG_TCK_Pin <<16;
//		Work_State();
#if !ONLINE
//    NRF_Check_Event(); //检测nrf数据
//    if (NRF_Connect() == 0)
//    {
//    }
#endif
		if (hid_len)
		{
			
			usbd_hid_process_online();
			//tusb_hid_device_send(&hid_dev, hid_buf, hid_len);
			hid_len = 0;
		}
//		if(user_len){
//      
//			usbd_winusb_process_online();
////      tusb_user_device_send(&user_dev, user_buf, user_len);
//			user_len = 0;
//		}
//		if (cdc_len)
//		{
//			tusb_cdc_device_send(&cdc_dev, cdc_buf, cdc_len);
////			while (HAL_UART_Transmit(&huart2, cdc_buf, cdc_len, 1000) != HAL_OK)
////				;
//			cdc_len = 0;
//		}

		tusb_msc_device_loop(&msc_dev);
	}
}

void Work_State(void)
{
	if (Show.mode != MODE_SET_ONLINE && Show.mode != MODE_SET_TX && Show.mode != MODE_SET_RX)
		Show_Duty();
	switch (Show.mode)
	{
	case MODE_SET_NORMAL: //首页选择模式
		Select_Mode();
		break;
	case MODE_SET_ONLINE: //有线仿真模式  当正常DAP使用
		if (hid_len)
		{
			hid_len = 0;
//			usbd_hid_process_online();
		}
		break;
	case MODE_SET_OFFLINE: //脱机烧录模式  自动烧录  选择文件和下载算法
		Select_Offline();
		Auto_Fash();
		break;
	case MODE_SET_ALGO: //选择烧录算法（也就是目标芯片）
		Select_FLM();
		break;
	case MODE_SET_FILE: //选择下载文件
		Select_BIN();
		break;
	case MODE_SET_WIRELESS: //无线模式选择模式
		Select_WL_MODE();
		break;
	case MODE_SET_TX: //无线发射端模式
		usbd_hid_process_wireless_tx();
		break;
	case MODE_SET_RX: //无线接收端模式
		usbd_hid_process_wireless_rx();
		break;
	default:
		break;
	}
}
