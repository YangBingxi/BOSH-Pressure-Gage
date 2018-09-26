#include "variable.h"
/******全局变量*******/

			//PID
float PID_P=230;
float PID_I=4.79;
float PID_D=57000;
//前后 100 0.79 6w
// 200 4.9 5.5w

			//PWM
int CH1=0;
int CH2=0;
int CH3=0;
int CH4=0;

int OUT_PWM_1=300;		//用于PWM
int OUT_PWM_2=300;


			//MPU6050
float pitch=0;
float roll =0;
float yaw  =0;

float last_pitch =0;
float last_roll  =0;

short ang_speed[3]={0};
short g[3]={0};
			
			//time_counter
int d_time=0;
			
			//PID
float err_one=0;
float err_two=0;
float d_err_one=0;
float d_err_two=0;
float last_err_one=0;
float last_err_two=0;
float pre_err_one=0;
float pre_err_two=0;

float err_sum_one=0;
float err_sum_two=0;


			//OTHER
int Mode_1_flag=0;
int Mode_2_flag=0;
int Mode_3_flag=0;
int Mode=1;		
char project_name[25]={"PID_1"};
