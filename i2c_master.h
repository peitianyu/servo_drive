#ifndef __I2C_MASTER_H__
#define __I2C_MASTER_H__

#include "config.h"


void i2c_master_init(u8 port_id);

void i2c_master_send_datas(u8 dev_addr, u8 mem_addr, u8 *p, u8 len);

void i2c_master_recv(u8 dev_addr, u8 mem_addr, u8 *p, u8 len);

#endif // __I2C_MASTER_H__