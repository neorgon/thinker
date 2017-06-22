#include "../../thirdParty/googletest/include/gtest/gtest.h"
#include "../include/NeuralNetwork.h"
#include <cmath>
#include <random>
#include <iostream>
#include <vector>


TEST_F(NeuralNetworkTest, FeedForward_Layer_InPut_Values1)
{
	NeuralNetwork net{};
	vector<double> input{5.1,3.5,1.4,0.2};
	net.FeedForward(input);
	ASSERT_NEAR(net.neuralNetwork[net.neuralNetwork.size()-3]->outPutProcessFeed[0],5.1,0);
	ASSERT_NEAR(net.neuralNetwork[net.neuralNetwork.size()-3]->outPutProcessFeed[1],3.5,0);
	ASSERT_NEAR(net.neuralNetwork[net.neuralNetwork.size()-3]->outPutProcessFeed[2],1.4,0);
	ASSERT_NEAR(net.neuralNetwork[net.neuralNetwork.size()-3]->outPutProcessFeed[3],0.2,0);
	
}


TEST_F(NeuralNetworkTest, FeedForward_Layer_Hidden_Values1)
{
	NeuralNetwork net{};
	vector<double> input{5.1,3.5,1.4,0.2};
	net.FeedForward(input);
	ASSERT_NEAR(net.neuralNetwork[net.neuralNetwork.size()-2]->outPutProcessFeed[0],-0.999999,0.000001);
	ASSERT_NEAR(net.neuralNetwork[net.neuralNetwork.size()-2]->outPutProcessFeed[1],0.996601,0.000001);
	ASSERT_NEAR(net.neuralNetwork[net.neuralNetwork.size()-2]->outPutProcessFeed[2],0.978904,0.000001);
	ASSERT_NEAR(net.neuralNetwork[net.neuralNetwork.size()-2]->outPutProcessFeed[3],0.990252,0.000001);
	ASSERT_NEAR(net.neuralNetwork[net.neuralNetwork.size()-2]->outPutProcessFeed[4],0.720304,0.000001);
	ASSERT_NEAR(net.neuralNetwork[net.neuralNetwork.size()-2]->outPutProcessFeed[5],-0.999999,0.000001);
}


TEST_F(NeuralNetworkTest, FeedForward_Layer_OutPut_Values1)
{
	NeuralNetwork net{};
	vector<double> input{5.1,3.5,1.4,0.2};
	net.FeedForward(input);
	ASSERT_NEAR(net.neuralNetwork[net.neuralNetwork.size()-1]->outPutProcessFeed[0],0.606667,0.000001);
	ASSERT_NEAR(net.neuralNetwork[net.neuralNetwork.size()-1]->outPutProcessFeed[1],0.359006,0.000001);
	ASSERT_NEAR(net.neuralNetwork[net.neuralNetwork.size()-1]->outPutProcessFeed[2],0.034326,0.000001);
	
}


TEST_F(NeuralNetworkTest, FeedForward_Layer_InPut_Values2)
{
	NeuralNetwork net{};
	vector<double> input{7.0,3.2,4.7,1.4};
	net.FeedForward(input);
	ASSERT_NEAR(net.neuralNetwork[net.neuralNetwork.size()-3]->outPutProcessFeed[0],7.0,0);
	ASSERT_NEAR(net.neuralNetwork[net.neuralNetwork.size()-3]->outPutProcessFeed[1],3.2,0);
	ASSERT_NEAR(net.neuralNetwork[net.neuralNetwork.size()-3]->outPutProcessFeed[2],4.7,0);
	ASSERT_NEAR(net.neuralNetwork[net.neuralNetwork.size()-3]->outPutProcessFeed[3],1.4,0);
	
}

TEST_F(NeuralNetworkTest, FeedForward_Layer_Hidden_Values2)
{
	NeuralNetwork net{};
	vector<double> input{7.0,3.2,4.7,1.4};
	net.FeedForward(input);
	ASSERT_NEAR(net.neuralNetwork[net.neuralNetwork.size()-2]->outPutProcessFeed[0],-0.999996,0.00001);
	ASSERT_NEAR(net.neuralNetwork[net.neuralNetwork.size()-2]->outPutProcessFeed[1],0.999629,0.000001);
	ASSERT_NEAR(net.neuralNetwork[net.neuralNetwork.size()-2]->outPutProcessFeed[2],0.999998,0.000001);
	ASSERT_NEAR(net.neuralNetwork[net.neuralNetwork.size()-2]->outPutProcessFeed[3],0.998074,0.000001);
	ASSERT_NEAR(net.neuralNetwork[net.neuralNetwork.size()-2]->outPutProcessFeed[4],0.979233,0.000001);
	ASSERT_NEAR(net.neuralNetwork[net.neuralNetwork.size()-2]->outPutProcessFeed[5],-0.999999,0.000001);
}

TEST_F(NeuralNetworkTest, FeedForward_Layer_OutPut_Values2)
{
	NeuralNetwork net{};
	vector<double> input{7.0,3.2,4.7,1.4};
	net.FeedForward(input);
	ASSERT_NEAR(net.neuralNetwork[net.neuralNetwork.size()-1]->outPutProcessFeed[0],0.620335,0.000001);
	ASSERT_NEAR(net.neuralNetwork[net.neuralNetwork.size()-1]->outPutProcessFeed[1],0.338987,0.000001);
	ASSERT_NEAR(net.neuralNetwork[net.neuralNetwork.size()-1]->outPutProcessFeed[2],0.040677,0.000001);
	
}

