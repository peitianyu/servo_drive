#ifndef __ICR_H__
#define __ICR_H__

#include "config.h"

#define internal_irc_init()  do {               \
    P_SW2 = 0x80;                               \
    CLKSEL = 0x00;                              \
    P_SW2 = 0x00;                               \
} while (0)

#endif // __ICR_H__