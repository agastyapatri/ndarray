#include "ndarray_math.h"
#include <math.h>


double sigmoid(double x){
	return 1 / (1 + exp(-x));
}
double relu(double x){
	return (x >= 0) ? x : 0;
}

double normal(double x){
	double mu = 0 ;
	double sigma = 1;
	double temp = ((x-mu)*(x-mu)) / ((sigma*sigma));
	return (1 / sqrt(2*PI*sigma*sigma))*exp(-0.5*temp);
}

double add(double x, double y){
	return x+y;
}

double sub(double x, double y){
	return x-y;
}

double mul(double x, double y){
	return x*y;
}

double divide(double x, double y){
	return x/y;
}

