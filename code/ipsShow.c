#include "zf_common_headfile.h"
#include "init.h"

void Ips_init(void)
{
    ips114_init();
}

void Ips_show(void)
{
    ips114_show_int(0, 16, duty1, 5);                         // 显示按键状态
    ips114_show_int(0, 32, duty2, 5);                         // 显示按键状态
    // ips114_show_float(0, 16, imu963ra_gyro_transition(imu963ra_gyro_x), 5, 2); // 显示陀螺仪 X 轴数据
    // ips114_show_float(0, 32, imu963ra_gyro_transition(imu963ra_gyro_y), 5, 2); // 显示陀螺仪 Y 轴数据
    // ips114_show_float(0, 48, imu963ra_gyro_transition(imu963ra_gyro_z), 5, 2); // 显示陀螺仪 Z 轴数据
    // ips114_show_float(0, 64, imu963ra_acc_transition(imu963ra_acc_x), 5, 2);   // 显示加速度计 X 轴数据
    // ips114_show_float(0, 80, imu963ra_acc_transition(imu963ra_acc_y), 5, 2);   // 显示加速度计 Y 轴数据
    // ips114_show_float(0, 96, imu963ra_acc_transition(imu963ra_acc_z), 5, 2);   // 显示加速度计 Z 轴数据
}
