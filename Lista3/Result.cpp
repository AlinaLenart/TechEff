#include "Result.h"
#include "Error.h"

#include <vector>
#include <iostream>
#include <string>

template <typename T, typename E>
Result<T, E>::Result(const T& cValue)
    : pc_value(new T(cValue)), v_errors(NULL) {}

template <typename T, typename E>
Result<T, E>::Result(E* pcError)
    : pc_value(NULL), v_errors(1, pcError) {} //todo czy dobrze?

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
    return pc_value != NULL;
}

template <typename T, typename E>
T Result<T, E>::cGetValue() {
    if (!bIsSuccess()) {
        return T(); // Return a default-constructed value if Result is a failure
    }
    return *pc_value;
}

template <typename T, typename E>
vector<E*>& Result<T, E>::vGetErrors() {
    if (bIsSuccess()) {
        static vector<E*> emptyErrors;
        return emptyErrors;
    }
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
void Result<T, E>::cleanup() {
    delete pc_value;
    pc_value = NULL;
    for (size_t i = 0; i < v_errors.size(); ++i) {
        delete v_errors[i];
    }
    v_errors.clear();
}

template <typename T, typename E>
void Result<T, E>::push_back(E* pcError) {
    if (bIsSuccess()) {
        return;
    }
    vGetErrors().push_back(pcError);
}

