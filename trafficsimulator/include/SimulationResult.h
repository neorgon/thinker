#ifndef SIMULATIONRESULT_H
#define SIMULATIONRESULT_H

#include <map>
#include <vector>

using namespace std;

class SimulationResult
{
    map<int,vector<int>> resultTrafficLight;
    map<int,int> resutlVehicle;

    public:
    SimulationResult();
    ~SimulationResult();

};

#endif // SIMULATIONRESULT_H
