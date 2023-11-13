#include "adc.h"


void adc_init(void)
{
    P_SW2 |= 0x80;
    ADCTIM = 0x3f;                              //设置ADC内部时序
    P_SW2 &= 0x7f;

    ADCCFG = 0x2f;                              //设置ADC时钟为系统时钟/2/16
    ADC_CONTR = 0x80;                           //打开ADC电源
}

static int adc_read_once(u8 adc_pin, u16 *adc_value)
{
    int res;
    
    ADC_CONTR |= adc_pin;                       //选择ADC通道
    ADC_CONTR |= 0x40;                          //启动AD转换
    _nop_();
    _nop_();
    while (!(ADC_CONTR & 0x20));                //查询ADC完成标志
    ADC_CONTR &= ~0x20;                         //清完成标志
    res = (ADC_RES << 8) | ADC_RESL;            //读取ADC结果

    return res;
}

int adc_read(u8 adc_pin, u16 *adc_value)
{
    u8 i;
    int res = 0;
    for(i=0; i<8; i++){
        res += adc_read_once(adc_pin, adc_value);
    }
    res >>= 3;
    return res;
}