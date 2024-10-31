#include <iostream>
#include "Zadanie2_3.h"

using namespace std;

bool b_alloc_table_2_dim(int*** piTable, int iSizeX, int iSizeY) {
    if (iSizeX <= 0 || iSizeY <= 0) {
        cout << "BLAD= rozmiar tablicy <= 0" << endl;
        return false;
    }
    if(piTable == nullptr) {
        return false;
    }

    *piTable = new int*[iSizeX]; /*alokacja dla wskaznikow na wiersze*/
    if (*piTable == nullptr) {
        cout << "BLAD= alokacja dla wierszy nieudana" << endl;
        return false;
    }

    for (int i = 0; i < iSizeX; i++) {
        (*piTable)[i] = new int[iSizeY];

        if ((*piTable)[i] == nullptr) {
            cout << "BLAD= alokacja dla kolumn w wierszu" << i << "nieudana" << endl;

            for (int j = 0; j < i; j++) {
                delete[] (*piTable)[j]; /*unikam wycieku pamieci*/
            }

            delete[] *piTable;
            return false;
        }
    }

    return true;
}

bool b_dealloc_table_2_dim(int** piTable, int iSizeX) {
    if (piTable == nullptr) {
        cout << "Błąd: tablica jest już zdealokowana lub nie została zaalokowana" << endl;
        return false;
    }

    for (int i = 0; i < iSizeX; i++) {
        delete[] (piTable)[i]; /*zwalniam wiersze*/
    }

    delete[] piTable; /*zwalniam tablice wskaznikow */
    
    return true;
}


void fill_table(int** piTable, int iSizeX, int iSizeY) {
    for (int i = 0; i < iSizeX; i++) {
        for (int j = 0; j < iSizeY; j++) {
            piTable[i][j] = j + i; 
        }
    }
}

void display_table(int** piTable, int iSizeX, int iSizeY) {
    cout << "Wydruk tablicy:" << endl;
    for (int i = 0; i < iSizeX; i++) {
        for (int j = 0; j < iSizeY; j++) {
            cout << piTable[i][j] << " ";
        }
        cout << endl;
    }
}

int main() {
    int** pi_table = nullptr; 
    int iSizeX = 5;
    int iSizeY = 3;

    if (b_alloc_table_2_dim(&pi_table, iSizeX, iSizeY)) { /*ampersand zwraca adres*/
        cout << "Tablica o rozmiarach x=" << iSizeX << " na y=" << iSizeY << " zaalokowana." << endl;

        fill_table(pi_table, iSizeX, iSizeY);

        display_table(pi_table, iSizeX, iSizeY);

        if (b_dealloc_table_2_dim(pi_table, iSizeX)) {
            cout << "Dealokacja udana" << endl;
        } else {
            cout << "Dealokacja nieudana" << endl;
        }
    } else {
        cout << "Alokacja nieudana" << endl;
    }

    return 0;
}