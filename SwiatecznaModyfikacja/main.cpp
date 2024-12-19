#include <iostream>

using namespace std;

void v_print_chain(int& length) {
    for (int i = 0; i < length; i++) {
        cout << "*-";
    }
    cout << endl;
}

void v_print_chain(int&& length) {
    for (int i = 0; i < length * 2; i++) {
        cout << "*-";
    }
    cout << endl;
}

int main() {
    int i_val = 5;
    v_print_chain(i_val);
    v_print_chain(5);



    return 0;
}



