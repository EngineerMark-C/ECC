#include "zf_common_headfile.h"
#include "init.h"

void Ips_init(void)
{
    ips114_init();
    ips114_clear();
    ips114_set_color(RGB565_BLACK, RGB565_WHITE);
    system_delay_ms(200);  // 等待屏幕稳定
}

void Ips_show(void)
{
    ips114_show_float(0, 0, pid.target, 5, 2);     // 目标值
    ips114_show_float(0, 16, speed, 5, 2);         // 当前速度
    ips114_show_float(0, 32, pid.error, 5, 2);     // 误差
    ips114_show_float(0, 48, pid.integral, 5, 2);  // 积分项
    ips114_show_int(0, 64, output, 5);             // 输出值
    ips114_show_float(0, 80, pitch, 5, 2);         // pitch
    ips114_show_float(0, 96, roll, 5, 2);          // roll
    ips114_show_float(0, 112, yaw, 5, 2);          // yaw
    system_delay_ms(10);  // 短暂延时确保显示稳定
}
