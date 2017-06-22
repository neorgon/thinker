#include "../include/Vehicle.h"
//#include "../include/Map.h"
#include "../include/TrafficLight.h"

Vehicle::Vehicle(size_t licencePlate, double speed, vector <shared_ptr<TrafficLight>> route/*const shared_ptr<TrafficLight>& origin,
			const shared_ptr<TrafficLight>& destiny, const shared_ptr<Map>& map/*,
			size_t startTime*/)
:licencePlate{licencePlate},speed{speed},route{route} /*startTime{startTime},*/
{
	if (route[0]==nullptr)
		throw ("error");
	//if (destiny==nullptr)
	//	throw ("error");
		//cerr<<"error";
	//location=origin;
	location=route[0];
	if (!location->EnQueue(make_shared<Vehicle>(*this)))
		cout<<"error no push"<<endl;
	//cout<<"AN: "<<location->GetVehiculoLocation(make_shared<Vehicle>(*this))<<endl;
	//cout<<" Auto indice n: "<<location->GetVehiculoLocation(make_shared<Vehicle>(*this))<<endl;
	//pedir cambio de vector;
	//vector<shared_ptr<TrafficLight> ruta = map->CreateRoute(origin,destiny);
	//hardcore
	//auto mymapa=map->get_mapTLight();
	//try{route = map->CreateRoute(origin,destiny);}
	//catch(...){cerr<<"error"<<endl;}
}

void Vehicle::Move(function<void(shared_ptr<Vehicle>)> func)
{
	if(state)
	{
		double bufferspeed = speed;
		arrivalTime++;
		
		//verificar luz verde con velocidad mayor

		auto at= location->GetVehiculoLocation(make_shared<Vehicle>(*this));
		if (at<=speed)
		{
			if (location->GetLight())
			{
				indice++;
				if (route.at(indice)->EnQueue(make_shared<Vehicle>(*this),(speed-at))==1)
					{
					 location->Clean(at);
					 location=route.at(indice);
					 speed-=at;
						cout<<"ubicacion nueva: "<< location->GetVehiculoLocation(make_shared<Vehicle>(*this))<<endl;
					}
				else
					{
						indice--;
						speed=at-1;
						if(location->EnQueue(make_shared<Vehicle>(*this), location->GetMaxVQueue()-at+speed))
					 		location->Clean(at);
					}
			}
			else
			{
				speed=at-1;
				if(location->EnQueue(make_shared<Vehicle>(*this), location->GetMaxVQueue()-at+speed))
			 		location->Clean(at);
			 
			}

		}

		if(at>speed)
		{
		 	if(location->EnQueue(make_shared<Vehicle>(*this), location->GetMaxVQueue()-at+speed))
		 		location->Clean(at);
		 
			//cout< location->GetVehiculoLocation(make_shared<Vehicle>(*this))<<endl;
		}

		//	if location->FirstVehicle().get()->GetLicencePlate()==this->GetLicencePlate()
		//		&& location->GetLight()) 
		//		if (route.at(indice++)->EnQueue(make_shared<Vehicle>(*this)),5)
		//		{
		//		 location=route.at(indice++);
		//		}
		//if location==route.back().first);
			//boos->RegisterVehicle(this);
			//cout<<"auno numero: "< location->GetVehiculoLocation(make_shared<Vehicle>(*this))<<endl;
		cout<<endl;
		//cout<<"nodo inicio id semaforo :"<<location->GetNode()
		//<<" auto n: "<< location->CountVehicles()<<endl;
		for (auto& i: route)
		{
			cout<<"nodo: "<<i->GetNode() 
			<<" auto n: "<<i->CountVehicles()<<endl;
		}
		speed=bufferspeed;
		if  (location==route.back())
		{
			state=false;
		}
	}
	else
	{
		func(make_shared<Vehicle>(*this));
		// location->Clean(at)
	}
}

size_t Vehicle::GetLicencePlate() const
{
	return licencePlate;
}

shared_ptr<TrafficLight> Vehicle::GetLocation() const
{
	return location;
}

size_t Vehicle::GetArrivalTime()const
{
	return arrivalTime;
}
double Vehicle::getspeed()
{return speed;}
/*
Vehicle::~Vehicle()
{

}
*/
