#include "sys.h"
#include "usart.h"
#include "delay.h"
#include "HMI.h"
 int main(void)
 { 
	
	delay_init(); 
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	HMI_INIT();
	uart_init(115200);
    Send_mesg("system is ok!");

   	while(1)
	{	
	 ;
	}

}

