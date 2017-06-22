#include "../../thirdParty/googletest/include/gtest/gtest.h"
#include "../include/Layer.h"
#include <iostream>
#include <random>
#include <vector>

default_random_engine generator;
uniform_real_distribution<double> distribution{-1,1};
double RoundPlaces(double value, int to)
{
    double places = pow(10.0, to);
    return round(value * places) / places;
}
TEST(LayerTest, BuildHiddenLayer)
 {
 	int nodes = 4;
 	int inputs = 1;
	Layer* hidden = new Layer{nodes,inputs,TypeOfTransition::TANGHIPERBOLIC,LayerType::HIDDEN,distribution,generator};
    EXPECT_EQ(hidden->layerPerceptron.size(),nodes);
    EXPECT_EQ(hidden->layerType,LayerType::HIDDEN);
    EXPECT_EQ(hidden->transitionType,TypeOfTransition::TANGHIPERBOLIC);
    for (int perceptron = 0; perceptron < hidden->layerPerceptron.size(); ++perceptron)
    {
    	EXPECT_EQ(hidden->layerPerceptron[perceptron]->weights.size(),inputs);
    }
}
TEST(LayerTest, EvaluateHiddenLayerWithHiperbolicTangentSingleInput)
{
 	int nodes = 4;
 	int inputs = 1;
	Layer* hidden = new Layer{nodes,inputs,TypeOfTransition::TANGHIPERBOLIC,LayerType::HIDDEN,distribution,generator};
    vector<double> input {0.3};
    vector<double> output{};
    for (int iteration = 0; iteration < 5; ++iteration)
    {
        output = hidden->Evaluate(input);
        EXPECT_EQ(RoundPlaces(output[0],6),-0.821592);
        EXPECT_EQ(RoundPlaces(output[1],6),0.749992);
        EXPECT_EQ(RoundPlaces(output[2],6),0.313115);
        EXPECT_EQ(RoundPlaces(output[3],6),0.568369);
    }

}
TEST(LayerTest, EvaluateHiddenLayerWithHiperbolicTangentMultiplesInput)
 {	
 	int nodes = 2;
 	int inputs = 3;
	Layer* hidden = new Layer{nodes,inputs,TypeOfTransition::TANGHIPERBOLIC,LayerType::HIDDEN,distribution,generator};
    EXPECT_EQ(hidden->layerPerceptron.size(),nodes);
    for (int perceptron = 0; perceptron < hidden->layerPerceptron.size(); ++perceptron)
    {
    	EXPECT_EQ(hidden->layerPerceptron[perceptron]->weights.size(),inputs);
    }
    vector<double> input {0.3,0.25,0.8};
    vector<double> output{};
    for (int iteration = 0; iteration < 5; ++iteration)
    {
        output = hidden->Evaluate(input);
        EXPECT_EQ(RoundPlaces(output[0],6),-0.213151);
        EXPECT_EQ(RoundPlaces(output[1],6),0.463626);
    }
}
TEST(LayerTest,OutputLayerWithSigmoidMultiplesInputs)
{
 	int nodes = 2;
 	int inputs = 2;
	Layer * out = new Layer{nodes,inputs,TypeOfTransition::SIGMOID,LayerType::OUTPUT,distribution,generator};

	EXPECT_EQ(out->layerPerceptron.size(),nodes);
    for (int perceptron = 0; perceptron < out->layerPerceptron.size(); ++perceptron)
    {
    	EXPECT_EQ(out->layerPerceptron[perceptron]->weights.size(),inputs);
    }
    vector<double> input {0.3,0.25};
    vector<double> output{};
    for (int iteration = 0; iteration < 5; ++iteration)
    {
        output = out->Evaluate(input);
        EXPECT_EQ(RoundPlaces(output[0],6),0.377664);
        EXPECT_EQ(RoundPlaces(output[1],6),0.293149);
    }
}
TEST(LayerTest,InputLayerWithMultiplesInputs)
{
 	int nodes = 5;
 	int inputs = 1;
	Layer * layer = new Layer{nodes,inputs,TypeOfTransition::SIGMOID,LayerType::INPUT,distribution,generator};

	EXPECT_EQ(layer->layerPerceptron.size(),nodes);
    for (int perceptron = 0; perceptron < layer->layerPerceptron.size(); ++perceptron)
    {
    	EXPECT_EQ(layer->layerPerceptron[perceptron]->weights.size(),inputs);
    }
    vector<double> input {0.3,0.25,1.2,0.68,0.89};
    vector<double> output{};
    for (int iteration = 0; iteration < 5; ++iteration)
    {
        output = layer->Evaluate(input);
        EXPECT_EQ(output[0],0.3);
        EXPECT_EQ(output[1],0.25);
        EXPECT_EQ(output[2],1.2);
        EXPECT_EQ(output[3],0.68);
        EXPECT_EQ(output[4],0.89);
    }
}