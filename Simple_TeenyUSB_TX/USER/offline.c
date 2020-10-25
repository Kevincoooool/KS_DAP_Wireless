/*
 * @Descripttion: 
 * @version: 
 * @Author: Kevincoooool
 * @Date: 2020-08-21 20:06:12
 * @LastEditors  : Kevincoooool
 * @LastEditTime : 2020-10-15 19:02:14
 * @FilePath     : \Simple_TeenyUSB_TX\USER\offline.c
 */
#include "offline.h"
#include "ff.h"		/* FatFs configurations and declarations */
#include "diskio.h" /* Declarations of low level disk I/O functions */
#include "swd_host.h"
#include "SWD_flash.h"
#include "gpio.h"
#include "string.h"
#include "include.h"
/***********************文件系统使用定义************************/
extern FIL fnew; /* file objects */
extern FILINFO FileInfo;
extern DIR DirInfo;
extern FATFS fs; /* Work area (file system object) for logical drives */
extern FRESULT Res;
extern UINT br, bw;			 /* File R/W count */
extern BYTE work[FF_MAX_SS]; /* Work area (larger is better for processing time) */

/***********************变量定义************************/
char rData[1024] = "";
uint8_t readflag = 1;
uint32_t addr = 0;
uint32_t i = 0;
uint16_t bytesread;
char Name_Buffer[20][20];
int8_t file_name = 0, name_cnt = 0;

extern uint8_t button_num;
extern uint8_t Select_algo;
extern uint8_t Select_file;
extern uint8_t show_page;
uint8_t FLASH_SWD(uint8_t *File)
{
	Res = f_open(&fnew, (const TCHAR *)File, FA_READ);
	if (Res == FR_OK)
	{
		static uint32_t progess=0x0, burn_addr = 0x0;
		readflag = 1;
		if (swd_init_debug())
		{
			if (target_opt_init() == ERROR_SUCCESS)
			{
				if (target_opt_erase_chip() != ERROR_SUCCESS)
				{
					return 0;
				}
			}
			else
				return 0;
			target_opt_uninit();
			if (swd_init_debug())
			{

				if (target_flash_init(0x08000000) == ERROR_SUCCESS)
				{

					if (target_flash_erase_chip() == ERROR_SUCCESS)
					{

						while (readflag)
						{
							f_read(&fnew, rData, 1024, (void *)&bytesread);
							
							if (bytesread < 1024)
							{
								readflag = 0;
							}
							if (target_flash_program_page(0x08000000 + burn_addr, (const uint8_t *)&rData[0], 1024) == ERROR_SUCCESS)
							{
								burn_addr += 1024;
								progess = (((double)burn_addr / f_size(&fnew)) * 100);
								//OLED_Show_progress_bar(progess / 10, 12, 12, 0, 30, 12, 1);
								OLED_ShowNumber(50, Y3, progess, 3, 12);
								OLED_ShowString(70, Y3, "%", 12, 1);
							}
							else
								return 0;
						}
						if (swd_init_debug())
						{
							HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_13);
							swd_set_target_reset(0); //复位运行
							OLED_ShowNumber(50, Y3, 100, 3, 12);
							OLED_ShowString(70, Y3, "%", 12, 1);
							for (uint8_t i = 0; i < 8; i++)
								OLED_Show_CH_String(35 + i * 6, Y2, oled_CH5[i], 12, 1);
							HAL_Delay(1000);
							OLED_ShowString(0, Y4, "                   ", 12, 1);
							burn_addr = 0;
							//Display_BIN();
							readflag = 1;
							return 1;
						}
						else
							return 0;
					}
					else
						return 0;
				}
				target_flash_uninit();
			}
			else
				return 0;
		}
		else
			return 0;
	}
	else
		return 0;
	return 0;
}
void Auto_Fash(void)
{
	if (swd_init_debug())
	{
		OLED_ShowString(0, 50, "Connected!!!", 12, 1);
		if (f_open(&fnew, (const TCHAR *)Name_Buffer[Select_file], FA_READ) == FR_OK)
		{
			HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_RESET);
			for (uint8_t i = 0; i < 8; i++)
				OLED_Show_CH_String(35 + i * 6, Y2, oled_CH3[i], 12, 1);
			while (!FLASH_SWD((uint8_t *)Name_Buffer[Select_file]))
			{
				if (button_num == 1)//卡住了可以按下退出
				{
					button_num = 0;
					Show.windows = SHOW_MENU;
					Show.mode = MODE_SET_NORMAL;
					break;
				}
				else if(!swd_init_debug())//芯片断开连接则退出
				{
					//OLED_Init();
					OLED_Clear();
					button_num = 0;
					Show.windows = SHOW_OFFLINE;
					Show.mode = MODE_SET_OFFLINE;
					break;
				}
			}
		}
		else
		{
			OLED_ShowString(0, Y3, "Open Bin failed", 12, 1);
			HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_SET);
		}
	}
	else
	{
		OLED_ShowString(0, 50, "Disconnected", 12, 1);
	}
	
}

