#include "zf_common_headfile.h"
#include "init.h"

float target_speed = 0.0f;
float target_angle = 0.0f;

uint8_t Start_GPS_Point;                                             // 第一个 GPS 数据索引
uint8_t End_GPS_Point;                                               // 最后一个 GPS 数据索引

void Point_to_Point(uint8_t i)
{
    // char str[20];
    // sprintf(str, "go to %d", i);
    // ips114_show_string(0, 112, str);
    double angle = get_two_points_azimuth(NOW_location.latitude, NOW_location.longitude, GPS_Point[i][0], GPS_Point[i][1]);
    double distance = get_two_points_distance(NOW_location.latitude, NOW_location.longitude, GPS_Point[i][0], GPS_Point[i][1]);

    // target_speed = 0.0f;
    target_angle = (float)angle;
    // ips114_show_float(0, 96, target_angle, 5, 1);
    // ips114_show_float(90, 96, (float)distance, 5, 1);
    if (distance < 1.0f)
    {
        target_speed = 0.0f;
    }
}

void One_By_One(void)
{
    if (Start_GPS_Point < End_GPS_Point)
    {
        Point_to_Point(Start_GPS_Point);
        if (target_speed == 0.0f)
        {
            Start_GPS_Point = (Start_GPS_Point + 1) % End_GPS_Point;
        }
    }
}
