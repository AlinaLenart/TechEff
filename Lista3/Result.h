
#ifndef RESULT_H
#define RESULT_H

#include <vector>

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


private:
    T* pc_value;
    vector<E*> v_errors;
    void copyFrom(const Result<T, E>& other);
    void cleanup();
    void push_back(E *error);

};


#endif //RESULT_H
