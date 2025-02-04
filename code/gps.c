#include "zf_common_headfile.h"
#include "init.h"

void Gps_init(void)
{
    gnss_init(TAU1201);
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
                printf("经度: %.6f°%c\n", gnss.longitude, gnss.ew);
                printf("纬度: %.6f°%c\n", gnss.latitude, gnss.ns);
                printf("海拔: %.2fm\n", gnss.height);
                
                // 打印运动信息
                printf("速度: %.2fkm/h\n", gnss.speed);
                printf("航向: %.2f°\n", gnss.direction);
                
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
    // 添加基本显示，即使没有GPS数据也能看到
    ips114_show_string(0, 0, "GPS Status:");
    
    if(gnss_flag)
    {
        // 解析GPS数据
        if(0 == gnss_data_parse())
        {
            // 显示GPS信息
            ips114_show_string(0, 0, "GPS:");
            ips114_show_string(40, 0, gnss.state ? "Valid" : "Invalid");
            
            if(gnss.state)  // 如果GPS定位有效
            {
                // 显示位置信息
                ips114_show_float(0, 16, gnss.longitude, 8, 4);    // 经度
                ips114_show_char(90, 16, gnss.ew);                 // 东/西
                
                ips114_show_float(0, 32, gnss.latitude, 8, 4);     // 纬度
                ips114_show_char(90, 32, gnss.ns);                 // 南/北
                
                ips114_show_float(0, 48, gnss.height, 6, 1);       // 海拔
                ips114_show_string(90, 48, "m");
                
                // 显示运动信息
                ips114_show_float(0, 64, gnss.speed, 6, 1);        // 速度
                ips114_show_string(90, 64, "km/h");
                
                ips114_show_float(0, 80, gnss.direction, 6, 1);    // 航向角
                
                // 显示卫星信息
                ips114_show_int(0, 96, gnss.satellite_used, 3);    // 卫星数
                
                // 显示时间
                ips114_show_int(0, 112, gnss.time.hour, 2);
                ips114_show_string(20, 112, ":");
                ips114_show_int(30, 112, gnss.time.minute, 2);
                ips114_show_string(50, 112, ":");
                ips114_show_int(60, 112, gnss.time.second, 2);
            }
            
            system_delay_ms(10);  // 短暂延时确保显示稳定
        }
        gnss_flag = 0;
    }
}
