#include "ExpressionMenu.h"

using namespace std;

int main() {
    // ExpressionMenu reader;
    // reader.startMenu();

    Tree::resetCopyCount();

    Tree tree1;
    Tree tree2;

    Tree tree3 = tree1;
    tree3 = tree2;
    tree1 = tree2 + tree3 + tree3;

    cout << "Copy count (after copy operations): " << Tree::getCopyCount() << endl;

    Tree::resetCopyCount();

    Tree tree4 = move(tree1);
    tree4 = move(tree2);
    tree1 = tree2 + move(tree3) + move(tree4);

    cout << "Copy count (after move operations): " << Tree::getCopyCount() << endl;

    // Tree::resetCopyCount();
    //
    // Tree tree5;
    // Tree tree6;
    // Tree tree7;
    // Tree tree8;
    // Tree tree9;
    //
    // tree5 = tree5 + tree6 + tree7 + tree8 + tree9;
    // cout << "tree5 = tree5 + tree6 + tree7 + tree8 + tree9;"<<endl;
    // cout << "Copy count (after + operations): " << Tree::getCopyCount()<<endl;

    return 0;




}
