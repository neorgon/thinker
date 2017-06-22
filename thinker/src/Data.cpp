#include "../include/Data.h"
#include <vector>
#include <string>

Data::Data(string path, vector<vector<double>>& inputs, vector<vector<double>>& values)
{
  string namePath = path;
  json objectJsonCurrent;
  ifstream i(namePath);
  if(!i)
  {
    cerr<<"exception ocurred reading file \n";
  }
  else {
    i >> objectJsonCurrent;
    json inputCurrent = objectJsonCurrent["inputs"];
    json valuesCurrent = objectJsonCurrent["value"];
    vector<vector<double>> inputsConverter = inputCurrent;
    vector<vector<double>> valuesConverter = valuesCurrent;
    inputs =  inputsConverter;
    values =  valuesConverter;
  }
}

void Data::GetMaximumAndMinimum(vector<vector<double>>& inputs, int& column)
{
   double min = inputs[0][column];
    double max = inputs[0][column];

    for(int i = 0; i<inputs.size(); ++i)
    {
      if(inputs[i][column] < min)
           min = inputs[i][column];
      if (inputs[i][column] > max)
           max = inputs[i][column];
     }
     double range = max - min;

     for(int i = 0; i<inputs.size(); ++i)
     {
       inputs[i][column] = (inputs[i][column] - min) / range;
     }
}

void Data::NormalizationMinMax(vector<vector<double>>& inputs)
{
   for(int j = 0; j<inputs[0][0];j++)
   {
     GetMaximumAndMinimum(inputs, j);
   }
}
void Data::NormalizationMinMax(vector<vector<double>>& inputs,
   vector<vector<double>>& values)
{
   for(int j = 0; j<inputs[0][0];j++)
   {
     GetMaximumAndMinimum(inputs, j);
   }
   for(int j = 0; j<values[0][0];j++)
   {
     GetMaximumAndMinimum(values, j);
   }
}

void Data::GetMeanGauss(vector<vector<double>>& values, int& column)
{
    double sum = 0.0;
    for (int i = 0; i < values.size(); ++i)
       sum += values[i][column];

    double mean = sum / values.size();
    double sumSquares = 0.0;
    for (int i = 0; i < values.size(); ++i)
     sumSquares += (values[i][column] - mean) * (values[i][column] - mean);
    double stdDev = sqrt(sumSquares / values.size());
    for (int i = 0; i < values.size(); ++i)
    {
       values[i][column] = (values[i][column] - mean) / stdDev;
    }
}

void Data::NormalizationGauss(vector<vector<double>>& inputs)
{
   for(int j = 0; j<inputs[0][0];j++)
   {
     GetMeanGauss(inputs, j);
   }
}

void Data::NormalizationGauss(vector<vector<double>>& inputs,
   vector<vector<double>>& values)
{
   for(int j = 0; j<inputs[0][0];j++)
   {
     GetMeanGauss(inputs, j);
   }
   for(int j = 0; j<values[0][0];j++)
   {
     GetMeanGauss(values, j);
   }
}

void Data::CodificationDummy()
{

}
void Data::CodificationEfects()
{

}

Data::~Data()
{
    //dtor
}
