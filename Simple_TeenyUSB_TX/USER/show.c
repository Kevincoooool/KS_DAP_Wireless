
#include "show.h"
#include "oledfont.h"
#include "oled.h"
#include "swd_host.h"
#include "SWD_flash.h"
#include "include.h"
#include "flash_blob.h"
#include "ff.h"		/* FatFs configurations and declarations */
#include "diskio.h" /* Declarations of low level disk I/O functions */

_Show Show = {0, 0};
extern FIL fnew; /* file objects */
extern FILINFO FileInfo;
extern DIR DirInfo;
extern FATFS fs; /* Work area (file system object) for logical drives */
extern FRESULT Res;
extern UINT br, bw;			 /* File R/W count */
extern BYTE work[FF_MAX_SS]; /* Work area (larger is better for processing time) */
extern char Name_Buffer[20][20];
uint8_t Select_file = 0;
extern uint8_t Select_algo;
extern uint8_t button_num;
/**************************************************************************
函数功能：OLED显示
入口参数：无
返回  值：无
**************************************************************************/
uint8_t Select_Mode(void)
{
	static uint8_t choose = Y2;
	if (button_num == 1)
	{
		choose += 12;
		if (choose >= Y4)
			choose = Y4;
		OLED_ShowString(0, choose - 12, "  ", 12, 1);
	}
	else if (button_num == 3)
	{
		choose -= 12;
		if (choose < Y2)
			choose = Y2;
		OLED_ShowString(0, choose + 12, "  ", 12, 1);
	}
	else if (button_num == 2)
	{
		OLED_Clear();
		if (choose == Y2)
		{
			Show.mode = MODE_SET_ONLINE;
			Show.windows = SHOW_ONLINE;
			for (uint8_t i = 0; i < 12; i++)
				OLED_Show_CH_String(Line1_Begin + i * 6, Y2, oled_CH0[i], 12, 1);
		}
		else if (choose == Y3)
		{
			Show.mode = MODE_SET_OFFLINE;
			Show.windows = SHOW_OFFLINE;
			button_num = 0;
		}
		if (choose == Y4)
		{
			Show.windows = SHOW_WIRELESS;
			Show.mode = MODE_SET_WIRELESS;
			for (uint8_t i = 0; i < 12; i++)
				OLED_Show_CH_String(Line1_Begin + i * 6, Y2, oled_CH2[i], 12, 1);
		}
		button_num = 0;
		return Show.mode;
	}
	button_num = 0;
	OLED_ShowString(0, choose, ">>", 12, 1);

	return MODE_SET_NORMAL;
}
//首页菜单显示
void Menu_Show(void)
{
	///////////////////////////////第一行///////////////////////////////////
	//显示
	OLED_Show_CH(20 + 00, 0, 0, 12, 1);
	OLED_Show_CH(20 + 12, 0, 1, 12, 1);
	OLED_Show_CH(20 + 24, 0, 2, 12, 1);
	OLED_Show_CH(20 + 36, 0, 3, 12, 1);
	OLED_Show_CH(20 + 48, 0, 4, 12, 1);
	OLED_Show_CH(20 + 60, 0, 5, 12, 1);
	OLED_Show_CH(20 + 72, 0, 6, 12, 1);
	OLED_Show_CH(20 + 84, 0, 7, 12, 1);
	OLED_ShowString(0, Y1, "================", 12, 1);
	///////////////////////////////第三行///////////////////////////////////
	//有线模式
	for (uint8_t i = 0; i < 12; i++)
		OLED_Show_CH_String(Line1_Begin + i * 6, Y2, oled_CH0[i], 12, 1);
	///////////////////////////////第四行/////////////////////////////////
	//离线模式
	for (uint8_t i = 0; i < 12; i++)
		OLED_Show_CH_String(Line1_Begin + i * 6, Y3, oled_CH1[i], 12, 1);
	///////////////////////////////第五行///////////////////////////////////
	//无线模式
	for (uint8_t i = 0; i < 12; i++)
		OLED_Show_CH_String(Line1_Begin + i * 6, Y4, oled_CH2[i], 12, 1);
	OLED_Refresh_Gram(); //开始显示
}
//脱机烧录模式显示
void Display_Offline(void)
{
	///////////////////////////////第一行///////////////////////////////////
	//下载算法
	OLED_ShowNumber(0, Y0, 1, 1, 12);
	OLED_ShowString(8, Y0, ".", 12, 1);
	OLED_ShowString(16, Y0, (const uint8_t *)STM32_ALGO[Select_algo].name, 12, 1);
	///////////////////////////////第二行///////////////////////////////////
	//下载文件
	OLED_ShowNumber(0, Y1, 2, 1, 12);
	OLED_ShowString(8, Y1, ".", 12, 1);
	OLED_ShowString(16, Y1, (const uint8_t *)Name_Buffer[Select_file], 12, 1);
	///////////////////////////////第三行/////////////////////////////////
	// ///离线模式
	// for (uint8_t i = 0; i < 12; i++)
	// 	OLED_Show_CH_String(Line1_Begin + i * 6, Y3, oled_CH1[i], 12, 1);
	// ///////////////////////////////第五行///////////////////////////////////
	// for (uint8_t i = 0; i < 12; i++)
	// 	OLED_Show_CH_String(Line1_Begin + i * 6, Y4, oled_CH2[i], 12, 1);
	OLED_Refresh_Gram(); //开始显示
}
//无线模式选择
void Display_WL_MODE(void)
{
	///////////////////////////////第一行///////////////////////////////////
	//下载算法
	OLED_ShowNumber(0, Y0, 1, 1, 12);
	OLED_ShowString(8, Y0, ".", 12, 1);
	for (uint8_t i = 0; i < 10; i++)
		OLED_Show_CH_String(Line1_Begin + i * 6, Y0, oled_CH6[i], 12, 1);
	///////////////////////////////第二行///////////////////////////////////
	//下载文件
	OLED_ShowNumber(0, Y1, 2, 1, 12);
	OLED_ShowString(8, Y1, ".", 12, 1);
	for (uint8_t i = 0; i < 10; i++)
		OLED_Show_CH_String(Line1_Begin + i * 6, Y1, oled_CH7[i], 12, 1);
	///////////////////////////////第三行/////////////////////////////////
	// ///离线模式
	// for (uint8_t i = 0; i < 12; i++)
	// 	OLED_Show_CH_String(Line1_Begin + i * 6, Y3, oled_CH1[i], 12, 1);
	// ///////////////////////////////第五行///////////////////////////////////
	// for (uint8_t i = 0; i < 12; i++)
	// 	OLED_Show_CH_String(Line1_Begin + i * 6, Y4, oled_CH2[i], 12, 1);
	OLED_Refresh_Gram(); //开始显示
}
//选择脱机烧录模式中的下载算法和文件
void Select_Offline(void)
{
	static uint8_t choose = Y0;
	if (button_num == 1)
	{
		choose += 12;
		if (choose >= Y1)
			choose = Y1;
		OLED_ShowString(110, choose - 12, "  ", 12, 1);
	}
	else if (button_num == 3)
	{
		if (choose >= 12)
			choose -= 12;
		if (choose < 12)
			choose = Y0;
		OLED_ShowString(110, choose + 12, "  ", 12, 1);
	}
	else if (button_num == 2)
	{
		if (choose == Y0)
		{
			Show.windows = SHOW_FLM;
			Show.mode = MODE_SET_ALGO;
		}
		else if (choose == Y1)
		{
			Show.windows = SHOW_BIN;
			Show.mode = MODE_SET_FILE;
		}
	}
	button_num = 0;
	OLED_ShowString(110, choose, "<<", 12, 1);
}
//选择无限模式是发射还是接受
void Select_WL_MODE(void)
{
	static uint8_t choose = Y0;
	OLED_ShowString(110, choose, "<<", 12, 1);
	if (button_num == 1)
	{
		choose += 12;
		if (choose >= Y1)
			choose = Y1;
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
		OLED_Clear();
		if (choose == Y0)
		{
			Show.windows = SHOW_WL_TX;
			Show.mode = MODE_SET_TX;
			for (uint8_t i = 0; i < 10; i++)
				OLED_Show_CH_String(Line1_Begin + i * 6, Y2, oled_CH6[i], 12, 1);
		}
		else if (choose == Y1)
		{
			Show.windows = SHOW_WL_RX;
			Show.mode = MODE_SET_RX;
			for (uint8_t i = 0; i < 10; i++)
				OLED_Show_CH_String(Line1_Begin + i * 6, Y2, oled_CH7[i], 12, 1);
		}
	}

	button_num = 0;
}
void OLED_Show_FLM(void)
{

	uint8_t page;
	static uint8_t page_temp;
	if (page_temp != page)
	{
		page_temp = page;
		OLED_Clear();
	}
	Display_FLM();
	while (1)
	{
		Select_FLM();
		if (Show.windows == 0)
			break;
	}
	OLED_Refresh_Gram(); //开始显示
}

