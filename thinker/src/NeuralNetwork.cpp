#include "../include/NeuralNetwork.h"
#include <typeinfo>
#include <iomanip>
using std::setw;

NeuralNetwork::NeuralNetwork()
{
}
NeuralNetwork::NeuralNetwork(int inputNodes,int quantityLayersHidden,int hiddenNodes,int outputNodes)
{
}
NeuralNetwork::NeuralNetwork(int inputNodes,int quantityLayersHidden,int hiddenNodes,TypeOfTransition hiddenFunction,int outputNodes,TypeOfTransition outputFunction,double learnRate,double momentum,double error):learnRate{learnRate},momentum{momentum},error{error}
{
	int inputsPerNode = 1;
	int weights = inputNodes;
	neuralNetwork.push_back(new Layer(inputNodes,inputsPerNode,TypeOfTransition::STEPBYSTEP,LayerType::INPUT, distribution, generator));

	for (int hiddenLayer = 0; hiddenLayer < quantityLayersHidden; ++hiddenLayer)
	{
		neuralNetwork.push_back(new Layer(hiddenNodes,weights,hiddenFunction,LayerType::HIDDEN, distribution, generator));
		weights = hiddenNodes;
	}
	neuralNetwork.push_back(new Layer(outputNodes,weights,outputFunction,LayerType::OUTPUT, distribution, generator));
}
NeuralNetwork::~NeuralNetwork()
{
	for(auto & layer:neuralNetwork)
	{
		delete layer;	
	}
}
void NeuralNetwork::Train(const string& examples)
{
	vector<vector<double>> inputs;
    vector<vector<double>> expectedValue;
	
	Data* datos = new Data(examples, inputs, expectedValue);
	double errorN = 1;
	int * sequence = new int[inputs.size()];
	for (int i = 0; i < inputs.size(); ++i)
	{
		sequence[i] = i;
	}

	for (int i = 0; i < limitLoop; i++)
	{
		if(errorN < error)
		{
			cout <<"salio de error\n";
			break;
		}
		sequence = ShuffleIndex(sequence,inputs.size());
		errorN = Backpropagation(inputs,expectedValue,sequence);
	}
	delete datos;
}
void NeuralNetwork::FeedForward(vector<double>& inputs)
{
 	neuralNetwork[0]->Evaluate(inputs);
 	for(int i = 1; i < neuralNetwork.size(); i++)
 	{
 		neuralNetwork[i]->Evaluate(neuralNetwork[i-1]->outPutProcessFeed);
 	}
}
vector<double> NeuralNetwork::Evaluate(vector<double>& input)
{
 	vector<double> result{};
 	FeedForward(input);
 	double max=0;
 	int position=0;
 	for (int output = 0; output < neuralNetwork[neuralNetwork.size()-1]->outPutProcessFeed.size(); ++output)
 	{
 		if(neuralNetwork[neuralNetwork.size()-1]->outPutProcessFeed[output] > max)
 		{
 			max = neuralNetwork[neuralNetwork.size()-1]->outPutProcessFeed[output];
 			position = output;
 		}
 	}
 	for (int output = 0; output < neuralNetwork[neuralNetwork.size()-1]->outPutProcessFeed.size(); ++output)
 	{
 		if(output == position)
 			result.push_back(1);
 		else
 			result.push_back(0);
 	}
 	return result;
 }

