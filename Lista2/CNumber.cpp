#include "CNumber.h"
#include "Constants.h"
#include <algorithm>
#include <iostream>
#include <cstdlib>

CNumber::CNumber() : pi_table(nullptr), i_length(1), is_negative(false) {
    pi_table = new int[i_length];
    pi_table[0] = 0;
}

CNumber::CNumber(int iValue) {
    pi_table = nullptr;  
    *this = iValue; 
}

CNumber::CNumber(const CNumber &pcOther) {
    i_length = pcOther.getILength();
    pi_table = new int[i_length];
    std::copy(pcOther.pi_table, pcOther.pi_table + i_length, pi_table);
    is_negative = pcOther.getIsNegative();
}
 
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

CNumber CNumber::operator=(const int iValue) {

    delete[] pi_table;

    is_negative = (iValue < 0);
    int tempValue = (iValue == 0) ? 0 : (is_negative ? -iValue : iValue);

    i_length = 0;
    int temp = tempValue;
    while (temp > 0) {
        temp /= DIGIT_DIVIDER;
        i_length++;
    }

    if (iValue == 0) {
        i_length = 1;
    }

    pi_table = new int[i_length];

    for (int i = i_length - 1; i >= 0; i--) {
        pi_table[i] = tempValue % DIGIT_DIVIDER; 
        tempValue /= DIGIT_DIVIDER;              
    }
    return *this;
}

/*void CNumber::operator=(const CNumber &pcOther) {
    pi_table = pcOther.pi_table;
    i_length = pcOther.i_length;
} */
/* ta metoda kopiuje wskaznik pi_table z jednego obiektu do drugiego,
przez co oba obiekty wskazuja na te sama dynamicznie alokowana tablice
w cpp może prowadzic do problemow w destruktorze poniewaz 
jezeli jeden z obiektow zostanie zniszczony (zwolni pamiec do której wskazuje wskaznik)
a drugi obiekt bedzie odwolywal sie do nieistniejacej juz tablicy to mozee to prowadzic do wycieku pamieci*/

CNumber CNumber::operator=(const CNumber &number) {
    if (this == &number) {
        std::cout<<"Proba samoprzypisania"<<std::endl;// sprawdzenie samoprzypisania
        return *this;
    }

    delete[] pi_table;

    i_length = number.getILength(); //kopiowanie wartosci atrybutow
    is_negative = number.getIsNegative();

    pi_table = new int[i_length];
    std::copy(number.getPITable(), number.getPITable() + i_length, pi_table);
    return *this;
}

CNumber CNumber::operator^(const int valueToDelete) {
    if (valueToDelete > 9) {
        return *this;
    }
    int i = 0;
    CNumber newNumber(*this);
    while (newNumber.pi_table[i] == valueToDelete) {
        newNumber.pi_table[i] = 0;
        i++;
    }
    removeLeadingZeros(newNumber.pi_table, newNumber.i_length);
    return newNumber;
}

CNumber CNumber::operator+(int iValue) const {
    return *this + CNumber(iValue);
}

CNumber CNumber::operator+(const CNumber &number) const {
    CNumber thisCopy(*this);
    CNumber numberCopy(number);

    return handleAdditionCase(thisCopy, numberCopy);
}

CNumber CNumber::operator-(int iValue) const{
    return *this - CNumber(iValue);
}

CNumber CNumber::operator-(const CNumber &number) const {
    CNumber thisCopy(*this);
    CNumber numberCopy(number);

    return handleSubtractionCase(thisCopy, numberCopy);
}

CNumber CNumber::operator*(int iValue){
    return *this * CNumber(iValue);
}

CNumber CNumber::operator*(const CNumber &number)  {
    
    int result_length = i_length + number.getILength();
    int *result_array = new int[result_length]();

    for (int i = i_length - 1; i >= 0; --i) {
        
        for (int j = number.getILength() - 1; j >= 0; --j) {
    
            int result_index = (i_length - 1 - i) + (number.getILength() - 1 - j);
            result_array[result_index] += pi_table[i] * number.getPITable()[j];
            
            if (result_array[result_index] >= DIGIT_DIVIDER) { // ponad carry
                result_array[result_index + 1] += result_array[result_index] / DIGIT_DIVIDER;
                result_array[result_index] %= DIGIT_DIVIDER;
            }
        }
    }

    bool result_is_negative = (is_negative != number.getIsNegative());

    reverseTable(result_array, result_length);
    removeLeadingZeros(result_array, result_length);

    CNumber result(result_array, result_length, result_is_negative);
    delete[] result_array; 
    return result;
}

