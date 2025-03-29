#ifndef _BLDC_H_
#define _BLDC_H_

#include "zf_common_headfile.h"

void BLDC_Init(void);
void BLDC_Set_Speed(uint32 speed);
void BLDC_Update(void);

#endif