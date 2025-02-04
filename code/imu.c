#include "zf_common_headfile.h"

// 使用 Infineon 的 iLLD 库中的 STM 头文件
#include "IfxStm.h"
#include "IfxStm_reg.h"

#define PIT1                            (CCU60_CH1 )                            // 使用的周期中断编号

// 定义四元数和欧拉角变量
static float q0 = 1.0f, q1 = 0.0f, q2 = 0.0f, q3 = 0.0f;     // 四元数
float pitch = 0.0f, roll = 0.0f, yaw = 0.0f;                 // 欧拉角
float yaw_mag = 0.0f;                                        // 磁力计偏航角

// 添加时间测量变量
// uint32 quaternion_time = 0;      // 四元数解算时间
// uint32 mag_yaw_time = 0;         // 磁力计解算时间

void Imu_init(void)
{
    imu963ra_init();                // 初始化 IMU963RA
    pit_ms_init(PIT1, 5);           // 初始化 PIT1 为周期中断 5ms 周期
}

// 获取 IMU963RA 数据
void Imu_get_data(void)
{
    imu963ra_get_gyro();            // 获取 IMU963RA 陀螺仪数据
    imu963ra_get_acc();             // 获取 IMU963RA 加速度计数据
    imu963ra_get_mag();             // 获取 IMU963RA 磁力计数据
}

//四元素解算
void Imu_get_quaternion(void)
{
    // uint32 start_time = IfxStm_getLower(IfxStm_getAddress(IfxStm_Index_0));   // 使用 iLLD 的 API
    
    float norm;
    float ax, ay, az;
    float gx, gy, gz;
    float vx, vy, vz;
    float ex, ey, ez;
    static float q0q0, q0q1, q0q2, q0q3, q1q1, q1q2, q1q3, q2q2, q2q3, q3q3;
    static float dt = 0.005f;    // 采样周期 5ms
    static float Kp = 2.0f;      // 比例增益
    static float Ki = 0.001f;    // 积分增益
    static float exInt = 0.0f, eyInt = 0.0f, ezInt = 0.0f;   // 误差积分
    
    // 获取加速度计和陀螺仪数据并转换为实际物理值
    ax = imu963ra_acc_transition(imu963ra_acc_x);
    ay = imu963ra_acc_transition(imu963ra_acc_y);
    az = imu963ra_acc_transition(imu963ra_acc_z);
    gx = imu963ra_gyro_transition(imu963ra_gyro_x) * 0.0174533f; // 角度转弧度
    gy = imu963ra_gyro_transition(imu963ra_gyro_y) * 0.0174533f;
    gz = imu963ra_gyro_transition(imu963ra_gyro_z) * 0.0174533f;
    
    // 加速度计数据归一化
    norm = sqrt(ax * ax + ay * ay + az * az);
    ax = ax / norm;
    ay = ay / norm;
    az = az / norm;
    
    // 估计重力方向和方向误差
    q0q0 = q0 * q0;
    q0q1 = q0 * q1;
    q0q2 = q0 * q2;
    q0q3 = q0 * q3;
    q1q1 = q1 * q1;
    q1q2 = q1 * q2;
    q1q3 = q1 * q3;
    q2q2 = q2 * q2;
    q2q3 = q2 * q3;
    q3q3 = q3 * q3;
    
    // 根据当前姿态计算重力方向
    vx = 2 * (q1q3 - q0q2);
    vy = 2 * (q0q1 + q2q3);
    vz = q0q0 - q1q1 - q2q2 + q3q3;
    
    // 计算误差
    ex = (ay * vz - az * vy);
    ey = (az * vx - ax * vz);
    ez = (ax * vy - ay * vx);
    
    // 对误差进行积分
    exInt += ex * Ki * dt;
    eyInt += ey * Ki * dt;
    ezInt += ez * Ki * dt;
    
    // 补偿陀螺仪数据
    gx = gx + Kp * ex + exInt;
    gy = gy + Kp * ey + eyInt;
    gz = gz + Kp * ez + ezInt;
    
    // 四元数微分方程
    q0 = q0 + (-q1 * gx - q2 * gy - q3 * gz) * dt * 0.5f;
    q1 = q1 + (q0 * gx + q2 * gz - q3 * gy) * dt * 0.5f;
    q2 = q2 + (q0 * gy - q1 * gz + q3 * gx) * dt * 0.5f;
    q3 = q3 + (q0 * gz + q1 * gy - q2 * gx) * dt * 0.5f;
    
    // 四元数归一化
    norm = sqrt(q0 * q0 + q1 * q1 + q2 * q2 + q3 * q3);
    q0 = q0 / norm;
    q1 = q1 / norm;
    q2 = q2 / norm;
    q3 = q3 / norm;
    
    // 计算欧拉角（弧度）
    pitch = asin(2 * (q0 * q2 - q1 * q3));
    roll = atan2(2 * (q0 * q1 + q2 * q3), 1 - 2 * (q1 * q1 + q2 * q2));
    yaw = atan2(2 * (q0 * q3 + q1 * q2), 1 - 2 * (q2 * q2 + q3 * q3));
    
    // 转换为角度
    pitch *= 57.3f;  // 弧度转角度
    roll *= 57.3f;
    yaw *= 57.3f;
    
    // 将yaw从-180~180转换为0~360
    if (yaw < 0)
    {
        yaw += 360.0f;
    }
    
    // uint32 end_time = IfxStm_getLower(IfxStm_getAddress(IfxStm_Index_0));     // 使用 iLLD 的 API
    // quaternion_time = end_time - start_time;
}

void Imu_get_mag_yaw(void)
{
    // uint32 start_time = IfxStm_getLower(IfxStm_getAddress(IfxStm_Index_0));   // 使用 iLLD 的 API
    
    // 1. 获取磁力计数据并转换为物理值
    float mx = imu963ra_mag_transition(imu963ra_mag_x);
    float my = imu963ra_mag_transition(imu963ra_mag_y);
    float mz = imu963ra_mag_transition(imu963ra_mag_z);
    
    // 2. 倾角补偿
    float cos_roll = cos(roll * 0.0174533f);  // 度转弧度
    float sin_roll = sin(roll * 0.0174533f);
    float cos_pitch = cos(pitch * 0.0174533f);
    float sin_pitch = sin(pitch * 0.0174533f);
    
    // 补偿后的磁力计数据
    float mx_comp = mx * cos_pitch + my * sin_roll * sin_pitch + mz * cos_roll * sin_pitch;
    float my_comp = my * cos_roll - mz * sin_roll;
    
    // 3. 计算偏航角
    yaw_mag = atan2(-my_comp, mx_comp) * 57.3f;  // 弧度转度
    
    // 4. 转换为0-360度
    if(yaw_mag < 0) 
    {
        yaw_mag += 360.0f;
    }
    
    // uint32 end_time = IfxStm_getLower(IfxStm_getAddress(IfxStm_Index_0));     // 使用 iLLD 的 API
    // mag_yaw_time = end_time - start_time;
}

// 添加一个函数用于打印执行时间
void Print_imu_time(void)
{
    // STM时钟频率为100MHz时的时间换算（单位：微秒）
    float quaternion_us = (float)quaternion_time / 100.0f;
    float mag_yaw_us = (float)mag_yaw_time / 100.0f;
    
    printf("四元数解算时间: %.2f us\n", quaternion_us);
    printf("磁力计解算时间: %.2f us\n", mag_yaw_us);
}
