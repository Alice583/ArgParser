#include "string"
#include "vector"
#include "iostream"

namespace Argument {
    class Arg {
    private:
        char type;

        bool is_multi_value = false;
        bool is_positional = false;
        bool is_storeValue = false;
        bool is_default = false;
        bool is_user = false;

        int *linkOnInt = nullptr;
        std::string *linkOnStr = nullptr;
        bool *linkOnBool = nullptr;
        std::vector<std::string> *linkMultiStrings = nullptr;
        std::vector<int> *linkMultiInt = nullptr;

        int attributeForIntValue;
        std::string attributeForStringValue = "";
        bool attributeForBoolValue;

        size_t size_vector = 0;
        std::vector<std::string> multiString;
        std::vector<int> multiInt;

    public:

        void setType(char type);

        void setAttributeForIntValue(int attributeForIntValue);

        void setAttributeForStringValue(const std::string &attributeForStringValue);

        void setAttributeForBoolValue(bool attributeForBoolValue);

        bool isMultiValue() const;

        bool isPositional() const;

        int *getLinkOnInt() const;

        const std::vector<std::string> &getMultiString() const;

        const std::vector<int> &getMultiInt() const;

        int getAttributeForIntValue() const;

        const std::string &getAttributeForStringValue() const;

        int getSizeVector() const;

        char getType() const;

        bool isAttributeForBoolValue() const;

        bool isDefault() const;

        bool isUser() const;

        Argument::Arg &Default(const char *string);

        Argument::Arg &Default(bool i);

        Argument::Arg &StoreValue(std::string &basicString);

        Argument::Arg &StoreValue(int &arg);

        Argument::Arg &StoreValue(bool &flag);

        Argument::Arg &MultiValue();

        Argument::Arg &MultiValue(int size);

        Argument::Arg &StoreValues(std::vector<int> &vector1);

        Argument::Arg &StoreValues(std::vector<std::string> &vector1);

        Argument::Arg &Positional();
    };
}