/*****************************************************************************************
 *   Pin connection:              
 *                 ___
 * LED  ->  P5.4 -|   |- P3.3  SCL
 * 5.0V ->   VCC -|   |- P3.2  SDA
 *  ADC ->  P5.5 -|   |- P3.1  PWM1
 *  GND ->   GND -|___|- P3.0  PWM0
 *   test-MCU: STC8G1K08A
 * P54 : BOOT
 * P55 : ADC
 * P33 : SCL
 * P32 : SDA
 * P31 : PWM1/Tx
 * P30 : PWM0/Rx
 *****************************************************************************************/

#include "lib/gpio.h"
#include "lib/os.h"

void led_blink(void);
void system_init(void);

void main(void)
{
	void system_init();

	while(1)
	{
		task_process();
	}
}


void led_blink(void)
{
	gpio_toggle(P54);
}

void system_init(void)
{
	gpio_init_allpin(5, GPIO_OUT_PP);

	os_timer0_init();
	add_task(1, 0, 500, led_blink);
}





