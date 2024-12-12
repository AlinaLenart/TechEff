#ifndef TREE_H
#define TREE_H

#include <map>
#include "Node.h"
#include <string>

#include "Result.h"

using namespace std;

class Tree {
public:
    Tree();
    Tree(const Tree& other);
    ~Tree();

    Node* getRoot() const;
    void setRoot(Node* root);
    map<string, int> getVariables() const;

    string printPrefix() const;
    Result<Tree*, Error > buildTree(const vector<string>& tokens);
    string getInOrder() const;
    Tree operator+(Tree &other) const;
    Tree& operator=(const Tree& other);
    Tree& operator=(Tree&& other);
    static int getCopyCount();
    static void resetCopyCount();

private:
    Node* root;
    map<string, int> variables;
    static int copyCount;

    void copyChildren(Node* dest, Node* src);
    Result<Node*, Error > buildTreeHelper(const vector<string>& tokens, int& index);
    string printPrefixHelper(Node* node) const;
    string inorderTraversal(Node* node) const;
    Node* findLeaf(Node* node) const;
    Node* findParent(Node* root, Node* child) const;
    Node* copySubtree(Node* node) const;
    void replaceChild(Node* parentNode, Node* oldChild, Node* newChild) const;
    void swap(Tree& other);
    string intToString(int value);
    string getExtraTokensDescription(const vector<string>& tokens, int startIndex);
};

#endif