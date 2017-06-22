#include "../include/TransitionHiperbolicTangent.h"
#include <cmath>

double TransitionHiperbolicTangent::TransitionFunction(double sum)
{
	if(sum < -20.0)
	{
		return -1;
	}
	else if(sum > 20.0)
	{
		return 1;
	}
	else
	{
		return tanh(sum);
    }
}
double TransitionHiperbolicTangent::TransitionFunction(int position, vector<double>& sums)
{
	return 0;
}
double TransitionHiperbolicTangent::Derived(double otuput) 
{
	return (1 + otuput) * (1 - otuput);
}