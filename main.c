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

/*
#include "gpio.h"
#include "delay.h"
#include "uart.h"

#if 0
#include "i2c_master.h"

u8 table[5] = {0x00, 0x23, 0x45, 0x67, 0x32};
u8 p[10];
u8 cnt = 0;
void main()
{
	gpio_init(3, 2, GPIO_OUT_OD);
	gpio_init(3, 3, GPIO_OUT_OD);

    i2c_master_init(I2C_P33_P32);
	uart1_init();
	
    while (1)
	{                                 
		table[0] = cnt++;

        i2c_master_send_datas(0x5a, 0x00, table, 5);
		
		delay_ms(1000); 							//发送停止命令
		
		i2c_master_recv(0x5a, 0x00, p, 5);
		uart1_send_array(p, 5);
    }
}

#else

#include "i2c_slave.h"

void main()
{
    gpio_init(3, 2, GPIO_PullUp);
	gpio_init(3, 3, GPIO_PullUp);
	
	i2c_slave_init(I2C_P33_P32, 0x5a);
	
	uart1_init();

    while(1)
    {
        delay_ms(1500);
        uart1_send_array(i2c_slave_get(), 5);

        i2c_slave_set(i2c_slave_get(), 5);
    }
}

#endif 
*/
