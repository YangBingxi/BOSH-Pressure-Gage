#include "My_GUI.h"
#include "lcd.h"
#include "usart.h"
#include "delay.h"
#include <stdio.h>
#include "My_key.h"
//#include "MY_GPIO.h"
#include "variable.h"

//功能：初始化LCD 
void LCD_DISINIT(void)
{
	u8 lcd_id[12];			//存放LCD ID字符串	
	delay_init();	
	uart_init(9600);
	LCD_Init();
	POINT_COLOR=BLACK; 
	sprintf((char*)lcd_id,"LCD ID:%04X",lcddev.id);//将LCD ID打印到lcd_id数组。	
	LCD_Clear(WHITE);
}

void dis_data_int(char* name,int data,int post,enum char_size size)
{
   char data_s[30];
	 sprintf(data_s,"%s:%4d",name,data);
	 LCD_ShowString(10,10+post*24,200,24,size,data_s); 
}

void dis_data_float(char* name,float data,int post,enum char_size size)
{
   char data_s[30];
	 sprintf(data_s,"%s:%.4f",name,data);
	 LCD_ShowString(10,10+post*24,200,24,size,data_s); 
}

void dis_data_string(char* name,char* data,int post,enum char_size size)
{
   char data_s[30];
	 sprintf(data_s,"%s:%s",name,data);
	 LCD_ShowString(10,10+post*24,200,24,size,data_s); 
}

void dis_all_data(void)
{	
	Close_Key();
	POINT_COLOR=BLACK;
	dis_data_string("PID_name",project_name,0,mid);
	dis_data_float("PID_P",PID_P,1,big);
	dis_data_float("PID_I",PID_I,2,big);
	dis_data_float("PID_D",PID_D,3,big);
	//dis_data_float("ANG_X",ANGLE_X,4,mid);
//	dis_data_int("PWM_CH1",CH1,4,mid);
//	dis_data_int("PWM_CH2",CH2,5,mid);
//	dis_data_int("PWM_CH3",CH3,6,mid);
//	dis_data_int("PWM_CH4",CH4,7,mid);
	dis_data_float("pitch",pitch,4,mid);
	dis_data_float("roll",roll,5,mid);
	dis_data_int("OUT_PWM_1",OUT_PWM_1,6,mid);
	dis_data_int("OUT_PWM_2",OUT_PWM_2,7,mid);
	Start_Key();
}

void Draw_Key(void)
{	
	LCD_DrawRectangle(10,200, 230, 310);
	LCD_DrawRectangle(11,201, 229, 309);
	LCD_DrawLine(65,200,65,310);
	LCD_DrawLine(120,200,120,310);
	LCD_DrawLine(175,200,175,310);
	LCD_DrawLine(10,255,230,255);
	LCD_ShowChar(30,215,'+',24,0);
	LCD_ShowChar(85,215,'-',24,0);
	LCD_ShowChar(140,215,'^',24,0);
	LCD_ShowChar(195,215,'v',24,0);
	LCD_ShowChar(30,275,'D',24,0);
	LCD_ShowChar(85,275,'R',24,0);
	LCD_ShowChar(140,275,'M',24,0);
	LCD_ShowChar(195,275,'S',24,0);
}

