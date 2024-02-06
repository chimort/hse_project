#include <iostream>
#include <string>

class custom_long
{
private:
    std::string integer;
    std::string fraction;
public:
    inline custom_long(std::string integer, std::string fraction) : integer(integer), fraction(fraction) {}
    inline friend std::ostream& operator<<(std::ostream& os, const custom_long& cl) {
         return os << cl.integer + "." + cl.fraction ;
    }
    friend bool operator==(const custom_long& num1, const custom_long& num2);
    friend bool operator<(const custom_long& num1, const custom_long& num2);
    friend bool operator>(const custom_long& num1, const custom_long& num2);
    std::string add(const std::string& num1, const std::string& num2, bool is_frac);
    std::string subtract(const std::string& num1, const std::string& num2, bool is_frac);
    custom_long operator+(const custom_long& other);
    custom_long operator-(const custom_long& other);
    custom_long operator*(const custom_long& other);
    custom_long operator/(const custom_long& other);
};