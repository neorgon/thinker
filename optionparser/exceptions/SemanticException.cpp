#include "SemanticException.h"

SemanticException::SemanticException(const char* msg)
:msg{msg}
{

}

const char* SemanticException::what() const throw ()
{
    return msg;
}
