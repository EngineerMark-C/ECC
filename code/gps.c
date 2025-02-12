#include "zf_common_headfile.h"
#include "init.h"

#define PIT2                            (CCU61_CH0 )                            // 使用的周期中断编号
struct Now_gnss NOW_location;

void Gps_init(void)
{
    gnss_init(TAU1201);
    pit_ms_init(PIT2, 100);  // 初始化PIT2为周期中断100ms周期
}

void Get_Now_Location(void)
{
    if(gnss_flag)
    {
        // 解析GPS数据
        if(0 == gnss_data_parse())
        {
            if(gnss.state)
            {
                NOW_location.latitude = gnss.latitude;
                NOW_location.longitude = gnss.longitude;
            }
        }
        gnss_flag = 0;
    }
}

// 打印GPS信息到串口
void Print_Gps_Info(void)
{
    if(gnss_flag)
    {
        // 解析GPS数据
        if(0 == gnss_data_parse())
        {
            printf("----------------------------------------\n");
            printf("GPS状态: %s\n", gnss.state ? "有效" : "无效");
            
            if(gnss.state)  // 如果GPS定位有效
            {
                // 打印位置信息
                printf("经度: %.15g°%c\n", gnss.longitude, gnss.ew);
                printf("纬度: %.15g°%c\n", gnss.latitude, gnss.ns);
                printf("海拔: %.6fm\n", gnss.height);
                
                // 打印运动信息
                printf("速度: %.6fkm/h\n", gnss.speed);
                printf("航向: %.6f°\n", gnss.direction);
                
                // 打印卫星信息
                printf("使用卫星数: %d\n", gnss.satellite_used);
                
                // 打印时间信息
                printf("时间: %d-%02d-%02d %02d:%02d:%02d\n", 
                    gnss.time.year, gnss.time.month, gnss.time.day,
                    gnss.time.hour, gnss.time.minute, gnss.time.second);
            }
            printf("----------------------------------------\n");
        }
        gnss_flag = 0;
    }
}

void Display_Gps_Info(void)
{
    // 始终显示标题
    ips114_show_string(0, 0, "GPS:");
    ips114_show_string(40, 0, gnss.state ? "Valid" : "No Fix");
    
    if(gnss_flag)
    {
        // 解析GPS数据
        if(0 == gnss_data_parse())
        {
            if(gnss.state)
            {
                // Location data
                ips114_show_string(0, 16, "LON:");
                ips114_show_double(30, 16, gnss.longitude, 4, 8);
                ips114_show_char(130, 16, gnss.ew);
                
                ips114_show_string(0, 32, "LAT:");
                ips114_show_double(30, 32, gnss.latitude, 4, 8);
                ips114_show_char(130, 32, gnss.ns);
                
                ips114_show_string(0, 48, "ALT:");
                ips114_show_float(30, 48, gnss.height, 6, 1);
                ips114_show_string(90, 48, "m");
                
                // Movement data
                ips114_show_string(0, 64, "SPD:");
                ips114_show_float(30, 64, gnss.speed, 5, 1);
                ips114_show_string(90, 64, "km/h");
                
                ips114_show_string(0, 80, "DIR:");
                ips114_show_float(30, 80, gnss.direction, 5, 1);
                ips114_show_string(90, 80, "deg");
                
                // System info
                ips114_show_string(0, 96, "SAT:");
                ips114_show_int(30, 96, gnss.satellite_used, 2);
                
                // Time display
                ips114_show_string(0, 112, "UTC:");
                ips114_show_int(30, 112, gnss.time.hour, 2);
                ips114_show_string(46, 112, ":");
                ips114_show_int(54, 112, gnss.time.minute, 2);
                ips114_show_string(70, 112, ":");
                ips114_show_int(78, 112, gnss.time.second, 2);
            }
            else
            {
                // Show waiting message when GPS is invalid
                ips114_show_string(0, 48, "Waiting for signal...");
            }
            system_delay_ms(50);  // Refresh interval
        }
        gnss_flag = 0;
    }
}
