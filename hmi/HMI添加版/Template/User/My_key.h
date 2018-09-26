#ifndef My_key_h
#define My_key_h
#include "sys.h"

//标志位定义

extern char set_which; //指向
extern float DIV;		//分度值
extern char  div_flag; //分度值标志位
void key_init(void);
void dis_key_about(void);

void Start_Key(void);
void Close_Key(void);
#endif