double NeuralNetwork::Backpropagation(vector<vector<double>>& inputs,vector<vector<double>>& expected,int * sequence)
{
	vector<vector<double>> generalError{};
	vector<vector<double>> delta{};

	for(int i = 0 ; i <inputs.size();i++)
	{
		FeedForward(inputs[sequence[i]]);
		ComputeGradient(expected[sequence[i]],generalError);
		UpdateWeightsAndBias();		
	}
	return MeanSquaredError(generalError);
}
void NeuralNetwork::ComputeGradient(vector<double>& expected,vector<vector<double>>& generalError)
{
	double error = 0;
	double derived = 0;
	double sum = 0;
	double gradient = 0;
	vector<double> errorIteration {};
	//calculo de la gadiente de la capa de salida
	for(int outNode = 0 ; outNode < neuralNetwork[neuralNetwork.size()-1]->layerPerceptron.size() ; outNode++)
	{
		error = expected[outNode]- neuralNetwork[neuralNetwork.size()-1]->outPutProcessFeed[outNode];
		derived = neuralNetwork[neuralNetwork.size()-1]->function->Derived(neuralNetwork[neuralNetwork.size()-1]->outPutProcessFeed[outNode]);
		gradient = error * derived;
		neuralNetwork[neuralNetwork.size()-1]->layerPerceptron[outNode]->gradient = gradient;
		errorIteration.push_back(error);
	}
	generalError.push_back(errorIteration);
	//calcular la gradiente de las capas ocultas
	for(int layer = (neuralNetwork.size() - 2); layer > 0;layer--)
	{
		for(int perceptron = 0; perceptron < neuralNetwork[layer]->layerPerceptron.size(); perceptron++)
		{
			derived = neuralNetwork[layer]->function->Derived(neuralNetwork[layer]->outPutProcessFeed[perceptron]);
			for(int summatory = 0 ; summatory < neuralNetwork[layer + 1]->layerPerceptron.size() ;summatory++)
			{	
				sum += neuralNetwork[layer + 1]->layerPerceptron[summatory]->weights[perceptron] * neuralNetwork[layer + 1]->layerPerceptron[summatory]->gradient;
			}
			gradient = derived * sum;
			neuralNetwork[layer]->layerPerceptron[perceptron]->gradient = gradient;
			sum = 0;
		}
	}
}
void NeuralNetwork::UpdateWeightsAndBias()
{
	double delta = 0;
	for (int layer = neuralNetwork.size()-1; layer > 0; layer--)
	{
		for (int perceptron = 0; perceptron < neuralNetwork[layer]->layerPerceptron.size();perceptron++)
		{
			for (int weigth =  0; weigth < neuralNetwork[layer]->layerPerceptron[perceptron]->weights.size(); weigth++)
			{
				delta = learnRate * neuralNetwork[layer - 1]->outPutProcessFeed[weigth] * neuralNetwork[layer]->layerPerceptron[perceptron]->gradient;
				neuralNetwork[layer]->layerPerceptron[perceptron]->weights[weigth]+= delta;
			}
			delta = learnRate * neuralNetwork[layer]->layerPerceptron[perceptron]->gradient;
			neuralNetwork[layer]->layerPerceptron[perceptron]->bias+= delta;
		}
	}
}
double NeuralNetwork::MeanSquaredError(vector<vector<double>>& generalError)
{
	double error= 0;
	for(int i = 0; i < generalError.size();i++)
	{
		for (int j = 0; j < generalError[i].size(); ++j)
		{
			error +=(generalError[i][j]*generalError[i][j]);
		}
	}
	error = error/generalError.size();
	return error;
}
void NeuralNetwork::SetTransitionFunction(int layer, TypeOfTransition typeFunction)
{
	delete neuralNetwork[layer]->function;
	switch(typeFunction)
 	{
 		case TypeOfTransition::STEPBYSTEP:
			neuralNetwork[layer]->function = new TransitionByStep();
 		break;
 		case TypeOfTransition::SIGMOID:
 			neuralNetwork[layer]->function  = new TransitionSigmoid();
 		break;
 		case TypeOfTransition::TANGHIPERBOLIC:
 			neuralNetwork[layer]->function  = new TransitionHiperbolicTangent();
 		break;
 		case TypeOfTransition::SOFTMAX:
			neuralNetwork[layer]->function  = new TransitionSoftMax();
 		break;
 	}
}
int* NeuralNetwork::ShuffleIndex(int* result,size_t size)
{
	int random = 0;
	int temp = 0;
	for(size_t i = 0; i < size - 1; i++)
	{
		uniform_int_distribution<int> distribution(i,size-1);
		random = distribution(generator);
		temp = result[random];
 		result[random] = result[i];
 		result[i] = temp;
 	}
 	return result;
}
double NeuralNetwork::BackpropagationByBatches(vector<vector<double>>& inputs,vector<vector<double>>& expected,int * sequence)
{
	vector<double> gradient;
	vector<vector<double>> gradientsTotal{};
	vector<vector<double>> generalError{};
		
	for(int j = 0;j < inputs.size();j++)
	{
		FeedForward(inputs[sequence[j]]);
		ComputeGradient(expected[sequence[j]],generalError);
		if(j == 0)
		{
			for (int layer = neuralNetwork.size()-1; layer > 0; --layer)
			{
				for (int node = 0; node < neuralNetwork[layer]->layerPerceptron.size(); ++node)
				{
					gradient.push_back(neuralNetwork[layer]->layerPerceptron[node]->gradient);
				}
				gradientsTotal.push_back(gradient);//si el numero de ejemplos es 1
				gradient.clear();
			}
		}
		else
		{	
			SummaryGradients(gradientsTotal);
		}
		
	}
	double delta = 0;
	int indexGradient = 0;
	for (int layer = neuralNetwork.size()-1; layer > 0; layer--)
	{
		for (int perceptron = 0; perceptron < neuralNetwork[layer]->layerPerceptron.size();perceptron++)
		{
			for (int weigth =  0; weigth < neuralNetwork[layer]->layerPerceptron[perceptron]->weights.size(); weigth++)
			{
				delta = learnRate * neuralNetwork[layer - 1]->outPutProcessFeed[weigth] * gradientsTotal[indexGradient][perceptron];
				neuralNetwork[layer]->layerPerceptron[perceptron]->weights[weigth]+= delta;
			}
			delta = learnRate * neuralNetwork[layer]->layerPerceptron[perceptron]->gradient;
			neuralNetwork[layer]->layerPerceptron[perceptron]->bias+= delta;
		}
		indexGradient++;
	}
	gradientsTotal.clear();
	return MeanSquaredError(generalError);
}

