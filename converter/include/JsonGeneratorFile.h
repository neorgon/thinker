#ifndef JSONGENERATORFILE_H
#define JSONGENERATORFILE_H
#include <fstream>
#include <vector>
#include <string>
#include "SerializeObject.h"
#include "DeserializeObject.h"
#include "json.hpp"

using json = nlohmann::json;
using namespace std;

class JsonGeneratorFile
{
	SerializeObject serObject;
	DeserializeObject desObject;

	public:
	void Serialize(vector<vector<double>> weights,vector<double> bias,vector<vector<double>> inputs);
	string Deserialize(string p);
};
#endif