void Select_BIN(void)
{
	static uint8_t choose = Y0;
	if (button_num == 1)
	{
		choose += 12;
		if (choose >= Y5)
			choose = Y5;
		OLED_ShowString(110, choose - 12, "  ", 12, 1);
	}
	else if (button_num == 3)
	{
		if (choose >= 12)
			choose -= 12;
		if (choose <= Y0)
			choose = Y0;
		OLED_ShowString(110, choose + 12, "  ", 12, 1);
	}
	else if (button_num == 2)
	{
		Select_file = choose / 12;
		Show.windows = SHOW_OFFLINE;
		Show.mode = MODE_SET_OFFLINE;
		OLED_Clear();
		for (uint8_t i = 0; i < 10; i++)
			OLED_Show_CH_String(29 + i * 6, Y2, oled_CH4[i], 12, 1);
		HAL_Delay(500);
		OLED_Clear();
	}
	button_num = 0;
	OLED_ShowString(110, choose, "<<", 12, 1);
}

void Display_BIN(void)
{
	static uint8_t choose = Y0;
	name_cnt = 0;
	if (f_opendir(&DirInfo, (const TCHAR *)"0:") == FR_OK) /* 打开文件夹目录成功，目录信息已经在dir结构体中保存 */
	{
		f_readdir(&DirInfo, &FileInfo);//先读取一次无用值

		while (f_readdir(&DirInfo, &FileInfo) == FR_OK) /* 读文件信息到文件状态结构体中 */
		{
			if (!FileInfo.fname[0])
				break;
			strcpy(Name_Buffer[name_cnt], FileInfo.fname);
			OLED_ShowNumber(0, choose, (choose + 12) / 12, 1, 12);
			OLED_ShowString(8, choose, ".", 12, 1);
			OLED_ShowString(16, choose, (const uint8_t *)Name_Buffer[name_cnt], 12, 1);
			choose += 12;
			name_cnt++;
		}
	}
	choose = 0;
}
void Display_FLM(void)
{
	static uint8_t choose = Y0;
	for (uint8_t i = 0; i < 6; i++)
	{
		OLED_ShowNumber(0, choose, (i + 1), 1, 12);
		OLED_ShowString(8, choose, ".", 12, 1);
		OLED_ShowString(16, choose, (const uint8_t *)STM32_ALGO[choose / 10].name, 12, 1);
		choose += 10;
	}
	choose = 0;
}

