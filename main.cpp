#include "custom_long.h"

int main()
{
    custom_long num1{"123", "999"};
    custom_long num2{"789", "999"};
    // custom_long num3{"1111", "00000000000001"};
    std::cout << num1+num2 << std::endl;
    return 0;
}