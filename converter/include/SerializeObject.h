#ifndef SERIALIZEOBJECT_H
#define SERIALIZEOBJECT_H

#include <iostream>
#include <vector>
#include <string>
#include "json.hpp"
#define MACRO_VARIABLE_TO_STRING(Variable) (void(Variable),#Variable)

using json = nlohmann::json;
using namespace std;

class SerializeObject
{
public:
  json SerializePerceptron(vector<vector<double>>& weights,vector<double>& bias,vector<vector<double>>& inputs);
private:
  template<class T>
	json CreateJson(T& v);
};

#endif
