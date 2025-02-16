#ifndef _control_h_
#define _control_h_

extern float target_speed;
extern float target_angle;

extern uint8_t Start_GPS_Point;
extern uint8_t End_GPS_Point;
extern uint8_t Start_INS_Point;
extern uint8_t End_INS_Point;

void GPS_One_By_One(void);
void INS_One_By_One(void);

#endif
