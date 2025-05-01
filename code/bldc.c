#include "init.h"

#define DIROUT_PIN  (P02_5) // 方向输出引脚
#define PWMOUT_PIN  (ATOM0_CH4_P02_4) // PWM输出引脚

int16_t BLDC_duty = 0; // 电机1的占空比

void BLDC_Init(void)
{
    // 初始化PWM输出引脚
    pwm_init(PWMOUT_PIN, 20000, 0); // 初始化 PWM 通道 频率 17KHz 初始占空比 0%
    // 初始化方向输出引脚
    gpio_init(DIROUT_PIN, GPO, GPIO_HIGH, GPO_PUSH_PULL);                          // 初始化电机方向输出引脚
}


void BLDC_Set_Duty(int16_t BLDC_duty)
{
        
    // 设置方向引脚
    if (BLDC_duty >= 0)
    {
        gpio_set_level(DIROUT_PIN, GPIO_HIGH); // 正转
    }
    else
    {
        gpio_set_level(DIROUT_PIN, GPIO_LOW); // 反转
        BLDC_duty = -BLDC_duty; // 取绝对值
    }

    if (BLDC_duty > DUTY_MAX)
    {
        BLDC_duty = DUTY_MAX;
    }
    else if (BLDC_duty < -DUTY_MAX)
    {
        BLDC_duty = -DUTY_MAX;
    }
    
    // 设置PWM占空比
    pwm_set_duty(PWMOUT_PIN, BLDC_duty);
}
