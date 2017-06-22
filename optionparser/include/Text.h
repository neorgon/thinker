#ifndef TEXT_H
#define TEXT_H

#include "IOptionType.h"

class Text:public IOptionType
{
    string name;
    char abbr;
    OptionType type;
    string strValue;

    public:
        Text(const string& name, const char abbr, const OptionType type, const string& strValue);
        string GetName() const override;
        char GetAbbr() const override;
        string GetValueString() const override;
        OptionType GetType() const override;
        const char* GetValue()const;
        ~Text();
};

#endif // TEXT_H
