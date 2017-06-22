#include "../include/TransitionSoftMax.h"

double TransitionSoftMax::TransitionFunction(int position,vector<double>& sums)
{
	double divisor = 0;
	for(int i = 0; i < sums.size(); i++)
	{
			divisor += exp(sums[i]);
	}
	return exp(sums[position])/divisor;

}
double TransitionSoftMax::TransitionFunction(double sum)
{
	return 0;
}
double TransitionSoftMax::Derived(double otuput) 
{
	return otuput * (1 - otuput);
}