#ifndef IOPTIONTYPE_H
#define IOPTIONTYPE_H

#include <string>
#include "OptionType.h"

using namespace std;

class IOptionType
{
    public:
        virtual string GetName() const = 0;
        virtual char GetAbbr() const = 0;
        virtual string GetValueString() const = 0;
        virtual OptionType GetType() const = 0;
        virtual ~IOptionType() {}
};

#endif // IOPTIONTYPE_H
