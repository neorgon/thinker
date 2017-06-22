project(thinker)
cmake_minimum_required(VERSION 2.8.9)
set(libthinker_SRCS 
	./src/Perceptron.cpp 
	./src/TransitionByStep.cpp 
	./src/TransitionSoftMax.cpp
	./src/TransitionHiperbolicTangent.cpp
	./src/TransitionSigmoid.cpp
	./src/Layer.cpp
	./src/NeuralNetwork.cpp
	./src/Data.cpp
	./include/Perceptron.h 
	./include/TransitionByStep.h
	./include/TransitionSoftMax.h
	./include/TransitionHiperbolicTangent.h
	./include/TransitionSigmoid.h
	./include/Layer.h
	./include/NeuralNetwork.h
	./include/Data.h

	
)
add_library(thinker STATIC
    ${libthinker_SRCS}
)

target_include_directories(thinker PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)
#set(main main.cpp)
#add_executable(Neural
#    ${main}
#)
#target_link_libraries(Neural
#    thinker
#)

