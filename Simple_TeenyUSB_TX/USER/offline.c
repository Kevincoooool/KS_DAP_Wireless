/*
 * @Descripttion: 
 * @version: 
 * @Author: Kevincoooool
 * @Date: 2020-08-21 20:06:12
 * @LastEditors  : Kevincoooool
 * @LastEditTime : 2021-05-22 17:17:20
 * @FilePath     : \Simple_TeenyUSB_TX\USER\offline.c
 */
#include "offline.h"

/***********************文件系统使用定义************************/
extern FIL fnew; /* file objects */
extern FILINFO FileInfo;
extern DIR DirInfo;
extern FATFS fs; /* Work area (file system object) for logical drives */
extern FRESULT Res;
extern UINT br, bw;			 /* File R/W count */
extern BYTE work[FF_MAX_SS]; /* Work area (larger is better for processing time) */
uint8_t *rData[1024], Check_Data[1024];

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
uint8_t Need_Next = 0, Burn_cnt = 0;
#if OLED_0_96
/***********************变量定义************************/

uint8_t FLASH_SWD(uint8_t *File)
{
	Res = f_open(&fnew, (const TCHAR *)File, FA_READ);
	if (Res == FR_OK)
	{
		uint32_t progess = 0x0, burn_addr = 0x0, time1, time2,time3;
		readflag = 1;
		if (swd_init_debug())
		{

			if (swd_init_debug())
			{
				time1 = HAL_GetTick();
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

								swd_read_memory(0x08000000 + burn_addr, Check_Data, 1024);
								if (memcmp(Check_Data, rData, 1024) != 0)
								{
									OLED_Clear();
									OLED_ShowString(10, Y1, "Verify Faild!!", 12, 1);
									HAL_Delay(1000);
									OLED_Clear();
									burn_addr = 0;
									readflag = 1;
									return 1;
								}
								burn_addr += 1024;
								progess = (((double)burn_addr / f_size(&fnew)) * 100);
								//OLED_Show_progress_bar(progess / 10, 12, 12, 0, 30, 12, 1);
								OLED_ShowNumber(50, Y0, progess, 3, 12, 1);
								OLED_ShowString(70, Y0, "%", 12, 1);
							}
							else
								return 0;
						}
						time2 = HAL_GetTick();
						if (swd_init_debug())
						{
							Burn_cnt++;
							OLED_ShowNumber(0, Y0, (time2 - time1) / 1000, 2, 12, 1);
							OLED_ShowString(13, Y0, ".", 12, 1);
							OLED_ShowNumber(18, Y0, ((time2 - time1) / 10) % 100, 2, 12, 1);
							OLED_ShowString(30, Y0, "S", 12, 1);
							time3 = (time2 - time1) / 1000 + (((time2 - time1) / 10) % 100)/100;

							OLED_ShowNumber(80, Y0, f_size(&fnew) / time3, 2, 12, 1);
							OLED_ShowString(95, Y0, "Kb/s", 12, 1);

							HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_13);
							swd_set_target_reset(0); //复位运行
							OLED_ShowNumber(50, Y0, 100, 3, 12, 1);
							OLED_ShowString(70, Y0, "%", 12, 1);
							for (uint8_t i = 0; i < 8; i++)
								OLED_Show_CH_String(35 + i * 6, Y2, oled_CH5[i], 12, 1);
							HAL_Delay(1000);
							OLED_Clear();
							burn_addr = 0;
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
		OLED_ShowString(0, Y4, "Connected!!!", 12, 1);
		OLED_ShowNumber(100, Y4, Burn_cnt, 4, 12, 1);
		if (Need_Next == 1 || button_num == 9)
		{
			if (strstr(Name_Buffer[Select_file], "HEX"))
			{
				if (f_open(&fnew, (const TCHAR *)Name_Buffer[Select_file], FA_READ) == FR_OK)
				{
					if (HexFormatUncode((uint8_t *)Name_Buffer[Select_file]) != 1)
					{
						OLED_Clear();
						OLED_ShowString(0, Y2, "Error!!", 12, 1);
					}
					else
					{
						//OLED_Clear();
						HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_RESET);
						for (uint8_t i = 0; i < 8; i++)
							OLED_Show_CH_String(35 + i * 6, Y3, oled_CH3[i], 12, 1); //开始烧录
						while (!FLASH_SWD((uint8_t *)"write.bin"))					 //打开文件
						{
							if (button_num == 1) //卡住了可以按下退出
							{
								button_num = 0;
								Show.windows = SHOW_MENU;
								Show.mode = MODE_SET_NORMAL;
								break;
							}
							else if (!swd_init_debug()) //芯片断开连接则退出
							{
								OLED_Clear();
								button_num = 0;
								Show.windows = SHOW_OFFLINE;
								Show.mode = MODE_SET_OFFLINE;
								break;
							}
						}
						//f_unlink("0:/write.bin");
						//如果烧录完了还连接着芯片
						if (swd_init_debug())
						{
							Need_Next = 0;
						}
					}
				}
				else
				{
					OLED_Clear();
					OLED_ShowString(0, Y2, "Open HEX failed", 12, 1);
					HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_SET);
				}
			}
			else
			{
				if (f_open(&fnew, (const TCHAR *)Name_Buffer[Select_file], FA_READ) == FR_OK) //如果存在这个文件
				{
					OLED_Clear();
					HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_RESET);
					for (uint8_t i = 0; i < 8; i++)
						OLED_Show_CH_String(35 + i * 6, Y2, oled_CH3[i], 12, 1); //开始烧录
					while (!FLASH_SWD((uint8_t *)Name_Buffer[Select_file]))		 //打开文件
					{
						if (button_num == 1) //卡住了可以按下退出
						{
							button_num = 0;
							Show.windows = SHOW_MENU;
							Show.mode = MODE_SET_NORMAL;
							break;
						}
						else if (!swd_init_debug()) //芯片断开连接则退出
						{
							OLED_Clear();
							button_num = 0;
							Show.windows = SHOW_OFFLINE;
							Show.mode = MODE_SET_OFFLINE;
							break;
						}
					}
					//如果烧录完了还连接着芯片
					if (swd_init_debug())
					{
						Need_Next = 0;
					}
				}
				else
				{
					OLED_ShowString(0, Y2, "Open Bin failed", 12, 1);
					HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_SET);
				}
			}
		}
	}
	else
	{
		Need_Next = 1;
		OLED_ShowNumber(100, Y4, Burn_cnt, 4, 12, 1);
		OLED_ShowString(0, Y4, "Disconnected", 12, 1);
	}
}
MENU_T g_tMenu_BIN;
char *g_Menu_BIN_Text[20];
void Display_BIN(void)
{
	static uint8_t fRefresh = 1;
	static uint8_t s_MenuInit = 0;
	if (s_MenuInit == 0)
	{
		name_cnt = 0;
		memset(g_Menu_BIN_Text, 0, sizeof(g_Menu_BIN_Text));
		if (f_opendir(&DirInfo, (const TCHAR *)"0:") == FR_OK) /* 打开文件夹目录成功，目录信息已经在dir结构体中保存 */
		{
			f_readdir(&DirInfo, &FileInfo);					//先读取一次无用值
			while (f_readdir(&DirInfo, &FileInfo) == FR_OK) /* 读文件信息到文件状态结构体中 */
			{
				if (!FileInfo.fname[0])
				{
					for (uint8_t i = 0; i < name_cnt; i++)
					{
						g_Menu_BIN_Text[i] = Name_Buffer[i];
					}
					g_Menu_BIN_Text[name_cnt] = "&";
					break;
				}
				strcpy(Name_Buffer[name_cnt], FileInfo.fname);
				name_cnt++;
			}
		}
		s_MenuInit = 1;
		g_tMenu_BIN.Left = MENU_LEFT;
		g_tMenu_BIN.Top = MENU_TOP;
		g_tMenu_BIN.Height = MENU_HEIGHT;
		g_tMenu_BIN.Width = MENU_WIDTH;
		g_tMenu_BIN.LineCap = MENU_CAP;
		g_tMenu_BIN.Font = 12;
		g_tMenu_BIN.ViewLine = MENU_HEIGHT / g_tMenu_BIN.Font;
		g_tMenu_BIN.RollBackEn = 1; /* 允许回滚 */
		g_tMenu_BIN.GBK = 0;
		g_tMenu_BIN.ActiveBackColor = 0;					  /* 选中行背景色ID */
		LCD_InitMenu(&g_tMenu_BIN, (char **)g_Menu_BIN_Text); /* 初始化菜单结构 */
	}

	if (fRefresh) /* 重新进入就 刷新整个界面 */
	{
		fRefresh = 0;
		LCD_DispMenu(&g_tMenu_BIN);
		if (g_tMenu_BIN.Cursor == 0)
		{
			;
		}
	}

	/* 有键按下 */
	switch (button_num)
	{
	case 3: /* S键 上 */
		OLED_Clear();
		LCD_MoveUpMenu(&g_tMenu_BIN);
		break;
	case 2: /* S键 上 */
		OLED_Clear();
		fRefresh = 1;
		for (uint8_t i = 0; i < 10; i++)
			OLED_Show_CH_String(29 + i * 6, Y2, oled_CH4[i], 12, 1);
		Select_file = g_tMenu_BIN.Cursor;
		HAL_Delay(500);
		OLED_Clear();
		Show.windows = SHOW_OFFLINE;
		Show.mode = MODE_SET_OFFLINE;
		break;
	case 1: /* S键 上 */
		OLED_Clear();
		LCD_MoveDownMenu(&g_tMenu_BIN);
		break;
	}
	button_num = 0;
}
MENU_T g_tMenu_FLM;
const uint8_t *g_Menu1_Text[] = {
	"1.STM32F0XX",
	"2.STM32F1XX",
	"3.STM32F3XX",
	"4.STM32F4XX",
	"5.STM32F7XX",
	"6.STM32H7XX",
	"7.HK32F0XXX",
	"8.HK32F1XXX",
	"9.GD32F0XXX",
	"10.GD32F1XX",
	"11.MM32F1XX",
	"&",
};
void Display_FLM(void)
{
	uint8_t fRefresh;
	static uint8_t s_MenuInit = 0;

	if (s_MenuInit == 0)
	{
		s_MenuInit = 1;

		g_tMenu_FLM.Left = MENU_LEFT;
		g_tMenu_FLM.Top = MENU_TOP;
		g_tMenu_FLM.Height = MENU_HEIGHT;
		g_tMenu_FLM.Width = MENU_WIDTH;
		g_tMenu_FLM.LineCap = MENU_CAP;
		g_tMenu_FLM.Font = 12;
		g_tMenu_FLM.ViewLine = MENU_HEIGHT / g_tMenu_FLM.Font;
		g_tMenu_FLM.RollBackEn = 1; /* 允许回滚 */
		g_tMenu_FLM.GBK = 0;
		g_tMenu_FLM.ActiveBackColor = 0;				   /* 选中行背景色ID */
		LCD_InitMenu(&g_tMenu_FLM, (char **)g_Menu1_Text); /* 初始化菜单结构 */
	}

	if (fRefresh) /* 刷新整个界面 */
	{
		fRefresh = 0;
		LCD_DispMenu(&g_tMenu_FLM);
		if (g_tMenu_FLM.Cursor == 0)
		{
			;
		}
	}

	/* 有键按下 */
	switch (button_num)
	{
	case 3: /* S键 上 */
		LCD_MoveUpMenu(&g_tMenu_FLM);
		break;
	case 2: /* S键 上 */
		OLED_Clear();
		fRefresh = 1;
		for (uint8_t i = 0; i < 10; i++)
			OLED_Show_CH_String(29 + i * 6, Y2, oled_CH4[i], 12, 1);
		Select_algo = g_tMenu_FLM.Cursor;
		HAL_Delay(500);
		OLED_Clear();
		Show.windows = SHOW_OFFLINE;
		Show.mode = MODE_SET_OFFLINE;
		break;
	case 1: /* S键 上 */
		LCD_MoveDownMenu(&g_tMenu_FLM);
		break;
	}
	button_num = 0;
}
//选择脱机烧录模式中的下载算法和文件
void Select_Offline(void)
{
	static uint8_t choose = Y2;
	if (button_num == 1)
	{
		choose += 12;
		if (choose >= Y2)
			choose = Y2;
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
		else if (choose == Y2)
		{
			Need_Next = 1;
		}
	}
	button_num = 0;
	OLED_ShowString(110, choose, "<<", 12, 1);
}
#else
/***********************文件系统使用定义************************/

