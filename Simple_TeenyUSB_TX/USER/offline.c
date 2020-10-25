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
uint32_t progess, address = 0x0;
extern uint8_t button_num;
extern uint8_t Select_algo;
extern uint8_t show_page;
uint8_t FLASH_SWD(uint8_t *File)
{
	Res = f_open(&fnew, (const TCHAR *)File, FA_READ);
	if (Res == FR_OK)
	{
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
					OLED_ShowString(30, 20, "Erase Chip", 16, 1);
					if (target_flash_erase_chip() == ERROR_SUCCESS)
					{
						OLED_ShowString(30, 20, "           ", 16, 1);
						while (readflag)
						{
							f_read(&fnew, rData, 1024, (void *)&bytesread);
							if (bytesread < 1024)
							{
								readflag = 0;
							}
							if (target_flash_program_page(0x08000000 + address, (const uint8_t *)&rData[0], 1024) == ERROR_SUCCESS)
							{
								address += 1024;
								progess = (((double)address / f_size(&fnew)) * 100);
								//OLED_Show_progress_bar(progess / 10, 12, 12, 0, 30, 12, 1);
								OLED_ShowNumber(40, 20, progess, 3, 16);
								OLED_ShowString(70, 20, "%", 16, 1);
							}
							else
								return 0;
						}
						if (swd_init_debug())
						{
							HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_13);
							swd_set_target_reset(0); //复位运行
							OLED_ShowNumber(40, 20, 100, 3, 16);
							OLED_ShowString(70, 20, "%", 16, 1);
							for (uint8_t i = 0; i < 8; i++)
								OLED_Show_CH_String(35 + i * 6, Y4, oled_CH5[i], 12, 1);
							HAL_Delay(1000);
							OLED_Clear();
							file_name = 0;
							name_cnt = 0;
							address = 0;
							Display_BIN();
							//Show.windows = 3;
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
void Select_BIN(void)
{
	if (button_num == 1)
	{
		file_name += 10;
		if (file_name >= name_cnt * 10)
			file_name = name_cnt * 10 - 10;
		OLED_ShowString(110, file_name - 10, "  ", 12, 1);
	}
	else if (button_num == 3)
	{
		file_name -= 10;
		if (file_name < 10)
			file_name = 0;
		OLED_ShowString(110, file_name + 10, "  ", 12, 1);
	}
	else if (button_num == 2)
	{
		if (!swd_init_debug())
		{
			OLED_ShowString(0, 50, "Connect Failed!", 12, 1);
			HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_RESET);
			HAL_Delay(1000);
			OLED_ShowString(0, 50, "                ", 12, 1);
			HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_SET);
		}
		else
		{
			OLED_Clear();
			file_name /= 10;
			if (f_open(&fnew, (const TCHAR *)Name_Buffer[file_name], FA_READ) == FR_OK)
			{
				HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_RESET);
				for (uint8_t i = 0; i < 8; i++)
					OLED_Show_CH_String(35 + i * 6, 0, oled_CH3[i], 12, 1);
				while (!FLASH_SWD((uint8_t *)Name_Buffer[file_name]))
				{
					if (button_num == 1)
					{
						Show.windows = 0;
						break;
					}
					uint8_t WaitTips[] = "....";
					OLED_ShowString(32, 30, "             ", 12, 1);
					OLED_ShowString(0, 30, "WAIT", 12, 1);
					for (uint8_t i = 0; i < 4; i++)
					{
						OLED_ShowChar(32 + i * 6, 30, WaitTips[i], 12, 1);
						HAL_Delay(500);
					}
					OLED_ShowString(35, 30, "               ", 12, 1);
				}
			}
			else
			{
				OLED_ShowString(0, 30, "Open Bin failed", 12, 1);
				HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_SET);
			}
		}
	}

	button_num = 0;
	OLED_ShowString(110, file_name, "<<", 12, 1);
}

void Display_BIN(void)
{
	file_name = 0;
	name_cnt = 0;
	f_unlink("0:write.bin");
	if (f_opendir(&DirInfo, (const TCHAR *)"0:") == FR_OK) /* 打开文件夹目录成功，目录信息已经在dir结构体中保存 */
	{
		f_readdir(&DirInfo, &FileInfo);

		while (f_readdir(&DirInfo, &FileInfo) == FR_OK) /* 读文件信息到文件状态结构体中 */
		{
			if (!FileInfo.fname[0])
				break;
			strcpy(Name_Buffer[name_cnt], FileInfo.fname);
			OLED_ShowNumber(0, file_name, (file_name + 10) / 10, 1, 12);
			OLED_ShowString(8, file_name, ".", 12, 1);
			OLED_ShowString(16, file_name, (const uint8_t *)Name_Buffer[name_cnt], 12, 1);
			file_name += 10;
			name_cnt++;
		}
	}
	OLED_ShowString(110, 0, "<<", 12, 1);
	file_name = 0;
}
void Display_FLM(void)
{
	file_name = 0;
	for (uint8_t i = 0; i < 6; i++)
	{
		OLED_ShowNumber(0, i * 10, (i + 1), 1, 12);
		OLED_ShowString(8, i * 10, ".", 12, 1);
		OLED_ShowString(16, i * 10, (const uint8_t *)STM32_ALGO[i].name, 12, 1);
	}
	OLED_ShowString(110, 0, "<<", 12, 1);
}
extern uint8_t show_dap;
void Select_FLM(void)
{
	if (button_num == 1)
	{
		file_name += 10;
		if (file_name >= 50)
			file_name = 50;
		OLED_ShowString(110, file_name - 10, "  ", 12, 1);
	}
	else if (button_num == 3)
	{
		file_name -= 10;
		if (file_name < 10)
			file_name = 0;
		OLED_ShowString(110, file_name + 10, "  ", 12, 1);
	}
	else if (button_num == 2)
	{
		OLED_Clear();
		for (uint8_t i = 0; i < 10; i++)
			OLED_Show_CH_String(29 + i * 6, Y2, oled_CH4[i], 12, 1);
		Select_algo = file_name / 10;
		HAL_Delay(2000);
		show_dap = 1;
		OLED_Clear();
		Show.windows = 0;
	}
	button_num = 0;
	OLED_ShowString(110, file_name, "<<", 12, 1);
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
