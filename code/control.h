#ifndef _control_h_
#define _control_h_

extern float target_speed;
extern float target_angle;

extern float GPS_ENU[MAX_GPS_POINTS][2];

extern uint8_t Start_GPS_Point;
extern uint8_t End_GPS_Point;
extern uint8_t Start_INS_Point;
extern uint8_t End_INS_Point;

void WGS84_to_ENU_Init(void);
void WGS84_to_ENU(double lat, double lon, float* east, float* north);

void GPS_One_By_One(void);
void INS_One_By_One(void);

#endif