/***********************变量定义************************/

uint8_t FLASH_SWD(uint8_t *File)
{
	Res = f_open(&fnew, (const TCHAR *)File, FA_READ);
	if (Res == FR_OK)
	{
		uint32_t progess = 0x0, burn_addr = 0x0, time1, time2,time3;
		readflag = 1;
		if (swd_init_debug())
		{
			if (swd_init_debug())
			{
				time1 = HAL_GetTick();
				if (target_flash_init(0x08000000) == ERROR_SUCCESS)
				{
					OLED_Show_CH_String(35 + i * 6, Y2, oled_CH5[i], 12, 1);
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

								swd_read_memory(0x08000000 + burn_addr, Check_Data, 1024);
								if (memcmp(Check_Data, rData, 1024) != 0)
								{
									OLED_Clear();
									OLED_ShowString(20, Y1, "Verify Faild!!", 12, 1);
									HAL_Delay(1000);
									OLED_Clear();
									burn_addr = 0;
									readflag = 1;
									return 1;
								}
								burn_addr += 1024;
								progess = (((double)burn_addr / f_size(&fnew)) * 100);
								//OLED_Show_progress_bar(progess / 10, 12, 12, 0, 30, 12, 1);
								OLED_ShowNumber(50, Y0, progess, 3, 12, 1);
								OLED_ShowString(70, Y0, "%", 12, 1);
							}
							else
								return 0;
						}
						time2 = HAL_GetTick();
						if (swd_init_debug())
						{
							Burn_cnt++;
							OLED_ShowNumber(0, Y0, (time2 - time1) / 1000, 2, 12, 1);
							OLED_ShowString(13, Y0, ".", 12, 1);
							OLED_ShowNumber(18, Y0, ((time2 - time1) / 10) % 100, 2, 12, 1);
							OLED_ShowString(30, Y0, "S", 12, 1);
							time3 = (time2 - time1) / 1000 + (((time2 - time1) / 10) % 100)/100;

							OLED_ShowNumber(90, Y0, f_size(&fnew) / time3, 2, 12, 1);
							OLED_ShowString(105, Y0, "Kb/s", 12, 1);

							HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_13);
							swd_set_target_reset(0); //复位运行
							OLED_ShowNumber(50, Y0, 100, 3, 12, 1);
							OLED_ShowString(70, Y0, "%", 12, 1);
							for (uint8_t i = 0; i < 8; i++)
								OLED_Show_CH_String(35 + i * 6, Y2, oled_CH5[i], 12, 1);
							HAL_Delay(1000);
							OLED_Clear();
							burn_addr = 0;
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
		OLED_ShowString(0, Y3, "Connected!!!", 8, 1);
		OLED_ShowNumber(110, Y3, Burn_cnt, 4, 8, 1);
		if (Need_Next == 1 || button_num == 9)
		{
			if (strstr(Name_Buffer[Select_file], "HEX"))
			{
				if (f_open(&fnew, (const TCHAR *)Name_Buffer[Select_file], FA_READ) == FR_OK)
				{
					if (HexFile2BinFile((char *)Name_Buffer[Select_file],"write.bin") != 0)
					{
						OLED_Clear();
						OLED_ShowString(0, Y2, "Error!!", 8, 1);
					}
					else
					{
						OLED_Clear();
						HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_RESET);
						for (uint8_t i = 0; i < 8; i++)
							OLED_Show_CH_String(35 + i * 6, Y2, oled_CH3[i], 12, 1); //开始烧录
						while (!FLASH_SWD((uint8_t *)"write.bin"))					 //打开文件
						{
							if (button_num == 1) //卡住了可以按下退出
							{
								button_num = 0;
								Show.windows = SHOW_MENU;
								Show.mode = MODE_SET_NORMAL;
								break;
							}
							else if (!swd_init_debug()) //芯片断开连接则退出
							{
								OLED_Clear();
								button_num = 0;
								Show.windows = SHOW_OFFLINE;
								Show.mode = MODE_SET_OFFLINE;
								break;
							}
						}
						//f_unlink("0:/write.bin");
						//如果烧录完了还连接着芯片
						if (swd_init_debug())
						{
							Need_Next = 0;
						}
					}
				}
				else
				{
					OLED_Clear();
					OLED_ShowString(0, Y2, "Open HEX failed", 8, 1);
					HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_SET);
				}
			}
			else
			{
				if (f_open(&fnew, (const TCHAR *)Name_Buffer[Select_file], FA_READ) == FR_OK) //如果存在这个文件
				{
					OLED_Clear();
					HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_RESET);
					for (uint8_t i = 0; i < 8; i++)
						OLED_Show_CH_String(35 + i * 6, Y2, oled_CH3[i], 12, 1); //开始烧录
					while (!FLASH_SWD((uint8_t *)Name_Buffer[Select_file]))		 //打开文件
					{
						if (button_num == 1) //卡住了可以按下退出
						{
							button_num = 0;
							Show.windows = SHOW_MENU;
							Show.mode = MODE_SET_NORMAL;
							break;
						}
						else if (!swd_init_debug()) //芯片断开连接则退出
						{
							OLED_Clear();
							button_num = 0;
							Show.windows = SHOW_OFFLINE;
							Show.mode = MODE_SET_OFFLINE;
							break;
						}
					}
					//如果烧录完了还连接着芯片
					if (swd_init_debug())
					{
						Need_Next = 0;
					}
				}
				else
				{
					OLED_ShowString(0, Y2, "Open Bin failed", 8, 1);
					HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_SET);
				}
			}
		}
	}
	else
	{
		Need_Next = 1;
		OLED_ShowNumber(110, Y3, Burn_cnt, 4, 8, 1);
		OLED_ShowString(0, Y3, "Disconnected", 8, 1);
	}
}

