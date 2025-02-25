#include "zf_common_headfile.h"
#include "init.h"

// 使用 Infineon 的 iLLD 库中的 STM 头文件
#include "IfxStm.h"
#include "IfxStm_reg.h"

#define PIT1                            (CCU60_CH1 )                            // 使用的周期中断编号

// 定义四元数和欧拉角变量
static float q0 = 1.0f, q1 = 0.0f, q2 = 0.0f, q3 = 0.0f;     // 四元数
float pitch = 0.0f, roll = 0.0f, yaw = 0.0f;                 // 欧拉角
float yaw_mag = 0.0f;                                        // 磁力计偏航角

// 添加时间测量变量
// uint32 quaternion_time = 0;                               // 四元数解算时间
// uint32 mag_yaw_time = 0;                                  // 磁力计解算时间

// 添加卡尔曼滤波和陀螺仪偏置相关变量
static float P[3] = {1.0f, 1.0f, 1.0f};                      // 卡尔曼滤波误差协方差
static float Q = 0.001f;                                     // 过程噪声协方差
static float R = 0.03f;                                      // 测量噪声协方差
static float K[3];                                           // 卡尔曼增益

// 陀螺仪偏置校准函数
// void Calibrate_gyro(void)
// {
//     printf("开始陀螺仪校准，请保持IMU静止...\n");
//     const int samples = 1000;  // 采样次数
//     float sum_x = 0.0f, sum_y = 0.0f, sum_z = 0.0f;
    
//     // 采集静止状态下的陀螺仪数据
//     for(int i = 0; i < samples; i++)
//     {
//         imu963ra_get_gyro();
//         sum_x += imu963ra_gyro_transition(imu963ra_gyro_x);
//         sum_y += imu963ra_gyro_transition(imu963ra_gyro_y);
//         sum_z += imu963ra_gyro_transition(imu963ra_gyro_z);
//         system_delay_ms(5);  // 延时5ms
        
//         if(i % 100 == 0)  // 每100次采样打印一次进度
//         {
//             printf("校准进度：%d%%\n", i / 10);
//         }
//     }
    
//     // 计算平均值作为偏置
//     gyro_bias[0] = sum_x / samples;
//     gyro_bias[1] = sum_y / samples;
//     gyro_bias[2] = sum_z / samples;
    
//     printf("陀螺仪偏置值：\nX: %.2f\nY: %.2f\nZ: %.2f\n", 
//            gyro_bias[0], gyro_bias[1], gyro_bias[2]);
// }

// 陀螺仪偏置校准函数
void Calibrate_Gyro(void)
{
    ips114_show_string(60, 0, "Gyro Calibrating...");
    ips114_show_string(60, 16, "Keep IMU Still");
    
    const int samples = 1000;  // 采样次数
    float sum_x = 0.0f, sum_y = 0.0f, sum_z = 0.0f;
    char progress_str[20];
    
    // 采集静止状态下的陀螺仪数据
    for(int i = 0; i < samples; i++)
    {
        imu963ra_get_gyro();
        sum_x += imu963ra_gyro_transition(imu963ra_gyro_x);
        sum_y += imu963ra_gyro_transition(imu963ra_gyro_y);
        sum_z += imu963ra_gyro_transition(imu963ra_gyro_z);
        system_delay_ms(5);  // 5ms,与实际采样周期一致
        
        if(i % 100 == 0)  // 每100次采样更新一次进度
        {
            sprintf(progress_str, "Progress:%d%%", i / 10);
            ips114_show_string(60, 32, progress_str);
        }
    }
    
    // 计算平均值作为偏置
    gyro_bias[0] = sum_x / samples;
    gyro_bias[1] = sum_y / samples;
    gyro_bias[2] = sum_z / samples;
    
    // 显示校准结果
    ips114_show_string(60, 48, "Gyro Bias:");
    ips114_show_float(60, 64, gyro_bias[0], 6, 2);  // X
    ips114_show_float(60, 80, gyro_bias[1], 6, 2);  // Y
    ips114_show_float(60, 96, gyro_bias[2], 6, 2);  // Z
    ips114_show_string(60, 112, "Calibration Done!");
}

// 初始化 IMU963RA
// void Imu_init(void)
// {
//     uint8_t imu_init_state = imu963ra_init();
//     if(imu_init_state != 0)
//     {
//         printf("IMU初始化失败！错误代码：%d\n", imu_init_state);
//         while(1);  // 如果初始化失败则停止运行
//     }
//     printf("IMU初始化成功！\n");
    
