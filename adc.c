#include "adc.h"


void adc_init()
{
    P_SW2 |= 0x80;
    ADCTIM = 0x3f;                              //设置ADC内部时序
    P_SW2 &= 0x7f;

    ADCCFG = 0x0f;                              //设置ADC时钟为系统时钟/2/16
    ADC_CONTR = 0x80;                           //打开ADC电源
}

u16 adc_get(u8 adc_id)
{
    u16 adc_val = 0;
    ADC_CONTR |= adc_id;                    //设置ADC通道
    _nop_(); _nop_();
    ADC_CONTR |= 0x40;                      //启动AD转换
    while (!(ADC_CONTR & 0x20));            //查询ADC完成标志
    ADC_CONTR &= ~0x20;                     //清完成标志
    adc_val = (ADC_RES << 2) | ADC_RESL;    //读取AD转换结果
    return adc_val;
}
