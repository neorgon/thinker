#include "../include/TransitionSigmoid.h"

double TransitionSigmoid::TransitionFunction(double sum)
{
	if(sum < -45.0)
	{
		return 0;
	}
	else if(sum > 45.0)
		{
			return 1;
		}
		else{
			return 1/(1 + exp(-sum));
		}
}

double TransitionSigmoid::TransitionFunction(int position,vector<double>& sums)
{
 	return 0;
}
double TransitionSigmoid::Derived(double otuput) 
{
	return (1 + otuput) * (1 - otuput);
}