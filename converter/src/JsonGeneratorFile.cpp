#include "../include/JsonGeneratorFile.h"

void JsonGeneratorFile::Serialize(vector<vector<double>> weights,vector<double> bias,vector<vector<double>> inputs)
{
	json convertido = serObject.SerializePerceptron(weights, bias, inputs);
	ofstream myfile;
	try
	{
		myfile.open ("perceptron.json");
		myfile << convertido;
		myfile.close();
	}
	catch(ofstream::failure &readErr) {
    cerr << "Exception occured when writing a file\n"
              << readErr.what()
              << endl;
	}

}

string JsonGeneratorFile::Deserialize(string pathName)
{
	string resultDeserialize = "Error in parameter pathName";
	if(!pathName.empty())
	{
			resultDeserialize  = desObject.DeserializePerceptron(pathName).dump();
	}

	return resultDeserialize;
}
