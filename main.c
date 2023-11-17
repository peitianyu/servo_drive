/*
gpio 	ok
uart 	ok
timer 	ok
pwm		ok
adc		no
i2c		no
*/

/*****************************************************************************************
 *   Pin connection:              
 *                 ___
 * LED  ->  P5.4 -|   |- P3.3  SCL
 * 5.0V ->   VCC -|   |- P3.2  SDA
 *  ADC ->  P5.5 -|   |- P3.1  PWM1
 *  GND ->   GND -|___|- P3.0  PWM0
 *   test-MCU: STC8G1K08A
 * P54 : SCL_2
 * P55 : SDA_2
 * P33 : PWM1
 * P32 : PWM0
 * P31 : ADC1
 * P30 : ADC0
 *****************************************************************************************/

#include "gpio.h"
#include "delay.h"
#include "pwm.h"
#include "timer.h"
#include "uart.h"
#include "adc.h"

void main()
{
	gpio_init(3, 2, GPIO_PullUp);
	gpio_init(3, 3, GPIO_PullUp);
	gpio_init(5, 5, GPIO_HighZ);
	
	timer0_init(50000);  // 50kHz
    uart1_init();
	
	adc_init();

	pwm_10bit_init(0, 20);
    
	while(TRUE)
    {
        delay_ms(1000);
		
        print("adc : %d\r\n", adc_get(ADC_Pin55));
    }
}
