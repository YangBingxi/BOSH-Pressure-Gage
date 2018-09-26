#include "angular_slip.h"
#include "sys.h"
#include "adc.h"

void angular_slip_init(void)
{
	Adc_Init();
	angular_slip_rest=Get_Adc_Average(ADC_Channel_3,5)*(3.3/4096);
}

float get_angular_slip(void)
{
	float temp;
	temp=Get_Adc(ADC_Channel_3)*(3.3/4096);
	return 90+(temp-angular_slip_rest)/0.008;
}

float get_angular_slip_aver(int time)
{
	float temp;
	temp=Get_Adc_Average(ADC_Channel_3,time)*(3.3/4096);
	return 90-(temp-angular_slip_rest)/0.008;
}