MENU_T g_tMenu_BIN;
char *g_Menu_BIN_Text[20];
void Display_BIN(void)
{
	static uint8_t fRefresh = 1;
	static uint8_t s_MenuInit = 0;
	if (s_MenuInit == 0)
	{
		name_cnt = 0;
		memset(g_Menu_BIN_Text, 0, sizeof(g_Menu_BIN_Text));
		if (f_opendir(&DirInfo, (const TCHAR *)"0:") == FR_OK) /* 打开文件夹目录成功，目录信息已经在dir结构体中保存 */
		{
			f_readdir(&DirInfo, &FileInfo);					//先读取一次无用值
			while (f_readdir(&DirInfo, &FileInfo) == FR_OK) /* 读文件信息到文件状态结构体中 */
			{
				if (!FileInfo.fname[0])
				{
					for (uint8_t i = 0; i < name_cnt; i++)
					{
						g_Menu_BIN_Text[i] = Name_Buffer[i];
					}
					g_Menu_BIN_Text[name_cnt] = "&";
					break;
				}
				strcpy(Name_Buffer[name_cnt], FileInfo.fname);
				name_cnt++;
			}
		}
		s_MenuInit = 1;
		g_tMenu_BIN.Left = MENU_LEFT;
		g_tMenu_BIN.Top = MENU_TOP;
		g_tMenu_BIN.Height = MENU_HEIGHT;
		g_tMenu_BIN.Width = MENU_WIDTH;
		g_tMenu_BIN.LineCap = MENU_CAP;
		g_tMenu_BIN.Font = 8;
		g_tMenu_BIN.ViewLine = MENU_HEIGHT / g_tMenu_BIN.Font;
		g_tMenu_BIN.RollBackEn = 1; /* 允许回滚 */
		g_tMenu_BIN.GBK = 0;
		g_tMenu_BIN.ActiveBackColor = 0;					  /* 选中行背景色ID */
		LCD_InitMenu(&g_tMenu_BIN, (char **)g_Menu_BIN_Text); /* 初始化菜单结构 */
	}

	if (fRefresh) /* 重新进入就 刷新整个界面 */
	{
		fRefresh = 0;
		LCD_DispMenu(&g_tMenu_BIN);
		if (g_tMenu_BIN.Cursor == 0)
		{
			;
		}
	}

	/* 有键按下 */
	switch (button_num)
	{
	case 3: /* S键 上 */
		OLED_Clear();
		LCD_MoveUpMenu(&g_tMenu_BIN);
		break;
	case 2: /* S键 上 */
		OLED_Clear();
		fRefresh = 1;
		for (uint8_t i = 0; i < 10; i++)
			OLED_Show_CH_String(29 + i * 6, Y2, oled_CH4[i], 12, 1);
		Select_file = g_tMenu_BIN.Cursor;
		HAL_Delay(500);
		OLED_Clear();
		Show.windows = SHOW_OFFLINE;
		Show.mode = MODE_SET_OFFLINE;
		break;
	case 1: /* S键 上 */
		OLED_Clear();
		LCD_MoveDownMenu(&g_tMenu_BIN);
		break;
	}
	button_num = 0;
}
MENU_T g_tMenu_FLM;
const uint8_t *g_Menu_FLM_Text[] = {
	"1.STM32F0XX",
	"2.STM32F1XX",
	"3.STM32F3XX",
	"4.STM32F4XX",
	"5.STM32F7XX",
	"6.STM32H7XX",
	"&",
};
void Display_FLM(void)
{
	static uint8_t fRefresh = 1;
	static uint8_t s_MenuInit = 0;

	if (s_MenuInit == 0)
	{
		s_MenuInit = 1;
		g_tMenu_FLM.Left = MENU_LEFT;
		g_tMenu_FLM.Top = MENU_TOP;
		g_tMenu_FLM.Height = MENU_HEIGHT;
		g_tMenu_FLM.Width = MENU_WIDTH;
		g_tMenu_FLM.LineCap = MENU_CAP;
		g_tMenu_FLM.Font = 8;
		g_tMenu_FLM.ViewLine = MENU_HEIGHT / g_tMenu_FLM.Font;
		g_tMenu_FLM.RollBackEn = 1; /* 允许回滚 */
		g_tMenu_FLM.GBK = 0;
		g_tMenu_FLM.ActiveBackColor = 0;					  /* 选中行背景色ID */
		LCD_InitMenu(&g_tMenu_FLM, (char **)g_Menu_FLM_Text); /* 初始化菜单结构 */
	}
	if (fRefresh) /* 重新进入就 刷新整个界面 */
	{
		fRefresh = 0;
		LCD_DispMenu(&g_tMenu_FLM);
		if (g_tMenu_FLM.Cursor == 0)
		{
			;
		}
	}
	/* 有键按下 */
	switch (button_num)
	{
	case 3: /* S键 上 */
		LCD_MoveUpMenu(&g_tMenu_FLM);
		break;
	case 2: /* S键 上 */
		OLED_Clear();
		fRefresh = 1;
		for (uint8_t i = 0; i < 10; i++)
			OLED_Show_CH_String(29 + i * 6, Y2, oled_CH4[i], 12, 1);
		Select_algo = g_tMenu_FLM.Cursor;
		HAL_Delay(500);
		OLED_Clear();
		Show.windows = SHOW_OFFLINE;
		Show.mode = MODE_SET_OFFLINE;
		break;
	case 1: /* S键 上 */
		LCD_MoveDownMenu(&g_tMenu_FLM);
		break;
	}
	button_num = 0;
}
//选择脱机烧录模式中的下载算法和文件
void Select_Offline(void)
{
	static uint8_t choose = Y2;
	if (button_num == 1)
	{
		if (choose < Y2)
			choose += 8;
		if (choose >= Y2)
			choose = Y2;
		OLED_ShowString(110, choose - 8, "  ", 8, 1);
	}
	else if (button_num == 3)
	{
		if (choose > Y0)
			choose -= 8;
		if (choose <= Y0)
			choose = Y0;
		OLED_ShowString(110, choose + 8, "  ", 8, 1);
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
		else if (choose == Y2)
		{
			Need_Next = 1;
		}
	}
	button_num = 0;
	OLED_ShowString(110, choose, "<<", 8, 1);
}

#endif
