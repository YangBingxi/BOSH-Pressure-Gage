#include "Step_Motor.h"
#include "sys.h"
#include "delay.h"



//Pa0 Pa1 Pa2
void Setp_Motor_init(void)
{
 GPIO_InitTypeDef  GPIO_InitStructure;
 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);	
	//PA0
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;				 // 端口配置
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz
 GPIO_Init(GPIOA, &GPIO_InitStructure);					 //根据设定参数初始化
 GPIO_ResetBits(GPIOA,GPIO_Pin_0);								// 使能有效
	//PA1
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;				 
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	
 GPIO_Init(GPIOA, &GPIO_InitStructure);				
 GPIO_SetBits(GPIOA,GPIO_Pin_1);									//正方向
	//PA2
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;				 //端口配置
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz
 GPIO_Init(GPIOA, &GPIO_InitStructure);					 //根据设定参数初始化
 GPIO_ResetBits(GPIOA,GPIO_Pin_2);
	//PA4 校正
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;				 //端口配置
 GPIO_InitStructure.GPIO_Mode =  GPIO_Mode_IPU; 		 //输入
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz
 GPIO_Init(GPIOA, &GPIO_InitStructure);					 //根据设定参数初始化
 GPIO_ResetBits(GPIOA,GPIO_Pin_4);
 
 Setp_Motor_Rest();
}

void Setp_Motor_Num(unsigned int Num, char direction,int speed)
{	
	//Setp_Motor_Enable=0;
	if(speed<200)
		speed=300;
	if(direction)
	{
		Setp_Motor_Dir=1;
		//Sum_Num+=Num;
		//Sum_Num=Sum_Num% plus_n;
	}
	else
	{
		Setp_Motor_Dir=0;
	/*	if(Sum_Num<Num)
		{	
			if(Num>=plus_n)
			{
				int Num_t=Num%plus_n;
					if(Sum_Num<Num_t)
						Sum_Num=plus_n-(Num_t-Sum_Num);
				  else
						Sum_Num-=Num_t;
			}
			else
			{
				Sum_Num=plus_n-(Num-Sum_Num);
			}		
		}
		else
			Sum_Num-=Num;*/	
	}
	for(int i=0;i<Num;i++)
		{
			Setp_Motor_Plus=0;
			delay_us(10);
			Setp_Motor_Plus=1;
			delay_us(speed);
		}
	Setp_Motor_Plus=0;
	//Setp_Motor_Enable=1;
}

void Setp_Motor_Rest()
{
	while(Setp_Motot_Rest)
		Setp_Motor_Num(1,1,300);
	Sum_Num=1600;
}
void Setp_Motor_Angle(float angle,int speed)
{
	int Num;
	Num= angle/LBS;
//	if(Num>=plus_n)
//	{
//		Num=Num%plus_n;
//	}
	if(Num>=Sum_Num)
	{	
		if(Num-Sum_Num>=16)
		{	Setp_Motor_Num(Num-Sum_Num,1,speed);
			Sum_Num=Num;
		}
	}
	else
	{		
		if(Sum_Num-Num>=32)
		{
			Setp_Motor_Num(Sum_Num-Num,0,speed);
			Sum_Num=Num;
		}
	}
}
