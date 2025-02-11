#include "isr_config.h"
#include "zf_common_headfile.h"

#define PIT0                            (CCU60_CH0 )                            // 使用的周期中断编号

#define ENCODER_DIR                     (TIM6_ENCODER)                          // 带方向编码器对应使用的编码器接口
#define ENCODER_DIR_PULSE               (TIM6_ENCODER_CH1_P20_3)                // PULSE 对应的引脚
#define ENCODER_DIR_DIR                 (TIM6_ENCODER_CH2_P20_0)                // DIR 对应的引脚
#define ENCODER_PULSE_NUM				1024									// 编码器一圈的脉冲数
#define WHEEL_PERIMETER					22.61947f								// 轮子周长，单位cm
#define GEAR_RATIO						0.245455f								// 齿轮传动比
#define SAMPLE_TIME						0.01f									// 采样时间

int16 encoder_data_dir = 0;
float speed = 0.0f;

void Encoder_init (void)
{
    encoder_dir_init(ENCODER_DIR, ENCODER_DIR_PULSE, ENCODER_DIR_DIR);
    pit_ms_init(PIT0, 10);                                                      // 初始化 PIT0 为周期中断 100ms 周
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
    static float filtered_speed = 0;
    speed = (float)encoder_data_dir / ENCODER_PULSE_NUM * GEAR_RATIO * WHEEL_PERIMETER / SAMPLE_TIME / 100.0f;
    //速度 = 脉冲数                  / 每圈脉冲数         * 传动比      * 轮周长          / 采样时间    / 100
    filtered_speed = 0.8f * filtered_speed + 0.2f * speed;  // 一阶低通滤波
    speed = filtered_speed;
}
