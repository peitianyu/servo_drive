#include "timer.h"

#define   TLOAD(k)                   (65536 - MAIN_Fosc/k)

void timer0_init(u16 hz)
{
	AUXR |= 0x80;  				// 定时器0 1T模式
    TMOD = 0x00;   				// 定时器模式0 16位自动重载模式
    TL0 = TLOAD(hz);	   		// 设置定时初始值
	TH0 = TLOAD(hz) >> 8;	   	// 设置定时初始值
    TR0 = 1;       				// 定时器开始计时
    ET0 = 1;       				// 使能定时器1中断
	EA = 1;  					// 使能总中断
}

void time0_irq() interrupt 1
{
}

void timer1_init(u16 hz)
{
	AUXR |= 0x40;			//定时器时钟1T模式
	TMOD &= 0x0F;			//设置定时器模式
	TL1 = TLOAD(hz);	   	// 设置定时初始值
	TH1 = TLOAD(hz) >> 8;	// 设置定时初始值
	//TF1 = 0;				//清除TF1标志
	TR1 = 1;				//定时器1开始计时
	ET1 = 1;				//使能定时器1中断
	EA = 1;					//使能总中断
}

void time1_irq() interrupt 3
{
}