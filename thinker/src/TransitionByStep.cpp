#include "../include/TransitionByStep.h"


double TransitionByStep::TransitionFunction(double sum)
{
	if(sum >= 0)
		return 1;
	else
		return -1;
}
double TransitionByStep::TransitionFunction(int position,vector<double>& sums)
{
 	return 0;
}
double TransitionByStep::Derived(double otuput) 
{
	return 0;
}
/*TransitionByStep::~TransitionByStep()
{
    //dtor
}
*/
