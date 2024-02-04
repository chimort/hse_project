#include "custom_long.h"
#include <stdio.h>
#include <string>
#include <cmath>


custom_long custom_long::operator+(const custom_long& other)
{
    std::string resINT = std::to_string(std::stoll(integer) + std::stoll(other.integer));
    std::string resFRAC = std::to_string(std::stoll(fraction) + std::stoll(other.fraction));

    // int64_t num_frac = std::stoll(resFRAC);
    // int64_t ord = pow(10, resFRAC.size() - 1);
    

    return custom_long(resINT, resFRAC);
}

custom_long custom_long::operator-(const custom_long& other)
{
    return custom_long("0", "0");
}

custom_long custom_long::operator*(const custom_long& other)
{
    return custom_long("0", "0");
}

custom_long custom_long::operator/(const custom_long& other)
{
    return custom_long("0", "0");
}
