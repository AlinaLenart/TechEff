
#ifndef ERROR_H
#define ERROR_H

#include <string>

using namespace std;

class Error {
public:
    Error();
    Error(const string &s);

    explicit Error(const char * str);

    ~Error();
    string getDescription() const;
private:
    string description;
};


#endif //ERROR_H
