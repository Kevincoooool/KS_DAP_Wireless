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

uint8_t FLASH_SWD(uint8_t *File);

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
extern int hid_len, cdc_len;
extern uint8_t cdc_buf[32];
extern tusb_hid_device_t hid_dev;
extern tusb_cdc_device_t cdc_dev;
extern tusb_msc_device_t msc_dev;
extern tusb_device_config_t device_config;
extern uint8_t button_num;
uint8_t NRF_OK = 1;
uint8_t In_MYUSB_Response[64 + 3]; // Request  Buffer
uint8_t Out_MYUSB_Request[64 + 3]; // Response Buffer
extern uint8_t dealing_data;
extern int8_t file_name, name_cnt;
extern char Name_Buffer[20][20];
uint8_t show_dap = 0;
int main(void)
{
	uint8_t RES_FS = 0;
	HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq() / 1000); //使用HAL_Delay才初始化
	tusb_device_t *dev = tusb_get_device(TEST_APP_USB_CORE);
	tusb_set_device_config(dev, &device_config);
	tusb_open_device(dev);
	DAP_SPI_Init();
	DAP_Setup();
	MX_USART1_UART_Init();
	MX_USART2_UART_Init();
	W25QXX_Init();
	OLED_Init();
	OLED_Clear();								 //清空OLED屏幕
	OLED_ShowString(0, 0, "DAP Connect", 12, 1); //绘制提示词
	algo_init();
	RES_FS = f_mount(&fs, "", 1);
	if (RES_FS == FR_OK) /* 打开文件夹目录成功，目录信息已经在dir结构体中保存 */
	{
		OLED_ShowString(0, 10, "Fatfs Success..", 12, 1);
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_14, GPIO_PIN_SET);
	}
	else if (RES_FS == FR_NO_FILESYSTEM) //如果是新芯片还没有文件系统
	{
		OLED_ShowString(0, 10, "Fatfs Format..", 12, 1);
		f_mkfs("", 0, work, sizeof(work));
		OLED_ShowString(0, 10, "Format Finished", 12, 1);
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_14, GPIO_PIN_SET);
	}
	else
	{
		OLED_ShowString(0, 10, "Fatfs Failed..", 12, 1);
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_14, GPIO_PIN_RESET);
	}

	HAL_Delay(1000);
	OLED_Clear();
	//	Display_FLM();
	//	Display_BIN();
	Button_Init();

	while (1)
	{
		Select_Menu();
		Show_Duty();
		// if (show_dap == 0)
		// {
		// 	Select_FLM();
		// }
		// else
		// {
		// 	Select_BIN();
		// }

		// HAL_UART_Receive_DMA(&huart1, rx_buffer, BUFFER_SIZE);
#if !ONLINE
//    NRF_Check_Event(); //检测nrf数据
//    if (NRF_Connect() == 0)
//    {

//    }
#endif
#if !WIRELESS_RX
		if (hid_len)
		{
			hid_len = 0;
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

		tusb_msc_device_loop(&msc_dev);
	}
}
