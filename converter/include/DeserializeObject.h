#ifndef DESERIALIZEOBJECT_H
#define DESERIALIZEOBJECT_H

#include <iostream>
#include <string>
#include <fstream>
#include "json.hpp"

using json = nlohmann::json;
using namespace std;

class DeserializeObject
{
public:
    json DeserializePerceptron(string path);
};
#endif
