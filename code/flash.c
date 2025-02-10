#include "zf_common_headfile.h"
#include "init.h"

#define FLASH_SECTION_INDEX       (0)                                // 存储数据用的扇区
#define FLASH_PAGE_INDEX          (8)                                // 存储数据用的页码
#define FLASH_GPS_DATA_INDEX      (5)                                // 存储 GPS 数据用的页码  第7页好像死了
#define FLASH_BASIC_DATA_INDEX    (6)                                // 存储基础数据用的页码

#define MAX_GPS_POINTS            (16)                               // 最大 GPS 点位数
#define GPS_DATA_SIZE             (5)                                // 5个存储单元（索引+纬度高低位+经度高低位）

uint8_t GPS_Point_Index = 0;                                         // GPS 数据索引
double GPS_Point[MAX_GPS_POINTS][2];                                             // GPS 数据

// 修改存储结构
typedef union {
    struct {
        uint32_t high;
        uint32_t low;
    } parts;
    double value;
} double_convert;

// 例程测试
void Flash_test(void)
{
if(flash_check(FLASH_SECTION_INDEX, FLASH_PAGE_INDEX))                      // 判断是否有数据
        flash_erase_page(FLASH_SECTION_INDEX, FLASH_PAGE_INDEX);                // 擦除这一页

    printf("\r\n");
    flash_read_page_to_buffer(FLASH_SECTION_INDEX, FLASH_PAGE_INDEX);           // 将数据从 flash 读取到缓冲区
    printf("\r\n FLASH_SECTION_INDEX: %d, FLASH_PAGE_INDEX: %d, origin data is :", FLASH_SECTION_INDEX, FLASH_PAGE_INDEX);
    printf("\r\n float_type : %f", flash_union_buffer[0].float_type);           // 将缓冲区第 0 个位置的数据以 float  格式输出
    printf("\r\n uint32_type: %lu", flash_union_buffer[1].uint32_type);         // 将缓冲区第 1 个位置的数据以 uint32 格式输出
    printf("\r\n int32_type : %d", flash_union_buffer[2].int32_type);           // 将缓冲区第 2 个位置的数据以 int32  格式输出
    printf("\r\n uint16_type: %u", flash_union_buffer[3].uint16_type);          // 将缓冲区第 3 个位置的数据以 uint16 格式输出
    printf("\r\n int16_type : %d", flash_union_buffer[4].int16_type);           // 将缓冲区第 4 个位置的数据以 int16  格式输出
    printf("\r\n uint8_type : %u", flash_union_buffer[5].uint8_type);           // 将缓冲区第 5 个位置的数据以 uint8  格式输出
    printf("\r\n int8_type  : %d", flash_union_buffer[6].int8_type);            // 将缓冲区第 6 个位置的数据以 int8   格式输出
    // 请注意 数据缓冲区的每个位置只能存储一种类型的数据
    // 请注意 数据缓冲区的每个位置只能存储一种类型的数据
    // 请注意 数据缓冲区的每个位置只能存储一种类型的数据

    // 例如 flash_data_union_buffer[0] 写入 int8_type 那么只能以 int8_type 读取
    // 同样 flash_data_union_buffer[0] 写入 float_type 那么只能以 float_type 读取
    printf("\r\n");
    printf("\r\n Data property display :");
    printf("\r\n flash_data_union_buffer[0] write int8 data type:");
    flash_union_buffer[0].int8_type   = -128;                                   // 向缓冲区第 0 个位置写入     int8   数据
    printf("\r\n float_type : %f-data error", flash_union_buffer[0].float_type);// 将缓冲区第 0 个位置的数据以  float  格式输出 数据将不正确
    printf("\r\n int8_type  : %d", flash_union_buffer[0].int8_type);            // 将缓冲区第 0 个位置的数据以  int8   格式输出 得到正确写入数据

    printf("\r\n flash_data_union_buffer[0] write int8 data type:");
    flash_union_buffer[0].int8_type  -= 1;                                      // 向缓冲区第 0 个位置写入     int8   数据
    printf("\r\n float_type : %f-data error", flash_union_buffer[0].float_type);// 将缓冲区第 0 个位置的数据以  float  格式输出 数据将不正确
    printf("\r\n int8_type  : %d", flash_union_buffer[0].int8_type);            // 将缓冲区第 0 个位置的数据以  int8   格式输出 得到正确写入数据

    printf("\r\n flash_data_union_buffer[0] write float data type:");
    flash_union_buffer[0].float_type  = 16.625;                                 // 向缓冲区第 0 个位置写入     float  数据
    printf("\r\n float_type : %f", flash_union_buffer[0].float_type);           // 将缓冲区第 0 个位置的数据以  float  格式输出 得到正确写入数据
    printf("\r\n int8_type  : %d-data error", flash_union_buffer[0].int8_type); // 将缓冲区第 0 个位置的数据以  int8   格式输出 数据将不正确

    // 请注意 数据缓冲区的每个位置只能存储一种类型的数据
    // 请注意 数据缓冲区的每个位置只能存储一种类型的数据
    // 请注意 数据缓冲区的每个位置只能存储一种类型的数据

    flash_buffer_clear();                                                       // 清空缓冲区
    flash_union_buffer[0].float_type  = 3.1415926;                              // 向缓冲区第 0 个位置写入 float  数据
    flash_union_buffer[1].uint32_type = 4294967294;                             // 向缓冲区第 1 个位置写入 uint32 数据
    flash_union_buffer[2].int32_type  = -2147483648;                            // 向缓冲区第 2 个位置写入 int32  数据
    flash_union_buffer[3].uint16_type = 65535;                                  // 向缓冲区第 3 个位置写入 uint16 数据
    flash_union_buffer[4].int16_type  = -32768;                                 // 向缓冲区第 4 个位置写入 int16  数据
    flash_union_buffer[5].uint8_type  = 255;                                    // 向缓冲区第 5 个位置写入 uint8  数据
    flash_union_buffer[6].int8_type   = -128;                                   // 向缓冲区第 6 个位置写入 int8   数据
    flash_write_page_from_buffer(FLASH_SECTION_INDEX, FLASH_PAGE_INDEX);        // 向指定 Flash 扇区的页码写入缓冲区数据

    printf("\r\n");
    flash_buffer_clear();                                                       // 清空缓冲区
    printf("\r\n Flash data buffer default data is :");
    printf("\r\n float_type : %f", flash_union_buffer[0].float_type);           // 将缓冲区第 0 个位置的数据以 float  格式输出
    printf("\r\n uint32_type: %lu",flash_union_buffer[1].uint32_type);          // 将缓冲区第 1 个位置的数据以 uint32 格式输出
    printf("\r\n int32_type : %d", flash_union_buffer[2].int32_type);           // 将缓冲区第 2 个位置的数据以 int32  格式输出
    printf("\r\n uint16_type: %u", flash_union_buffer[3].uint16_type);          // 将缓冲区第 3 个位置的数据以 uint16 格式输出
    printf("\r\n int16_type : %d", flash_union_buffer[4].int16_type);           // 将缓冲区第 4 个位置的数据以 int16  格式输出
    printf("\r\n uint8_type : %u", flash_union_buffer[5].uint8_type);           // 将缓冲区第 5 个位置的数据以 uint8  格式输出
    printf("\r\n int8_type  : %d", flash_union_buffer[6].int8_type);            // 将缓冲区第 6 个位置的数据以 int8   格式输出
    system_delay_ms(200);
    printf("\r\n");
    flash_read_page_to_buffer(FLASH_SECTION_INDEX, FLASH_PAGE_INDEX);           // 将数据从 flash 读取到缓冲区
    printf("\r\n FLASH_SECTION_INDEX: %d, FLASH_PAGE_INDEX: %d, new data is :", FLASH_SECTION_INDEX, FLASH_PAGE_INDEX);
    printf("\r\n float_type : %f", flash_union_buffer[0].float_type);           // 将缓冲区第 0 个位置的数据以 float  格式输出
    printf("\r\n uint32_type: %lu",flash_union_buffer[1].uint32_type);          // 将缓冲区第 1 个位置的数据以 uint32 格式输出
    printf("\r\n int32_type : %d", flash_union_buffer[2].int32_type);           // 将缓冲区第 2 个位置的数据以 int32  格式输出
    printf("\r\n uint16_type: %u", flash_union_buffer[3].uint16_type);          // 将缓冲区第 3 个位置的数据以 uint16 格式输出
    printf("\r\n int16_type : %d", flash_union_buffer[4].int16_type);           // 将缓冲区第 4 个位置的数据以 int16  格式输出
    printf("\r\n uint8_type : %u", flash_union_buffer[5].uint8_type);           // 将缓冲区第 5 个位置的数据以 uint8  格式输出
    printf("\r\n int8_type  : %d", flash_union_buffer[6].int8_type);            // 将缓冲区第 6 个位置的数据以 int8   格式输出
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
                if(flash_check(FLASH_SECTION_INDEX, FLASH_GPS_DATA_INDEX))                      // 判断是否有数据
                    flash_erase_page(FLASH_SECTION_INDEX, FLASH_GPS_DATA_INDEX);                // 擦除这一页
                flash_write_page_from_buffer(FLASH_SECTION_INDEX, FLASH_GPS_DATA_INDEX);        // 向指定 Flash 扇区的页码写入缓冲区数据
            }
        }
        gnss_flag = 0;
    }
}

