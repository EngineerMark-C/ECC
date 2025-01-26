#include "zf_common_headfile.h"
#include "encoder.h"
#include "imu.h"
#include "button.h"
#include "motor.h"
#include "sreer.h"
#include "ipsShow.h"


void Init(void)
{
    ips114_init();                  // 初始化 1.14 寸 IPS 液晶屏幕按键
    Encoder_init();              // 初始化编码器
    Imu_init();                     // 初始化 IMU963RA
    Button_init();                  // 初始化按键
    Motor_init();                   // 初始化电机
    Sreer_init();                   // 初始化舵机
    Ips_init();                     // 初始化 1.14 寸 IPS 液晶屏幕显示
}
