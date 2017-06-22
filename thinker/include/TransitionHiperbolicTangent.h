#ifndef TRANSITIONHIPERBOLICTANGENT_H
#define TRANSITIONHIPERBOLICTANGENT_H
#include "Transition.h"

class TransitionHiperbolicTangent : public Transition
{
public:
	double TransitionFunction(double sum) override;
	double TransitionFunction(int position, vector<double>& sums) override;
	double Derived(double otuput) override;
};

#endif // TRANSITIONHIPERBOLICTANGENT_H
