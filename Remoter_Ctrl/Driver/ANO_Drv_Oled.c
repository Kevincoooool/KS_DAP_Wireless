#include "ANO_Drv_Oled.h"
#include "ANO_Drv_Oled_font.h"
//OLED的显存
//存放格式如下.
//[0]0 1 2 3 ... 127	
//[1]0 1 2 3 ... 127	
//[2]0 1 2 3 ... 127	
//[3]0 1 2 3 ... 127	
//[4]0 1 2 3 ... 127	
//[5]0 1 2 3 ... 127	
//[6]0 1 2 3 ... 127	
//[7]0 1 2 3 ... 127 	

void ANO_OLED_SPI_Init(void)
{
	SPI_InitTypeDef SPI_InitStructure; 
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd(OLED_RCC_GPIO_SPI, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1, ENABLE); 

	/*配置 SPI_NRF_SPI的 SCK,MISO,MOSI引脚 */ 
	GPIO_InitStructure.GPIO_Pin = OLED_SPI_Pin_SCK| OLED_SPI_Pin_MOSI; 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; //复用功能 
	GPIO_Init(ANO_OLED_GPIO_SPI, &GPIO_InitStructure);
	
	SPI_InitStructure.SPI_Direction = SPI_Direction_1Line_Tx; 
	SPI_InitStructure.SPI_Mode = SPI_Mode_Master; //主模式 
	SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b; //数据大小8位 
	SPI_InitStructure.SPI_CPOL = SPI_CPOL_High; 
	SPI_InitStructure.SPI_CPHA = SPI_CPHA_2Edge; 
	SPI_InitStructure.SPI_NSS = SPI_NSS_Soft; //NSS信号由软件产生 
	SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_2; 
	SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB; //高位在前 
	SPI_InitStructure.SPI_CRCPolynomial = 0; 
	SPI_Init(SPI1, &SPI_InitStructure); 

	SPI_Cmd(SPI1, ENABLE);
	
}

void ANO_OLED_SPI_RW(u8 dat) 
{ 
	/* 当 SPI发送缓冲器非空时等待 */ 
	while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET); 
	/* 通过 SPI2发送一字节数据 */ 
	SPI_I2S_SendData(SPI1, dat); 
}

