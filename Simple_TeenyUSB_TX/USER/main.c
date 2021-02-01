/*
* @Descripttion: 
* @version: 
* @Author: Kevincoooool
* @Date: 2020-08-04 20:32:30
 * @LastEditors  : Kevincoooool
 * @LastEditTime : 2021-02-01 16:24:13
 * @FilePath     : \Simple_TeenyUSB_TX\USER\main.c
*/
#include "include.h"
#include "DAP.h"
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

extern int hid_len, cdc_len, user_len;
extern uint8_t cdc_buf[];
extern uint8_t user_buf[];
extern tusb_hid_device_t hid_dev;
extern tusb_cdc_device_t cdc_dev;
extern tusb_msc_device_t msc_dev;
extern tusb_user_device_t user_dev;
extern tusb_device_config_t device_config;

extern uint8_t button_num;
extern uint8_t dealing_data;
extern int8_t file_name, name_cnt;
extern char Name_Buffer[20][20];

int main(void)
{
	uint8_t RES_FS = 0;
	HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq() / 1000);		 //使用HAL_Delay才初始化
	DAP_SPI_Init();											 //IO和SPI初始化  SPI1测试用来模拟SWD  SPI2用作W25Q
	DAP_Setup();											 //DAP的IO口
	OLED_Init();											 //OLED初始化
	OLED_Clear();											 //清空OLED屏幕
	OLED_ShowString(20, 4, "DAPLink", 24, 1);				 //开机显示
	tusb_device_t *dev = tusb_get_device(TEST_APP_USB_CORE); //初始化teenyusb
	tusb_set_device_config(dev, &device_config);			 //初始化teenyusb
	tusb_open_device(dev);									 //初始化teenyusb
	MX_USART1_UART_Init();									 //串口1初始化
	MX_USART2_UART_Init();									 //串口2初始化
	if (W25QXX_Init())										 //W25Q初始化
	{
		algo_init();				  //烧录算法初始化
		RES_FS = f_mount(&fs, "", 1); //挂载文件系统到W25Q
		if (RES_FS == FR_OK)		  /* 打开文件夹目录成功，目录信息已经在dir结构体中保存 */
		{
			//f_mkfs("", 0, work, sizeof(work));
			//OLED_ShowString(0, 0, "Fatfs Success..", 12, 1);
			HAL_GPIO_WritePin(GPIOC, GPIO_PIN_14, GPIO_PIN_SET);
		}
		else if (RES_FS == FR_NO_FILESYSTEM) //如果是新芯片还没有文件系统
		{
			OLED_Clear();
			OLED_ShowString(0, 0, "Fatfs Format..", 12, 1);
			f_mkfs("", 0, work, sizeof(work));
			OLED_ShowString(0, 1, "Format Finished", 12, 1);
			HAL_GPIO_WritePin(GPIOC, GPIO_PIN_14, GPIO_PIN_SET);
		}
		else
		{
			OLED_ShowString(0, 0, "Fatfs Failed..", 12, 1);
			HAL_GPIO_WritePin(GPIOC, GPIO_PIN_14, GPIO_PIN_RESET);
		}
		//先读取一次文件到文件列表
		if (f_opendir(&DirInfo, (const TCHAR *)"0:") == FR_OK) /* 打开文件夹目录成功，目录信息已经在dir结构体中保存 */
		{
			f_readdir(&DirInfo, &FileInfo);
			while (f_readdir(&DirInfo, &FileInfo) == FR_OK) /* 读文件信息到文件状态结构体中 */
			{
				if (!FileInfo.fname[0])
					break;
				strcpy(Name_Buffer[name_cnt], FileInfo.fname);
				name_cnt++;
			}
		}

		HAL_Delay(1000); //等待外部IO口电平确定再初始化按键
		Button_Init();	 //初始化按键
		OLED_Clear();
		f_unlink("0:/write.bin");
		Show.mode = MODE_SET_OFFLINE;
		Show.windows = SHOW_OFFLINE;
	}
	else
	{
		Show.mode = MODE_SET_ONLINE;
		Show.windows = SHOW_ONLINE;
	}
	while (1)
	{
		Work_State();
#if !ONLINE
//    NRF_Check_Event(); //检测nrf数据
//    if (NRF_Connect() == 0)
//    {
//    }
#endif
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
			usbd_hid_process_online();
		}
		if (cdc_len)
		{
			tusb_cdc_device_send(&cdc_dev, cdc_buf, cdc_len);
			//			while (HAL_UART_Transmit(&huart2, cdc_buf, cdc_len, 1000) != HAL_OK)
			//			;
			cdc_len = 0;
		}
		HAL_UART_Receive_DMA(&huart2, rx_buffer, BUFFER_SIZE);
		if (recv_end_flag == 1)
		{
			recv_end_flag = 0;
			tusb_cdc_device_send(&cdc_dev, rx_buffer, rx_len);
		}
		tusb_msc_device_loop(&msc_dev);
		break;
	case MODE_SET_OFFLINE: //脱机烧录模式  自动烧录  选择文件和下载算法
		Select_Offline();
		Auto_Fash();
		break;
	case MODE_SET_ALGO: //选择烧录算法（也就是目标芯片）

		break;
	case MODE_SET_FILE: //选择下载文件

		break;
	case MODE_SET_WIRELESS: //无线模式选择模式
		Select_WL_MODE();
		break;
	case MODE_SET_TX: //无线发射端模式
		HAL_UART_Receive_DMA(&huart1, rx_buffer, BUFFER_SIZE);
		usbd_hid_process_wireless_tx();
		break;
	case MODE_SET_RX: //无线接收端模式
		HAL_UART_Receive_DMA(&huart1, rx_buffer, BUFFER_SIZE);
		usbd_hid_process_wireless_rx();
		break;
	default:
		break;
	}
}
void Show_Duty(void)
{
	static uint8_t temp;

	if (Show.windows != temp)
	{
		temp = Show.windows;
		OLED_Clear();
	}
	switch (Show.windows)
	{
	case SHOW_MENU:
		Menu_Show();
		break;
	case SHOW_FLM:
		Display_FLM();
		break;
	case SHOW_BIN:
		Display_BIN();
		break;
	case SHOW_AUTO:

		break;
	case SHOW_ONLINE:

		break;
	case SHOW_OFFLINE:
		Display_Offline();
		break;
	case SHOW_WIRELESS:
		Display_WL_MODE();
		break;
	default:
		break;
	}
}
