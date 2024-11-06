#include <iostream>
#include "CNumber.cpp"

int main() {
    CNumber num1(379);
    CNumber num2(999);
    CNumber result;
    result = num1 - num2;
    std::cout << "379 - 999 = " << result.sToStr() << std::endl;

    num2 = -999;
    result = num1 + num2;
    std::cout << "379 + (-999) = " << result.sToStr() << std::endl;

    num1 = 1000;
    num2 = 22;
    result = num1 - num2;
    std::cout << "1000 - 22 = " << result.sToStr() << std::endl;

    num2 = -22;
    std::cout << "1000 + (-22) = " << result.sToStr() << std::endl;

    num1 = 999;
    num2 = 1;
    result = num1 + num2;
    std::cout << "999 + 1 = " << result.sToStr() << std::endl;

    num1 = 37;
    num2 = -11;
    result = num1 * num2;
    std::cout << "37 * (-11) = " << result.sToStr() << std::endl;

    num1 = -99;
    num2 = -2;
    result = num1 * num2;
    std::cout << "-99 * (-2) = " << result.sToStr() << std::endl;

    num1 = 121;
    num2 = 3012;
    result = num1 * num2;
    std::cout << "121 * 3012 = " << result.sToStr() << std::endl;

    int largeValue = std::numeric_limits<int>::max(); // INT_MAX
    CNumber largeNumber1(largeValue);
    CNumber largeNumber2(largeValue);

    result = largeNumber1 * largeNumber2;
    std::cout << largeNumber1.sToStr() << " * " << largeNumber2.sToStr() << " = " << result.sToStr() << std::endl;

    num1 = 364452;
    num2 = 13;
    result = num1 / num2;
    std::cout << "364452 / 13 = " << result.sToStr() << std::endl;

    num1 = 3448182;
    num2 = -123;
    result = num1 / num2;
    std::cout << "3448182 / (-123) = " << result.sToStr() << std::endl;

    num1 = -89998;
    num2 = -7777;
    result = num1 / num2;
    std::cout << "-89998 / (-7777) = " << result.sToStr() << std::endl;

    num1 = -89998;
    num2 = 0;
    result = num1 / num2;
    std::cout << "-89998 / 0 = " << result.sToStr() << std::endl;

    num1 = 0;
    num2 = -899;
    result = num1 / num2;
    std::cout << "0 / -899 = " << result.sToStr() << std::endl;


    CNumber numMod1(33012);
    CNumber numMod2 = numMod1 ^ 3;
    std::cout << "Test modyfikacji liczba przed: "<< numMod1.sToStr() << " liczba po: " << numMod2.sToStr() << std::endl;

    numMod1 = 4124;
    numMod2 = numMod1 ^ 4;
    std::cout << "Test modyfikacji liczba przed: "<< numMod1.sToStr() << " liczba po: " << numMod2.sToStr() << std::endl;

    numMod1 = 1921;
    numMod2 = numMod1 ^ 9;
    std::cout << "Test modyfikacji liczba przed: "<< numMod1.sToStr() << " liczba po: " << numMod2.sToStr() << std::endl;

    numMod1 = 3471;
    numMod2 = numMod1 ^ 10;
    std::cout << "Test modyfikacji liczba przed: "<< numMod1.sToStr() << " liczba po: " << numMod2.sToStr() << std::endl;

    numMod1 = 4444;
    numMod2 = numMod1 ^ 4;
    std::cout << "Test modyfikacji liczba przed: "<< numMod1.sToStr() << " liczba po: " << numMod2.sToStr() << std::endl;






    // CNumber number1; 
    // std::cout << "Konstruktor domyslny: " << number1.sToStr() << std::endl;

    // CNumber number2(379);
    // std::cout << "Konstruktor z inta: " << number2.sToStr() << std::endl;

    // CNumber number3(number2);
    // std::cout << "Konstruktor kopoujacy: " << number3.sToStr() << std::endl;

    // number1 = 999;
    // std::cout << "Uzycie operatora=(int iValue): " << number1.sToStr() << std::endl;

    // number3 = number1;
    // std::cout << "Uzycie operatora=(const CNumber &number): " << number3.sToStr() << std::endl;

    // CNumber sum1 = number2 + 100;
    // std::cout << "Dodawanie inta: " << sum1.sToStr() << std::endl;

    // CNumber sum2 = number2 + number3;
    // std::cout << "Dodawanie CNumber: " << sum2.sToStr() << std::endl;

    // CNumber diff1 = number1 - 500;
    // std::cout << "Odejmowanie inta: " << diff1.sToStr() << std::endl;

    // CNumber diff2 = number3 - number2;
    // std::cout << "Odejmowanie CNumber: " << diff2.sToStr() << std::endl;

    // CNumber prod1 = number2 * 3;
    // std::cout << "Mnozenie inta: " << prod1.sToStr() << std::endl;

    // CNumber prod2 = number2 * number3;
    // std::cout << "Mnozenie CNumber: " << prod2.sToStr() << std::endl;

    // CNumber quot1 = number1 / 3;
    // std::cout << "Dzielenie inta: " << quot1.sToStr() << std::endl;

    // CNumber quot2 = number3 / number2;
    // std::cout << "Dzielenie CNumber: " << quot2.sToStr() << std::endl;

    // CNumber negativeNumber(-1234);
    // std::cout << "Konstruktor z ujemnym intem: " << negativeNumber.sToStr() << std::endl;


    // int largeValue1 = std::numeric_limits<int>::max(); // INT_MAX
    // int largeValue2 = std::numeric_limits<int>::max() - 2; // INT_MAX - 2
    // CNumber largeNumber1(largeValue1);
    // CNumber largeNumber2(largeValue2);
    
    // CNumber result = largeNumber1 * largeNumber2;

    // std::cout << largeNumber1.sToStr() << " * " << largeNumber2.sToStr() << " = " << result.sToStr() << std::endl;


    // return 0;
}
