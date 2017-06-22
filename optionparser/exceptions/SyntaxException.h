#ifndef SYNTAXEXCEPTION_H
#define SYNTAXEXCEPTION_H

#include<exception>

using namespace std;

class SyntaxException:public exception
{
    const char* msg;
    public:
        SyntaxException(const char* msg);
        const char* what() const throw();
};

#endif // SYNTAXEXCEPTION_H