void NeuralNetwork::SummaryGradients(vector<vector<double>>& gradientsTotal)
{
	int indexGradient = 0;
	for (int layer = neuralNetwork.size()-1;layer > 0; layer--)
	{
		for (int node = 0; node < neuralNetwork[layer]->layerPerceptron.size(); ++node)
		{
			gradientsTotal[indexGradient][node] += neuralNetwork[layer]->layerPerceptron[node]->gradient;
		}
		indexGradient++;
	}
}
void NeuralNetwork::TrainByBatches(const string& examples)
{
	vector<vector<double>> inputs {};
	vector<vector<double>> expectedValue {};
	Data* datos = new Data(examples, inputs, expectedValue);
	double errorN = 1;
	int * sequence = new int[inputs.size()];
	for (int i = 0; i < inputs.size(); ++i)
	{
		sequence[i] = i;
	}
	for (int i = 0; i < limitLoop; i++)
	{
		if(errorN < error)
		{
			cout <<"salio de error\n";
			break;
		}
		sequence = ShuffleIndex(sequence,inputs.size());
		errorN = BackpropagationByBatches(inputs,expectedValue,sequence);
	}
	delete datos;
}
void NeuralNetwork::ShowWeights()
{
	for (int i = 1; i < neuralNetwork.size(); ++i)
	{
		cout << "capa: "<<i<<"\n";
		for (int j = 0; j < neuralNetwork[i]->layerPerceptron.size(); ++j)
		{
			cout << " perceptron: "<<j<<" ";
			for (int p = 0; p < neuralNetwork[i]->layerPerceptron[j]->weights.size(); ++p)
			{
				cout <<neuralNetwork[i]->layerPerceptron[j]->weights[p]<<" ";
			}
			cout << " sesgo: "<<neuralNetwork[i]->layerPerceptron[j]->bias<<"\n";
		}
		cout<<"\n";
	}
}

void NeuralNetwork::TrainByMomemtum(const string& exmaples){

	vector<vector<vector<double>>> diffWeight;
	vector<vector<double>> diffBias;
	vector<vector<double>> diffWeightAux;
	vector<double> auxBias;
	vector<double> auxWeight;

	for(int layer = 0; layer < neuralNetwork.size();layer++)
	{
		for(int perceptron = 0; perceptron < neuralNetwork[layer]->layerPerceptron.size(); perceptron++)
		{
			auxWeight.push_back(0);
			//diffBias[layer].push_back(0);
			for(int weight = 0 ; weight < neuralNetwork[layer]->layerPerceptron[perceptron]->weights.size() ;weight++)
			{	
				auxBias.push_back(0);
				//diffWeight[layer][perceptron].push_back(0);
			}
			diffWeightAux.push_back(auxBias);
			auxBias.clear();
		}
		diffBias.push_back(auxWeight);
		diffWeight.push_back(diffWeightAux);
		diffWeightAux.clear();
		auxWeight.clear();
	}
	
	vector<vector<double>> inputs;
	vector<vector<double>> expectedValue;
	vector<vector<double>> calcError;
	Data* datos = new Data(exmaples, inputs, expectedValue);
	int * sequence = new int[inputs.size()];
	
	for (int i = 0; i < inputs.size(); ++i)
	{
		sequence[i] = i;
	}

	for(int train = 0;train<limitLoop;train++){
		for(int i=0;i<inputs.size();i++){
			FeedForward(inputs[sequence[i]]);
			ComputeGradient(expectedValue[sequence[i]],calcError);
			//UpdateWeightsBiasByMomentum(diffWeight,diffBias);
			UpdateWeightsAndBias();
		}
		double c=CalculateError(calcError)/inputs.size();
		if(!(c>error)){
			cout<<"termino "<<train<<"\n";
			train = limitLoop;
		}
		sequence = ShuffleIndex(sequence,inputs.size());
		calcError.clear();
	}
}	
void NeuralNetwork::UpdateWeightsBiasByMomentum(vector<vector<vector<double>>>& diffWeight,vector<vector<double>>& diffBias){
	for (int layer = neuralNetwork.size()-1; layer > 0; layer--) {

        for (int perceptron = 0; perceptron < neuralNetwork[layer]->layerPerceptron.size(); perceptron++) {
        	diffBias[layer][perceptron] = learnRate * 
        	neuralNetwork[layer]->layerPerceptron[perceptron]->gradient +
        	momentum * diffBias[layer][perceptron];
			
			neuralNetwork[layer]->layerPerceptron[perceptron]->bias += diffBias[layer][perceptron];

			for(int weight = 0;weight < neuralNetwork[layer]->layerPerceptron[perceptron]->weights.size();weight++){
				diffWeight[layer][perceptron][weight] = learnRate * neuralNetwork[layer]->layerPerceptron[perceptron]->gradient *
				neuralNetwork[layer-1]->outPutProcessFeed[weight] + momentum * diffWeight[layer][perceptron][weight];
				neuralNetwork[layer]->layerPerceptron[perceptron]->weights[weight] += diffWeight[layer][perceptron][weight];
			}
	    }
	}
}
double NeuralNetwork::CalculateError(vector<vector<double>>& errorValue){
	double allError = 0;
        
    for(auto& err:errorValue){
    	for(auto& errValue:err){
    		allError += 0.5*pow(errValue,2);
    	}
    }
    return allError;
}

