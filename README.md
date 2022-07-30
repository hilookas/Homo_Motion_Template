# Homo_Motion

项目基于：<https://gitee.com/seekfree/TC264_RTThread_Library> 进行

这是一个模板项目，对一些代码做了优化，便于 VSCode 等环境下使用。

下载后重新命名为 Homo_Motion 即可正常使用。

如果想要修改项目名称，推荐通过 VSCode 的搜索替换功能，将整个文件夹中的 Homo_Motion 部分全部替换为文件夹的名称。

此外本项目还提供了串口通信部分的参考实现

## 20220502 更新文件编码

涉及到 `.c .h .txt` 文件

```bash
find . -type f -name "*.c" | while read x; do
  set -o pipefail
  iconv -f GB2312 -t UTF-8 < "$x" | tr -d '\015' > "$x.tmp"
  
  if [[ $? != 0 ]]; then
    echo $x
    rm "$x.tmp"
  else
    mv "$x.tmp" "$x"
  fi
done
```

## 20220718 更改调试用串口

逐飞代码中 printf 与 rtt 的 kprintf 使用的都是 uart0 ，而硬件上调试用的串口为无线串口 uart3

Libraries\rtthread_libraries\bsp\rtconfig.h:38 uart0->uart3  
USER\isr.c: uart0_rx_isr uart2_rx_isr uart3_rx_isr 有移动代码的位置，使串口对应  
Libraries\seekfree_libraries\zf_uart.c:364 修改为使用逐飞无线驱动的代码以实现流控功能,但是可能会 stop the world(延迟不可控,不插无线模块电脑端这段代码就会卡死)  
Libraries\seekfree_libraries\board\board.c:110 修改为使用逐飞无线驱动的代码以实现流控功能,但是可能会 stop the world(延迟不可控,不插无线模块电脑端这段代码就会卡死)  
Libraries\seekfree_libraries\common\common.c:49 修改为使用逐飞无线驱动初始化代码  
USER\TC264_config.h:36 已注释(由逐飞无线驱动管理)  
Libraries\seekfree_peripheral\SEEKFREE_WIRELESS.h:36 修改为相应的引脚和波特率  

Libraries\seekfree_peripheral\SEEKFREE_WIRELESS.c:151 让程序 return 掉就可以实现关闭串口