/*
 * @Descripttion : 
 * @version      : 
 * @Author       : Kevincoooool
 * @Date         : 2020-10-15 14:43:02
 * @LastEditors  : Kevincoooool
 * @LastEditTime : 2020-10-15 19:12:43
 * @FilePath     : \Simple_TeenyUSB_TX\BSP\oled.h
 */
// #ifndef __OLED_H
// #define __OLED_H			  	 
// #include "stm32f1xx.h"
// #include "stdlib.h"	    	
// //OLED模式设置
// //0:4线串行模式
// //1:并行8080模式
// #define OLED_MODE 0
// #define SIZE 8
// #define XLevelL		0x00
// #define XLevelH		0x10
// #define Max_Column	128
// #define Max_Row		64
// #define	Brightness	0xFF 
// #define X_WIDTH 	128
// #define Y_WIDTH 	64	    

// //-----------------测试LED端口定义---------------- 
// #define LED_ON GPIO_ResetBits(GPIOC,GPIO_Pin_13)//DC
// #define LED_OFF GPIO_SetBits(GPIOC,GPIO_Pin_13)

//-----------------OLED端口定义----------------  					   
/*
 * @Descripttion : 
 * @version      : 
 * @Author       : Kevincoooool
 * @Date         : 2020-10-15 14:43:02
 * @LastEditors  : Kevincoooool
 * @LastEditTime : 2020-10-15 18:12:10
 * @FilePath     : \Simple_TeenyUSB_TX\BSP\oled.h
 */
#ifndef __OLED_H
#define __OLED_H			  	 
#include "stm32f1xx.h"
#include "stdlib.h"
#include "oledfont.h"	  	    	
//OLED模式设置
//0:4线串行模式
//1:并行8080模式
#define OLED_MODE 0
#define SIZE 8
#define XLevelL		0x00
#define XLevelH		0x10
#define Max_Column	128
#define Max_Row		64
#define	Brightness	0xFF 
#define X_WIDTH 	128
#define Y_WIDTH 	64	    

//-----------------测试LED端口定义---------------- 
#define LED_ON GPIO_ResetBits(GPIOC,GPIO_Pin_13)//DC
#define LED_OFF GPIO_SetBits(GPIOC,GPIO_Pin_13)

//-----------------OLED端口定义----------------  					   

#define OLED_CS_GPIO		GPIOB	
#define OLED_CS_Pin		    GPIO_PIN_0

#define OLED_DC_GPIO		GPIOB	
#define OLED_DC_Pin		    GPIO_PIN_1

#define OLED_RST_GPIO		GPIOB	
#define OLED_RST_Pin		GPIO_PIN_3

#define OLED_SDA_GPIO		GPIOB	
#define OLED_SDA_Pin		GPIO_PIN_4

#define OLED_SCL_GPIO		GPIOB	
#define OLED_SCL_Pin		GPIO_PIN_5

#define OLED_CS_H   		OLED_CS_GPIO ->BSRR  = OLED_CS_Pin  //高电平
#define OLED_CS_L   		OLED_CS_GPIO ->BRR   = OLED_CS_Pin  //低电平

#define OLED_DC_H   		OLED_DC_GPIO ->BSRR  = OLED_DC_Pin  //高电平
#define OLED_DC_L   		OLED_DC_GPIO ->BRR   = OLED_DC_Pin  //低电平

#define OLED_RST_H   		OLED_RST_GPIO ->BSRR = OLED_RST_Pin  //高电平
#define OLED_RST_L   		OLED_RST_GPIO ->BRR  = OLED_RST_Pin  //低电平

#define OLED_SDA_H   		OLED_SDA_GPIO ->BSRR = OLED_SDA_Pin  //高电平
#define OLED_SDA_L   		OLED_SDA_GPIO ->BRR  = OLED_SDA_Pin  //低电平

#define OLED_SCL_H   		OLED_SCL_GPIO ->BSRR = OLED_SCL_Pin  //高电平
#define OLED_SCL_L   		OLED_SCL_GPIO ->BRR  = OLED_SCL_Pin  //低电平
//-----------------OLED端口定义---------------- 
#define OLED_CS_Clr()   OLED_CS_L    //DC
#define OLED_CS_Set()   OLED_CS_H    //DC

#define OLED_DC_Clr()   OLED_DC_L    //DC
#define OLED_DC_Set()   OLED_DC_H    //DC

#define OLED_RST_Clr()  OLED_RST_L   //RST
#define OLED_RST_Set()  OLED_RST_H   //RST

