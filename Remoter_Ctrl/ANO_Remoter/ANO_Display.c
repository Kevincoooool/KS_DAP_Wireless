#include "ANO_Display.h"
#include "ANO_Param.h"

u8 Menu_State = 0;	//=0,显示遥控状态信息，=1，显示菜单,=2，显示摇杆校准

void show_state(void)
{
	static u8 refresh_line = 0;
	
	refresh_line++;
	if(refresh_line==4)
	refresh_line = 0;
	
	switch(refresh_line)//显示遥控状态界面
	{
		case 0:
			OLED_ShowC_NMKC(0,0,0);
			OLED_ShowString(75,0,"ARMED",6);
			if(ANO_Stick_Mode)
				OLED_ShowString(75,1,"M:  Ack",6);
			else
				OLED_ShowString(75,1,"M:Stick",6);
			break;
		case 1:
			OLED_ShowString(0,2,"ROL:       PIT:    ",6);
			OLED_ShowNum(29,2,ANO_STICK_ROL,4,6);//显示ASCII字符的码值
			OLED_ShowNum(95,2,ANO_STICK_PIT,4,6);//显示ASCII字符的码值
			OLED_ShowString(0,3,"THR:       YAW:    ",6); 
			OLED_ShowNum(29,3,ANO_STICK_THR,4,6);//显示ASCII字符的码值	
			OLED_ShowNum(95,3,ANO_STICK_YAW,4,6);//显示ASCII字符的码值
			break;
		case 2:
			OLED_ShowC_FXQSJ(0,2,0);
			break;
		case 3:
			OLED_ShowString(0,6,"ROL:       PIT:    ",6); 
			OLED_ShowAngel(29,6,PLANE_ROL,6);//显示ASCII字符的码值
			OLED_ShowAngel(95,6,PLANE_PIT,6);//显示ASCII字符的码值
			OLED_ShowString(0,7,"YAW:       ALT:    ",6); 
			OLED_ShowAngel(29,7,PLANE_YAW,6);//显示ASCII字符的码值	
			OLED_ShowNum(95,7,0000,4,6);//显示ASCII字符的码值
			break;
	}
}

void show_stick_init(void)
{
	static u8 refresh_line = 0;
	static u8 init_state = 0;
	
	refresh_line++;
	if(refresh_line==4)
	refresh_line = 0;
	
	if(ANO_KEY_VALUE==1)
	{
		init_state++;
		OLED_Clear();
	}
	ANO_KEY_VALUE = 0;
	
	if(init_state==2)//退出校准
	{
		Menu_State = 0;
		init_state = 0;
		ANO_Stick_Check = 0;
		ANO_Param_SAVE();
		return;
	}
	
	if(init_state==0)
	{
		ANO_Stick_Check = 1;
		switch(refresh_line)//显示遥控状态界面
		{
			case 0:
				OLED_ShowC_YGJZ(0,0,0);
				OLED_ShowC_BZ(79,0,0);
				OLED_ShowNum(111,0,1,1,8);//显示ASCII字符的码值
				break;
			case 1:
				OLED_ShowString(0,2,"ROL:       PIT:    ",6);
				OLED_ShowNum(29,2,ANO_STICK_ROL,4,6);//显示ASCII字符的码值
				OLED_ShowNum(95,2,ANO_STICK_PIT,4,6);//显示ASCII字符的码值
				OLED_ShowString(0,3,"THR:       YAW:    ",6); 
				OLED_ShowNum(29,3,ANO_STICK_THR,4,6);//显示ASCII字符的码值	
				OLED_ShowNum(95,3,ANO_STICK_YAW,4,6);//显示ASCII字符的码值
				break;
			case 2:
				OLED_ShowC_SXZY(0,2,0);
				break;
			case 3:
				OLED_ShowC_YDLGYG(0,3,0);
				break;
		}
	}
	else if(init_state==1)
		{
			ANO_Stick_Check = 2;
			switch(refresh_line)//显示遥控状态界面
			{
				case 0:
					OLED_ShowC_YGJZ(0,0,0);
					OLED_ShowC_BZ(79,0,0);
					OLED_ShowNum(111,0,2,1,8);//显示ASCII字符的码值
					break;
				case 1:
					OLED_ShowString(0,2,"ROL:       PIT:    ",6);
					OLED_ShowNum(29,2,ANO_STICK_ROL,4,6);//显示ASCII字符的码值
					OLED_ShowNum(95,2,ANO_STICK_PIT,4,6);//显示ASCII字符的码值
					OLED_ShowString(0,3,"THR:       YAW:    ",6); 
					OLED_ShowNum(29,3,ANO_STICK_THR,4,6);//显示ASCII字符的码值	
					OLED_ShowNum(95,3,ANO_STICK_YAW,4,6);//显示ASCII字符的码值
					break;
				case 2:
					OLED_ShowC_ZBYGLDZD(0,2,0);
					break;
				case 3:
					OLED_ShowString(0,6,"PRESS BUTTON1",8);
					break;
			}
		}
}
void show_stick_init2(void)
{
	static u8 refresh_line = 0;
	
	refresh_line++;
	if(refresh_line==4)
	refresh_line = 0;
	
	if(ANO_KEY_VALUE==1)
	{
		OLED_Clear();
		Menu_State = 0;
	}
	ANO_KEY_VALUE = 0;
	
	switch(refresh_line)
	{
		case 0:
			OLED_ShowC_YGWT(0,0,0);
			break;
		case 1:
			break;
		case 2:
			break;
		case 3:
			break;
		default:
			break;
	}
}
void ANO_Display_30ms(void)
{
	if(Menu_State == 0)						//显示正常界面
	{
		if(ANO_KEY_VALUE==11)				//长按BUT
		{
			Menu_State = 2;						//显示摇杆校准界面
			OLED_Clear();
			ANO_KEY_VALUE = 0;
		}
		else if(ANO_KEY_VALUE==1)		//短按BUT
		{
			Menu_State = 1;					//进入菜单界面
			OLED_Clear();
			ANO_KEY_VALUE = 0;
		}
		else if(ANO_KEY_VALUE==12)	//长按右摇杆
		{
			ANO_KEY_VALUE = 0;
			ANO_Stick_Mode = !ANO_Stick_Mode;//切换控制模式
		}
		else if(ANO_KEY_VALUE==2)		//短按右摇杆
		{
			ANO_KEY_VALUE = 0;
			ANO_Stick_Mode = !ANO_Stick_Mode;//切换控制模式
		}
		else
			show_state();
	}
	else if(Menu_State == 1)//显示菜单界面
	{
		show_stick_init2();
	}
	else if(Menu_State == 2)//显示摇杆校准界面
	{
		show_stick_init();
	}
}
