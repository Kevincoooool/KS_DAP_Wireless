
#include "show.h"
#include "oledfont.h"
#include "oled.h"
#include "swd_host.h"
#include "SWD_flash.h"
#include "ff.h"		/* FatFs configurations and declarations */
#include "diskio.h" /* Declarations of low level disk I/O functions */
#define Line1_Begin 29
#define Line2_Begin 5
#define Line3_Begin 5
#define Line4_Begin 30
#define Line5_Begin 0

#define X_Begin 0
#define Y_Begin 47
#define Z_Begin 95

#define Line1_Begin1 0
#define Line2_Begin1 0
#define Line3_Begin1 40
#define Line4_Begin1 0
#define Line5_Begin1 0

#define Y0 0
#define Y1 14
#define Y2 Y1 + 12
#define Y3 Y2 + 12
#define Y4 Y3 + 12
#define Y5 Y4 + 12

struct _Show Show;
extern FIL fnew; /* file objects */
extern FILINFO FileInfo;
extern DIR DirInfo;
extern FATFS fs; /* Work area (file system object) for logical drives */
extern FRESULT Res;
extern UINT br, bw;			 /* File R/W count */
extern BYTE work[FF_MAX_SS]; /* Work area (larger is better for processing time) */

unsigned char Send_Count; //串口需要发送的数据个数
float Vol;
extern uint8_t button_num;
/**************************************************************************
函数功能：OLED显示
入口参数：无
返回  值：无
**************************************************************************/
void Select_Menu(void)
{
	static uint8_t choose = Y2;
	Show_Duty();
	if (button_num == 1)
	{
		choose += 12;
		if (choose >= Y4)
			choose = Y4;
		OLED_ShowString(0, choose-12, "  ", 12, 1);
	}
	else if (button_num == 3)
	{
		choose -= 12;
		if (choose < Y2)
			choose = Y2;
		OLED_ShowString(0, choose+12, "  ", 12, 1);
	}
	else if (button_num == 2)
	{
		OLED_Clear();
		if (choose == Y2)
			Show.windows = 1;
		else if (choose == Y3)
			Show.windows = 2;
		if (choose == Y4)
			Show.windows = 3;
	}
	button_num = 0;
	OLED_ShowString(0, choose, ">>", 12, 1);
}
void oled_show(void)
{
	static uint8_t page, page_temp, show_mode = 1;
	if (page != page_temp) //切换页面先清屏
	{
		page_temp = page;
		OLED_Clear();
	}
	///////////////////////////////第一行///////////////////////////////////
	//显示
	OLED_Show_CH(Line1_Begin + 00, 0, 0, 12, 1);
	OLED_Show_CH(Line1_Begin + 12, 0, 1, 12, 1);
	OLED_Show_CH(Line1_Begin + 24, 0, 2, 12, 1);
	OLED_Show_CH(Line1_Begin + 36, 0, 3, 12, 1);
	OLED_Show_CH(Line1_Begin + 48, 0, 4, 12, 1);
	OLED_ShowString(0, Y1, "================", 12, 1);
	///////////////////////////////第二行///////////////////////////////////
	//显示电压
	for (uint8_t i = 0; i < 12; i++)
		OLED_Show_CH_String(Line1_Begin + i * 6, Y2, oled_CH0[i], 12, 1);
	///////////////////////////////第三行/////////////////////////////////
	//显示遥控数据
	for (uint8_t i = 0; i < 12; i++)
		OLED_Show_CH_String(Line1_Begin + i * 6, Y3, oled_CH1[i], 12, 1);
	///////////////////////////////第五行///////////////////////////////////
	for (uint8_t i = 0; i < 12; i++)
		OLED_Show_CH_String(Line1_Begin + i * 6, Y4, oled_CH2[i], 12, 1);
	OLED_Refresh_Gram(); //开始显示
}

uint16_t set_bit = 0, bit_max = 6;
uint16_t set_temp = 0x0000;

void OLED_Show_FLM(void)
{

	uint8_t mode, page;
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
	uint8_t mode, page;
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
	if (swd_init_debug())
	{
		OLED_Clear();
		file_name /= 10;
		if (f_open(&fnew, (const TCHAR *)Name_Buffer[file_name], FA_READ) == FR_OK)
		{
			HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_RESET);
			OLED_ShowString(20, 0, "START FLASH", 12, 1);
			while (!FLASH_SWD((uint8_t *)Name_Buffer[file_name]))
			{
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
			//OLED_ShowString(98, 50, "BACK", 12, 1);
		}
		else
		{
			OLED_ShowString(0, 30, "Open Bin failed", 12, 1);
			HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_SET);
		}
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
	case 0:
		oled_show();
		break;
	case 1:
		OLED_Show_FLM();
		break;
	case 2:
		OLED_Show_BIN();
		break;
	case 3:
		OLED_Show_Auto();
		break;
	default:
		break;
	}
}
