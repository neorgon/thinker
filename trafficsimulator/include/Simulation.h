#ifndef SIMULATION_H
#define SIMULATION_H

#include "Vehicle.h"
#include "Map.h"
#include <vector>
#include <memory>

using namespace std;

class Simulation
{
	string name;
	shared_ptr<Map> map;
   	vector<shared_ptr<Vehicle>> vehicles;

    public:
        Simulation(shared_ptr<Map>mapTrafficLight,string name,vector<shared_ptr<Vehicle>> vehicles);
        vector<shared_ptr<Vehicle>> getVehicles();
        shared_ptr<Map> getMap();
        string getName();
        //void BuildVehicle(int amountVehicles, int speedMin,int speedMax);
};

#endif // SIMULATION_H
