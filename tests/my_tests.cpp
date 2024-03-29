#include "gtest/gtest.h"
#include "custom_long.h"
#include <iostream>

TEST(Compare1, SameIntegers) {
    std::cout << "--------------------\n" << "Compare1, SameIntegers:" << std::endl;

    custom_long num1 = {"22", "124525"};
    custom_long num2 = {"22", "2"};

    std::cout << "Testing: " << num1 << " < " << num2 << std::endl;
    EXPECT_TRUE(num1 < num2) << "Comparison failed: " << num1 << " < " << num2;

    std::cout << "--------------------\n" << std::endl;
}

TEST(Compare2, LargeNumbers) {
    std::cout << "--------------------\n" << "Compare2, LargeNumbers:" << std::endl;

    custom_long num1 = {"9876543210123456789", "124525"};
    custom_long num2 = {"1234567890123456789", "2"};

    std::cout << "Testing: " << num1 << " > " << num2 << std::endl;
    EXPECT_TRUE(num1 > num2) << "Comparison failed: " << num1 << " > " << num2;

    std::cout << "--------------------\n" << std::endl;
}

TEST(Compare3, OneNegativeNumber) {
    std::cout << "--------------------\n" << "Compare3, OneNegativeNumber:" << std::endl;

    custom_long num1 = {"-22", "124525"};
    custom_long num2 = {"22", "123456"};

    std::cout << "Testing: " << num1 << " < " << num2 << std::endl;
    EXPECT_TRUE(num1 < num2) << "Comparison failed: " << num1 << " < " << num2;

    std::cout << "--------------------\n" << std::endl;
}

TEST(Compare, TwoNegativeNumber) {
    std::cout << "--------------------\n" << "Compare, TwoNegativeNumber:" << std::endl;

    custom_long num1 = {"-22", "56"};
    custom_long num2 = {"-22", "124525"};

    std::cout << "Testing: " << num1 << " < " << num2 << std::endl;
    EXPECT_TRUE(num1 < num2) << "Comparison failed: " << num1 << " < " << num2;

    std::cout << "--------------------\n" << std::endl;
}

TEST(Equality, SameIntegers) {
    std::cout << "--------------------\n" << "Equality, SameIntegers:" << std::endl;

    custom_long num1 = {"-22", "124525"};
    custom_long num2 = {"-22", "124525"};

    std::cout << "Testing equality: " << num1 << " == " << num2 << std::endl;
    EXPECT_TRUE(num1 == num2);
    EXPECT_FALSE(num1 != num2) << "Equality check failed: " << num1 << " != " << num2;

    std::cout << "--------------------\n" << std::endl;
}

TEST(Inequality, DifferentLengths) {
    std::cout << "--------------------\n" << "Inequality, DifferentLengths:" << std::endl;

    custom_long num1 = {"-22", "124525"};
    custom_long num2 = {"-22", "124"};

    std::cout << "Testing inequality: " << num1 << " != " << num2 << std::endl;
    EXPECT_TRUE(num1 != num2);
    EXPECT_FALSE(num1 == num2) << "Inequality check failed: " << num1 << " == " << num2;

    std::cout << "--------------------\n" << std::endl;
}

TEST(PositiveEqualation, SimpleEqualation) {
    std::cout << "--------------------\n" << "PositiveEqualation, SimpleEqualation:" << std::endl;

    custom_long num1 = {"22", "124525"};
    custom_long num2 = {"22", "124"};

    std::cout << "Testing inequality: " << num1 << " != " << num2 << std::endl;
    EXPECT_TRUE(num1 != num2);
    EXPECT_FALSE(num1 == num2) << "Inequality check failed: " << num1 << " == " << num2;

    std::cout << "--------------------\n" << std::endl;
}

TEST(Compare, NegativeNumbers) {
    std::cout << "--------------------\n" << "Compare, NegativeNumbers:" << std::endl;

    custom_long num1 = {"-123", "456"};
    custom_long num2 = {"-123", "789"};

    std::cout << "Testing less than: " << num1 << " < " << num2 << std::endl;
    EXPECT_FALSE(num1 < num2) << "Less than check failed: " << num1 << " < " << num2;

    std::cout << "Testing greater than: " << num1 << " > " << num2 << std::endl;
    EXPECT_TRUE(num1 > num2) << "Greater than check failed: " << num1 << " > " << num2;

    std::cout << "Testing equality: " << num1 << " == " << num2 << std::endl;
    EXPECT_FALSE(num1 == num2) << "Equality check failed: " << num1 << " == " << num2;

    std::cout << "Testing inequality: " << num1 << " != " << num2 << std::endl;
    EXPECT_TRUE(num1 != num2) << "Inequality check failed: " << num1 << " != " << num2;

    std::cout << "--------------------\n" << std::endl;
}

