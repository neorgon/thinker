#ifndef PERCEPTRON_H
#define PERCEPTRON_H
#include <vector>
#include <iostream>
#include <cmath>
#include <random>
#include "TransitionByStep.h"
using namespace std;

class Transition;

class Perceptron
{
public:
  Transition* transition;
  vector<double> weights{};
  double bias;
  double output;
  double gradient;
    public:
        Perceptron(int numberInputs);
        Perceptron(int numberInputs, Transition* function, uniform_real_distribution<double>& distribution, default_random_engine& generator);
        double Evaluate(vector<double>& inputs) const;
        double Summatory(vector<double>& inputs) const;
        void Train(vector< vector<double> >& trainDataInput, vector<double>& expectedoutput,double learning_rate,int loop_learn);
        ~Perceptron();
};
#endif // PERCEPTRON_H

