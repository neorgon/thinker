#ifndef DATA_H
#define DATA_H
#include <vector>
#include <string>
#include "../../thirdParty/jsonlib/json.hpp"
#include <iostream>
#include <fstream>
using namespace std;
using json = nlohmann::json;

class Data
{
    public:
        Data(string path, vector<vector<double>>& inputs,
           vector<vector<double>>& values);
        void NormalizationMinMax(vector<vector<double>>& inputs);
        void NormalizationMinMax(vector<vector<double>>& inputs,
           vector<vector<double>>& values);
        void NormalizationGauss(vector<vector<double>>& inputs);
        void NormalizationGauss(vector<vector<double>>& inputs,
          vector<vector<double>>& values);
        void CodificationDummy();
        void CodificationEfects();
        virtual ~Data();

    protected:

    private:
    void GetMaximumAndMinimum(vector<vector<double>>& inputs, int& column);
    void GetMeanGauss(vector<vector<double>>& values, int& column);
};

#endif // DATA_H
