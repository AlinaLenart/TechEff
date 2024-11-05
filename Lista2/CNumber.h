#ifndef CNUMBER_H
#define CNUMBER_H

#include <string>

class CNumber {

public:

    CNumber();
    CNumber(int iValue);
    CNumber(const CNumber &pcOther);
    ~CNumber();

    std::string sToStr() const; 
    
    CNumber operator=(int iValue);
    CNumber operator=(const CNumber &number);
    CNumber operator+(int iValue) const;
    CNumber operator+(const CNumber &number) const;
    CNumber operator-(int iValue) const;
    CNumber operator-(const CNumber &number) const;
    CNumber operator*(int iValue);
    CNumber operator*(const CNumber &number);
    CNumber operator/(int iValue);
    CNumber operator/(const CNumber &number);
    
    int getILength() const;
    bool getIsNegative() const;
    const int* getPITable() const;
    void setIsNegative(bool isNegative);

private:
    int i_length;
    int* pi_table;
    bool is_negative;

    CNumber(int *&numberTable, int iLength, bool isNegative);

    CNumber handleAdditionCase(CNumber &thisCopy, CNumber &numberCopy) const;
    CNumber handleSubtractionCase(CNumber &thisCopy, CNumber &numberCopy) const;

    static CNumber processAdding(const CNumber &number, const CNumber &thisNumber, int iLength);
    static CNumber processSubtraction(CNumber &biggerNumber, CNumber &lowerNumber, bool isNegative);

    static void fillArrayWithZeros(int amountOfZeros, CNumber &number);
    static void removeLeadingZeros(int *&numberTable, int &iLength);
    void reverseTable(int *&iArray, int iLength); 

    bool isBiggerThan (const CNumber &number) const;
    bool isEqual(const CNumber &number) const;
};


#endif  
