#include "../include/Perceptron.h"

Perceptron::Perceptron(int numberInputs)
{
	transition = new TransitionByStep();
	default_random_engine generator;
    uniform_real_distribution<double> distribution(0.2,0.5);   
	for (int i = 0; i < numberInputs; ++i)
	{
		weights.push_back(distribution(generator));
	}
    bias = distribution(generator);
}
Perceptron::Perceptron(int numberInputs, Transition* function, uniform_real_distribution<double>& distribution, default_random_engine& generator)
{
	transition = function;
	gradient = 0;	
	for (int i = 0; i < numberInputs; ++i)
	{
		weights.push_back(distribution(generator));
	}
    bias = distribution(generator);
}
double Perceptron::Evaluate(vector<double>& inputs) const
{
	if(inputs.size() > weights.size())
		return -1000;

	double sum = 0;
	for(int i = 0;  i< weights.size(); ++i)
	{
		sum+= inputs[i]*weights[i];
	}
	sum += bias;

	sum = transition->TransitionFunction(sum);
    return sum;
}

double Perceptron::Summatory(vector<double>& inputs) const
{
	if(inputs.size() > weights.size())
		return -1;

	double sum = 0;
	for(int i = 0;  i< weights.size(); ++i)
	{
		sum+= inputs[i]*weights[i];
	}
	sum += bias;
    return sum;
}

void Perceptron::Train(vector< vector<double> >& trainDataInput, vector<double>& expectedOutput,double learningRate,int loopLearn)
{
	int count = 0;
	int alpha =0;
	double outputObtained = 0;
	while(count < loopLearn)
	{
		for (int i = 0; i < trainDataInput.size(); ++i)
		{
		    outputObtained = Evaluate(trainDataInput[i]);
            alpha = outputObtained - expectedOutput[i];
			for(int j  = 0; j < weights.size(); j++)
			{
				if(trainDataInput[i][j] > 0 && alpha > 0)
				{
					weights[j]  = weights[j] - (alpha * learningRate * trainDataInput[i][j]);
				}
				else if(trainDataInput[i][j] < 0 && alpha > 0)
				{
					weights[j]  = weights[j] + (alpha * learningRate * trainDataInput[i][j]);
				}
				else if(trainDataInput[i][j] > 0  && alpha < 0)
				{
					weights[j]  = weights[j] - (alpha * learningRate * trainDataInput[i][j]);
				}
				else if(trainDataInput[i][j] < 0  && alpha < 0)
				{
					weights[j]  = weights[j] + (alpha * learningRate * trainDataInput[i][j]);
				}
                bias = bias - (alpha * learningRate);
			}
		}
		count++;
	}
}
Perceptron::~Perceptron()
{
}
