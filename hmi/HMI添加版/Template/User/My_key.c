#include "My_key.h"
#include "variable.h"
#include "My_GUI.h"
#include "24cxx.h" 
#include "myiic.h"
#include "touch.h"
#include "lcd.h"
#include "delay.h"
#include "adxl345.h"
#include "Step_Motor.h"
#include "My_PWM.h"

#define LED PAout(8)
char set_which=0; //ָ��
float DIV=0.1;		//�ֶ�ֵ
char  div_flag=0; //�ֶ�ֵ��־λ



void key_init(void)
{
	 EXTI_InitTypeDef EXTI_InitStructure;
	 NVIC_InitTypeDef NVIC_InitStructure;
	 GPIO_InitTypeDef  GPIO_InitStructure;
	 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOD|RCC_APB2Periph_GPIOC, ENABLE);	
		 
	 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;				 //LED0-->PA.8 �˿�����
	 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //�������
	 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO���ٶ�Ϊ50MHz  		
	 GPIO_Init(GPIOD, &GPIO_InitStructure);	  			
	 GPIO_SetBits(GPIOD,GPIO_Pin_2); 		
		
	//�����ж�����
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_1;//PC1
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //���ó���������
 	GPIO_Init(GPIOC, &GPIO_InitStructure);//��ʼ��GPIOC1
	
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_15;//PA15
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //���ó���������
 	GPIO_Init(GPIOA, &GPIO_InitStructure);//��ʼ��GPIOC1
	//�ж�����
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);//�ⲿ�жϣ���Ҫʹ��AFIOʱ��
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOC,GPIO_PinSource1);

  EXTI_InitStructure.EXTI_Line=EXTI_Line1;
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;//�½��ش���
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  EXTI_Init(&EXTI_InitStructure);	
	
	EXTI_InitStructure.EXTI_Line=EXTI_Line15;
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;//����
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  EXTI_Init(&EXTI_InitStructure);	
	
	NVIC_InitStructure.NVIC_IRQChannel = EXTI1_IRQn;			//ʹ�ܰ������ڵ��ⲿ�ж�ͨ��
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;	//��ռ���ȼ�2�� 
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x02;					//�����ȼ�1
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//ʹ���ⲿ�ж�ͨ��
  NVIC_Init(&NVIC_InitStructure);
	
		
	NVIC_InitStructure.NVIC_IRQChannel =EXTI15_10_IRQn;			//ʹ�ܰ������ڵ��ⲿ�ж�ͨ��
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;	//��ռ���ȼ�2�� 
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x02;					//�����ȼ�1
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//ʹ���ⲿ�ж�ͨ��
  NVIC_Init(&NVIC_InitStructure);
	
	
}

void Close_Key(void)
{
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannel = EXTI1_IRQn;			//ʹ�ܰ������ڵ��ⲿ�ж�ͨ��
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;	//��ռ���ȼ�2�� 
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x02;					//�����ȼ�1
  NVIC_InitStructure.NVIC_IRQChannelCmd = DISABLE;	
  NVIC_Init(&NVIC_InitStructure);	
}
void Start_Key(void)
{
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannel = EXTI1_IRQn;			//ʹ�ܰ������ڵ��ⲿ�ж�ͨ��
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;	//��ռ���ȼ�2�� 
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x02;					//�����ȼ�1
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);	
}

