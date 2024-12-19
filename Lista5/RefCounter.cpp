#include "RefCounter.h"

RefCounter::RefCounter() {
    i_count = 0;
}
int RefCounter::iAdd() { return(++i_count); }
int RefCounter::iDec() { return(--i_count); }
int RefCounter::iGet() { return(i_count); }



