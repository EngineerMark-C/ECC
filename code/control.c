#include "zf_common_headfile.h"
#include "init.h"

float target_speed = 0.0f;
float target_angle = 0.0f;

uint8_t First_GPS_Point = 0;                                             // 第一个 GPS 数据标志

void Point_to_Point(void)
{
    double angle = get_two_points_azimuth(gnss.latitude, gnss.longitude, GPS_Point[GPS_Point_Index][0], GPS_Point[GPS_Point_Index][1]);
    double distance = get_two_points_distance(gnss.latitude, gnss.longitude, GPS_Point[GPS_Point_Index][0], GPS_Point[GPS_Point_Index][1]);
    target_speed = 1.0f;
    target_angle = angle;
    if (distance < 1.0f)
    {
        target_speed = 0.0f;
    }
}
