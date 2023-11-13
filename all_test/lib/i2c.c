#include "i2c.h"

#define		I2C_ENABLE()	I2CCFG |= 0x80		/* 使能 I2C 功能 */
#define		I2C_DISABLE()	I2CCFG &= ~0x80		/* 禁止 I2C 功能 */
#define		I2C_SetSpeed(n)	I2CCFG = (I2CCFG & ~0x3f) | (n & 0x3f)	/* 总线速度=Fosc/2/(Speed*2+4) */
#define		I2C_Master()	I2CCFG |=  0x40		/* 1: 设为主机	*/
#define		I2C_Slave()		I2CCFG &= ~0x40		/* 0: 设为从机	*/

#define		I2C_WDTA_EN()		I2CMSAUX |= 0x01		/* 使能自动发送 */
#define		I2C_WDTA_DIS()	I2CMSAUX &= ~0x01		/* 禁止自动发送 */

#define		I2C_Address(n)	I2CSLADR = (I2CSLADR & 0x01) | (n << 1)	/* 从机地址 */
#define		I2C_MATCH_EN()	I2CSLADR &= ~0x01	/* 使能从机地址比较功能，只接受相匹配地址 */
#define		I2C_MATCH_DIS()	I2CSLADR |= 0x01	/* 禁止从机地址比较功能，接受所有设备地址 */

void i2c_master_init(u8 sw_io, u16 speed, u8 wtda)
{
    P_SW2 |= sw_io;
    I2C_DISABLE();
    I2C_Master();
    I2CMSST = 0x00;
    I2C_SetSpeed(speed);
    if (wtda) I2C_WDTA_EN();
    else I2C_WDTA_DIS();
    I2C_ENABLE();
}

void i2c_slave_init(u8 sw_io, u8 addr, u8 match)
{
    P_SW2 |= sw_io;
    I2C_DISABLE();
    I2C_Slave();
    I2CSLST = 0x00;
    I2C_Address(addr);
    if (match) I2C_MATCH_EN();
    else I2C_MATCH_DIS();
    I2C_ENABLE();
}

static void wait(void) { while (!(I2CMSST & 0x40)); I2CMSST &= ~0x40; }

static void start(void) { I2CMSCR = 0x01; wait(); }
static void stop(void) { I2CMSCR = 0x06; wait(); }

static void send_byte(u8 dat) { I2CTXD = dat; I2CMSCR = 0x02; wait(); }
static u8 recv_byte(void) { I2CMSCR = 0x04; wait(); return I2CRXD; }

static void send_ack(void) { I2CMSST = 0x00; I2CMSCR = 0x05; wait(); }
static void send_nack(void) { I2CMSST = 0x01; I2CMSCR = 0x05; wait(); }
static void recv_ack(void) { I2CMSCR = 0x03; wait(); }


void i2c_write_cmd(u8 cmd, u8 dat) { I2CTXD = dat; I2CMSCR = cmd; wait(); }

void i2c_write_date(u8 addr, u8 reg, u8 *p, u8 len)
{
    start();
    send_byte(addr);
    recv_ack();
    send_byte(reg);
    recv_ack();
    while (len--) {
        send_byte(*p++);
        recv_ack();
    }
    stop();
}

void i2c_read_date(u8 addr, u8 reg, u8 *p, u8 len)
{
    start();
    send_byte(addr);
    recv_ack();
    send_byte(reg);
    recv_ack();
    start();
    send_byte(addr | 0x01);
    recv_ack();
    while (len--) {
        *p++ = recv_byte();
        if (len) recv_ack();
        else send_nack();
    }
    stop();
}