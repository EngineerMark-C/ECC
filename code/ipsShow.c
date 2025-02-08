#include "zf_common_headfile.h"
#include "init.h"

void Ips_init(void)
{
    ips114_init();
    ips114_clear();
    ips114_set_color(RGB565_BLACK, RGB565_WHITE);
    system_delay_ms(200);  // 等待屏幕稳定
}

void Speed_Imu_Info(void)
{
    // 第一列：速度相关信息
    ips114_show_string(0, 0, "Speed:");
    ips114_show_float(60, 0, pid_speed.target, 5, 2);     // 目标值
    ips114_show_float(60, 16, speed, 5, 2);               // 当前速度
    ips114_show_float(60, 32, pid_speed.error, 5, 2);     // 误差
    ips114_show_float(60, 48, pid_speed.integral, 5, 2);  // 积分项
    ips114_show_int(60, 64, output_speed, 5);             // 输出值

    // 第二列：IMU姿态信息
    ips114_show_string(0, 80, "IMU:");
    ips114_show_string(0, 96, "P:");
    ips114_show_float(20, 96, pitch, 6, 2);               // pitch
    ips114_show_string(90, 96, "R:");
    ips114_show_float(110, 96, roll, 6, 2);              // roll
    ips114_show_string(0, 112, "Y:");
    ips114_show_float(20, 112, yaw, 6, 2);               // yaw
    ips114_show_string(90, 112, "YM:");
    ips114_show_float(110, 112, yaw_mag, 6, 2);          // yaw_mag

    system_delay_ms(10);  // 短暂延时确保显示稳定
}
