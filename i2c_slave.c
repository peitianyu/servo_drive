#include "i2c_slave.h"

bit g_isda;                                         //设备地址标志
bit g_isma;                                         //存储地址标志
u8 g_addr;
u8 pdata g_rbuf[10];
u8 pdata g_tbuf[10];
void i2c_slave_init(u8 port_id, u8 addr)
{
    P_SW2 |= 0x80;
	P_SW2 |= port_id;

    I2CCFG = 0x81;                              
    I2CSLADR = addr;

    I2CSLST = 0x00;
    I2CSLCR = 0x78;                                 //使能从机模式中断
    EA = 1;

    g_isda = 1;                                     //用户变量初始化
    g_isma = 1;
    g_addr = 0;
    I2CTXD = g_tbuf[g_addr];
}


void i2c_isr() interrupt 24
{
    _push_(P_SW2);
    P_SW2 |= 0x80;

    if (I2CSLST & 0x40) {
        I2CSLST &= ~0x40;                           //处理START事件
    } else if (I2CSLST & 0x20) {
        I2CSLST &= ~0x20;                           //处理RECV事件
        if (g_isda) {
            g_isda = 0;                             //处理RECV事件（RECV DEVICE ADDR）
        } else if (g_isma) {    
            g_isma = 0;                             //处理RECV事件（RECV MEMORY ADDR）
            g_addr = I2CRXD;
            I2CTXD = g_rbuf[g_addr];
        } else {
            g_rbuf[g_addr++] = I2CRXD;              //处理RECV事件（RECV DATA）
        }
    } else if (I2CSLST & 0x10) {
        I2CSLST &= ~0x10;                           //处理SEND事件
        if (I2CSLST & 0x02) {
            I2CTXD = 0xff;                          //接收到NAK则停止读取数据
        } else {
            I2CTXD = g_tbuf[g_addr++];              //接收到ACK则继续读取数据
        }
    } else if (I2CSLST & 0x08) {
        I2CSLST &= ~0x08;                           //处理STOP事件
        g_isda = 1;
        g_isma = 1;
    }

    _pop_(P_SW2);
}

u8* i2c_slave_get(void) { return g_rbuf; }

void i2c_slave_set(u8* p, u8 len) { 
    u8 i;
    for (i = 0; i < len; i++) {
        g_tbuf[i] = p[i];
    }
}
