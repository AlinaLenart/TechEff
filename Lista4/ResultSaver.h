#ifndef RESULTSAVER_H
#define RESULTSAVER_H

#include "Result.h"
#include "Tree.h"
#include "Error.h"
#include <fstream>
#include <sstream>

using namespace std;

// szablon generyczny dla nie *tree
template <typename T, typename Error>
class ResultSaver {
public:
    static void saveToFile(const Result<T, Error>& result) {
        string fileName;
        cout << "Enter file name to save the result: ";
        cin >> fileName;

        ofstream file(fileName);

        if (file.is_open()) {
            if (result.bIsSuccess()) {
                file << "SUCCESS: \n";
            } else {
                file << "FAILURE: \n";

                typename vector<Error>::const_iterator it;
                for (it = result.vGetErrors().begin(); it != result.vGetErrors().end(); ++it) {
                    file << it->getDescription() << "\n";
                }
            }

            file.close();
            cout << "Result saved to " << fileName << endl;
        } else {
            cout << "Error opening file!" << endl;
        }
    }
};

//specjalizacja
template <typename Error>
class ResultSaver<Tree*, Error> {
public:
    static void saveToFile(Result<Tree*, Error>& result) {
        string fileName;
        cout << "Enter file name to save the result: ";
        cin >> fileName;

        ofstream file(fileName);

        if (file.is_open()) {
            if (result.bIsSuccess()) {
                file << "SUCCESS: \n";
                file << result.cGetValue()->printPrefix();
            } else {
                file << "FAILURE: \n";

                typename vector<Error*>::const_iterator it;
                for (it = result.vGetErrors().begin(); it != result.vGetErrors().end(); ++it) {
                    file << (*it)->getDescription() << "\n";
                }
            }

            file.close();
            cout << "Result saved to " << fileName << endl;
        } else {
            cout << "Error opening file!" << endl;
        }
    }
};

#endif //RESULTSAVER_H
