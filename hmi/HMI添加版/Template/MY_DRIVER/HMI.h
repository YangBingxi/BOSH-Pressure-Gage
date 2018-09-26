#ifndef HMI_H
#define HMI_H
#include "usart.h"
#include "sys.h"
void HMI_INIT(void);
void Send_end(void);
void Send_mesg(char*);
void Send_data(int pos,float data);
#endif
