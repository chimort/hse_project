#include "custom_long.h"
#include <stdio.h>
#include <string>
#include <cmath>
#include <algorithm>

custom_long::custom_long(std::string integer, std::string fraction)
{
    this->integer = integer;
    this->fraction = cut(fraction);
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

//Добавить проверку на то является ли число отрицательным
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
        return true;
    } else if (int_compare(other.integer, integer)){
        return false;
    } else {
        return (*this == other) ? false : frac_compare(fraction, other.fraction);
    }
}

bool custom_long::operator>(const custom_long& other)
{
    return (*this == other) ? false : !(*this < other);
}

std::string custom_long::add(const std::string& num1, const std::string& num2, bool is_frac, int& extra)
{
    std::string res;
    int carry = 0;

    auto [size1, size2] = get_sizes(num1, num2);
    int max_size = std::max(size1, size2);

    if (is_frac) {
        int min_len = std::min(size1, size2);
        int j = 0;
        int i = 0;
        
        std::string new_num1 = num1;
        std::string new_num2 = num2;

        if (size1 < size2) {
            std::swap(new_num1, new_num2);

            std::swap(size1, size2);
        }

        while (i < max_size) {
            int digit1 = 0;
            int digit2 = 0;

            if (max_size - 1 - i > min_len - 1) {
                digit1 = new_num1[size1 - 1 - i] - '0';
            }else {
                digit1 = new_num1[size1 - 1 - i] - '0';
                digit2 = new_num2[size2 - 1 - j] - '0';
                j++;
            }
            int sum = digit1 + digit2 + carry;

            carry = sum / 10;
            sum %= 10;
            res.push_back(sum + '0');
            i++;
        }
    } else {
        for (int i = 0; i < max_size || carry; i++) {
            int digit1 = i < size1 ? num1[size1 - 1 - i] - '0' : 0;
            int digit2 = i < size2 ? num2[size2 - 1 - i] - '0' : 0;

            int sum = digit1 + digit2 + carry;

            carry = sum / 10;
            sum %= 10;
            res.push_back(sum + '0');
        }
    }

    if (carry && !is_frac) {
        res.push_back('0' + carry);
    } else if (carry && is_frac) {
        extra = 1;
    }

    std::reverse(res.begin(), res.end());
    return res;
}

custom_long custom_long::operator+(const custom_long& other)
{
    custom_long res("0", "0");
    int carry = 0;

    res.fraction = add(fraction, other.fraction, true, carry);
    res.integer = add(integer, other.integer, false, carry);

    auto [size1, size2] = get_sizes(fraction, other.fraction);
    int max_size = std::max(size1, size2);


    if (carry) {
        res.integer = add(res.integer, "1", false, carry);
    }

    return res;
}

std::string custom_long::subtract(const std::string& num1, const std::string& num2, bool is_frac)
{
    std::string res;
    auto [size1, size2] = get_sizes(num1, num2);
    int max_size = std::max(size1, size2);
    int borrow = 0;

    std::string new_num1 = num1;
    std::string new_num2 = num2;

    // std::cout << "-------before-------" << std::endl;
    // std::cout << new_num1 << std::endl;
    // std::cout << new_num2 << std::endl;
    if (is_frac) {
        if (size1 < max_size) {
            new_num1.append(max_size - size1, '0');
        }

        if (size2 < max_size) {
            new_num2.append(max_size - size2, '0');
        }
    }


    // std::cout << new_num1 << std::endl;
    // std::cout << new_num2 << std::endl;
    // std::cout << "-------after-------" << std::endl;

    for (int i = 0; i < max_size; i++) {
        int digit1 = i < size1 ? new_num1[size1 - 1 - i] - '0' : 0;
        int digit2 = i < size2 ? new_num2[size2 - 1 - i] - '0' : 0;

        int rest = digit1 - digit2 - borrow;

        if (rest < 0) {
            rest += 10;
            borrow = 1;
        } else {
            borrow = 0;
        }
        res.push_back(rest + '0');
    }

    if (!is_frac) {
        cut(res);
    }
    

    std::reverse(res.begin(), res.end());
    return res;
}

custom_long custom_long::operator-(const custom_long& other)
{
    custom_long res("0", "0");
    
    std::string num_int1 = integer;
    std::string num_int2 = other.integer;
    std::string num_frac1 = fraction;
    std::string num_frac2 = other.fraction;
    bool sign = false;
    bool flag = false;

    bool compare_of_ints = int_compare(integer, other.integer);
    bool compare_of_fracs = frac_compare(fraction, other.fraction);

    if (!(*this == other)) {
        if (compare_of_ints) { // int1 < int2
            std::swap(num_int1, num_int2);
            sign = true;

            if (compare_of_fracs) { // frac1 < frac2
                std::swap(num_frac1, num_frac2);
                flag = true;
            }
        } else {
            if (compare_of_fracs) { // frac1 < frac2
                std::swap(num_frac1, num_frac2);
                flag = true;
                sign = true;
            }
        }
    } else {
        return res;
    }

    auto [size1, size2] = get_sizes(fraction, other.fraction);
    int max_size = std::max(size1, size2);

    res.fraction = subtract(num_frac1, num_frac2, true);
    res.integer = subtract(num_int1, num_int2, false);

    if (flag) {
        res.integer = subtract(res.integer, "1", false);
    }

    if (sign) {
        res.integer.insert(0, 1, '-');
    }

    cut(res.fraction);
    return res;
}

custom_long custom_long::operator*(const custom_long& other)
{
    return custom_long("0", "0");
}

custom_long custom_long::operator/(const custom_long& other)
{
    return custom_long("0", "0");
}