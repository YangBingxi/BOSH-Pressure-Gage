#ifndef  __MY_GUI_H__
#define  __MY_GUI_H__
#include <stdio.h>
//º¯ÊýÉùÃ÷

enum char_size{ small=12,mid=16,big=24};
void LCD_DISINIT(void);
void dis_data_int(char* name,int data,int post,enum char_size size);
void dis_data_float(char* name,float data,int post,enum char_size size);
void dis_data_string(char* name,char* data,int post,enum char_size size);
void dis_all_data(void);
void Draw_Key(void);
#endif
