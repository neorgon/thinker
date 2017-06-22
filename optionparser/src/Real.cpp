#include <iostream>

#include "../include/Real.h"

Real::Real(const string& name, const char abbr, const OptionType type, const string& strValue)
:name{name}, abbr{abbr}, type{type}, strValue{strValue}
{
	for(auto c : strValue)
	{
		if(c>47&&c<58)
		{

		}
		else if (c==46 || c == 45)
        {

        }
        else
            throw SemanticException("Error Real Number Type");
	}
    value=stof(strValue);
}

string Real::GetName()const
{
    return name;
}

char Real::GetAbbr()const
{
    return abbr;
}

string Real::GetValueString()const
{
    return strValue;
}

OptionType Real::GetType()const
{
    return type;
}

float Real::GetValue()const
{
    return value;
}


Real::~Real()
{
    //dtor
}
