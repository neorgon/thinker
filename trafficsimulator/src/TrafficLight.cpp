#include "../include/TrafficLight.h"

size_t TrafficLight::GetDirection() const
{
    return direction;
}

bool TrafficLight::GetLight() const
{
    return green;
}

MapCoord TrafficLight::GetCoord() const
{
    return coord;
}

void TrafficLight::SetCoord(int x, int y)
{
    coord.x = x;
    coord.y = y;
}

size_t TrafficLight::CountVehicles() const
{
    size_t p = 0;
    size_t v = 0;

    while (p < maxVQueue)
    {
        if (vehicles[p] != nullptr)
            v++;
        p++;
    }

    return v;
}

size_t TrafficLight::GetMaxVQueue()const
{
    return maxVQueue;
}

void TrafficLight::SwitchLight()
{
    green = !green;
}

bool TrafficLight::EnQueue(const shared_ptr<Vehicle>& v)
{
    size_t i = 0;
    //cout<<vehicles.size()<<endl;
    while (i < maxVQueue)
    {
    	if( vehicles[i].get() == nullptr)
    	{
        	vehicles[i] = v;
        	//cout<<"encolando vehiculo: "<<i<<endl;
       		return true;
    	}
    	/*else
    	{
    		cout<<"puntero lleno"<<endl;
    	}*/

   		i++;
    }

    return false;
}

bool TrafficLight::EnQueue(const shared_ptr<Vehicle>& v,size_t id)
{
	//cout<<"otro encolado"<<endl;
	//cout<<id<<endl;
    size_t i=vehicles.size()-(id+1);
    //cout<<i<<endl;
    //cout<<vehicles.size()<<endl;
    while (i < vehicles.size())
    {// cout<<"ciclo"<<endl;
    	if( vehicles[i] == nullptr)
    	{
        	vehicles[i] = v;
       		return true;
    	}
   		i++;
    }

    return false;
}

void TrafficLight::Clean(size_t at)
{
	vehicles.at(at-1)=nullptr;
}

shared_ptr<Vehicle> TrafficLight::FirstVehicle() const
{
    return vehicles.front();
}

bool TrafficLight::DeQueue()
{
    /*
    Tal vez este m?odo tendr? que devolver una lista de todos los veh?ulos que pueden pasar luz verde.
    */

    return true;
}

void TrafficLight::Update()
{
    if (timer > 0)
    {
        timer --;
    }
    else
    {
        SwitchLight();
        timer = countdown;
    }
/*
    if (green)
    {
        DeQueue(); //?
    }*/
}

size_t TrafficLight::GetVehiculoLocation(const shared_ptr<Vehicle>& v) const
{
	int i=0;
	auto thisVehicle = find_if(vehicles.begin(), vehicles.end(),
				 		[&v,&i](const shared_ptr<Vehicle>& it)
         				{
         					i++;
         					if(it!=nullptr)
         					return v->GetLicencePlate()==it->GetLicencePlate();

				        });

	if (thisVehicle==vehicles.end())
		return 0;
	//else
	//	cout<<" licencia: "<<(*thisVehicle)->GetLicencePlate()<<endl;
	//cout<<" lista de autos"<<endl;
	/*for(auto i:vehicles)
	{
        if(i!=nullptr)
		cout<<" auto: "<<i->GetLicencePlate()<<endl;

	}*/

	return i;

    }
    size_t TrafficLight::GetNode()const
    {
        return node;
    }
