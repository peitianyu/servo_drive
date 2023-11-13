#ifndef __I2C_H__
#define __I2C_H__


#include "config.h"

#define	I2C_P14_P15				0
#define	I2C_P24_P25				1
#define	I2C_P33_P32				3

void i2c_master_init(u8 io, u16 speed, u8 wtda);   // speed: 总线速度=Fosc/2/(Speed*2+4), wtda: 使能自动发送
void i2c_slave_init(u8 io, u8 addr, u8 match);     //addr: 接收主机地址, match: 从机地址比较功能，只接受相匹配地址

void i2c_write_cmd(u8 cmd, u8 dat);
void i2c_write_date(u8 addr, u8 reg, u8 *p, u8 len);
void i2c_read_date(u8 addr, u8 reg, u8 *p, u8 len);

#endif // __I2C_H__