#ifndef INTEGER_H
#define INTEGER_H

#include "IOptionType.h"
#include "../exceptions/SemanticException.h"

class Integer: public IOptionType
{
    string name;
    char abbr;
    OptionType type;
    string strValue;
    int value;

    public:
        Integer(const string& name, const char abbr, const OptionType type, const string& strValue);
        string GetName() const override;
        char GetAbbr() const override;
        string GetValueString() const override;
        OptionType GetType() const override;
        int GetValue()const;
        ~Integer();
};

#endif // INTEGER_H
