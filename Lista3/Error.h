
#ifndef ERROR_H
#define ERROR_H

#include <string>

using namespace std;

class Error {
public:
    Error();
    Error(const string &s);
    ~Error();
    string getDescription();
private:
    string description;
};


#endif //ERROR_H
