#ifndef _BLDC_H_
#define _BLDC_H_

#include "zf_common_headfile.h"

extern uint8_t BLDC_Dir;   //   0:正转  1:反转

void BLDC_Init(void);
void BLDC_Set_duty(int32_t duty);
void BLDC_Update(void);
void BLDC_Dir_Judge(void);

#endif