#ifndef __OLED_H_
#define __OLED_H_
#include "sys.h"
#include "stm32f10x.h"

//#include "stdlib.h"
//////////////////////////////////////////////////////////////////////////////////
//imodule
//////////////////////////////////////////////////////////////////////////////////

//OLED模式设置
//0:4线串行模式
//1:并行8080模式
#define OLED_MODE 0

//-----------------OLED端口定义----------------

#define OLED_RST_Clr() GPIO_ResetBits(GPIOB,GPIO_Pin_7)    //RST
#define OLED_RST_Set() GPIO_SetBits(GPIOB,GPIO_Pin_7)

#define OLED_RS_Clr() GPIO_ResetBits(GPIOB,GPIO_Pin_6)     //DC
#define OLED_RS_Set() GPIO_SetBits(GPIOB,GPIO_Pin_6)     

#define OLED_SCLK_Clr() GPIO_ResetBits(GPIOB,GPIO_Pin_8)   //D0
#define OLED_SCLK_Set() GPIO_SetBits(GPIOB,GPIO_Pin_8)

#define OLED_SDIN_Clr() GPIO_ResetBits(GPIOB,GPIO_Pin_9)   //D1
#define OLED_SDIN_Set() GPIO_SetBits(GPIOB,GPIO_Pin_9)    

#define OLED_CMD  0 //写命令
#define OLED_DATA 1 //写数据


//OLED控制用函数
void OLED_WR_Byte(u8 dat, u8 cmd);
void OLED_Display_On(void);
void OLED_Display_Off(void);
void OLED_Refresh_Gram(void);
void LCD_P6x8Str(u8 x, u8 y, u8 ch[]);
void OLED_Init(void);
void OLED_Clear(void);
void OLED_DrawPoint(u8 x, u8 y, u8 t);
void OLED_Fill(u8 x1, u8 y1, u8 x2, u8 y2, u8 dot);
void OLED_ShowChar(u8 x, u8 y, u8 chr, u8 size, u8 mode);
void OLED_ShowNum(u8 x, u8 y, u32 num, u8 len, u8 size);
void OLED_ShowString(u8 x, u8 y, const u8 *p);

 void LCD_P8x16Str(u8 x,u8 y,u8 ch[]);//???????
void LCD_Set_Pos(u8 x, u8 y);
void LCD_PutPixel(u8 x, u8 y);

void refresh_show(u8 x);
void LCD_powershow( u8 y, u8 t);
void temp(u8 xx, u8 data);
void wave(u8 xx , u8 split);
void point(u8 xx, u8 data);

#endif