TEST_F(NeuralNetworkTest, FeedForward_Layer_InPut_Values3)
{
	NeuralNetwork net{};
	vector<double> input{6.3,3.3,6,2.5};
	net.FeedForward(input);
	ASSERT_NEAR(net.neuralNetwork[net.neuralNetwork.size()-3]->outPutProcessFeed[0],6.3,0);
	ASSERT_NEAR(net.neuralNetwork[net.neuralNetwork.size()-3]->outPutProcessFeed[1],3.3,0);
	ASSERT_NEAR(net.neuralNetwork[net.neuralNetwork.size()-3]->outPutProcessFeed[2],6,0);
	ASSERT_NEAR(net.neuralNetwork[net.neuralNetwork.size()-3]->outPutProcessFeed[3],2.5,0);
	
}

TEST_F(NeuralNetworkTest, FeedForward_Layer_Hidden_Values3)
{
	NeuralNetwork net{};
	vector<double> input{6.3,3.3,6,2.5};
	net.FeedForward(input);
	ASSERT_NEAR(net.neuralNetwork[net.neuralNetwork.size()-2]->outPutProcessFeed[0],-0.999803,0.001);
	ASSERT_NEAR(net.neuralNetwork[net.neuralNetwork.size()-2]->outPutProcessFeed[1],0.999014,0.001);
	ASSERT_NEAR(net.neuralNetwork[net.neuralNetwork.size()-2]->outPutProcessFeed[2],0.999999,0.001);
	ASSERT_NEAR(net.neuralNetwork[net.neuralNetwork.size()-2]->outPutProcessFeed[3],0.982603,0.001);
	ASSERT_NEAR(net.neuralNetwork[net.neuralNetwork.size()-2]->outPutProcessFeed[4],0.847606,0.001);
	ASSERT_NEAR(net.neuralNetwork[net.neuralNetwork.size()-2]->outPutProcessFeed[5],-0.999999,0.001);
}

TEST_F(NeuralNetworkTest, FeedForward_Layer_OutPut_Values3)
{
	NeuralNetwork net{};
	vector<double> input{6.3,3.3,6,2.5};
	net.FeedForward(input);
	ASSERT_NEAR(net.neuralNetwork[net.neuralNetwork.size()-1]->outPutProcessFeed[0],0.610937,0.001);
	ASSERT_NEAR(net.neuralNetwork[net.neuralNetwork.size()-1]->outPutProcessFeed[1],0.351690,0.001);
	ASSERT_NEAR(net.neuralNetwork[net.neuralNetwork.size()-1]->outPutProcessFeed[2],0.037371,0.001);
}

TEST_F(NeuralNetworkTest, UpdateWeightsAndBias_outputLayer)
{
	NeuralNetwork net{};
	vector<vector<double>> gradientes,generalError;
	vector<vector<vector<double>>> WeightsObtains {
		{
			{-0.984604,-0.866316,0.373545,0.860873},
			{0.307799,0.402354,0.524385,-0.905072},
			{0.512930,-0.269248,0.965130,0.506716},
			{0.769319,-0.127241,-0.044562,-0.450189},
			{0.795349,-0.878845,0.009055,-0.361932},
			{-0.818534,-0.852502,-0.231716,0.827635}
		},
		{
			{-0.898384,0.538966,-0.750686,0.375477,0.258044,0.452271},
			{-0.386529,0.025724,0.691154,0.682202,-0.169806,-0.063339},
			{0.142989,-0.933572,-0.002726,0.496901,0.781705,0.683758}
		}
	};
	
	vector<double> input{5.1,3.5,1.4,0.2};
	vector<double> outs{0,0,1};
	net.FeedForward(input);
	net.ComputeGradient(outs,gradientes,generalError);
	net.UpdateWeightsAndBias(gradientes);
	for(int i=1;i<net.neuralNetwork.size();i++){
		//cout<<"layer "<<i<<"\n";
		for(int j=0;j<net.neuralNetwork[i]->layerPerceptron.size();j++){
			//cout<<"perceptron "<<j<<"\n";
			for(int k=0;k<net.neuralNetwork[i]->layerPerceptron[j]->weights.size();k++){
				//cout<<net.neuralNetwork[i]->layerPerceptron[j]->weights[k]<<" = "<<WeightsObtains[i-1][j][k]<<" dif ->"<<net.neuralNetwork[i]->layerPerceptron[j]->weights[k]-WeightsObtains[i-1][j][k]<<"\n";
				//cout<<"peso "<<k<<" = "<<WeightsObtains[i-1][j][k]<<"!";
				ASSERT_NEAR(net.neuralNetwork[i]->layerPerceptron[j]->weights[k],WeightsObtains[i-1][j][k],0.000009);
			}
		}
	}
}
/*
void mostrarPesos(){
	NeuralNetwork net{};
	vector<double> input{5.1,3.5,1.4,0.2};
	for(int k=1;k<net.neuralNetwork.size();k++){
		cout<<"layer"<<k<<"\n";
		for(int i=0;i<net.neuralNetwork[k]->layerPerceptron.size();i++){
			cout<<"perceotron "<<i<<" \n";
			
			for(int j=0;j<net.neuralNetwork[k]->layerPerceptron[i]->weights.size();j++){
				cout<<"peso = "<<net.neuralNetwork[k]->layerPerceptron[i]->weights[j];			
			}
			cout<<"\n";
			for(int j=0;j<net.neuralNetwork[k]->layerPerceptron[i]->weights.size();j++){
				cout<<" bias = "<<net.neuralNetwork[k]->layerPerceptron[i]->bias;
				
			}
			cout<<"\n";
		}
	}
}

int main(){

mostrarPesos();
}/**/
