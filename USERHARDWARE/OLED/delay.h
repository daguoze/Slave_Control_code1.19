#ifndef _DELAY_H_
#define _DELAY_H_

#include<stm32f10x.h>
#include<stm32f10x_rcc.h>
#include<system_stm32f10x.h>

//ע��nms�ķ�Χ
//SysTick->LOADΪ24λ�Ĵ��������ԣ������ʱ:
//nms<=0xffffff*8*1000/SYSCLK
//SYSCLK��λΪHz,nms��λΪms
//��72M������,����8��Ƶ��SysTick��ʱ��Ƶ��Ϊ9MHz
//����ó�:nms<=1864

void delay_ms(uint32_t nms)
{
    uint32_t temp;
    SysTick->LOAD = 9000 * nms;
    SysTick->VAL = 0x00; //��ռ�����
    SysTick->CTRL = 0x01; //ʹ�ܣ�������ʱ�޶����������ⲿʱ��Դ
    do
    {
        temp = SysTick->CTRL; //��ȡ��ǰ����ʱֵ
    }
    while (temp & 0x01 && !(temp & (1 << 16))); //�ȴ�ʱ�䵽�CTRL�Ĵ�����16λ
    SysTick->CTRL = 0x00; //�رռ�����
    SysTick->VAL = 0x00; //��ռ�����
}

void delay_us(uint32_t nus)
{
    uint32_t temp;
    SysTick->LOAD = 9 * nus;
    SysTick->VAL = 0x00; //��ռ�����
    SysTick->CTRL = 0x01; //ʹ�ܣ�������ʱ�޶����������ⲿʱ��Դ
    do
    {
        temp = SysTick->CTRL; //��ȡ��ǰ����ʱֵ
    }
    while (temp & 0x01 && !(temp & (1 << 16))); //�ȴ�ʱ�䵽��
    SysTick->CTRL = 0x00; //�رռ�����
    SysTick->VAL = 0x00; //��ռ�����
}

#endif
