#include "zf_common_headfile.h"

#define SREER                   (ATOM1_CH1_P33_9)

void Sreer_init(void)
{
    pwm_init(SREER, 50, 1130);
}

void Sreer_set_duty(int duty)
{
    pwm_set_duty(SREER, duty);
}
