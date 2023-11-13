#ifndef __PWM_H__
#define __PWM_H__

#include "config.h"

#define PWMCKS(x) PWM##x##CKS
#define PWMC(x) PWM##x##C
#define PWMT1(x, y) PWM##x##y##T1
#define PWMT2(x, y) PWM##x##y##T2
#define PWMCR(x, y) PWM##x##y##CR

#define pwm_init(GPIO, Pin, Period, Duty) do        \
{                                                   \
    P_SW2 |= 0x80;                                  \
    PWMSET = 1<<GPIO;                               \
                                                    \
    PWMCKS(GPIO) = MAIN_Fosc / (8 * Period);        \
    PWMC(GPIO) = Period-1;                          \
                                                    \
    PWMT1(GPIO, Pin) = 0;                           \
    PWMT2(GPIO, Pin) = Duty;                        \
    PWMCR(GPIO, Pin) = 0x80;                        \
                                                    \
    if(GPIO < 2) PWMCFG01 = 0x01;                   \
    else if(GPIO < 4) PWMCFG23 = 0x01;              \
    else if(GPIO < 6) PWMCFG45 = 0x01;              \
} while (0)

#define pwm_set(Pin, Duty) do                      \
{                                                  \
    PWMT2(GPIO, Pin) = Duty;                       \
} while (0)

#endif // __PWM_H__