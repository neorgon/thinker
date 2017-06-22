#include "SyntaxException.h"

SyntaxException::SyntaxException(const char* msg)
:msg{msg}
{

}

const char* SyntaxException::what()const throw()
{
    return msg;
}


