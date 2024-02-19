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
    res.set_precision(1234);

    std::cout << "----------addition block----------" << std::endl;
    std::cout << res.set_precision(0) << std::endl;
    std::cout << num3+num4 << std::endl;
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

    std::cout << num3 / num4 << std::endl;
    std::cout << "-123.456"_cl / "789.012"_cl << std::endl;

    auto tessst = "1243825821852186578216578126785682176528.124215215215"_cl;
    std::cout << tessst << std::endl;

    return 0;
}