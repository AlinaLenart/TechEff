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

    cout << "Copy count (after copy operations): " << Tree::getCopyCount() << endl;

    Tree::resetCopyCount();

    Tree tree4 = std::move(tree1);
    tree4 = std::move(tree2);

    cout << "Copy count (after move operations): " << Tree::getCopyCount() << endl;

    return 0;







    return 0;
}
