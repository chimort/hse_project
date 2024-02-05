#include "custom_long.h"
#include <chrono>
#include <algorithm>

int main()
{
    custom_long num1{"9", "11"};
    custom_long num2{"1", "99"};
    
    custom_long num3{"9", "00100001"};
    custom_long num4{"1", "90901"};

    custom_long num5{"9", "0001"};
    custom_long num6{"1", "90901"};

    custom_long num7{"9", "00100001"};
    custom_long num8{"1", "9090100000001"};

    std::cout << num1+num2 << std::endl;
    std::cout << num3+num4 << std::endl;
    std::cout << num5+num6 << std::endl;
    std::cout << num7+num8 << std::endl;

    return 0;
}