CNumber CNumber::operator/(int iValue) {
    return *this / CNumber(iValue);
}

CNumber CNumber::operator/(const CNumber &number) {
    bool result_is_negative = (is_negative != number.getIsNegative());

    CNumber divisor(number); //tworze kopie eby moc modyfikowac
    divisor.setIsNegative(false);

    if (divisor.getILength() == 1 && divisor.getPITable()[0] == 0) {
        std::cout << "Dzielenie przez zero" << std::endl;
        return CNumber(0); 
    }

    if (!isBiggerThan(divisor) && !isEqual(divisor)) {
        return CNumber(0);
    }

    if (isEqual(divisor)) {
        return result_is_negative ? CNumber(-1) : CNumber(1);
    }

    int result_length = i_length; //maksymalna mozliwa dlugosc to dzielna
    int* result_array = new int[result_length]();

    CNumber tempResult(0);  //reszta 

    for (int i = 0; i < i_length; i++) {
        tempResult = tempResult * DIGIT_DIVIDER + getPITable()[i];
        int count = 0;

        while (tempResult.isBiggerThan(divisor) || tempResult.isEqual(divisor)) {
            tempResult = tempResult - divisor;
            count++;
        }
        result_array[i] = count; 
    }

    removeLeadingZeros(result_array, result_length);

    CNumber result(result_array, result_length, result_is_negative);
    delete[] result_array;  
    return result;
}

int CNumber::getILength() const {
    return i_length;
}

bool CNumber::getIsNegative() const {
    return is_negative;
}

const int* CNumber::getPITable() const {
    return pi_table;
}

void CNumber::setIsNegative(bool isNegative) {
    is_negative = isNegative;
}

CNumber::CNumber(int *&numberTable, int iLength, bool isNegative) {
    if (!numberTable || iLength <= 0) {
        i_length = 1;
        pi_table = new int[1];
        pi_table[0] = 0;
        is_negative = false;
    } else {
        i_length = iLength;
        pi_table = new int[i_length];
        std::copy(numberTable, numberTable + i_length, pi_table);
        is_negative = isNegative;
    }
}

CNumber CNumber::handleAdditionCase(CNumber &thisCopy, CNumber &numberCopy) const {
    if (is_negative != numberCopy.getIsNegative()) { //rozne znaki
        if (thisCopy.getIsNegative()) {
            if (numberCopy.isBiggerThan(thisCopy)) {
                return processSubtraction(numberCopy, thisCopy, false); //dodatni
            } else {
                return processSubtraction(thisCopy, numberCopy, true);  //ujemny
            }
        } else { 
            if (thisCopy.isBiggerThan(numberCopy)) {
                return processSubtraction(thisCopy, numberCopy, false); //dodatni
            } else {
                return processSubtraction(numberCopy, thisCopy, true);  //ujemny
            }
        }
    } 
    else { //te same znaki
        int length = std::max(thisCopy.getILength(), numberCopy.getILength());
        int amountOfZeros = std::abs(thisCopy.getILength() - numberCopy.getILength());

        if (thisCopy.getILength() > numberCopy.getILength()) {
            fillArrayWithZeros(amountOfZeros, numberCopy);
        } else if (thisCopy.getILength() < numberCopy.getILength()) {
            fillArrayWithZeros(amountOfZeros, thisCopy);
        }

        CNumber result = processAdding(thisCopy, numberCopy, length);
        result.setIsNegative(is_negative); 
        return result;
    }
}

