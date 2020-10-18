#ifndef __ANO_DRV_ADC_H
#define	__ANO_DRV_ADC_H

#include "board.h"

#define M 9
void ADC1_Init(void);

extern __IO uint16_t ADC_ConvertedValue[M];

#endif /* __ADC_H */


