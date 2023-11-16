#include "adc.h"


void adc_init(u8 adc_pin)
{
    P_SW2 |= 0x80;
    ADCTIM = 0x3f;                              //设置ADC内部时序
    P_SW2 &= 0x7f;

    ADCCFG = 0x2f;                              //设置ADC时钟为系统时钟/2/16
    ADC_CONTR = 0x80;                           //打开ADC电源
    ADC_CONTR |= adc_pin;                       //选择ADC通道
    ADC_CONTR |= 0x40;                          //启动AD转换
}

static u16 g_adc_value = 0;
u16 adc_read(void)
{
    u8 i;
    u16 res = 0;
    for(i=0; i<8; i++) { res += g_adc_value; }
    res >>= 3;
    return res;
}

void adc_irq(void) interrupt 5
{
    ADC_CONTR &= ~0x20;                         //清中断标志
    g_adc_value = (ADC_RES << 8) | ADC_RESL;    //读取ADC结果
    ADC_CONTR |= 0x40;                          //继续AD转换
}