TEST(Compare, MixedSignNumbers) {
    std::cout << "--------------------\n" << "Compare, MixedSignNumbers:" << std::endl; 
    custom_long num1 = {"-123", "456"};
    custom_long num2 = {"123", "789"};

    std::cout << "Testing: " << num1 << " < " << num2 << std::endl;
    EXPECT_TRUE(num1 < num2) << "Comparison failed: " << num1 << " < " << num2;

    std::cout << "Testing: " << num1 << " not > " << num2 << std::endl;
    EXPECT_FALSE(num1 > num2) << "Comparison failed: " << num1 << " not > " << num2;

    std::cout << "Testing: " << num1 << " == " << num2 << std::endl;
    EXPECT_FALSE(num1 == num2) << "Comparison failed: " << num1 << " != " << num2;

    std::cout << "Testing: " << num1 << " != " << num2 << std::endl;
    EXPECT_TRUE(num1 != num2) << "Comparison failed: " << num1 << " != " << num2;
    std::cout << "--------------------\n" << std::endl;
}

TEST(CustomLongTest, SetPrecision) {
    std::cout << "--------------------\n" << "CustomLongTest, SetPrecision:" << std::endl; 

    custom_long n1 = {"-123", "456"};

    std::cout << "Testing precision 0: " << n1.set_precision(0) << std::endl;
    EXPECT_TRUE(n1.set_precision(0) == custom_long("-123", ""));

    std::cout << "Testing precision 1: " << n1.set_precision(1) << std::endl;
    EXPECT_TRUE(n1.set_precision(1) == custom_long("-123", "4"));

    std::cout << "Testing precision 2: " << n1.set_precision(2) << std::endl;
    EXPECT_TRUE(n1.set_precision(2) == custom_long("-123", "45"));

    std::cout << "Testing precision 3: " << n1.set_precision(3) << std::endl;
    EXPECT_TRUE(n1.set_precision(3) == custom_long("-123", "456"));

    std::cout << "Additional check precision 0: " << n1.set_precision(0) << std::endl;
    EXPECT_FALSE(n1.set_precision(0) != custom_long("-123", ""));

    std::cout << "Additional check precision 1: " << n1.set_precision(1) << std::endl;
    EXPECT_FALSE(n1.set_precision(1) != custom_long("-123", "4"));

    std::cout << "Additional check precision 2: " << n1.set_precision(2) << std::endl;
    EXPECT_FALSE(n1.set_precision(2) != custom_long("-123", "45"));

    std::cout << "Additional check precision 3: " << n1.set_precision(3) << std::endl;
    EXPECT_FALSE(n1.set_precision(3) != custom_long("-123", "456"));

    std::cout << "--------------------\n" << std::endl;
}


TEST(CustomLongTest, SumNoCarry) {
    std::cout << "--------------------\n" << "CustomLongTest, SumNoCarry:" << std::endl; 

    custom_long n1("123", "456");
    custom_long n2("789", "012");

    custom_long expected("912", "468");

    std::cout << "Testing sum: " << n1 << " + " << n2 << " = " << expected << std::endl;
    EXPECT_TRUE(n1 + n2 == expected);

    std::cout << "--------------------\n" << std::endl;
}

TEST(CustomLongTest, SumDifferentIntegerLengthCarry) {
    std::cout << "--------------------\n" << "CustomLongTest, SumDifferentIntegerLengthCarry:" << std::endl;

    custom_long num1{"1001009", "101"};
    custom_long num2{"43031", "01"};

    custom_long expected{"1044040", "111"};

    std::cout << "Testing sum: " << num1 << " + " << num2 << " = " << expected << std::endl;
    EXPECT_TRUE(num1 + num2 == expected);

    std::cout << "--------------------\n" << std::endl;
}

