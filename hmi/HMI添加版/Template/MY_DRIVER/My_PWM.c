#include "sys.h"
#include "My_PWM.h"

//初始化PWM 
void TIM1_PWM_Init(unsigned int  arr,unsigned int  psc)
{  
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);  
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA , ENABLE); 
	//RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE); 	
	                                                                     	     
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2; //TIM2_CH3
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	   
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3; //TIM2_CH4
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;//TIM2_CH1
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;//TIME_CH2
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	
	
	TIM_TimeBaseStructure.TIM_Period = arr; 
	TIM_TimeBaseStructure.TIM_Prescaler =psc; 
	TIM_TimeBaseStructure.TIM_ClockDivision = 0; 
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);
	//TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);
 
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_Pulse = 0;
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	
	TIM_OC1Init(TIM2, &TIM_OCInitStructure);
	TIM_OC2Init(TIM2, &TIM_OCInitStructure);
	TIM_OC3Init(TIM2, &TIM_OCInitStructure);
	TIM_OC4Init(TIM2, &TIM_OCInitStructure);

	TIM_CtrlPWMOutputs(TIM2,ENABLE);
	//TIM_CtrlPWMOutputs(TIM3,ENABLE);	
 	
	TIM_OC1PreloadConfig(TIM2, TIM_OCPreload_Enable);
	TIM_OC2PreloadConfig(TIM2, TIM_OCPreload_Enable);	
	TIM_OC3PreloadConfig(TIM2, TIM_OCPreload_Enable); 	 
	TIM_OC4PreloadConfig(TIM2, TIM_OCPreload_Enable); 	 
	
	TIM_ARRPreloadConfig(TIM2, ENABLE);
	//TIM_ARRPreloadConfig(TIM3, ENABLE);
	
	TIM_Cmd(TIM2, ENABLE); 
	//TIM_Cmd(TIM3, ENABLE);             
   
}

//设置占空比
void PWM_Set(char chx,int data)
{
	switch(chx)
	{
		case 1:TIM_SetCompare1(TIM2,data);	break;
		case 2:TIM_SetCompare2(TIM2,data);	break;
		case 3:TIM_SetCompare3(TIM2,data);	break;  
		case 4:TIM_SetCompare4(TIM2,data);	break;  
		defalut:break;
	}
}
