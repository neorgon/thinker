#include "../include/TrafficLight.h"
#include "../include/Map.h"
#include <math.h>

Map::Map(int sizeBlock, size_t timeTrafficLight, size_t maxVehicle) : sizeMap{sizeBlock + 1}
{
	int id=0;
	size_t dir1, dir2;
    vector<int> adyacents;
    vector<shared_ptr<TrafficLight>> VectorTrafictlight;


	for (int i = 1; i <= sizeMap; ++i)
	{
		for (int j = 1; j <= sizeMap; ++j)
		{
			id++;
			adyacents = {0, 0};

		 	if ((i % 2 != 0) && (j % 2 != 0))
			{
				if (id - (sizeMap * i) != 0)
				{
					adyacents[0] = id + 1;
				}
				if (id-sizeMap>=1)
				{
					adyacents[1] = id - sizeMap;
				}
				dir1 = static_cast<int>(Direction::goRight);
				dir2 = static_cast<int>(Direction::goUp);
			}

			if ((i % 2 != 0) && (j % 2 == 0))
			{
				if (id - (sizeMap * i) !=0 )
				{
					adyacents[0] = id + 1;
				}
				if (id + sizeMap <= sizeMap * sizeMap)
				{
					adyacents[1] = id + sizeMap;
				}
				dir1 = static_cast<int>(Direction::goRight);
				dir2 = static_cast<int>(Direction::goDown);
			}

			if ((i % 2 == 0) && (j % 2 != 0))
			{
				if (id - (sizeMap * (i - 1) + 1) != 0)
				{
					adyacents[0] = id - 1;
				}
				if (id - sizeMap >= 1)
				{
					adyacents[1] = id - sizeMap;
				}
				dir1 = static_cast<int>(Direction::goLeft);
				dir2 = static_cast<int>(Direction::goUp);
			}

			if ((i % 2 == 0) && (j % 2 == 0))
			{
				if (id - (sizeMap * (i - 1) + 1) !=0 )
				{
					adyacents[0] = id - 1;
				}
				if (id + sizeMap <= sizeMap * sizeMap)
				{
					adyacents[1] = id + sizeMap;
				}
                dir1 = static_cast<int>(Direction::goLeft);
                dir2 = static_cast<int>(Direction::goDown);
			}

			VectorTrafictlight.push_back
			(
                make_shared<TrafficLight>(dir1, timeTrafficLight, maxVehicle,id,  true)
            );
            VectorTrafictlight.push_back
            (
                make_shared<TrafficLight>(dir2, timeTrafficLight, maxVehicle, id, false)
            );

			mapRoutes.insert(pair<int, vector<int>> (id, adyacents));
			mapTrafficLight.insert(pair<int, vector<shared_ptr<TrafficLight>>> (id, VectorTrafictlight));
			VectorTrafictlight.clear();
		}
	}
}

void Map::showMap()
{
	//map<int,vector<int>>::iterator it = mapTrafficLight.begin();
		cout<<"\n ID  AdH  AdV\n-------------------\n";
	for (auto it = mapRoutes.begin(); it != mapRoutes.end(); ++it)
    	cout <<"  "<< it->first << " : " << it->second[0] << " : "<< it->second[1] << '\n';
}


void Map::show()
{

	cout<<"\nNODO  TL  TL\n-------------------\n";
	for(auto it = mapTrafficLight.begin(); it != mapTrafficLight.end(); ++it)
	{
		cout
            << "  " << it->first << "  " << it->second[0]->GetNode() << "  "
            << it->second[0]->GetDirection() << "  " << it->second[1]->GetNode() << " " << it->second[1]->GetDirection() <<"\n";
	}
}

