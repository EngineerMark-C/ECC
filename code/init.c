#include "zf_common_headfile.h"
#include "encoder.h"
#include "imu.h"
#include "menu.h"
#include "motor.h"
#include "sreer.h"
#include "ipsShow.h"
#include "pid.h"
#include "uartReceiver.h"
#include "gps.h"
#include "flash.h"
#include "control.h"


void Init(void)
{
    Encoder_init();                             // 初始化编码器
    Button_init();                              // 初始化按键
    Motor_init();                               // 初始化电机
    Sreer_init();                               // 初始化舵机
    IPS_Init();                                 // 初始化 1.14 寸 IPS 液晶屏幕显示
    Imu_init();                                 // 初始化 IMU963RA
    UartReceiver_init();                        // 初始化串口接收机
    Gps_init();                                 // 初始化 GPS
    PID_init(&pid_speed, 10.0, 0.0, 0.0);      // 初始化 PID 控制器
    PID_init(&pid_sreer, 1.0f, 0.0f, 0.3f);     // 初始化 PID 控制器
    GPS_Points_Init();                          // 初始化 GPS 点位
    GPS_Path_Init();                            // 初始化 GPS 路径
}
