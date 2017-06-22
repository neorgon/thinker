#ifndef TRANSITIONBYSTEP_H
#define TRANSITIONBYSTEP_H
#include "Transition.h"
class TransitionByStep : public Transition
{
    public:
		double TransitionFunction(double sum) override;
		double TransitionFunction(int position, vector<double>& sums) override;
		double Derived(double otuput) override;
        ~TransitionByStep(){};
};

#endif // TRANSITIONBYSTEP_H
