#ifndef _encoder_h_
#define _encoder_h_

#define ENCODER_DIR                     (TIM6_ENCODER)                         // 带方向编码器对应使用的编码器接口
#define ENCODER_DIR_PULSE               (TIM6_ENCODER_CH1_P20_3)               // PULSE 对应的引脚
#define ENCODER_DIR_DIR                 (TIM6_ENCODER_CH2_P20_0)               // DIR 对应的引脚

extern int16 encoder_data_dir;
extern float speed;
extern uint16_t hall_count; // 霍尔计数
extern uint16_t countttt; // 霍尔计数
extern float rpm; // 转速
extern float BLDC_speed; // BLDC 电机速度

void Encoder_init(void);
void Encoder_get_speed(void);
void BLDC_get_speed(void);

#endif
