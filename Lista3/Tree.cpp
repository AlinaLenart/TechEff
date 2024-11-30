#include "Tree.h"
#include "Node.h"
#include "Constants.h"
#include <iostream>
#include <set>
#include <sstream>
#include <string>
#include <vector>
#include <cmath>

using namespace std;

Tree::Tree() : root(NULL) {}
Tree::~Tree() { delete root; }

Tree::Tree(const Tree& other)
    : root(NULL), variables(other.variables) {
    if (other.root) {
        root = new Node(*other.root);  //kopia node roota
        copyChildren(root, other.root);
    }
}

void Tree::buildTree(const vector<string>& tokens) {

    int index = 0;
    root = buildTreeHelper(tokens, index);
    if (index < tokens.size()) {
        cout << "WARNING: Too many tokens in expression" << endl;
        cout << "Ignoring: ";
        for (size_t i = index; i < tokens.size(); ++i) {
             cout << tokens[i] <<"; ";
        }
        cout << endl;
    }
}

Node* Tree::buildTreeHelper(const vector<string>& tokens, int& index) {
    if (index >= tokens.size()) return NULL;

    string token = tokens[index++];

    if (token == "+" || token == "-" || token == "*" || token == "/" || token == SINUS_SYMBOL || token == COSINUS_SYMBOL) {

        int numChildren = (token == SINUS_SYMBOL || token == COSINUS_SYMBOL) ? 1 : 2; // sin i cos mają 1 dziecko, reszta 2
        Node* node = new Node(OPERATOR, token, numChildren);

        for (int i = 0; i < numChildren; ++i) {
            // jesli napotkamy operator z brakiem operandów (np. "+ +")
            if (index >= tokens.size()) {
                cout << "Missing operand, using default value\n";
                node->addChild(new Node(DEFAULT_FILL_VALUE));
            } else {
                node->addChild(buildTreeHelper(tokens, index));
            }
        }
        return node;
    }
    //token to zmienna a, b, c
    else if (isalpha(token[0])) {
        if (variables.find(token) == variables.end()) { //jesli nie znajdzie
            variables[token] = DEFAULT_FILL_VALUE;
        }
        //uklada alfabetycznie bo to mapaa
        return new Node(VARIABLE, token);
    }
    //token to stala liczbowa 5, 3, 7265
    else if (isdigit(token[0])) {
        return new Node(atoi(token.c_str())); //ascii na int
    }

    // token jest niepoprawny lub pusta lista
    else {
        cout << "ERROR: Invalid token encountered: " << token << endl;
        return new Node(CONSTANT, intToString(DEFAULT_FILL_VALUE)); //np ujemna
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

void Tree::vars() const {
    for (map<string, int>::const_iterator it = variables.begin(); it != variables.end(); ++it) {
        cout << it->first << " "; // klucz czyli nazwa zmiennej
    }
    cout << endl;
}

void Tree::comp(const vector<int>& values) {
    if (values.size() != variables.size()) {
        cout << "ERROR: Number of values provided: "<<values.size()<<" does not match the number of variables: "<<variables.size()<< endl;
        return;
    }

    int i = 0;
    for (map<string, int>::iterator it = variables.begin(); it != variables.end(); ++it) {
        it->second = values[i++];
    }

    int result = compHelper(root);
    cout << "Result: " << result << endl;
}

double Tree::compHelper(Node* node) {
    if (!node) return 0;

    if (node->type == CONSTANT) {
        //before: return atoi(node->value.c_str());
        char* end;
        long value = strtol(node->value.c_str(), &end, BASE);  // base 10 for decimal numbers

        if (*end != '\0') { // sprawdzenie czy konwersja powiodla sie
            cerr << "ERROR: Invalid constant value '" << node->value << "' in expression." << endl;
            return 0;
        }

        return static_cast<int>(value);
    }
    if (node->type == VARIABLE) {
        return variables[node->value];
    }
    if (node->type == OPERATOR) {
        if (node->value == "+") {
            return compHelper(node->children[0]) + compHelper(node->children[1]);
        } else if (node->value == "-") {
            return compHelper(node->children[0]) - compHelper(node->children[1]);
        } else if (node->value == "*") {
            return compHelper(node->children[0]) * compHelper(node->children[1]);
        } else if (node->value == "/") {
            int divisor = compHelper(node->children[1]);
            return divisor != 0 ? compHelper(node->children[0]) / divisor : 0;
        } else if (node->value == SINUS_SYMBOL) {
            return sin(compHelper(node->children[0]));
        } else if (node->value == COSINUS_SYMBOL) {
            return cos(compHelper(node->children[0]));
        }
    }
    return 0;
}

Tree Tree::operator+(Tree& other) const {
    if (!this->root) return other;
    if (!other.root) return *this;

    Tree result = *this;
    Node* targetLeaf = findLeaf(result.root);

    if (targetLeaf) {

        Node* parentNode = findParent(result.root, targetLeaf);
        if (parentNode) {

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

    Tree temp(other);
    swap(temp);
    return *this;
}

int Tree::countGreatherThan(int number) const {
    int count = 0;
    countGreatherThanHelper(count, number, root);
    return count;
}


void Tree::countGreatherThanHelper(int &count, int number, Node* node) const {
    if (node == NULL) return;

    if (node->isLeaf() && node->type == CONSTANT) {
        if (stoi(node->value) > number) {
            count++;
        }
        return;
    }

    for (size_t i = 0; i < node->children.size(); ++i) {
        countGreatherThanHelper(count, number, node->children[i]);
    }

}

void Tree::swap(Tree& other) {
    std::swap(root, other.root);
    std::swap(variables, other.variables);
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