#include "../../thirdParty/googletest/include/gtest/gtest.h"
#include "../include/NeuralNetwork.h"
#include <iostream>
#include <random>
#include <string>
#include <typeinfo>
#include <vector>
string ruta = "result.json";

double RoundPlaces1(double value, int to)
{
    double places = pow(10.0, to);
    return round(value * places) / places;
}
bool FindElement(int* array,int size, int element)
{
	bool result = false;
	for (int i = 0; i < size; ++i)
	{
		if(array[i] == element)
			result = true;
	}
	return result;
}
TEST(neuralNetwork, constructorCustomize)
{
	int inputNodes = 3;
    int quantityLayersHidden = 2;
    int hiddenNodes = 4;
    int outputNodes = 5;
    double learnRate = 0.01;
    double momentum = 0.02;
    double error =0.12;
    NeuralNetwork net {inputNodes,quantityLayersHidden,hiddenNodes,TypeOfTransition::SIGMOID,outputNodes,TypeOfTransition::SIGMOID,learnRate,momentum,error};

    EXPECT_EQ(net.neuralNetwork.size(),4);
    // capa de entrada
    EXPECT_EQ(net.neuralNetwork[0]->layerType,LayerType::INPUT);
    EXPECT_EQ(net.neuralNetwork[0]->layerPerceptron.size(),inputNodes);
    EXPECT_EQ(net.neuralNetwork[0]->transitionType,TypeOfTransition::STEPBYSTEP);

    for(int perceptron = 0;perceptron < net.neuralNetwork[0]->layerPerceptron.size();perceptron++)
    {
    	EXPECT_EQ(net.neuralNetwork[0]->layerPerceptron[perceptron]->weights.size(),1);	
    }
    //capas oculta
    for(int layer = 1;layer < net.neuralNetwork.size()-1; layer++)
    {
	    EXPECT_EQ(net.neuralNetwork[layer]->layerType,LayerType::HIDDEN);
	    EXPECT_EQ(net.neuralNetwork[layer]->layerPerceptron.size(),hiddenNodes);
	    EXPECT_EQ(net.neuralNetwork[layer]->transitionType,TypeOfTransition::SIGMOID);
	    for(int perceptron = 0; perceptron < net.neuralNetwork[layer]->layerPerceptron.size();perceptron++)
	    {
	    	EXPECT_EQ(net.neuralNetwork[layer]->layerPerceptron[perceptron]->weights.size(),net.neuralNetwork[layer-1]->layerPerceptron.size());
	    }
    }
    //capa de salida
    EXPECT_EQ(net.neuralNetwork[net.neuralNetwork.size()-1]->layerType,LayerType::OUTPUT);
    EXPECT_EQ(net.neuralNetwork[net.neuralNetwork.size()-1]->layerPerceptron.size(),outputNodes);
    EXPECT_EQ(net.neuralNetwork[net.neuralNetwork.size()-1]->transitionType,TypeOfTransition::SIGMOID);
    for(int perceptron = 0;perceptron < net.neuralNetwork[net.neuralNetwork.size()-1]->layerPerceptron.size();perceptron++)
    {
    	EXPECT_EQ(net.neuralNetwork[net.neuralNetwork.size()-1]->layerPerceptron[perceptron]->weights.size(),net.neuralNetwork[net.neuralNetwork.size()-2]->layerPerceptron.size());	
    }
}
TEST(NeuralNetwork, FeedForwardWithHiperbolicTangentAndSoftmax)
{
	int inputNodes = 4;
    int quantityLayersHidden = 1;
    int hiddenNodes = 5;
    int outputNodes = 3;
    double learnRate = 0.01;
    double momentum = 0.02;
    double error =0.12;

    NeuralNetwork net {inputNodes,quantityLayersHidden,hiddenNodes,TypeOfTransition::TANGHIPERBOLIC,outputNodes,TypeOfTransition::SOFTMAX,learnRate,momentum,error};
	vector<double> inputs {0.20,0.50,0.60,0.10};
    for (int i = 0; i < 5; ++i)
    {
	    net.FeedForward(inputs);
	    //capa de entrada
	    EXPECT_EQ(net.neuralNetwork[0]->outPutProcessFeed[0],0.2);
	    EXPECT_EQ(net.neuralNetwork[0]->outPutProcessFeed[1],0.5);
	    EXPECT_EQ(net.neuralNetwork[0]->outPutProcessFeed[2],0.6);
	    EXPECT_EQ(net.neuralNetwork[0]->outPutProcessFeed[3],0.1);
	    //capa oculta 
	    EXPECT_EQ(RoundPlaces1(net.neuralNetwork[1]->outPutProcessFeed[0],6),-0.259905);
	    EXPECT_EQ(RoundPlaces1(net.neuralNetwork[1]->outPutProcessFeed[1],6), 0.142383);
	    EXPECT_EQ(RoundPlaces1(net.neuralNetwork[1]->outPutProcessFeed[2],6),-0.251482);
	    EXPECT_EQ(RoundPlaces1(net.neuralNetwork[1]->outPutProcessFeed[3],6),-0.570613);
	    EXPECT_EQ(RoundPlaces1(net.neuralNetwork[1]->outPutProcessFeed[4],6),-0.312385);
	    //capa de salida   
	    EXPECT_EQ(RoundPlaces1(net.neuralNetwork[2]->outPutProcessFeed[0],6),0.144521);
	    EXPECT_EQ(RoundPlaces1(net.neuralNetwork[2]->outPutProcessFeed[1],6),0.555696);
	    EXPECT_EQ(RoundPlaces1(net.neuralNetwork[2]->outPutProcessFeed[2],6),0.299784);
    }
}
TEST(NeuralNetwork, ShuffleIndex)
{
	int inputNodes = 4;
    int quantityLayersHidden = 1;
    int hiddenNodes = 5;
    int outputNodes = 3;
    double learnRate = 0.01;
    double momentum = 0.02;
    double error =0.12;

    NeuralNetwork net {inputNodes,quantityLayersHidden,hiddenNodes,TypeOfTransition::TANGHIPERBOLIC,outputNodes,TypeOfTransition::SOFTMAX,learnRate,momentum,error};
	int* result = new int[10];
	size_t size = 10;
	for (int i = 0; i < size; ++i)
	{
		result[i] = i;
	}
	for (int i = 0; i < 10; ++i)
	{
		net.ShuffleIndex(result,size);
		for (int i = 0; i < size; ++i)
		{
			EXPECT_TRUE(FindElement(result,size,i));
		}
	}
}
TEST(NeuralNetwork, FeedForwardWithSigmoid)
{}
TEST(NeuralNetwork, FeedForwardWithSigmoidAndSoftmax)
{}
TEST(NeuralNetwork, ComputeGradient)
{
	int inputNodes = 4;
    int quantityLayersHidden = 1;
    int hiddenNodes = 5;
    int outputNodes = 3;
    double learnRate = 0.001;
    double momentum = 0.02;
    double error = 0.12;
    NeuralNetwork net {inputNodes,quantityLayersHidden,hiddenNodes,TypeOfTransition::TANGHIPERBOLIC,outputNodes,TypeOfTransition::SOFTMAX,learnRate,momentum,error};
    
    vector<double> input {0.20,0.50,0.60,0.10};
    vector<double> expected {0,0,1};
    vector<vector<double>> generalError;

    net.FeedForward(input);

	net.ComputeGradient(expected, generalError);
    //error de salida
    EXPECT_EQ(RoundPlaces1(generalError[0][0],6), -0.144521);
    EXPECT_EQ(RoundPlaces1(generalError[0][1],6), -0.555696);
    EXPECT_EQ(RoundPlaces1(generalError[0][2],6), 0.700216);
    //gradiente de la capa de salida
    /*derivada
    	0.123635
		0.246898
		0.209914
    */   
    EXPECT_EQ(RoundPlaces1(net.neuralNetwork[2]->layerPerceptron[0]->gradient,6), -0.017868);
    EXPECT_EQ(RoundPlaces1(net.neuralNetwork[2]->layerPerceptron[1]->gradient,6), -0.137200);
    EXPECT_EQ(RoundPlaces1(net.neuralNetwork[2]->layerPerceptron[2]->gradient,6), 0.146985);

    //gradiente de la capa de las capas ocultas
    //derivadas
	EXPECT_EQ(RoundPlaces1(net.neuralNetwork[1]->function->Derived(net.neuralNetwork[1]->outPutProcessFeed[0]),6), 0.932449);
    EXPECT_EQ(RoundPlaces1(net.neuralNetwork[1]->function->Derived(net.neuralNetwork[1]->outPutProcessFeed[1]),6), 0.979727);
    EXPECT_EQ(RoundPlaces1(net.neuralNetwork[1]->function->Derived(net.neuralNetwork[1]->outPutProcessFeed[2]),6), 0.936757);
    EXPECT_EQ(RoundPlaces1(net.neuralNetwork[1]->function->Derived(net.neuralNetwork[1]->outPutProcessFeed[3]),6), 0.674400);
    EXPECT_EQ(RoundPlaces1(net.neuralNetwork[1]->function->Derived(net.neuralNetwork[1]->outPutProcessFeed[4]),6), 0.902416);
    /* pesos
	capa: 2
	 perceptron: 0 -0.8185342108 -0.8525018496 -0.2317157041 0.8276348841 -0.0711083501  sesgo: -0.8998320326
	 perceptron: 1 0.5404090940 -0.7492692488 0.3769106021 0.2590868362 0.4508239973  sesgo: 0.7771444281
	 perceptron: 2 -0.3873563382 0.0265474044 0.6919631206 0.6830212791 -0.1692107691  sesgo: -0.0641652630*/
    //sumatoria de pesos por gradientes
    /*
    	-0.017868 X -0.8185342108 + -0.137200 X 0.5404090940 + 0.146985 X -0.3873563382 = -0.11645413
		-0.017868 X -0.8525018496 + -0.137200 X -0.7492692488 + 0.146985 X 0.0265474044 = 0.12193431
		-0.017868 X -0.2317157041 + -0.137200 X 0.3769106021 + 0.146985 X 0.6919631206 = 0.05413636
		-0.017868 X 0.82763488411 + -0.137200 X 0.2590868362 + 0.146985 X 0.6830212791 = 0.05005899
		-0.017868 X -0.0711083501 + -0.137200 X 0.4508239973 + 0.146985 X -0.1692107691 = -0.085454
    */
    EXPECT_EQ(RoundPlaces1(net.neuralNetwork[1]->layerPerceptron[0]->gradient,6), -0.108588);
    EXPECT_EQ(RoundPlaces1(net.neuralNetwork[1]->layerPerceptron[1]->gradient,6), 0.119462);
    EXPECT_EQ(RoundPlaces1(net.neuralNetwork[1]->layerPerceptron[2]->gradient,6), 0.050712);
    EXPECT_EQ(RoundPlaces1(net.neuralNetwork[1]->layerPerceptron[3]->gradient,6), 0.03376);
    EXPECT_EQ(RoundPlaces1(net.neuralNetwork[1]->layerPerceptron[4]->gradient,6), -0.077115);
    net.UpdateWeightsAndBias();
}
TEST(NeuralNetwork, UpdateWeights)
{

}
/*TEST(NeuralNetwork, BackPropagation)
{
	int inputNodes = 4;
    int quantityLayersHidden = 1;
    int hiddenNodes = 5;
    int outputNodes = 3;
    double learnRate = 0.01;
    double momentum = 0.02;
    double error =0.12;
    NeuralNetwork net {inputNodes,quantityLayersHidden,hiddenNodes,TypeOfTransition::TANGHIPERBOLIC,outputNodes,TypeOfTransition::SOFTMAX,learnRate,momentum,error};

    vector<vector<double>> inputs {{0.20,0.50,0.60,0.10},{0.20,0.50,0.60,0.10}};
    vector<vector<double>> expected {{0,0,1},{0,0,1}};
    int* sequence = new int[2];
    sequence[0] = 0;
    sequence[1] = 1;
	net.Backpropagation(inputs ,expected, sequence);
}*

TEST(NeuralNetwork, batchesTrain)
 {
	NeuralNetwork n2{};
	n2.TrainByBatches(ruta);
    EXPECT_EQ(1,1);
}*/
TEST(NeuralNetowrk,evaluateIncremental)
{
	int inputNodes = 4;
    int quantityLayersHidden = 1;
    int hiddenNodes = 5;
    int outputNodes = 3;
    double learnRate = 0.01;
    double momentum = 0.02;
    double error = 0.012;
    NeuralNetwork net {inputNodes,quantityLayersHidden,hiddenNodes,TypeOfTransition::TANGHIPERBOLIC,outputNodes,TypeOfTransition::SOFTMAX,learnRate,momentum,error};

	net.Train(ruta);
	vector<double> result;
	vector<double> setosa{5.4,3.9,1.7,0.4};
	result = net.Evaluate(setosa);
	/*EXPECT_EQ(net.neuralNetwork[net.neuralNetwork.size()-1]->outPutProcessFeed[0],0);
	EXPECT_EQ(net.neuralNetwork[net.neuralNetwork.size()-1]->outPutProcessFeed[1],0);
	EXPECT_EQ(net.neuralNetwork[net.neuralNetwork.size()-1]->outPutProcessFeed[2],1);
	vector<double> versicolor{6.7,3.1,4.4,1.4};
	net.Evaluate(versicolor);
	EXPECT_EQ(net.neuralNetwork[net.neuralNetwork.size()-1]->outPutProcessFeed[0],0);
	EXPECT_EQ(net.neuralNetwork[net.neuralNetwork.size()-1]->outPutProcessFeed[1],1);
	EXPECT_EQ(net.neuralNetwork[net.neuralNetwork.size()-1]->outPutProcessFeed[2],0);
	vector<double> virginica{7.1,3.0,5.9,2.1};
	net.Evaluate(virginica);
	EXPECT_EQ(net.neuralNetwork[net.neuralNetwork.size()-1]->outPutProcessFeed[0],1);
	EXPECT_EQ(net.neuralNetwork[net.neuralNetwork.size()-1]->outPutProcessFeed[1],0);
	EXPECT_EQ(net.neuralNetwork[net.neuralNetwork.size()-1]->outPutProcessFeed[2],0);
	*/
    EXPECT_EQ(result[0],0);
    EXPECT_EQ(result[1],0);
    EXPECT_EQ(result[2],1);
    vector<double> versicolor{6.7,3.1,4.4,1.4};
    result = net.Evaluate(versicolor);
    EXPECT_EQ(result[0],0);
    EXPECT_EQ(result[1],1);
    EXPECT_EQ(result[2],0);
    vector<double> virginica{7.1,3.0,5.9,2.1};
    result = net.Evaluate(virginica);
    EXPECT_EQ(result[0],1);
    EXPECT_EQ(result[1],0);
    EXPECT_EQ(result[2],0);
}
TEST(NeuralNetowrk,evaluateIncrementalWithMomentum)
{
    int inputNodes = 4;
    int quantityLayersHidden = 1;
    int hiddenNodes = 5;
    int outputNodes = 3;
    double learnRate = 0.01;
    double momentum = 0.02;
    double error = 0.012;
    NeuralNetwork net {inputNodes,quantityLayersHidden,hiddenNodes,TypeOfTransition::TANGHIPERBOLIC,outputNodes,TypeOfTransition::SOFTMAX,learnRate,momentum,error};

    net.TrainByMomemtum(ruta);
    vector<double> result;
    vector<double> setosa{5.4,3.9,1.7,0.4};
    result = net.Evaluate(setosa);
    EXPECT_EQ(result[0],0);
    EXPECT_EQ(result[1],0);
    EXPECT_EQ(result[2],1);
    vector<double> versicolor{6.7,3.1,4.4,1.4};
    result = net.Evaluate(versicolor);
    EXPECT_EQ(result[0],0);
    EXPECT_EQ(result[1],1);
    EXPECT_EQ(result[2],0);
    vector<double> virginica{7.1,3.0,5.9,2.1};
    result = net.Evaluate(virginica);
    EXPECT_EQ(result[0],1);
    EXPECT_EQ(result[1],0);
    EXPECT_EQ(result[2],0);
    
}
TEST(NeuralNetowrk,evaluateIncrementalWithSigmoid)
{
    int inputNodes = 4;
    int quantityLayersHidden = 1;
    int hiddenNodes = 5;
    int outputNodes = 3;
    double learnRate = 0.01;
    double momentum = 0.02;
    double error = 0.012;
    NeuralNetwork net {inputNodes,quantityLayersHidden,hiddenNodes,TypeOfTransition::SIGMOID,outputNodes,TypeOfTransition::SIGMOID,learnRate,momentum,error};

    net.Train(ruta);
    
    vector<double> result;
    vector<double> setosa{5.4,3.9,1.7,0.4};
    result = net.Evaluate(setosa);
    EXPECT_EQ(result[0],0);
    EXPECT_EQ(result[1],0);
    EXPECT_EQ(result[2],1);
    vector<double> versicolor{6.7,3.1,4.4,1.4};
    result = net.Evaluate(versicolor);
    EXPECT_EQ(result[0],0);//1
    EXPECT_EQ(result[1],1);//0
    EXPECT_EQ(result[2],0);//0
    vector<double> virginica{7.7,2.6,6.9,2.3};
    result = net.Evaluate(virginica);
    EXPECT_EQ(result[0],1);
    EXPECT_EQ(result[1],0);
    EXPECT_EQ(result[2],0);
    
}
TEST(NeuralNetowrk,evaluateIncrementalWithSigmoidAndMomentum)
{
    int inputNodes = 4;
    int quantityLayersHidden = 1;
    int hiddenNodes = 5;
    int outputNodes = 3;
    double learnRate = 0.01;
    double momentum = 0.02;
    double error = 0.012;
    NeuralNetwork net {inputNodes,quantityLayersHidden,hiddenNodes,TypeOfTransition::SIGMOID,outputNodes,TypeOfTransition::SIGMOID,learnRate,momentum,error};

    net.TrainByMomemtum(ruta);
    
    vector<double> result;
    vector<double> setosa{5.4,3.9,1.7,0.4};
    result = net.Evaluate(setosa);
    EXPECT_EQ(result[0],0);
    EXPECT_EQ(result[1],0);
    EXPECT_EQ(result[2],1);
    vector<double> versicolor{6.7,3.1,4.4,1.4};
    result = net.Evaluate(versicolor);
    EXPECT_EQ(result[0],0);
    EXPECT_EQ(result[1],1);
    EXPECT_EQ(result[2],0);
    vector<double> virginica{7.1,3.0,5.9,2.1};
    result = net.Evaluate(virginica);
    EXPECT_EQ(result[0],1);
    EXPECT_EQ(result[1],0);
    EXPECT_EQ(result[2],0);
    
}
TEST(NeuralNetowrk,evaluateByBatchesWithHiperbolicTangAndSoftmax)
{
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
    EXPECT_EQ(result[0],0);
    EXPECT_EQ(result[1],0);
    EXPECT_EQ(result[2],1);
    vector<double> versicolor{6.7,3.1,4.4,1.4};
    result = net.Evaluate(versicolor);
    EXPECT_EQ(result[0],0);
    EXPECT_EQ(result[1],1);
    EXPECT_EQ(result[2],0);
    
}
TEST(NeuralNetowrk,evaluateByBatchesWithSigmoid)
{
    int inputNodes = 4;
    int quantityLayersHidden = 1;
    int hiddenNodes = 5;
    int outputNodes = 3;
    double learnRate = 0.01;
    double momentum = 0.02;
    double error = 0.012;
    NeuralNetwork net {inputNodes,quantityLayersHidden,hiddenNodes,TypeOfTransition::SIGMOID,outputNodes,TypeOfTransition::SIGMOID,learnRate,momentum,error};

    net.TrainByBatches(ruta);
    
     vector<double> result;
    vector<double> setosa{5.4,3.9,1.7,0.4};
    result = net.Evaluate(setosa);
    EXPECT_EQ(result[0],0);
    EXPECT_EQ(result[1],0);
    EXPECT_EQ(result[2],1);
    vector<double> versicolor{4.9,2.4,3.3,1.0};
    result = net.Evaluate(versicolor);
    EXPECT_EQ(result[0],0);
    EXPECT_EQ(result[1],1);
    EXPECT_EQ(result[2],0);
    vector<double> virginica{7.1,3.0,5.9,2.1};
    result = net.Evaluate(virginica);
    EXPECT_EQ(result[0],1);
    EXPECT_EQ(result[1],0);
    EXPECT_EQ(result[2],0);
}