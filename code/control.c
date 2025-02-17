#include "zf_common_headfile.h"
#include "init.h"

float target_speed;
float target_angle = 0.0f;

float GPS_ENU[MAX_GPS_POINTS][2];                                    // GPS ENU 坐标

uint8_t Start_GPS_Point;                                             // 第一个 GPS 数据索引
uint8_t End_GPS_Point;                                               // 最后一个 GPS 数据索引

uint8_t Start_INS_Point;                                             // 第一个 INS 数据索引
uint8_t End_INS_Point;                                               // 最后一个 INS 数据索引

typedef struct {
    double origin_lat;    // 原点纬度（弧度）
    double origin_lon;    // 原点经度（弧度）
    float easting;        // 东向坐标（米）
    float northing;       // 北向坐标（米）
} CoordinateSystem;

CoordinateSystem local_frame;  // 本地坐标系

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
        target_speed = 0.0f;
    }
}

void GPS_ENU_Point_to_Point(uint8_t i) 
{
    // 使用平面坐标系计算
    float dx = GPS_ENU[i][0]- position[0];
    float dy = GPS_ENU[i][0] - position[1];
    
    // 后续计算与INS统一
    float angle = RAD_TO_ANGLE(atan2f(dy, dx));
    angle = angle < 0 ? angle + 360 : angle;
    float distance = sqrtf(dx*dx + dy*dy);
    
    target_angle = angle;
    if (distance < 1.0f) target_speed = 0.0f;
}

void GPS_One_By_One(void)
{
    
    if (Start_GPS_Point < End_GPS_Point)
    {
    //     GPS_Point_to_Point(Start_GPS_Point);
        GPS_ENU_Point_to_Point(Start_GPS_Point);
        if (target_speed == 0.0f)
        {
            Start_GPS_Point = (Start_GPS_Point + 1) % End_GPS_Point;
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
        target_speed = 0.0f;
    }
}

void INS_One_By_One(void)
{
    
    if (Start_INS_Point < End_INS_Point)
    {
        INS_Point_to_Point(Start_INS_Point);
        if (target_speed == 0.0f)
        {
            Start_INS_Point = (Start_INS_Point + 1) % End_INS_Point;
        }
    }
}

// void Navigation_Control(void) 
// {
//     static KalmanFilter gps_ins_filter;  // 应实现卡尔曼滤波
//     static uint8_t ins_completed = 0;

//     // 坐标融合（示例）
//     float gps_east, gps_north;
//     WGS84_to_ENU(NOW_location.latitude, NOW_location.longitude, &gps_east, &gps_north);
    
//     // 卡尔曼滤波更新
//     kalman_update(&gps_ins_filter, 
//                  position[0], position[1],
//                  gps_east, gps_north);
    
//     // 使用滤波后位置
//     position[0] = gps_ins_filter.x;
//     position[1] = gps_ins_filter.y;

//     switch(current_phase) {
//         case PHASE_GPS_NAV:
//             GPS_One_By_One();
            
//             // 当到达指定GPS点时触发INS阶段
//             if(Start_GPS_Point == gps_trigger_point && target_speed == 0.0f) {
//                 current_phase = PHASE_INS_NAV;
//                 ins_completed = 0;
//                 target_speed = 0.5f;  // 重置速度
//             }
//             break;

//         case PHASE_INS_NAV:
//             INS_One_By_One();
            
//             // 检测INS是否完成
//             if(Start_INS_Point >= End_INS_Point) {
//                 ins_completed = 1;
//                 current_phase = PHASE_TRANSITION;
//             }
//             break;

//         case PHASE_TRANSITION:
//             // 过渡处理（可选）
//             target_speed = 0.0f;
            
//             // 返回GPS导航
//             if(ins_completed) {
//                 current_phase = PHASE_GPS_NAV;
//                 Start_GPS_Point = gps_trigger_point + 1; // 继续后续GPS点
//                 ins_completed = 0;
//             }
//             break;
//     }
// }
