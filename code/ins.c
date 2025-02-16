#include "zf_common_headfile.h"
#include "init.h"

#define SAMPLE_TIME                 0.005f                 // 5ms采样周期

// 状态变量
float position[2] = {0};   // 东北天坐标系位置 (x,y)

// 初始化惯导系统
void INS_Init(void)
{
    memset(position, 0, sizeof(position));
}

// 速度位置更新
void Update_Position(void)
{
    // 将角度转换为弧度
    float yaw_radian = yaw * 0.0174533f;  
    
    // 使用偏航角进行航位推算
    float cos_yaw = cos(yaw_radian);
    float sin_yaw = sin(yaw_radian);
    
    // 速度积分得到位置
    position[0] += speed * cos_yaw * SAMPLE_TIME;
    position[1] += speed * sin_yaw * SAMPLE_TIME;
}
