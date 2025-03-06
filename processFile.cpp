#include "stdafx.h"

float processFile(FILE *fp) {
	float x;
	float sum;
	int result;

	sum=0.0;
	result=fscanf(fp," %f",&x);
	while (result>0) {
		sum+=x;
		result=fscanf(fp," %f",&x);
	}
	return(sum);
}