#define OLED_SDIN_Clr() OLED_SDA_L   //SDA
#define OLED_SDIN_Set() OLED_SDA_H   //SDA

#define OLED_SCLK_Clr() OLED_SCL_L   //SCL
#define OLED_SCLK_Set() OLED_SCL_H   //SCL

#define OLED_CMD  0	//写命令
#define OLED_DATA 1	//写数据
//OLED控制用函数
//OLED控制用函数
void OLED_WR_Byte(uint8_t dat,uint8_t cmd);	    
void OLED_Display_On(void);
void OLED_Display_Off(void);
void OLED_Refresh_Gram(void);		   				   		    
void OLED_Init(void);
void OLED_Clear(void);
void OLED_DrawPoint(uint8_t x,uint8_t y,uint8_t t);
void OLED_ShowChar(uint8_t x,uint8_t y,uint8_t chr,uint8_t size,uint8_t mode);
void OLED_ShowNumber(uint8_t x,uint8_t y,uint32_t num,uint8_t len,uint8_t size);
void OLED_ShowString(uint8_t x,uint8_t y,const uint8_t *p,uint8_t size,uint8_t mode);
void OLED_ShowCH(uint8_t x,uint8_t y,uint8_t chr,uint8_t size,uint8_t mode);
void OLED_Show_CH(uint8_t x,uint8_t y,uint8_t chr,uint8_t size,uint8_t mode);
void OLED_Show_CH_String(uint8_t x,uint8_t y,const uint8_t *p,uint8_t size,uint8_t mode);
void OLED_Show_progress_bar(uint8_t temp,uint8_t chr_star,uint8_t chr_default,uint8_t x,uint8_t y,uint8_t size,uint8_t mode);
#endif  
	 





// #define OLED_SCLK_Clr() HAL_GPIO_WritePin(GPIOB,GPIO_PIN_5,GPIO_PIN_RESET)//CLK
// #define OLED_SCLK_Set() HAL_GPIO_WritePin(GPIOB,GPIO_PIN_5,GPIO_PIN_SET)

// #define OLED_SDIN_Clr() HAL_GPIO_WritePin(GPIOB,GPIO_PIN_4,GPIO_PIN_RESET)//DIN
// #define OLED_SDIN_Set() HAL_GPIO_WritePin(GPIOB,GPIO_PIN_4,GPIO_PIN_SET)

// #define OLED_RST_Clr() HAL_GPIO_WritePin(GPIOB,GPIO_PIN_3,GPIO_PIN_RESET)//RES
// #define OLED_RST_Set() HAL_GPIO_WritePin(GPIOB,GPIO_PIN_3,GPIO_PIN_SET)

// #define OLED_RS_Clr() HAL_GPIO_WritePin(GPIOB,GPIO_PIN_1,GPIO_PIN_RESET)//DC
// #define OLED_RS_Set() HAL_GPIO_WritePin(GPIOB,GPIO_PIN_1,GPIO_PIN_SET)
 		     
// #define OLED_CS_Clr()  HAL_GPIO_WritePin(GPIOB,GPIO_PIN_0,GPIO_PIN_RESET)//CS
// #define OLED_CS_Set()  HAL_GPIO_WritePin(GPIOB,GPIO_PIN_0,GPIO_PIN_SET)

// #define OLED_CMD  0	//写命令
// #define OLED_DATA 1	//写数据


// //OLED控制用函数
// void OLED_WR_Byte(uint8_t dat,uint8_t cmd);	    
// void OLED_Display_On(void);
// void OLED_Display_Off(void);
// void OLED_Refresh_Gram(void);		   				   		    
// void OLED_Init(void);
// void OLED_Clear(void);
// void OLED_DrawPoint(uint8_t x,uint8_t y,uint8_t t);
// void OLED_ShowChar(uint8_t x,uint8_t y,uint8_t chr,uint8_t size,uint8_t mode);
// void OLED_ShowNumber(uint8_t x,uint8_t y,uint32_t num,uint8_t len,uint8_t size);
// void OLED_ShowString(uint8_t x,uint8_t y,const uint8_t *p,uint8_t size,uint8_t mode);
// void OLED_ShowCH(uint8_t x,uint8_t y,uint8_t chr,uint8_t size,uint8_t mode);
// void OLED_Show_CH(uint8_t x,uint8_t y,uint8_t chr,uint8_t size,uint8_t mode);
// void OLED_Show_CH_String(uint8_t x,uint8_t y,const uint8_t *p,uint8_t size,uint8_t mode);
// #endif  
	 



