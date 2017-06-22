cmake_minimum_required(VERSION 2.8.9)

#set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/build)
#set(EXECUTABLE_OUTPUT_PATH ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})

add_compile_options(-std=c++11)

add_subdirectory(thirdParty/googletest)
add_subdirectory(thinker)
add_subdirectory(thinker/test)
add_subdirectory(optionparser)
add_subdirectory(optionparser/test)
add_subdirectory(Dev22food)

