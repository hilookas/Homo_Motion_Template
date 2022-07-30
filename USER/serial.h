#ifndef _SERIAL_H_
#define _SERIAL_H_

#include <stdint.h>
#include <stdbool.h>

bool serial_init(void);

bool serial_send_blocking(uint8_t c);

bool serial_recv_poll(uint8_t *c);

#endif
