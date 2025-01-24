#include "zf_common_headfile.h"

void Imu_init(void)
{
    imu963ra_init();                // 初始化 IMU963RA
}

void Imu_get_data(void)
{
    imu963ra_get_gyro();            // 获取 IMU963RA 陀螺仪数据
    imu963ra_get_acc();             // 获取 IMU963RA 加速度计数据
}