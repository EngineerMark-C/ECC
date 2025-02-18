#include "zf_common_headfile.h"
#include "init.h"

float target_speed;
float target_angle = 0.0f;

float GPS_ENU[MAX_GPS_POINTS][2];                                    // GPS ENU 坐标

uint8_t Start_GPS_Point;                                             // 第一个 GPS 数据索引
uint8_t End_GPS_Point;                                               // 最后一个 GPS 数据索引
uint8_t NOW_GPS_Point;                                               // 当前 GPS 数据索引

uint8_t Start_INS_Point;                                             // 第一个 INS 数据索引
uint8_t End_INS_Point;                                               // 最后一个 INS 数据索引
uint8_t NOW_INS_Point;                                               // 当前 INS 数据索引

uint8_t GPS_TO_INS_POINT = 0;                                        // GPS点位转换到INS点位

typedef struct {
    double origin_lat;    // 原点纬度（弧度）
    double origin_lon;    // 原点经度（弧度）
    float easting;        // 东向坐标（米）
    float northing;       // 北向坐标（米）
} CoordinateSystem;

CoordinateSystem local_frame;  // 本地坐标系

// 到达标志位
uint8_t reach_flag = 0;

// 初始化零点坐标
void Local_Frame_Init(double lat0, double lon0) 
{
    local_frame.origin_lat = ANGLE_TO_RAD(lat0);
    local_frame.origin_lon = ANGLE_TO_RAD(lon0);
}

// WGS84坐标转ENU坐标
void WGS84_to_ENU(double lat, double lon, float* east, float* north) 
{
    const double a = 6378137.0;       // WGS84长半轴
    const double f = 1.0/298.257223563; // 扁率
    
    double sin_lat0 = sin(local_frame.origin_lat);
    double cos_lat0 = cos(local_frame.origin_lat);
    
    double dLon = ANGLE_TO_RAD(lon) - local_frame.origin_lon;
    double dLat = ANGLE_TO_RAD(lat) - local_frame.origin_lat;
    
    // 卯酉圈曲率半径
    double N = a / sqrt(1 - (2*f - f*f)*sin_lat0*sin_lat0);
    
    // 泰勒展开近似（适用于10km范围内）
    *east  = (float)(N * cos_lat0 * dLon);
    *north = (float)(N * dLat - 0.5 * N * (dLat*dLat)*sin_lat0*cos_lat0);
}

// 将路径点预转换为ENU坐标（启动时初始化）
void WGS84_to_ENU_Init(void)
{
    Local_Frame_Init(GPS_Point[0][0], GPS_Point[0][1]);
    for(int i=0; i <= End_GPS_Point; i++){
        WGS84_to_ENU(GPS_Point[i][0], GPS_Point[i][1], 
                    &GPS_ENU[i][0], &GPS_ENU[i][1]);
    }
}

void GPS_Point_to_Point(uint8_t i)
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
        reach_flag = 1;  // 使用标志位代替直接修改速度
    }
}

void GPS_ENU_Point_to_Point(uint8_t i) 
{
    // 使用平面坐标系计算
    float dx = GPS_ENU[i][0] - position[0];  // 东向差值
    float dy = GPS_ENU[i][1] - position[1];  // 北向差值
    
    float angle = RAD_TO_ANGLE(atan2f(dy, dx));
    angle = angle < 0 ? angle + 360 : angle;
    float distance = sqrtf(dx*dx + dy*dy);
    
    target_angle = angle;
    if (distance < 1.0f) 
    {
        reach_flag = 1;  // 统一使用标志位
    }
}

void GPS_Navigation(void)
{
    if (NOW_GPS_Point > End_GPS_Point) {
        target_speed = 0.0f;
        return;
    }
    if (NOW_GPS_Point <= End_GPS_Point && Start_GPS_Point < End_GPS_Point)
    {
        GPS_Point_to_Point(NOW_GPS_Point);
        if (reach_flag)  // 改为检查标志位
        {
            if(NOW_GPS_Point < End_GPS_Point) {
                NOW_GPS_Point++;
            }
            reach_flag = 0;  // 重置标志位
        }
    }
}

void GPS_ENU_Navigation(void)
{
    if (NOW_GPS_Point > End_GPS_Point) {
        target_speed = 0.0f;
        return;
    }
    if (NOW_GPS_Point <= End_GPS_Point && Start_GPS_Point < End_GPS_Point)
    {
        GPS_ENU_Point_to_Point(NOW_GPS_Point);
        if (reach_flag)  // 改为检查标志位
        {
            if(NOW_GPS_Point < End_GPS_Point) {
                NOW_GPS_Point++;
            }
            reach_flag = 0;  // 重置标志位
        }
    }
}

void INS_Point_to_Point(uint8_t i)
{
    // 使用平面坐标系计算（单位：米）
    float dx = INS_Point[i][0] - position[0];
    float dy = INS_Point[i][1] - position[1];
    
    // 计算平面方位角（0-360度）
    float angle = RAD_TO_ANGLE(atan2f(dy, dx));
    angle = angle < 0 ? angle + 360 : angle;
    
    // 计算欧几里得距离
    float distance = sqrtf(dx*dx + dy*dy);

    target_angle = angle;

    if (distance < 0.1f)
    {
        reach_flag = 1;  // INS使用相同标志位
    }
}

