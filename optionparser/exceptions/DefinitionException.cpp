#include "DefinitionException.h"

DefinitionException::DefinitionException(const char* msg)
:msg{msg}
{

}

const char* DefinitionException::what() const throw ()
{
    return msg;
}
