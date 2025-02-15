#ifndef _steer_h_
#define _steer_h_

extern int duty_steer;

#define PWM_STEER_MIN_L_SMALL					1005                                            // L-Small车舵机PWM右极限
#define PWM_STEER_MIDDLE_L_SMALL				1130                                            // L-Small车舵机PWM中值
#define PWM_STEER_MAX_L_SMALL					1250                                            // L-Small车舵机PWM左极限
#define MAX_ANGLE_L_SMALL						22.0f                                           // L-Small车舵机最大转角

void Steer_init(void);
void Steer_set_duty(int duty);
void Steer_set_angle(float angle);
void Steer_angle(float angle);

#endif