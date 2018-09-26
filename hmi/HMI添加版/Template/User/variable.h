#ifndef __variable_h_
#define __variable_h_
/*******宏定义*********/


/******全局变量*******/

			//PID
extern float PID_P;
extern float PID_I;
extern float PID_D;

			//ADC
			
			//ANGLE SENSOR
extern float ANGLE_X;
extern float ANGLE_Y;
extern float ANGLE_Z;

			//ADXL345
extern short ADXL_X;
extern short ADXL_Y;
extern short ADXL_Z;
extern char ADXL_xval;
extern char ADXL_yval;
extern char ADXL_zval;

			//SetMoto
extern unsigned int Setp_Num;
extern unsigned int Sum_Num;

			//angular_slip
extern float angular_slip_x;
extern float angular_slip_rest;   //复位参数
			
			//PWM
extern int CH1;
extern int CH2;
extern int CH3;
extern int CH4;

extern int OUT_PWM_1;		//用于PWM
extern int OUT_PWM_2;
			//MPU6050
extern float pitch;
extern float roll;
extern float yaw;

extern float last_pitch;
extern float last_roll;

extern short ang_speed[3];
extern short g[3];
			//time_counter
extern int d_time;
		
		
			//PID
extern float d_err_one;
extern float d_err_two;

extern float err_one;
extern float err_two;

extern float last_err_one;
extern float last_err_two;
extern float pre_err_one;
extern float pre_err_two;

extern float err_sum_one;
extern float err_sum_two;

			

			//OTHER
extern char project_name[25] ;
extern int Mode_1_flag;
extern int Mode_2_flag;
extern int Mode_3_flag;
extern int Mode;

#endif
