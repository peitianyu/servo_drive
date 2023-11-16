#include "os.h"

typedef struct{
    u8 m_id;                                /*!< 任务ID */
    u8 m_run;                               /*!< 程序运行标记：0-不运行，1运行 */
    u16 m_timer;                            /*!< 计时器 */
    u16 m_itv_time;                         /*!< 任务运行间隔时间 */
    void (*m_task_hook)(void);              /*!< 要运行的任务函数 */
} TASK_InfoType;                            /*!< 任务信息结构体 */   

static TASK_InfoType g_task_info[TASKS_MAX] = {0};  /*!< 任务信息数组 */

void add_task(u8 id, u16 timer, u16 itv_time, void (*task_hook)(void))
{
    if(id > TASKS_MAX)
        return;

    g_task_info[id].m_id = id;
    g_task_info[id].m_run = 0;
    g_task_info[id].m_timer = timer;
    g_task_info[id].m_itv_time = itv_time;
    g_task_info[id].m_task_hook = task_hook;
}

void task_remark(void)
{
	u8 i = TASKS_MAX;
    while(i--)
    {
        if(g_task_info[i].m_timer){
            g_task_info[i].m_timer--;

            if(g_task_info[i].m_timer == 0){
                g_task_info[i].m_timer = g_task_info[i].m_itv_time; 
                g_task_info[i].m_run = 1;
            }
        }
    }
}

void task_process(void)
{ 
    u8 i = TASKS_MAX;
    while(i--)
    {
        if (!g_task_info[i].m_run) continue;

        print("task %d run \r\n", i);
        g_task_info[i].m_task_hook();           // 运行任务
        g_task_info[i].m_run = 0;               // 标志清0
    }   
}


void os_timer0_init(void)    //100us@24MHz
{
	AUXR |= 0x80;  // 定时器0 1T模式
    TMOD = 0x00;   // 定时器模式0 16位自动重载模式
    TL0 = 0xA0;	   // 设置定时初始值
	TH0 = 0xF6;	   // 设置定时初始值
    TR0 = 1;       // 定时器开始计时
    ET0 = 1;       // 使能定时器1中断
    EA  = 1;       // 打开总中断
}

void os_irq() interrupt 1
{
    task_remark();
}