void EXTI1_IRQHandler(void)
{
	delay_ms(2);
	if(!GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_1))
	{
			GPIO_ResetBits(GPIOD,GPIO_Pin_2);
			tp_dev.scan(0); 
			if(tp_dev.x[0]<lcddev.width&&tp_dev.y[0]<lcddev.height)
			{	
			//	TP_Draw_Big_Point(tp_dev.x[0],tp_dev.y[0],RED);		//��ͼ	
				//dis_data_int("x",tp_dev.x[0],5,big);
				//dis_data_int("y",tp_dev.y[0],6,big);
				//+
				if(tp_dev.x[0]>10&&tp_dev.y[0]>200&&tp_dev.x[0]<65&&tp_dev.y[0]<255)
				{
					switch(set_which)
					{
						case 0: PID_P+=DIV;break;
						case 1: PID_I+=DIV;break;
						case 2: PID_D+=DIV;break;
						//case 3:	ANGLE+=DIV;break;
						default:break;
					}
				}
				//-
				if(tp_dev.x[0]>65&&tp_dev.y[0]>200&&tp_dev.x[0]<120&&tp_dev.y[0]<255)
				{
					switch(set_which)
					{
						case 0: PID_P-=DIV;break;
						case 1: PID_I-=DIV;break;
						case 2: PID_D-=DIV;break;
						//case 3:	ANGLE-=DIV;break;
						default:break;
					}
				}
				//^
				if(tp_dev.x[0]>120&&tp_dev.y[0]>200&&tp_dev.x[0]<175&&tp_dev.y[0]<255)
				{
					switch(set_which)
					{
						case 0: set_which=2;break;
						case 1: set_which=0;break;
						case 2: set_which=1;break;
						//case 3:	set_which=2;break;
						default:break;
					}
				}
				//V
				if(tp_dev.x[0]>175&&tp_dev.y[0]>200&&tp_dev.x[0]<230&&tp_dev.y[0]<255)
				{
					switch(set_which)
					{
						case 0: set_which=1;break;
						case 1: set_which=2;break;
						case 2: set_which=0;break;
						//case 3:	set_which=0;break;
						default:break;
					}
				}
				//D
				if(tp_dev.x[0]>10&&tp_dev.y[0]>255&&tp_dev.x[0]<65&&tp_dev.y[0]<330)
				{	
						switch(div_flag)
					{
						case 0:div_flag=1 ;break;
						case 1:div_flag=2;break;
						case 2:div_flag=3;break;
						case 3:div_flag=4;break;
						case 4:div_flag=0;break;
						default:break;
					}			
					switch(div_flag)
					{
						case 0: DIV=0.1;break;
						case 1:	DIV=1;break;
						case 2: DIV=10;break;
						case 3: DIV=100;break;
						case 4: DIV=0.01;break;
						default:break;
					}
				}//R
				if(tp_dev.x[0]>65&&tp_dev.y[0]>255&&tp_dev.x[0]<120&&tp_dev.y[0]<330)
				{
					err_one=0;
					err_two=0;
					err_sum_one=0;
					err_sum_two=0;
					OUT_PWM_1=0;
					OUT_PWM_2=0;
					last_err_one=0;
					last_err_two=0;
					OUT_PWM_1=0;
					OUT_PWM_2=0;
				}
				//M
				if(tp_dev.x[0]>120&&tp_dev.y[0]>255&&tp_dev.x[0]<175&&tp_dev.y[0]<330)
				{
					//��ʱ
					Setp_Motor_Angle(90,300);			
					POINT_COLOR=BLUE;
					dis_data_int("NUM",Sum_Num,5,mid);
					//��ʱ
				}
				//s
					if(tp_dev.x[0]>175&&tp_dev.y[0]>255&&tp_dev.x[0]<230&&tp_dev.y[0]<330)
				{
					//��ʱ
					CH1=0;
					CH2=0;
					CH3=0;
					CH4=0;
					PWM_Set(1,CH1);  
					PWM_Set(2,CH2);	
					PWM_Set(3,CH3);
					PWM_Set(4,CH4);
					delay_ms(1000);
					//��ʱ
				}
			}
	}
	while(1)
	{
		if(GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_1))
		{
			delay_ms(2);
				if(GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_1))
					break;	
		}		
	}	
	//ָʾ��
	GPIO_SetBits(GPIOD,GPIO_Pin_2);
	//ˢ�½���
	dis_all_data();
	dis_key_about();
	//���ж�
	EXTI_ClearITPendingBit(EXTI_Line1);
}

void dis_key_about(void)
{
	POINT_COLOR=BLUE; 
	{
	 LCD_ShowChar(200,34+24*0,' ',24,0);
	 LCD_ShowChar(200,34+24*1,' ',24,0);
	 LCD_ShowChar(200,34+24*2,' ',24,0);
	 LCD_ShowChar(200,34+24*3,' ',24,0);
	}
	LCD_ShowChar(200,34+24*set_which,'<',24,0);
	POINT_COLOR=RED;
	
	char data_s[30];
	sprintf(data_s,"%s:%.2f","DIV",DIV);
	LCD_ShowString(130,10+7*24,200,24,mid,data_s); 
}


void EXTI15_10_IRQHandler(void)
 {
	 delay_ms(10);
	 if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_15))
	 {
		 GPIO_ResetBits(GPIOD,GPIO_Pin_2);
		  Mode_1_flag=1;
		 dis_data_int("MF:",Mode_1_flag,6,mid);
	 }
	 EXTI_ClearITPendingBit(EXTI_Line15);
 }
 
