#include "zf_common_headfile.h"
#include "zf_device_key.h"
#include "motor.h"

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

// 定义菜单项结构
typedef struct {
    const char* name;
    int value;
    int min;
    int max;
    int step;
} MenuItem;

// 定义菜单状态
typedef enum {
    MENU_STATE_SELECT,  // 选择菜单项状态
    MENU_STATE_EDIT     // 编辑数值状态
} MenuState;

// 菜单项定义
MenuItem menu_items[] = {
    {"Speed", 0, 0, 5000, 1000},
    {"Para1", 0, 0, 100, 10},
    {"Para2", 0, 0, 100, 10},
    {"Para3", 0, 0, 100, 10}
};

#define MENU_ITEMS_COUNT (sizeof(menu_items)/sizeof(MenuItem))

// 菜单全局变量
static int current_item = 0;    // 当前选中的菜单项
static MenuState menu_state = MENU_STATE_SELECT;  // 当前菜单状态

void display_menu(void) {
    ips114_clear();    // 清屏
    
    // 显示所有菜单项
    for(int i = 0; i < MENU_ITEMS_COUNT; i++) {
        char buffer[32];
        sprintf(buffer, "%s%s: %d", 
            (i == current_item) ? "> " : "  ",    // 当前选中项显示箭头
            menu_items[i].name, 
            menu_items[i].value);
        ips114_show_string(0, i * 16, buffer);    // 每行间隔16像素
    }
    
    // 显示当前状态
    ips114_show_string(0, MENU_ITEMS_COUNT * 16 + 16, 
        menu_state == MENU_STATE_SELECT ? "SELECT" : "EDIT");
}

void My_Key(void) {
    key_scanner();  // 按键扫描
    
    // 获取所有按键状态
    key_state_enum key1_state = key_get_state(KEY_1);  // 上
    key_state_enum key2_state = key_get_state(KEY_2);  // 下
    key_state_enum key3_state = key_get_state(KEY_3);  // 确认/编辑
    key_state_enum key4_state = key_get_state(KEY_4);  // 返回
    
    if(menu_state == MENU_STATE_SELECT) {
        // 选择模式下的按键处理
        if(key1_state == KEY_SHORT_PRESS) {
            // 向上选择
            if(current_item > 0) current_item--;
            key_clear_state(KEY_1);
        }
        
        if(key2_state == KEY_SHORT_PRESS) {
            // 向下选择
            if(current_item < MENU_ITEMS_COUNT - 1) current_item++;
            key_clear_state(KEY_2);
        }
        
        if(key3_state == KEY_SHORT_PRESS) {
            // 进入编辑模式
            menu_state = MENU_STATE_EDIT;
            key_clear_state(KEY_3);
        }
    }
    else {
        // 编辑模式下的按键处理
        if(key1_state == KEY_SHORT_PRESS) {
            // 增加值
            menu_items[current_item].value += menu_items[current_item].step;
            if(menu_items[current_item].value > menu_items[current_item].max)
                menu_items[current_item].value = menu_items[current_item].max;
            key_clear_state(KEY_1);
        }
        
        if(key2_state == KEY_SHORT_PRESS) {
            // 减小值
            menu_items[current_item].value -= menu_items[current_item].step;
            if(menu_items[current_item].value < menu_items[current_item].min)
                menu_items[current_item].value = menu_items[current_item].min;
            key_clear_state(KEY_2);
        }
        
        if(key3_state == KEY_SHORT_PRESS || key4_state == KEY_SHORT_PRESS) {
            // 返回选择模式
            menu_state = MENU_STATE_SELECT;
            key_clear_state(KEY_3);
            key_clear_state(KEY_4);
        }
    }
    
    // 更新显示
    display_menu();
}