void Gps_data_from_flash(void)
{
    flash_read_page_to_buffer(FLASH_SECTION_INDEX, FLASH_GPS_DATA_INDEX);           // 将数据从 flash 读取到缓冲区
    printf("longitude: %.6f\n", flash_union_buffer[0].float_type);
    printf("latitude: %.6f\n", flash_union_buffer[1].float_type);
    printf("height: %.2f\n", flash_union_buffer[2].float_type);
    printf("speed: %.2f\n", flash_union_buffer[3].float_type);
    printf("direction: %.2f\n", flash_union_buffer[4].float_type);
    printf("satellite_used: %d\n", flash_union_buffer[5].uint8_type);
    printf("time: %02d:%02d:%02d\n", flash_union_buffer[6].uint8_type, flash_union_buffer[7].uint8_type, flash_union_buffer[8].uint8_type);
}

// 打印 GPS 点位
void Print_GPS_Point_From_Flash(void)
{
    flash_read_page_to_buffer(FLASH_SECTION_INDEX, FLASH_GPS_DATA_INDEX);

    for (uint8_t i = 0; i < MAX_GPS_POINTS; i++)
    {
        // 检查数据是否有效
        if (flash_union_buffer[i * GPS_DATA_SIZE].uint8_type == i)
        {
            double_convert lat, lon;
            lat.parts.high = flash_union_buffer[i * GPS_DATA_SIZE + 1].uint32_type;
            lat.parts.low = flash_union_buffer[i * GPS_DATA_SIZE + 2].uint32_type;
            lon.parts.high = flash_union_buffer[i * GPS_DATA_SIZE + 3].uint32_type;
            lon.parts.low = flash_union_buffer[i * GPS_DATA_SIZE + 4].uint32_type;
            
            GPS_Point[i][0] = lat.value;
            GPS_Point[i][1] = lon.value;
            
            printf("Point %d: latitude = %.9f, longitude= %.9f\n",
                    flash_union_buffer[i * GPS_DATA_SIZE].uint8_type,
                    GPS_Point[i][0],  // 直接从内存读取已重组的数据
                    GPS_Point[i][1]);
        }
        else
        {
            printf("Point %d: No valid data.\n", i);
        }
    }
}

