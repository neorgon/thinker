cmake_minimum_required(VERSION 2.6)
set(NAME_PROJECT optionparserlib)
project(${NAME_PROJECT})

add_compile_options(-std=c++11)

set(libreria 
	./exceptions/SemanticException.cpp
	./exceptions/SemanticException.h
	./exceptions/SyntaxException.cpp
	./exceptions/SyntaxException.h 
	./exceptions/DefinitionException.cpp
	./exceptions/DefinitionException.h 
	./include/Boolean.h 
	./include/Integer.h
	./include/IOptionType.h
	./include/OptionDefinition.h
	./include/OptionParser.h
	./include/OptionType.h
	./include/Real.h
	./include/Text.h
	./src/Boolean.cpp
	./src/Integer.cpp
	./src/OptionDefinition.cpp
	./src/OptionParser.cpp
	./src/Real.cpp
	./src/Text.cpp

)


add_library(optionparserlib STATIC
    ${libreria}
)

# Specify here the include directories exported
# by this library
target_include_directories(optionparserlib PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)