//     pit_ms_init(PIT1, 5);           // 初始化PIT1为周期中断5ms周期
//     Calibrate_gyro();              // 校准陀螺仪偏置
//     printf("陀螺仪校准完成！\n");
// }

// 初始化 IMU963RA
void Imu_init(void)
{
    imu963ra_init();
    pit_ms_init(PIT1, 5);   // 初始化PIT1为周期中断5ms周期
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
    
    // 获取陀螺仪数据并应用卡尔曼滤波
    float gx_raw = imu963ra_gyro_transition(imu963ra_gyro_x);
    float gy_raw = imu963ra_gyro_transition(imu963ra_gyro_y);
    float gz_raw = imu963ra_gyro_transition(imu963ra_gyro_z);
    
    // 卡尔曼滤波更新
    for(int i = 0; i < 3; i++)
    {
        float gyro_raw = (i == 0) ? gx_raw : ((i == 1) ? gy_raw : gz_raw);
        
        // 预测
        P[i] = P[i] + Q;
        
        // 更新
        K[i] = P[i] / (P[i] + R);
        float gyro_filtered = gyro_raw - gyro_bias[i];
        gyro_bias[i] = gyro_bias[i] + K[i] * (gyro_raw - gyro_filtered - gyro_bias[i]);
        P[i] = (1 - K[i]) * P[i];
        
        // 更新滤波后的陀螺仪数据
        if(i == 0) gx = (gyro_filtered) * 0.0174533f;
        else if(i == 1) gy = (gyro_filtered) * 0.0174533f;
        else gz = (gyro_filtered) * 0.0174533f;
    }
    
    // 加速度计数据归一化
    // 计算 norm 并检查是否接近零
    norm = sqrt(ax * ax + ay * ay + az * az);
    if (norm > 1e-6f) {  // 避免除以零
        ax /= norm;
        ay /= norm;
        az /= norm;
    }
    
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
    
    // 计算四元数的 norm 并检查是否接近零
    norm = sqrt(q0 * q0 + q1 * q1 + q2 * q2 + q3 * q3);
    if (norm > 1e-6f) {  // 避免除以零
        q0 /= norm;
        q1 /= norm;
        q2 /= norm;
        q3 /= norm;
    } else {
        // 如果四元数崩溃，重置为单位四元数
        q0 = 1.0f;
        q1 = q2 = q3 = 0.0f;
    }
    
    // 计算欧拉角（弧度）
    pitch = asin(2 * (q0 * q2 - q1 * q3));
    roll = atan2(2 * (q0 * q1 + q2 * q3), 1 - 2 * (q1 * q1 + q2 * q2));
    yaw = -atan2(2 * (q0 * q3 + q1 * q2), 1 - 2 * (q2 * q2 + q3 * q3));
    
    // 转换为角度
    pitch *= 57.3f;  // 弧度转角度
    roll *= 57.3f;
    yaw *= 57.3f;
    
    // 将yaw从-180~180转换为0~360
    if (yaw < 0)
    {
        yaw += 360.0f;
    }
    else if (yaw >= 360.0f)  // 添加安全限制
    {
        yaw -= 360.0f;
    }
    
    // printf("%d, %d, %d, %d, %d, %d\n", imu963ra_acc_x, imu963ra_acc_y, imu963ra_acc_z, imu963ra_gyro_x, imu963ra_gyro_y, imu963ra_gyro_z);
    // printf("%.2f, %.2f, %.2f, %.2f, %.2f, %.2f\n", ax, ay, az, gx, gy, gz);
    
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
    // printf("%.2f, %.2f, %.2f, %.2f\n", mx, my, mz, yaw_mag);
    
    // uint32 end_time = IfxStm_getLower(IfxStm_getAddress(IfxStm_Index_0));     // 使用 iLLD 的 API
    // mag_yaw_time = end_time - start_time;
}

// 添加一个函数用于打印执行时间
//void Print_imu_time(void)
//{
//    // STM时钟频率为100MHz时的时间换算（单位：微秒）
//    float quaternion_us = (float)quaternion_time / 100.0f;
//    float mag_yaw_us = (float)mag_yaw_time / 100.0f;
//
//    printf("四元数解算时间: %.2f us\n", quaternion_us);
//    printf("磁力计解算时间: %.2f us\n", mag_yaw_us);
//}
