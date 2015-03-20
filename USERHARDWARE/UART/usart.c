#include "usart.h"
#include <stdarg.h>

/*
 * ��������USART1_Config
 * ����  ��USART1 GPIO ����,����ģʽ���á�115200 8-N-1
 * ����  ����
 * ���  : ��
 * ����  ���ⲿ����
 */
void USART1_Config(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    USART_InitTypeDef USART_InitStructure;

    /* config USART1 clock */
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1 | RCC_APB2Periph_GPIOA, ENABLE);

    /* USART1 GPIO config */
    /* Configure USART1 Tx (PA.09) as alternate function push-pull */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
    /* Configure USART1 Rx (PA.10) as input floating */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    /* USART1 mode config */
    USART_InitStructure.USART_BaudRate = 115200;    //���ò�ͬ�Ĳ�����
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_Parity = USART_Parity_No ;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
    USART_Init(USART1, &USART_InitStructure);
    USART_Cmd(USART1, ENABLE);
}



void USART3_Config(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    USART_InitTypeDef USART_InitStructure;

    /* config USART2 clock */
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);

    /* USART2 GPIO config */
    /* Configure USART2 Tx (PA.02) as alternate function push-pull */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_InitStructure);

    /* Configure USART2 Rx (PA.03) as input floating */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIOB, &GPIO_InitStructure);

    /* USART2 mode config */
    USART_InitStructure.USART_BaudRate = 115200;
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_Parity = USART_Parity_No ;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;

    USART_Init(USART3, &USART_InitStructure);
    USART_Cmd(USART3, ENABLE);
}

/*
 * ��������fputc
 * ����  ���ض���c�⺯��printf��USART1
 * ����  ����
 * ���  ����
 * ����  ����printf����
 */
int fputc(int ch, FILE *f)
{
    /* ��Printf���ݷ������� */
    USART_SendData(USART2, (unsigned char) ch);
    while (!(USART2->SR & USART_FLAG_TXE));

    return (ch);
}

/*
 * ��������itoa
 * ����  ������������ת�����ַ���
 * ����  ��-radix =10 ��ʾ10���ƣ��������Ϊ0
 *         -value Ҫת����������
 *         -buf ת������ַ���
 *         -radix = 10
 * ���  ����
 * ����  ����
 * ����  ����USART1_printf()����
 */
static char *itoa(int value, char *string, int radix)
{
    int     i, d;
    int     flag = 0;
    char    *ptr = string;

    /* This implementation only works for decimal numbers. */    //��������10��������
    if (radix != 10)
    {
        *ptr = 0;
        return string;
    }

    if (!value)
    {
        *ptr++ = 0x30;
        *ptr = 0;
        return string;
    }

    /* if this is a negative value insert the minus sign. */
    if (value < 0)
    {
        *ptr++ = '-';

        /* Make the value positive. */
        value *= -1;
    }

    for (i = 10000; i > 0; i /= 10)
    {
        d = value / i;

        if (d || flag)
        {
            *ptr++ = (char)(d + 0x30);
            value -= (d * i);
            flag = 1;
        }
    }

    /* Null terminate the string. */
    *ptr = 0;

    return string;

} /* NCL_Itoa */

/*
 * ��������USART1_printf
 * ����  ����ʽ�������������C���е�printf��������û���õ�C��
 * ����  ��-USARTx ����ͨ��������ֻ�õ��˴���1����USART1
 *           -Data   Ҫ���͵����ڵ����ݵ�ָ��
 *             -...    ��������
 * ���  ����
 * ����  ����
 * ����  ���ⲿ����
 *         ����Ӧ��USART1_printf( USART1, "\r\n this is a demo \r\n" );
 *                   USART1_printf( USART1, "\r\n %d \r\n", i );
 *                   USART1_printf( USART1, "\r\n %s \r\n", j );
 */
void USART_printf(USART_TypeDef *USARTx, uint8_t *Data, ...)
{
    const char *s;
    int d;
    char buf[16];

    va_list ap;
    va_start(ap, Data);

 while ( *Data != 0xFF&&*Data+1!= 0xFC)     // �ж��Ƿ񵽴��ַ���������
    {
//        if ( *Data == 0x5c )  //'\'
//        {
//            switch ( *++Data )
//            {
//            case 'r':                                     //�س���
//                USART_SendData(USARTx, 0x0d);
//                Data ++;
//                break;

//            case 'n':                                     //���з�
//                USART_SendData(USARTx, 0x0a);
//                Data ++;
//                break;

//            default:
//                Data ++;
//                break;
//            }
//        }
//        else if ( *Data == '%')
//        {
//            //
//            switch ( *++Data )
//            {
//            case 's':                                         //�ַ���
//                s = va_arg(ap, const char *);
//                for ( ; *s; s++)
//                {
//                    USART_SendData(USARTx, *s);
//                    while ( USART_GetFlagStatus(USARTx, USART_FLAG_TC) == RESET );
//                }
//                Data++;
//                break;

//            case 'd':                                       //ʮ����
//                d = va_arg(ap, int);
//                itoa(d, buf, 10);
//                for (s = buf; *s; s++)
//                {
//                    USART_SendData(USARTx, *s);
//                    while ( USART_GetFlagStatus(USARTx, USART_FLAG_TC) == RESET );
//                }
//                Data++;
//                break;
//            default:
//                Data++;
//                break;
//            }
//        } /* end of else if */
       // else USART_SendData(USARTx, *Data);
	 USART_SendData(USARTx, *Data);
				Data++;
        while ( USART_GetFlagStatus(USARTx, USART_FLAG_TC) == RESET );
    }
		
}


void NVIC_Configuration(void)
{


	NVIC_InitTypeDef NVIC_InitStructure; 
	/* Configure the NVIC Preemption Priority Bits */  
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);
	
	/* Enable the USARTy Interrupt */
	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;	 
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

    USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);//�����ж�
	
	
		NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;	 
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

    USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);//�����ж�

}

