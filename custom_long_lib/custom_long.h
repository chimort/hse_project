#include <iostream>
#include <string>
#include <tuple>

class custom_long
{
private:
    std::string integer;
    std::string fraction;
    bool sign = false;
    int precision;

    std::string cut(std::string& num1);
    custom_long add(custom_long& num1, custom_long& num2);
    custom_long subtract(custom_long& num1, custom_long& num2);

    bool frac_compare(std::string num1, std::string num2);
    bool int_compare(std::string num1, std::string num2);
    std::tuple<int, int> get_sizes(const std::string& num1, const std::string& num2);

public:
    custom_long(std::string integer, std::string fraction);
    custom_long(int number);
    custom_long(double number);
    custom_long(std::string number);
    
    friend std::ostream& operator<<(std::ostream& os, const custom_long& cl);
    bool operator==(const custom_long& other);
    bool operator!=(const custom_long& other);
    bool operator<(const custom_long& other);
    bool operator>(const custom_long& other);
    custom_long operator+(custom_long& other);
    custom_long operator-(custom_long& other);
    custom_long operator*(const custom_long& other);
    custom_long operator/(const custom_long& other);

    inline custom_long new_with_precision(int acc) { 
        return custom_long(this->integer, this->fraction.substr(0, acc));
    }
};