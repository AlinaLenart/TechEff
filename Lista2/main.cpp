#include "CNumber.h"
#include "Constants.h"
#include <iostream>

int main() {
    CNumber number;
    number = 12345;  
    std::cout << number.sToStr() << std::endl;  

    number = -987654;  
    std::cout << number.sToStr() << std::endl;  

    CNumber c_num_0, c_num_1;
    c_num_0 = 368;
    c_num_1 = 1567;
    c_num_0 = c_num_1; 
    std::cout << c_num_0.sToStr() << std::endl;  
    std::cout << c_num_1.sToStr() << std::endl;  

    return 0;
}
