//************玩物励志科技***************************************************************

//与本软件配套的硬件：https://item.taobao.com/item.htm?id=530846387509
//使用过程中有什么问题请旺旺联系店主，或者加店主QQ：544645244

//************玩物励志科技***************************************************************
#include "show.h"
#include "oledfont.h"
#include "oled.h"

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
#define Y2 Y1+12
#define Y3 Y2+12
#define Y4 Y3+12
#define Y5 Y4+12

struct _Show Show;

//unsigned char i;          //计数变量
unsigned char Send_Count; //串口需要发送的数据个数
float Vol;

/**************************************************************************
函数功能：OLED显示
入口参数：无
返回  值：无
**************************************************************************/
void oled_show(void)
{
	uint8_t temp;
	int temp1;
	
	static uint8_t page,page_temp,flash_cnt,show_mode=1;
	
	if(page != page_temp)//切换页面先清屏
	{
		page_temp = page;
		OLED_Clear();
	}
	///////////////////////////////第一行///////////////////////////////////
	//显示提示
	if(Show.low_power)//遥控低电量
	{
		flash_cnt ++;
		if(flash_cnt>3) 
		{
			flash_cnt=0;
			if(show_mode==0)show_mode=1;
			else show_mode = 0;
		}
		
		for(uint8_t i=0;i<12;i++) OLED_Show_CH_String(Line1_Begin+i*6,Y0,oled_CH16[i],12,show_mode);
	}
	else if(Show.test_flag&BIT5)//飞机低电量
	{
		flash_cnt ++;
		if(flash_cnt>3) 
		{
			flash_cnt=0;
			if(show_mode==0)show_mode=1;
			else show_mode = 0;
		}
		
		for(uint8_t i=0;i<12;i++) OLED_Show_CH_String(Line1_Begin+i*6,Y0,oled_CH17[i],12,show_mode);
	}
	else if(Show.Set_Succeed)//设置成功
	{
		show_mode = 1;
		for(uint8_t i=0;i<12;i++) OLED_Show_CH_String(Line1_Begin+i*6,Y0,oled_CH21[i],12,show_mode);
	}
	else if(Show.Set_Fail)//设置失败
	{
		show_mode = 1;
		for(uint8_t i=0;i<12;i++) OLED_Show_CH_String(Line1_Begin+i*6,Y0,oled_CH22[i],12,show_mode);
	}
	else if(Show.test_flag&BIT8)//指南针异常！
	{
		flash_cnt ++;
		if(flash_cnt>3)
		{
			flash_cnt=0;
			if(show_mode==0)show_mode=1;
			else show_mode = 0;
		}
		
		for(uint8_t i=0;i<12;i++) OLED_Show_CH_String(Line1_Begin+i*6,Y0,oled_CH24[i],12,show_mode);
	}
	else
	{
		OLED_Show_CH(Line1_Begin+00,Y0,0,12,1);
		OLED_Show_CH(Line1_Begin+12,Y0,1,12,1);
		OLED_Show_CH(Line1_Begin+24,Y0,2,12,1);
		OLED_Show_CH(Line1_Begin+36,Y0,3,12,1);
		OLED_Show_CH(Line1_Begin+48,Y0,4,12,1);
		OLED_Show_CH(Line1_Begin+60,Y0,5,12,1);
	}
	//////////////////////////////////////////////////////
	if(0)	OLED_Show_CH(2,Y0,6 ,12,1);//无线模块故障显示X
	else							OLED_ShowNumber(2,Y0,2,3,12);//显示无线信道
	
	//显示信号强度
	temp = 80/20;
	switch(temp)
	{
		case 0:OLED_Show_CH(Line1_Begin+85,Y0,6 ,12,1);break;
		case 1:OLED_Show_CH(Line1_Begin+85,Y0,7 ,12,1);break;
		case 2:OLED_Show_CH(Line1_Begin+85,Y0,8 ,12,1);break;
		case 3:OLED_Show_CH(Line1_Begin+85,Y0,9 ,12,1);break;
		case 4:OLED_Show_CH(Line1_Begin+85,Y0,10,12,1);break;
		default:OLED_Show_CH(Line1_Begin+85,Y0,11,12,1);break;
	}
	///////////////////////////////第二行///////////////////////////////////
	//显示电压	
	OLED_ShowString(Line2_Begin+00,Y1,"R-V:",12,1);OLED_ShowString(Line2_Begin+36,Y1,".",12,1);
	OLED_ShowNumber(Line2_Begin+30,Y1,80/100,1,12);OLED_ShowNumber(Line2_Begin+42,Y1,80%100,2,12);
	if(Show.Battery_Rc%100<10)	OLED_ShowNumber(Line2_Begin+42,Y1,0,1,12);
	
	OLED_ShowString(Line2_Begin+64,Y1,"F-V:",12,1);OLED_ShowString(Line2_Begin+100,Y1,".",12,1);
	OLED_ShowNumber(Line2_Begin+94,Y1,70/100,1,12);OLED_ShowNumber(Line2_Begin+106,Y1,70%100,2,12);
	if(Show.Battery_Fly%100<10)	OLED_ShowNumber(Line2_Begin+106,Y1,0,1,12);
	///////////////////////////////第三、四行/////////////////////////////////
	//显示遥控数据
	OLED_ShowString(Line3_Begin+00,Y2,"THR:",12,1);
	temp = (1700-1000)/41;
	OLED_Show_progress_bar(temp,12,24,Line4_Begin+6 ,Y2,12,1);
	temp = (1700-1500)/41;
	OLED_Show_progress_bar(temp,12,12,Line4_Begin+18,Y2,12,1);
	
	OLED_ShowString(Line3_Begin+64,Y2,"ROL:",12,1);
	temp = (1800-1000)/41;
	OLED_Show_progress_bar(temp,12,24,Line4_Begin+70,Y2,12,1);
	temp = (1800-1500)/41;
	OLED_Show_progress_bar(temp,12,12,Line4_Begin+82,Y2,12,1);
	
	OLED_ShowString(Line3_Begin+00,Y3,"YAW:",12,1);
	temp = (1800-1000)/41;
	OLED_Show_progress_bar(temp,12,24,Line4_Begin+6 ,Y3,12,1);
	temp = (1800-1500)/41;
	OLED_Show_progress_bar(temp,12,12,Line4_Begin+18,Y3,12,1);
	
	OLED_ShowString(Line3_Begin+64,Y3,"PIT:",12,1);
	temp = (1800-1000)/41;
	OLED_Show_progress_bar(temp,12,24,Line4_Begin+70,Y3,12,1);
	temp = (1800-1500)/41;
	OLED_Show_progress_bar(temp,12,12,Line4_Begin+82,Y3,12,1);
	///////////////////////////////第五行///////////////////////////////////
	if(Show.Rc_num && Show.hardware_type == 1)
	{
		page = 1;//第一页
		//显示姿态角度和高度
		if(Show.X<0) temp1 = -Show.X,OLED_ShowString(X_Begin,Y4,"-",12,1);
		else         temp1 = Show.X, OLED_ShowString(X_Begin,Y4,"+",12,1);
		OLED_ShowNumber(X_Begin+8,Y4,temp1/10,3,12);
		OLED_ShowString(X_Begin+28,Y4,".",12,1);
		OLED_ShowNumber(X_Begin+32,Y4,temp1%10,1,12);
		
		if(Show.Y<0) temp1 = -Show.Y,OLED_ShowString(Y_Begin,Y4,"-",12,1);
		else    temp1 = Show.Y, OLED_ShowString(Y_Begin,Y4,"+",12,1);
		OLED_ShowNumber(Y_Begin+8,Y4,temp1/10,3,12);
		OLED_ShowString(Y_Begin+28,Y4,".",12,1);
		OLED_ShowNumber(Y_Begin+32,Y4,temp1%10,1,12);
		
		if(Show.H<0) 	temp1 =-Show.H/10,  OLED_ShowString(Z_Begin,Y4,"-",12,1);
		else    			temp1 = Show.H/10,  OLED_ShowString(Z_Begin,Y4,"+",12,1);
		//最高显示9999分米,也就是999.9米。
		if(temp1>9999) temp1 = 9999,OLED_ShowString(Z_Begin,Y4,">",12,1);
		OLED_ShowNumber(Z_Begin+8,Y4,temp1,4,12);
	}
	else
	{
		page = 2;//第二页
		//显示微调旋钮数据
		OLED_ShowString(Line5_Begin+00,Y4,"L:",12,1);
		temp = (1800-1000)/41;
		OLED_Show_progress_bar(temp,12,24,Line5_Begin+15 ,Y4,12,1);
		temp = (1800-1500)/41;
		OLED_Show_progress_bar(temp,12,12,Line5_Begin+27,Y4,12,1);
		
		OLED_ShowString(Line5_Begin+44,Y4,"M:",12,1);
		temp = (1800-1000)/41;
		OLED_Show_progress_bar(temp,12,24,Line5_Begin+59 ,Y4,12,1);
		temp = (1800-1500)/41;
		OLED_Show_progress_bar(temp,12,12,Line5_Begin+71,Y4,12,1);
		
		OLED_ShowString(Line5_Begin+88,Y4,"R:",12,1);
		temp = (1800-1000)/41;
		OLED_Show_progress_bar(temp,12,24,Line5_Begin+103 ,Y4,12,1);
		temp = (1800-1500)/41;
		OLED_Show_progress_bar(temp,12,12,Line5_Begin+115,Y4,12,1);
	}
	
	OLED_Refresh_Gram();//开始显示
}
//进度条显示函数
void OLED_Show_progress_bar(uint8_t temp,uint8_t chr_star,uint8_t chr_default,uint8_t x,uint8_t y,uint8_t size,uint8_t mode)
{
	switch(temp)
	{
		case  0:OLED_Show_CH(x,y,chr_star+temp,size,size);break;
		case  1:OLED_Show_CH(x,y,chr_star+temp,size,size);break;
		case  2:OLED_Show_CH(x,y,chr_star+temp,size,size);break;
		case  3:OLED_Show_CH(x,y,chr_star+temp,size,size);break;
		case  4:OLED_Show_CH(x,y,chr_star+temp,size,size);break;
		case  5:OLED_Show_CH(x,y,chr_star+temp,size,size);break;
		case  6:OLED_Show_CH(x,y,chr_star+temp,size,size);break;
		case  7:OLED_Show_CH(x,y,chr_star+temp,size,size);break;
		case  8:OLED_Show_CH(x,y,chr_star+temp,size,size);break;
		case  9:OLED_Show_CH(x,y,chr_star+temp,size,size);break;
		case 10:OLED_Show_CH(x,y,chr_star+temp,size,size);break;
		case 11:OLED_Show_CH(x,y,chr_star+temp,size,size);break;
		case 12:OLED_Show_CH(x,y,chr_star+temp,size,size);break;
		
		default:OLED_Show_CH(x,y,chr_default,size,size);break;
	}
}

