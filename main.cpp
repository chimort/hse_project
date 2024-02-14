#include "custom_long.h"

int main()
{
    custom_long num1{"1001009", "101"};
    custom_long num2{"43031", "01"};
    
    custom_long num3{"9", "00100001"};
    custom_long num4{"22", "00090901"};

    custom_long num5{"9", "0001"};
    custom_long num6{"1", "90901"};

    custom_long num7{"9", "12"};
    custom_long num8{"9", "13"};


    custom_long res = num1 + num2;
    res.new_with_precision(1234);

    std::cout << "----------addition block----------" << std::endl;
    std::cout << res.new_with_precision(0) << std::endl;
    std::cout << (num3+num4).new_with_precision(12) << std::endl;
    std::cout << num5+num6 << std::endl;
    std::cout << num7+num8 << std::endl;


    std::cout << "----------compare block----------" << std::endl;
    if (num1 > num2) {
        std::cout << "num1 > num2" << std::endl;
    } else if(num1 < num2) {
        std::cout << "num1 < num2" << std::endl;
    } else {
        std::cout << "num1 = num2" << std::endl;
    }

    // custom_long negativ_num1("-123", "000001");
    // std::cout << negativ_num1 << std::endl;

    if (num1 != num2) {
        std::cout << "num1 != num2" << std::endl;
    }

    std::cout << "----------substract block----------" << std::endl;
    std::cout << num1-num2 << std::endl; //-0.0009999        //ВЕРНЫЕ ОТВЕТЫ
    std::cout << num3-num4 << std::endl; //-7,999909
    std::cout << num5-num6 << std::endl; // 7,09109
    std::cout << num7-num8 << std::endl; //-3,01

    //std::cout << custom_long("123", "0") * custom_long("123", "0") << std::endl;

    custom_long n1("123", "456");
    custom_long n2("789", "012");

    bool tesst = n1 < n2;
    std::cout << tesst << std::endl;
    custom_long n3 = n1.new_with_precision(2);

    std::cout << (n1 + n2) << std::endl;
    std::cout << n1.new_with_precision(0) << std::endl;

    std::cout << custom_long(1.12) << std::endl;
    std::cout << custom_long("2343535.444444") << std::endl;

    return 0;
}