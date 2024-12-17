#include "ExpressionMenu.h"

using namespace std;

int main() {
    // ExpressionMenu reader;
    // reader.startMenu();

    Tree::resetCopyCount();

    Tree tree1;
    Tree tree2;

    cout << "Tree tree3 = tree1;"<<endl;
    Tree tree3 = tree1;
    cout << "tree3 = tree2;"<<endl;
    tree3 = tree2;

    cout << "Copy count (after copy operations): " << Tree::getCopyCount() << endl;

    Tree::resetCopyCount();

    cout << "Tree tree4 = std::move(tree1);"<<endl;
    Tree tree4 = std::move(tree1);
    cout << "tree4 = std::move(tree2);"<<endl;
    tree4 = std::move(tree2);

    cout << "Copy count (after move operations): " << Tree::getCopyCount() << endl;

    Tree::resetCopyCount();

    Tree tree5;
    Tree tree6;
    Tree tree7;
    Tree tree8;
    Tree tree9;

    tree5 = tree5 + tree6 + tree7 + tree8 + tree9;
    cout << "tree5 = tree5 + tree6 + tree7 + tree8 + tree9;"<<endl;
    cout << "Copy count (after + operations): " << Tree::getCopyCount()<<endl;
    return 0;







    return 0;
}
