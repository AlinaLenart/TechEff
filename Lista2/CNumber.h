#ifndef CNUMBER_H
#define CNUMBER_H

#include <iostream>

class CNumber {

    public:
        CNumber();
        ~CNumber();

        std::string sToStr() const;

        CNumber& operator=(int iValue);
        CNumber& operator=(const CNumber &pcOther);
        
    private:
        int* pi_table;   
        int i_length;        
        bool is_negative;
};

#endif 
