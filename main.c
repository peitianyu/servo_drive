/*******************************************
 *   test-MCU: STC8G1K08A             
 *                  ___
 * SCL_2 ->  P5.4 -|   |- P3.3  PWM1
 *  5.0V ->   VCC -|   |- P3.2  PWM0
 * SDA_2 ->  P5.5 -|   |- P3.1  ADC1
 *   GND ->   GND -|___|- P3.0  ADC0
 *   
 *******************************************/
//	注意串口下发时以ff aa作为判断结尾
//|---------------------------------------------------------------------------------------------|
//|  		I2C指令       	|           主机下发                	|           从机上传         	|
//| 指令格式         		| CMD(1byte) 	| DATA[4byte]   	| CMD(1byte) 	| DATA[4byte]	|
//|-------------------------|---------------|-------------------|---------------|---------------|
//| 设置角度, 不保存    		| 0x01       	| 角度float       	| 0x20       	| 当前角度float 	|
//| 设置速度, 不保存    		| 0x02       	| 速度float       	| 0x22       	| 当前速度float 	|
//| 设置转矩, 不保存    		| 0x03       	| 转矩设置(0, 1.0f) 	| 0x20       	| 当前角度float 	|
//| 读取角度         		| 0x11       	| 无             	| 0x20       	| 当前角度float 	|
//| 读取速度         		| 0x12       	| 无             	| 0x22       	| 当前速度float 	|
//| 设置ID, 保存参数   		| 0x21       	| ID[1byte]     	| 0x21       	| 0或1[1byte]   |
//| 设置KP, 保存参数   		| 0x22       	| 比例系数float     	| 0x20       	| 当前角度float 	|
//| 设置KI, 保存参数   		| 0x23       	| 位置环积分float   	| 0x20       	| 当前角度float 	|
//| 设置KV, 保存参数   		| 0x24       	| 速度环积分float   	| 0x20       	| 当前角度float 	|
//| 设置KD, 保存参数   		| 0x25       	| 微分系数float     	| 0x20       	| 当前角度float 	|
//| 设置转矩, 保存参数   	| 0x26       	| 转矩限制float     	| 0x20       	| 当前角度float 	|
//| 设置初始角度, 保存参数 	| 0x27       	| 初始角度float     	| 0x20       	| 当前角度float 	|
//| 使能/失能舵机      		| 0x55       	| 0或1[1byte]       | 0x55       	| 无			|
//|---------------------------------------------------------------------------------------------|
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
	print("%d\r\n", adc_val);
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
	add_task(1, 0, 1, print_adc);
    
	while(TRUE)
    {
		task_process();
    }
}


/*

#include "gpio.h"
#include "delay.h"
#include "uart.h"
#include "config.h"

#if 1
#include "i2c_master.h"

u8 p[5];
u8 cnt = 0;
void main()
{
	gpio_init(3, 2, GPIO_OUT_OD);
	gpio_init(3, 3, GPIO_OUT_OD);

    i2c_master_init(I2C_P33_P32);
	uart1_init();
	
    while (1)
	{                                 
        i2c_master_send_datas(0x5a, 0x00, uart1_get(), 5);
		
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
