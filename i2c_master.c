#include "i2c_master.h"

static void i2c_wait()
{
    while (!(I2CMSST & 0x40));
    I2CMSST &= ~0x40;
}

static void i2c_start()
{
    I2CMSCR = 0x01;                             //发送START命令
    i2c_wait();
}

static void i2c_send_data(char dat)
{
    I2CTXD = dat;                               //写数据到数据缓冲区
    I2CMSCR = 0x02;                             //发送SEND命令
    i2c_wait();
}

static void i2c_recv_ack()
{
    I2CMSCR = 0x03;                             //发送读ACK命令
    i2c_wait();
}

static char i2c_recv_data()
{
    I2CMSCR = 0x04;                             //发送RECV命令
    i2c_wait();
    return I2CRXD;
}

static void i2c_send_ack()
{
    I2CMSST = 0x00;                             //设置ACK信号
    I2CMSCR = 0x05;                             //发送ACK命令
    i2c_wait();
}

static void i2c_send_nak()
{
    I2CMSST = 0x01;                             //设置NAK信号
    I2CMSCR = 0x05;                             //发送ACK命令
    i2c_wait();
}

static void i2c_stop()
{
    I2CMSCR = 0x06;                             //发送STOP命令
    i2c_wait();
}


void i2c_master_init(u8 port_id)
{
    P_SW2 |= 0x80;
	P_SW2 |= port_id;

    I2CCFG = 0xe0;                              //使能I2C主机模式
    I2CMSST = 0x00;
}

int i = 0;
void i2c_master_send_datas(u8 dev_addr, u8 mem_addr, u8 *p, u8 len)
{
    i2c_start();
    i2c_send_data(dev_addr);
    i2c_recv_ack();
    i2c_send_data(mem_addr);
    i2c_recv_ack();
	
    for(i = 0; i < len; i++) {
        i2c_send_data(p[i]);
        i2c_recv_ack();
    }
    
    i2c_stop();
}

void i2c_master_recv(u8 dev_addr, u8 mem_addr, u8 *p, u8 len)
{
    i2c_start();
    i2c_send_data(dev_addr);
    i2c_recv_ack();
    i2c_send_data(mem_addr);
    i2c_recv_ack();

    i2c_start();
    i2c_send_data(dev_addr + 1);
    i2c_recv_ack();

    for(i = 0; i < len; i++){
        p[i] = i2c_recv_data();

        (i == len - 1) ? i2c_send_nak() : i2c_send_ack();
    }

    i2c_stop();
}


