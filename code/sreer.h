#ifndef _sreer_h_
#define _sreer_h_

#define PWM_STEER_MIN_L_SMALL					655                                            // L-Small车舵机PWM右极限   其实是 R 车
#define PWM_STEER_MIDDLE_L_SMALL				765                                            // L-Small车舵机PWM中值
#define PWM_STEER_MAX_L_SMALL					885                                            // L-Small车舵机PWM左极限
#define MAX_ANGLE_L_SMALL						21.3f                                          // L-Small车舵机最大转角

void Sreer_init(void);
void Sreer_set_duty(int duty);

#endif