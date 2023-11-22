#ifndef __I2C_SLAVE_H__
#define __I2C_SLAVE_H__

#include "config.h"

void i2c_slave_init(u8 port_id, u8 addr);

void i2c_set_addr(u8 addr);

u8* i2c_slave_get(void);

void i2c_slave_set(u8* p, u8 len);

#endif // __I2C_SLAVE_H__