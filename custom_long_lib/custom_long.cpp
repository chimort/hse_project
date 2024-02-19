#include "custom_long.h"
#include <stdio.h>
#include <string>
#include <cmath>
#include <algorithm>

custom_long::custom_long(std::string integer, std::string fraction)
{
    this->integer = integer;
    this->fraction = cut(fraction);
    if (integer[0] == '-') {
        this->sign = true;
        this->integer.erase(this->integer.begin());
    }
    this->precision = fraction.size();
}

custom_long::custom_long(int number)
{
    if (number < 0) {
        this->sign = true;
        number = -number;
    } else {
        this->sign = false;
    }
    this->integer = std::to_string(number);
    this->fraction = "0";
    this->precision = 1;
}

custom_long::custom_long(double number) {
    if (number < 0) {
        this->sign = true;
        number = -number;
    } else {
        this->sign = false;
    }
    std::string new_num = std::to_string(number);

    size_t dot_pos = new_num.find('.');

    this->integer = new_num.substr(0, dot_pos);

    this->fraction = new_num.substr(dot_pos + 1);
    this->precision = this->fraction.size();
}

custom_long::custom_long(std::string number) {
    size_t dot_pos = number.find('.');

    if (number[0] == '-') {
        this->sign = true;
        number.erase(number.begin());
    } else {
        this->sign = false;
    }

    if (dot_pos != std::string::npos) {
        this->integer = number.substr(0, dot_pos);
        this->fraction = number.substr(dot_pos + 1);
        this->precision = this->fraction.empty() ? 0 : this->fraction.size();
    } else {
        this->integer = number;
        this->fraction = "0";
        this->precision = 1;
    }
}

