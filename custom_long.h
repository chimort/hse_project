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
    custom_long operator+(const custom_long& other);
    custom_long operator-(const custom_long& other);
    custom_long operator*(const custom_long& other);
    custom_long operator/(const custom_long& other);
};