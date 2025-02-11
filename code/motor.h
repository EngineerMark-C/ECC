#ifndef _motor_h_
#define _motor_h_

#define PWM1                    (ATOM0_CH4_P02_4)
#define PWM2                    (ATOM0_CH5_P02_5)
#define DUTY_MAX                (8000)

extern int16_t duty1;
extern int16_t duty2;

void Motor_init(void);
void Motor_set_duty(int duty1, int duty2);

#endif