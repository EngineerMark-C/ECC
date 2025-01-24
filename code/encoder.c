#include "isr_config.h"
#include "zf_common_headfile.h"

#define PIT0                            (CCU60_CH0 )                            // 使用的周期中断编号

#define ENCODER_DIR                     (TIM6_ENCODER)                         // 带方向编码器对应使用的编码器接口
#define ENCODER_DIR_PULSE               (TIM6_ENCODER_CH1_P20_3)               // PULSE 对应的引脚
#define ENCODER_DIR_DIR                 (TIM6_ENCODER_CH2_P20_0)               // DIR 对应的引脚
#define ENCODER_PULSE_NUM				1024									// 编码器一圈的脉冲数
#define WHEEL_PERIMETER					22.61947f								// 轮子周长，单位cm
#define GEAR_RATIO						0.245455f								// 齿轮传动比

int16 encoder_data_dir = 0;
float speed = 0.0f;

void Encoder_init (void)
{
    encoder_dir_init(ENCODER_DIR, ENCODER_DIR_PULSE, ENCODER_DIR_DIR);
    pit_ms_init(PIT0, 100);                                                     // 初始化 PIT0 为周期中断 100ms 周
}

void Encoder_get_speed(void)
{
    speed = encoder_data_dir / ENCODER_PULSE_NUM * GEAR_RATIO * WHEEL_PERIMETER / 0.1f / 100;  // 单位 m/s
}
