#include "zf_common_headfile.h"
#include "init.h"

struct PID pid;
int output = 0;

void PID_init(struct PID *pid, float kp, float ki, float kd)
{
    pid->kp = kp;
    pid->ki = ki;
    pid->kd = kd;
    pid->target = 0;
    pid->current = 0;
    pid->error = 0;
    pid->error_last = 0;
    pid->integral = 0;
    pid->derivative = 0;
    pid->output = 0;
}

// 位置式 PID
void PID_calc(struct PID *pid, float current)
{
    pid->current = current;
    pid->error = pid->target - pid->current;                    // 计算当前误差
    
    pid->integral += pid->error;                               // 累积误差积分
    pid->derivative = pid->error - pid->error_last;            // 计算误差微分
    
    // 积分限幅，防止积分饱和
    if(pid->integral > 10000) pid->integral = 10000;
    if(pid->integral < -10000) pid->integral = -10000;
    
    // 计算PID输出
    pid->output = pid->kp * pid->error + 
                 pid->ki * pid->integral + 
                 pid->kd * pid->derivative;
    
    // 输出限幅
    if(pid->output > 5000) pid->output = 5000;
    if(pid->output < -5000) pid->output = -5000;
    
    pid->error_last = pid->error;                              // 保存上次误差
}

//// 增量式 PID
//int PID_calc(struct PID *pid, float current)
//{
//    pid->current = current;
//    pid->error = pid->target - pid->current;
//    pid->output = pid->kp * (pid->error - pid->error_last) + pid->ki * pid->error + pid->kd * (pid->error - 2 * pid->error_last + pid->derivative);
//    pid->error_last = pid->error;
//    pid->derivative = pid->error;
//}

void PID_OK(float target)
{
    pid.target = target;                    // 设置目标值
    PID_calc(&pid, speed);                  // 使用当前速度作为反馈值
    output += (int)pid.output;               // 将PID输出转换为占空比
    
    // 电机控制
    if(output >= 0)
    {
        Motor_set_duty(0, output);          // 正转
    }
    else
    {
        Motor_set_duty(-output, 0);         // 反转
    }
}
