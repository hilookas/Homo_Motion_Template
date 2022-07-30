/*********************************************************************************************************************
 * COPYRIGHT NOTICE
 * Copyright (c) 2020,逐飞科技
 * All rights reserved.
 * 技术讨论QQ群：三群：824575535
 *
 * 以下所有内容版权均属逐飞科技所有，未经允许不得用于商业用途，
 * 欢迎各位使用并传播本程序，修改内容时必须保留逐飞科技的版权声明。
 *
 * @file            main
 * @company         成都逐飞科技有限公司
 * @author          逐飞科技(QQ3184284598)
 * @version         查看doc内version文件 版本说明
 * @Software        ADS v1.2.2
 * @Target core     TC264D
 * @Taobao          https://seekfree.taobao.com/
 * @date            2020-3-23
 ********************************************************************************************************************/

#include "headfile.h"
#include "rtthread.h"
#pragma section all "cpu0_dsram"
// 将本语句与#pragma section all restore语句之间的全局变量都放在CPU0的RAM中

// ================运行移植提示================
// ====== 当前 RTThread 仅能在 Cpu 0 运行 ======
// ====== 当前 RTThread 仅能在 Cpu 0 运行 ======
// ====== 当前 RTThread 仅能在 Cpu 0 运行 ======
// ================运行移植提示================


// 工程导入到软件之后，应该选中工程然后点击refresh刷新一下之后再编译
// 工程默认设置为关闭优化，可以自己右击工程选择properties->C/C++ Build->Setting
// 然后在右侧的窗口中找到C/C++ Compiler->Optimization->Optimization level处设置优化等级
// 一般默认新建立的工程都会默认开2级优化，因此大家也可以设置为2级优化

// 对于TC系列默认是不支持中断嵌套的，希望支持中断嵌套需要在中断内使用enableInterrupts();来开启中断嵌套
// 简单点说实际上进入中断后TC系列的硬件自动调用了disableInterrupts();来拒绝响应任何的中断，因此需要我们自己手动调用enableInterrupts();来开启中断的响应。

// 函数声明

// user code start
#include "comm.h"
#include "zf_assert.h"
#define my_assert ZF_ASSERT
// user code end

int main(void) {
    // 等待所有核心初始化完毕
    IfxCpu_emitEvent(&g_cpuSyncEvent);
    IfxCpu_waitEvent(&g_cpuSyncEvent, 0xFFFF);

    // user code start
    // 无线串口已经在 rtt 初始化调用 get_clk 中已经初始化
    // 屏蔽无线模块可参见 Libraries\seekfree_peripheral\SEEKFREE_WIRELESS.c:84 和 152 让两个函数直接 return 掉即可
    printf("Hello World!\n"); // Hello~

    // 通讯
    comm_init();

    // 上电通知
    uint8_t payload[] = { 0 };
    bool ret = comm_send_blocking(COMM_TYPE_HELLO_FROM_TC264, payload);
    my_assert(!ret);
    
    while (1) {
        // 不断尝试获取EB回传的打角数据，只有成功获取后才会继续运行
        while (true) {
            comm_type_t type;
            uint8_t payload[10];

            bool last_ret = true;
            bool ret = comm_recv_poll(&type, payload);
            while (!ret) {
                // 清空剩下数据
                last_ret = ret;
                ret = comm_recv_poll(&type, payload);
            }
            ret = last_ret;

            if (!ret) {
                // success
                if (type == COMM_TYPE_PING) {
                    // pong back
                    // printf("pong %02x\n", payload[0]);
                    ret = comm_send_blocking(COMM_TYPE_PONG, payload);
                    my_assert(!ret);
                } else if (type == COMM_TYPE_UPDATE_TO_TC264) {
                    // var1 = payload[0];
                    // var2 = payload[1];
                    // var3 = payload[2];
                    break;
                }
            }
            rt_thread_mdelay(1);
        }

        //

        rt_thread_mdelay(5);
    }
    // user code end
}

#pragma section all restore
