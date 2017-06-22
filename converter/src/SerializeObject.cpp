#include "../include/SerializeObject.h"

template<class T>
json SerializeObject::CreateJson(T& v)
{
	json j_vector(v);
	return j_vector;
}

json SerializeObject::SerializePerceptron(vector<vector<double>>& weights,vector<double>& bias,vector<vector<double>>& inputs)
{
	json perceptron = {{"Perceptron",
                        {{MACRO_VARIABLE_TO_STRING(weights), CreateJson<vector<vector<double>>>(weights)},
                        {MACRO_VARIABLE_TO_STRING(bias), CreateJson<vector<double>>(bias)},
                        {MACRO_VARIABLE_TO_STRING(inputs), CreateJson<vector<vector<double>>>(inputs)}}
					 }};
	return perceptron;
}
