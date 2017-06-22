#ifndef REAL_H
#define REAL_H

#include "IOptionType.h"
#include "../exceptions/SemanticException.h"

class Real:public IOptionType
{
    string name;
    char abbr;
    OptionType type;
    string strValue;
    float value;
public:
    Real(const string& name, const char abbr, const OptionType type, const string& strValue);
    string GetName() const override;
    char GetAbbr() const override;
    string GetValueString() const override;
    OptionType GetType() const override;
    float GetValue()const;
    ~Real();
};

#endif // REAL_H
