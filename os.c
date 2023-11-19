#include "os.h"

typedef struct{
    u8 m_id;                                /*!< 任务ID */
    u8 m_run;                               /*!< 程序运行标记：0-不运行，1运行 */
    u16 m_timer;                            /*!< 计时器 */
    u16 m_itv_time;                         /*!< 任务运行间隔时间 */
    void (*m_task_hook)(void);              /*!< 要运行的任务函数 */
} TASK_InfoType;                            /*!< 任务信息结构体 */   

static TASK_InfoType g_task_info[TASKS_MAX] = {0};  /*!< 任务信息数组 */

static u8 g_task_num = 0;                   /*!< 任务数量 */
void add_task(u8 id, u16 timer, u16 itv_time, void (*task_hook)(void))
{
    if(id > TASKS_MAX)
        return;

    g_task_info[id].m_id = id;
    g_task_info[id].m_run = 0;
    g_task_info[id].m_timer = timer;
    g_task_info[id].m_itv_time = itv_time;
    g_task_info[id].m_task_hook = task_hook;

    g_task_num++;
}

void task_remark(void)
{
	u8 i = g_task_num;
    while(i--)
    {
        if(g_task_info[i].m_timer-- == 0){
            g_task_info[i].m_timer = g_task_info[i].m_itv_time; 
            g_task_info[i].m_run = 1;
        }
    }
}

void task_process(void)
{ 
    u8 i = g_task_num;
    while(i--)
    {
        if (!g_task_info[i].m_run) continue;

        g_task_info[i].m_task_hook();           // 运行任务
        g_task_info[i].m_run = 0;               // 标志清0
    }   
}

// 1ms = 20us * 50
void os_irq() interrupt 1
{
    static u8 s_cnt = 0;
    if(++s_cnt >= 50){
        s_cnt = 0;
        task_remark();
    }
}
