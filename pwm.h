#ifndef __PWM_H__
#define __PWM_H__

#include "config.h"

// id : p32(0) p33(1) p54(2)
#define pwm_10bit_init(id, pwm_val)     do              \
{                                                       \
    CCON = 0x00;                                        \
    CMOD = 0x84;                                        \                                
    CL = 0x00;                                          \									
    CH = 0x00;                                          \
                                                        \	
    CCAPM##id = 0x42;                                   \
    PCA_PWM##id = 0xc0;                                 \
    PCA_PWM##id |= ((pwm_val >> 8) << 4);               \
    CCAP##id##H = (u8)pwm_val;                          \
                                                        \
    CR = 1;                                             \								
} while(0)  

#define pwm_set(id, pwm_val)    do                      \
{                                                       \
    PCA_PWM##id |= ((pwm_val >> 8) << 4);               \
    CCAP##id##H = (u8)pwm_val;                          \
} while(0)

#endif // __PWM_H__