vector<shared_ptr<TrafficLight>> Map::CreateRoute(const shared_ptr<TrafficLight> &origin, const shared_ptr<TrafficLight> &destination)     
{
	vector<shared_ptr<TrafficLight>> route;
	auto XYorigin = ConvertCoordinates(origin->GetNode());
	auto XYdestination = ConvertCoordinates(destination->GetNode());

	cout<<origin->GetNode()<<"  "<<destination->GetNode()<<" \n";

	int nodoAux;

	int bandera;

/////////////////////////////Si el Nodo destino se encuentra a la derecha y abajo///////////////////////////////////

	if(XYorigin[1]<=XYdestination[1] && XYorigin[0]<=XYdestination[0])// destino esta --> y abajo
	{
		//cout<<"AQUI\n";
		if(XYorigin[0]%2!=0) //orientacion --->
		{
	
			if(XYdestination[1]%2==0  ) // destino puedo ir abajo 
			{  			
					route.push_back(origin);	
					StoreRoute(XYorigin[1],XYdestination[1],Direction::goRight,route);
					StoreRoute(XYorigin[0],XYdestination[0],Direction::goDown,route);	
			}
			else
			{

			  if(XYorigin[0]%2==0  || XYorigin[1]!=XYdestination[1] )
			  {
				if(XYdestination[0]%2!=0 ) // destino puede ir --->
				{
				
					route.push_back(origin);
					StoreRoute(XYorigin[1],XYdestination[1]-1,Direction::goRight,route);
					StoreRoute(XYorigin[0],XYdestination[0],Direction::goDown,route);
					auto aux = route.at(route.size()-1);
					nodoAux = aux->GetNode()+1;
					auto TL = mapTrafficLight.find(nodoAux);
					route.push_back( TL->second[0] );
				}
				else
				{

					if(XYdestination[0]<sizeMap) // dar giro por abajo
					{

						route.push_back(origin);
						StoreRoute(XYorigin[1],XYdestination[1]-1,Direction::goRight,route);
						StoreRoute(XYorigin[0],XYdestination[0]+1,Direction::goDown,route);
						auto aux = route.at(route.size()-1);
						
						nodoAux = aux->GetNode()+1;
						auto TL = mapTrafficLight.find(nodoAux);
						route.push_back( TL->second[0] );

						nodoAux += -sizeMap;
						TL = mapTrafficLight.find(nodoAux);
						route.push_back(TL->second[1]);
					}
					else
					{
						if(XYdestination[1]<sizeMap) //giro por -->
						{

							route.push_back(origin);
							StoreRoute(XYorigin[1],XYdestination[1]-1,Direction::goRight,route);
							StoreRoute(XYorigin[0],XYdestination[0]-1,Direction::goDown,route);
							auto aux = route.at(route.size()-1);

							nodoAux = aux->GetNode()+1;
							auto TL = mapTrafficLight.find(nodoAux);
							route.push_back( TL->second[0] );

							nodoAux += 1;
							TL = mapTrafficLight.find(nodoAux);
							route.push_back( TL->second[0]);

							nodoAux += sizeMap;
							TL = mapTrafficLight.find(nodoAux);
							route.push_back( TL->second[1]);
							
							nodoAux += -1;
							TL = mapTrafficLight.find(nodoAux);
							route.push_back( TL->second[0]);
						}
						else
						{
							cout<<"No se puede llegar";
						}
					}
				}
			  }
			}
		}
		
		else
		{

			if(XYorigin[1]%2==0) // orientacion abajo
			{

			  if(XYorigin[1]!=XYdestination[1])
			  {
				if(XYdestination[0]%2!=0) // destino puedo ir --> 
				{  

					route.push_back(origin);
					StoreRoute(XYorigin[0],XYdestination[0],Direction::goDown,route);
					StoreRoute(XYorigin[1],XYdestination[1],Direction::goRight,route);
				}
				else
				{
					if(XYdestination[1]%2==0) //destono puedo baja
					{

						route.push_back(origin);
						StoreRoute(XYorigin[0],XYdestination[0]-1,Direction::goDown,route);
						StoreRoute(XYorigin[1],XYdestination[1],Direction::goRight,route);

						auto aux = route.at(route.size()-1);

						nodoAux = aux->GetNode()+sizeMap;
						auto TL = mapTrafficLight.find(nodoAux);
						route.push_back( TL->second[1] );
	
					}
					else
					{
						if(XYdestination[0]<sizeMap)  // girar por abajo
						{

							route.push_back(origin);
							StoreRoute(XYorigin[0],XYdestination[0]+1,Direction::goDown,route);
							StoreRoute(XYorigin[1],XYdestination[1],Direction::goRight,route);
							
							auto aux = route.at(route.size()-1);

							nodoAux = aux->GetNode()-sizeMap;
							auto TL = mapTrafficLight.find(nodoAux);
							route.push_back( TL->second[1] );
							
						}
						else
						{
							if(XYdestination[1]<sizeMap) // girar por --->
							{
								route.push_back(origin);
								StoreRoute(XYorigin[0],XYdestination[0]-1,Direction::goDown,route);
								StoreRoute(XYorigin[1],XYdestination[1]+1,Direction::goRight,route);

								auto aux = route.at(route.size()-1);

								nodoAux = aux->GetNode()+sizeMap;
								auto TL = mapTrafficLight.find(nodoAux);
								route.push_back( TL->second[1] );

								nodoAux += -1;
								TL = mapTrafficLight.find(nodoAux);
								route.push_back( TL->second[0] );
							}
							else
							{
								cout<<"No se puede llegar 1";
							}
						}

					}
				}
			  }
			}
			else
			{
				if(XYorigin[1]-1>0) // recorrer -1 <-- y bajar
				{

					if(XYdestination[0]%2!=0) //destino puede ir --> 
					{  
						route.push_back(origin);
						
						auto aux = route.at(route.size()-1);

						nodoAux = aux->GetNode()-1;
						auto TL = mapTrafficLight.find(nodoAux);
						route.push_back( TL->second[0]);

						StoreRoute(XYorigin[0],XYdestination[0],Direction::goDown,route);
						StoreRoute(XYorigin[1],XYdestination[1]+1,Direction::goRight,route);
					}
					else
					{
						if(XYdestination[1]%2==0) // destino puede baja
						{
							route.push_back(origin);
							auto aux = route.at(route.size()-1);

							nodoAux = aux->GetNode()-1;
							auto TL = mapTrafficLight.find(nodoAux);
							route.push_back( TL->second[0]);

							StoreRoute(XYorigin[0],XYdestination[0]-1,Direction::goDown,route);
							StoreRoute(XYorigin[1],XYdestination[1]+1,Direction::goRight,route);	

							aux = route.at(route.size()-1);
						
							nodoAux = aux->GetNode()+sizeMap;
							TL = mapTrafficLight.find(nodoAux);
							route.push_back( TL->second[1]);	
						}

						else
						{
							if(XYdestination[1]<sizeMap) // girar por abajo
							{

								route.push_back(origin);
								auto aux = route.at(route.size()-1);

								nodoAux = aux->GetNode()-1;
								auto TL = mapTrafficLight.find(nodoAux);
								route.push_back( TL->second[0]);

								StoreRoute(XYorigin[0],XYdestination[0]+1,Direction::goDown,route);
								StoreRoute(XYorigin[1],XYdestination[1]+1,Direction::goRight,route);

								aux = route.at(route.size()-1);
								nodoAux = aux->GetNode()-sizeMap;	
								TL = mapTrafficLight.find(nodoAux);
								route.push_back( TL->second[1]);
									
							}
							else
							{
								if(XYdestination[1]<sizeMap)// girar por ---->
								{
									route.push_back(origin);
									auto aux = route.at(route.size()-1);

									nodoAux = aux->GetNode()-1;
									auto TL = mapTrafficLight.find(nodoAux);
									route.push_back( TL->second[0]);

									StoreRoute(XYorigin[0],XYdestination[0]-1,Direction::goDown,route);
									StoreRoute(XYorigin[1],XYdestination[1]+2,Direction::goRight,route);
									aux = route.at(route.size()-1);
						
									nodoAux = aux->GetNode()+sizeMap;
									
									TL = mapTrafficLight.find(nodoAux);
									route.push_back( TL->second[1]);
									
									nodoAux += -1;
									TL = mapTrafficLight.find(nodoAux);
									route.push_back( TL->second[0]);
								}
								else
								{
									cout<<"No se puede llegar 2";
								}
							}

						}
					}

				}
				else
				{
					if(XYdestination[1]%2==0) // subir por 1 arriba y -----> 
					{
						route.push_back(origin);
						auto aux = route.at(route.size()-1);

						nodoAux = aux->GetNode()-sizeMap;
						auto TL = mapTrafficLight.find(nodoAux);
						route.push_back( TL->second[1]);

						StoreRoute(XYorigin[1],XYdestination[1],Direction::goRight,route);
						StoreRoute(XYorigin[0],XYdestination[0]+1,Direction::goDown,route);
					}
					else
					{
						if(XYdestination[0]%2!=0) //destino puede bajar y -->
						{
							route.push_back(origin);
							auto aux = route.at(route.size()-1);

							nodoAux = aux->GetNode()-sizeMap;
							auto TL = mapTrafficLight.find(nodoAux);
							route.push_back( TL->second[1]);

							StoreRoute(XYorigin[1],XYdestination[1]-1,Direction::goRight,route);
							StoreRoute(XYorigin[0],XYdestination[0]+1,Direction::goDown,route);		

							aux = route.at(route.size()-1);
							nodoAux = aux->GetNode()+1;
							TL = mapTrafficLight.find(nodoAux);
							route.push_back( TL->second[0]);
						}

						else
						{
							if(XYdestination[0]<sizeMap) ///  girar por abajo
							{
								route.push_back(origin);
								auto aux = route.at(route.size()-1);

								nodoAux = aux->GetNode()-sizeMap;
								auto TL = mapTrafficLight.find(nodoAux);
								route.push_back( TL->second[1]);

								StoreRoute(XYorigin[1],XYdestination[1]-1,Direction::goRight,route);
								StoreRoute(XYorigin[0],XYdestination[0]+2,Direction::goDown,route);	

								aux = route.at(route.size()-1);
						
								nodoAux = aux->GetNode()+1;
								TL = mapTrafficLight.find(nodoAux);
								route.push_back( TL->second[0]);

								nodoAux += -sizeMap;
								TL = mapTrafficLight.find(nodoAux);
								route.push_back( TL->second[1]);
							}
							
							else
							{
								if(XYdestination[1]<sizeMap)// girar por --->
								{		
									route.push_back(origin);
									auto aux = route.at(route.size()-1);

									nodoAux = aux->GetNode()-sizeMap;
									auto TL = mapTrafficLight.find(nodoAux);
									route.push_back( TL->second[1]);

									StoreRoute(XYorigin[1],XYdestination[1]-1,Direction::goRight,route);
									StoreRoute(XYorigin[0],XYdestination[0],Direction::goDown,route);

									aux = route.at(route.size()-1);
									nodoAux = aux->GetNode()+1;
									TL = mapTrafficLight.find(nodoAux);
									route.push_back( TL->second[0]);
								
									nodoAux += 1;
									TL = mapTrafficLight.find(nodoAux);
									route.push_back( TL->second[0]);
									
									nodoAux += sizeMap;
									TL = mapTrafficLight.find(nodoAux);
									route.push_back( TL->second[1]);
									
									nodoAux += -1;
									TL = mapTrafficLight.find(nodoAux);
									route.push_back( TL->second[0]);
									
								}
								else
								{
									cout<<"No se puede llegar 3";
								}
							}
						}		
					}
				}
			}
		}
	}
///////////////////////////////////Si el Nodo destino se encuentra a la derecha y abajo//////////////////////////////



	if(XYorigin[1]>=XYdestination[1] && XYorigin[0]<=XYdestination[0])
	{
		if(XYorigin[0]%2==0) //orientacion <---
		{
			if(XYdestination[1]%2==0) // destino puedo ir abajo  CORRECTO
			{  			
					route.push_back(origin);	
					StoreRoute(XYorigin[1],XYdestination[1],Direction::goLeft,route);
					StoreRoute(XYorigin[0],XYdestination[0],Direction::goDown,route);	
			}
			else
			{

			 if(XYorigin[1]!=XYdestination[1] )
			 {
				if(XYdestination[0]%2==0) // destino puede ir <--- CORRECTO
				{
					route.push_back(origin);

					StoreRoute(XYorigin[1],XYdestination[1]+1,Direction::goLeft,route);
					StoreRoute(XYorigin[0],XYdestination[0],Direction::goDown,route);	

					auto aux = route.at(route.size()-1);

					nodoAux = aux->GetNode()-1;
					auto TL = mapTrafficLight.find(nodoAux);
					route.push_back( TL->second[0] );
				}
				else
				{
					if(XYdestination[0]<sizeMap ) // dar giro por abajo   CORRECTO
					{
						route.push_back(origin);

						StoreRoute(XYorigin[1],XYdestination[1]+1,Direction::goLeft,route);
						StoreRoute(XYorigin[0],XYdestination[0]+1,Direction::goDown,route);	

						auto aux = route.at(route.size()-1);

						nodoAux = aux->GetNode()-1;
						auto TL = mapTrafficLight.find(nodoAux);
						route.push_back( TL->second[0] );

						nodoAux += -sizeMap;
						TL = mapTrafficLight.find(nodoAux);
						route.push_back( TL->second[1] );
					}
					else
					{
						if(XYdestination[1]<sizeMap) //giro por <---  CORRECTO
						{
							route.push_back(origin);

							StoreRoute(XYorigin[1],XYdestination[1]+1,Direction::goLeft,route);
							StoreRoute(XYorigin[0],XYdestination[0]-1,Direction::goDown,route);	

							auto aux = route.at(route.size()-1);

							nodoAux = aux->GetNode()-1;
							auto TL = mapTrafficLight.find(nodoAux);
							route.push_back( TL->second[0] );

							nodoAux += -1;
							TL = mapTrafficLight.find(nodoAux);
							route.push_back( TL->second[0] );

							nodoAux += sizeMap;
							TL = mapTrafficLight.find(nodoAux);
							route.push_back( TL->second[1] );
							
							nodoAux += 1;
							TL = mapTrafficLight.find(nodoAux);
							route.push_back( TL->second[0] );
						}
						else
						{
							cout<<"No se puede llegar";
						}
					}
				}
			  }	
			}
		}
		
		else
		{
			if(XYorigin[1]%2==0) // orientacion abajo
			{
				if(XYdestination[0]%2==0) // destino puedo ir <--- CORRECTO
				{  

					route.push_back(origin);
					StoreRoute(XYorigin[0],XYdestination[0],Direction::goDown,route);
					StoreRoute(XYorigin[1],XYdestination[1],Direction::goLeft,route);	

				}
				else
				{
					if(XYdestination[1]%2==0) //destono puedo baja    CORRECTO
					{
						route.push_back(origin);

						StoreRoute(XYorigin[0],XYdestination[0]-1,Direction::goDown,route);
						StoreRoute(XYorigin[1],XYdestination[1],Direction::goLeft,route);	

						auto aux = route.at(route.size()-1);

						nodoAux = aux->GetNode()+sizeMap;
						auto TL = mapTrafficLight.find(nodoAux);
						route.push_back( TL->second[1] );
	
					}
					else
					{
						if(XYdestination[0]<sizeMap)  // girar por abajo CORRECTO
						{
							
							route.push_back(origin);

							StoreRoute(XYorigin[0],XYdestination[0]-1,Direction::goDown,route);
							StoreRoute(XYorigin[1],XYdestination[1]+1,Direction::goLeft,route);	

							auto aux = route.at(route.size()-1);

							nodoAux = aux->GetNode()+sizeMap;
							auto TL = mapTrafficLight.find(nodoAux);
							route.push_back( TL->second[1] );

							nodoAux +=  sizeMap;
							TL = mapTrafficLight.find(nodoAux);
							route.push_back( TL->second[1] );
							
							nodoAux +=  -1;
							TL = mapTrafficLight.find(nodoAux);
							route.push_back( TL->second[0] );
							
							nodoAux += -sizeMap;
							TL = mapTrafficLight.find(nodoAux);
							route.push_back( TL->second[1] );
														
						}
						else
						{
							if(XYdestination[1]>1) // girar por <---  CORRECTO
							{

								route.push_back(origin);

								StoreRoute(XYorigin[0],XYdestination[0]-1,Direction::goDown,route);
								StoreRoute(XYorigin[1],XYdestination[1]-1,Direction::goLeft,route);	

								auto aux = route.at(route.size()-1);

								nodoAux = aux->GetNode()+sizeMap;
								auto TL = mapTrafficLight.find(nodoAux);
								route.push_back( TL->second[1] );

								nodoAux += 1;
								TL = mapTrafficLight.find(nodoAux);
								route.push_back( TL->second[0] );
							}
							else
							{
								cout<<"No se puede llegar 1";
							}
						}
					}
				}
			}
			else
			{
				if(XYorigin[1]+1<=sizeMap) // recorrer +1 --> y bajar
				{
					if(XYdestination[0]%2==0) //destino puede ir <--   CORRECTO
					{  
						route.push_back(origin);
						auto aux = route.at(route.size()-1);
						nodoAux = aux->GetNode()+1;
						auto TL = mapTrafficLight.find(nodoAux);
						route.push_back( TL->second[0] );

						StoreRoute(XYorigin[0],XYdestination[0],Direction::goDown,route);
						StoreRoute(XYorigin[1],XYdestination[1]-1,Direction::goLeft,route);				
					}
					else
					{
						if(XYdestination[1]%2==0) // destino puede baja  CORRECTO
						{
							
							route.push_back(origin);

							auto aux = route.at(route.size()-1);
							nodoAux = aux->GetNode()+1;
							auto TL = mapTrafficLight.find(nodoAux);
							route.push_back( TL->second[0] );

							StoreRoute(XYorigin[0],XYdestination[0]-1,Direction::goDown,route);
							StoreRoute(XYorigin[1],XYdestination[1]-1,Direction::goLeft,route);

							aux = route.at(route.size()-1);

							nodoAux = aux->GetNode()+sizeMap;
							TL = mapTrafficLight.find(nodoAux);
							route.push_back( TL->second[1] );
						}

						else
						{
							if(XYdestination[0]<sizeMap) // girar por abajo  CORRECTO
							{

								route.push_back(origin);

								auto aux = route.at(route.size()-1);
								nodoAux = aux->GetNode()+1;
								auto TL = mapTrafficLight.find(nodoAux);
								route.push_back( TL->second[0] );

								StoreRoute(XYorigin[0],XYdestination[0]-1,Direction::goDown,route);
								StoreRoute(XYorigin[1],XYdestination[1],Direction::goLeft,route);

								aux = route.at(route.size()-1);

								nodoAux = aux->GetNode()+sizeMap;
								TL = mapTrafficLight.find(nodoAux);
								route.push_back( TL->second[1] );

								nodoAux += sizeMap;
								TL = mapTrafficLight.find(nodoAux);
								route.push_back( TL->second[1] );

								nodoAux += -1;
								TL = mapTrafficLight.find(nodoAux);
								route.push_back( TL->second[0] );

								nodoAux += -sizeMap;
								TL = mapTrafficLight.find(nodoAux);
								route.push_back( TL->second[1] );
							}
							else
							{
								if(XYdestination[1]>1)// girar por <---- CORRECTO
								{
									route.push_back(origin);

									auto aux = route.at(route.size()-1);
									nodoAux = aux->GetNode()+1;
									auto TL = mapTrafficLight.find(nodoAux);
									route.push_back( TL->second[0] );

									StoreRoute(XYorigin[0],XYdestination[0]-1,Direction::goDown,route);
									StoreRoute(XYorigin[1],XYdestination[1]-2,Direction::goLeft,route);

									aux = route.at(route.size()-1);

									nodoAux = aux->GetNode()+sizeMap;
									TL = mapTrafficLight.find(nodoAux);
									route.push_back( TL->second[1] );

									nodoAux += 1;
									TL = mapTrafficLight.find(nodoAux);
									route.push_back( TL->second[0] );
								}
								else
								{
									cout<<"No se puede llegar 2";
								}
							}

						}
					}

				}
				else
				{
					if(XYdestination[1]%2==0) // subir por 1 arriba y <----- CORRECTO
					{	
						route.push_back(origin);

						auto aux = route.at(route.size()-1);
						nodoAux = aux->GetNode() - sizeMap;
						auto TL = mapTrafficLight.find(nodoAux);
						route.push_back( TL->second[1]);

						StoreRoute(XYorigin[1],XYdestination[1],Direction::goLeft,route);
						StoreRoute(XYorigin[0],XYdestination[0]+1,Direction::goDown,route);
					}
					else
					{

						if(XYdestination[0]%2==0) //destino puede bajar y <-- CORRECTO
						{
							route.push_back(origin);

							auto aux = route.at(route.size()-1);
							nodoAux = aux->GetNode() - sizeMap;
							auto TL = mapTrafficLight.find(nodoAux);
							route.push_back( TL->second[1]);

							StoreRoute(XYorigin[1],XYdestination[1]+1,Direction::goLeft,route);
							StoreRoute(XYorigin[0],XYdestination[0]+1,Direction::goDown,route);
							
							aux = route.at(route.size()-1);

							nodoAux = aux->GetNode()-1;
							TL = mapTrafficLight.find(nodoAux);
							route.push_back( TL->second[0] );	
						}

						else
						{
							if(XYdestination[0]<sizeMap) ///  girar por abajo CORRECTO
							{
								route.push_back(origin);

								auto aux = route.at(route.size()-1);
								nodoAux = aux->GetNode() - sizeMap;
								auto TL = mapTrafficLight.find(nodoAux);
								route.push_back( TL->second[1]);

								StoreRoute(XYorigin[1],XYdestination[1]+1,Direction::goLeft,route);
								StoreRoute(XYorigin[0],XYdestination[0]+2,Direction::goDown,route);
								
								aux = route.at(route.size()-1);

								nodoAux = aux->GetNode()-1;
								TL = mapTrafficLight.find(nodoAux);
								route.push_back( TL->second[0] );

								nodoAux += -sizeMap;
								TL = mapTrafficLight.find(nodoAux);
								route.push_back( TL->second[1] );

							}
							
							else
							{
								if(XYdestination[1]<sizeMap)// girar por ---> CORRECTO
								{

									route.push_back(origin);

									auto aux = route.at(route.size()-1);
									nodoAux = aux->GetNode() - sizeMap;
									auto TL = mapTrafficLight.find(nodoAux);
									route.push_back( TL->second[1]);

									StoreRoute(XYorigin[1],XYdestination[1]+1,Direction::goLeft,route);
									StoreRoute(XYorigin[0],XYdestination[0],Direction::goDown,route);
									
								    aux = route.at(route.size()-1);

									nodoAux = aux->GetNode()-1;
									TL = mapTrafficLight.find(nodoAux);
									route.push_back( TL->second[0] );

									nodoAux += -1;
									TL = mapTrafficLight.find(nodoAux);
									route.push_back( TL->second[0] );

									nodoAux += +sizeMap;
									TL = mapTrafficLight.find(nodoAux);
									route.push_back( TL->second[1] );

									nodoAux += 1;
									TL = mapTrafficLight.find(nodoAux);
									route.push_back( TL->second[0] );
								}
								else
								{
									cout<<"No se puede llegar 3";
								}
							}
						}		
					}
				}
			}
		}
	}

//////////////////////////////////////////derecha y arriba//////////////////////////////////////////////////////////////////////////////

	if(XYorigin[1]<=XYdestination[1] && XYorigin[0]>=XYdestination[0])
	{
	    if( XYorigin[0]!=XYdestination[0] )
		{
			if(XYorigin[0]%2!=0) //orientacion --->
			{
				if(XYdestination[1]%2!=0) // destino puedo ir arriba  OK
				{  			
					route.push_back(origin);

					StoreRoute(XYorigin[1],XYdestination[1],Direction::goRight,route);
					StoreRoute(XYorigin[0],XYdestination[0],Direction::goUp,route);			
				}
				else
				{
					if(XYorigin[0]%2==0  || XYorigin[1]!=XYdestination[1] )
					{
						if(XYdestination[0]%2!=0 ) // destino puede ir --->  OK
						{

							route.push_back(origin);

							StoreRoute(XYorigin[1],XYdestination[1]-1,Direction::goRight,route);
							StoreRoute(XYorigin[0],XYdestination[0],Direction::goUp,route);	

							auto aux = route.at(route.size()-1);
							nodoAux = aux->GetNode() + 1;
							auto TL = mapTrafficLight.find(nodoAux);
							route.push_back( TL->second[0]);
						}
						else
						{
							if(XYdestination[0]>1) // dar giro por arriba   OK
							{

								route.push_back(origin);

								StoreRoute(XYorigin[1],XYdestination[1]-1,Direction::goRight,route);
								StoreRoute(XYorigin[0],XYdestination[0]-1,Direction::goUp,route);	

								auto aux = route.at(route.size()-1);
								nodoAux = aux->GetNode() + 1;
								auto TL = mapTrafficLight.find(nodoAux);
								route.push_back( TL->second[0]);

								nodoAux += sizeMap;
								TL = mapTrafficLight.find(nodoAux);
								route.push_back(TL->second[1]);
							}
							else
							{
								if(XYdestination[1]<sizeMap) //giro por --> Ok
								{
									
									route.push_back(origin);

									StoreRoute(XYorigin[1],XYdestination[1]-1,Direction::goRight,route);
									StoreRoute(XYorigin[0],XYdestination[0]+1,Direction::goUp,route);	

									auto aux = route.at(route.size()-1);
									nodoAux = aux->GetNode() + 1;
									auto TL = mapTrafficLight.find(nodoAux);
									route.push_back( TL->second[0]);

									nodoAux += 1;
									TL = mapTrafficLight.find(nodoAux);
									route.push_back( TL->second[0]);

									nodoAux += -sizeMap;
									TL = mapTrafficLight.find(nodoAux);
									route.push_back(TL->second[1]);

									nodoAux += -1;
									TL = mapTrafficLight.find(nodoAux);
									route.push_back( TL->second[0]);								
								}
								else
								{
									cout<<"No se puede llegar";
								}
							}
						}
				  	}
				}
			}
			
			else
			{
				if(XYorigin[1]%2!=0) // orientacion arriba
				{
				  if(XYorigin[1]!=XYdestination[1])
				  {
					if(XYdestination[0]%2!=0) // destino puedo ir --> OK
					{  
						route.push_back(origin);

						StoreRoute(XYorigin[0],XYdestination[0],Direction::goUp,route);
						StoreRoute(XYorigin[1],XYdestination[1],Direction::goRight,route);
					}
					else
					{
						if(XYdestination[1]%2!=0) //destono puedo subir  OK
						{
							route.push_back(origin);

							StoreRoute(XYorigin[0],XYdestination[0]+1,Direction::goUp,route);
							StoreRoute(XYorigin[1],XYdestination[1],Direction::goRight,route);

							auto aux = route.at(route.size()-1);
							nodoAux = aux->GetNode() - sizeMap;
							auto TL = mapTrafficLight.find(nodoAux);
							route.push_back( TL->second[1]);
						}
						else
						{
							if(XYdestination[0]>1)  // girar por arriba OK
							{
								route.push_back(origin);

								StoreRoute(XYorigin[0],XYdestination[0]-1,Direction::goUp,route);
								StoreRoute(XYorigin[1],XYdestination[1],Direction::goRight,route);

								auto aux = route.at(route.size()-1);
								nodoAux = aux->GetNode() + sizeMap;
								auto TL = mapTrafficLight.find(nodoAux);
								route.push_back( TL->second[1]);
							}
							else
							{
								if(XYdestination[1]<sizeMap) // girar por ---> OK
								{		
									route.push_back(origin);

									StoreRoute(XYorigin[0],XYdestination[0]+1,Direction::goUp,route);
									StoreRoute(XYorigin[1],XYdestination[1]+1,Direction::goRight,route);

									auto aux = route.at(route.size()-1);
									nodoAux = aux->GetNode() - sizeMap;
									auto TL = mapTrafficLight.find(nodoAux);
									route.push_back( TL->second[1]);

									nodoAux += - 1;
									TL = mapTrafficLight.find(nodoAux);
									route.push_back( TL->second[0]);									
								}
								else
								{
									cout<<"No se puede llegar 1";
								}
							}

						}
					}
				  }
				}
				else
				{

					if(XYorigin[1]-1>0) // recorrer -1 <-- y subir
					{

						if(XYdestination[0]%2!=0) //destino puede ir -->  OK
						{  

							route.push_back(origin);

							auto aux = route.at(route.size()-1);
							nodoAux = aux->GetNode() - 1;
							auto TL = mapTrafficLight.find(nodoAux);
							route.push_back( TL->second[0]);

							StoreRoute(XYorigin[0],XYdestination[0],Direction::goUp,route);
							StoreRoute(XYorigin[1],XYdestination[1]+1,Direction::goRight,route);						
						}
						else
						{
						 
							if(XYdestination[1]%2!=0) // destino puede subir OK
							{
								route.push_back(origin);

								auto aux = route.at(route.size()-1);
								nodoAux = aux->GetNode() - 1;
								auto TL = mapTrafficLight.find(nodoAux);
								route.push_back( TL->second[0]);

								StoreRoute(XYorigin[0],XYdestination[0]+1,Direction::goUp,route);
								StoreRoute(XYorigin[1],XYdestination[1]+1,Direction::goRight,route);

								aux = route.at(route.size()-1);
								nodoAux = aux->GetNode() - sizeMap;
								TL = mapTrafficLight.find(nodoAux);
								route.push_back( TL->second[1]);
							}

							else
							{

								if(XYdestination[0]>1) // girar por arriba OK
								{

									route.push_back(origin);

									auto aux = route.at(route.size()-1);
									nodoAux = aux->GetNode() - 1;
									auto TL = mapTrafficLight.find(nodoAux);
									route.push_back( TL->second[0]);

									StoreRoute(XYorigin[0],XYdestination[0]-1,Direction::goUp,route);
									StoreRoute(XYorigin[1],XYdestination[1]+1,Direction::goRight,route);

									aux = route.at(route.size()-1);
									nodoAux = aux->GetNode() + sizeMap;
									TL = mapTrafficLight.find(nodoAux);
									route.push_back( TL->second[1]);
								}
								else
								{
									if(XYdestination[1]<sizeMap)// girar por ---->  OK
									{

										route.push_back(origin);

										auto aux = route.at(route.size()-1);
										nodoAux = aux->GetNode() - 1;
										auto TL = mapTrafficLight.find(nodoAux);
										route.push_back( TL->second[0]);

										StoreRoute(XYorigin[0],XYdestination[0]+1,Direction::goUp,route);
										StoreRoute(XYorigin[1],XYdestination[1]+2,Direction::goRight,route);

										aux = route.at(route.size()-1);
										nodoAux = aux->GetNode() - sizeMap;
										TL = mapTrafficLight.find(nodoAux);
										route.push_back( TL->second[1]);

										nodoAux += -1;
										TL = mapTrafficLight.find(nodoAux);
										route.push_back( TL->second[0]);
									}
									else
									{
										cout<<"No se puede llegar 2";
									}
								}

							}

						}

					}
					else
					{
						
						if(XYdestination[1]%2!=0) // bajar por 1 abajo y ----->  OK
						{
							
							route.push_back(origin);

							auto aux = route.at(route.size()-1);
							nodoAux = aux->GetNode() + sizeMap;
							auto TL = mapTrafficLight.find(nodoAux);
							route.push_back( TL->second[1]);

							StoreRoute(XYorigin[1],XYdestination[1],Direction::goRight,route);
							StoreRoute(XYorigin[0],XYdestination[0]-1,Direction::goUp,route);	

						}
						else
						{
							if(XYdestination[0]%2!=0) //destino puede bajar y --> OK
							{

								route.push_back(origin);

								auto aux = route.at(route.size()-1);
								nodoAux = aux->GetNode() + sizeMap;
								auto TL = mapTrafficLight.find(nodoAux);
								route.push_back( TL->second[1]);

								StoreRoute(XYorigin[1],XYdestination[1]-1,Direction::goRight,route);
								StoreRoute(XYorigin[0],XYdestination[0]-1,Direction::goUp,route);	

								aux = route.at(route.size()-1);
								nodoAux = aux->GetNode() + 1;
								TL = mapTrafficLight.find(nodoAux);
								route.push_back( TL->second[0]);	
							}

							else
							{
								if(XYdestination[0]>1) ///  girar por arriba
								{
									route.push_back(origin);

									auto aux = route.at(route.size()-1);
									nodoAux = aux->GetNode() + sizeMap;
									auto TL = mapTrafficLight.find(nodoAux);
									route.push_back( TL->second[1]);

									StoreRoute(XYorigin[1],XYdestination[1]-1,Direction::goRight,route);
									StoreRoute(XYorigin[0],XYdestination[0]-2,Direction::goUp,route);	

									aux = route.at(route.size()-1);
									nodoAux = aux->GetNode() + 1;
									TL = mapTrafficLight.find(nodoAux);
									route.push_back( TL->second[0]);

									nodoAux += sizeMap;
									TL = mapTrafficLight.find(nodoAux);
									route.push_back( TL->second[1]);
								}
								
								else
								{
									if(XYdestination[1]<sizeMap)// girar por --->
									{


										route.push_back(origin);

										auto aux = route.at(route.size()-1);
										nodoAux = aux->GetNode() + sizeMap;
										auto TL = mapTrafficLight.find(nodoAux);
										route.push_back( TL->second[1]);

										StoreRoute(XYorigin[1],XYdestination[1]-1,Direction::goRight,route);
										StoreRoute(XYorigin[0],XYdestination[0],Direction::goUp,route);	

										aux = route.at(route.size()-1);
										nodoAux = aux->GetNode() + 1;
										TL = mapTrafficLight.find(nodoAux);
										route.push_back( TL->second[0]);

										nodoAux += 1;
										TL = mapTrafficLight.find(nodoAux);
										route.push_back( TL->second[0]);
										
										nodoAux += -sizeMap;
										TL = mapTrafficLight.find(nodoAux);
										route.push_back( TL->second[1]);

										nodoAux += -1;
										TL = mapTrafficLight.find(nodoAux);
										route.push_back( TL->second[0]);
									}
									else
									{
										cout<<"No se puede llegar 3";
									}
								}
							}		
						}
					}
				}
	 		}
        }	
	}
////////////////////////////////////////////////////////////////////////////////

	if(XYorigin[1]>=XYdestination[1] && XYorigin[0]>=XYdestination[0])
	{
		if( XYorigin[0]!=XYdestination[0] || XYorigin[0]%2==0 )
		{
			if(XYorigin[0]%2==0) //orientacion <---
			{
				
				if(XYdestination[1]%2!=0) // destino puedo ir arriba OK
				{  			
					route.push_back(origin);

					StoreRoute(XYorigin[1],XYdestination[1],Direction::goLeft, route);
					StoreRoute(XYorigin[0],XYdestination[0],Direction::goUp,route);	
				}
				else
				{
					if(XYorigin[1]!=XYdestination[1] )
					{
						if(XYdestination[0]%2==0) // destino puede ir <--- OK
						{
							route.push_back(origin);

							StoreRoute(XYorigin[1],XYdestination[1]+1,Direction::goLeft, route);
							StoreRoute(XYorigin[0],XYdestination[0],Direction::goUp,route);	

							auto aux = route.at(route.size()-1);
							nodoAux = aux->GetNode() - 1;
							auto TL = mapTrafficLight.find(nodoAux);
							route.push_back( TL->second[0]);
						}
						else
						{
							if(XYdestination[0]>1 ) // dar giro por arriba   OK
							{
								route.push_back(origin);

								StoreRoute(XYorigin[1],XYdestination[1]+1,Direction::goLeft, route);
								StoreRoute(XYorigin[0],XYdestination[0]-1,Direction::goUp,route);	

								auto aux = route.at(route.size()-1);
								nodoAux = aux->GetNode() - 1;
								auto TL = mapTrafficLight.find(nodoAux);
								route.push_back( TL->second[0]);

								nodoAux += sizeMap;
								TL = mapTrafficLight.find(nodoAux);
								route.push_back( TL->second[1]);
							}
							else
							{
								if(XYdestination[1]>1) //giro por <---  OK
								{
									route.push_back(origin);

									StoreRoute(XYorigin[1],XYdestination[1]+1,Direction::goLeft, route);
									StoreRoute(XYorigin[0],XYdestination[0]+1,Direction::goUp,route);	

									auto aux = route.at(route.size()-1);
									nodoAux = aux->GetNode() - 1;
									auto TL = mapTrafficLight.find(nodoAux);
									route.push_back( TL->second[0]);

									nodoAux += -1;
									TL = mapTrafficLight.find(nodoAux);
									route.push_back( TL->second[0]);

									nodoAux += -sizeMap;
									TL = mapTrafficLight.find(nodoAux);
									route.push_back( TL->second[1]);

									nodoAux += 1;
									TL = mapTrafficLight.find(nodoAux);
									route.push_back( TL->second[0]);									
								}
								else
								{
									cout<<"No se puede llegar";
								}
							}
						}
					}	
				}
			}
			
			else
			{
				if(XYorigin[1]%2!=0) // orientacion arriba
				{
					if(XYdestination[0]%2==0) // destino puedo ir <--- CORRECTO
					{  
						route.push_back(origin);

						StoreRoute(XYorigin[0],XYdestination[0],Direction::goUp, route);
						StoreRoute(XYorigin[1],XYdestination[1],Direction::goLeft,route);
					}
					else
					{
						if(XYdestination[1]%2!=0) //destono puedo subir    OK
						{

							route.push_back(origin);

							StoreRoute(XYorigin[0],XYdestination[0]+1,Direction::goUp, route);
							StoreRoute(XYorigin[1],XYdestination[1],Direction::goLeft,route);

							auto aux = route.at(route.size()-1);
							nodoAux = aux->GetNode() - sizeMap;
							auto TL = mapTrafficLight.find(nodoAux);
							route.push_back( TL->second[1]);	
						}
						else
						{
							if(XYdestination[0]>1)  // girar por arriba OK
							{
								route.push_back(origin);

								StoreRoute(XYorigin[0],XYdestination[0]+1,Direction::goUp, route);
								StoreRoute(XYorigin[1],XYdestination[1]+1,Direction::goLeft,route);

								auto aux = route.at(route.size()-1);
								nodoAux = aux->GetNode() - sizeMap;
								auto TL = mapTrafficLight.find(nodoAux);
								route.push_back( TL->second[1]);

								nodoAux += -sizeMap;
								TL = mapTrafficLight.find(nodoAux);
								route.push_back( TL->second[1]);

								nodoAux += -1;
								TL = mapTrafficLight.find(nodoAux);
								route.push_back( TL->second[0]);

								nodoAux += sizeMap;
								TL = mapTrafficLight.find(nodoAux);
								route.push_back( TL->second[1]);
							}
							else
							{
								if(XYdestination[1]>1) // girar por <---  OK
								{
									route.push_back(origin);

									StoreRoute(XYorigin[0],XYdestination[0]+1,Direction::goUp, route);
									StoreRoute(XYorigin[1],XYdestination[1]-1,Direction::goLeft,route);

									auto aux = route.at(route.size()-1);
									nodoAux = aux->GetNode() - sizeMap;
									auto TL = mapTrafficLight.find(nodoAux);
									route.push_back( TL->second[1]);

									nodoAux += 1;
									TL = mapTrafficLight.find(nodoAux);
									route.push_back( TL->second[0]);
								}
								else
								{
									cout<<"No se puede llegar 1";
								}
							}
						}
					}
				}
				else
				{
					if(XYorigin[1]+1<=sizeMap) // recorrer +1 --> y subir
					{
						if(XYdestination[0]%2==0) //destino puede ir <--   OK
						{  

							route.push_back(origin);

							auto aux = route.at(route.size()-1);
							nodoAux = aux->GetNode() + 1;
							auto TL = mapTrafficLight.find(nodoAux);
							route.push_back( TL->second[0]);

							StoreRoute(XYorigin[0],XYdestination[0],Direction::goUp, route);
							StoreRoute(XYorigin[1],XYdestination[1]-1,Direction::goLeft,route);
						}
						else
						{
							
							if(XYdestination[1]%2!=0) // destino puede baja  CORRECTO
							{
								route.push_back(origin);

								auto aux = route.at(route.size()-1);
								nodoAux = aux->GetNode() + 1;
								auto TL = mapTrafficLight.find(nodoAux);
								route.push_back( TL->second[0]);

								StoreRoute(XYorigin[0],XYdestination[0]+1,Direction::goUp, route);
								StoreRoute(XYorigin[1],XYdestination[1]-1,Direction::goLeft,route);

								aux = route.at(route.size()-1);
								nodoAux = aux->GetNode() - sizeMap;
								TL = mapTrafficLight.find(nodoAux);
								route.push_back( TL->second[1]);
							}
							else
							{
								if(XYdestination[0]>1) // girar por arriba  OK
								{
									route.push_back(origin);

									auto aux = route.at(route.size()-1);
									nodoAux = aux->GetNode() + 1;
									auto TL = mapTrafficLight.find(nodoAux);
									route.push_back( TL->second[0]);

									StoreRoute(XYorigin[0],XYdestination[0]+1,Direction::goUp, route);
									StoreRoute(XYorigin[1],XYdestination[1],Direction::goLeft,route);

									aux = route.at(route.size()-1);
									nodoAux = aux->GetNode() - sizeMap;
									TL = mapTrafficLight.find(nodoAux);
									route.push_back( TL->second[1]);

									nodoAux += -sizeMap;
									TL = mapTrafficLight.find(nodoAux);
									route.push_back( TL->second[1]);

									nodoAux += -1;
									TL = mapTrafficLight.find(nodoAux);
									route.push_back( TL->second[0]);

									nodoAux += sizeMap;
									TL = mapTrafficLight.find(nodoAux);
									route.push_back( TL->second[1]);
								}
								else
								{
									if(XYdestination[1]>1)// girar por <---- OK
									{
										route.push_back(origin);

										auto aux = route.at(route.size()-1);
										nodoAux = aux->GetNode() + 1;
										auto TL = mapTrafficLight.find(nodoAux);
										route.push_back( TL->second[0]);

										StoreRoute(XYorigin[0],XYdestination[0]+1,Direction::goUp, route);
										StoreRoute(XYorigin[1],XYdestination[1]-2,Direction::goLeft,route);

										aux = route.at(route.size()-1);
										nodoAux = aux->GetNode() - sizeMap;
										TL = mapTrafficLight.find(nodoAux);
										route.push_back( TL->second[1]);

										nodoAux += 1;
										TL = mapTrafficLight.find(nodoAux);
										route.push_back( TL->second[0]);
									}
									else
									{
										cout<<"No se puede llegar 2";
									}
								}
							}
						}
					}
					else
					{
						if(XYorigin[0]+1<=sizeMap) //  bajar por 1 abajo y <----- OK
						{
							////VERIFICAR DESDE AQUI
							if(XYdestination[1]%2!=0) // DESTINO TIENE CAMINO ASIA ARRIBA
							{
								route.push_back(origin);

								auto aux = route.at(route.size()-1);
								nodoAux = aux->GetNode() + sizeMap;
								auto TL = mapTrafficLight.find(nodoAux);
								route.push_back( TL->second[1]);

								StoreRoute(XYorigin[1],XYdestination[1],Direction::goLeft, route);
								StoreRoute(XYorigin[0],XYdestination[0]-1,Direction::goUp,route);

							}
							else
							{
								if(XYdestination[0]%2==0) //destino puede bajar y <-- OK
								{
									
									route.push_back(origin);

									auto aux = route.at(route.size()-1);
									nodoAux = aux->GetNode() + sizeMap;
									auto TL = mapTrafficLight.find(nodoAux);
									route.push_back( TL->second[1]);

									StoreRoute(XYorigin[1],XYdestination[1]+1,Direction::goLeft, route);
									StoreRoute(XYorigin[0],XYdestination[0]-1,Direction::goUp,route);

									aux = route.at(route.size()-1);
									nodoAux = aux->GetNode() -1;
									TL = mapTrafficLight.find(nodoAux);
									route.push_back( TL->second[0]);	
								}
								else
								{
									if(XYdestination[0]>1) ///  girar por arriba OK
									{
										route.push_back(origin);

										auto aux = route.at(route.size()-1);
										nodoAux = aux->GetNode() + sizeMap;
										auto TL = mapTrafficLight.find(nodoAux);
										route.push_back( TL->second[1]);

										StoreRoute(XYorigin[1],XYdestination[1]+1,Direction::goLeft, route);
										StoreRoute(XYorigin[0],XYdestination[0]-2,Direction::goUp,route);

										aux = route.at(route.size()-1);
										nodoAux = aux->GetNode() -1;
										TL = mapTrafficLight.find(nodoAux);
										route.push_back( TL->second[0]);

										nodoAux += sizeMap;
										TL = mapTrafficLight.find(nodoAux);
										route.push_back( TL->second[1]);										
									}
									
									else
									{
										if(XYdestination[1]>1)// girar por ---> CORRECTO
										{
											route.push_back(origin);

											auto aux = route.at(route.size()-1);
											nodoAux = aux->GetNode() + sizeMap;
											auto TL = mapTrafficLight.find(nodoAux);
											route.push_back( TL->second[1]);

											StoreRoute(XYorigin[1],XYdestination[1]+1,Direction::goLeft, route);
											StoreRoute(XYorigin[0],XYdestination[0],Direction::goUp,route);

											aux = route.at(route.size()-1);
											nodoAux = aux->GetNode() -1;
											TL = mapTrafficLight.find(nodoAux);
											route.push_back( TL->second[0]);

											nodoAux += -1;
											TL = mapTrafficLight.find(nodoAux);
											route.push_back( TL->second[0]);

											nodoAux += -sizeMap;
											TL = mapTrafficLight.find(nodoAux);
											route.push_back( TL->second[1]);

											nodoAux += 1;
											TL = mapTrafficLight.find(nodoAux);
											route.push_back( TL->second[0]);
										}
										else
										{
											cout<<"No se puede llegar 3";
										}
									}
								}		
							}
						}
					}
				}
			}
		}
	}


	
	auto aux = route.at(route.size()-1);

	if (aux != destination)
	{
		cout<<"dar una vuelta \n";
		if(aux->GetDirection() == 0 && destination->GetDirection() == 90 )
		{
			nodoAux = aux->GetNode() +1;
			auto TL = mapTrafficLight.find(nodoAux);
			route.push_back( TL->second[0]);

			nodoAux += sizeMap;
			TL = mapTrafficLight.find(nodoAux);
			route.push_back( TL->second[1]);

			nodoAux += -1;
			TL = mapTrafficLight.find(nodoAux);
			route.push_back( TL->second[0]);

			nodoAux += -sizeMap;
			TL = mapTrafficLight.find(nodoAux);
			route.push_back( TL->second[1]);
		}
		else
		{
			if(aux->GetDirection() == 0 && destination->GetDirection() == 270 )
			{
				nodoAux = aux->GetNode() +1;
				auto TL = mapTrafficLight.find(nodoAux);
				route.push_back( TL->second[0]);

				nodoAux += -sizeMap;
				TL = mapTrafficLight.find(nodoAux);
				route.push_back( TL->second[1]);

				nodoAux += -1;
				TL = mapTrafficLight.find(nodoAux);
				route.push_back( TL->second[0]);

				nodoAux += sizeMap;
				TL = mapTrafficLight.find(nodoAux);
				route.push_back( TL->second[1]);
			}
			else
			{
				if(aux->GetDirection() == 180 && destination->GetDirection() == 90 )
				{
					nodoAux = aux->GetNode() -1;
					auto TL = mapTrafficLight.find(nodoAux);
					route.push_back( TL->second[0]);

					nodoAux += sizeMap;
					TL = mapTrafficLight.find(nodoAux);
					route.push_back( TL->second[1]);

					nodoAux += 1;
					TL = mapTrafficLight.find(nodoAux);
					route.push_back( TL->second[0]);

					nodoAux += -sizeMap;
					TL = mapTrafficLight.find(nodoAux);
					route.push_back( TL->second[1]);
				}
				else
				{
					if(aux->GetDirection() == 180 && destination->GetDirection() == 270 )
					{
						nodoAux = aux->GetNode() -1;
						auto TL = mapTrafficLight.find(nodoAux);
						route.push_back( TL->second[0]);

						nodoAux += -sizeMap;
						TL = mapTrafficLight.find(nodoAux);
						route.push_back( TL->second[1]);

						nodoAux += 1;
						TL = mapTrafficLight.find(nodoAux);
						route.push_back( TL->second[0]);

						nodoAux += sizeMap;
						TL = mapTrafficLight.find(nodoAux);
						route.push_back( TL->second[1]);
					}
					else
					{
						if(aux->GetDirection() == 90 && destination->GetDirection() == 180 )
						{

							
							nodoAux = aux->GetNode() - sizeMap;
							auto TL = mapTrafficLight.find(nodoAux);
							route.push_back( TL->second[1]);

							nodoAux += 1;
							TL = mapTrafficLight.find(nodoAux);
							route.push_back( TL->second[0]);

							nodoAux += sizeMap;
							TL = mapTrafficLight.find(nodoAux);
							route.push_back( TL->second[1]);

							nodoAux += -1;
							TL = mapTrafficLight.find(nodoAux);
							route.push_back( TL->second[0]);
						}
						else
						{
							if(aux->GetDirection() == 90 && destination->GetDirection() == 0 )
							{
								
								nodoAux = aux->GetNode() - sizeMap;
								auto TL = mapTrafficLight.find(nodoAux);
								route.push_back( TL->second[1]);

								nodoAux += -1;
								TL = mapTrafficLight.find(nodoAux);
								route.push_back( TL->second[0]);

								nodoAux += sizeMap;
								TL = mapTrafficLight.find(nodoAux);
								route.push_back( TL->second[1]);

								nodoAux += 1;
								TL = mapTrafficLight.find(nodoAux);
								route.push_back( TL->second[0]);
							}
							else
							{
								if(aux->GetDirection() == 270 && destination->GetDirection() == 180 )
								{
									
									nodoAux = aux->GetNode() +sizeMap;
									auto TL = mapTrafficLight.find(nodoAux);
									route.push_back( TL->second[1]);

									nodoAux += 1;
									TL = mapTrafficLight.find(nodoAux);
									route.push_back( TL->second[0]);

									nodoAux += -sizeMap;
									TL = mapTrafficLight.find(nodoAux);
									route.push_back( TL->second[1]);

									nodoAux += -1;
									TL = mapTrafficLight.find(nodoAux);
									route.push_back( TL->second[0]);
								}
								else
								{
									nodoAux = aux->GetNode() +sizeMap;
									auto TL = mapTrafficLight.find(nodoAux);
									route.push_back( TL->second[1]);

									nodoAux += -1;
									TL = mapTrafficLight.find(nodoAux);
									route.push_back( TL->second[0]);

									nodoAux += -sizeMap;
									TL = mapTrafficLight.find(nodoAux);
									route.push_back( TL->second[1]);

									nodoAux += 1;
									TL = mapTrafficLight.find(nodoAux);
									route.push_back( TL->second[0]);
								}

							}
						}

					}
				}

			}
		}

	}
aux = route.at(route.size()-1);
	if (aux == destination)
	{
		cout<<"si llegue por el semforo que tenia que llegar\n";
	}

	for(auto i : route)
	{
		cout<<i->GetNode() <<":"<< i->GetDirection() <<"  ";
	}
	cout<<"\n";

 	return route;
}


