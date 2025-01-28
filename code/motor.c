#include "zf_common_headfile.h"

#define PWM1                    (ATOM0_CH4_P02_4)
#define PWM2                    (ATOM0_CH5_P02_5)

int duty1 = 0;
int duty2 = 0;

// 初始化PWM
void Motor_init(void)
{
    pwm_init(PWM1, 17000, 0);                                                   // 初始化 PWM 通道 频率 17KHz 初始占空比 0%
    pwm_init(PWM2, 17000, 0);                                                   // 初始化 PWM 通道 频率 17KHz 初始占空比 0%
}

// 设置PWM占空比
void Motor_set_duty(int duty1, int duty2)
{
    pwm_set_duty(PWM1, duty1);
    pwm_set_duty(PWM2, duty2);
}
