project(trafficsimulator)
cmake_minimum_required(VERSION 2.8.9)
set(libtraffic_SRCS 
	./src/Map.cpp 
	./src/Simulation.cpp 
	./src/TrafficSimulator.cpp
	./src/Vehicle.cpp
	./src/WindowsConsole.cpp
	./src/TrafficLight.cpp
	./include/Map.h
	./include/Simulation.h
	./include/TrafficSimulator.h
	./include/Vehicle.h
	./include/WindowsConsole.h
	./include/TrafficLight.h
)

add_library(traffic STATIC
    ${libtraffic_SRCS}
)

target_include_directories(traffic PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

set(m main.cpp)
add_executable(traffic1
    ${m}
)

target_link_libraries(traffic1
   traffic
)




