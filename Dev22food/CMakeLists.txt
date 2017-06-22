cmake_minimum_required(VERSION 2.8.9)
project(devfood)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/build)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
set(Main_SRCS
    main.cpp
)

add_executable(devFood
    ${Main_SRCS}
)

if(TARGET thinker)
message("existe")
else()
	add_subdirectory(./../thinker thinker)
	set(compila 1)
endif()

target_link_libraries(devFood 
    thinker
)