uint16_t test_bit = 0, test_max = 6;
uint16_t test_temp = 0;

void OLED_Show_BIN(void)
{
	uint8_t page;
	static uint8_t page_temp;
	if (page_temp != page)
	{
		page_temp = page;
		OLED_Clear();
	}
	Display_BIN();
	while (1)
	{
		Select_BIN();
		if (Show.windows == 0)
			break;
	}
	OLED_Refresh_Gram(); //开始显示
}
extern char Name_Buffer[20][20];
extern uint8_t file_name;
void OLED_Show_Auto(void)
{
	uint8_t Continue = 1;
	if (swd_init_debug() && Continue == 1)
	{
		OLED_Clear();
		file_name /= 10;
		if (f_open(&fnew, (const TCHAR *)Name_Buffer[file_name], FA_READ) == FR_OK)
		{
			HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_RESET);
			for (uint8_t i = 0; i < 8; i++)
				OLED_Show_CH_String(35 + i * 6, Y0, oled_CH3[i], 12, 1);
			while (!FLASH_SWD((uint8_t *)Name_Buffer[file_name]))
			{
				if (button_num == 1)
				{
					Show.windows = 0;
					break;
				}
				uint8_t WaitTips[] = "....";
				OLED_ShowString(62, Y4, "             ", 12, 1);
				OLED_ShowString(30, Y4, "WAIT", 12, 1);
				for (uint8_t i = 0; i < 4; i++)
				{
					OLED_ShowChar(62 + i * 6, Y4, WaitTips[i], 12, 1);
					HAL_Delay(500);
				}
				OLED_ShowString(65, Y4, "               ", 12, 1);
			}
			Continue = 0;
			if (swd_init_debug())
			{
				Continue = 0;
			}
		}
		else
		{
			OLED_ShowString(0, 30, "Open Bin failed", 12, 1);
			HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_SET);
		}
	}
	else
	{
		Continue = 1;
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
		OLED_Show_Auto();
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
