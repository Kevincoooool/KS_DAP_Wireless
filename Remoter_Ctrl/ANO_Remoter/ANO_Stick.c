/******************** (C) COPYRIGHT 2016 ANO Tech ***************************
 * 作者		 ：玩物励志科技
 * 移植自  ：匿名科创
 * 淘宝    ：https://wanwulizhi.taobao.com
 * 技术Q群 ：572299632
*****************************************************************************/
#include "ANO_Stick.h"

#define American_Mode

struct _Rc Rc;
struct _Filter Filter_THR,Filter_PIT,Filter_ROL,Filter_YAW,
							 Filter_AUX1,Filter_AUX2,Filter_AUX3,Filter_AUX5;

void Mid_Limit(struct _Rc *rc)
{
	if(rc->THR>1450 && rc->THR<1550) rc->THR = 1500;
	if(rc->PIT>1450 && rc->PIT<1550) rc->PIT = 1500;
	if(rc->ROL>1450 && rc->ROL<1550) rc->ROL = 1500;
	if(rc->YAW>1450 && rc->YAW<1550) rc->YAW = 1500;
}

void RC_Limit(struct _Rc *rc)
{
	rc->THR = (rc->THR<=1000)?1000:rc->THR; 
	rc->THR = (rc->THR>=2000)?2000:rc->THR; 
	rc->PIT = (rc->PIT<=1000)?1000:rc->PIT; 
	rc->PIT = (rc->PIT>=2000)?2000:rc->PIT; 
	rc->ROL = (rc->ROL<=1000)?1000:rc->ROL; 
	rc->ROL = (rc->ROL>=2000)?2000:rc->ROL; 
	rc->YAW  = (rc->YAW<=1000)?1000:rc->YAW; 
	rc->YAW  = (rc->YAW>=2000)?2000:rc->YAW; 
	rc->AUX1 = (rc->AUX1<=1000)?1000:rc->AUX1; 
	rc->AUX1 = (rc->AUX1>=2000)?2000:rc->AUX1; 
	rc->AUX2 = (rc->AUX2<=1000)?1000:rc->AUX2; 
	rc->AUX2 = (rc->AUX2>=2000)?2000:rc->AUX2; 
	rc->AUX3 = (rc->AUX3<=1000)?1000:rc->AUX3; 
	rc->AUX3 = (rc->AUX3>=2000)?2000:rc->AUX3; 
}

void Window_Filter(struct _Rc *rc)
{
	static uint8_t 	Filter_Count = 0;
	
	//丢数据
	Filter_THR.sum  -= Filter_THR.old[Filter_Count];
	Filter_YAW.sum  -= Filter_YAW.old[Filter_Count];
	Filter_ROL.sum  -= Filter_ROL.old[Filter_Count];
	Filter_PIT.sum  -= Filter_PIT.old[Filter_Count];
	Filter_AUX1.sum -= Filter_AUX1.old[Filter_Count];
	Filter_AUX2.sum -= Filter_AUX2.old[Filter_Count];
	Filter_AUX3.sum -= Filter_AUX3.old[Filter_Count];
	Filter_AUX5.sum -= Filter_AUX5.old[Filter_Count];
	
	Filter_THR.old[Filter_Count]  = rc->THR;
	Filter_YAW.old[Filter_Count]  = rc->YAW;
	Filter_ROL.old[Filter_Count]  = rc->ROL;
	Filter_PIT.old[Filter_Count]  = rc->PIT;
	Filter_AUX1.old[Filter_Count] = rc->AUX1;
	Filter_AUX2.old[Filter_Count] = rc->AUX2;
	Filter_AUX3.old[Filter_Count] = rc->AUX3;
	Filter_AUX5.old[Filter_Count] = rc->AUX5;
	
	//更新数据
	Filter_THR.sum  += Filter_THR.old[Filter_Count];
	Filter_YAW.sum  += Filter_YAW.old[Filter_Count];
	Filter_ROL.sum  += Filter_ROL.old[Filter_Count];
	Filter_PIT.sum  += Filter_PIT.old[Filter_Count];
	Filter_AUX1.sum += Filter_AUX1.old[Filter_Count];
	Filter_AUX2.sum += Filter_AUX2.old[Filter_Count];
	Filter_AUX3.sum += Filter_AUX3.old[Filter_Count];
	Filter_AUX5.sum += Filter_AUX5.old[Filter_Count];
	
	//输出数据
	rc->THR = Filter_THR.sum / Filter_Num;
	rc->YAW = Filter_YAW.sum / Filter_Num;
	rc->ROL = Filter_ROL.sum / Filter_Num;
	rc->PIT = Filter_PIT.sum / Filter_Num;
	rc->AUX1 = Filter_AUX1.sum / Filter_Num;
	rc->AUX2 = Filter_AUX2.sum / Filter_Num;
	rc->AUX3 = Filter_AUX3.sum / Filter_Num;
	rc->AUX5 = Filter_AUX5.sum / Filter_Num;
	
	Filter_Count++;
	if(Filter_Count == Filter_Num)	Filter_Count=0;
}