TEST(CustomLongTest, test2) {
    std::cout << "--------------------\n" << "CustomLongTest, test2:" << std::endl;

    custom_long num1{"9", "0001"};
    custom_long num2{"1", "90901"};

    custom_long expected{"10", "90911"};

    std::cout << "Testing sum: " << num1 << " + " << num2 << " = " << expected << std::endl;
    EXPECT_TRUE(num1 + num2 == expected);

    std::cout << "--------------------\n" << std::endl;
}

TEST(CustomLongTest, test3) {
    std::cout << "--------------------\n" << "CustomLongTest, test3:" << std::endl;

    custom_long num1{"9", "12"};
    custom_long num2{"9", "13"};

    custom_long expected{"18", "25"};

    std::cout << "Testing sum: " << num1 << " + " << num2 << " = " << expected << std::endl;
    EXPECT_TRUE(num1 + num2 == expected);

    std::cout << "--------------------\n" << std::endl;
}

TEST(DifferentCreation, test1) {
    std::cout << "--------------------\n" << "DifferentCreation, test1:" << std::endl;

    custom_long num1 = custom_long(123);
    custom_long expected = custom_long("123", "0");

    std::cout << "Testing creation and comparison: " << num1 << " == " << expected << std::endl;
    EXPECT_TRUE(num1 == expected);

    std::cout << "--------------------\n" << std::endl;
}

TEST(DifferentCreation, test2) {
    std::cout << "--------------------\n" << "DifferentCreation, test2:" << std::endl;

    custom_long num1 = custom_long("2343535");
    custom_long expected = custom_long(2343535);

    std::cout << "Testing creation and comparison: " << num1 << " == " << expected << std::endl;
    EXPECT_TRUE(num1 == expected);

    std::cout << "--------------------\n" << std::endl;
}

TEST(DifferentCreation, test3) {
    std::cout << "--------------------\n" << "DifferentCreation, test3:" << std::endl;

    custom_long num1 = custom_long("2343535.444444");
    custom_long expected = custom_long("2343535", "444444");

    std::cout << "Testing creation and comparison: " << num1 << " == " << expected << std::endl;
    EXPECT_TRUE(num1 == expected);

    std::cout << "--------------------\n" << std::endl;
}


TEST(Subtraction, SimpleSubtraction) {
    std::cout << "--------------------\n" << "Subtraction, SimpleSubtraction:" << std::endl;

    custom_long num1 = {"22", "124525"};
    custom_long num2 = {"22", "124"};

    std::cout << "Testing subtraction: " << num1 << " - " << num2 << " = " << num1 - num2 << std::endl;
    EXPECT_TRUE(num1 - num2 == custom_long("0", "000525"));

    std::cout << "--------------------\n" << std::endl;
}

TEST(Subtraction, NegativeSubtraction) {
    std::cout << "--------------------\n" << "Subtraction, NegativeSubtraction:" << std::endl;

    custom_long num1 = {"-123", "789"};
    custom_long num2 = {"-123", "456"};

    std::cout << "Testing subtraction: " << num1 << " - " << num2 << " = " << num1 - num2 << std::endl;
    EXPECT_TRUE(num1 - num2 == custom_long("0", "333"));

    std::cout << "--------------------\n" << std::endl;
}

TEST(Subtraction, DifferentSigns) {
    std::cout << "--------------------\n" << "Subtraction, DifferentSigns:" << std::endl;

    custom_long num1 = {"123", "789"};
    custom_long num2 = {"-23", "456"};

    std::cout << "Testing subtraction: " << num1 << " - " << num2 << " = " << num1 - num2 << std::endl;
    EXPECT_TRUE(num1 - num2 == custom_long("147", "245"));

    std::cout << "--------------------\n" << std::endl;
}

TEST(Multiplication, PositiveNumbers) {
    std::cout << "--------------------\n" << "Multiplication, PositiveNumbers:" << std::endl;

    custom_long num1 = {"123", "456"};
    custom_long num2 = {"789", "012"};

    std::cout << "Testing multiplication: " << num1 << " * " << num2 << " = " << num1 * num2 << std::endl;
    EXPECT_TRUE(num1 * num2 == custom_long("97408", "265472"));

    std::cout << "--------------------\n" << std::endl;
}

