#include "Tree.h"
#include "Node.h"
#include "Constants.h"
#include <iostream>
#include <set>
#include <sstream>
#include <string>
#include <vector>
#include <cmath>

Tree::Tree() : root(nullptr), invalidInput(false) {}
Tree::~Tree() { delete root; }

Tree::Tree(const Tree& other)
    : root(nullptr), invalidInput(other.invalidInput), variables(other.variables) {
    if (other.root) {
        root = new Node(*other.root);  //kopia node roota
        copyChildren(root, other.root);  // Recursively copy all children
    }
}

Node* Tree::getRoot() const { return root; }
map<string, int> Tree::getVariables() const { return variables; }

void Tree::copyChildren(Node* dest, Node* src) {
    if (!src || !dest) return;

    for (Node* child : src->children) {
        Node* newChild = new Node(*child);  // kopia dzieci
        dest->addChild(newChild);
        copyChildren(newChild, child);  // po kolei rekursja kopiuje dzieci wglab
    }
}

void Tree::buildTree(const vector<string>& tokens) {
    int index = 0;
    root = buildTreeHelper(tokens, index);
    if (root == nullptr || invalidInput) {
        cout << "Invalid input expression." << std::endl;
    }
}

Node* Tree::buildTreeHelper(const vector<string>& tokens, int& index) { //todo zmien nazwe na recursive
    if (index >= tokens.size()) return nullptr;

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
            variables[token] = DEFAULT_FILL_VALUE; //difultowo daje 1
        }
        //uklada alfabetycznie bo to mapa
        return new Node(VARIABLE, token);
    }
    //token to stala liczbowa 5, 3, 7265
    else if (isdigit(token[0])) {
        return new Node(atoi(token.c_str())); //ascii na int
    }

    // token jest niepoprawny lub pusta lista
    else {
        std::cout << "ERROR: Invalid token encountered: " << token << std::endl;
        invalidInput = true; //flaga bledu
        return nullptr;
    }
}

void Tree::printPrefixHelper(Node* node) const {
    if (!node) return;
    cout << node->value << " ";
    for (size_t i = 0; i < node->children.size(); ++i) {
        printPrefixHelper(node->children[i]);
    }
}

void Tree::printPrefix() const {
    printPrefixHelper(root);
    cout << endl;
}

string Tree::inorderTraversal(Node* node) const {
    if (node == nullptr) return string("");

    string result;

    // sin or cos
    if (node->value == SINUS_SYMBOL || node->value == COSINUS_SYMBOL) {
        result += node->value + "(";
        if (!node->children.empty()) {
            result += inorderTraversal(node->children[0]);
        }
        result += ")";
    } else {
        // +, -, *, /
        if (node->children.size() > 1) {
            result += "(";
            result += inorderTraversal(node->children[0]); // Left child
            result += " " + node->value + " "; // Operator
            result += inorderTraversal(node->children[1]); // Right child
            result += ")";
        }
        // lisc
        else {
            result += node->value;
        }
    }

    return result;
}


string Tree::getInOrder() const {
    return inorderTraversal(root);
}

void Tree::vars() const {
    for (map<string, int>::const_iterator it = variables.begin(); it != variables.end(); ++it) {
        cout << it->first << " "; // klucz czyli nazwa zmiennej
    }
    cout << endl;
}


