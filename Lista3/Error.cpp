#include "Error.h"
#include <string>

Error::Error() : description("Unknown error") {}

Error::Error(const string &s) : description(s) {}

Error::~Error() {}

string Error::getDescription() {
    return description;
}





