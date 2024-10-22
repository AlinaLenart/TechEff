#ifndef CTable_H
#define CTable_H

#include <string>
using namespace std;

const string DEFAULT_TABLE_NAME = "tablica domyslna";
const int DEFAULT_TABLE_LENGTH = 10; //>0

class CTable {
    private:
        string s_name;
        int i_table_length;
        int* pi_table;  

    public:
        CTable();
        CTable(string sName, int iTableLength);
        CTable(CTable &pcOther);

        ~CTable();

        void vSetName(string sName);
        bool bSetNewSize(int iTableLen);

        CTable* pcClone();

        void vPrintTable();
};

#endif 
