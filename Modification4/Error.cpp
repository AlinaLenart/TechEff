#include "Error.h"
#include <string>

Error::Error() : description("Unknown error") {}

Error::Error(const string &s) : description(s) {}

Error::Error(const char *str) {
    description = str;
}

Error::~Error() {}

string Error::getDescription() const {
    return description;
}






