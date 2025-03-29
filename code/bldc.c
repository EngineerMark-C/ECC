#include "zf_common_headfile.h"
#include "init.h"

#define          PIT3               (CCU61_CH1 )                            // 使用的周期中断编号
#define          freq               20000

uint8_t control_hall[6]= {6, 2, 3, 1, 5, 4};        //霍尔时序
static uint32_t speed_val = 0;

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

void BLDC_Set_Speed(uint32 speed)
{
    speed_val = speed; // 保存速度值用于中断换向
}

void BLDC_Update(void)
{
    switch (hall_value_now) {
        case 1: pwm_set_duty(ATOM3_CH2_P33_6, speed_val); pwm_set_duty(ATOM3_CH1_P33_5, 0); pwm_set_duty(ATOM3_CH0_P33_4, 0); break; // AH BL
        case 3: pwm_set_duty(ATOM3_CH2_P33_6, speed_val); pwm_set_duty(ATOM3_CH1_P33_5, 0); pwm_set_duty(ATOM3_CH0_P33_4, 0); break; // AH CL
        case 2: pwm_set_duty(ATOM3_CH2_P33_6, 0); pwm_set_duty(ATOM3_CH1_P33_5, speed_val); pwm_set_duty(ATOM3_CH0_P33_4, 0); break; // BH CL
        case 6: pwm_set_duty(ATOM3_CH2_P33_6, 0); pwm_set_duty(ATOM3_CH1_P33_5, speed_val); pwm_set_duty(ATOM3_CH0_P33_4, 0); break; // BH AL
        case 4: pwm_set_duty(ATOM3_CH2_P33_6, 0); pwm_set_duty(ATOM3_CH1_P33_5, 0); pwm_set_duty(ATOM3_CH0_P33_4, speed_val); break; // CH AL
        case 5: pwm_set_duty(ATOM3_CH2_P33_6, 0); pwm_set_duty(ATOM3_CH1_P33_5, 0); pwm_set_duty(ATOM3_CH0_P33_4, speed_val); break; // CH BL
        default: pwm_set_duty(ATOM3_CH2_P33_6, 0); pwm_set_duty(ATOM3_CH1_P33_5, 0); pwm_set_duty(ATOM3_CH0_P33_4, 0); break; // 关闭所有相
    }
}
