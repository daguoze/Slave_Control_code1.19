/******************** (C) COPYRIGHT 2015 Shell Era **************************
 * 库版本  ：ST3.5.0
 *
 * 作者    ：Guo Zeyu
 **********************************************************************************/
#include "stm32f10x.h"
#include "init.h"
int g_ms;
void select_port()
{

	switch (get_sockettype.hole_type) //2h
	{
	case 0:
		get_sockettype.select_array[0][0] = 1;
		get_sockettype.select_array[1][0] = 0;
		get_sockettype.select_array[2][0] = 0;
		get_sockettype.select_array[3][0] = 0;

		get_sockettype.select_array[4][0] = 1;
		get_sockettype.select_array[5][0] = 0;
		get_sockettype.select_array[6][0] = 0;
		get_sockettype.select_array[7][0] = 0;
		break;
	case 1:
		get_sockettype.select_array[0][0] = 1;
		get_sockettype.select_array[1][0] = 1;
		get_sockettype.select_array[2][0] = 0;
		get_sockettype.select_array[3][0] = 0;

		get_sockettype.select_array[4][0] = 1;
		get_sockettype.select_array[5][0] = 1;
		get_sockettype.select_array[6][0] = 0;
		get_sockettype.select_array[7][0] = 0;
		break;
	case 2:
		get_sockettype.select_array[0][0] = 1;
		get_sockettype.select_array[1][0] = 1;
		get_sockettype.select_array[2][0] = 1;
		get_sockettype.select_array[3][0] = 0;

		get_sockettype.select_array[4][0] = 1;
		get_sockettype.select_array[5][0] = 1;
		get_sockettype.select_array[6][0] = 1;
		get_sockettype.select_array[7][0] = 0;
		break;
	case 3:
		get_sockettype.select_array[0][0] = 1;
		get_sockettype.select_array[1][0] = 1;
		get_sockettype.select_array[2][0] = 1;
		get_sockettype.select_array[3][0] = 1;

		get_sockettype.select_array[4][0] = 1;
		get_sockettype.select_array[5][0] = 1;
		get_sockettype.select_array[6][0] = 1;
		get_sockettype.select_array[7][0] = 1;
		break;
	}
	get_sockettype.select_array[0][1] = 0;
	get_sockettype.select_array[1][1] = 0;
	get_sockettype.select_array[2][1] = 0;
	get_sockettype.select_array[3][1] = 0;
	get_sockettype.select_array[4][1] = 0;
	get_sockettype.select_array[5][1] = 0;
	get_sockettype.select_array[6][1] = 0;
	get_sockettype.select_array[7][1] = 0;
}

u8 temp_sigelarry[8] = {0};
void sigelarray_init()
{
	u8 i = 0;
	for (i = 0; i < 7; i++)
		temp_sigelarry[i] = get_sockettype.select_array[i][1];
}
void doublearry_init()
{
	u8 i = 0;
	for (i = 0; i < 7; i++)
		get_sockettype.select_array[i][1] = temp_sigelarry[i];
}

u8 sigelarry_hex()
{
	u8 hex;
	u8 i = 0;
	hex = temp_sigelarry[i++] << 7 |
	      temp_sigelarry[i++] << 6 |
	      temp_sigelarry[i++] << 5 |
	      temp_sigelarry[i++] << 4 |
	      temp_sigelarry[i++] << 3 |
	      temp_sigelarry[i++] << 2 |
	      temp_sigelarry[i++] << 1 |
	      temp_sigelarry[i++];
	return hex;
}
u8 array_hex()
{
	u8 hex;
	u8 i = 0;
	hex = 	get_sockettype.select_array[i++][1] << 7 |
	        get_sockettype.select_array[i++][1] << 6 |
	        get_sockettype.select_array[i++][1] << 5 |
	        get_sockettype.select_array[i++][1] << 4 |
	        get_sockettype.select_array[i++][1] << 3 |
	        get_sockettype.select_array[i++][1] << 2 |
	        get_sockettype.select_array[i++][1] << 1 |
	        get_sockettype.select_array[i++][1] ;

	return hex;
}

int main(void)
{
//	 struct socket_type  get_sockettype;
	u8 i = 0;
	u8 last_state = 0;
	init_all();
	module_discriminate();
	module_config();
	relay_all = 0;
	relay_splithex(0x00);
	relay_all = 1;
	delay_ms(200);
	relay_all = 0;
	select_port();
	while (1)
	{
		
		if(g_ms==4000)
		{
					relay_splithex( array_hex());
		i=0;
			g_ms=0;
		}

		if (key3 == 0)
		{
g_ms=0;
			if (	get_sockettype.select_array[i][0] == 1)

			{
				sigelarray_init();
				if (temp_sigelarry[i] != 1)
				{
					temp_sigelarry[i] = 1;
				}
				else
				{
					temp_sigelarry[i] = 0;
				}

				relay_splithex( sigelarry_hex());
				do
				{
					i++;
				} 
				while (get_sockettype.select_array[i][0] != 1);
				while (key3 == 0);
				if (i >= 8)
					i = 0;
			}
		}
		if (key1 == 0)
		{	doublearry_init();
			relay_splithex( array_hex());
			relay_all = 1;
			while (key3 == 0);
			relay_all = 0;
		}
		command_handle();
	}
}
void TIM1_UP_IRQHandler(void)//1ms
{
	TIM_ClearITPendingBit(TIM1, TIM_FLAG_Update); //清中断
	g_ms++;
	

//	relay_splithex(0xff);
}


/******************* (C) COPYRIGHT 2015 Shell Era  *****END OF FILE************/


