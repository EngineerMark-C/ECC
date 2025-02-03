#include "zf_common_headfile.h"
#include "init.h"

// 初始化函数
void UartReceiver_init(void)
{
    uart_receiver_init();
}

// 遥控数据与速度映射
void Speed_map(void)
{
    // 假设 uart_receiver.channel[1] 的值在 224 到 1824 之间
    int16 channel_value = uart_receiver.channel[1];

    // 线性插值计算目标速度
    float target_speed;

    target_speed = (15.0 / (1824 - 1024)) * (channel_value - 1024);

    // 设置 PID 目标速度
    PID_speed(target_speed);
    // printf("channel_value: %d\r\n", channel_value);
    // printf("target_angle: %f\r\n", target_speed);
}

void Angle_map(void)
{
    // 假设 uart_receiver.channel[0] 的值在 224 到 1824 之间
    int16 channel_value = uart_receiver.channel[0];

    // 线性插值计算目标速度
    float target_angle;

    target_angle = (120.0 / (1824 - 1024)) * (channel_value - 1024) + 1130;

    // 设置 PID 目标速度
    Sreer_set_duty(target_angle);
    // printf("channel_value: %d\r\n", channel_value);
    // printf("target_angle: %f\r\n", target_angle);
}

// 遥控逻辑
void Remote_control(void)
{
    if(1 == uart_receiver.finsh_flag)                            // 帧完成标志判断
    {
        if(1 == uart_receiver.state)                             // 遥控器失控状态判断
        // {
        //     printf("CH1-CH6 data: ");
        //     for(int i = 0; i < 6; i++)
        //     {
        //         printf("%d ", uart_receiver.channel[i]);         // 串口输出6个通道数据
        //     }
        //     printf("\r\n");
        // }
        // else
        // {
        //     printf("Remote control has been disconnected.\r\n"); // 串口输出失控提示
        // }
        {
            Speed_map();                                          // 遥控数据与速度映射
            Angle_map();                                          // 遥控数据与舵机角度映射
        }
        uart_receiver.finsh_flag = 0;                            // 帧完成标志复位
    }
}
