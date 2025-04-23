#ifndef _control_h_
#define _control_h_

extern float target_speed;
extern float target_angle;

extern float SAFETY_X_MAX;
extern float SAFETY_X_MIN;
extern float SAFETY_Y_MAX;
extern float SAFETY_Y_MIN;

extern float MAX_SPEED;
extern float MIN_SPEED;
extern float APPROACH_SPEED;
extern float BRAKING_DISTANCE;

extern float GPS_ENU[MAX_GPS_POINTS][2];
extern float S_Point[MAX_INS_POINTS][2];

extern float S_Distance;

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

void Safety_Boundary_Check(void);
void Speed_Management(float distance);

void WGS84_to_ENU_Init(void);
void WGS84_to_ENU(double lat, double lon, float* east, float* north);
void S_Point_Init(void);

void GPS_Navigation(void);
void GPS_ENU_Navigation(void);
void INS_Navigation(void);
void GPS_INS_Navigation(void);
void GPS_ENU_INS_Navigation(void);


#endif
