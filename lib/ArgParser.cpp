#include <vector>
#include "ArgParser.h"
#include <iostream>

void ArgumentParser::ArgParser::AssigmentAttribute(std::string keyForCheck, std::string value) {
    if (strKeyArgVal[keyForCheck].getType() == 's') {
        strKeyArgVal[keyForCheck].setAttributeForStringValue(value);
    } else if (strKeyArgVal[keyForCheck].getType() == 'i') {
        if (CheckInt(value)) {
            strKeyArgVal[keyForCheck].setAttributeForIntValue(std::stoi(value));
        }
    } else if (strKeyArgVal[keyForCheck].getType() == 'b') {
        strKeyArgVal[keyForCheck].setAttributeForBoolValue(true);
    } else if (strKeyArgVal[keyForCheck].getType() == 'h') {
        strKeyArgVal[keyForCheck].setAttributeForBoolValue(true);
    }
}

bool ArgumentParser::ArgParser::CheckInt(std::string value) {
    for (int i = 0; i < value.length(); ++i) {
        if (!isdigit(value[i])) {
            return false;
        }
    }
    return true;
}

void ArgumentParser::ArgParser::GenerateHelp(char shortName, std::string fullName, std::string description) {
    int sizeStr = 1 + fullName.size() + description.size() + 9;
    char *oneStrHelp = new char[sizeStr];
    sprintf(oneStrHelp, "-%c,  --%s,  %s\n", shortName, fullName.c_str(), description.c_str());
    helpWithParser.push_back(oneStrHelp);
}

bool ArgumentParser::ArgParser::Parse(std::vector<std::string> vector1) {
    std::string wordFromVector;
    int index_char;
    std::string keyFullForCheck;
    std::string value;
    for (int i = 1; i < vector1.size(); ++i) {
        wordFromVector = vector1[i];
        if (wordFromVector[0] == '-' && wordFromVector[1] == '-') {
            if (wordFromVector == "--help") {
                return true;
            }
            index_char = wordFromVector.find('=');
            if (index_char != std::string::npos) {
                keyFullForCheck = wordFromVector.substr(2, index_char - 2);
                value = wordFromVector.substr(index_char + 1, wordFromVector.length() - 1);
                if (strKeyArgVal.find(keyFullForCheck) != strKeyArgVal.end()) {
                    AssigmentAttribute(keyFullForCheck, value);
                }
            } else {
                if (strKeyArgVal.find(wordFromVector.substr(2, wordFromVector.length() - 1)) != strKeyArgVal.end()) {
                    AssigmentAttribute(wordFromVector.substr(2, wordFromVector.length() - 1), "");
                }
            }
        } else if (wordFromVector[0] == '-' && wordFromVector[1] != '-') {
            if (wordFromVector == "-h") {
                return true;
            }
            if (wordFromVector[2] == '=') {
                if (index_char != std::string::npos) {
                    value = wordFromVector.substr(3, wordFromVector.length() - 1);
                    if (strKeyArgVal.find(charKeyStrValue[wordFromVector[1]]) != strKeyArgVal.end()) {
                        AssigmentAttribute(charKeyStrValue[wordFromVector[1]], value);
                    }
                } else {
                    if (strKeyArgVal.find(charKeyStrValue[wordFromVector[1]]) != strKeyArgVal.end()) {
                        AssigmentAttribute(charKeyStrValue[wordFromVector[1]], "");
                    }
                }
            } else {
                for (int j = 1; j < wordFromVector.length(); ++j) {
                    AssigmentAttribute(charKeyStrValue[wordFromVector[j]], "");
                }
            }
        } else {
            for (auto &keyValue: strKeyArgVal) {
                if (keyValue.second.isPositional()) {
                    if (keyValue.second.getType() == 's') {
                        keyValue.second.setAttributeForStringValue(wordFromVector);
                    } else if (keyValue.second.getType() == 'i') {
                        if (CheckInt(wordFromVector)) {
                            keyValue.second.setAttributeForIntValue(std::stoi(wordFromVector));
                        }
                    }
                }
            }
        }
    }
    for (auto &keyValue: strKeyArgVal) {
        if (!keyValue.second.isDefault() && !keyValue.second.isUser()) {
            return false;
        }
        if (keyValue.second.isMultiValue()) {
            if (keyValue.second.getType() == 's' &&
                keyValue.second.getMultiString().size() < keyValue.second.getSizeVector()) {
                return false;
            } else if ((keyValue.second.getType() == 'i' &&
                        keyValue.second.getMultiInt().size() < keyValue.second.getSizeVector())) {
                return false;
            }
        }
    }
    return true;
}

