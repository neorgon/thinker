#ifndef TRANSITIONSIGMOID_H
#define TRANSITIONSIGMOID_H
#include "Transition.h"
#include <vector>
#include <cmath>

class TransitionSigmoid :public Transition
{
    public:
       double TransitionFunction(double sum) override;
       double TransitionFunction(int position, vector<double>& sums) override;
       double Derived(double otuput) override;
};

#endif // TRANSITIONSIGMOID_H
