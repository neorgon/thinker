#include <iostream>

#include "../include/Boolean.h"

Boolean::Boolean(const string& name, const char abbr, const OptionType type, string strValue="true")
:name{name}, abbr{abbr}, type{type}, strValue{strValue}
{
	for (auto c: strValue)
	{
		if (c<97)
			c+=32;
	}
    if (strValue=="false")
        value=0;
    else if (strValue=="true"||strValue==""||strValue==" ")
        value=1;
    else
    	throw SemanticException("Error Boolean Type");
}

string Boolean::GetName()const
{
    return name;
}

char Boolean::GetAbbr()const
{
    return abbr;
}

string Boolean::GetValueString()const
{
    return strValue;
}

OptionType Boolean::GetType()const
{
    return type;
}

bool Boolean::GetValue()const
{
    return value;
}

Boolean::~Boolean()
{
    //dtor
}
