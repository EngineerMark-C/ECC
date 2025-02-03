#ifndef _pid_h_
#define _pid_h_

struct PID {
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

extern int output_speed;
extern struct PID pid_speed;

void PID_init(struct PID *pid, float kp, float ki, float kd);
void PID_calc(struct PID *pid, float current);
void PID_speed(float target);
#endif
