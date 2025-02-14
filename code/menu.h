#ifndef _menu_h_
#define _menu_h_

void Button_init(void);
void Menu(void);

void Display_Menu(void);
void Display_Main_Menu(void);
void Display_Steer_Menu(void);
void Display_Speed_Imu_Info(void);
void Display_Gps_Info(void);
void Display_GPS_Point(void);
void Display_GPS_Path(void);

void Main_Menu_Key_Process(void);
void Steer_Menu_Key_Process(void);
void GPS_Point_Menu_Key_Process(void);
void GPS_Path_Menu_Key_Process(void);

#endif
