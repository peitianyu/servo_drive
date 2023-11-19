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
#include "os.h"

void led_task(void)
{
	gpio_toggle(P54);
}

void print_adc(void)
{
	u16 adc_val = adc_get(5);
	print("adc_val: %d\r\n", adc_val);
}

u16 pwm_val = 0.02 * 1024;
void main()
{
	gpio_init(3, 2, GPIO_PullUp);
	gpio_init(3, 3, GPIO_PullUp);
	gpio_init(5, 5, GPIO_HighZ);
	gpio_init(5, 4, GPIO_PullUp);

	
	timer_init(0, 50000); // 50kHz
	uart1_init();
    
	adc_init();

	pwm_10bit_init(0, pwm_val); // 选择定时器0溢出为pwm发生源

	add_task(0, 0, 1000, led_task);
	add_task(1, 100, 1000, print_adc);
    
	while(TRUE)
    {
		task_process();
    }
}