void OLED_WR_Byte(u8 dat,u8 cmd)
{		  
	if(cmd)
	  OLED_DC_Set();
	else 
	  OLED_DC_Clr();		  
	OLED_CS_Clr();		 		 
	ANO_OLED_SPI_RW(dat);	
	OLED_CS_Set();
	OLED_DC_Set();   	  
} 
void OLED_Set_Pos(unsigned char x, unsigned char y) 
{ 
	OLED_WR_Byte(0xb0+y,OLED_CMD);
	OLED_WR_Byte(((x&0xf0)>>4)|0x10,OLED_CMD);
	OLED_WR_Byte((x&0x0f)|0x01,OLED_CMD); 
}   	
//开启OLED显示    
void OLED_Display_On(void)
{
	OLED_WR_Byte(0X8D,OLED_CMD);  //SET DCDC命令
	OLED_WR_Byte(0X14,OLED_CMD);  //DCDC ON
	OLED_WR_Byte(0XAF,OLED_CMD);  //DISPLAY ON
}
//关闭OLED显示     
void OLED_Display_Off(void)
{
	OLED_WR_Byte(0X8D,OLED_CMD);  //SET DCDC命令
	OLED_WR_Byte(0X10,OLED_CMD);  //DCDC OFF
	OLED_WR_Byte(0XAE,OLED_CMD);  //DISPLAY OFF
}	
//清屏函数,清完屏,整个屏幕是黑色的!和没点亮一样!!!	  
void OLED_Clear(void)  
{  
	u8 i,n;		    
	for(i=0;i<8;i++)  
	{  
		OLED_WR_Byte (0xb0+i,OLED_CMD);    //设置页地址（0~7）
		OLED_WR_Byte (0x00,OLED_CMD);      //设置显示位置—列低地址
		OLED_WR_Byte (0x10,OLED_CMD);      //设置显示位置—列高地址   
		for(n=0;n<128;n++)OLED_WR_Byte(0,OLED_DATA); 
	} //更新显示
}
//在指定位置显示一个字符,包括部分字符
//x:0~127
//y:0~63
//mode:0,反白显示;1,正常显示				 
//size:选择字体 8/6 
void OLED_ShowChar(u8 x,u8 y,u8 chr,u8 size)
{      	
	unsigned char c=0,i=0;	
		c=chr-' ';//得到偏移后的值			
		if(x>Max_Column-1){x=0;y=y+2;}
		if(size ==8)
		{
			OLED_Set_Pos(x,y);	
			for(i=0;i<8;i++)
			OLED_WR_Byte(F8X16[c*16+i],OLED_DATA);
			OLED_Set_Pos(x,y+1);
			for(i=0;i<8;i++)
			OLED_WR_Byte(F8X16[c*16+i+8],OLED_DATA);
		}
		else 
		{	
				OLED_Set_Pos(x,y);
				for(i=0;i<6;i++)
				OLED_WR_Byte(F6x8[c][i],OLED_DATA);
		}
}
//m^n函数
u32 oled_pow(u8 m,u8 n)
{
	u32 result=1;	 
	while(n--)result*=m;    
	return result;
}				  
//显示2个数字
//x,y :起点坐标	 
//len :数字的位数
//size:字体大小
//mode:模式	0,填充模式;1,叠加模式
//num:数值(0~4294967295);	 		  
void OLED_ShowNum(u8 x,u8 y,u32 num,u8 len,u8 size)
{         	
	u8 t,temp;
	u8 enshow=0;						   
	for(t=0;t<len;t++)
	{
		temp=(num/oled_pow(10,len-t-1))%10;
		if(enshow==0&&t<(len-1))
		{
			if(temp==0)
			{
				OLED_ShowChar(x+size*t,y,' ',size);
				continue;
			}
			else 
				enshow=1; 
		}
	 	OLED_ShowChar(x+size*t,y,temp+'0',size); 
	}
} 
void OLED_ShowAngel(u8 x,u8 y,int16_t num,u8 size)
{         	
	u8 temp;
	u8 enshow=0;	
	
	num = num / 100;
	
	if(num>0)
	{
		temp=(num/100)%10;
		if(temp)
		{
			OLED_ShowChar(x+size*1,y,temp+'0',size); 
			enshow = 1;
		}
		else
			OLED_ShowChar(x+size*1,y,' ',size);
		
		temp=(num/10)%10;
		if(temp || enshow)
			OLED_ShowChar(x+size*2,y,temp+'0',size); 
		else
			OLED_ShowChar(x+size*2,y,' ',size);
		
		temp=num%10;
			OLED_ShowChar(x+size*3,y,temp+'0',size); 
		
	}
	else
	{
		num = 0 - num;
		OLED_ShowChar(x,y,'-',size);
		
		temp=(num/100)%10;
		if(temp)
		{
			OLED_ShowChar(x+size*1,y,temp+'0',size); 
			enshow = 1;
		}
		else
			OLED_ShowChar(x+size*1,y,' ',size);
		
		temp=(num/10)%10;
		if(temp || enshow)
			OLED_ShowChar(x+size*2,y,temp+'0',size); 
		else
			OLED_ShowChar(x+size*2,y,' ',size);
		
		temp=num%10;
			OLED_ShowChar(x+size*3,y,temp+'0',size); 
	}
} 
//显示一个字符号串
void OLED_ShowString(u8 x,u8 y,const char *chr, u8 size)
{
	unsigned char j=0;
	while (chr[j]!='\0')
	{		
		OLED_ShowChar(x,y,chr[j],size);
		x+=size;
		if(x>128) return;
			//{x=0;y+=2;}
			j++;
	}
}
//显示汉字
void OLED_ShowCHinese(u8 x,u8 y,char (*text)[32], u8 no, u8 mode)
{      			    
	u8 t=0;
	y = y * 2;
	OLED_Set_Pos(x,y);	
	for(t=0;t<16;t++)
	{
		if(mode)
			OLED_WR_Byte(~ *(*(text+2*no)+t),OLED_DATA);
		else
			OLED_WR_Byte(*(*(text+2*no)+t),OLED_DATA);
	 }	
	OLED_Set_Pos(x,y+1);	
	for(t=0;t<16;t++)
	{	
		if(mode)
			OLED_WR_Byte(~ *(*(text+2*no+1)+t),OLED_DATA);
		else
			OLED_WR_Byte(*(*(text+2*no+1)+t),OLED_DATA);
	}					
}
/***********功能描述：显示显示BMP图片128×64起始点坐标(x,y),x的范围0～127，y为页的范围0～7*****************/
void OLED_DrawBMP(unsigned char x0, unsigned char y0,unsigned char x1, unsigned char y1,unsigned char BMP[])
{ 	
 unsigned int j=0;
 unsigned char x,y;
  
  if(y1%8==0) y=y1/8;      
  else y=y1/8+1;
	for(y=y0;y<y1;y++)
	{
		OLED_Set_Pos(x0,y);
    for(x=x0;x<x1;x++)
	    {      
	    	OLED_WR_Byte(BMP[j++],OLED_DATA);	    	
	    }
	}
} 
static void delay_ms(u32 time)
{
	u32 m;
	while(time)
	{
		time--;
		m = 10000;
		while(m)
			m--;
	}
}
//初始化SSD1306					    
void OLED_Init(void)
{ 	
 	GPIO_InitTypeDef  GPIO_InitStructure;
 	
	ANO_OLED_SPI_Init();
	
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);	 //使能A端口时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6; 
 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;//速度50MHz
 	GPIO_Init(GPIOA, &GPIO_InitStructure);	  //初始化GPIOD3,6
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0; 
 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;//速度50MHz
 	GPIO_Init(GPIOB, &GPIO_InitStructure);	  //初始化GPIOD3,6

  OLED_RST_Set();
	delay_ms(100);
	OLED_RST_Clr();
	delay_ms(200);
	OLED_RST_Set(); 
					  
	OLED_WR_Byte(0xAE,OLED_CMD);//--turn off oled panel
	OLED_WR_Byte(0x00,OLED_CMD);//---set low column address
	OLED_WR_Byte(0x10,OLED_CMD);//---set high column address
	OLED_WR_Byte(0x40,OLED_CMD);//--set start line address  Set Mapping RAM Display Start Line (0x00~0x3F)
	OLED_WR_Byte(0x81,OLED_CMD);//--set contrast control register
	OLED_WR_Byte(0xCF,OLED_CMD); // Set SEG Output Current Brightness
	OLED_WR_Byte(0xA1,OLED_CMD);//--Set SEG/Column Mapping     0xa0左右反置 0xa1正常
	OLED_WR_Byte(0xC8,OLED_CMD);//Set COM/Row Scan Direction   0xc0上下反置 0xc8正常
	OLED_WR_Byte(0xA6,OLED_CMD);//--set normal display
	OLED_WR_Byte(0xA8,OLED_CMD);//--set multiplex ratio(1 to 64)
	OLED_WR_Byte(0x3f,OLED_CMD);//--1/64 duty
	OLED_WR_Byte(0xD3,OLED_CMD);//-set display offset	Shift Mapping RAM Counter (0x00~0x3F)
	OLED_WR_Byte(0x00,OLED_CMD);//-not offset
	OLED_WR_Byte(0xd5,OLED_CMD);//--set display clock divide ratio/oscillator frequency
	OLED_WR_Byte(0x80,OLED_CMD);//--set divide ratio, Set Clock as 100 Frames/Sec
	OLED_WR_Byte(0xD9,OLED_CMD);//--set pre-charge period
	OLED_WR_Byte(0xF1,OLED_CMD);//Set Pre-Charge as 15 Clocks & Discharge as 1 Clock
	OLED_WR_Byte(0xDA,OLED_CMD);//--set com pins hardware configuration
	OLED_WR_Byte(0x12,OLED_CMD);
	OLED_WR_Byte(0xDB,OLED_CMD);//--set vcomh
	OLED_WR_Byte(0x40,OLED_CMD);//Set VCOM Deselect Level
	OLED_WR_Byte(0x20,OLED_CMD);//-Set Page Addressing Mode (0x00/0x01/0x02)
	OLED_WR_Byte(0x02,OLED_CMD);//
	OLED_WR_Byte(0x8D,OLED_CMD);//--set Charge Pump enable/disable
	OLED_WR_Byte(0x14,OLED_CMD);//--set(0x10) disable
	OLED_WR_Byte(0xA4,OLED_CMD);// Disable Entire Display On (0xa4/0xa5)
	OLED_WR_Byte(0xA6,OLED_CMD);// Disable Inverse Display On (0xa6/a7) 
	OLED_WR_Byte(0xAF,OLED_CMD);//--turn on oled panel
	
	OLED_WR_Byte(0xAF,OLED_CMD); /*display ON*/ 
	OLED_Clear();
	OLED_Set_Pos(0,0); 	
} 

