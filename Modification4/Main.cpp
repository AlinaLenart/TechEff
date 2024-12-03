#include "Result.h"
#include "Error.h"
using namespace std;

Result<int*, Error> e_test0(int iValue) {
    if (iValue == 0) {
        return new Error("error!");
    }
    return new int(iValue);

}

Result<double*, Error> e_test1(int iValue) {

    return e_test0(iValue).cToResult<double>(new double(iValue/2.0));
}



int main() {

    cout << e_test1(0).bIsSuccess() << endl;
    cout << e_test1(6).bIsSuccess() << endl;
    cout << e_test0(0).bIsSuccess() << endl;




    return 0;
}
