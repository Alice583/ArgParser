#pragma once

#include "string"
#include "vector"
#include "map"
#include "Arg.h"

namespace ArgumentParser {

    class ArgParser {
    private:
        std::map<char, std::string> shortKeyFullNameValue;
        std::map<std::string, Argument::Arg> fullNameKeyArgValue;
        std::vector<std::string> helpWithParser;
        std::string nameProgram;
    public:
        ArgParser(const std::string& name) {
            nameProgram = name;
            helpWithParser.push_back(nameProgram + '\n');
        }

        void AssigmentAttribute(std::string keyForCheck, std::string value);

        bool CheckInt(std::string value);

        void GenerateHelp(const char& shortName, const std::string& fullName, const std::string& description);

        bool Parse(const std::vector<std::string>& vector1);

        bool Parse(int argc, char** argv);

        Argument::Arg& AddStringArgument(const char* fullName);

        Argument::Arg& AddStringArgument(char shortName, const char* fullName);

        Argument::Arg& AddStringArgument(char shortName, const char* fullName, const char* description);

        std::string GetStringValue(const char* fullName);

        Argument::Arg& AddIntArgument(const char* string);

        Argument::Arg& AddIntArgument(char i, const char* string);

        Argument::Arg& AddIntArgument(const char* fullName, const char* string2);

        int GetIntValue(const char* string);

        int GetIntValue(const char* fullName, int index);

        Argument::Arg& AddFlag(char i, const char* string);

        Argument::Arg& AddFlag(char i, const char* string1, const char* string2);

        Argument::Arg& AddFlag(const char* string1, const char* string2);

        bool GetFlag(const char* string);

        void AddHelp(char shortName, const char* fullName, const char* description);

        bool Help();

        void HelpDescription();
    };

}
