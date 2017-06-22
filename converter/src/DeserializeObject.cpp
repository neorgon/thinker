#include "../include/DeserializeObject.h"

json DeserializeObject::DeserializePerceptron(string path)
{
    json objectCurrent;
    ifstream converterPath(path);
    converterPath >> objectCurrent;

    return objectCurrent;
}
