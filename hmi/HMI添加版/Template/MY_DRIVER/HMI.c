#include "HMI.h"
#include "variable.h"
#include <stdlib.h>
#include "sys.h"
#include "delay.h"
char temp_data_str[11];
int rec_flag=0;
int count_num=0;
int num_flag=0;

//控件参数绑定（修改此处既可） // PID_P等修改为你要修改的参数
float *n1_d =&PID_P;	 //文本控件1
float *n2_d=&PID_P;
float *n3_d=&PID_I;
float *n4_d=&PID_I;
float *n5_d=&PID_I;
float *n6_d=&PID_I;		 //文本控件2
//

/*
HMI初始化函数 
*/
void HMI_INIT(void)
{
	//初始化串口
	uart3_init(115200);
	Send_end();		//清空hmi的缓存

	//注册可修改控件个数
	printf("num1.val=6");
	Send_end();
	//注册控件名字和初始值  n1.txt 代表控件，\" (名字)\"代表显示的字符串
		//控件1
	printf("n1.txt=\"P:\"");
	Send_end();
	printf("n1_n.txt=\"0\"");
	Send_end();
		//控件2
	printf("n2.txt=\"I:\"");
	Send_end();
	printf("n2_n.txt=\"0\"");
	Send_end();
		//控件3
	printf("n3.txt=\"D:\"");
	Send_end();
	printf("n3_n.txt=\"0\"");
	Send_end();
		//控件4
	printf("n4.txt=\"ang:\"");
	Send_end();
	printf("n4_n.txt=\"0\"");
	Send_end();
		//控件5
	printf("n5.txt=\"dis:\"");
	Send_end();
	printf("n5_n.txt=\"0\"");
	Send_end();
		//控件6
	printf("n6.txt=\"V:\"");
	Send_end();
	printf("n6_n.txt=\"0\"");
	Send_end();
	
}

/*底层函数 发送结束字符串*/
void Send_end(void)	//发送结束字符
{
printf("%c",0xff);
printf("%c",0xff);
printf("%c",0xff);
}
/*消息窗口api*/
void Send_mesg(char* mesg)
{
	printf("wd.txt=\"%s\"",mesg);
	Send_end();
}
/*6个文本窗API
pos:第几个文本窗口 1-6
data:所需要显示的数据 精度为.4f
*/
void Send_data(int pos,float data)
{
	switch(pos)
	{
		case 1:
		{
			printf("n1_n.txt=\"%.4f\"",data);
			Send_end();
		}break;
		case 2:
		{
			printf("n2_n.txt=\"%.4f\"",data);
			Send_end();
		}break;
		case 3:
		{
			printf("n3_n.txt=\"%.4f\"",data);
			Send_end();
		}break;
		case 4:
		{
			printf("n4_n.txt=\"%.4f\"",data);
			Send_end();
		}break;
		case 5:
		{
			printf("n5_n.txt=\"%.4f\"",data);
			Send_end();
		}break;
		case 6:
		{
			printf("n6_n.txt=\"%.4f\"",data);
			Send_end();
		}break;
		default:break;
	}
}

/*
HMI串口通信函数 底层
*/
void USART3_IRQHandler(void)                	//串口3中断服务程序
{
	u8 Res;
	if(USART_GetITStatus(USART3, USART_IT_RXNE) != RESET)  //接收中断
		{
			Res =USART_ReceiveData(USART3);	//读取接收到的数据			
			switch(Res)
			{
				case 0x41:				//1  0x41 =A
						{
							//初始化结束数组
							for(int i=0;i<11;i++)
								temp_data_str[i]=0x20;
							rec_flag=1;
							count_num=0;
							num_flag=1;
						}break;
				case 0x42:				//2
						{
							for(int i=0;i<11;i++)
								temp_data_str[i]=0x20;
							rec_flag=1;
							count_num=0;
							num_flag=2;
						}break;
				case 0x43:				//3
						{
							for(int i=0;i<11;i++)
								temp_data_str[i]=0x20;
							rec_flag=1;
							count_num=0;
							num_flag=3;
						}break;
				case 0x44:				//4
						{
							for(int i=0;i<11;i++)
								temp_data_str[i]=0x20;
							rec_flag=1;
							count_num=0;
							num_flag=4;
						}break;
				case 0x45:				//5
						{
							for(int i=0;i<11;i++)
								temp_data_str[i]=0x20;
							rec_flag=1;
							count_num=0;
							num_flag=5;
						}break;
				case 0x46:				//6
						{
							for(int i=0;i<11;i++)
								temp_data_str[i]=0x20;
							rec_flag=1;
							count_num=0;
							num_flag=6;
						}break;
				default:break;
			}
			if(rec_flag&&Res!=0x5a&&count_num<11)
			{
				temp_data_str[count_num]=Res;
				count_num++;
			}
			else
			{
				if(Res==0x5a)
				{
					//接收结束处理程序
					float cov_temp= atof(&temp_data_str[1]);
					switch(num_flag)
					{
						case 1:{
							printf("wd.txt=\"%.4f\"",cov_temp);
							Send_end();	
							*n1_d=cov_temp;
						}break;
						case 2:{
							printf("wd.txt=\"%.4f\"",cov_temp);
							Send_end();	
							*n2_d=cov_temp;
						}break;
						case 3:{
							printf("wd.txt=\"%.4f\"",cov_temp);
							Send_end();	
							*n3_d=cov_temp;
						}break;
						case 4:{
							printf("wd.txt=\"%.4f\"",cov_temp);
							Send_end();	
							*n4_d=cov_temp;
						}break;
						case 5:{
							printf("wd.txt=\"%.4f\"",cov_temp);
							Send_end();	
							*n5_d=cov_temp;
						}break;
						case 6:{
							printf("wd.txt=\"%.4f\"",cov_temp);
							Send_end();	
							*n6_d=cov_temp;
						}break;
						default:break;
					}
				}
				else	//接收错误处理程序
				{
				   rec_flag=0;
				}
			}
  		 
	} 
}		
