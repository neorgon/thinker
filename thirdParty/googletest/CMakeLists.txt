cmake_minimum_required(VERSION 2.8.9)
project(googletest)
set(libgoogle_SRCS 
	#./include/gtest/gtest.h 
	#./src/gtest.cc 
	./src/gtest-all.cc 
	./src/gtest_main.cc 
	
)

add_library(googlet STATIC
    ${libgoogle_SRCS}
)

target_include_directories(googlet PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

