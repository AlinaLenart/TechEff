#ifndef MYSMARTPOINTER_H
#define MYSMARTPOINTER_H

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
};

class CRefCounter {
public:
    CRefCounter() {
        i_count = 0;
    }
    int iAdd() { return(++i_count); }
    int iDec() { return(--i_count); }
    int iGet() { return(i_count); }
private:
    int i_count;
};

template <typename T, typename E>
MySmartPointer<T, E>::MySmartPointer(T *pcPointer) {
    pc_pointer = pcPointer;
    pc_counter = new E();
    pc_counter->iAdd();
}

template <typename T, typename E>
MySmartPointer<T, E>::MySmartPointer(const MySmartPointer<T, E>& pcOther) {
    pc_pointer = pcOther.pc_pointer;
    pc_counter = pcOther.pc_counter;
    pc_counter->iAdd();
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
    if (this != &pcOther) {
        if (pc_counter->iDec() == 0) {
            delete pc_pointer;
            delete pc_counter;
        }
        pc_pointer = pcOther.pc_pointer;
        pc_counter = pcOther.pc_counter;
        pc_counter->iAdd();
    }
    return *this;
}




#endif //MYSMARTPOINTER_H
