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
#include "lib/pwm.h"
#include "lib/os.h"

void pwm_task(void);
void system_init(void);

void main(void)
{
	void system_init();

	while(1)
	{
		task_process();
	}
}

void pwm_task(void)
{
	pwm_set(P31, 2000);
	pwm_set(P30, 5000);
}

void system_init(void)
{
	gpio_init_allpin(3, GPIO_OUT_PP);
	pwm_init(3, 1, 20000, 1000);
	pwm_init(3, 0, 20000, 20000-1000);

	os_timer0_init();
	add_task(0, 0, 10, pwm_task);
}





