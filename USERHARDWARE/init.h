#ifndef _INIT_H_
#define _INIT_H_

#include "GPIO.h"
#include "tempad.h"
#include "stdio.h"
#include "usart.h"
#include "sys.h"
#include "delay.h"

/* ADC1ת���ĵ�ѹֵͨ��MDA��ʽ����sram*/
extern __IO u16 ADC_ConvertedValue;
u16 Current_Temp;
u8 char_temp[16];
//#include "delay.h"
/*
 * ��������main
 * ����  : ������
 * ����  ����
 * ���  : ��
 */

#define beep PAout(8)

#define key1 PCin(10)
#define key2 PCin(11)
#define key3 PCin(12)

#define relay0 PCout(9)
#define relay1 PCout(8)
#define relay2 PCout(7)
#define relay3 PCout(6)
#define relay4 PBout(15)
#define relay5 PBout(14)
#define relay6 PBout(13)
#define relay7 PBout(12)
#define relay_all PBout(1)

#define sel0 PDin(2)
#define sel1 PBin(3)
#define sel2 PBin(4)
#define sel3 PBin(5)
#define sel4 PBin(6)
#define sel5 PBin(7)
#define sel6 PBin(8)
#define sel7 PBin(9)

u8 module_flag = 0; //����ģʽ״̬  0�ӻ�  1 ����
u8 gethex()
{
    u8 address;
    address = PDin(2) << 7 | PBin(3) << 6 | PBin(4) << 5 | PBin(5) << 4 | PBin(6) << 3 | PBin(7) << 2 | PBin(8) << 1 | PBin(9);
    return address;
}
void relay_splithex(u8 hex)
{
    relay0 = relay1 = relay2 = relay3 = relay4 = relay5 = relay6 = relay7 = 0;
    relay0 = (hex & 0x80) >> 7;
    relay1 = (hex & 0x40) >> 6;
    relay2 = (hex & 0x20) >> 5;
    relay3 = (hex & 0x10) >> 4;
    relay4 = (hex & 0x08) >> 3;
    relay5 = (hex & 0x04) >> 2;
    relay6 = (hex & 0x02) >> 1;
    relay7 = (hex & 0x01);
}

//��λ
//+  +  +  +  +  +  +  +
//0  0  0 2h |    
//   0  1 4h |    PHY
//   1  0 6h |  ADDRESS
//   1  1 8h |
struct socket_type{
u8 address;
u8 hole_type;
	u8 select_array[8][2];

}get_sockettype;

void module_discriminate()
{
	
// struct socket_type  get_sockettype;

	get_sockettype.address= gethex();
	get_sockettype.address=get_sockettype.address<<4;
    if (get_sockettype.address==0x00)//��Ե�ַ
    {
        beep = 1;
        delay_ms(100);
        beep = 0;
        delay_ms(100);
        beep = 1;
        delay_ms(100);
        beep = 0;
        module_flag = 1;
    }//����ģʽ
    else
    {
   //   combinechar=  gethex();
	
			beep = 1;
        delay_ms(100);
        beep = 0;
        module_flag = 0;//�ӻ�ģʽ
    }
				get_sockettype.hole_type= PBin(3) << 1 | PBin(4) ;
		

}



void NVIC_init()



{

	NVIC_InitTypeDef NVIC_InitStructure; 
		TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1,ENABLE); 
		TIM_DeInit(TIM1);
	  TIM_TimeBaseStructure.TIM_Period=1000;		 								/* �Զ���װ�ؼĴ������ڵ�ֵ(����ֵ) */

    TIM_TimeBaseStructure.TIM_Prescaler= (72 - 1);				    /* ʱ��Ԥ��Ƶ�� 72M/72 */
	TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1; //������Ƶ 
	TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up;//������ʽ 
	TIM_TimeBaseStructure.TIM_RepetitionCounter = 0; 
	TIM_TimeBaseInit(TIM1, & TIM_TimeBaseStructure);
	TIM_ClearFlag(TIM1, TIM_FLAG_Update); //�������жϱ�־
	TIM_ITConfig(TIM1,TIM_IT_Update,ENABLE);
	TIM_Cmd(TIM1, ENABLE);	 
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1); 
	NVIC_InitStructure.NVIC_IRQChannel = TIM1_UP_IRQn; //ͨ�� TIM5 
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;//ռ���ȼ� 
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0; //�����ȼ� 
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; 
	NVIC_Init(&NVIC_InitStructure); 	

}
void init_all()
{
//    u16 start_delay = 0;
    SystemInit();
    GPIO_Config();
	NVIC_init();

}
u8 command_send[9] = {0};
u8 master_send[9] = {0};

void module_config()
{
    u16 start_delay;
    if (module_flag == 0) //�ӻ�
    {
        USART3_Config();               //�ز�ͨѶ
        NVIC_Configuration();

        delay_ms(50);
        start_delay = (u16)gethex() * 5;
        if ( start_delay == 0)
            start_delay = 1;
        delay_ms(start_delay);
        delay_ms(start_delay);


        command_send[0] = 0xaa;  //��λ
        command_send[1] = 0x01;  //01 ����״̬   0F ����
        command_send[2] = gethex();
        command_send[3] = 0x11;
        command_send[4] = 0x3c;
        command_send[5] = 0xcc;
        command_send[6] = 0xaa;
        command_send[7] = 0xFF;
        command_send[8] = 0xFC;



        USART_printf(USART3, command_send);

    }

    else //����
    {
        USART1_Config();               //���ڴ���USART1������   �ز���
        USART3_Config();               //�ز�ͨѶ
        NVIC_Configuration();

        delay_ms(50);
        start_delay = (u16)gethex() * 5;
        if ( start_delay == 0)
            start_delay = 1;
        delay_ms(start_delay);
        delay_ms(start_delay);


        command_send[0] = 0xAA;  //��λ
        command_send[1] = 0x03;  //03��ѯ��
        command_send[2] = gethex();
        command_send[3] = 0xBB;
        command_send[4] = 0xBB;
        command_send[5] = 0xcc;
        command_send[6] = 0xaa;
        command_send[7] = 0xFF;
        command_send[8] = 0xFC;

        USART_printf(USART3, command_send);

        master_send[0] = 0xAA;
        master_send[1] = 0x05;  //֪ͨ����,�Ѿ�����
        master_send[2] = gethex();
        master_send[3] = 0xBB;
        master_send[4] = 0xBB;
        master_send[5] = 0xcc;
        master_send[6] = 0xaa;
        master_send[7] = 0xFF;
        master_send[8] = 0xFC;

        USART_printf(USART1, master_send);

    }
}

extern u8 recive_command[3];
extern u8 handle_flag;
void command_handle()
{
    if (handle_flag)
    {
        switch ( recive_command[0])
        {
        case 0x01://��������
            if (recive_command[1] == 0x00) //��������
            {

                USART_SendData(USART1, 0x11);
                delay_us(500);
                USART_SendData(USART1, 0x11);
                delay_us(500);
                USART_SendData(USART1, 0x11);
                delay_us(500);
                USART_SendData(USART1, 0xcc);
                delay_us(500);
                USART_SendData(USART1, 0xaa);
                delay_us(500);

                relay_splithex(recive_command[2]);
                relay_all = 1;
            }
            else
                relay_splithex(00);
            break;

        }
    }

    handle_flag = 0;
}




#endif