uint16_t set_bit=0,bit_max=6;
uint16_t set_temp=0x0000;

void OLED_Show_Seting(void)
{
	uint8_t cnt=0,bit_cnt=0;
	uint8_t mode,page;
	static uint8_t page_temp;
	
	for(uint8_t i=0;i<8;i++) OLED_Show_CH_String(40+i*6,cnt,oled_CH0[i],12,1);

	page = set_bit/4;
	bit_cnt = 4*page;
	if(page_temp!=page)
	{
		page_temp=page;
		OLED_Clear();
	}
	
	switch(page)
	{
		case 0:
			cnt+=13;
			for(uint8_t i=0;i<10;i++) OLED_Show_CH_String(0+i*6,cnt,oled_CH1[i],12,1);
			if(set_bit==bit_cnt) mode=0;	else mode=1;
			if( set_temp&BIT0 )	for(uint8_t i=0;i<6;i++) OLED_Show_CH_String(94+i*6,cnt,oled_CH12[i],12,mode);
			else								for(uint8_t i=0;i<6;i++) OLED_Show_CH_String(94+i*6,cnt,oled_CH13[i],12,mode);
			bit_cnt++;//bit_max=0

			cnt+=13;
			for(uint8_t i=0;i<10;i++) OLED_Show_CH_String(0+i*6,cnt,oled_CH2[i],12,1);
			if(set_bit==bit_cnt) mode=0;	else mode=1;
			if( set_temp&BIT1 )	for(uint8_t i=0;i<6;i++) OLED_Show_CH_String(94+i*6,cnt,oled_CH12[i],12,mode);
			else								for(uint8_t i=0;i<6;i++) OLED_Show_CH_String(94+i*6,cnt,oled_CH13[i],12,mode);
			bit_cnt++;//bit_max=1

			cnt+=13;
			for(uint8_t i=0;i<10;i++) OLED_Show_CH_String(0+i*6,cnt,oled_CH3[i],12,1);
			if(set_bit==bit_cnt) mode=0; else mode=1;
			if( set_temp&BIT2 )	for(uint8_t i=0;i<6;i++) OLED_Show_CH_String(94+i*6,cnt,oled_CH12[i],12,mode);
			else								for(uint8_t i=0;i<6;i++) OLED_Show_CH_String(94+i*6,cnt,oled_CH13[i],12,mode);
			bit_cnt++;//bit_max=2

			cnt+=13;
			for(uint8_t i=0;i<10;i++) OLED_Show_CH_String(0+i*6,cnt,oled_CH4[i],12,1);
			if(set_bit==bit_cnt)	mode=0; else mode=1;
			if( set_temp&BIT3 )	for(uint8_t i=0;i<6;i++) OLED_Show_CH_String(94+i*6,cnt,oled_CH12[i],12,mode);
			else								for(uint8_t i=0;i<6;i++) OLED_Show_CH_String(94+i*6,cnt,oled_CH13[i],12,mode);
			bit_cnt++;//bit_max=3
		break;
		
		case 1:
			cnt+=13;
			for(uint8_t i=0;i<10;i++) OLED_Show_CH_String(0+i*6,cnt,oled_CH14[i],12,1);
			if(set_bit==bit_cnt)	mode=0; else mode=1;
			if( set_temp&BIT4 )	for(uint8_t i=0;i<6;i++) OLED_Show_CH_String(94+i*6,cnt,oled_CH12[i],12,mode);
			else								for(uint8_t i=0;i<6;i++) OLED_Show_CH_String(94+i*6,cnt,oled_CH13[i],12,mode);
			bit_cnt++;//bit_max=4
		
			cnt+=13;
			for(uint8_t i=0;i<10;i++) OLED_Show_CH_String(0+i*6,cnt,oled_CH18[i],12,1);
			if(set_bit==bit_cnt)	mode=0; else mode=1;
			if( set_temp&BIT5 )	for(uint8_t i=0;i<6;i++) OLED_Show_CH_String(94+i*6,cnt,oled_CH12[i],12,mode);
			else								for(uint8_t i=0;i<6;i++) OLED_Show_CH_String(94+i*6,cnt,oled_CH13[i],12,mode);
			bit_cnt++;//bit_max=5
		
			cnt+=13;
			for(uint8_t i=0;i<10;i++) OLED_Show_CH_String(0+i*6,cnt,oled_CH20[i],12,1);
			if(set_bit==bit_cnt)	mode=0; else mode=1;
			if( set_temp&BIT6 )	for(uint8_t i=0;i<6;i++) OLED_Show_CH_String(94+i*6,cnt,oled_CH12[i],12,mode);
			else								for(uint8_t i=0;i<6;i++) OLED_Show_CH_String(94+i*6,cnt,oled_CH13[i],12,mode);
			bit_cnt++;//bit_max=6
		
		break;
		
		default:break;
	}
	
	OLED_Refresh_Gram();//开始显示
}