CNumber CNumber::handleSubtractionCase(CNumber &thisCopy, CNumber &numberCopy) const {
    if (numberCopy.getIsNegative()) {
        // -(-x) = + x
        numberCopy.setIsNegative(false);
        return thisCopy + numberCopy;
    } else {
        if (thisCopy.getIsNegative()) {
            // -x - y = - (x+y)
            numberCopy.setIsNegative(true);
            return thisCopy + numberCopy;
        } else {
            if (thisCopy.isBiggerThan(numberCopy)) {
                return processSubtraction(thisCopy, numberCopy, false); //dodatni
            } else {
                return processSubtraction(numberCopy, thisCopy, true);  //ujemny
            }
        }
    }
}

CNumber CNumber::processAdding(const CNumber &number, const CNumber& thisNumber, int iLength) {
    int* result_array = new int[iLength];
    int carry = 0;

    for (int i = iLength - 1; i >= 0; i--) {
        int sum = thisNumber.getPITable()[i] + number.getPITable()[i] + carry;
        carry = sum / DIGIT_DIVIDER;
        result_array[i] = sum % DIGIT_DIVIDER;
    }

    if (carry > 0) {
        int* new_result_array = new int[iLength + 1];
        new_result_array[0] = carry;
        std::copy(result_array, result_array + iLength, new_result_array + 1);
        delete[] result_array;
        return CNumber(new_result_array, iLength + 1, false);
    }

    return CNumber(result_array, iLength, false);
}

CNumber CNumber::processSubtraction(CNumber &biggerNumber, CNumber &lowerNumber, bool isNegative) {
    int i_length = biggerNumber.getILength();
    int* result_array = new int[i_length];

    int difference_in_length = biggerNumber.getILength() - lowerNumber.getILength();
    fillArrayWithZeros(difference_in_length, lowerNumber);

    for (int i = i_length - 1; i >= 0; i--) {
        int diff = biggerNumber.getPITable()[i] - lowerNumber.getPITable()[i];
        if (diff < 0) {
            int j = i - 1;
            while (j >= 0 && biggerNumber.getPITable()[j] == 0) {
                biggerNumber.pi_table[j] = 9;
                j--;
            }
            if (j >= 0) biggerNumber.pi_table[j]--;
            diff += DIGIT_DIVIDER;
        }
        result_array[i] = diff;
    }

    removeLeadingZeros(result_array, i_length);
    return CNumber(result_array, i_length, isNegative);
}

void CNumber::fillArrayWithZeros(int amountOfZeros, CNumber &number) {
    int newLength = number.getILength() + amountOfZeros;
    int* temp = new int[newLength];
    for (int i = 0; i < amountOfZeros; i++) {
        temp[i] = 0;
    }
    for (int i = amountOfZeros; i < newLength; i++) {
        temp[i] = number.getPITable()[i - amountOfZeros];
    }
    delete[] number.pi_table;
    number.pi_table = temp;
}

void CNumber::removeLeadingZeros(int *&numberTable, int &iLength) {
    int firstNonZero = 0;
    while (firstNonZero < iLength - 1 && numberTable[firstNonZero] == 0) {
        firstNonZero++;
    }
    int new_length = iLength - firstNonZero;

    int* new_array = new int[new_length];
    std::copy(numberTable + firstNonZero, numberTable + iLength, new_array);

    delete[] numberTable;
    numberTable = new_array;
    iLength = new_length;
}

void CNumber::reverseTable(int*& array, int iLength) {
    int* reversed_array = new int[iLength];
    for (int i = 0; i < iLength; ++i) {
        reversed_array[i] = array[iLength - 1 - i];
    }
    delete[] array;  
    array = reversed_array;  //nowa tablica na wskaznik
}


bool CNumber::isBiggerThan (const CNumber &number) const {
    if (i_length > number.getILength()) {
        return true; 
    }
    if (i_length < number.getILength()) {
        return false; 
    }

    for (int i = 0; i < i_length; ++i) {
        if (pi_table[i] > number.getPITable()[i]) {
            return true; // This number is bigger
        }
        if (pi_table[i] < number.getPITable()[i]) {
            return false; 
        }
    }

    return false; //rowne
}

bool CNumber::isEqual(const CNumber &number) const {
    if (is_negative != number.getIsNegative()) {
        return false; 
    }

    if (i_length != number.getILength()) {
        return false; 
    }

    for (int i = 0; i < i_length; ++i) {
        if (pi_table[i] != number.getPITable()[i]) {
            return false; 
        }
    }
    return true; 
}



