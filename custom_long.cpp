#include "custom_long.h"
#include <stdio.h>
#include <string>
#include <cmath>
#include <algorithm>

custom_long::custom_long(std::string integer, std::string fraction)
{
    this->integer = integer;
    this->fraction = cut(fraction);
    integer[0] == '-' ? this->sign = true : this->sign = false;
    this->precision = 10;
}

std::string custom_long::cut(std::string& num1)
{
    int size1 = num1.size();
    int i = size1 - 1;
    while(num1[i] == '0' && i > 0) {
        num1.pop_back();
        i--;
    }
    return num1;
}

std::tuple<int, int> custom_long::get_sizes(const std::string& num1, const std::string& num2)
{
    return std::make_tuple(num1.size(), num2.size());
}

void custom_long::check_sign(custom_long& number)
{
    if (number.integer[0] == '-') {
        this->sign = true;
        number.integer.erase(number.integer.begin());
    }
}


bool custom_long::int_compare(std::string num1, std::string num2)
{
    auto [size1, size2] = get_sizes(num1, num2);

    if (size1 < size2) {
        return true;
    } else if (size1 > size2) {
        return false;
    } else {
        for (int i = 0; i < size1; i++) {
            if (num1[i] - '0' < num2[i] - '0') {
                return true;
            } else if (num1[i] - '0' > num2[i] - '0') {
                return false;
            }
        }
        return false;
    }
}

bool custom_long::frac_compare(std::string num1, std::string num2)
{
    auto [size1, size2] = get_sizes(num1, num2);
    int max_size = std::max(size1, size2);

    for (int i = 0; i < max_size; i++) {
        if (i > size1 - 1 && i < size2 - 1) {
            return false;
        } else if (i < size1 - 1 && i > size2 - 1){
            return true;
        }
        if (num1[i] - '0' < num2[i] - '0') {
            return true;
        } else if (num1[i] - '0' > num2[i] - '0') {
            return false;
        }
    }
    return false;
}

bool custom_long::operator==(const custom_long& other)
{
    auto [size_int1, size_int2] = get_sizes(integer, other.integer);
    auto [size_frac1, size_frac2] = get_sizes(fraction, other.fraction);

    if (size_int1 != size_int2 || size_frac1 != size_frac2) {
        return false;
    }
    for (int i = 0; i < size_int1; i++) {
        if (integer[i] != other.integer[i]) {
            return false;
        }
    }
    for (int i = 0; i < size_frac1; i++) {
        if (fraction[i] != other.fraction[i]) {
            return false;
        }
    }
    return true;
}

bool custom_long::operator!=(const custom_long& other)
{
    return !(*this == other);
}

bool custom_long::operator<(const custom_long& other)
{   
    if (int_compare(integer, other.integer)) {
        return (this->sign == other.sign) || (this->sign && !other.sign);
    } else if (int_compare(other.integer, integer)) {
        return !(this->sign == other.sign) || (this->sign && !other.sign);
    } else {
        return (*this != other) && ((this->sign == other.sign) ? frac_compare(fraction, other.fraction) : !frac_compare(fraction, other.fraction));
    }
}

bool custom_long::operator>(const custom_long& other)
{
    return (*this == other) ? false : !(*this < other);
}

