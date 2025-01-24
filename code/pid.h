#ifndef _pid_h_
#define _pid_h_

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
    float output;
};

void PID_init(PID *pid, float kp, float ki, float kd, float target, float current);
int PID_calc(PID *pid, float current);

#endif