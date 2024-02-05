#include "custom_long.h"
#include <stdio.h>
#include <string>
#include <cmath>
#include <algorithm>


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

std::string subtract(const std::string& num1, const std::string& num2)
{
    std::string res;   
    return res;
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
