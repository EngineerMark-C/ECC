#ifndef _flash_h_
#define _flash_h_

#define FLASH_SECTION_INDEX       (0)                                // 存储数据用的扇区
#define FLASH_PAGE_INDEX          (8)                                // 存储数据用的页码
#define FLASH_GPS_DATA_INDEX      (7)                                // 存储 GPS 数据用的页码
#define FLASH_BASIC_DATA_INDEX    (6)                                // 存储基础数据用的页码

void Flash_test(void);
void Gps_data_to_flash(void);
void Gps_data_from_flash(void);
void Collection_GPS_Point(void);
void Display_GPS_Point(void);

#endif
