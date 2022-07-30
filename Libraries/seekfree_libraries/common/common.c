/*********************************************************************************************************************
 * COPYRIGHT NOTICE
 * Copyright (c) 2020,逐飞科技
 * All rights reserved.
 * 技术讨论QQ群：三群：824575535
 *
 * 以下所有内容版权均属逐飞科技所有，未经允许不得用于商业用途，
 * 欢迎各位使用并传播本程序，修改内容时必须保留逐飞科技的版权声明。
 *
 * @file       		common
 * @company	   		成都逐飞科技有限公司
 * @author     		逐飞科技(QQ3184284598)
 * @version    		查看doc内version文件 版本说明
 * @Software 		ADS v1.5.2
 * @Target core		TC264D
 * @Taobao   		https://seekfree.taobao.com/
 * @date       		2022-3-14
 ********************************************************************************************************************/

#include "Cpu0_Main.h"
#include "IfxScuEru.h"
#include "SysSe/Bsp/Bsp.h"
#include "TC264_config.h"
#include "zf_uart.h"
#include "common.h"

CAMERA_TYPE_enum camera_type;	//摄像头型号
uint8 *camera_buffer_addr;      //摄像头数组地址
WIRELESS_TYPE_enum wireless_type;//无线转串口类型
GPS_TYPE_enum gps_type;          //gps类型

IFX_ALIGN(4) IfxCpu_syncEvent g_cpuSyncEvent = 0;//事件同步变量

App_Cpu0 g_AppCpu0; //频率信息变量
void get_clk(void)
{
	disableInterrupts();
	//禁用看门狗
    IfxScuWdt_disableCpuWatchdog(IfxScuWdt_getCpuWatchdogPassword());
    IfxScuWdt_disableSafetyWatchdog(IfxScuWdt_getSafetyWatchdogPassword());


    //获取时钟频率，便于查看当前系统运行频率
    g_AppCpu0.info.pllFreq = IfxScuCcu_getPllFrequency();
    g_AppCpu0.info.cpuFreq = IfxScuCcu_getCpuFrequency(IfxCpu_getCoreIndex());
    g_AppCpu0.info.sysFreq = IfxScuCcu_getSpbFrequency();
    g_AppCpu0.info.stmFreq = IfxStm_getFrequency(&MODULE_STM0);
#if(PRINTF_ENABLE)
    // uart_init(DEBUG_UART, DEBUG_UART_BAUD, DEBUG_UART_TX_PIN, DEBUG_UART_RX_PIN);
    void seekfree_wireless_init(void);
    seekfree_wireless_init();
#endif
}