void OLED_ShowC_NMKC(u8 x,u8 y, u8 mode)
{
	if(y>3)
		return;
	OLED_ShowCHinese(x,y,&F_NMKC[0],0,mode);
	OLED_ShowCHinese(x+16,y,&F_NMKC[0],1,mode);
	OLED_ShowCHinese(x+32,y,&F_NMKC[0],2,mode);
	OLED_ShowCHinese(x+48,y,&F_NMKC[0],3,mode);
}
void OLED_ShowC_FXQSJ(u8 x,u8 y, u8 mode)
{
	if(y>3)
		return;
	OLED_ShowCHinese(x,y,&F_FXQSJ[0],0,mode);
	OLED_ShowCHinese(x+16,y,&F_FXQSJ[0],1,mode);
	OLED_ShowCHinese(x+32,y,&F_FXQSJ[0],2,mode);
	OLED_ShowCHinese(x+48,y,&F_FXQSJ[0],3,mode);
	OLED_ShowCHinese(x+64,y,&F_FXQSJ[0],4,mode);
}
void OLED_ShowC_YGJZ(u8 x,u8 y, u8 mode)
{
	if(y>3)
		return;
	OLED_ShowCHinese(x,y,&F_YGJZ[0],0,mode);
	OLED_ShowCHinese(x+16,y,&F_YGJZ[0],1,mode);
	OLED_ShowCHinese(x+32,y,&F_YGJZ[0],2,mode);
	OLED_ShowCHinese(x+48,y,&F_YGJZ[0],3,mode);
}
void OLED_ShowC_YGWT(u8 x,u8 y, u8 mode)
{
	if(y>3)
		return;
	OLED_ShowCHinese(x,y,&F_YGWT[0],0,mode);
	OLED_ShowCHinese(x+16,y,&F_YGWT[0],1,mode);
	OLED_ShowCHinese(x+32,y,&F_YGWT[0],2,mode);
	OLED_ShowCHinese(x+48,y,&F_YGWT[0],3,mode);
}
void OLED_ShowC_SXZY(u8 x,u8 y, u8 mode)
{
	if(y>3)
		return;
	OLED_ShowCHinese(x,y,&F_SXZY[0],0,mode);
	OLED_ShowCHinese(x+16,y,&F_SXZY[0],1,mode);
	OLED_ShowCHinese(x+32,y,&F_SXZY[0],2,mode);
	OLED_ShowCHinese(x+48,y,&F_SXZY[0],3,mode);
}
void OLED_ShowC_YDLGYG(u8 x,u8 y, u8 mode)
{
	if(y>3)
		return;
	OLED_ShowCHinese(x,y,&F_YDLGYG[0],0,mode);
	OLED_ShowCHinese(x+16,y,&F_YDLGYG[0],1,mode);
	OLED_ShowCHinese(x+32,y,&F_YDLGYG[0],2,mode);
	OLED_ShowCHinese(x+48,y,&F_YDLGYG[0],3,mode);
	OLED_ShowCHinese(x+64,y,&F_YDLGYG[0],4,mode);
	OLED_ShowCHinese(x+80,y,&F_YDLGYG[0],5,mode);
}
void OLED_ShowC_ZBYGLDZD(u8 x,u8 y, u8 mode)
{
	if(y>3)
		return;
	OLED_ShowCHinese(x,y,&F_ZBYGLDZD[0],0,mode);
	OLED_ShowCHinese(x+16,y,&F_ZBYGLDZD[0],1,mode);
	OLED_ShowCHinese(x+32,y,&F_ZBYGLDZD[0],2,mode);
	OLED_ShowCHinese(x+48,y,&F_ZBYGLDZD[0],3,mode);
	OLED_ShowCHinese(x+64,y,&F_ZBYGLDZD[0],4,mode);
	OLED_ShowCHinese(x+80,y,&F_ZBYGLDZD[0],5,mode);
	OLED_ShowCHinese(x+96,y,&F_ZBYGLDZD[0],6,mode);
	OLED_ShowCHinese(x+112,y,&F_ZBYGLDZD[0],7,mode);
}
void OLED_ShowC_BZ(u8 x,u8 y, u8 mode)
{
	if(y>3)
		return;
	OLED_ShowCHinese(x,y,&F_BZ[0],0,mode);
	OLED_ShowCHinese(x+16,y,&F_BZ[0],1,mode);
}

