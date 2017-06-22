
#include <iostream>
using namespace std;
//#include "../include/ShowFood.h"
//#include "../include/Food.h"
#include <iostream>
/*#include "Perceptron.h"
#include "NeuralNetwork.h"
#include "Data.h"*/

#include "../thinker/include/Perceptron.h"

int main()
{
	Perceptron p = Perceptron(2,0.3);
    vector<double> data={0.9,0.2};
    vector<double> data1={4.1,0.5};
    vector<double> data2={1.2,2.3};
    vector<double> data3={0.8,1.2};
    vector<double> data4={0.7,5.6};
    
    vector<vector<double>> datas;
    datas.push_back(data);
    datas.push_back(data1);
    datas.push_back(data2);
    datas.push_back(data3);
    datas.push_back(data4);

    vector<double> expected = {-1,-1,1,1,1};
    
    p.Train(datas,expected);
    cout << p.ComputeOutput(data)<<"\n";
    return 0;
}
