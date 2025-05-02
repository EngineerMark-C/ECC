#ifndef _imu_h_
#define _imu_h_

extern float pitch, roll, yaw;

void Imu_init(void);
void Calibrate_Gyro(void);
void Imu_get_data(void);
void Imu_get_quaternion(void);

#endif
