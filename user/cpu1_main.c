/*********************************************************************************************************************
* TC264 Opensourec Library 即（TC264 开源库）是一个基于官方 SDK 接口的第三方开源库
* Copyright (c) 2022 SEEKFREE 逐飞科技
*
* 本文件是 TC264 开源库的一部分
*
* TC264 开源库 是免费软件
* 您可以根据自由软件基金会发布的 GPL（GNU General Public License，即 GNU通用公共许可证）的条款
* 即 GPL 的第3版（即 GPL3.0）或（您选择的）任何后来的版本，重新发布和/或修改它
*
* 本开源库的发布是希望它能发挥作用，但并未对其作任何的保证
* 甚至没有隐含的适销性或适合特定用途的保证
* 更多细节请参见 GPL
*
* 您应该在收到本开源库的同时收到一份 GPL 的副本
* 如果没有，请参阅<https://www.gnu.org/licenses/>
*
* 额外注明：
* 本开源库使用 GPL3.0 开源许可证协议 以上许可申明为译文版本
* 许可申明英文版在 libraries/doc 文件夹下的 GPL3_permission_statement.txt 文件中
* 许可证副本在 libraries 文件夹下 即该文件夹下的 LICENSE 文件
* 欢迎各位使用并传播本程序 但修改内容时必须保留逐飞科技的版权声明（即本声明）
*
* 文件名称          cpu1_main
* 公司名称          成都逐飞科技有限公司
* 版本信息          查看 libraries/doc 文件夹内 version 文件 版本说明
* 开发环境          ADS v1.9.20
* 适用平台          TC264D
* 店铺链接          https://seekfree.taobao.com/
*
* 修改记录
* 日期              作者                备注
* 2022-09-15       pudding            first version
********************************************************************************************************************/

#include "zf_common_headfile.h"
#include "init.h"
#pragma section all "cpu1_dsram"
// 将本语句与#pragma section all restore语句之间的全局变量都放在CPU1的RAM中

// **************************** 代码区域 ****************************

// 本例程是开源库空工程 可用作移植或者测试各类内外设
// 本例程是开源库空工程 可用作移植或者测试各类内外设
// 本例程是开源库空工程 可用作移植或者测试各类内外设
//uint32_t time = 0;                     // 用于计算时间的变量
//float  time_us = 0;

void core1_main(void)
{
    disable_Watchdog();                     // 关闭看门狗
    interrupt_global_enable(0);             // 打开全局中断
    // 此处编写用户代码 例如外设初始化代码等
    
    hall_init();                            // 初始化霍尔值
    BLDC_Init();                            // 初始化 BLDC
    //BLDC_target_speed = -2;                // 设置 BLDC 电机目标速度
    //BLDC_Set_duty(-200);       // 设置 BLDC 电机速度
    
    // 此处编写用户代码 例如外设初始化代码等
    cpu_wait_event_ready();                 // 等待所有核心初始化完毕
    while (TRUE)
    {
        // 此处编写需要循环执行的代码
        //printf("%d\r\n", hall_value_now);          // 打印当前霍尔值
        //printf("%d \r\n", countttt);               // 打印霍尔计数
        printf("BLDC_speed: %.2f \r\n", BLDC_speed); // 打印 BLDC 电机速度
        //printf("DIR: %d \r\n", BLDC_Dir); // 打印电机转向
        // printf("speed: %.2f \r\n", speed); // 打印编码器速度
        // printf("所需时间: %.2f us\n", time_us);

        // 此处编写需要循环执行的代码
    }
}

IFX_INTERRUPT(cc61_pit_ch1_isr, 0, CCU6_1_CH1_ISR_PRIORITY)
{
    interrupt_global_enable(0);                     // 开启中断嵌套
    pit_clear_flag(CCU61_CH1);

//    uint32 start_time = IfxStm_getLower(IfxStm_getAddress(IfxStm_Index_0));

    read_hall_value();                              // 读取当前霍尔值

    if(hall_value_now != last_hall )
    {
        BLDC_Dir_Judge();                            // 判断电机转向
        last_hall = hall_value_now;
        hall_count++;                               // 霍尔计数
        BLDC_Update();                              // BLDC 电机更新
    }

//    uint32 end_time = IfxStm_getLower(IfxStm_getAddress(IfxStm_Index_0));
//    time = end_time - start_time;
//    time_us = (float)time / 100.0f;
}

#pragma section all restore
// **************************** 代码区域 ****************************
