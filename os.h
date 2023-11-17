#ifndef __OS_H__
#define __OS_H__

#include "config.h"

#define TASKS_MAX 4

void os_timer0_init(void);  // 100us

void add_task(u8 run, u16 timer, u16 itv_time, void (*task_hook)(void)); // 初始状态, 计时器, 运行间隔(100us), 任务函数

void task_process(void);

void task_remark(void);

#endif // __OS_H__