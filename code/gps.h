#ifndef _gps_h_
#define _gps_h_

void Gps_init(void);                        // GPS 初始化
void Print_Gps_Info(void);                  // 打印 GPS 信息
void Display_Gps_Info(void);                // 显示 GPS 信息
void Gps_data_to_flash(void);               // GPS 数据写入 Flash
void Gps_data_from_flash(void);             // GPS 数据从 Flash 读取

#endif
