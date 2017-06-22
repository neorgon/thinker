#include "Transition.h"
#include <cmath>

class TransitionSoftMax : public Transition
{
public:
	double TransitionFunction(double sum)override;
    double TransitionFunction(int position,vector<double>& sums)override;
    double Derived(double otuput) override;

};
