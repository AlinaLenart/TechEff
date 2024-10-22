#include <iostream>
#include "CTable.h" 

using namespace std;

CTable::CTable() {
    s_name = DEFAULT_TABLE_NAME;
    cout << "bezp: " << s_name << endl;
    if(DEFAULT_TABLE_LENGTH <= 0) {
        cout << "DOMYSLNA dlugosc tablicy <= 0; ustawiono wartosc 1" << endl;
        i_table_length = 1;
    }
    else {
        i_table_length = DEFAULT_TABLE_LENGTH;
    }
    pi_table = new int[i_table_length];
}   

CTable::CTable(string sName, int iTableLength) {
    s_name = sName;
    cout << "parametr: " << s_name << endl;
    if (iTableLength <= 0) {
        cout << "Dlugosc tablicy <= 0; ustawiono wartosc 1" << endl;
        iTableLength = 1;  
    }
    i_table_length = iTableLength;
    pi_table = new int[i_table_length];
}

CTable::CTable(CTable &pcOther) { /*ampesand bo przesylam referencje (operuje bezposrednio na obiekcie) a nie kopie*/
    s_name = pcOther.s_name + "_copy";
    cout << "kopiuj: " << s_name << endl;
    i_table_length = pcOther.i_table_length;
    pi_table = new int[i_table_length];

    for (int i = 0; i < i_table_length; i++) {
        pi_table[i] = pcOther.pi_table[i];
    }
}

CTable::~CTable() { /*destruktor, cel: posprzatac po obiekcie, wywola sie (aut.) przy dealokacji obiektu*/
    if (pi_table != nullptr) {
        delete[] pi_table;
        pi_table = nullptr;  
    }
    cout << "usuwam: " << s_name <<  endl;
}

void CTable::vSetName(string sName) {
    s_name = sName;
}

bool CTable::bSetNewSize(int iTableLen) {
    if (iTableLen <= 0) {
        return false;
    }

    int* newTable = new int[iTableLen];

    int min_length = (iTableLen < i_table_length) ? iTableLen : i_table_length;
    for (int i = 0; i < min_length; i++) {
        newTable[i] = pi_table[i];
    }

    delete[] pi_table; /*alokacja dynamiczna, konieczne aby uniknac wycieku pamieci*/

    i_table_length = iTableLen;
    pi_table = newTable;
    return true;
}

CTable* CTable::pcClone() {
    return new CTable(*this); /*uzycie konstruktora kopiujacego daje bieżący obiekt (*this) */
}

void CTable::vPrintTable(){
    if (pi_table == nullptr) {
        cout << "Tablica '" << s_name << "' została usunięta lub nie jest zainicjalizowana." << endl;
        return;
    }
    cout << s_name << " : ";
    for (int i = 0; i < i_table_length; i++)
    {
        cout << pi_table[i] << " ";
    }
    cout << endl;
}

