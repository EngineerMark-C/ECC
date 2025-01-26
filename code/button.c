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

void My_Key(void)
{
    key_scanner(); // 在主循环中调用按键扫描函数

    if (key_get_state(KEY_1) == KEY_SHORT_PRESS) {
        duty1 += 1000;
        if (duty1 > 5000) {
            duty1 = 5000;
        }
        pwm_set_duty(PWM1, duty1);
        ips114_show_string(0, 48, key_state_to_string(key_get_state(KEY_1)));
        key_clear_state(KEY_1); // 清除按键状态
    }
    if (key_get_state(KEY_2) == KEY_SHORT_PRESS) {
        duty1 -= 1000;
        if (duty1 < 0) {
            duty1 = 0;
        }
        pwm_set_duty(PWM1, duty1);
        ips114_show_string(0, 64, key_state_to_string(key_get_state(KEY_2)));
        key_clear_state(KEY_2); // 清除按键状态
    }
}
