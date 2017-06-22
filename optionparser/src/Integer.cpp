#include <iostream>

#include "../include/Integer.h"

Integer::Integer(const string& name, const char abbr, const OptionType type, const string& strValue)
:name{name}, abbr{abbr}, type{type}, strValue{strValue}
{
	for(auto c : strValue)
	{
	    if(c != 45)
		if(c < 48 || c > 57)
			throw SemanticException("Error Integer Number Type");
	}
    value=stoi(strValue);
}

string Integer::GetName()const
{
    return name;
}

char Integer::GetAbbr()const
{
    return abbr;
}

string Integer::GetValueString()const
{
    return strValue;
}

OptionType Integer::GetType()const
{
    return type;
}

int Integer::GetValue()const
{
    return value;
}

Integer::~Integer()
{

}
