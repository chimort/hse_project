#include "custom_long.h"
#include <stdio.h>
#include <string>
#include <cmath>
#include <algorithm>

//Добавить проверку на то является ли число отрицательным
bool int_compare(std::string num1, std::string num2)
{
    int size1_int = num1.size();
    int size2_int = num2.size();
    if (size1_int < size2_int) {
        return true;
    } else if (size1_int > size2_int) {
        return false;
    } else {
        for (int i = 0; i < size1_int; i++) {
            if (num1[i] - '0' < num2[i] - '0') {
                return true;
            } else if (num1[i] - '0' > num2[i] - '0') {
                return false;
            }
        }
        return false;
    }
}

bool frac_compare(std::string num1, std::string num2)
{
    int size1 = num1.size();
    int size2 = num2.size();
    int max_size = std::max(size1, size2);

    //Сделать округления до ближайщего числа != 0
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

bool operator==(const custom_long &num1, const custom_long &num2)
{
    int size_int1 = num1.integer.size();
    int size_int2 = num2.integer.size();
    int size_frac1 = num1.fraction.size();
    int size_frac2 = num2.fraction.size();

    if (size_int1 != size_int2 || size_frac1 != size_frac2) {
        return false;
    }
    for (int i = 0; i < size_int1; i++) {
        if (num1.integer[i] != num2.integer[i]) {
            return false;
        }
    }
    for (int i = 0; i < size_frac1; i++) {
        if (num1.fraction[i] != num2.fraction[i]) {
            return false;
        }
    }
    return true;
}

bool operator<(const custom_long &num1, const custom_long &num2)
{   
    if (int_compare(num1.integer, num2.integer)) {
        return true;
    } else if (int_compare(num2.integer, num1.integer)){
        return false;
    } else {
        return operator==(num1, num2) ? false : frac_compare(num1.fraction, num2.fraction);
    }
}

bool operator>(const custom_long &num1, const custom_long &num2)
{
    return operator==(num1, num2) ? false : !operator<(num1, num2);;
}

std::string custom_long::add(const std::string& num1, const std::string& num2, bool is_frac)
{
    std::string res;
    int carry = 0;

    uint32_t len1 = num1.size();
    uint32_t len2 = num2.size();
    uint32_t max_len = std::max(len1, len2);

    if (is_frac) {
        uint32_t min_len = std::min(len1, len2);
        int j = 0;
        int i = 0;
        
        std::string new_num1 = num1;
        std::string new_num2 = num2;

        if (len1 < len2) {
            std::string temp = new_num1;
            new_num1 = new_num2;
            new_num2 = temp;

            int temp_len = len1;
            len1 = len2;
            len2 = temp_len;
        }

        while (i < max_len) {
            int digit1 = 0;
            int digit2 = 0;

            if (max_len - 1 - i > min_len - 1) {
                digit1 = new_num1[len1 - 1 - i] - '0';
            }else {
                digit1 = new_num1[len1 - 1 - i] - '0';
                digit2 = new_num2[len2 - 1 - j] - '0';
                j++;
            }
            int sum = digit1 + digit2 + carry;

            carry = sum / 10;
            sum %= 10;
            res.push_back(sum + '0');
            i++;
        }
    } else {
        for (int i = 0; i < max_len || carry; i++) {
            int digit1 = i < len1 ? num1[len1 - 1 - i] - '0' : 0;
            int digit2 = i < len2 ? num2[len2 - 1 - i] - '0' : 0;

            int sum = digit1 + digit2 + carry;

            carry = sum / 10;
            sum %= 10;
            res.push_back(sum + '0');
        }
    }


    if (carry) {
        res.push_back('0' + carry);
    }

    std::reverse(res.begin(), res.end());
    return res;
}

custom_long custom_long::operator+(const custom_long& other)
{
    custom_long res("0", "0");
    
    res.fraction = add(fraction, other.fraction, true);
    res.integer = add(integer, other.integer, false);

    uint32_t len1 = fraction.size();
    uint32_t len2 = other.fraction.size();
    uint32_t max_len = std::max(len1, len2);

    if (res.fraction.size() > max_len) {
        res.integer = add(res.integer, "1", false);
    }

    return res;
}

std::string custom_long::subtract(const std::string& num1, const std::string& num2, bool is_frac)
{
    std::string res;
    uint32_t len1 = num1.size();
    uint32_t len2 = num2.size();
    uint32_t max_len = std::max(len1, len2);
    int borrow = 0;

    for (int i = 0; i < max_len; i++) {
        int digit1 = i < len1 ? num1[len1 - 1 - i] - '0' : 0;
        int digit2 = i < len2 ? num2[len2 - 1 - i] - '0' : 0;

        int rest = digit1 - digit2 - borrow; 

        if (rest < 0) {
            rest += 10;
            borrow = 1;
        } else {
            borrow = 0;
        }
        std::cout << digit1 << " " << digit2 << std::endl;
        std::cout << rest << std::endl;
        res.push_back(rest + '0');
    }

    while (res.size() > 1 && res.back() == '0') {
        res.pop_back();
    }

    std::reverse(res.begin(), res.end());
    return res;
}

custom_long custom_long::operator-(const custom_long& other)
{
    custom_long res("0", "0");
    
    //res.fraction = subtract(fraction, other.fraction, true);
    res.fraction = fraction;
    res.integer = subtract(integer, other.integer, false);

    // if (res.fraction.size() > max_len) {
    //     res.integer = subtract(res.integer, "1", false);
    // }

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