#include "include/TrafficSimulator.h"
#include "include/WindowsConsole.h"

using namespace std;

int main()
{
	Map mapa = Map(4, 2, 10);

	WindowsConsole wc(600, 800, "Traffic Simulator", 7, 4);
	//wc.PrintCity();
	//wc.ClearScreen();
	auto TLs = mapa.GetMapTrafficLight();
	wc.PrintMap(TLs, mapa.getSizeMap());

    getchar();
    //cout << TLs[6].first << "\n";

    return 0;
}
