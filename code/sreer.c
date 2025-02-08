#include "zf_common_headfile.h"
#include "init.h"

#define SREER                   (ATOM1_CH1_P33_9)

#define PWM_STEER_MIN_L_SMALL					1005                                            // L-Small车舵机PWM右极限
#define PWM_STEER_MIDDLE_L_SMALL				1130                                            // L-Small车舵机PWM中值
#define PWM_STEER_MAX_L_SMALL					1250                                            // L-Small车舵机PWM左极限
#define MAX_ANGLE_L_SMALL						22.0f                                           // L-Small车舵机最大转角

int duty_sreer = 0;

void Sreer_init(void)
{
    pwm_init(SREER, 50, PWM_STEER_MIDDLE_L_SMALL);
}

void Sreer_set_duty(int duty)
{
    if (duty < PWM_STEER_MIN_L_SMALL)
    {
        duty = PWM_STEER_MIN_L_SMALL;
    }
    if (duty > PWM_STEER_MAX_L_SMALL)
    {
        duty = PWM_STEER_MAX_L_SMALL;
    }
    pwm_set_duty(SREER, duty);
}

void Sreer_set_angle(float angle)
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
    Sreer_set_duty(duty);
}

void Sreer_angle(float angle)
{
    int angleYaw;
    if (yaw > 180)
    {
        angleYaw = yaw - 360;
    }
    else
    {
        angleYaw = yaw;
    }
    angle = angleYaw- angle;
    if (angleYaw - angle >MAX_ANGLE_L_SMALL)
    {
        angle = MAX_ANGLE_L_SMALL;
    }
    if (angleYaw - angle < -MAX_ANGLE_L_SMALL)
    {
        angle = MAX_ANGLE_L_SMALL;
    }
    angle = -angle;
    Sreer_set_angle(angle);
}
