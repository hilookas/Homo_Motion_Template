#include "serial.h"
#include "headfile.h"

// 初始化串口
// 返回是否发生错误
bool serial_init(void) {
    uart_init(UART_2, 460800, UART2_TX_P02_0, UART2_RX_P02_1); // 初始化串口
    return false;
}

// 堵塞输出一个字符
// c 为要发送的字符
// 返回是否发生错误
bool serial_send_blocking(uint8_t c) {
    uart_putchar(UART_2, c); // 实际上为非堵塞输出
    return false;
}

// 非堵塞轮询一个字符
// c 为要接受的字符
// 返回是否发生错误
bool serial_recv_poll(uint8_t *c) {
    bool ret = uart_query(UART_2, c); // 非阻塞
    return !ret;
}
