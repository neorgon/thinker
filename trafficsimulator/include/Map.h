#ifndef MAP_H
#define MAP_H

#include <iostream>
#include <vector>
#include <memory>
#include <deque>
#include <stack>
#include <map>
#include <algorithm>

#include "../include/Direction.h"

using namespace std;

class TrafficLight;
class Map
{
    int sizeMap;
    map<int, vector<int>> mapRoutes;
    map<int, vector<shared_ptr<TrafficLight>>> mapTrafficLight;

    public:
        Map(int sizeMap, size_t timeTrafficLight, size_t maxVehicle);
        vector<shared_ptr<TrafficLight>> CreateRoute(const shared_ptr<TrafficLight> &origin, const shared_ptr<TrafficLight> &destination);
        void StoreRoute(const size_t &ini , const size_t &fin , Direction orientation, vector<shared_ptr<TrafficLight>> &route);
        vector<size_t> ConvertCoordinates(const int &x) ; 
        map<int, vector<shared_ptr<TrafficLight>>> GetMapTrafficLight() const;
        int getSizeMap() const;
        void show();
        void showMap();
};

#endif // MAP_H
