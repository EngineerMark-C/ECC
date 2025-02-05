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

void Gps_data_to_flash(void)
{
    if(gnss_flag)
    {
        // 解析GPS数据
        if(0 == gnss_data_parse())
        {
            if(gnss.state)  // 如果GPS定位有效
            {
                flash_buffer_clear();                                                       // 清空缓冲区
                flash_union_buffer[0].float_type  = gnss.longitude;                        // 向缓冲区第 0 个位置写入 float  数据
                flash_union_buffer[1].float_type  = gnss.latitude;                         // 向缓冲区第 1 个位置写入 float  数据
                flash_union_buffer[2].float_type  = gnss.height;                           // 向缓冲区第 2 个位置写入 float  数据
                flash_union_buffer[3].float_type  = gnss.speed;                            // 向缓冲区第 3 个位置写入 float  数据
                flash_union_buffer[4].float_type  = gnss.direction;                        // 向缓冲区第 4 个位置写入 float  数据
                flash_union_buffer[5].uint8_type  = gnss.satellite_used;                   // 向缓冲区第 5 个位置写入 uint8  数据
                flash_union_buffer[6].uint8_type  = gnss.time.hour;                        // 向缓冲区第 6 个位置写入 uint8  数据
                flash_union_buffer[7].uint8_type  = gnss.time.minute;                      // 向缓冲区第 7 个位置写入 uint8  数据
                flash_union_buffer[8].uint8_type  = gnss.time.second;                      // 向缓冲区第 8 个位置写入 uint8  数据
                flash_write_page_from_buffer(FLASH_SECTION_INDEX, FLASH_PAGE_INDEX);        // 向指定 Flash 扇区的页码写入缓冲区数据
            }
        }
        gnss_flag = 0;
    }
}

void Gps_data_from_flash(void)
{
    flash_read_page_to_buffer(FLASH_SECTION_INDEX, FLASH_PAGE_INDEX);           // 将数据从 flash 读取到缓冲区
    printf("longitude: %.6f\n", flash_union_buffer[0].float_type);
    printf("latitude: %.6f\n", flash_union_buffer[1].float_type);
    printf("height: %.2f\n", flash_union_buffer[2].float_type);
    printf("speed: %.2f\n", flash_union_buffer[3].float_type);
    printf("direction: %.2f\n", flash_union_buffer[4].float_type);
    printf("satellite_used: %d\n", flash_union_buffer[5].uint8_type);
    printf("time: %02d:%02d:%02d\n", flash_union_buffer[6].uint8_type, flash_union_buffer[7].uint8_type, flash_union_buffer[8].uint8_type);
}