custom_long custom_long::add(custom_long& num1, custom_long& num2)
{
    if (num1.sign && !num2.sign) {
        return subtract(num2, num1);
    }

    if (!num1.sign && num2.sign) {
        return subtract(num1, num2);
    }

    custom_long res = {"0", "0"};
    int carry = 0;
    auto [size1, size2] = get_sizes(num1.fraction, num2.fraction);
    int max_size = std::max(size1, size2);

    auto [int_size1, int_size2] = get_sizes(num1.integer, num2.integer);
    int max_int_size = std::max(int_size1, int_size2);


    int min_len = std::min(size1, size2);
    int j = 0;
    int i = 0;

    if (size1 < size2) {
        std::swap(num1.fraction, num2.fraction);

        std::swap(size1, size2);
    }

    while (i < max_size) {
        int digit1 = 0;
        int digit2 = 0;

        if (max_size - 1 - i > min_len - 1) {
            digit1 = num1.fraction[size1 - 1 - i] - '0';
        }else {
            digit1 = num1.fraction[size1 - 1 - i] - '0';
            digit2 = num2.fraction[size2 - 1 - j] - '0';
            j++;
        }
        int sum = digit1 + digit2 + carry;

        carry = sum / 10;
        sum %= 10;
        res.fraction.push_back(sum + '0');
        i++;
    }

    std::reverse(res.fraction.begin(), res.fraction.end());
    cut(res.fraction);

    for (int i = 0; i < max_int_size || carry; i++) {
        int digit1 = i < int_size1 ? num1.integer[int_size1 - 1 - i] - '0' : 0;
        int digit2 = i < int_size2 ? num2.integer[int_size2 - 1 - i] - '0' : 0;

        int sum = digit1 + digit2 + carry;

        carry = sum / 10;
        sum %= 10;
        res.integer.push_back(sum + '0');
    }

    std::reverse(res.integer.begin(), res.integer.end());
    res.integer.pop_back();
    return res;
}

custom_long custom_long::operator+(custom_long& other)
{
    return add(*this, other);
}

custom_long custom_long::subtract(custom_long& num1, custom_long& num2)
{
    int carry = 0;
    bool extra = false;
    custom_long res = {"0", "0"};

    auto [size1, size2] = get_sizes(num1.fraction, num2.fraction);
    int max_size = std::max(size1, size2);

    if (num1 > num2) {
        res.sign = false;
    } else if (num1 < num2){
        std::swap(num1, num2);
        res.sign = true;
    } else {
        res.sign = false;
        return res;
    }

    if (size1 < max_size) {
        num1.fraction.append(max_size - size1, '0');
    }

    if (size2 < max_size) {
        num2.fraction.append(max_size - size2, '0');
    }

    for (int i = max_size - 1; i >= 0; i--) {
        int digit1 = (i < size1) ? num1.fraction[i] - '0' : 0;
        int digit2 = (i < size2) ? num2.fraction[i] - '0' : 0;

        int diff = digit1 - digit2 - carry;
        carry = 0;

        if (diff < 0) {
            diff += 10;
            carry = 1;
        }
        res.fraction.push_back(diff + '0');
    }

    std::reverse(res.fraction.begin(), res.fraction.end());
    cut(res.fraction);

    auto [int_size1, int_size2] = get_sizes(num1.integer, num2.integer);
    int max_int_size = std::max(int_size1, int_size2);

    if (int_size1 < max_int_size) {
        num1.integer.insert(0, max_int_size - int_size1, '0');
    }

    if (int_size2 < max_int_size) {
        num2.integer.insert(0, max_int_size - int_size2, '0');
    }

    for (int i = int_size1 - 1; i >= 0; i--) {
        int diff = num1.integer[i] - num2.integer[i] - carry;
        carry = 0;
        if (diff < 0) {
            diff += 10;
            carry = 1;
            extra = true;
        }else {
            extra = false;
        }
        res.integer.push_back(diff + '0');
    }

    cut(res.integer);
    std::reverse(res.integer.begin(), res.integer.end());
    cut(res.integer);

    return res;
}

custom_long custom_long::operator-(custom_long& other)
{
    return subtract(*this, other);
}

custom_long custom_long::operator*(const custom_long& other)
{   
    custom_long res("0", "0");
    

    return res;
}

custom_long custom_long::operator/(const custom_long& other)
{
    return custom_long("0", "0");
}

std::ostream &operator<<(std::ostream &os, const custom_long &cl)
{
    if (cl.precision > 0) {
        if (!cl.sign) {
            return os << cl.integer + "." + cl.fraction.substr(0, cl.precision);
        } else {
            return os << "-" << cl.integer + "." + cl.fraction.substr(0, cl.precision);
        }
    } else {
        if (!cl.sign) {
            return os << cl.integer; 
        } else {
            return os << "-" << cl.integer;
        }
    }
}
