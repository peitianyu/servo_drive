#include "timer.h"

void timer0_init(void)    //100us@24MHz
{
	AUXR |= 0x80;  // 定时器0 1T模式
    TMOD = 0x00;   // 定时器模式0 16位自动重载模式
    TL0 = 0xA0;	   // 设置定时初始值
	TH0 = 0xF6;	   // 设置定时初始值
    TR0 = 1;       // 定时器开始计时
    ET0 = 1;       // 使能定时器1中断
    EA  = 1;       // 打开总中断
}

void os_irq() interrupt 1
{
    
}