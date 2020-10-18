
#ifndef __OLED_H
#define __OLED_H			  	 
#include "sysconfig.h"

#define OLED_DC_GPIO		GPIOB	
#define OLED_DC_Pin		GPIO_Pin_1

#define OLED_RST_GPIO		GPIOB	
#define OLED_RST_Pin		GPIO_Pin_3

#define OLED_SDA_GPIO		GPIOB	
#define OLED_SDA_Pin		GPIO_Pin_4

#define OLED_SCL_GPIO		GPIOB	
#define OLED_SCL_Pin		GPIO_Pin_5

#define OLED_DC_H   		OLED_DC_GPIO ->BSRR  = OLED_DC_Pin  //高电平
#define OLED_DC_L   		OLED_DC_GPIO ->BRR   = OLED_DC_Pin  //低电平

#define OLED_RST_H   		OLED_RST_GPIO ->BSRR = OLED_RST_Pin  //高电平
#define OLED_RST_L   		OLED_RST_GPIO ->BRR  = OLED_RST_Pin  //低电平

#define OLED_SDA_H   		OLED_SDA_GPIO ->BSRR = OLED_SDA_Pin  //高电平
#define OLED_SDA_L   		OLED_SDA_GPIO ->BRR  = OLED_SDA_Pin  //低电平

#define OLED_SCL_H   		OLED_SCL_GPIO ->BSRR = OLED_SCL_Pin  //高电平
#define OLED_SCL_L   		OLED_SCL_GPIO ->BRR  = OLED_SCL_Pin  //低电平
//-----------------OLED端口定义---------------- 
#define OLED_RS_Clr()   OLED_DC_L    //DC
#define OLED_RS_Set()   OLED_DC_H    //DC

#define OLED_RST_Clr()  OLED_RST_L   //RST
#define OLED_RST_Set()  OLED_RST_H   //RST

#define OLED_SDIN_Clr() OLED_SDA_L   //SDA
#define OLED_SDIN_Set() OLED_SDA_H   //SDA

#define OLED_SCLK_Clr() OLED_SCL_L   //SCL
#define OLED_SCLK_Set() OLED_SCL_H   //SCL

#define OLED_CMD  0	//写命令
#define OLED_DATA 1	//写数据
//OLED控制用函数
void OLED_WR_Byte(u8 dat,u8 cmd);	    
void OLED_Display_On(void);
void OLED_Display_Off(void);
void OLED_Refresh_Gram(void);		   				   		    
void OLED_Init(void);
void OLED_Clear(void);
void OLED_DrawPoint(u8 x,u8 y,u8 t);
void OLED_ShowChar(u8 x,u8 y,u8 chr,u8 size,u8 mode);
void OLED_ShowNumber(u8 x,u8 y,u32 num,u8 len,u8 size);
void OLED_ShowString(u8 x,u8 y,const u8 *p,u8 size,u8 mode);
void OLED_ShowCH(u8 x,u8 y,u8 chr,u8 size,u8 mode);
void OLED_Show_CH(u8 x,u8 y,u8 chr,u8 size,u8 mode);
void OLED_Show_CH_String(u8 x,u8 y,const u8 *p,u8 size,u8 mode);
#endif  
	 
