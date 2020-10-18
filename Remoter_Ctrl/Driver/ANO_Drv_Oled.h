#ifndef __ANO_DRV_OLED_H__
#define	__ANO_DRV_OLED_H__
#include "board.h"

#define XLevelL		0x00
#define XLevelH		0x10
#define Max_Column	128
#define Max_Row		64
#define X_WIDTH 	128
#define Y_WIDTH 	64	
#define OLED_CMD  0	//写命令
#define OLED_DATA 1	//写数据

/***************SPI GPIO定义******************/
#define ANO_OLED_GPIO_SPI			GPIOA
#define OLED_SPI_Pin_SCK			GPIO_Pin_5
#define OLED_SPI_Pin_MOSI			GPIO_Pin_7
#define OLED_RCC_GPIO_SPI			RCC_APB2Periph_GPIOA

#define OLED_RST_Clr() GPIO_ResetBits(GPIOA,GPIO_Pin_6)//RES
#define OLED_RST_Set() GPIO_SetBits(GPIOA,GPIO_Pin_6)

#define OLED_DC_Clr() GPIO_ResetBits(GPIOB,GPIO_Pin_0)//DC
#define OLED_DC_Set() GPIO_SetBits(GPIOB,GPIO_Pin_0)
 		     
#define OLED_CS_Clr()  //GPIO_ResetBits(GPIOC,GPIO_Pin_15)//CS
#define OLED_CS_Set()  //GPIO_SetBits(GPIOC,GPIO_Pin_15)

//OLED控制用函数
void OLED_WR_Byte(u8 dat,u8 cmd);	    
void OLED_Display_On(void);
void OLED_Display_Off(void);	   							   		    
void OLED_Init(void);
void OLED_Clear(void);
void OLED_DrawPoint(u8 x,u8 y,u8 t);
void OLED_Fill(u8 x1,u8 y1,u8 x2,u8 y2,u8 dot);
void OLED_ShowChar(u8 x,u8 y,u8 chr, u8 size);
void OLED_ShowNum(u8 x,u8 y,u32 num,u8 len,u8 size);
void OLED_ShowAngel(u8 x,u8 y,int16_t num,u8 size);
void OLED_ShowString(u8 x,u8 y,const char *chr, u8 size);	 
void OLED_Set_Pos(unsigned char x, unsigned char y);
void OLED_ShowCHinese(u8 x,u8 y,char (*text)[32], u8 no, u8 mode);
void OLED_DrawBMP(unsigned char x0, unsigned char y0,unsigned char x1, unsigned char y1,unsigned char BMP[]);

void OLED_ShowC_NMKC(u8 x,u8 y, u8 mode);
void OLED_ShowC_FXQSJ(u8 x,u8 y, u8 mode);
void OLED_ShowC_YGJZ(u8 x,u8 y, u8 mode);
void OLED_ShowC_YGWT(u8 x,u8 y, u8 mode);
void OLED_ShowC_BZ(u8 x,u8 y, u8 mode);
void OLED_ShowC_SXZY(u8 x,u8 y, u8 mode);
void OLED_ShowC_YDLGYG(u8 x,u8 y, u8 mode);
void OLED_ShowC_ZBYGLDZD(u8 x,u8 y, u8 mode);
	
#endif