double Tree::compHelper(Node* node) {
    if (!node) return 0;

    if (node->type == CONSTANT) {
        //before: return atoi(node->value.c_str());
        char* end;
        long value = strtol(node->value.c_str(), &end, BASE);  // base 10 for decimal numbers

        if (*end != '\0') { // sprawdzenie czy konwersja powiodla sie
            std::cerr << "ERROR: Invalid constant value '" << node->value << "' in expression." << std::endl;
            invalidInput = true;
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

void Tree::comp(const std::vector<int>& values) {
    if (values.size() != variables.size()) {
        std::cout << "ERROR: Number of values provided: "<<values.size()<<" does not match the number of variables: "<<variables.size()<< std::endl;
        return;
    }

    int i = 0;
    for (std::map<std::string, int>::iterator it = variables.begin(); it != variables.end(); ++it) {
        it->second = values[i++];
    }

    int result = compHelper(root);
    std::cout << "Result: " << result << std::endl;
}

Tree Tree::operator+(Tree& other) const {
    // Jeśli jedno z drzew jest puste, zwracamy drugie (kopia)
    if (!this->root) return other;
    if (!other.root) return *this;

    Tree result = *this; // Kopia bieżącego drzewa
    Node* targetLeaf = findLeaf(result.root); // Znajdź liść do zamiany

    if (targetLeaf) {
        Node* parentNode = findParent(result.root, targetLeaf); // Znajdź rodzica liścia
        if (parentNode) {
            // Stwórz kopię `other.root` i jego dzieci
            Node* newSubtree = copySubtree(other.root);

            // Zamień liść na nowe poddrzewo
            replaceChild(parentNode, targetLeaf, newSubtree);

            // Usuń stary liść
            delete targetLeaf;
        }
    }

    return result;
}

// Kopiuje całe poddrzewo
Node* Tree::copySubtree(Node* node) const {
    if (!node) return nullptr;
    Node* copy = new Node(*node); // Kopia węzła
    for (Node* child : node->children) {
        copy->addChild(copySubtree(child)); // Rekurencyjnie kopiuj dzieci
    }
    return copy;
}

// Zamienia dziecko `oldChild` na `newChild` w `parentNode`
void Tree::replaceChild(Node* parentNode, Node* oldChild, Node* newChild) const {
    if (!parentNode || !oldChild || !newChild) return;

    for (size_t i = 0; i < parentNode->children.size(); ++i) {
        if (parentNode->children[i] == oldChild) {
            parentNode->children[i] = newChild;
            return;
        }
    }
}


Node* Tree::findParent(Node* root, Node* child) const{
    if (root == nullptr) return nullptr;

    for (Node* node : root->children) {
        if (node == child) {
            return root;
        }
        Node* foundParent = findParent(node, child);
        if (foundParent) return foundParent;
    }

    return nullptr;
}


Node* Tree::findLeaf(Node* node) const {
    if (!node) return nullptr;

    if (node->isLeaf()) {
        return node;
    }

    for (Node* child : node->children) {
        Node* leaf = findLeaf(child);
        if (leaf) {
            return leaf;
        }//is not nullptr
    }

    return nullptr;
}

Tree& Tree::operator=(const Tree& other) {
    if (this == &other) {
        return *this;
    }

    Tree temp(other);
    swap(temp);
    return *this;
}

void Tree::swap(Tree& other) {
    std::swap(root, other.root);
    std::swap(invalidInput, other.invalidInput);
    std::swap(variables, other.variables);
}







/*

void Tree::comp(const vector<int>& varValues) {
    if (varValues.size() != variables.size()) {
        std::cout << "ERROR: The number of values does not match the number of variables." << std::endl;
        return;
    }

    string inorderExpr = getInOrder();
    cout<<inorderExpr<<endl;
    completeVariablesWithValues(varValues);
    double result = evaluateMathExpression(inorderExpr);
    std::cout << "Result: " << result << std::endl;
}

void Tree::completeVariablesWithValues(const vector<int>& varValues) {
    map<string, int>::iterator it = variables.begin();
    int i = 0;

    // Update each variable in the map with corresponding value from varValues
    while (it != variables.end() && i < varValues.size()) {
        it->second = varValues[i];  // Set the map's value to the value in varValues
        ++it;
        ++i;
    }
}


double Tree::evaluateMathExpression(const string& expression) const {
    std::istringstream exprStream(expression);

    double result = 0;
    double temp;
    char op = '+';

    while (exprStream >> temp) {

        if (op == '+') result += temp;
        else if (op == '-') result -= temp;
        else if (op == '*') result *= temp;
        else if (op == '/') result /= temp;

        exprStream >> op;  // Get next operator
    }

    return result;
}
*/
