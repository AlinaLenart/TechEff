#ifndef REFCOUNTER_H
#define REFCOUNTER_H

class RefCounter {
public:
    RefCounter();
    int iAdd();
    int iDec();
    int iGet();
private:
    int i_count;
};



#endif //REFCOUNTER_H
