#ifndef __ADC_H__
#define __ADC_H__

#include "config.h"

#define ADC_Pin30     0
#define ADC_Pin31     1
#define ADC_Pin32     2
#define ADC_Pin33     3
#define ADC_Pin54     4
#define ADC_Pin55     5

void adc_init();

u16 adc_get(u8 adc_id);

#endif // __ADC_H__