custom_long custom_long::set_precision(int acc)
{
    custom_long res = {this->integer, this->fraction.substr(0, acc)};
    res.sign = this->sign;
    return res;
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
        if (i >= size1 && i < size2) {
            return true;  // num1 короче, считаем его меньшим
        } else if (i < size1 && i >= size2) {
            return false;  // num2 короче, считаем его меньшим
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
    if (this->precision != other.precision) {
        return false;
    }
    return (this->integer == other.integer) && (this->fraction == other.fraction);
}

bool custom_long::operator!=(const custom_long& other)
{
    return !(*this == other);
}

bool custom_long::operator<(const custom_long& other)
{   
    if (this->sign && !other.sign) {
        return true;
    } else if (!this->sign && other.sign) {
        return false;
    } else if (this->sign && other.sign) {
        if (int_compare(other.integer, integer)) {
            return true;
        } else if (int_compare(integer, other.integer)) {
            return false;
        } else {
            return frac_compare(other.fraction, fraction);
        }
    } else {
        if (int_compare(integer, other.integer)) {
            return true;
        } else if (int_compare(other.integer, integer)) {
            return false;
        } else {
            return frac_compare(fraction, other.fraction);
        }
    }
}

bool custom_long::operator>(const custom_long& other)
{
    return (*this == other) ? false : !(*this < other);
}

custom_long custom_long::add(const custom_long& num1, const custom_long& num2, bool side, bool unexpected)
{
    bool sgn = true;
    if (num1.integer < num2.integer) {
        sgn = false;
    } else if (num1.integer == num2.integer){
        if (num1.fraction < num2.fraction) {
            sgn = false;
        }
    }
    if (!side) {
        if (num1.sign && !num2.sign) {
            return subtract(num2, num1, true, sgn);
        }

        if (!num1.sign && num2.sign) {
            return subtract(num1, num2, true, sgn);
        }
    }

    auto [size_int1, size_int2] = get_sizes(num1.integer, num2.integer);
    size_t max_int_size = std::max(size_int1, size_int2);

    std::string temp_int_num1 = std::string(max_int_size - size_int1, '0') + num1.integer;
    std::string temp_int_num2 = std::string(max_int_size - size_int2, '0') + num2.integer;

    auto [size_frac1, size_frac2] = get_sizes(num1.fraction, num2.fraction);
    size_t max_frac_size = std::max(size_frac1, size_frac2);

    std::string temp_frac_num1 = num1.fraction + std::string(max_frac_size - size_frac1, '0');
    std::string temp_frac_num2 = num2.fraction + std::string(max_frac_size - size_frac2, '0');

    int carry = 0;

    std::string frac_res;

    for (int i = max_frac_size - 1; i >= 0; i--) {
        int digit1 = temp_frac_num1[i] - '0';
        int digit2 = temp_frac_num2[i] - '0';

        int res = digit1 + digit2 + carry;

        frac_res.push_back(res % 10 + '0');
        carry = res / 10;
    }

    std::reverse(frac_res.begin(), frac_res.end());

    std::string int_res;

    for (int i = max_int_size - 1; i >= 0; i--) {
        int digit1 = temp_int_num1[i] - '0';
        int digit2 = temp_int_num2[i] - '0';

        int res = digit1 + digit2 + carry;

        int_res.push_back(res % 10 + '0');
        carry = res / 10;
    }

    if (carry > 0) {
        int_res.push_back(carry + '0');
    }

    std::reverse(int_res.begin(), int_res.end());

    custom_long res = {int_res, frac_res};
    res.sign = unexpected;
    return res;
}

custom_long custom_long::operator+(const custom_long& other)
{   
    return add(*this, other, false, false);
}

custom_long custom_long::subtract(const custom_long& num1, const custom_long& num2, bool side, bool unexpected)
{
    bool sgn = false;

    if (!side) {
        if (num1.sign && !num2.sign) {
            return add(num2, num1, true, true);
        }

        if (!num1.sign && num2.sign) {
            return add(num1, num2, true, false);
        }
    }
    
    auto [size_int1, size_int2] = get_sizes(num1.integer, num2.integer);
    size_t max_int_size = std::max(size_int1, size_int2);

    std::string temp_int_num1 = std::string(max_int_size - size_int1, '0') + num1.integer;
    std::string temp_int_num2 = std::string(max_int_size - size_int2, '0') + num2.integer;


    auto [size_frac1, size_frac2] = get_sizes(num1.fraction, num2.fraction);
    size_t max_frac_size = std::max(size_frac1, size_frac2);

    std::string temp_frac_num1 = num1.fraction + std::string(max_frac_size - size_frac1, '0');
    std::string temp_frac_num2 = num2.fraction + std::string(max_frac_size - size_frac2, '0');

    if (temp_int_num1 < temp_int_num2) {
        std::swap(temp_int_num1, temp_int_num2);
        std::swap(temp_frac_num1, temp_frac_num2);
        sgn = true;
    } else if (temp_int_num1 == temp_int_num2){
        if (temp_frac_num1 < temp_frac_num2) {
            std::swap(temp_int_num1, temp_int_num2);
            std::swap(temp_frac_num1, temp_frac_num2);
            sgn = true;
        }
    }
    
    int borrow = 0;

    std::string frac_res;

    for (int i = max_frac_size - 1; i >= 0; i--) {
        int digit1 = temp_frac_num1[i] - '0';
        int digit2 = temp_frac_num2[i] - '0';
        
        int res = digit1 - digit2 - borrow;
        if (res < 0) {
            res += 10;
            borrow = 1;
        } else {
            borrow = 0;
        }
        frac_res.push_back(res + '0');   
    }

    std::reverse(frac_res.begin(), frac_res.end());
    cut(frac_res);

    std::string int_res;

    for (int i = max_int_size - 1; i >= 0; i--) {
        int digit1 = temp_int_num1[i] - '0';
        int digit2 = temp_int_num2[i] - '0';
        
        int res = digit1 - digit2 - borrow;
        if (res < 0) {
            res += 10;
            borrow = 1;
        } else {
            borrow = 0;
        }
        int_res.push_back(res + '0');
    }
    cut(int_res);
    std::reverse(int_res.begin(), int_res.end());
    custom_long res = {int_res, frac_res};
    res.sign = sgn;
    return res;
}

custom_long custom_long::operator-(const custom_long& other)
{ 
    return subtract(*this, other, false, false);
}

custom_long custom_long::multiply(const custom_long& num1, const custom_long& num2)
{   
    if ((num1.integer == "0" && num1.fraction == "0") || (num2.integer == "0" && num2.fraction == "0")) {
        return {"0", "0"};
    }

    bool sgn = num1.sign ^ num2.sign;

    std::string temp1 = num1.integer + num1.fraction;
    size_t dot_pos1 = num1.fraction.size();

    std::string temp2 = num2.integer + num2.fraction;
    size_t dot_pos2 = num2.fraction.size();

    size_t res_dot_pos = dot_pos1 + dot_pos2;

    auto [size1, size2] = get_sizes(temp1, temp2);

    std::string result_string(size1 + size2, '0');
    for (int i = size1 - 1; i >= 0; i--) {
            int carry = 0;
            for (int j = size2 - 1; j >= 0; j--) {
                int product = (temp1[i] - '0') * (temp2[j] - '0') + (result_string[i + j + 1] - '0') + carry;
                carry = product / 10;
                result_string[i + j + 1] = (product % 10) + '0';
            }
            result_string[i] += carry;
        }

    if (num1.integer == "0" && num2.integer == "0") {
        custom_long res = {"0", result_string.erase(0, 2)};
        res.sign = sgn;
        return res;
    }

    int idx = 0;
    while (idx < res_dot_pos && result_string[idx] == '0') {
        result_string.erase(idx, 1);
    }
    res_dot_pos = result_string.size() - res_dot_pos;
    custom_long res = {result_string.substr(0, res_dot_pos), result_string.substr(res_dot_pos, result_string.size())};
    res.sign = sgn;
    return res;
}

custom_long custom_long::operator*(const custom_long& other)
{   
    return multiply(*this, other);
}

custom_long custom_long::div(custom_long num1, custom_long num2)
{
    bool sgn = num1.sign ^ num2.sign;
    custom_long int_part = "0"_cl;
    std::string dividend = num1.integer + num1.fraction;
    std::string divisor = num2.integer + num2.fraction;

    int max_precision = std::max(num1.precision, num2.precision);
    int prec1 = num1.precision;
    int prec2 = num2.precision;

    dividend += std::string(max_precision - num1.precision, '0');
    divisor += std::string(max_precision - num2.precision, '0');

    custom_long temp_div = {dividend, "0"};
    custom_long temp_sor = {divisor, "0"};

    while ((temp_div > temp_sor) || (temp_div == temp_sor)) {
        temp_div = subtract(temp_div, temp_sor, false, false);
        int_part = add(int_part, "1"_cl, false, false);
    };

    std::string frac_part = "0";
    int precision_count = 0;
    while (precision_count <= max_precision * 2 + 1) {
        temp_div.integer += "0";
        custom_long temp = "0"_cl;

        while ((temp_div > temp_sor) || (temp_div == temp_sor)) {
            temp_div = subtract(temp_div, temp_sor, false, false);
            temp = add(temp, "1"_cl, false, false);
        }

        frac_part += temp.integer;
        precision_count++;
    }
    frac_part.erase(0, 1);
    custom_long res = {int_part.integer, frac_part};
    res.sign = sgn;
    return res;
}

custom_long custom_long::operator/(const custom_long& other)
{
    *this = div(*this, other);
    return *this;
}

custom_long operator ""_cl(const char *str, size_t size)
{
    return custom_long(str);
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
