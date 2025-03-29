#include "isr_config.h"
#include "zf_common_headfile.h"

#define PIT0                            (CCU60_CH0 )                            // 使用的周期中断编号

#define ENCODER_DIR                     (TIM6_ENCODER)                          // 带方向编码器对应使用的编码器接口
#define ENCODER_DIR_PULSE               (TIM6_ENCODER_CH1_P20_3)                // PULSE 对应的引脚
#define ENCODER_DIR_DIR                 (TIM6_ENCODER_CH2_P20_0)                // DIR 对应的引脚
#define ENCODER_PULSE_NUM				1024									// 编码器一圈的脉冲数
#define WHEEL_PERIMETER					22.61947f								// 轮子周长，单位cm
#define GEAR_RATIO						0.245455f								// 齿轮传动比
#define SAMPLE_TIME						0.1f									// 采样时间

int16 encoder_data_dir = 0;
float speed = 0.0f;
uint16_t hall_count = 0; // 霍尔计数
uint16_t countttt = 0; // 霍尔计数
float rpm = 0.0f; // 转速
float BLDC_speed = 0.0f; // BLDC 电机速度


void Encoder_init (void)
{
    encoder_dir_init(ENCODER_DIR, ENCODER_DIR_PULSE, ENCODER_DIR_DIR);
    pit_ms_init(PIT0, 100);                                                      // 初始化 PIT0 为周期中断 10ms
}

void Encoder_get_speed(void)
{
    // 速度计算公式：
    // encoder_data_dir：10ms内的脉冲数
    // ENCODER_PULSE_NUM：每圈的脉冲数
    // GEAR_RATIO：齿轮传动比
    // WHEEL_PERIMETER：轮周长(cm)
    // SAMPLE_TIME：采样时间(s)
    // /100：将cm转换为m
    
    // printf("encoder_data_dir: %d\n", encoder_data_dir);
    // static float filtered_speed = 0;
    speed = (float)encoder_data_dir / ENCODER_PULSE_NUM * GEAR_RATIO * WHEEL_PERIMETER / SAMPLE_TIME / 100.0f;
    //速度 = 脉冲数                  / 每圈脉冲数         * 传动比      * 轮周长          / 采样时间    / 100
    // filtered_speed = 0.8f * filtered_speed + 0.2f * speed;  // 一阶低通滤波
    // speed = filtered_speed;
}

void BLDC_get_speed(void)
{
    countttt = hall_count; // 霍尔计数
    hall_count = 0; // 清零霍尔计数
    // rpm = 计数 / 6
    rpm = (float)countttt / 6 ;
    // 转速 =    rpm *  传动比      * 轮周长         / 采样时间      / 100.0f
    BLDC_speed = rpm *  GEAR_RATIO * WHEEL_PERIMETER / SAMPLE_TIME / 100.0f;
}
