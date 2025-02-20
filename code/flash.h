#ifndef _flash_h_
#define _flash_h_

#define FLASH_SECTION_INDEX       (0)                                // 存储数据用的扇区
#define FLASH_PAGE_INDEX          (8)                                // 存储数据用的页码
#define FLASH_BASIC_DATA_INDEX    (6)                                // 存储基础数据用的页码
#define FLASH_GPS_DATA_INDEX      (5)                                // 存储 GPS 数据用的页码  第7页好像死了
#define FLASH_INS_DATA_INDEX      (4)                                // 存储 INS 数据用的页码

#define MAX_GPS_POINTS            (16)                               // 最大 GPS 点位数
#define GPS_DATA_SIZE             (5)                                // GPS 数据大小

#define MAX_INS_POINTS            (16)                               // 最大 INS 点位数
#define INS_DATA_SIZE             (3)                                // 5个存储单元（索引 + x轴坐标 + y轴坐标）

extern uint8_t GPS_Point_Index;                                      // GPS 数据索引
extern uint8_t INS_Point_Index;                                      // INS 数据索引
extern double GPS_Point[MAX_GPS_POINTS][2];                          // GPS 数据
extern float INS_Point[MAX_INS_POINTS][2];                           // INS 点位

extern float gyro_bias[3];

void Flash_test(void);
void Gps_data_to_flash(void);
void Gps_data_from_flash(void);

void Print_GPS_Point_From_Flash(void);
void Print_GPS_Point_From_Memory(void);

//************************************GPS点位处理****************************************//
void Save_GPS_Point(void);
void GPS_Points_Init(void);
void Erase_GPS_Points(void);

//************************************INS点位处理****************************************//
void Save_INS_Point(void);
void INS_Points_Init(void);

//************************************基础数据处理****************************************//
void Save_Basic_Data(void);
void Basic_Data_Init(void);

#endif
