#include <iostream>
#include "../thirdParty/json/src/json.hpp"
#include <iostream>
#include <fstream>
#include <string>
#include "include/JsonGeneratorFile.h"

using namespace std;
using json = nlohmann::json;

int main()
{
    vector<double> peso1={0.3,0.1};
    vector<double> peso2={3.1,1.1};
    vector<double> peso3={1.5,1.6};
    vector<double> peso4={1.1,1.3};
    vector<vector<double>> pesos;
    pesos.push_back(peso1);
    pesos.push_back(peso2);
    pesos.push_back(peso3);
    pesos.push_back(peso4);

    vector<double> bias = {1.0,1.1,1.2,1.3};
    vector<double> data={-1,-1};
    vector<double> data1={-1,1};
    vector<double> data2={1,-1};
    vector<double> data3={1,1};
    vector<vector<double>> datas;
    datas.push_back(data);
    datas.push_back(data1);
    datas.push_back(data2);
    datas.push_back(data3);

    JsonGeneratorFile conv;

    conv.Serialize(pesos, bias, datas);
    auto objDes = conv.Deserialize("perceptron.json");
    cout<<objDes<<"\n";

    return 0;
}
;
