/*********************************************************************************************************************
 * COPYRIGHT NOTICE
 * Copyright (c) 2020,逐飞科技
 * All rights reserved.
 * 技术讨论QQ群：三群：824575535
 *
 * 以下所有内容版权均属逐飞科技所有，未经允许不得用于商业用途，
 * 欢迎各位使用并传播本程序，修改内容时必须保留逐飞科技的版权声明。
 *
 * @file       		zf_assert
 * @company	   		成都逐飞科技有限公司
 * @author     		逐飞科技(QQ3184284598)
 * @version    		查看doc内version文件 版本说明
 * @Software 		ADS v1.2.2
 * @Target core		TC264D
 * @Taobao   		https://seekfree.taobao.com/
 * @date       		2020-3-23
 ********************************************************************************************************************/

#include "stdio.h"
#include "TC264_config.h"
#include "zf_assert.h"

void assert(pchar __file, unsigned int __line, pchar __function)
{
	//输出断言错误 所在文件目录 所在文件行 调用函数名称
#if(DEBUG_PRINTF)
	printf("ASSERTION: %s %d %s\n",__file, __line, __function);
#endif
#pragma warning 507
	while(TRUE)
	{
		//等待程序员解决 断言错误

	}
#pragma warning default
}
