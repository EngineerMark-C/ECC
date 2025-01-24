#include "zf_common_headfile.h"

struct PID
{
    float kp;
    float ki;
    float kd;
    float target;
    float current;
    float error;
    float error_last;
    float integral;
    float derivative;
    int output;
};

void PID_init(struct PID *pid, float kp, float ki, float kd, float target)
{
    pid->kp = kp;
    pid->ki = ki;
    pid->kd = kd;
    pid->target = target;
    pid->current = 0;
    pid->error = 0;
    pid->error_last = 0;
    pid->integral = 0;
    pid->derivative = 0;
    pid->output = 0;
}

int PID_calc(struct PID *pid, float current)
{
    pid->current = current;
    pid->error = pid->target - pid->current;
    pid->integral += pid->error;
    pid->derivative = pid->error - pid->error_last;
    pid->output = pid->kp * pid->error + pid->ki * pid->integral + pid->kd * pid->derivative;
    pid->error_last = pid->error;
    return pid->output;
}
