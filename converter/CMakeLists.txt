cmake_minimum_required(VERSION 2.6)
set(NAME_PROJECT converterlib)
project(${NAME_PROJECT})

add_compile_options(-std=c++11)

set(libreria 

	./include/DeserializeObject.h 
	./include/json.hpp
	./include/JsonGeneratorFile.h
	./include/SerializeObject.h	
	./src/DeserializeObject.cpp
	./src/JsonGeneratorFile.cpp
	./src/SerializeObject.cpp	
    ./main.cpp

)


add_executable(jsonConverter
    ${libreria}
)



