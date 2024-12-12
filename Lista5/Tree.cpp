#include "Tree.h"
#include "Node.h"
#include "Constants.h"
#include <iostream>
#include <set>
#include <sstream>
#include <string>
#include <vector>
#include <cmath>

#include "Error.h"
#include "Result.h"

using namespace std;

int Tree::copyCount = 0;

Tree::Tree() : root(NULL) {}
Tree::~Tree() { delete root; }

Tree::Tree(const Tree& other)
    : root(NULL), variables(other.variables) {
    if (other.root) {
        root = new Node(*other.root);  //kopia node roota
        copyChildren(root, other.root);
    }
    ++copyCount;
}

Result<Tree*, Error> Tree::buildTree(const vector<string>& tokens) {
    int index = 0;

    Result<Node*, Error> result = buildTreeHelper(tokens, index);

    if (index < tokens.size()) {
        vector<Error*> errors = result.vGetErrors();
        string description = getExtraTokensDescription(tokens, index);
        errors.push_back(new Error("Too many tokens in expression: " + description));
        return Result<Tree*, Error>::cFail(errors);
    }

    if (result.bIsSuccess()) {
        Node* rootNode = result.cGetValue();
        Tree* tree = new Tree();
        tree->root = rootNode;
        tree->variables = variables;
        return Result<Tree*, Error>::cOk(tree);
    } else {
        vector<Error*> errors = result.vGetErrors();
        return Result<Tree*, Error>::cFail(errors);
    }
}

Result<Node*, Error> Tree::buildTreeHelper(const vector<string>& tokens, int& index) {
    if (index >= tokens.size()) {
        vector<Error*> errors;
        errors.push_back(new Error("Unexpected end of tokens."));
        return Result<Node*, Error>::cFail(errors);
    }

    string token = tokens[index++];

    if (token == "+" || token == "-" || token == "*" || token == "/" || token == SINUS_SYMBOL || token == COSINUS_SYMBOL) {
        int numChildren = (token == SINUS_SYMBOL || token == COSINUS_SYMBOL) ? 1 : 2;

        Node* node = new Node(OPERATOR, token, numChildren);
        vector<Error*> errors;

        for (int i = 0; i < numChildren; ++i) {
            if (index >= tokens.size()) {
                errors.push_back(new Error("Missing operand for operator: " + token));
                //node->addChild(new Node(DEFAULT_FILL_VALUE));
                return Result<Node*, Error>::cFail(errors);
            } else {
                Result<Node*, Error> childResult = buildTreeHelper(tokens, index);
                if (childResult.bIsSuccess()) {
                    node->addChild(childResult.cGetValue());
                } else {
                    vector<Error*> childErrors = childResult.vGetErrors();

                    for (vector<Error*>::iterator it = childErrors.begin(); it != childErrors.end(); ++it) {
                        errors.push_back(&**it);
                    }
                }
            }
        }

        if (errors.empty()) {
            return Result<Node*, Error>::cOk(node);
        } else {
            delete node;
            return Result<Node*, Error>::cFail(errors);
        }
    }
    else if (isalpha(token[0])) {
        if (variables.find(token) == variables.end()) {
            variables[token] = DEFAULT_FILL_VALUE;
        }
        return Result<Node*, Error>::cOk(new Node(VARIABLE, token));
    }
    else if (isdigit(token[0])) {
        return Result<Node*, Error>::cOk(new Node(atoi(token.c_str())));
    }
    else {
        vector<Error*> errors;
        errors.push_back(new Error("Invalid token encountered: " + token));
        return Result<Node*, Error>::cFail(errors);
    }
}


string Tree::printPrefix() const {
    return printPrefixHelper(root);
}

string Tree::printPrefixHelper(Node* node) const {
    if (!node) return string("");

    string result = node->value + " ";

    for (size_t i = 0; i < node->children.size(); ++i) {
        result += printPrefixHelper(node->children[i]);
    }

    return result;
}


string Tree::getInOrder() const {
    return inorderTraversal(root);
}

