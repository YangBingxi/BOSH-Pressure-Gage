#ifndef _Setp_Motor_H
#define _Setp_Motor_H

#define  LBS 0.05625
#define  plus_n 6400

#define  Setp_Motor_Enable PAout(0)
#define  Setp_Motor_Dir    PAout(1)
#define  Setp_Motor_Plus   PAout(2)
#define  Setp_Motot_Rest   PAin(4)


void Setp_Motor_init(void);							//��ʼ������
void Setp_Motor_Num(unsigned int Num, char direction,int speed);  //��Num����,���� 0 ����1��
void Setp_Motor_Rest(void);
void Setp_Motor_Angle(float angle,int speed);
#endif

