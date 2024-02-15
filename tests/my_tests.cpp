#include "gtest/gtest.h"
#include "custom_long.h"
#include <iostream>

TEST(Compare1, SameIntegers){
    custom_long num1 = {"22", "124525"};
    custom_long num2 = {"22", "2"};
    EXPECT_TRUE(num1 < num2);
}

TEST(Compare2, LargeNumbers) {
    custom_long num1 = {"9876543210123456789", "124525"};
    custom_long num2 = {"1234567890123456789", "2"};

    EXPECT_TRUE(num1 > num2);
}

TEST(Compare3, OneNegativeNumber) {
    custom_long num1 = {"-22", "124525"};
    custom_long num2 = {"22", "123456"};

    EXPECT_TRUE(num1 < num2);
}

TEST(Compare, TwoNegativeNumber) {
    custom_long num1 = {"-22", "56"};
    custom_long num2 = {"-22", "124525"};

    EXPECT_TRUE(num1 < num2);
}

TEST(Equality, SameIntegers) {
    custom_long num1 = {"-22", "124525"};
    custom_long num2 = {"-22", "124525"};

    EXPECT_TRUE(num1 == num2);
    EXPECT_FALSE(num1 != num2);
}

TEST(Inequality, DifferentLengths) {
    custom_long num1 = {"-22", "124525"};
    custom_long num2 = {"-22", "124"};

    EXPECT_TRUE(num1 != num2);
    EXPECT_FALSE(num1 == num2);
}

TEST(PositiveEqualation, SimpleEqualation) {
    custom_long num1 = {"22", "124525"};
    custom_long num2 = {"22", "124"};

    EXPECT_TRUE(num1 != num2);
    EXPECT_FALSE(num1 == num2);
}

TEST(Compare, NegativeNumbers) {
    custom_long num1 = {"-123", "456"};
    custom_long num2 = {"-123", "789"};

    EXPECT_FALSE(num1 < num2);
    EXPECT_TRUE(num1 > num2);
    EXPECT_FALSE(num1 == num2);
    EXPECT_TRUE(num1 != num2);
}

TEST(Compare, MixedSignNumbers) {
    custom_long num1 = {"-123", "456"};
    custom_long num2 = {"123", "789"};

    EXPECT_TRUE(num1 < num2);
    EXPECT_FALSE(num1 > num2);
    EXPECT_FALSE(num1 == num2);
    EXPECT_TRUE(num1 != num2);
}

TEST(CustomLongTest, SetPrecision) {
    custom_long n1 = {"-123", "456"};

    EXPECT_TRUE(n1.new_with_precision(0) == custom_long("-123", ""));
    EXPECT_TRUE(n1.new_with_precision(1) == custom_long("-123", "4"));
    EXPECT_TRUE(n1.new_with_precision(2) == custom_long("-123", "45"));
    EXPECT_TRUE(n1.new_with_precision(3) == custom_long("-123", "456"));

    EXPECT_FALSE(n1.new_with_precision(0) != custom_long("-123", ""));
    EXPECT_FALSE(n1.new_with_precision(1) != custom_long("-123", "4"));
    EXPECT_FALSE(n1.new_with_precision(2) != custom_long("-123", "45"));
    EXPECT_FALSE(n1.new_with_precision(3) != custom_long("-123", "456"));
}


TEST(CustomLongTest, SumNoCarry) {
    custom_long n1("123", "456");
    custom_long n2("789", "012");

    custom_long expected("912", "468");

    EXPECT_TRUE(n1 + n2 == expected);
}

TEST(CustomLongTest, SumDifferentIntegerLengthCarry) {
    custom_long num1{"1001009", "101"};
    custom_long num2{"43031", "01"};

    custom_long expected{"1044040", "111"};

    EXPECT_TRUE(num1 + num2 == expected);
}

TEST(CustomLongTest, test2) {
    custom_long num1{"9", "0001"};
    custom_long num2{"1", "90901"};

    custom_long expected{"10", "90911"};

    EXPECT_TRUE(num1 + num2 == expected);
}

TEST(CustomLongTest, test3) {
    custom_long num1{"9", "12"};
    custom_long num2{"9", "13"};

    custom_long expected{"18", "25"};

    EXPECT_TRUE(num1 + num2 == expected);
}

TEST(DifferentCreation, test1) {
    custom_long num1 = custom_long(123);
    custom_long expected = custom_long("123", "0");
    EXPECT_TRUE(num1 == expected);
}

TEST(DifferentCreation, test2) {
    custom_long num1 = custom_long(222.333);
    custom_long expected = custom_long("222", "333");

    EXPECT_TRUE(num1 == expected);
}

TEST(DifferentCreation, test3) {
    custom_long num1 = custom_long("2343535");
    custom_long expected = custom_long(2343535);

    EXPECT_TRUE(num1 == expected);
}

TEST(DifferentCreation, test4) {
    custom_long num1 = custom_long("2343535.444444");
    custom_long expected = custom_long("2343535", "444444");
    EXPECT_TRUE(num1 == expected);
}


int main(int argc, char **argv)
{
  ::testing::InitGoogleTest(&argc, argv);

  return RUN_ALL_TESTS();
}