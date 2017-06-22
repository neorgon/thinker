#ifndef DEFINITIONEXCEPTION_H
#define DEFINITIONEXCEPTION_H

#include<exception>

using namespace std;

class DefinitionException:public exception
{
    const char* msg;
    public:
        DefinitionException(const char* msg);
        const char* what() const throw();
};

#endif // DEFINITIONEXCEPTION_H
