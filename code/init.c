#include "zf_common_headfile.h"
#include "flash.h"
#include "encoder.h"
#include "imu.h"
#include "menu.h"
#include "motor.h"
#include "steer.h"
#include "ipsShow.h"
#include "pid.h"
#include "uartReceiver.h"
#include "gps.h"
#include "control.h"
#include "ins.h"
#include "mode.h"
#include "camera.h"
#include "hall.h"
#include "bldc.h"

void Init(void)
{
    IPS_Init();                                 // 初始化 1.14 寸 IPS 液晶屏幕显示
    Button_init();                              // 初始化按键
    Encoder_init();                             // 初始化编码器
    Motor_init();                               // 初始化电机
    Steer_init();                               // 初始化舵机
    Basic_Data_Init();                          // 初始化基础数据
    GPS_Points_Init();                          // 初始化 GPS 点位
    INS_Points_Init();                          // 初始化 INS 点位
    WGS84_to_ENU_Init();                        // 初始化 WGS84 坐标转 ENU 坐标
    S_Point_Init();                             // 初始化 S 型走位点
    Imu_init();                                 // 初始化 IMU963RA
    Gps_init();                                 // 初始化 GPS
    //PID_init(&pid_speed, 50.0f, 5.0f, 0.0f);       // 初始化 PID 控制器
    PID_init(&pid_speed, 10.0f, 0.0f, 0.0f);       // 初始化 PID 控制器
    PID_init(&pid_steer, 1.0f, 0.0f, 0.3f);     // 初始化 PID 控制器
    UartReceiver_init();                        // 初始化串口接收机
    INS_Init();                                 // 初始化惯导系统
    Camera_Init();                              // 初始化摄像头
    //hall_init();                                // 初始化霍尔值
}
