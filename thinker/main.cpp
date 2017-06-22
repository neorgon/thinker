/*#include "include/TransitionHiperbolicTangent.h"
#include "include/TransitionSoftMax.h"
#include "include/TransitionByStep.h"
#include "include/TransitionSigmoid.h"
#include "include/Perceptron.h"*/
#include <iostream>
#include <cmath>
#include "include/NeuralNetwork.h"
using namespace std;


int main(int argc, char const *argv[])
{
    string ruta = "result.json";
    int inputNodes = 4;
    int quantityLayersHidden = 1;
    int hiddenNodes = 5;
    int outputNodes = 3;
    double learnRate = 0.01;
    double momentum = 0.02;
    double error = 0.012;
    NeuralNetwork net {inputNodes,quantityLayersHidden,hiddenNodes,TypeOfTransition::TANGHIPERBOLIC,outputNodes,TypeOfTransition::SOFTMAX,learnRate,momentum,error};
    net.TrainByBatches(ruta);
    vector<double> result;
    vector<double> setosa{5.4,3.9,1.7,0.4};
    result = net.Evaluate(setosa);
    cout<< result[0]<<" "<< result[1]<<" "<< result[2]<<"\n";
    vector<double> versicolor{6.7,3.1,4.4,1.4};
    result = net.Evaluate(versicolor);
    cout<< result[0]<<" "<< result[1]<<" "<< result[2]<<"\n";
    vector<double> virginica{7.2,3.0,5.8,1.6};
    result = net.Evaluate(virginica);
    cout<< result[0]<<" "<< result[1]<<" "<< result[2]<<"\n";

 }

