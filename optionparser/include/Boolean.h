#ifndef BOOLEAN_H
#define BOOLEAN_H

#include "IOptionType.h"
#include "../exceptions/SemanticException.h"

class Boolean:public IOptionType
{
    string name;
    char abbr;
    OptionType type;
    string strValue;
    bool value = true;

    public:
        Boolean(const string& name, const char abbr, const OptionType type, string strValue);
        string GetName() const override;
        char GetAbbr() const override;
        string GetValueString() const override;
        OptionType GetType() const override;
        bool GetValue()const;
        ~Boolean();
};

#endif // BOOLEAN_H
