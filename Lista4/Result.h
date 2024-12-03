
#ifndef RESULT_H
#define RESULT_H

#include <iostream>
#include <vector>
#include <sstream>
#include "Error.h"

using namespace std;

template <typename T, typename E>
class Result {
public:
    Result(const T& value);
    Result(E* error);
    Result(vector<E*>& errors);
    Result(const Result<T, E>& other);

    ~Result();

    static Result<T, E> cOk(const T &cValue);
    static Result<T, E> cFail(E *pcError);
    static Result<T, E> cFail(vector<E *> &vErrors);

    Result<T, E>& operator=(const Result<T, E>& cOther);

    bool bIsSuccess() const;

    T cGetValue();

    vector<E*>& vGetErrors();
    string sGetErrors() const;


private:
    T* pc_value;
    vector<E*> v_errors;
    void copyFrom(const Result<T, E>& other);
    void cleanup();
};


template <typename T, typename E>
Result<T, E>::Result(const T& cValue)
    : pc_value(new T(cValue)), v_errors() {}

template <typename T, typename E>
Result<T, E>::Result(E* pcError)
    : pc_value(NULL), v_errors() {
    if (pcError != NULL) {
        v_errors.push_back(pcError);
    }
}

template <typename T, typename E>
Result<T, E>::Result(vector<E*>& vErrors)
    : pc_value(NULL), v_errors(vErrors) {}


template <typename T, typename E>
Result<T, E>::Result(const Result<T, E>& cOther)
    : pc_value(NULL), v_errors() {
    copyFrom(cOther);
}

template <typename T, typename E>
Result<T, E>::~Result() {
    cleanup();
}

template <typename T, typename E>
Result<T, E> Result<T, E>::cOk(const T& cValue) {
    return Result<T, E>(cValue);
}

template <typename T, typename E>
Result<T, E> Result<T, E>::cFail(E* pcError) {
    return Result<T, E>(pcError);
}

template <typename T, typename E>
Result<T, E> Result<T, E>::cFail(vector<E*>& vErrors) {
    return Result<T, E>(vErrors);
}

template <typename T, typename E>
Result<T, E>& Result<T, E>::operator=(const Result<T, E>& cOther) {
    if (this != &cOther) {
        cleanup();
        copyFrom(cOther);
    }
    return *this;
}

template <typename T, typename E>
bool Result<T, E>::bIsSuccess() const {
    return v_errors.empty();
}

template <typename T, typename E>
T Result<T, E>::cGetValue() {
    if (!bIsSuccess()) {
        return T();
    }
    return *pc_value;
}

template <typename T, typename E>
vector<E*>& Result<T, E>::vGetErrors() {
    return v_errors;
}


template <typename T, typename E>
void Result<T, E>::copyFrom(const Result<T, E>& cOther) {
    if (cOther.pc_value != NULL) {
        pc_value = new T(*cOther.pc_value);
    } else {
        pc_value = NULL;
        for (size_t i = 0; i < cOther.v_errors.size(); ++i) {
            v_errors.push_back(new E(*cOther.v_errors[i]));
        }
    }
}


template <typename T, typename E>
string Result<T, E>::sGetErrors() const {
    stringstream ss;
    for (size_t i = 0; i < v_errors.size(); ++i) {
        ss << "Error " << i + 1 << ": " << v_errors[i]->getDescription() << "\n";
    }
    return ss.str();
}

template <typename T, typename E>
void Result<T, E>::cleanup() {
    delete pc_value;
    pc_value = NULL;
    v_errors.clear();
}



// specjalizacja szablonu klasy
template <typename E>
class Result<void, E> {
public:
    Result();
    Result(E* pcError);
    Result(vector<E*>& vErrors);
    Result(const Result<void, E>& cOther);
    ~Result();

    static Result<void, E> cOk();
    static Result<void, E> cFail(E* pcError);
    static Result<void, E> cFail(vector<E*>& vErrors);

    Result<void, E>& operator=(const Result<void, E>& cOther);

    bool bIsSuccess();
    vector<E*>& vGetErrors();

private:
    vector<E*> v_errors;

    void copyFrom(const Result<void, E>& cOther);
    void cleanup();
};


template <typename E>
Result<void, E>::Result() {}

template <typename E>
Result<void, E>::Result(E* pcError) {
    if (pcError != NULL) {
        v_errors.push_back(pcError);
    }
}

template <typename E>
Result<void, E>::Result(vector<E*>& vErrors)
    : v_errors(vErrors) {}

template <typename E>
Result<void, E>::Result(const Result<void, E>& cOther) {
    copyFrom(cOther);
}

template <typename E>
Result<void, E>::~Result() {
    cleanup();
}

template <typename E>
Result<void, E> Result<void, E>::cOk() {
    return Result<void, E>();
}

template <typename E>
Result<void, E> Result<void, E>::cFail(E* pcError) {
    return Result<void, E>(pcError);
}

template <typename E>
Result<void, E> Result<void, E>::cFail(vector<E*>& vErrors) {
    return Result<void, E>(vErrors);
}

template <typename E>
Result<void, E>& Result<void, E>::operator=(const Result<void, E>& cOther) {
    if (this != &cOther) {
        cleanup();
        copyFrom(cOther);
    }
    return *this;
}

template <typename E>
bool Result<void, E>::bIsSuccess() {
    return v_errors.empty();
}

template <typename E>
vector<E*>& Result<void, E>::vGetErrors() {
    return v_errors;
}

template <typename E>
void Result<void, E>::copyFrom(const Result<void, E>& cOther) {
    v_errors.clear();
    for (size_t i = 0; i < cOther.v_errors.size(); ++i) {
        v_errors.push_back(new E(*cOther.v_errors[i]));
    }
}

template <typename E>
void Result<void, E>::cleanup() {
    v_errors.clear();
}






#endif //RESULT_H
