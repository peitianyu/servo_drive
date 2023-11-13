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
#include "lib/delay.h"
#include "lib/uart.h"
#include "lib/pwm.h"
#include "lib/i2c.h"
#include "lib/os.h"
#include "lib/adc.h"

void i2c_task(void);
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

void i2c_task(void)
{
	i2c_write_date(0x50, 0x00, "Hello World!", 1);
}

void led_blink(void)
{
	gpio_toggle(P54);
}

void adc_task(void)
{
	int adc_value;
	adc_value = adc_read();
	print("ADC: %d\r\n", adc_value);
}

void system_init(void)
{
	gpio_init_allpin(3, GPIO_OUT_PP);
	gpio_init_allpin(5, GPIO_OUT_PP);
	pwm_init(3, 1, 20000, 1000);
	pwm_init(3, 0, 20000, 20000-1000);
	i2c_slave_init(I2C_P33_P32, 0x50, 0);
	uart1_init();

	gpio_init(5, 5, GPIO_HighZ);			// ADC
	adc_init(ADC_Pin55);

	os_timer0_init();
	add_task(0, 0, 10, i2c_task);
	add_task(0, 1, 10, adc_task);
	add_task(0, 3, 500, led_blink);
	
	delay_ms(1000);
	print("Hello World!\r\n");
}





