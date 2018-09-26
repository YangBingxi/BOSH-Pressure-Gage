#include "filtering.h"

float M_F(float*ptr,int num)
{	
	float max=0;
	float min=0;
	int max_i=num;
	int min_i=num;
	float sum=0;
	for(int i=0;i<num;i++)
	{
		if(*(ptr+i)>max)
		{
			max_i=i;
		}
		else if(*(ptr+i)<min)
				{
					min_i=i;
				}
	}
	for(int j=0;j<num;j++)
	{
		if((j!=max_i)&&(j!=min_i))
		{
			sum+=*(ptr+j);
		}
	}
		return sum/(num-2);
	
//	for(int i=0;i<num;i++)
//	{
//		sum+=*(ptr+i);
//	}
//	return sum/num;
}