uint16_t test_bit=0,test_max=6;
uint16_t  test_temp=0;

void OLED_Show_Test(void)
{
	uint8_t cnt=0,bit_cnt=0;
	uint8_t mode,page;
	static uint8_t page_temp;
	
	test_temp = Show.test_flag;
	
	for(uint8_t i=0;i<10;i++) OLED_Show_CH_String(34+i*6,cnt,oled_CH5[i],12,1);
	
	page = test_bit/4;
	bit_cnt = 4*page;
	if(page_temp!=page)	
	{
		page_temp=page;
		OLED_Clear();
	}
	
	switch(page)
	{
		case 0:
			cnt+=13;
			for(uint8_t i=0;i<8;i++) OLED_Show_CH_String(0+i*6,cnt,oled_CH6[i],12,1);
			if(test_bit==bit_cnt++) mode=0; else mode=1;
			if( test_temp&BIT0 )for(uint8_t i=0;i<4;i++) OLED_Show_CH_String(104+i*6,cnt,oled_CH10[i],12,mode);
			else								for(uint8_t i=0;i<4;i++) OLED_Show_CH_String(104+i*6,cnt,oled_CH11[i],12,mode);
			
			cnt+=13;
			for(uint8_t i=0;i<8;i++) OLED_Show_CH_String(0+i*6,cnt,oled_CH7[i],12,1);
			if(test_bit==bit_cnt++) mode=0; else mode=1;
			if( test_temp&BIT1 )for(uint8_t i=0;i<4;i++) OLED_Show_CH_String(104+i*6,cnt,oled_CH10[i],12,mode);
			else								for(uint8_t i=0;i<4;i++) OLED_Show_CH_String(104+i*6,cnt,oled_CH11[i],12,mode);
			
			cnt+=13;
			for(uint8_t i=0;i<10;i++) OLED_Show_CH_String(0+i*6,cnt,oled_CH8[i],12,1);
			if(test_bit==bit_cnt++) mode=0; else mode=1;
			if( test_temp&BIT2 )for(uint8_t i=0;i<4;i++) OLED_Show_CH_String(104+i*6,cnt,oled_CH10[i],12,mode);
			else								for(uint8_t i=0;i<4;i++) OLED_Show_CH_String(104+i*6,cnt,oled_CH11[i],12,mode);

			cnt+=13;
			for(uint8_t i=0;i<8;i++) OLED_Show_CH_String(0+i*6,cnt,oled_CH23[i],12,1);
			if(test_bit==bit_cnt++) mode=0; else mode=1;
			if( test_temp&BIT7 )for(uint8_t i=0;i<4;i++) OLED_Show_CH_String(104+i*6,cnt,oled_CH10[i],12,mode);
			else								for(uint8_t i=0;i<4;i++) OLED_Show_CH_String(104+i*6,cnt,oled_CH11[i],12,mode);
		break;
		
		case 1:
			cnt+=13;
			for(uint8_t i=0;i<10;i++) OLED_Show_CH_String(0+i*6,cnt,oled_CH19[i],12,1);
			if(test_bit==bit_cnt++) mode=0; else mode=1;
			if( test_temp&BIT6 )for(uint8_t i=0;i<4;i++) OLED_Show_CH_String(104+i*6,cnt,oled_CH10[i],12,mode);
			else								for(uint8_t i=0;i<4;i++) OLED_Show_CH_String(104+i*6,cnt,oled_CH11[i],12,mode);
		
			cnt+=13;
			for(uint8_t i=0;i<14;i++) OLED_Show_CH_String(0+i*6,cnt,oled_CH15[i],12,1);
			if(test_bit==bit_cnt++) mode=0; else mode=1;
			if( test_temp&BIT4 )for(uint8_t i=0;i<4;i++) OLED_Show_CH_String(104+i*6,cnt,oled_CH10[i],12,mode);
			else								for(uint8_t i=0;i<4;i++) OLED_Show_CH_String(104+i*6,cnt,oled_CH11[i],12,mode);
		
			cnt+=13;
			for(uint8_t i=0;i<9;i++) OLED_Show_CH_String(0+i*6,cnt,oled_CH25[i],12,1);
			if(test_bit==bit_cnt++) mode=0; else mode=1;
			if( test_temp&BIT9 )for(uint8_t i=0;i<4;i++) OLED_Show_CH_String(104+i*6,cnt,oled_CH10[i],12,mode);
			else								for(uint8_t i=0;i<4;i++) OLED_Show_CH_String(104+i*6,cnt,oled_CH11[i],12,mode);
		break;
		
		default:break;
	}

	OLED_Refresh_Gram();//开始显示
}

