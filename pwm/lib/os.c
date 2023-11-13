#include "os.h"

typedef struct{
    u8 m_run;                               /*!< 程序运行标记：0-不运行，1运行 */
    u16 m_timer;                            /*!< 计时器 */
    u16 m_itv_time;                         /*!< 任务运行间隔时间 */
    void (*m_task_hook)(void);              /*!< 要运行的任务函数 */
} TASK_InfoType;                            /*!< 任务信息结构体 */   

static TASK_InfoType g_task_info[TASKS_MAX];


static u8 g_task_num = 0;                   /*!< 任务数量 */
void add_task(u8 run, u16 timer, u16 itv_time, void (*task_hook)(void))
{
    if(g_task_num >= TASKS_MAX)
        return;

    g_task_info[g_task_num].m_run = run;
    g_task_info[g_task_num].m_timer = timer;
    g_task_info[g_task_num].m_itv_time = itv_time;
    g_task_info[g_task_num].m_task_hook = task_hook;
    g_task_num++;
}

void task_remark(void)
{
	u8 i;
    for ( i = 0; i < g_task_num; i++)
    {
        if(g_task_info[i].m_timer > 0){
            g_task_info[i].m_timer--;
        }else {
            g_task_info[i].m_timer = g_task_info[i].m_itv_time; 
            g_task_info[i].m_run = 1;
        }  
    }
}
 
void task_process(void)
{ 
    u8 i;
    for ( i = 0; i < g_task_num; i++)
    {
        if (!g_task_info[i].m_run) continue;

        g_task_info[i].m_task_hook();           // 运行任务
        g_task_info[i].m_run = 0;               // 标志清0
    }   
}


void os_timer0_init(void)    //100微秒@24.000MHz
{
    AUXR |= 0x80;			//定时器时钟1T模式
	TMOD &= 0xF0;			//设置定时器模式
	TL0 = 0xA0;				//设置定时初始值
	TH0 = 0xF6;				//设置定时初始值
	TF0 = 0;				//清除TF0标志
	TR0 = 1;				//定时器0开始计时
}
 
void os_irq(void) interrupt 1
{
    task_remark();
}