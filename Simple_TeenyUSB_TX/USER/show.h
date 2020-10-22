/*
 * @Descripttion : 
 * @version      : 
 * @Author       : Kevincoooool
 * @Date         : 2020-10-15 18:33:12
 * @LastEditors  : Kevincoooool
 * @LastEditTime : 2020-10-15 18:33:43
 * @FilePath     : \Simple_TeenyUSB_TX\USER\show.h
 */

#ifndef __SHOW_H
#define __SHOW_H
#include "stm32f1xx.h"

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
	uint8_t hardware_type;
	uint8_t oled_delay;
	uint8_t windows;
	uint8_t low_power;
	uint8_t NRF_Err;
	uint8_t Rc_num;
	uint8_t Set_Succeed;
	uint8_t Set_Fail;
	uint8_t Connect_Succeed;
	uint16_t Battery_Rc;
	uint16_t Battery_Fly;
	uint16_t test_flag,set_flag;
	int X,Y,Z,H;
};

extern struct _Show Show;
extern uint16_t set_temp;
extern uint16_t test_temp;
extern uint8_t send_flag;
void Select_Menu(void);
void oled_show(void);
void OLED_Show_progress_bar(uint8_t temp,uint8_t chr_star,uint8_t chr_default,uint8_t x,uint8_t y,uint8_t size,uint8_t mode);
void OLED_Show_Seting(void);
void OLED_Show_Test(void);
void Gesture_Check0(uint16_t val,uint16_t *set,uint16_t max);
void Gesture_Check1(uint16_t val,uint16_t *set,uint16_t bit);
void Gesture_Check(void);
void Show_Duty(void);
#endif