void Select_FLM(void)
{
	static uint8_t choose = Y0;
	
	if (button_num == 1)
	{
		choose += 10;
		if (choose >= Y5)
			choose = Y5;
		OLED_ShowString(110, choose - 10, "  ", 12, 1);
	}
	else if (button_num == 3)
	{
		choose -= 10;
		if (choose <= Y0)
			choose = Y0;
		OLED_ShowString(110, choose + 10, "  ", 12, 1);
	}
	else if (button_num == 2)
	{
		OLED_Clear();
		for (uint8_t i = 0; i < 10; i++)
			OLED_Show_CH_String(29 + i * 6, Y2, oled_CH4[i], 12, 1);
		Select_algo = choose / 10;
		HAL_Delay(500);
		OLED_Clear();
		Show.windows = SHOW_OFFLINE;
		Show.mode = MODE_SET_OFFLINE;
	}
	button_num = 0;
	OLED_ShowString(110, choose, "<<", 12, 1);
}
// f_open(&fnew, (const TCHAR *)"23.txt", FA_CREATE_NEW | FA_WRITE);
// /* Write a message */
// f_write(&fnew, "nihaoya!\r\nnihaoya!", sizeof("nihaoya!\r\nnihaoya!") - 1, &bw);
// f_close(&fnew);

// NRF_OK = NRF_Check();
// if (NRF_OK == 0)
// {
//     NRF_Init(MODEL_TX2, 51);
// }
//	if (f_open(&fnew, (const TCHAR *)"22.txt", FA_READ) == FR_OK)
//	{
//		f_read(&fnew, rData, 20, (void *)&bytesread);
//		sprintf((char*)ccc,rData,20);
//		ccc[20]=0;
//		OLED_ShowString(0, 40, ccc, 12, 1);
//	}

//	  if (f_open(&fnew, (const TCHAR *)"ToyDog.bin", FA_READ) == FR_OK)
//	  {
//		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_RESET);
//		OLED_ShowString(0, 20, "AUTO FLASH", 12, 1);
//		while (!FLASH_SWD("ToyDog.bin"))
//		{
//		  uint8_t WaitTips[] = "...";
//		  OLED_ShowString(75, 30, "          ", 12, 1);
//		  OLED_ShowString(45, 30, "WAIT", 12, 1);
//		  for (i = 0; i < 3; i++)
//		  {
//			OLED_ShowChar(69 + i * 6, 2, WaitTips[i], 12, 1);
//			HAL_Delay(200);
//		  }
//		  OLED_ShowString(75, 30, "       ", 12, 1);
//		}
//		OLED_ShowString(98, 50, "BACK", 12, 1);
//	  }
//	  else
//	  {
//		OLED_ShowString(0, 30, "Open Bin failed", 12, 1);
//		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_SET);
//	  }
// if (!swd_init_debug())
		// {
		// 	OLED_ShowString(0, 50, "Connect Failed!", 12, 1);
		// 	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_RESET);
		// 	HAL_Delay(1000);
		// 	OLED_ShowString(0, 50, "                ", 12, 1);
		// 	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_SET);
		// }
		// else
		// {
		// 	OLED_Clear();
		// 	file_name /= 10;
		// 	if (f_open(&fnew, (const TCHAR *)Name_Buffer[file_name], FA_READ) == FR_OK)
		// 	{
		// 		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_RESET);
		// 		for (uint8_t i = 0; i < 8; i++)
		// 			OLED_Show_CH_String(35 + i * 6, 0, oled_CH3[i], 12, 1);
		// 		while (!FLASH_SWD((uint8_t *)Name_Buffer[file_name]))
		// 		{
		// 			if (button_num == 1)
		// 			{
		// 				Show.windows = 0;
		// 				break;
		// 			}
		// 			uint8_t WaitTips[] = "....";
		// 			OLED_ShowString(32, 30, "             ", 12, 1);
		// 			OLED_ShowString(0, 30, "WAIT", 12, 1);
		// 			for (uint8_t i = 0; i < 4; i++)
		// 			{
		// 				OLED_ShowChar(32 + i * 6, 30, WaitTips[i], 12, 1);
		// 				HAL_Delay(500);
		// 			}
		// 			OLED_ShowString(35, 30, "               ", 12, 1);
		// 		}
		// 	}
		// 	else
		// 	{
		// 		OLED_ShowString(0, 30, "Open Bin failed", 12, 1);
		// 		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_SET);
		// 	}
		// }

