#include "stm32f10x.h"
//#include "init.h"

u8 temp_cnt;
u8 recive_temp[10];//ָ����մ����
u8 recive_command[3];//ָ����ȡ
u8 temp_char[10];//�ַ���ת����
u8 handle_flag = 0; //�����־λ




void USART3_IRQHandler(void)                    //����3�жϷ������
{
    u8 Res;
    u8 i;

    if (USART_GetITStatus(USART3, USART_IT_RXNE) != RESET) //�����ж�(���յ������ݱ�����0x0d 0x0a��β)
    {
        Res = USART_ReceiveData(USART3); //(USART1->DR);  //��ȡ���յ�������
        //      USART_SendData(USART1, Res);
        recive_temp[temp_cnt] = (u8)Res;

        if (recive_temp[temp_cnt] == 0xAA)
        {
            if (recive_temp[temp_cnt - 1] == 0XCC)
            {
                recive_command[2] = recive_temp[temp_cnt - 2];
                recive_command[1] = recive_temp[temp_cnt - 3];
                recive_command[0] = recive_temp[temp_cnt - 4];

                temp_cnt = 0;
            }

        }
        temp_cnt++;
    }

}


void USART1_IRQHandler(void)                    //����1�жϷ������
{
    u8 Res;
    //    u8 i;

    if (USART_GetITStatus(USART1, USART_IT_RXNE) != RESET) //�����ж�(���յ������ݱ�����0x0d 0x0a��β)
    {
        Res = USART_ReceiveData(USART1); //(USART1->DR);  //��ȡ���յ�������
        //      USART_SendData(USART1, Res);
        recive_temp[temp_cnt] = (u8)Res;

        if (recive_temp[temp_cnt] == 0xAA)
        {
            if (recive_temp[temp_cnt - 1] == 0XCC)
            {
                recive_command[2] = recive_temp[temp_cnt - 2];
                recive_command[1] = recive_temp[temp_cnt - 3];
                recive_command[0] = recive_temp[temp_cnt - 4];

                handle_flag = 1;
                temp_cnt = 0;
            }

        }
        temp_cnt++;
    }

}