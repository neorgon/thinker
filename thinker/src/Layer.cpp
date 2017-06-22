#include "../include/Layer.h"

Layer::Layer(int numNodes,int numInputs,TypeOfTransition transitionType,LayerType layerType,uniform_real_distribution<double>& distribution,default_random_engine& generator):transitionType{transitionType},layerType{layerType}
{
	switch(transitionType)
	{
		case TypeOfTransition::STEPBYSTEP:
			function = new TransitionByStep();
		break;
		case TypeOfTransition::SIGMOID:
			function = new TransitionSigmoid();
		break;
		case TypeOfTransition::TANGHIPERBOLIC:
			function = new TransitionHiperbolicTangent();
		break;
		case TypeOfTransition::SOFTMAX:
			function = new TransitionSoftMax();
		break;
	}
	for(int nodes = 0; nodes < numNodes ; nodes++)
	{
		layerPerceptron.push_back(new Perceptron {numInputs,function,distribution,generator});
	}
}
vector<double>& Layer::Evaluate(vector<double>& inputs)
{
    outPutProcessFeed.clear();
    if(layerType == LayerType::INPUT)
    {
    	outPutProcessFeed = inputs;
    }
    else if(transitionType != TypeOfTransition::SOFTMAX)
    {
        for(vector<Perceptron*>::iterator i = layerPerceptron.begin(); i != layerPerceptron.end();i++)
        {
            outPutProcessFeed.push_back((*i)->Evaluate(inputs));
        }
    }
    else
    {
        vector<double> sums;
        for(vector<Perceptron*>::iterator i = layerPerceptron.begin(); i < layerPerceptron.end();i++)
        {
          sums.push_back((*i)->Summatory(inputs));
        }
        for(int i=0;i<sums.size();i++)
        {
          outPutProcessFeed.push_back(function->TransitionFunction(i,sums));
        }
    }
    return outPutProcessFeed;
}
Layer::~Layer()
{
    delete function;
    for (int node = 0; node < layerPerceptron.size(); ++node)
    {
        delete layerPerceptron[node];
    }
};