#ifndef TRAFFICSIMULATOR_H
#define TRAFFICSIMULATOR_H

#include <vector>
#include <memory>
#include <string>
#include <utility>
#include <iostream>
#include <math.h>
#include <exception>
#include <conio.h>
#include <iomanip>
#include <windows.h>
#include <map>
#include <typeinfo>
#include <stdlib.h>
#include <time.h>
#include <functional>

#include "WindowsConsole.h"
#include "Simulation.h"
#include "Map.h"
#include "Vehicle.h"
#include "TrafficLight.h"

#define WINDOWS 1

using namespace std;
class Map;
class TrafficLight;
class TrafficSimulator
{


	map<string,shared_ptr<Simulation>> simulations;


	public:
	TrafficSimulator();
	~TrafficSimulator();
	int RandomInteger(int lowest, int highest);
	void BuildSimulation(shared_ptr<Map>& map,string name,size_t vehicleQuantity,
	size_t speedMin,size_t speedMax);
    void StartLoopSim(map<string,shared_ptr<Simulation>>::iterator simulationIterator, int cycles = 0);
    void StartSimulation(string simulationName, int cycles = 0);
    vector<string> Data;
    vector<size_t> GetStartEndPoints(shared_ptr<Map>& mapSimulation,size_t vehicleQuantity,size_t id);

};

#endif // TRAFFICSIMULATOR_H

