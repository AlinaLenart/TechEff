#include <iostream>
#include "CNumber.h"

int main() {
    CNumber number1; 
    std::cout << "Konstruktor domyslny: " << number1.sToStr() << std::endl;

    CNumber number2(379);
    std::cout << "Konstruktor z inta: " << number2.sToStr() << std::endl;

    CNumber number3(number2);
    std::cout << "Konstruktor kopoujacy: " << number3.sToStr() << std::endl;

    number1 = 999;
    std::cout << "Uzycie operatora=(int iValue): " << number1.sToStr() << std::endl;

    number3 = number1;
    std::cout << "Uzycie operatora=(const CNumber &number): " << number3.sToStr() << std::endl;

    CNumber sum1 = number2 + 100;
    std::cout << "Dodawanie inta: " << sum1.sToStr() << std::endl;

    CNumber sum2 = number2 + number3;
    std::cout << "Dodawanie CNumber: " << sum2.sToStr() << std::endl;

    CNumber diff1 = number1 - 500;
    std::cout << "Odejmowanie inta: " << diff1.sToStr() << std::endl;

    CNumber diff2 = number3 - number2;
    std::cout << "Odejmowanie CNumber: " << diff2.sToStr() << std::endl;

    CNumber prod1 = number2 * 3;
    std::cout << "Mnozenie inta: " << prod1.sToStr() << std::endl;

    CNumber prod2 = number2 * number3;
    std::cout << "Mnozenie CNumber: " << prod2.sToStr() << std::endl;

    CNumber quot1 = number1 / 3;
    std::cout << "Dzielenie inta: " << quot1.sToStr() << std::endl;

    CNumber quot2 = number3 / number2;
    std::cout << "Dzielenie CNumber: " << quot2.sToStr() << std::endl;

    CNumber negativeNumber(-1234);
    std::cout << "Konstruktor z ujemnym intem: " << negativeNumber.sToStr() << std::endl;


    int largeValue1 = std::numeric_limits<int>::max(); // INT_MAX
    int largeValue2 = std::numeric_limits<int>::max() - 2; // INT_MAX - 2
    CNumber largeNumber1(largeValue1);
    CNumber largeNumber2(largeValue2);
    
    CNumber result = largeNumber1 * largeNumber2;

    std::cout << largeNumber1.sToStr() << " * " << largeNumber2.sToStr() << " = " << result.sToStr() << std::endl;


    return 0;
}
