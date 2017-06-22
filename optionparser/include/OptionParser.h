#ifndef OPTIONPARSER_H
#define OPTIONPARSER_H

#include <iostream>
#include <string>
#include <vector>
#include <utility>
#include <algorithm>
#include <map>

#include "OptionDefinition.h"
#include "IOptionType.h"
#include "Boolean.h"
#include "Integer.h"
#include "Real.h"
#include "Text.h"
#include "../exceptions/SyntaxException.h"
#include "../exceptions/DefinitionException.h"

using namespace std;

class OptionParser
{
    string tokenOption;
    string tokenValue;
    bool addList = false;

    vector<OptionDefinition> definitions;
    vector<pair<string, string>> tokens;
    map<string, vector<IOptionType*>> options;

    void AddDefinition(const char* name, char abbr, OptionType type, bool optional);
    string isOption(const string &token);
    string isValue(const string &token);
    bool AnalyzeSyntax();
    bool AnalyzeSemantic();

    public:
        OptionParser(int argc, const char** args);
        virtual ~OptionParser();
        void AddInteger(const char* name, char abbr, bool optional = false);
        void AddReal(const char* name, char abbr, bool optional = false);
        void AddBoolean(const char* name, char abbr, bool optional = true);
        void AddText(const char* name, char abbr, bool optional = false);
        bool Validate();

        const string GetToken(size_t i);
        const map<string, vector<IOptionType*>> GetOptions() const;
};

#endif // OPTIONPARSER_H
//
