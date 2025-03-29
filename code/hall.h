#ifndef _HALL_H
#define _HALL_H

//定义霍尔值输入引脚
#define HALLA_PIN   P33_7
#define HALLB_PIN   P33_8
#define HALLC_PIN   P33_9

extern uint8_t hall_value_now;     //当前霍尔的值
extern uint8_t last_hall;         //上一个霍尔值

void hall_init(void);
void read_hall_value(void);

#endif
