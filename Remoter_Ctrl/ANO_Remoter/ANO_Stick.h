#ifndef __ANO_STICK_H__
#define __ANO_STICK_H__

#include "sysconfig.h"

struct _Rc
{
	int16_t THR;
	int16_t YAW;
	int16_t PIT;
	int16_t ROL;
	
	int16_t AUX1;
	int16_t AUX2;
	int16_t AUX3;
	int16_t AUX4;
	int16_t AUX5;
	int16_t AUX6;
};

#define Filter_Num 10

struct _Filter
{
	uint32_t sum;
	uint16_t old[Filter_Num];
};

extern struct _Filter Filter;
extern struct _Rc Rc;

void ANO_Stick_Init(void);
void ANO_Stick_Scan(void);

#endif
