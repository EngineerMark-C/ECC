#include "zf_common_headfile.h"
#include "init.h"

#define STEER                   (ATOM1_CH1_P33_9)

#define PWM_STEER_MIN_L_SMALL					1005                                            // L-Small车舵机PWM右极限
#define PWM_STEER_MIDDLE_L_SMALL				1130                                            // L-Small车舵机PWM中值
#define PWM_STEER_MAX_L_SMALL					1250                                            // L-Small车舵机PWM左极限
#define MAX_ANGLE_L_SMALL						22.0f                                           // L-Small车舵机最大转角

int duty_steer = 0;

void Steer_init(void)
{
    pwm_init(STEER, 50, PWM_STEER_MIDDLE_L_SMALL);
}

void Steer_set_duty(int duty)
{
    if (duty < PWM_STEER_MIN_L_SMALL)
    {
        duty = PWM_STEER_MIN_L_SMALL;
    }
    if (duty > PWM_STEER_MAX_L_SMALL)
    {
        duty = PWM_STEER_MAX_L_SMALL;
    }
    pwm_set_duty(STEER, duty);
}

void Steer_set_angle(float angle)
{
    //  duty = 中值 + (角度 / 最大角度) * (左极限 - 中值)
    if (angle > MAX_ANGLE_L_SMALL)
    {
        angle = MAX_ANGLE_L_SMALL;
    }
    if (angle < -MAX_ANGLE_L_SMALL)
    {
        angle = -MAX_ANGLE_L_SMALL;
    }
    int duty = (int)(PWM_STEER_MIDDLE_L_SMALL + (angle / MAX_ANGLE_L_SMALL) * (PWM_STEER_MAX_L_SMALL - PWM_STEER_MIDDLE_L_SMALL));

    // 限制舵机PWM范围
    if (duty < PWM_STEER_MIN_L_SMALL)
    {
        duty = PWM_STEER_MIN_L_SMALL;
    }
    if (duty > PWM_STEER_MAX_L_SMALL)
    {
        duty = PWM_STEER_MAX_L_SMALL;
    }
    Steer_set_duty(duty);
}

void Steer_angle(float angle)
{
    float error;
    float current_yaw = yaw;
    
    // 计算角度差
    error = current_yaw - angle;
    
    // 将角度差规范化到 -180 到 180 度
    while(error > 180.0f) error -= 360.0f;
    while(error < -180.0f) error += 360.0f;
    
    // 限制舵机打角范围
    if(error > MAX_ANGLE_L_SMALL)
        error = MAX_ANGLE_L_SMALL;
    if(error < -MAX_ANGLE_L_SMALL)
        error = -MAX_ANGLE_L_SMALL;
        
    // 设置舵机角度
    Steer_set_angle(-error);
}
