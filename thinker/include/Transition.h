#ifndef TRANSITION_H
#define TRANSITION_H

#include <vector>

using namespace std;
class Transition
{
	public:
		virtual double TransitionFunction(double sum) = 0;
		virtual double TransitionFunction(int position, vector<double>& sums) = 0;
		virtual double Derived(double otuput) =0;
		virtual ~Transition(){};
};

#endif // TRANSITION_H