void Mid_Offset(struct _Rc *rc)
{
	if(ANO_Param.OffSet_En)
	{		
		static uint8_t count=0;
		static int32_t count0,count1,count2,count3;
		if(count==0)
		{
			ANO_Param.OffSet_Thr = 0;
			ANO_Param.OffSet_Yaw = 0;
			ANO_Param.OffSet_Pit = 0;
			ANO_Param.OffSet_Rol = 0;
			count  = 1;
			count0 = 0;
			count1 = 0;
			count2 = 0;
			count3 = 0;
			return;
		}
		else
		{
			count++;
			count0 += rc->THR;
			count1 += rc->YAW;
			count2 += rc->PIT;
			count3 += rc->ROL;
		}
		if(count==51)
		{
			count--;
			ANO_Param.OffSet_Thr = count0 / count - 1500;
			ANO_Param.OffSet_Yaw = count1 / count - 1500;
			ANO_Param.OffSet_Pit = count2 / count - 1500;
			ANO_Param.OffSet_Rol = count3 / count - 1500;
			count = 0;
			
			ANO_Param.OffSet_En = 0;
			ANO_Param_SAVE();
		}
	}
}
void ANO_Stick_Scan(void)
{
#ifdef American_Mode
	Rc.THR = 1000 + (uint16_t)(0.25f*ADC_ConvertedValue[4]) - ANO_Param.OffSet_Thr;
	Rc.PIT = 2000 - (uint16_t)(0.25f*ADC_ConvertedValue[7]) - ANO_Param.OffSet_Pit;
#else
	Rc.PIT = 1000 + (uint16_t)(0.25f*ADC_ConvertedValue[4]) - ANO_Param.OffSet_Pit;
	Rc.THR = 2000 - (uint16_t)(0.25f*ADC_ConvertedValue[7]) - ANO_Param.OffSet_Thr;
#endif

	Rc.YAW = 1000 + (uint16_t)(0.25f*ADC_ConvertedValue[5]) - ANO_Param.OffSet_Yaw;
	Rc.ROL = 2000 - (uint16_t)(0.25f*ADC_ConvertedValue[6]) - ANO_Param.OffSet_Rol;
	
	Rc.AUX1 = 2000 - (uint16_t)(0.25f*ADC_ConvertedValue[2]);
	Rc.AUX2 = 2000 - (uint16_t)(0.25f*ADC_ConvertedValue[0]);
	Rc.AUX3 = 2000 - (uint16_t)(0.25f*ADC_ConvertedValue[1]);
	Rc.AUX5 = (uint16_t)(2.0f*ADC_ConvertedValue[3]/ADC_ConvertedValue[8]*1.2f*100);
	
	Window_Filter(&Rc);	//滑动窗口滤波
	Mid_Offset(&Rc);			//中点校准
	RC_Limit(&Rc);			//输出限幅
	Mid_Limit(&Rc);			//中点限幅
}

