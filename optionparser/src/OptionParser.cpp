#include "../include/OptionParser.h"
#include <sstream>

OptionParser::OptionParser(int argc, const char** args)
{
    int token = 1;
    tokenOption = "";
    tokenValue = "";

    while (token < argc)
    {
        if(tokenOption.empty())
        {
            tokenOption = isOption(string(args[token]));
            token++;
        }
        else
            if(tokenValue.empty())
            {
                if (args[token][0] == '-' &&
                    (args[token][1] < '0' || args[token][1] > '9'))
                    tokenValue = "true";
                else
                    if (args[token][0] == '[')
                    {
                        addList = true;
                        tokenValue = isValue(string(args[token]).substr(1));
                        token++;
                    }
                    else
                    {
                        tokenValue = isValue(string(args[token]));
                        token++;
                    }
            }
            else
                if (addList)
                {
                   tokenValue += " ";
                   tokenValue += isValue(string(args[token]));
                   token++;
                }

        if (!tokenOption.empty() && !tokenValue.empty())
        {
            if (!addList)
            {
                tokens.push_back(make_pair(tokenOption, tokenValue));
                tokenOption = "";
                tokenValue = "";
            }
        }
    }

    if (!tokenOption.empty())
        tokens.push_back(make_pair(tokenOption, "true"));
}

OptionParser::~OptionParser()
{
    for (auto m: options)
    {
    	for(auto o: m.second)
    	{
    		delete o;
    	}
    }
}

string OptionParser::isOption(const string &token)
{
    if(token[0] == '-' && token[1] == '-')
    {
        return token.substr(2);
    }
    else
        if (token[0] == '-' && token[2] == '\0')
        {
            return token.substr(1);
        }
        else
        {
            throw SyntaxException ("Wrong format Option.");
        }
}

string OptionParser::isValue(const string &token)
{
    if (token[token.length() - 1] == ']')
    {
        addList = false;
        return token.substr(0, token.length() - 1);
    }

    return token;
}

void OptionParser::AddDefinition(const char* name, char abbr, OptionType type, bool optional)
{
    string names = name;

	for (auto i:names)
	{
		if ( !(isalpha(i)) && (i != '_') )
		{
			throw DefinitionException ("Name declaration error");
		}
	}

	if (!isalpha(abbr))
		throw DefinitionException ("Abbreviation declaration error");

	for (auto& i: definitions)
	{
		if(i.GetName()==names||i.GetAbbr()[0]==abbr)
			throw DefinitionException ("Repeated definition");
	}

    OptionDefinition newDefinition(string(name), string(1, abbr), type, optional);
    definitions.push_back(newDefinition);
}

void OptionParser::AddInteger(const char* name, char abbr, bool optional)
{
    AddDefinition(name, abbr, OptionType::Integer, optional);
}

void OptionParser::AddReal(const char* name, char abbr, bool optional)
{
    AddDefinition(name, abbr, OptionType::Real, optional);
}

void OptionParser::AddBoolean(const char* name, char abbr, bool optional)
{
    AddDefinition(name, abbr, OptionType::Boolean, optional);
}

void OptionParser::AddText(const char* name, char abbr, bool optional)
{
    AddDefinition(name, abbr, OptionType::Text, optional);
}

bool OptionParser::AnalyzeSyntax()
{
    vector <OptionDefinition>::iterator it;

    for (auto &t : tokens)
    {
        it = find_if(definitions.begin(), definitions.end(), OptionDefinition::Finder(t.first));
        if (it == definitions.end()/* && t.first.compare("EndList") != 0*/)
            throw SyntaxException("Command not found");
        else
            if (it->GetDefined())
                throw SyntaxException("Duplicated Parameter");
            else
                it->SetDefined();
    }

    vector<OptionDefinition> trueOptions;

    for (auto j:definitions)
    	if (j.GetOptional())
    		trueOptions.push_back(j);

    for (auto i: trueOptions)
    {
    	for (auto j: tokens)
    	{
    		if(i.GetName() == j.first || i.GetAbbr() == j.first)
    			trueOptions.pop_back();
    	}
    }

    if(!trueOptions.empty())
    	throw SyntaxException("Mandatory command not found");

    return true;
}

vector<string> explode(string const &s, char delim)
{
    vector<string> result;
    istringstream iss(s);

    for (string token; getline(iss, token, delim); )
    {
        result.push_back(move(token));
    }

    return result;
}

bool OptionParser::AnalyzeSemantic()
{
    vector<OptionDefinition>::const_iterator itOptionDefinition;
    vector<pair<string, string>>::const_iterator itTokens;
    vector<string> values;
    size_t e = 0;

    for (itTokens = tokens.begin(); itTokens < tokens.end(); itTokens++, e++)
    {
        itOptionDefinition = find_if(definitions.begin(),
                                     definitions.end(),
                                     OptionDefinition::Finder(tokens[e].first));
        string name = itOptionDefinition->GetName();
        string abbr = itOptionDefinition->GetAbbr();
        OptionType type = itOptionDefinition->GetType();
        options.insert(pair<string, vector<IOptionType*>> (name, vector<IOptionType*>()));
        values = explode(tokens[e].second, ' ');
        if (type == OptionType::Text)
        {
            string txt;
            for (auto v : values)
                txt += v + " ";
            IOptionType* newOption = new Text(name, abbr[0], type, txt.substr(0, txt.length() - 1));
            options[name].push_back(newOption);
        }
        else
        {
            for (auto v : values)
                switch(type)
                {
                    case OptionType::Boolean:
                    {
                        IOptionType* newOption = new Boolean(name, abbr[0], type, v);
                        options[name].push_back(newOption);
                        break;
                    }
                    case OptionType::Integer:
                    {
                        IOptionType* newOption = new Integer(name, abbr[0], type, v);
                        options[name].push_back(newOption);
                        break;
                    }
                    case OptionType::Real:
                    {
                        IOptionType* newOption = new Real(name, abbr[0], type, v);
                        options[name].push_back(newOption);
                        break;
                    }
                    case OptionType::Text:
                    {
                        /*IOptionType* newOption = new Text(name, abbr[0], type, v);
                        options[name].push_back(newOption);*/
                        break;
                    }
                }
        }
    }

    return true;
}

bool OptionParser::Validate()
{
    if (tokens.size() == 0)
        return false;

    return AnalyzeSyntax() && AnalyzeSemantic();
}

const string OptionParser::GetToken(size_t i)
{
    if (i < tokens.size())
        return tokens.at(i).first + ": " + tokens.at(i).second;
    else
        return "";
}

const map<string, vector<IOptionType*>> OptionParser::GetOptions() const
{
    return options;
}