// 打印 GPS 点位
void Print_GPS_Point_From_Memory(void)
{
    for(uint8_t i = 0; i < MAX_GPS_POINTS; i++)
    {
        printf("point: %d, latitude: %.9f, longitude: %.9f\n", 
                i,                  // i 点位序号
                GPS_Point[i][0],    // GPS_Point[i][0] 存储纬度
                GPS_Point[i][1]);   // GPS_Point[i][1] 存储经度
    }
}

void Save_GPS_Point(void)
{
    if(GPS_Point_Index < MAX_GPS_POINTS)
    {
        // 1. 保存到内存
        GPS_Point[GPS_Point_Index][0] = NOW_location.latitude;
        GPS_Point[GPS_Point_Index][1] = NOW_location.longitude;
        
        // 2. 同步到Flash
        flash_buffer_clear();
        
        // 2.1 写入所有内存中的点位数据(包括新点位)
        for(uint8_t i = 0; i < MAX_GPS_POINTS; i++)
        {
            double_convert lat, lon;
            lat.value = GPS_Point[i][0];
            lon.value = GPS_Point[i][1];
            
            flash_union_buffer[i * GPS_DATA_SIZE].uint8_type = i;
            flash_union_buffer[i * GPS_DATA_SIZE + 1].uint32_type = lat.parts.high;
            flash_union_buffer[i * GPS_DATA_SIZE + 2].uint32_type = lat.parts.low;
            flash_union_buffer[i * GPS_DATA_SIZE + 3].uint32_type = lon.parts.high;
            flash_union_buffer[i * GPS_DATA_SIZE + 4].uint32_type = lon.parts.low;
        }
        
        // 2.2 擦除并写入Flash
        flash_erase_page(FLASH_SECTION_INDEX, FLASH_GPS_DATA_INDEX);
        flash_write_page_from_buffer(FLASH_SECTION_INDEX, FLASH_GPS_DATA_INDEX);
        ips114_show_string(60, 32, "GPS Point Saved.");
        system_delay_ms(500);
    }
}

// 上电初始化时调用
void GPS_Points_Init(void)
{
    ips114_show_string(60, 32, "Loading GPS Points...");
    
    flash_read_page_to_buffer(FLASH_SECTION_INDEX, FLASH_GPS_DATA_INDEX);

    if(flash_union_buffer[0].uint8_type != 0xFF)  // 检查首字节是否有效
    {
        for(uint8_t i = 0; i < MAX_GPS_POINTS; i++)
        {        
            if(flash_union_buffer[i * GPS_DATA_SIZE].uint8_type == i)
            {
                double_convert lat, lon;
                lat.parts.high = flash_union_buffer[i * GPS_DATA_SIZE + 1].uint32_type;
                lat.parts.low = flash_union_buffer[i * GPS_DATA_SIZE + 2].uint32_type;
                lon.parts.high = flash_union_buffer[i * GPS_DATA_SIZE + 3].uint32_type;
                lon.parts.low = flash_union_buffer[i * GPS_DATA_SIZE + 4].uint32_type;
                
                GPS_Point[i][0] = lat.value;
                GPS_Point[i][1] = lon.value;
            }
            else
            {
                continue;
            }
        }
        ips114_show_string(60, 32, "GPS Points Loaded.");
        system_delay_ms(1000);  // 显示1秒
        ips114_clear();         // 清屏
    }
}

// 擦除 GPS 数据
void Erase_GPS_Points(void)
{
    flash_erase_page(FLASH_SECTION_INDEX, FLASH_GPS_DATA_INDEX);
    ips114_show_string(60, 32, "GPS Points Erased.");
    system_delay_ms(500);
}
