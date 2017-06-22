#include "../include/Text.h"

Text::Text(const string& name, const char abbr, const OptionType type, const string& strValue)
:name{name}, abbr{abbr}, type{type}, strValue{strValue}
{

}

string Text::GetName()const
{
    return name;
}

char Text::GetAbbr()const
{
    return abbr;
}

string Text::GetValueString()const
{
    return strValue;
}

OptionType Text::GetType()const
{
    return type;
}

const char* Text::GetValue()const
{
    return strValue.c_str();
}

Text::~Text()
{
    //dtor
}
