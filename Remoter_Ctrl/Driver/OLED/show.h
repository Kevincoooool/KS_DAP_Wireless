
#ifndef __SHOW_H
#define __SHOW_H
#include "sysconfig.h"

#define REVERSE(DATA,BIT) (DATA)^(1<<(BIT))//按位取反
#define BIT0	0x0001
#define BIT1	0x0002
#define BIT2	0x0004
#define BIT3	0x0008
#define BIT4	0x0010
#define BIT5	0x0020
#define BIT6	0x0040
#define BIT7	0x0080
#define BIT8	0x0100
#define BIT9	0x0200
#define BIT10 0x0400
#define BIT11 0x0800

struct _Show
{
	u8 hardware_type;
	u8 oled_delay;
	u8 windows;
	u8 low_power;
	u8 NRF_Err;
	u8 Rc_num;
	u8 Set_Succeed;
	u8 Set_Fail;
	u8 Connect_Succeed;
	u16 Battery_Rc;
	u16 Battery_Fly;
	u16 test_flag,set_flag;
	int X,Y,Z,H;
};

extern struct _Show Show;
extern u16 set_temp;
extern u16 test_temp;
extern u8 send_flag;

void oled_show(void);
void OLED_Show_progress_bar(u8 temp,u8 chr_star,u8 chr_default,u8 x,u8 y,u8 size,u8 mode);
void OLED_Show_Seting(void);
void OLED_Show_Test(void);
void Gesture_Check0(u16 val,vs16 *set,vs16 max);
void Gesture_Check1(u16 val,u16 *set,vs16 bit);
void Gesture_Check(void);
void Show_Duty(void);
#endif
