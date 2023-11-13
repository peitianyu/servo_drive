#ifndef __GPIO_H__
#define __GPIO_H__

#include "config.h"

#define	GPIO_PullUp		0	    //上拉准双向口
#define	GPIO_HighZ		1	    //浮空输入
#define	GPIO_OUT_OD		2	    //开漏输出
#define	GPIO_OUT_PP		3	    //推挽输出

enum PinValue
{
    Pin_Low = 0,
    Pin_High = 1
};

#define gpio_init(GPIO, pin_id, Mode)	do														\			
{	                                                                                            \
    u8 Pin = 1 << pin_id;																		\		
	if(GPIO > 7)		 	break;															    \
	if(Mode > GPIO_OUT_PP)	break;															    \
	if(Mode == GPIO_PullUp)		P##GPIO##M1 &= ~Pin,	P##GPIO##M0 &= ~Pin;					\
	if(Mode == GPIO_HighZ)		P##GPIO##M1 |=  Pin,	P##GPIO##M0 &= ~Pin;	 				\
	if(Mode == GPIO_OUT_OD)		P##GPIO##M1 |=  Pin,	P##GPIO##M0 |=  Pin;					\
	if(Mode == GPIO_OUT_PP)		P##GPIO##M1 &= ~Pin,	P##GPIO##M0 |=  Pin;	 				\
}while(0)

#define gpio_init_allpin(GPIO, Mode) 			do 												\
{																								\
	if(GPIO > 7)		 	break;																\
	if(Mode > GPIO_OUT_PP)	break;																\
	if(Mode == GPIO_PullUp)		P##GPIO##M1 = 0x00,	P##GPIO##M0 = 0x00;							\
	if(Mode == GPIO_HighZ)		P##GPIO##M1 = 0xFF,	P##GPIO##M0 = 0x00;	 						\
	if(Mode == GPIO_OUT_OD)		P##GPIO##M1 = 0xFF,	P##GPIO##M0 = 0xFF;							\
	if(Mode == GPIO_OUT_PP)		P##GPIO##M1 = 0x00,	P##GPIO##M0 = 0xFF;	 						\
}while(0)

#define gpio_set(Pin, Value)		    (Pin = Value)
#define gpio_toggle(Pin)				(Pin = ~Pin)
#define gpio_get(Pin)					(Pin)

#endif // __GPIO_H__