#include "ANO_Drv_I2C.h"

//模拟IIC初始化
void ANO_I2C_Init(void)
{
  GPIO_InitTypeDef  GPIO_InitStructure; 
  RCC_APB2PeriphClockCmd(ANO_RCC_I2C , ENABLE );
  GPIO_InitStructure.GPIO_Pin =  I2C_Pin_SCL;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD;  
  GPIO_Init(ANO_GPIO_I2C, &GPIO_InitStructure);

  GPIO_InitStructure.GPIO_Pin =  I2C_Pin_SDA;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD;
  GPIO_Init(ANO_GPIO_I2C, &GPIO_InitStructure);		
}


void ANO_I2C_delay(void)
{
   /*u8 i=0; 
   while(i) 
   { 
     i--; 
   } 
		*/ 	
}

int ANO_I2C_Start(void)
{
	SDA_H;
	SCL_H;
	ANO_I2C_delay();
	if(!SDA_read)return 0;	//SDA线为低电平则总线忙,退出
	SDA_L;
	ANO_I2C_delay();
	if(SDA_read) return 0;	//SDA线为高电平则总线出错,退出
	SDA_L;
	ANO_I2C_delay();
	return 1;	
}

void ANO_I2C_Stop(void)
{
	SCL_L;
	ANO_I2C_delay();
	SDA_L;
	ANO_I2C_delay();
	SCL_H;
	ANO_I2C_delay();
	SDA_H;
	ANO_I2C_delay();
} 

void ANO_I2C_Ack(void)
{	
	SCL_L;
	ANO_I2C_delay();
	SDA_L;
	ANO_I2C_delay();
	SCL_H;
	ANO_I2C_delay();
	SCL_L;
	ANO_I2C_delay();
}   

void ANO_I2C_NoAck(void)
{	
	SCL_L;
	ANO_I2C_delay();
	SDA_H;
	ANO_I2C_delay();
	SCL_H;
	ANO_I2C_delay();
	SCL_L;
	ANO_I2C_delay();
} 

int ANO_I2C_WaitAck(void) 	 //返回为:=1有ACK,=0无ACK
{
	SCL_L;
	ANO_I2C_delay();
	SDA_H;			
	ANO_I2C_delay();
	SCL_H;
	ANO_I2C_delay();
	if(SDA_read)
	{
      SCL_L;
			ANO_I2C_delay();
      return 0;
	}
	SCL_L;
	ANO_I2C_delay();
	return 1;
}

void ANO_I2C_SendByte(u8 SendByte) //数据从高位到低位//
{
    u8 i=8;
    while(i--)
    {
        SCL_L;
        ANO_I2C_delay();
      if(SendByte&0x80)
        SDA_H;  
      else 
        SDA_L;   
        SendByte<<=1;
        ANO_I2C_delay();
				SCL_H;
				ANO_I2C_delay();
    }
    SCL_L;
}  

u8 ANO_I2C_ReadByte(void)  //数据从高位到低位//
{ 
    u8 i=8;
    u8 ReceiveByte=0;

    SDA_H;				
    while(i--)
    {
      ReceiveByte<<=1;      
      SCL_L;
      ANO_I2C_delay();
			SCL_H;
      ANO_I2C_delay();	
      if(SDA_read)
      {
        ReceiveByte|=0x01;
      }
    }
    SCL_L;
    return ReceiveByte;
} 

//单字节写入*******************************************
int ANO_I2C_Single_Write(u8 SlaveAddress,u8 REG_Address,u8 REG_data)		
{
  	if(!ANO_I2C_Start())return 0;
    ANO_I2C_SendByte(SlaveAddress);   //发送设备地址+写信号//I2C_SendByte(((REG_Address & 0x0700) >>7) | SlaveAddress & 0xFFFE);//设置高起始地址+器件地址 
    if(!ANO_I2C_WaitAck()){ANO_I2C_Stop(); return 0;}
    ANO_I2C_SendByte(REG_Address );   //设置低起始地址      
    ANO_I2C_WaitAck();	
    ANO_I2C_SendByte(REG_data);
    ANO_I2C_WaitAck();   
    ANO_I2C_Stop(); 
    return 1;
}

//单字节读取*****************************************
int ANO_I2C_Single_Read(u8 SlaveAddress,u8 REG_Address)
{   
		unsigned char REG_data;     	
		if(!ANO_I2C_Start())return 0;
    ANO_I2C_SendByte(SlaveAddress); //I2C_SendByte(((REG_Address & 0x0700) >>7) | REG_Address & 0xFFFE);//设置高起始地址+器件地址 
    if(!ANO_I2C_WaitAck())
		{
			ANO_I2C_Stop();
			return 0;
		}
    ANO_I2C_SendByte((u8) REG_Address);   //设置低起始地址      
    ANO_I2C_WaitAck();
    ANO_I2C_Start();
    ANO_I2C_SendByte(SlaveAddress+1);
    ANO_I2C_WaitAck();

		REG_data= ANO_I2C_ReadByte();
    ANO_I2C_NoAck();
    ANO_I2C_Stop();
    //return TRUE;
	return REG_data;

}	

/******************************************************************************
多字节读取
******************************************************************************/
int ANO_I2C_Mult_Read(u8 SlaveAddress,u8 REG_Address,u8 * ptChar,u8 size)
{
    uint8_t i;
    
    if(size < 1)
			return 0;
    if(!ANO_I2C_Start())
			return 0;
    ANO_I2C_SendByte(SlaveAddress);
    if(!ANO_I2C_WaitAck())
		{
			ANO_I2C_Stop();
			return 0;
		}
    ANO_I2C_SendByte(REG_Address);    
    ANO_I2C_WaitAck();
    
    ANO_I2C_Start();
    ANO_I2C_SendByte(SlaveAddress+1);
    ANO_I2C_WaitAck();
    
    for(i=1;i<size; i++)
    {
        *ptChar++ = ANO_I2C_ReadByte();
        ANO_I2C_Ack();
    }
    *ptChar++ = ANO_I2C_ReadByte();
    ANO_I2C_NoAck();
    ANO_I2C_Stop();
    return 1;    
}	

