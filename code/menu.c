#include "zf_common_headfile.h"
#include "zf_device_key.h"
#include "init.h"

void Button_init(void)
{
    key_init(10); // 初始化按键
}

const char* key_state_to_string(key_state_enum state) {
    switch (state) {
        case KEY_RELEASE:
            return "KEY_RELEASE";
        case KEY_SHORT_PRESS:
            return "KEY_SHORT_PRESS";
        case KEY_LONG_PRESS:
            return "KEY_LONG_PRESS";
        default:
            return "UNKNOWN_STATE";
    }
}

// 定义菜单状态
typedef enum {
    MENU_MAIN,           // 主菜单状态
    MENU_STEER,          // 舵机调节状态
    MENU_SPEED_IMU,      // 速度和IMU信息显示状态
    MENU_GPS,            // GPS信息显示状态
    Menu_GPS_Point       // GPS点位显示状态
} MenuState;

// 主菜单项定义
typedef struct {
    const char* name;
} MainMenuItem;

// 舵机菜单项定义
typedef struct {
    const char* name;
    int value;
    int min;
    int max;
    int step;
} SteerMenuItem;

// 主菜单项
MainMenuItem main_menu_items[] = {
    {"Steer Control"},
    {"Speed & IMU"},
    {"GPS Info"},
    {"GPS Point"}
};

// 舵机菜单项
SteerMenuItem steer_menu = {
    "Steer PWM",
    PWM_STEER_MIDDLE_L_SMALL,
    PWM_STEER_MIN_L_SMALL,
    PWM_STEER_MAX_L_SMALL,
    5
};

#define MAIN_MENU_ITEMS_COUNT (sizeof(main_menu_items)/sizeof(MainMenuItem))

// 菜单全局变量
static int current_item = 0;    // 当前选中的菜单项
static MenuState menu_state = MENU_MAIN;  // 当前菜单状态
static bool edit_mode = false;  // 舵机编辑模式标志
extern uint8_t GPS_Point_Index;
static uint8_t start_index = 0;      // 新增：当前显示起始索引
static const uint8_t visible_items = 6; // 一屏显示6个条目（16px/item）

void display_menu(void) {
    ips114_clear();    // 清屏
    
    switch(menu_state) {
        case MENU_MAIN:
            // 显示主菜单
            for(int i = 0; i < MAIN_MENU_ITEMS_COUNT; i++) {
                char buffer[32];
                sprintf(buffer, "%s%s", 
                    (i == current_item) ? "> " : "  ",
                    main_menu_items[i].name);
                ips114_show_string(0, i * 16, buffer);
            }
            break;
            
        case MENU_STEER:
            // 显示舵机调节界面
            ips114_show_string(0, 0, "Steer Control");
            char buffer[32];
            sprintf(buffer, "%sPWM: %d", 
                edit_mode ? "> " : "  ",
                steer_menu.value);
            ips114_show_string(0, 16, buffer);
            ips114_show_string(0, 48, "Press KEY3 to edit");
            ips114_show_string(0, 64, "Press KEY4 to return");
            break;
            
        case MENU_SPEED_IMU:
            Speed_Imu_Info();
            break;
            
        case MENU_GPS:
            Display_Gps_Info();
            //Print_Gps_Info();
            break;

        case Menu_GPS_Point:
            // 显示GPS点位管理界面
            ips114_show_string(0, 0, "GPS Points Management");
            
            // 显示当前可见范围的点位（Y轴间隔16像素）
            for(uint8_t i = 0; i < visible_items; i++) {
                uint8_t point_num = start_index + i;
                if(point_num >= MAX_GPS_POINTS) break;
                
                char point_info[32];
                sprintf(point_info, "%sP%d:%.6f,%.6f",
                    (point_num == GPS_Point_Index) ? ">" : " ",
                    point_num,
                    GPS_Point[point_num][0],
                    GPS_Point[point_num][1]);
                ips114_show_string(0, 16 + i*16, point_info);
            }
            // 底部提示信息
            char index_info[32];
            sprintf(index_info, "Idx:%02d KEY3:Save KEY4:Back", GPS_Point_Index);
            ips114_show_string(0, 112, index_info);  // 正确传参：x, y, 字符串
            break;
    }
}