void Map::StoreRoute(const size_t &ini , const size_t &fin , Direction orientation, vector<shared_ptr<TrafficLight>> &route)
{
	auto ultimatePosision = route.at(route.size()-1);
	int ultimateNodo = ultimatePosision->GetNode() ;
	size_t initial;
	size_t final;
	size_t incremento;
	int uxTL;
	switch(orientation)
	{
		case Direction::goUp:
				uxTL=1;
				initial= fin;
				final= ini;
				incremento= -sizeMap;
			break;
		case Direction::goDown:
				uxTL=1;
				initial= ini ;
				final= fin;
				incremento = sizeMap;
			break;
		case Direction::goRight:
				uxTL=0;
				initial= ini;
				final= fin;
				incremento = 1;	
			break;
		case Direction::goLeft:
				uxTL=0;
				initial= fin;
				final= ini;
				incremento = -1;
			break;	
	}
	for(auto i = initial ; i<final; ++i )
	{
		ultimateNodo+=incremento;
		auto findNodo =  mapTrafficLight.find(ultimateNodo);
		route.push_back(findNodo->second[uxTL]);
	}
}
      
vector<size_t> Map::ConvertCoordinates(const int &x)
{
	vector<size_t> coordinates;
	coordinates={0,0};

	coordinates[0]=(int)ceil((double)x/sizeMap);
	coordinates[1]= sizeMap-((sizeMap*coordinates[0])-x);

	return coordinates;

}


int Map::getSizeMap() const
{
	return sizeMap;
}

map<int, vector<shared_ptr<TrafficLight>>> Map::GetMapTrafficLight() const
{
	return mapTrafficLight;
}
