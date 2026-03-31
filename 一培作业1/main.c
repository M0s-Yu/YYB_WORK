#include <REGX52.H>
#include <INTRINS.H>
//玉永彬
#define MAX_TASKS 2 //表示有两个任务
#define MAX_TASK_DEP 32 //表示栈的深度

#define TASK_READY   0
#define TASK_SUSPEND 1

unsigned char idata task_sp[MAX_TASKS];                     // 任务的堆栈指针
unsigned char idata task_stack[MAX_TASKS][MAX_TASK_DEP];    // 每个task任务的堆栈
unsigned char task_id;                                      // 当前任务号

unsigned char task_state[MAX_TASKS];                        // 任务状态：0=READY, 1=SUSPEND
unsigned int  task_delay[MAX_TASKS];                        // 任务延时计数器（单位：ms）


void task_switch(void);//提前声明函数原型
void task_switch(void);
void task0(void);
void task1(void);
void task_load(unsigned int fn,unsigned char tid);
void task_suspend(unsigned char tid);
void task_resume(unsigned char tid);
void task_delay_ms(unsigned int ms);
void task_delay_ms(unsigned int ms);


void task_suspend(unsigned char tid)// 任务挂起
{
    if (tid >= MAX_TASKS) return;
    task_state[tid] = TASK_SUSPEND;
    task_delay[tid] = 0;          // 手动挂起不使用定时恢复
}

void task_resume(unsigned char tid)   //恢复任务
{
    if (tid >= MAX_TASKS) return;
    task_state[tid] = TASK_READY;
    task_delay[tid] = 0;
}


void task_delay_ms(unsigned int ms)// 切换的延时
{
    if (ms == 0) return;
    task_delay[task_id] = ms;           // 设置延时计数
    task_state[task_id] = TASK_SUSPEND; // //任务状态设置为挂起
    task_switch();                      // 任务切换
}


void task_switch(void)// 任务切换
{
    task_sp[task_id] = SP;
    do
    {
        task_id++;//任务号置换
        if (task_id >= MAX_TASKS) {task_id = 0;}
    } while (task_state[task_id] == TASK_SUSPEND);//

    SP = task_sp[task_id];//任务存储位置
}


// Timer0 1ms 定时中断（负责所有延时计数）
void Timer0_ISR(void) interrupt 1 // Timer0 的中断号 1
{
    unsigned char i; 

    TH0 = 0xFC;      // 12MHz晶振下 1ms 重载值
    TL0 = 0x18;

    for (i = 0; i <MAX_TASKS; i++)
    {
        if (task_delay[i] > 0)
        {
            task_delay[i]--;
            if (task_delay[i] == 0)
            {
                task_state[i] = TASK_READY;   // 延时结束，自动恢复就绪
            }
        }
    }
}
//中断这里是不是可以加入两个计次函数Count1 2,if次数分别到达500和1000时，执行task并重置Count值，实现类似非阻塞延时亮灯效果

void task_load(unsigned int fn, unsigned char tid)//任务加载
{
    task_stack[tid][1] = (unsigned char)(fn >> 8);
    task_stack[tid][0] = (unsigned char)fn;
    task_sp[tid] = (unsigned char)&task_stack[tid][1];
}

//========================================================亮灯修改成了51单片机对应的两个灯
void task0(void)//任务0：0.5秒闪烁
{
    P2_0 = 0;
    while (1)
    {
        P2_0 = ~P2_0;
        task_delay_ms(500);   // 挂起式延时，任务切换
    }
}


void task1(void)//任务1：1秒闪烁
{
    P2_1 = 0;
    while (1)
    {
        P2_1 = ~P2_1;
        task_delay_ms(1000);  // 挂起式延时，符合任务切换
    }
}


void main(void)//主函数
{
    // 加载两个任务
    task_load((unsigned int)task0, 0);
    task_load((unsigned int)task1, 1);

    // 初始化任务状态和延时计数器
    task_state[0] = TASK_READY;
    task_state[1] = TASK_READY;
    task_delay[0] = 0;
    task_delay[1] = 0;

    task_id = 0;

    // 初始化 Timer0 为 1ms 定时中断（实现精确延时）
    TMOD = 0x01;        // Timer0模式1（16位）
    TH0 = 0xFC;
    TL0 = 0x18;
    TR0 = 1;            // 启动定时器
    ET0 = 1;            // 允许 Timer0 中断
    EA  = 1;            // 全局中断允许

    // 切换到任务0的栈并启动多任务
    SP = task_sp[0];
}
