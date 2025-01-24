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
* 文件名称          cpu0_main
* 公司名称          成都逐飞科技有限公司
* 版本信息          查看 libraries/doc 文件夹内 version 文件 版本说明
* 开发环境          ADS v1.9.4
* 适用平台          TC264D
* 店铺链接          https://seekfree.taobao.com/
*
* 修改记录
* 日期              作者                备注
* 2022-09-15       pudding            first version
********************************************************************************************************************/
#include "zf_common_headfile.h"
#include "init.h"
#pragma section all "cpu0_dsram"
// 将本语句与#pragma section all restore语句之间的全局变量都放在CPU0的RAM中

// **************************** 代码区域 ****************************
int core0_main(void)
{
    clock_init();                   // 获取时钟频率<务必保留>
    debug_init();                   // 初始化默认调试串口

    // 此处编写用户代码 例如外设初始化代码等
    cpu_wait_event_ready();         // 等待所有核心初始化完毕
    Init();                         // 初始化函数
    while (TRUE)
    {
        ips114_show_int(0, 16, duty1, 5);                         // 显示按键状态
        ips114_show_int(0, 32, duty2, 5);                         // 显示按键状态

        Imu_get_data();                                             // 获取 IMU963RA 数据
        Encoder_get_speed();
        My_Key();                                                   // 按键处理函数
        printf("%f\n",speed);
//        ips114_show_float(0, 16, imu963ra_gyro_transition(imu963ra_gyro_x), 5, 2); // 显示陀螺仪 X 轴数据
//        ips114_show_float(0, 32, imu963ra_gyro_transition(imu963ra_gyro_y), 5, 2); // 显示陀螺仪 Y 轴数据
//        ips114_show_float(0, 48, imu963ra_gyro_transition(imu963ra_gyro_z), 5, 2); // 显示陀螺仪 Z 轴数据
//        ips114_show_float(0, 64, imu963ra_acc_transition(imu963ra_acc_x), 5, 2);   // 显示加速度计 X 轴数据
//        ips114_show_float(0, 80, imu963ra_acc_transition(imu963ra_acc_y), 5, 2);   // 显示加速度计 Y 轴数据
//        ips114_show_float(0, 96, imu963ra_acc_transition(imu963ra_acc_z), 5, 2);   // 显示加速度计 Z 轴数据
    }

}

IFX_INTERRUPT(cc60_pit_ch0_isr, 0, CCU6_0_CH0_ISR_PRIORITY)
{
    interrupt_global_enable(0);                     // 开启中断嵌套
    pit_clear_flag(CCU60_CH0);

    encoder_data_dir = encoder_get_count(ENCODER_DIR);                          // 获取编码器计数

    encoder_clear_count(ENCODER_DIR);                                           // 清空编码器计数

}

#pragma section all restore
// **************************** 代码区域 ****************************
