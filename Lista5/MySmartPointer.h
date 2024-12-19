#ifndef MYSMARTPOINTER_H
#define MYSMARTPOINTER_H
#include <__stddef_null.h>

template <typename T, typename E>
class MySmartPointer {
public:
    explicit MySmartPointer(T *pcPointer);
    MySmartPointer(const MySmartPointer<T, E>& pcOther);
    ~MySmartPointer();
    MySmartPointer<T, E>& operator=(const MySmartPointer<T, E>& pcOther);
    T& operator*();
    T* operator->();
private:
    T *pc_pointer;
    E *pc_counter;
    void copyFrom(const MySmartPointer<T, E>& pcOther);
};



template <typename T, typename E>
MySmartPointer<T, E>::MySmartPointer(T *pcPointer) {
    pc_pointer = pcPointer;
    pc_counter = new E();
    pc_counter->iAdd();
}

template <typename T, typename E>
MySmartPointer<T, E>::MySmartPointer(const MySmartPointer<T, E>& pcOther) {
    copyFrom(pcOther);
}

template <typename T, typename E>
MySmartPointer<T, E>::~MySmartPointer() {
    if (pc_counter->iDec() == 0) {
        delete pc_pointer;
        delete pc_counter;
    }
}

template <typename T, typename E>
T& MySmartPointer<T, E>::operator*() {
    return(*pc_pointer);
}

template <typename T, typename E>
T* MySmartPointer<T, E>::operator->() {
    return(pc_pointer);
}

template <typename T, typename E>
MySmartPointer<T, E>& MySmartPointer<T, E>::operator=(const MySmartPointer<T, E>& pcOther) {
    if (this != &pcOther && pc_pointer != pcOther.pc_pointer) {
        if (pc_counter != NULL && pc_counter->iDec() == 0) {
            delete pc_pointer;
            delete pc_counter;
        }
        copyFrom(pcOther);
    }
    return *this;
}

template <typename T, typename E>
void MySmartPointer<T, E>::copyFrom(const MySmartPointer<T, E>& pcOther) {
    pc_pointer = pcOther.pc_pointer;
    pc_counter = pcOther.pc_counter;
    if (pc_counter) {
        pc_counter->iAdd();
    }
}



#endif //MYSMARTPOINTER_H
