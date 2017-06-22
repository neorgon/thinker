project(thinkerTest)
cmake_minimum_required(VERSION 2.8.9)
ADD_DEFINITIONS(-DGTEST)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/build)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
set(MainTest_SRCS
    AndTest.cpp
    OrTest.cpp 
    NotTest.cpp 
    XYTest.cpp 
    TransitionFunctionTests.cpp
    PerceptronTest.cpp
    LayerTest.cpp
    DataTest.cpp
    NeuralTest.cpp
  #  NeuralNetworkTest.cpp
)

add_executable(TestPeceptron
    ${MainTest_SRCS}
)

if(TARGET thinker)
message("saltando existe")
else()
	add_subdirectory(./../../thinker thinker)
endif()
if (TARGET googlet)
message("saltando existe")
else()
	add_subdirectory(./../../thirdParty/googletest googletest)
endif()

target_link_libraries(TestPeceptron
    googlet thinker
)