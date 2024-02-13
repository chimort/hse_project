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
    std::string add(const std::string& num1, const std::string& num2, bool is_frac, int& extra);
    custom_long subtract(custom_long& num1, custom_long& num2);

    bool frac_compare(std::string num1, std::string num2);
    bool int_compare(std::string num1, std::string num2);
    void check_sign(custom_long& num);
    std::tuple<int, int> get_sizes(const std::string& num1, const std::string& num2);

public:
    custom_long(std::string integer, std::string fraction);
    
    friend std::ostream& operator<<(std::ostream& os, const custom_long& cl);
    bool operator==(const custom_long& other);
    bool operator!=(const custom_long& other);
    bool operator<(const custom_long& other);
    bool operator>(const custom_long& other);
    custom_long operator+(const custom_long& other);
    custom_long operator-(custom_long& other);
    custom_long operator*(const custom_long& other);
    custom_long operator/(const custom_long& other);

    inline custom_long set_precision(int acc) { this->precision = acc; return *this; }
};