TEST(Multiplication, ZeroMultiplication) {
    std::cout << "--------------------\n" << "Multiplication, ZeroMultiplication:" << std::endl;

    custom_long num1 = {"123", "456"};
    custom_long num2 = {"0", "789"};

    std::cout << "Testing multiplication by zero: " << num1 << " * " << num2 << " = " << num1 * num2 << std::endl;
    EXPECT_TRUE(num1 * num2 == custom_long("97", "406784"));

    std::cout << "--------------------\n" << std::endl;
}

TEST(Multiplication, SingleDigitNumbers) {
    std::cout << "--------------------\n" << "Multiplication, SingleDigitNumbers:" << std::endl;

    custom_long num1 = {"247583476934", "43675674578345435"};
    custom_long num2 = {"0", "0"};

    std::cout << "Testing multiplication of single-digit numbers: " << num1 << " * " << num2 << " = " << num1 * num2 << std::endl;
    EXPECT_TRUE(num1 * num2 == custom_long("0", "0"));

    std::cout << "--------------------\n" << std::endl;
}

TEST(Multiplication, LargeNumbers) {
    std::cout << "--------------------\n" << "Multiplication, LargeNumbers:" << std::endl;

    custom_long num1 = {"9812421525", "9"};
    custom_long num2 = {"12323536666", "12"};

    std::cout << "Testing multiplication of large numbers: " << num1 << " * " << num2 << " = " << num1 * num2 << std::endl;
    EXPECT_TRUE(num1 * num2 == custom_long("120923736457853809232", "508"));

    std::cout << "--------------------\n" << std::endl;
}

TEST(Multiplication, SmallNumbers) {
    std::cout << "--------------------\n" << "Multiplication, SmallNumbers:" << std::endl;

    custom_long num1 = {"0", "1"};
    custom_long num2 = {"0", "1"};

    std::cout << "Testing multiplication of small numbers: " << num1 << " * " << num2 << " = " << num1 * num2 << std::endl;
    EXPECT_TRUE(num1 * num2 == custom_long("0", "01"));

    std::cout << "--------------------\n" << std::endl;
}

TEST(Division, DifferentSigns) {
    std::cout << "--------------------\n" << "Division, DifferentSigns:" << std::endl;

    custom_long num1 = {"-123", "456"};
    custom_long num2 = {"789", "012"};

    custom_long res = (num1 / num2);
    std::cout << "Testing division with different signs: " << num1 << " / " << num2 << " = " << res.set_precision(3) << std::endl;
    EXPECT_TRUE(res.set_precision(3) == custom_long("-0", "156"));

    std::cout << "--------------------\n" << std::endl;
}

// TEST(Division, LargerNumberDividedBySmaller) {
//     std::cout << "--------------------\n" << "Division, LargerNumberDividedBySmaller:" << std::endl;

//     custom_long num1 = {"9876543210123456789", "012345"};
//     custom_long num2 = {"123456789", "012"};

//     std::cout << "Testing division of larger number by smaller: " << num1 << " / " << num2 << " = " << (num1 / num2).set_precision(3) << std::endl;
//     EXPECT_TRUE((num1 / num2).set_precision(3) == custom_long("80000000000", "100"));

//     std::cout << "--------------------\n" << std::endl;
// }

TEST(Division, SmallerNumberDividedByLarger) {
    std::cout << "--------------------\n" << "Division, SmallerNumberDividedByLarger:" << std::endl;

    custom_long num1 = {"123456789", "012"};
    custom_long num2 = {"9876543210123456789", "012345"};

    std::cout << "Testing division of smaller number by larger: " << num1 << " / " << num2 << " = " << (num1 / num2).set_precision(3) << std::endl;
    EXPECT_TRUE((num1 / num2).set_precision(3) == custom_long("0", "0"));

    std::cout << "--------------------\n" << std::endl;
}

TEST(Division, RandomNumbers) {
    std::cout << "--------------------\n" << "Division, RandomNumbers:" << std::endl;

    custom_long num1 = {"98765432101", "987654"};
    custom_long num2 = {"123456789", "012"};

    custom_long res = (num1 / num2);

    std::cout << "Testing division of random numbers: " << num1 << " / " << num2 << " = " << res.set_precision(3) << std::endl;
    EXPECT_TRUE(res.set_precision(3) == custom_long("800", "0"));

    std::cout << "--------------------\n" << std::endl;
}


int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);

  return RUN_ALL_TESTS();
}