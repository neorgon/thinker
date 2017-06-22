#include "../include/Simulation.h"

Simulation::Simulation(shared_ptr< Map> mapTrafficLight,string name,vector<shared_ptr<Vehicle>> Vehicles):map{mapTrafficLight},
name{name},vehicles{Vehicles}
{
	/*map=mapTrafficLight;
	name=name;
	vehicles=Vehicles;*/
}
vector<shared_ptr<Vehicle>> Simulation::getVehicles()
{
	return vehicles;
}
shared_ptr<Map> Simulation::getMap()
{
	return map;
}
string Simulation::getName()
{
	return name;
}

