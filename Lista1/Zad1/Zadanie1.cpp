#include <iostream>
#include "Zadanie1.h" 

using namespace std;

void v_alloc_table_fill_34(int iSize) {

    if (iSize <= 0) {
        cout << "BLAD= rozmiar tablicy <= 0" << endl << endl;
        return;
    }

    int* pTable = new int[iSize];

    for (int i = 0; i < iSize; i++) {
        pTable[i] = FILL_TABLE_VALUE;
    }

    v_print_table(pTable, iSize);

    delete[] pTable;
}

void v_print_table(int* pTable, int iSize) {

    for (int i = 0; i < iSize; i++) {
        cout << pTable[i] << " ";
    }
    cout << endl << endl;

}

//TESTY

void test_negative_size() {
    cout << ">Test na rozmiarze = -2" << endl;
    int rozmiar = -2;
    v_alloc_table_fill_34(rozmiar); 
}

void test_size_1() {
    cout << ">Test na rozmiarze = 1" << endl;
    int rozmiar = 1;
    v_alloc_table_fill_34(rozmiar);
}

void test_size_40() {
    cout << ">Test na rozmiarze = 40" << endl;
    int rozmiar = 40;
    v_alloc_table_fill_34(rozmiar);
}

int main() {
    test_negative_size();
    test_size_1();
    test_size_40();
    return 0;
}



