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
    custom_long add(const custom_long& num1, const custom_long& num2, bool side, bool unexpected);
    custom_long subtract(const custom_long& num1, const custom_long& num2, bool side, bool unexpected);

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
    custom_long operator+(const custom_long& other);
    custom_long operator-(const custom_long& other);
    custom_long operator*(const custom_long& other);
    custom_long operator/(const custom_long& other);

    custom_long set_precision(int acc);
};

custom_long operator ""_cl(const char *str, size_t size);