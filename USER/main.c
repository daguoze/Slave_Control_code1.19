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
//	module_discriminate();
	//module_config();

	relay_all = 0;
	relay_splithex(0xff);

	relay_all = 1;




	while (1)
	{

		//
		//         USART_printf(USART1, master_send);

		if (key1 == 0 || key2 == 0 || key3 == 0)
			PCout(9) = 1;
		command_handle();

	}
}


/******************* (C) COPYRIGHT 2015 Shell Era  *****END OF FILE************/


