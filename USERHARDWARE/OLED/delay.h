#ifndef _DELAY_H_
#define _DELAY_H_

#include<stm32f10x.h>
#include<stm32f10x_rcc.h>
#include<system_stm32f10x.h>

//注意nms的范围
//SysTick->LOAD为24位寄存器，所以，最大延时:
//nms<=0xffffff*8*1000/SYSCLK
//SYSCLK单位为Hz,nms单位为ms
//对72M条件下,经过8分频，SysTick的时钟频率为9MHz
//计算得出:nms<=1864

void delay_ms(uint32_t nms)
{
    uint32_t temp;
    SysTick->LOAD = 9000 * nms;
    SysTick->VAL = 0x00; //清空计数器
    SysTick->CTRL = 0x01; //使能，减到零时无动作，采用外部时钟源
    do
    {
        temp = SysTick->CTRL; //读取当前倒计时值
    }
    while (temp & 0x01 && !(temp & (1 << 16))); //等待时间到达，CTRL寄存器第16位
    SysTick->CTRL = 0x00; //关闭计数器
    SysTick->VAL = 0x00; //清空计数器
}

void delay_us(uint32_t nus)
{
    uint32_t temp;
    SysTick->LOAD = 9 * nus;
    SysTick->VAL = 0x00; //清空计数器
    SysTick->CTRL = 0x01; //使能，减到零时无动作，采用外部时钟源
    do
    {
        temp = SysTick->CTRL; //读取当前倒计时值
    }
    while (temp & 0x01 && !(temp & (1 << 16))); //等待时间到达
    SysTick->CTRL = 0x00; //关闭计数器
    SysTick->VAL = 0x00; //清空计数器
}

#endif
