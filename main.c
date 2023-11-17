/*******************************************
 *   test-MCU: STC8G1K08A             
 *                  ___
 * SCL_2 ->  P5.4 -|   |- P3.3  PWM1
 *  5.0V ->   VCC -|   |- P3.2  PWM0
 * SDA_2 ->  P5.5 -|   |- P3.1  ADC1
 *   GND ->   GND -|___|- P3.0  ADC0
 *   
 *******************************************/

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
	
	timer_init(0, 50000); // 50kHz
    uart1_init();
	
	adc_init();

	pwm_10bit_init(0, 20);
    
	while(TRUE)
    {
        delay_ms(1000);
		
        print("adc : %d\r\n", adc_get(5));
    }
}
