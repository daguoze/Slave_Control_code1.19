/******************** (C) COPYRIGHT 2015 Shell Era **************************
 * ¿â°æ±¾  £ºST3.5.0
 *
 * ×÷Õß    £ºGuo Zeyu
 **********************************************************************************/
#include "stm32f10x.h"
#include "init.h"



int main(void)
{
	init_all();
	module_discriminate();
	module_config();

	relay_all = 0;
	relay_splithex(0x00);

	relay_all = 1;

	delay_ms(200);

	relay_all = 0;
	while (1)
	{

//			relay_splithex(0x80);
//		  delay_ms(200);
//			relay_splithex(0x40);
//		  delay_ms(200);
//			relay_splithex(0x20);
//		  delay_ms(200);
//			relay_splithex(0x10);
//		  delay_ms(200);
//					relay_splithex(0x08);
//		  delay_ms(200);
//			relay_splithex(0x04);
//		  delay_ms(200);
//			relay_splithex(0x02);
//		  delay_ms(200);
//			relay_splithex(0x01);
//		  delay_ms(200);
//
//
//		//
//		//         USART_printf(USART1, master_send);

		if (key1 == 0 || key2 == 0 || key3 == 0)
			PCout(9) = 1;
		else
			PCout(9) = 01;
		command_handle();

	}
}


/******************* (C) COPYRIGHT 2015 Shell Era  *****END OF FILE************/


