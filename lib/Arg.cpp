#include "Arg.h"

Argument::Arg& Argument::Arg::Default(const char* string) {
    is_default = true;
    attributeForStringValue = string;
    return* this;
}

Argument::Arg& Argument::Arg::Default(bool i) {
    is_default = true;
    attributeForBoolValue = i;
    return* this;
}

Argument::Arg& Argument::Arg::StoreValue(std::string& basicString) {
    linkOnStr = &basicString;
    is_storeValue = true;
    return* this;
}

Argument::Arg& Argument::Arg::StoreValue(int& arg) {
    linkOnInt = &arg;
    is_storeValue = true;
    return* this;
}

Argument::Arg& Argument::Arg::StoreValue(bool& flag) {
    is_storeValue = true;
    linkOnBool = &flag;
    return* this;
}

Argument::Arg& Argument::Arg::MultiValue() {
    is_multi_value = true;
    return* this;
}

Argument::Arg& Argument::Arg::MultiValue(int size) {
    size_vector = size;
    is_multi_value = true;
    return* this;
}

Argument::Arg& Argument::Arg::StoreValues(std::vector<int>& vector1) {
    is_storeValue = true;
    linkMultiInt = &vector1;
    return* this;
}

Argument::Arg& Argument::Arg::StoreValues(std::vector<std::string>& vector1) {
    is_storeValue = true;
    linkMultiStrings = &vector1;
    return* this;
}

Argument::Arg& Argument::Arg::Positional() {
    is_positional = true;
    return* this;
}

void Argument::Arg::setType(char type) {
    Arg::type = type;
}

void Argument::Arg::setAttributeForIntValue(int attributeForIntValue) {
    is_user = true;
    if (is_storeValue && linkOnInt != nullptr) {
        *linkOnInt = attributeForIntValue;
    }
    if (is_multi_value) {
        if (is_storeValue && linkMultiInt != nullptr) {
            linkMultiInt->push_back(attributeForIntValue);
        }
        multiInt.push_back(attributeForIntValue);
    } else {
        Arg::attributeForIntValue = attributeForIntValue;
    }
}

void Argument::Arg::setAttributeForStringValue(const std::string& attributeForStringValue) {
    is_user = true;
    if (is_storeValue && linkOnStr != nullptr) {
        *linkOnStr = attributeForStringValue;
    }
    if (is_multi_value) {
        if (is_storeValue && linkMultiStrings != nullptr) {
            linkMultiStrings->push_back(attributeForStringValue);
        }
        multiString.push_back(attributeForStringValue);
    } else {
        Arg::attributeForStringValue = attributeForStringValue;
    }
}

void Argument::Arg::setAttributeForBoolValue(bool attributeForBoolValue) {
    if (is_storeValue && linkOnBool != nullptr) {
        *linkOnBool = attributeForBoolValue;
    }
    is_user = true;
    Arg::attributeForBoolValue = attributeForBoolValue;
}

bool Argument::Arg::isMultiValue() const {
    return is_multi_value;
}

bool Argument::Arg::isPositional() const {
    return is_positional;
}

int* Argument::Arg::getLinkOnInt() const {
    return linkOnInt;
}

const std::vector<std::string>& Argument::Arg::getMultiString() const {
    return multiString;
}

const std::vector<int>& Argument::Arg::getMultiInt() const {
    return multiInt;
}

int Argument::Arg::getAttributeForIntValue() const {
    return attributeForIntValue;
}

const std::string& Argument::Arg::getAttributeForStringValue() const {
    return attributeForStringValue;
}

int Argument::Arg::getSizeVector() const {
    return size_vector;
}

char Argument::Arg::getType() const {
    return type;
}

bool Argument::Arg::isAttributeForBoolValue() const {
    return attributeForBoolValue;
}

bool Argument::Arg::isDefault() const {
    return is_default;
}

bool Argument::Arg::isUser() const {
    return is_user;
}