bool ArgumentParser::ArgParser::Parse(int argc, char **argv) {
    return Parse(std::vector<std::string>(argv, argv + argc));
}

Argument::Arg &ArgumentParser::ArgParser::AddStringArgument(const char *fullName) {
    Argument::Arg arg;
    arg.setType('s');
    strKeyArgVal[fullName] = arg;
    GenerateHelp(' ', fullName, "");
    return strKeyArgVal[fullName];
}

Argument::Arg &ArgumentParser::ArgParser::AddStringArgument(char shortName, const char *fullName) {
    charKeyStrValue[shortName] = fullName;
    Argument::Arg arg;
    arg.setType('s');
    strKeyArgVal[fullName] = arg;
    GenerateHelp(shortName, fullName, "");
    return strKeyArgVal[fullName];
}

Argument::Arg &
ArgumentParser::ArgParser::AddStringArgument(char shortName, const char *fullName, const char *description) {
    charKeyStrValue[shortName] = fullName;
    Argument::Arg arg;
    arg.setType('s');
    strKeyArgVal[fullName] = arg;
    GenerateHelp(shortName, fullName, description);
    return strKeyArgVal[fullName];
}

std::string ArgumentParser::ArgParser::GetStringValue(const char *fullName) {
    return strKeyArgVal[fullName].getAttributeForStringValue();
}

Argument::Arg &ArgumentParser::ArgParser::AddIntArgument(const char *fullName) {
    Argument::Arg arg;
    arg.setType('i');
    strKeyArgVal[fullName] = arg;
    GenerateHelp(' ', fullName, "");
    return strKeyArgVal[fullName];
}

Argument::Arg &ArgumentParser::ArgParser::AddIntArgument(char shortName, const char *fullName) {
    charKeyStrValue[shortName] = fullName;
    Argument::Arg arg;
    arg.setType('i');
    strKeyArgVal[fullName] = arg;
    GenerateHelp(shortName, fullName, "");
    return strKeyArgVal[fullName];
}

Argument::Arg &ArgumentParser::ArgParser::AddIntArgument(const char *fullName, const char *description) {
    Argument::Arg arg;
    arg.setType('i');
    strKeyArgVal[fullName] = arg;
    GenerateHelp(' ', fullName, description);
    return strKeyArgVal[fullName];
}

int ArgumentParser::ArgParser::GetIntValue(const char *fullName) {
    return strKeyArgVal[fullName].getAttributeForIntValue();
}

int ArgumentParser::ArgParser::GetIntValue(const char *fullName, int index) {
    if (strKeyArgVal[fullName].isMultiValue()) {
        return strKeyArgVal[fullName].getMultiInt()[index];
    }
    return 0;
}

Argument::Arg &ArgumentParser::ArgParser::AddFlag(char shortName, const char *fullName) {
    charKeyStrValue[shortName] = fullName;
    Argument::Arg arg;
    arg.setType('b');
    strKeyArgVal[fullName] = arg;
    GenerateHelp(shortName, fullName, "");
    return strKeyArgVal[fullName];
}

Argument::Arg &ArgumentParser::ArgParser::AddFlag(char shortName, const char *fullName, const char *description) {
    charKeyStrValue[shortName] = fullName;
    Argument::Arg arg;
    arg.setType('b');
    strKeyArgVal[fullName] = arg;
    GenerateHelp(shortName, fullName, description);
    return strKeyArgVal[fullName];
}

Argument::Arg &ArgumentParser::ArgParser::AddFlag(const char *fullName, const char *description) {
    Argument::Arg arg;
    arg.setType('b');
    strKeyArgVal[fullName] = arg;
    GenerateHelp(' ', fullName, description);
    return strKeyArgVal[fullName];
}

bool ArgumentParser::ArgParser::GetFlag(const char *fullName) {
    return strKeyArgVal[fullName].isAttributeForBoolValue();
}

void ArgumentParser::ArgParser::AddHelp(char shortName, const char *fullName, const char *description) {
    charKeyStrValue[shortName] = fullName;
    Argument::Arg arg;
    arg.setType('h');
    strKeyArgVal[fullName] = arg;
    GenerateHelp(shortName, fullName, description);
}

bool ArgumentParser::ArgParser::Help() {
    for (auto &keyValue: strKeyArgVal) {
        if (keyValue.second.isAttributeForBoolValue() && keyValue.second.getType() == 'h') {
            return true;
        }
    }
    return false;
}

void ArgumentParser::ArgParser::HelpDescription() {
    if (Help()) {
        for (int i = 0; i < helpWithParser.size(); ++i) {
            std::cout << helpWithParser[i];
        }
    } else {
        std::cout << "Error. Empty";
    }
}

