#include <iostream>
#include <climits>

using namespace std;

void v_print_table(int* pTable, int iSize) {
    cout <<"Tablica wydruk: ";

    for (int i = 0; i < iSize; i++) {
        cout << pTable[i] << " ";
    }
    cout << endl;

}

int iMax(int* piTable, int iLength) {
    if (iLength <= 0) {
        cout << "Niepoprawny rozmiar" << endl;
        return -(INT_MAX);
    }
    if (piTable == nullptr) {
        cout << "Niepoprawny wskaznik" << endl;
        return -(INT_MAX);
    }

    int max = piTable[0];

    for (int i = 1; i < iLength; i++) {
        if (piTable[i] > max) {
            max = piTable[i];
        }
    }
    return max;
}

int main(){
    int size = 5;
    int* piTable = new int[size];

    for (int i = 0; i < size; i++)
    {   
        piTable[i] = i + 1;
    }

    v_print_table(piTable, size);

    int max = iMax(piTable, size);
    cout << "Wartosc maksymalna: " << max;

    return 0;
}