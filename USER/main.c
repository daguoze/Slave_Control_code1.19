/******************** (C) COPYRIGHT 2015 Shell Era **************************
 * 库版本  ：ST3.5.0
 *
 * 作者    ：Guo Zeyu
 **********************************************************************************/
#include "stm32f10x.h"
#include "init.h"

void select_port()
{
	
	switch(get_sockettype.hole_type) //2h
	{case 0:
//		i&0x0F; 
//[][0]允许位
		get_sockettype.select_array[0][0]=1;
		get_sockettype.select_array[1][0]=0;
		get_sockettype.select_array[2][0]=0;
		get_sockettype.select_array[3][0]=0;
		
		get_sockettype.select_array[4][0]=1;		
		get_sockettype.select_array[5][0]=0;
		get_sockettype.select_array[6][0]=0;
		get_sockettype.select_array[7][0]=0;
		

		break;
	case 1:
	  get_sockettype.select_array[0][0]=1;
		get_sockettype.select_array[1][0]=1;
		get_sockettype.select_array[2][0]=0;
		get_sockettype.select_array[3][0]=0;
		
		get_sockettype.select_array[4][0]=1;		
		get_sockettype.select_array[5][0]=1;
		get_sockettype.select_array[6][0]=0;
		get_sockettype.select_array[7][0]=0;	
	
			break;
	case 2:
		get_sockettype.select_array[0][0]=1;
		get_sockettype.select_array[1][0]=1;
		get_sockettype.select_array[2][0]=1;
		get_sockettype.select_array[3][0]=0;
		
		get_sockettype.select_array[4][0]=1;		
		get_sockettype.select_array[5][0]=1;
		get_sockettype.select_array[6][0]=1;
		get_sockettype.select_array[7][0]=0;	
	
	
			break;
	case 3:
		get_sockettype.select_array[0][0]=1;
		get_sockettype.select_array[1][0]=1;
		get_sockettype.select_array[2][0]=1;
		get_sockettype.select_array[3][0]=1;
		
		get_sockettype.select_array[4][0]=1;		
		get_sockettype.select_array[5][0]=1;
		get_sockettype.select_array[6][0]=1;
		get_sockettype.select_array[7][0]=1;	
	
			break;
		
	}
				get_sockettype.select_array[0][1]=0;
				get_sockettype.select_array[1][1]=0;
				get_sockettype.select_array[2][1]=0;
				get_sockettype.select_array[3][1]=0;
				get_sockettype.select_array[4][1]=0;
				get_sockettype.select_array[5][1]=0;
				get_sockettype.select_array[6][1]=0;
				get_sockettype.select_array[7][1]=0;
//	if(get_sockettype.hole_type==1) //4h

//	
//			
//	if(get_sockettype.hole_type==2) //6h
//	

//	if(get_sockettype.hole_type==3) //8h


}	

u8 temp_sigelarry[8]={0};
void sigelarray_init()
{
u8 i=0;
	for(i=0;i<7;i++)
	
	temp_sigelarry[i]=get_sockettype.select_array[i][1];



}
void doublearry_init()
	
{
u8 i=0;
	for(i=0;i<7;i++)
	
	get_sockettype.select_array[i][1]=temp_sigelarry[i];



}


u8 sigelarry_hex()

{
	u8 hex;
	u8 i=0;
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
	u8 i=0;
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
	u8 i=0;
	u8 last_state=0;
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

//		if (key1 == 0 || key2 == 0 || key3 == 0)
//			PCout(9) = 1;
//		else
//			PCout(9) = 0;
//	relay_splithex( array_hex());
if(key3==0)
{
		
		if(	get_sockettype.select_array[i][0]==1)
			
		{
			sigelarray_init();
			if(temp_sigelarry[i]!=1)
			{	temp_sigelarry[i]=1;
			 //last_state=0;
			}
			else 
			{	temp_sigelarry[i]=0;
			 //last_state=1;}
			
//			 get_sockettype.select_array[i-1][1]=last_state;
				//last_state=array_hex();
		
		
		
		}
		
			relay_splithex( sigelarry_hex());
		do
		{
		i++;
		}while(get_sockettype.select_array[i][0]!=1);
			while(key3==0);
			
			if(i>=8)
				i=0;
		}
}


if(key1==0)
	{	 doublearry_init();
				relay_splithex( array_hex());
			relay_all = 1;
		while(key3==0);
			relay_all =0;
   }
		command_handle();
	}
}


/******************* (C) COPYRIGHT 2015 Shell Era  *****END OF FILE************/


