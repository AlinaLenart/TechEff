#include <iostream>
#include "CTable.h"
#include "Procedures.h"

int main() {
    
    CTable cTabDefault;
    
    CTable cTabParameter("Tablica parametrowa", 15);

    CTable cTabInvalid("Tablica z ujemna dlugoscia", -5);

    CTable cTabCopied(cTabParameter);
    
    cTabParameter.vSetName("Prosta tablica");
    cTabParameter.vPrintTable();

    cTabInvalid.bSetNewSize(4);
    cTabInvalid.vPrintTable();

    cTabInvalid.bSetNewSize(-5); 

    cout << "v_mod_tab z wartoscia (przekazuje wartosc, modyfikuje KOPIE)" << endl;
    Procedures::v_mod_tab(cTabParameter, 2);
    cTabParameter.vPrintTable();

    cout << endl << "v_mod_tab z referencja (praca na wskazniku, modyfikuje ORYGINAL)" << endl;
    Procedures::v_mod_tab(&cTabParameter, 5);
    cTabParameter.vPrintTable();    

    return 0;
}