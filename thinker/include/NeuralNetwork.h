#include "Layer.h"
#include "Data.h"
#include <typeinfo>
#include <random>

#define GTest

class NeuralNetwork
{
public:
    #ifdef GTest
    public:
    #else
    private:
    #endif
    vector<Layer*> neuralNetwork;
    double error = 1;
    double learnRate = 0.020;
    int limitLoop=1000;
    double momentum = 0;
    default_random_engine generator;
    uniform_real_distribution<double> distribution{-1,1};

    public:
        NeuralNetwork();
        NeuralNetwork(int inputNodes,int quantityLayersHidden,int hiddenNodes,int outputNodes);
        NeuralNetwork(int inputNodes,int quantityLayersHidden,int hiddenNodes,TypeOfTransition hiddenFunction,int outputNodes,TypeOfTransition outputFunction,double learnRate,double momentum,double error);
        void FeedForward(vector<double>& inputs);
        ~NeuralNetwork();
        void ShowWeights();
        void Train(const string& exmaples);
        void TrainByMomemtum(const string& exmaples);
        void SetTransitionFunction(int layer, TypeOfTransition typeFunction);
        void TrainByBatches(const string& examples);
        vector<double> Evaluate(vector<double>& outPut);
    #ifdef GTest
        public:
    #else    
        private:
    #endif
        int* ShuffleIndex(int* sequence,size_t size);
        double Backpropagation(vector<vector<double>>& inputs,vector<vector<double>>& expected,int * sequence);
        double BackpropagationByBatches(vector<vector<double>>& inputs,vector<vector<double>>& expected,int * sequence);
        void ComputeGradient(vector<double>& expected,vector<vector<double>>& generalError);
        void UpdateWeightsAndBias();
        void UpdateWeightsBiasByMomentum(vector<vector<vector<double>>>& diffWeight,vector<vector<double>>& diffBias);
		double MeanSquaredError(vector<vector<double>>& generalError);
		void SummaryGradients(vector<vector<double>>& gradientsTotal);	
        double CalculateError(vector<vector<double>>& errorValue);
};
