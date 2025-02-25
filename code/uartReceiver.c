#include "zf_common_headfile.h"
#include "init.h"

#define   RECEIVER_MIDDLE      1024   // 遥控器中位值
#define   RECEIVER_CHANGE      800    // 遥控器变化范围


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

    target_speed = (15.0 / (RECEIVER_CHANGE)) * (channel_value - RECEIVER_MIDDLE);

//     printf("channel_value: %d\r\n", channel_value);
//     printf("target_speed: %f\r\n", target_speed);
}

void Angle_map(void)
{
    // 假设 uart_receiver.channel[0] 的值在 224 到 1824 之间
    int16 channel_value = uart_receiver.channel[0];

    target_angle = (MAX_ANGLE_L_SMALL / (RECEIVER_CHANGE)) * (channel_value - RECEIVER_MIDDLE);

    // printf("channel_value: %d\r\n", channel_value);
    // printf("target_angle: %f\r\n", target_angle);
}

// 遥控逻辑
void Remote_control(void)
{
    if(1 == uart_receiver.finsh_flag)                               // 帧完成标志判断
    {
        if(1 == uart_receiver.state)                                // 遥控器失控状态判断
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
            Speed_map();                                            // 遥控数据与速度映射
            Angle_map();                                            // 遥控数据与舵机角度映射
        }
        uart_receiver.finsh_flag = 0;                               // 帧完成标志复位
    }
    // else
    // {
    //     printf("Waiting for remote control data...\n");          // 添加等待数据提示
    // }
}
