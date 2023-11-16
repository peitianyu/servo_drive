/*****************************************************************************************
 *   Pin connection:              
 *                 ___
 * LED  ->  P5.4 -|   |- P3.3  SCL
 * 5.0V ->   VCC -|   |- P3.2  SDA
 *  ADC ->  P5.5 -|   |- P3.1  PWM1 / TX
 *  GND ->   GND -|___|- P3.0  PWM0 / RX
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
#include "lib/adc.h"
#include "lib/pwm.h"

void system_init(void);

void main(void)
{
	system_init();
	
	while(1)
	{
		delay_ms(1000);
		// gpio_toggle(P54);
		print("hello : %d\r\n", adc_read());
	}
}

void system_init(void)
{
	gpio_init_allpin(3, GPIO_OUT_PP);
    gpio_init_allpin(5, GPIO_OUT_PP);

    uart1_init();

	adc_init(ADC_Pin54);
}

