/******************** (C) COPYRIGHT 2016 ANO Tech ***************************
 * 作者		 ：玩物励志科技
 * 移植自  ：匿名科创
 * 淘宝    ：https://wanwulizhi.taobao.com
 * 技术Q群 ：572299632
*****************************************************************************/
#include "ANO_Drv_LED.h"
#include "math.h"

#define LED TIM2->CCR4
#define PI 3.141592653f
#define LED_Red_On  LED = 0
#define LED_Red_OFF LED = 1999

float light = 1.5*PI;

static void Tim2_init(void)
{
	TIM_TimeBaseInitTypeDef		TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  			TIM_OCInitStructure;
	
 	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
	
	GPIO_PinRemapConfig(GPIO_PartialRemap2_TIM2,ENABLE);
	
	TIM_TimeBaseStructure.TIM_Period = 2000 - 1; 
	TIM_TimeBaseStructure.TIM_Prescaler = 72 - 1; 
	TIM_TimeBaseStructure.TIM_ClockDivision = 0;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);
	
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_Pulse = 0; 
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; 
	
	TIM_OC4Init(TIM2, &TIM_OCInitStructure); 
	TIM_OC4PreloadConfig(TIM2, TIM_OCPreload_Enable); 
	
	TIM_ARRPreloadConfig(TIM2, ENABLE); 
	TIM_Cmd(TIM2, ENABLE); 
	
	LED = 0;
}

void ANO_LED_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);      /*使能SWD 禁用JTAG*/
	RCC_APB2PeriphClockCmd(ANO_RCC_LED_0,ENABLE);

	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Pin   = ANO_Pin_LED_0;
	GPIO_Init(ANO_GPIO_LED_0, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin =  LED_Red_Pin;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; 
	GPIO_Init(LED_Red_GPIO, &GPIO_InitStructure);
	
	Tim2_init();
}

void ANO_LED_0_ON(void)
{
	GPIO_ResetBits(ANO_GPIO_LED_0, ANO_Pin_LED_0);	
}

void ANO_LED_0_OFF(void)
{
	GPIO_SetBits(ANO_GPIO_LED_0, ANO_Pin_LED_0);			
}

void ANO_LED_0_FLASH(void)
{
	for(u8 i=0;i<3;i++)
	{
		ANO_LED_0_ON();
		LED_Red_OFF;
		Delay(600000);
		ANO_LED_0_OFF();
		LED_Red_On;
		Delay(600000);
	}
}
void Breath_LED(float speed)
{
	light += speed;
	if(light >=2*PI)	light = 0.0f;
	LED = 1999*( (sin(light)+1) / 2);
}
/******************* (C) COPYRIGHT 2014 ANO TECH *****END OF FILE************/

