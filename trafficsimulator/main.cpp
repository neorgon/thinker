
#include "include/TrafficSimulator.h"
//#include "TrafficSimulator.h"
#include <iostream>
#include <memory>
#include <utility>


#include "include/Vehicle.h"
#include "include/Map.h"
#include "include/TrafficSimulator.h"
#include "include/TrafficLight.h"

using namespace std;

using namespace std;
int main()
{

	/*Map* m = new Map(4,10,20);
	//m.InitializeTrafficLight(10,20);
	auto route=m->createRoute(1,10);
	m->showMap();
	m->show();*/


	/*Map* m = new Map(4,10,20);

	auto mapa = m->GetMapTrafficLight();

	auto aux = mapa.find(10);
	auto ini = aux->second[0]; 
	
	auto aux2 = mapa.find(22);
	auto fin = aux2->second[1];

	auto route=m->CreateRoute(ini,fin);



	m->showMap();
	m->show();
*/

	

	size_t vehicleQuantity=100;
	size_t speedMin=1;
	size_t speedMax=2;
	size_t timeTrafficLight=2;
	size_t Vehicles=10;
	TrafficSimulator* a = new TrafficSimulator();
	shared_ptr<Map> mapa=make_shared<Map>(10,timeTrafficLight,Vehicles);
	//mapa->show();
	a->BuildSimulation(mapa,"primeraSImulacion", vehicleQuantity, speedMin, speedMax);
	//mapa->show();
	//a->StartSimulation("hola",4);
	//mapa->show();
    //cout<<s->getName()<<"NOMBRE SI\n";


    //a->StartSimulation("primeraSImulacion",20);

    //a->StartSimulation(s.get(),20);


    //TrafficSimulator* b = new TrafficSimulator();
	//shared_ptr<Map> mapa2=make_shared<Map>(4,timeTrafficLight,Vehicles);
	//mapa->show();
	//Simulation* s2=b->BuildSimulation(mapa2,"segunda", vehicleQuantity, speedMin, speedMax);
	//mapa->show();
	//a->StartSimulation("hola",4);
	//mapa->show();
    //cout<<s->getName()<<"NOMBRE SI\n";

    //a->StartSimulation(s2,20);




}
