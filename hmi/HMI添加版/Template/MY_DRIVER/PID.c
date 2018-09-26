#include "PID.h"
#include "sys.h"
#include "My_PWM.h"
#include "variable.h"
#include <math.h>

//y轴		参数：目标值
int Pid_control_1(float next_point1)
{		
	
		err_one=roll-next_point1;			//本次误差 
		if(fabsf(err_one)<0.2)
			return 1;
		d_err_one=err_one-last_err_one;		//两次误差差值
	
		err_sum_one+=err_one;				//累积误差
		if(err_sum_one>2000)
		{
			err_sum_one=2000;
		}
		if(err_sum_one<-2000)
			err_sum_one=-2000;
		
		OUT_PWM_1 = PID_P*err_one+PID_I*err_sum_one+PID_D*(err_one-last_err_one);
		
		pre_err_one=last_err_one;
		last_err_one=err_one;
		
		if(OUT_PWM_1>7000)				//速度限制
			OUT_PWM_1=7000;
		if(OUT_PWM_1<-7000)
			OUT_PWM_1=-7000;
		if(OUT_PWM_1>=0)		//速度大于0
		{	
			if(OUT_PWM_1<600)			//死区剔除
			{
				OUT_PWM_1=-600;
				PWM_Set(3,0);
				PWM_Set(4,0);
				PWM_Set(3,0);	
				PWM_Set(4,-OUT_PWM_1);				
			}
			else
			{
			PWM_Set(3,0);
			PWM_Set(4,0);
			
			PWM_Set(3,OUT_PWM_1);	
			PWM_Set(4,0);
			}
		}
		else					//死去小于0
		{
			if(OUT_PWM_1>-600)		  //死区剔除
			{	
				OUT_PWM_1=600;
				PWM_Set(3,0);
				PWM_Set(4,0);
				
				PWM_Set(3,OUT_PWM_1);	
				PWM_Set(4,0);	
			}
			else
			{
			PWM_Set(3,0);
			PWM_Set(4,0);
			PWM_Set(3,0);	
			PWM_Set(4,-OUT_PWM_1);	
			}				
		}	
	return 0;
		
}

int Pid_control_2(float next_point2)
{
		err_two=pitch-next_point2;
		if(fabsf(err_two)<0.2)
			return 1;
		d_err_two=err_two-last_err_two;
		
		err_sum_two+=err_two;
		
		if(err_sum_one>2000)
		{
			err_sum_one=2000;
		}
		if(err_sum_one<-2000)
			err_sum_one=-2000;
		
		OUT_PWM_2 =PID_P*err_two+PID_I*err_sum_two+PID_D*(err_two-last_err_two);
		
		pre_err_two=last_err_two;
		last_err_two=err_two;
		
		if(OUT_PWM_2>7200)
			OUT_PWM_2=7200;
		if(OUT_PWM_2<-7200)
			OUT_PWM_2=-7200;
		if(OUT_PWM_2>0)
		{
			if(OUT_PWM_2<600)
			{
				OUT_PWM_2=-600;
				PWM_Set(1,0);
				PWM_Set(2,0);
				
				PWM_Set(1,0);
				PWM_Set(2,-OUT_PWM_2);	
			}
			else
			{
			PWM_Set(1,0);
			PWM_Set(2,0);
			
			PWM_Set(1,OUT_PWM_2);
			PWM_Set(2,0);	
			}
		}
		else
		{
			if(OUT_PWM_2>-600)
			{
				OUT_PWM_2=600;
				PWM_Set(1,0);
				PWM_Set(2,0);
					
				PWM_Set(1,OUT_PWM_2);
				PWM_Set(2,0);		
			}
			else
			{
			PWM_Set(1,0);
			PWM_Set(2,0);
			
			PWM_Set(1,0);
			PWM_Set(2,-OUT_PWM_2);	
			}				
		}
	return 0;
}