void Menu(void) {
    key_scanner();  // 按键扫描
    
    // 获取所有按键状态
    key_state_enum key1_state = key_get_state(KEY_1);  // 上
    key_state_enum key2_state = key_get_state(KEY_2);  // 下
    key_state_enum key3_state = key_get_state(KEY_3);  // 确认/编辑
    key_state_enum key4_state = key_get_state(KEY_4);  // 返回
    
    switch(menu_state) {
        case MENU_MAIN:
            // 主菜单按键处理
            if(key1_state == KEY_SHORT_PRESS) {
                if(current_item > 0) current_item--;
                key_clear_state(KEY_1);
            }
            if(key2_state == KEY_SHORT_PRESS) {
                if(current_item < MAIN_MENU_ITEMS_COUNT - 1) current_item++;
                key_clear_state(KEY_2);
            }
            if(key3_state == KEY_SHORT_PRESS) {
                // 进入选中的子菜单
                switch(current_item) {
                    case 0: menu_state = MENU_STEER; break;
                    case 1: menu_state = MENU_SPEED_IMU; break;
                    case 2: menu_state = MENU_GPS; break;
                    case 3: menu_state = Menu_GPS_Point; break;
                }
                key_clear_state(KEY_3);
            }
            break;
            
        case MENU_STEER:
            if(edit_mode) {
                // 舵机PWM编辑模式
                if(key1_state == KEY_SHORT_PRESS) {
                    steer_menu.value += steer_menu.step;
                    if(steer_menu.value > steer_menu.max)
                        steer_menu.value = steer_menu.max;
                    Sreer_set_duty(steer_menu.value);
                    key_clear_state(KEY_1);
                }
                if(key2_state == KEY_SHORT_PRESS) {
                    steer_menu.value -= steer_menu.step;
                    if(steer_menu.value < steer_menu.min)
                        steer_menu.value = steer_menu.min;
                    Sreer_set_duty(steer_menu.value);
                    key_clear_state(KEY_2);
                }
                if(key3_state == KEY_SHORT_PRESS || key4_state == KEY_SHORT_PRESS) {
                    edit_mode = false;
                    key_clear_state(KEY_3);
                    key_clear_state(KEY_4);
                }
            } else {
                // 舵机菜单非编辑模式
                if(key3_state == KEY_SHORT_PRESS) {
                    edit_mode = true;
                    key_clear_state(KEY_3);
                }
                if(key4_state == KEY_SHORT_PRESS) {
                    menu_state = MENU_MAIN;
                    key_clear_state(KEY_4);
                }
            }
            break;
            
        case MENU_SPEED_IMU:
        case MENU_GPS:
            if(key4_state == KEY_SHORT_PRESS) {
                menu_state = MENU_MAIN;
                key_clear_state(KEY_4);
            }
            break;

        case Menu_GPS_Point:
            if(key1_state == KEY_SHORT_PRESS) { // 上
                if(GPS_Point_Index > 0) {
                    GPS_Point_Index--;
                    // 滚动逻辑：当当前索引小于起始索引时调整显示范围
                    if(GPS_Point_Index < start_index)
                        start_index = GPS_Point_Index;
                }
                key_clear_state(KEY_1);
            }
            if(key2_state == KEY_SHORT_PRESS) { // 下
                if(GPS_Point_Index < MAX_GPS_POINTS - 1) {
                    GPS_Point_Index++;
                    // 滚动逻辑：当当前索引超过显示范围时调整显示范围
                    if(GPS_Point_Index >= start_index + visible_items)
                        start_index = GPS_Point_Index - visible_items + 1;
                }
                key_clear_state(KEY_2);
            }
            if(key3_state == KEY_SHORT_PRESS) {
                Save_GPS_Point();
                // 保存后自动跳转到下一个点位并调整显示
                if(GPS_Point_Index < MAX_GPS_POINTS - 1) {
                    GPS_Point_Index++;  // 自动跳到下一个点位
                    // 滚动显示逻辑
                    if(GPS_Point_Index >= start_index + visible_items) {
                        start_index = GPS_Point_Index - visible_items + 1;
                    }
                }
                // GPS_Point_Index = (GPS_Point_Index + 1) % MAX_GPS_POINTS;
                // // 滚动显示逻辑
                // if(GPS_Point_Index >= start_index + visible_items || GPS_Point_Index < start_index) {
                // start_index = (GPS_Point_Index / visible_items) * visible_items;
                // }
                key_clear_state(KEY_3);
            }
            if(key4_state == KEY_SHORT_PRESS) {
                menu_state = MENU_MAIN;
                key_clear_state(KEY_4);
            }
            break;
    }
    
    // 更新显示
    display_menu();
}
