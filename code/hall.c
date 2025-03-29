#include "zf_common_headfile.h"
#include "init.h"

uint8_t hall_value_now;     //当前霍尔的值
uint8_t last_hall = -1;

uint8 gpio_get(gpio_pin_enum pin)
{
    return IfxPort_getPinState(get_port(pin), pin&0x1f);
}

void hall_init(void)
{
    gpio_init(HALLA_PIN, GPI, 0, GPI_PULL_UP);
    gpio_init(HALLB_PIN, GPI, 0, GPI_PULL_UP);
    gpio_init(HALLC_PIN, GPI, 0, GPI_PULL_UP);
    read_hall_value();
}

void read_hall_value(void)
{
    uint8 ha, hb, hc;

    ha = gpio_get(HALLA_PIN);
    hb = gpio_get(HALLB_PIN);
    hc = gpio_get(HALLC_PIN);

    hall_value_now = ha + hb*2 + hc*4;
    // hall_value_now = ha | (hb << 1) | (hc << 2);

    //printf("hall_value_now = %d\r\n",hall_value_now);
    // // 霍尔时序转换 将原始的霍尔时序重新排列
    // for(int i=0; i<6; i++)
    // {
    //     if(hall_value_now == control_hall[i])
    //     {
    //         hall_value_now = i+1;
    //         break;
    //     }
    // }
}