//遥杆检测
void Gesture_Check0(uint16_t val,uint16_t *set,uint16_t max)
{
	static uint8_t cnt0,cnt1;
	
	if(val>1800) 
	{
		cnt0++;
	}
	else
	{
		if(cnt0>2) (*set)--;
		cnt0 = 0;
	}
	
	if(val<1200) 
	{
		cnt1++;
	}
	else
	{
		if(cnt1>2) (*set)++;
		cnt1 = 0;
	}
	
	if((*set)<0) 				(*set) = max;
	else if((*set)>max) (*set) = 0;
}

void Gesture_Check1(uint16_t val,uint16_t *set,uint16_t bit)
{
	static uint8_t cnt0;
	
	if(val>1800 || val<1200) 
	{
		cnt0++;
	}
	else
	{
		if(cnt0>2) 
			*set = REVERSE(*set,bit);
		cnt0 = 0;
	}
}

uint8_t send_flag=0;

void Gesture_Check(void)
{
	static uint8_t temp;
	
	if(temp!=Show.windows)
	{
		if(Show.windows==1) 
		{
			set_temp = Show.set_flag;
			Show.Set_Succeed = 0;
			Show.Set_Fail = 0;
		}
		if(temp==1 && set_temp!=Show.set_flag) send_flag = 1;
		
		temp=Show.windows;
	}
	switch(Show.windows)
	{
		case 1:
			Gesture_Check0(1800,&set_bit,bit_max);
			if(Show.Connect_Succeed)
			{
				Gesture_Check1(1800,&set_temp,set_bit);
			}
		break;
		
		case 2:
			Gesture_Check0(1800,&test_bit,test_max);
		break;
		
		default:break;
	}
}

void Show_Duty(void)
{
	static uint8_t temp;
	
	if(Show.windows!=temp)
	{
		temp = Show.windows;
		OLED_Clear();
	}
	switch(Show.windows)
	{
		case 0:	oled_show();	break;
		case 1:	OLED_Show_Seting();	break;
		case 2:	OLED_Show_Test();	break;
		default:break;
	}
}
