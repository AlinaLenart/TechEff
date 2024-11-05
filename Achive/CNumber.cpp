#include "CNumber.h"
#include "Constants.h"
#include <iostream>

CNumber::CNumber() : pi_table(nullptr), i_length(0), is_negative(false) {}

CNumber::~CNumber() {
    delete[] pi_table;
}

std::string CNumber::sToStr() const {
    std::string result;
    if (is_negative) {
        result += '-';
    }
    for (int i = 0; i < i_length; i++) {
        result += '0' + pi_table[i]; 
    }
    return result;
}

CNumber& CNumber::operator=(int iValue) {
    
    delete[] pi_table;

    is_negative = (iValue < 0);
    int tempValue = (iValue == 0) ? 1 : (is_negative ? -iValue : iValue);

    i_length = 0;
    int temp = tempValue;
    while (temp > 0) {
        temp /= 10;
        i_length++;
    }

    pi_table = new int[i_length];

    for (int i = i_length - 1; i >= 0; i--) {
        pi_table[i] = tempValue % DEFAULT_DIVIDER; 
        tempValue /= DEFAULT_DIVIDER;              
    }

    return *this;
}

CNumber& CNumber::operator=(const CNumber &pcOther) {
    if (this == &pcOther) {
        return *this; // sprawdzenie samoprzypisania
    }

    delete[] pi_table;

    i_length = pcOther.i_length; //kopiowanie wartosci atrybutow
    is_negative = pcOther.is_negative;

    pi_table = new int[i_length];
    for (int i = 0; i < i_length; i++) {
        pi_table[i] = pcOther.pi_table[i]; //wypelnienie tablicy manualnie
    }

    return *this;
}
/*void CNumber::operator=(const CNumber &pcOther) {
    pi_table = pcOther.pi_table;
    i_length = pcOther.i_length;
} */
/* ta metoda kopiuje wskaznik pi_table z jednego obiektu do drugiego,
przez co oba obiekty wskazuja na te sama dynamicznie alokowana tablice
w cpp może prowadzic do problemów w destruktorze poniewaz 
jezeli jeden z obiektow zostanie zniszczony (zwolni pamiec do której wskazuje wskaznik)
a drugi obiekt bedzie odwolywal sie do nieistniejacej juz tablicy to mozee to prowadzic do wycieku pamieci*/






