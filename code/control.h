#ifndef _control_h_
#define _control_h_

extern float target_speed;
extern float target_angle;

extern float GPS_ENU[MAX_GPS_POINTS][2];
extern float S_Point[MAX_INS_POINTS][2];

extern uint8_t Start_GPS_Point;
extern uint8_t End_GPS_Point;
extern uint8_t NOW_GPS_Point;

extern uint8_t Start_INS_Point;
extern uint8_t End_INS_Point;
extern uint8_t NOW_INS_Point;

extern uint8_t Start_S_Point;
extern uint8_t End_S_Point;
extern uint8_t NOW_S_Point;

extern uint8_t GPS_TO_INS_POINT;

void WGS84_to_ENU_Init(void);
void WGS84_to_ENU(double lat, double lon, float* east, float* north);
void S_Point_Init(void);

void GPS_Navigation(void);
void GPS_ENU_Navigation(void);
void INS_Navigation(void);
void GPS_INS_Navigation(void);
void GPS_ENU_INS_Navigation(void);

#endif