void INS_Navigation(void)
{
    if (NOW_INS_Point > End_INS_Point) {
        target_speed = 0.0f;
        return;
    }
    if (Start_INS_Point < End_INS_Point)
    {
        INS_Point_to_Point(NOW_INS_Point);
        if (reach_flag)
        {
            NOW_INS_Point++;
            reach_flag = 0;  // 重置标志位
        }
    }
}

void GPS_INS_Navigation(void)
{
    static uint8_t navigation_phase = 0;  // 0:GPS导航阶段  1:INS导航阶段  2:返回GPS导航阶段
    
    // 添加全局停车判断
    if (NOW_GPS_Point > End_GPS_Point && NOW_INS_Point > End_INS_Point) {
        target_speed = 0.0f;
        return;
    }
    
    switch(navigation_phase) {
        case 0:
            if (NOW_GPS_Point <= GPS_TO_INS_POINT) {
                // 继续使用GPS导航到切换点
                GPS_Point_to_Point(NOW_GPS_Point);
                if (reach_flag)  // 改为检查标志位
                {
                    if (NOW_GPS_Point == GPS_TO_INS_POINT)
                    {
                        // 到达切换点，准备切换到INS导航
                        navigation_phase = 1;
                        NOW_INS_Point = Start_INS_Point;  // 初始化INS起始点
                    }
                    NOW_GPS_Point++;
                    reach_flag = 0;  // 重置标志位
                }
            } else {
                target_speed = 0.0f;  // GPS阶段超出范围时停车
            }
            break;
            
        case 1:
            if (NOW_INS_Point <= End_INS_Point) {
                INS_Point_to_Point(NOW_INS_Point);
                if (reach_flag)
                {
                    NOW_INS_Point++;
                    if (NOW_INS_Point > End_INS_Point)
                    {
                        // INS导航结束，切回GPS导航
                        navigation_phase = 2;
                        NOW_GPS_Point = GPS_TO_INS_POINT + 1;  // 从切换点后的GPS点继续导航
                    }
                    reach_flag = 0;  // 重置标志位
                }
            } else {
                target_speed = 0.0f;  // INS阶段超出范围时停车
            }
            break;
            
        case 2:
            if (NOW_GPS_Point <= End_GPS_Point) {
                GPS_Point_to_Point(NOW_GPS_Point);
                if (reach_flag)  // 改为检查标志位
                {
                    NOW_GPS_Point = NOW_GPS_Point + 1;
                }
                reach_flag = 0;  // 重置标志位
            } else {
                target_speed = 0.0f;  // 最终GPS阶段超出范围时停车
            }
            break;
    }
}

void GPS_ENU_INS_Navigation(void)
{
    static uint8_t navigation_phase = 0;  // 0:GPS导航阶段  1:INS导航阶段  2:返回GPS导航阶段
    
    // 全局停车条件
    if (NOW_GPS_Point > End_GPS_Point && NOW_INS_Point > End_INS_Point) {
        target_speed = 0.0f;
        return;
    }
    
    switch(navigation_phase) {
        case 0:
            if (NOW_GPS_Point <= GPS_TO_INS_POINT) {
                // 继续使用GPS导航到切换点
                GPS_ENU_Point_to_Point(NOW_GPS_Point);
                if (reach_flag)  // 改为检查标志位
                {
                    if (NOW_GPS_Point == GPS_TO_INS_POINT)
                    {
                        // 到达切换点，准备切换到INS导航
                        navigation_phase = 1;
                        NOW_INS_Point = Start_INS_Point;  // 初始化INS起始点
                    }
                    NOW_GPS_Point++;
                    reach_flag = 0;  // 重置标志位
                }
            } else {
                target_speed = 0.0f;
            }
            break;
            
        case 1:
            if (NOW_INS_Point <= End_INS_Point) {
                INS_Point_to_Point(NOW_INS_Point);
                if (reach_flag)
                {
                    NOW_INS_Point++;
                    if (NOW_INS_Point > End_INS_Point)
                    {
                        // INS导航结束，切回GPS导航
                        navigation_phase = 2;
                        NOW_GPS_Point = GPS_TO_INS_POINT + 1;  // 从切换点后的GPS点继续导航
                    }
                    reach_flag = 0;  // 重置标志位
                }
            } else {
                target_speed = 0.0f;
            }
            break;
            
        case 2:
            if (NOW_GPS_Point <= End_GPS_Point) {
                GPS_ENU_Point_to_Point(NOW_GPS_Point);
                if (reach_flag)  // 改为检查标志位
                {
                    NOW_GPS_Point = NOW_GPS_Point + 1;
                }
                reach_flag = 0;  // 重置标志位
            } else {
                target_speed = 0.0f;
            }
            break;
    }
}