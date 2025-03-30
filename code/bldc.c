#include "zf_common_headfile.h"
#include "init.h"

#define          PIT3               (CCU61_CH1 )                            // 使用的周期中断编号
#define          freq               20000

uint8_t control_hall[6]= {6, 2, 3, 1, 5, 4};        //霍尔时序
static int32_t speed_val = 0;
uint8_t BLDC_Dir;   //   0:正转  1:反转

// 位置 | ha | hb | hc | hall_value_now (ha + hb*2 + hc*4)
// 1    | 1  | 0  | 0  → 1    AH BL
// 2    | 1  | 1  | 0  → 3    AH CL
// 3    | 0  | 1  | 0  → 2    BH CL
// 4    | 0  | 1  | 1  → 6    BH AL
// 5    | 0  | 0  | 1  → 4    CH AL
// 6    | 1  | 0  | 1  → 5    CH BL

void BLDC_Init(void)
{
    pwm_init(ATOM3_CH2_P33_6, freq, 0);             // A相
    pwm_init(ATOM3_CH1_P33_5, freq, 0);             // B相
    pwm_init(ATOM3_CH0_P33_4, freq, 0);             // C相
    pit_init(PIT3, 500);                              // 初始化 PIT3 为周期中断 10ms
}

void BLDC_Set_duty(int32_t duty)
{
    speed_val = duty; // 保存速度值用于中断换向
}

void BLDC_Update(void)
{
    if (speed_val > 0) // 正转
    {
        switch (hall_value_now) 
        {
            case 1: pwm_set_duty(ATOM3_CH2_P33_6, speed_val); pwm_set_duty(ATOM3_CH1_P33_5, 0); pwm_set_duty(ATOM3_CH0_P33_4, 0); break; // AH BL
            case 3: pwm_set_duty(ATOM3_CH2_P33_6, speed_val); pwm_set_duty(ATOM3_CH1_P33_5, 0); pwm_set_duty(ATOM3_CH0_P33_4, 0); break; // AH CL
            case 2: pwm_set_duty(ATOM3_CH2_P33_6, 0); pwm_set_duty(ATOM3_CH1_P33_5, speed_val); pwm_set_duty(ATOM3_CH0_P33_4, 0); break; // BH CL
            case 6: pwm_set_duty(ATOM3_CH2_P33_6, 0); pwm_set_duty(ATOM3_CH1_P33_5, speed_val); pwm_set_duty(ATOM3_CH0_P33_4, 0); break; // BH AL
            case 4: pwm_set_duty(ATOM3_CH2_P33_6, 0); pwm_set_duty(ATOM3_CH1_P33_5, 0); pwm_set_duty(ATOM3_CH0_P33_4, speed_val); break; // CH AL
            case 5: pwm_set_duty(ATOM3_CH2_P33_6, 0); pwm_set_duty(ATOM3_CH1_P33_5, 0); pwm_set_duty(ATOM3_CH0_P33_4, speed_val); break; // CH BL
            default: pwm_set_duty(ATOM3_CH2_P33_6, 0); pwm_set_duty(ATOM3_CH1_P33_5, 0); pwm_set_duty(ATOM3_CH0_P33_4, 0); break; // 关闭所有相
        }
    }
    else if (speed_val < 0) // 反转
    {
        int32_t abs_speed = -speed_val; // 取绝对值
        switch (hall_value_now) 
        {
            case 1: pwm_set_duty(ATOM3_CH2_P33_6, 0); pwm_set_duty(ATOM3_CH1_P33_5, abs_speed); pwm_set_duty(ATOM3_CH0_P33_4, 0); break; // BH CL
            case 3: pwm_set_duty(ATOM3_CH2_P33_6, 0); pwm_set_duty(ATOM3_CH1_P33_5, abs_speed); pwm_set_duty(ATOM3_CH0_P33_4, 0); break; // BH AL
            case 2: pwm_set_duty(ATOM3_CH2_P33_6, 0); pwm_set_duty(ATOM3_CH1_P33_5, 0); pwm_set_duty(ATOM3_CH0_P33_4, abs_speed); break; // CH AL
            case 6: pwm_set_duty(ATOM3_CH2_P33_6, 0); pwm_set_duty(ATOM3_CH1_P33_5, 0); pwm_set_duty(ATOM3_CH0_P33_4, abs_speed); break; // CH BL
            case 4: pwm_set_duty(ATOM3_CH2_P33_6, abs_speed); pwm_set_duty(ATOM3_CH1_P33_5, 0); pwm_set_duty(ATOM3_CH0_P33_4, 0); break; // AH BL
            case 5: pwm_set_duty(ATOM3_CH2_P33_6, abs_speed); pwm_set_duty(ATOM3_CH1_P33_5, 0); pwm_set_duty(ATOM3_CH0_P33_4, 0); break; // AH CL
            default: pwm_set_duty(ATOM3_CH2_P33_6, 0); pwm_set_duty(ATOM3_CH1_P33_5, 0); pwm_set_duty(ATOM3_CH0_P33_4, 0); break; // 关闭所有相
        }
    }
    else // speed_val == 0，电机停止
    {
        pwm_set_duty(ATOM3_CH2_P33_6, 0); 
        pwm_set_duty(ATOM3_CH1_P33_5, 0); 
        pwm_set_duty(ATOM3_CH0_P33_4, 0);
    }
}

void BLDC_Dir_Judge(void)
{
    switch (hall_value_now) 
    {
        case 1:
        {
            if      (last_hall == 5) BLDC_Dir = 0; // 正转
            else if (last_hall == 3) BLDC_Dir = 1; // 反转
            break;
        }
        case 2:
        {
            if      (last_hall == 3) BLDC_Dir = 0; // 正转
            else if (last_hall == 6) BLDC_Dir = 1; // 反转
            break;
        }
        case 3:
        {
            if      (last_hall == 1) BLDC_Dir = 0; // 正转
            else if (last_hall == 2) BLDC_Dir = 1; // 反转
            break;
        }
        case 4:
        {
            if      (last_hall == 6) BLDC_Dir = 0; // 正转
            else if (last_hall == 5) BLDC_Dir = 1; // 反转
            break;
        }
        case 5:
        {
            if      (last_hall == 4) BLDC_Dir = 0; // 正转
            else if (last_hall == 1) BLDC_Dir = 1; // 反转
            break;
        }
        case 6:
        {
            if      (last_hall == 2) BLDC_Dir = 0; // 正转
            else if (last_hall == 4) BLDC_Dir = 1; // 反转
            break;
        }
    }
}