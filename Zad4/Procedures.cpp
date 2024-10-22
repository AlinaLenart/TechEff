#include "Procedures.h"

void Procedures::v_mod_tab(CTable *pcTab, int iNewSize) {
    pcTab->bSetNewSize(iNewSize);  /* praca na wskazniku, modyfikuje ORYGINAL */
}

void Procedures::v_mod_tab(CTable cTab, int iNewSize) {
    cTab.bSetNewSize(iNewSize);  /* przekazuje wartosc, modyfikuje KOPIE */
}