string Tree::inorderTraversal(Node* node) const {
    if (node == NULL) return string("");

    string result;
    // sin or cos
    if (node->value == SINUS_SYMBOL || node->value == COSINUS_SYMBOL) {
        result += node->value + "(";
        if (!node->children.empty()) {
            result += inorderTraversal(node->children[0]);
        }
        result += ")";
    }
    else {
        // +, -, *, /
        if (node->children.size() > 1) {
            result += "(";
            result += inorderTraversal(node->children[0]); // lewe dziecko
            result += " " + node->value + " "; // operator
            result += inorderTraversal(node->children[1]); // prawe dziecko
            result += ")";
        }
        // lisc
        else {
            result += node->value;
        }
    }

    return result;
}

Tree Tree::operator+(Tree& other) const {
    if (!this->root) return other;
    if (!other.root) return *this;

    Tree result = *this;
    Node* targetLeaf = findLeaf(result.root);

    if (targetLeaf != NULL) {

        Node* parentNode = findParent(result.root, targetLeaf);
        if (parentNode != NULL) {

            Node* newSubtree = copySubtree(other.root); //kopia podrzewa
            replaceChild(parentNode, targetLeaf, newSubtree);
            delete targetLeaf;
        }
    }
    return result;
}

void Tree::replaceChild(Node* parentNode, Node* oldChild, Node* newChild) const {
    if (!parentNode || !oldChild || !newChild) return;

    for (size_t i = 0; i < parentNode->children.size(); ++i) {
        if (parentNode->children[i] == oldChild) {
            parentNode->children[i] = newChild;
            return;
        }
    }
}

Node* Tree::findParent(Node* root, Node* child) const {
    if (root == NULL) return NULL;

    for (size_t i = 0; i < root->children.size(); ++i) {
        Node* node = root->children[i];

        if (node == child) {
            return root;
        }

        Node* foundParent = findParent(node, child);
        if (foundParent) return foundParent;
    }

    return NULL;
}


Node* Tree::findLeaf(Node* node) const {
    if (!node) return NULL;

    if (node->isLeaf()) {
        return node;
    }

    for (size_t i = 0; i < node->children.size(); ++i) {
        Node* leaf = findLeaf(node->children[i]); //szukam rekursja liscia w dzieciach
        if (leaf) {
            return leaf;
        }
    }

    return NULL;
}

Tree& Tree::operator=(const Tree& other) {
    if (this == &other) {
        return *this;
    }
    copyCount++;
    Tree temp(other);
    swap(temp);
    return *this;
}

void Tree::swap(Tree& other) {
    std::swap(root, other.root);
    std::swap(variables, other.variables);
}


Tree& Tree::operator=(Tree&& other) {
    if (this != &other) {
        delete root;
        variables.clear();

        root = other.root;
        other.root = nullptr;

        variables = std::move(other.variables);
        other.variables.clear();
    }
    return *this;
}


void Tree::copyChildren(Node* dest, Node* src) {
    if (!src || !dest) return;

    for (vector<Node*>::const_iterator it = src->children.begin(); it != src->children.end(); ++it) {
        Node* newChild = new Node(**it);
        dest->addChild(newChild);
        copyChildren(newChild, *it);
    }
}

Node* Tree::copySubtree(Node* node) const {
    if (!node) return NULL;

    Node* copy = new Node(*node);

    for (size_t i = 0; i < node->children.size(); ++i) {
        copy->addChild(copySubtree(node->children[i]));
    }

    return copy;
}

string Tree::intToString(int value) {
    stringstream ss;
    ss << value;
    return ss.str();
}

Node* Tree::getRoot() const { return root; }
map<string, int> Tree::getVariables() const { return variables; }

int Tree::getCopyCount() {
    return copyCount;
}

void Tree::resetCopyCount() {
    copyCount = 0;
}

string Tree::getExtraTokensDescription(const vector<string>& tokens, int startIndex) {
    stringstream ss;
    ss << "[";
    for (size_t i = startIndex; i < tokens.size(); ++i) {
        ss << tokens[i];
        if (i < tokens.size() - 1) {
            ss << ", ";
        }
    }
    ss << "]";
    return ss.str();
}
