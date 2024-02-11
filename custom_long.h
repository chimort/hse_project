#include <iostream>
#include <string>
#include <tuple>

class custom_long
{
private:
    std::string integer;
    std::string fraction;

    std::string cut(std::string& num1);
    bool frac_compare(std::string num1, std::string num2);
    bool int_compare(std::string num1, std::string num2);
    std::tuple<int, int> get_sizes(const std::string& num1, const std::string& num2);

public:
    custom_long(std::string integer, std::string fraction);
    
    inline friend std::ostream& operator<<(std::ostream& os, const custom_long& cl) {
        return os << cl.integer + "." + cl.fraction;
    }
    bool operator==(const custom_long& other);
    bool operator!=(const custom_long& other);
    bool operator<(const custom_long& other);
    bool operator>(const custom_long& other);
    custom_long operator+(const custom_long& other);
    custom_long operator-(const custom_long& other);
    custom_long operator*(const custom_long& other);
    custom_long operator/(const custom_long& other);

    std::string add(const std::string& num1, const std::string& num2, bool is_frac, int& extra);
    std::string subtract(const std::string& num1, const std::string& num2, bool is_frac);
};