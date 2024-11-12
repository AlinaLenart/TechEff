#include "Tree.h"
#include "Node.h"
#include "Constants.h"
#include <iostream>
#include <set>
#include <sstream>
#include <string>
#include <vector>

Tree::Tree() : root(nullptr), invalidInput(false) {}
Tree::~Tree() { delete root; }


void Tree::buildTree(const vector<string>& tokens) {
    int index = 0;
    root = buildTreeHelper(tokens, index);
    if (root == nullptr || invalidInput) {
        std::cout << "Invalid input expression." << std::endl;
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
                std::cout << "Warning: Missing operand, using default value '1'.\n";
                node->addChild(new Node(DEFAULT_FILL_VALUE));
            } else {
                node->addChild(buildTreeHelper(tokens, index));
            }
        }
        return node;
    }
    //token to zmienna a, b, c
    else if (isalpha(token[0])) {
        variables.insert(token);
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
    for (set<string>::const_iterator it = variables.begin(); it != variables.end(); ++it) {
        cout << *it << " ";
    }
    cout << endl;
}



/*
string Tree::replaceVariablesWithValues(const string& expression, const vector<double>& varValues) const {
    string result = expression;

    // For each variable in the list, replace its occurrence in the expression with the corresponding value.
    for (set<string>::const_iterator it = variables.begin(); it != variables.end(); ++it) {
        string var = *it; // Get variable name from the iterator
        string value = to_string(varValues[var]); // Get corresponding value as a string (assuming varValues is a map or similar structure)

        // Replace all occurrences of the variable with its value
        size_t pos = 0;
        while ((pos = result.find(var, pos)) != string::npos) {
            result.replace(pos, var.length(), value);
            pos += value.length();
        }
    }

    return result;
}

void Tree::comp(const vector<double>& varValues) {
    // Check if the number of provided values matches the number of variables
    if (varValues.size() != variables.size()) {
        std::cout << "ERROR: The number of values does not match the number of variables." << std::endl;
        return;
    }

    // Get the inorder expression
    string inorderExpr = getInOrder();

    // Replace variables in the expression with their corresponding values
    string exprWithValues = replaceVariablesWithValues(inorderExpr, varValues);

    // Now, we need to evaluate the expression with replaced variables.
    // We'll use a simple expression evaluator here to handle basic math operations.
    double result = evaluateMathExpression(exprWithValues); // You can implement this evaluator

    std::cout << "Result: " << result << std::endl;
}

double Tree::evaluateMathExpression(const string& expression) const {
    // A very basic evaluator for simple math expressions. You can improve this by using a proper expression parser.
    // For now, we'll use a simple eval function.

    std::istringstream exprStream(expression);
    double result = 0;
    double temp;
    char op = '+';

    while (exprStream >> temp) {
        if (op == '+') result += temp;
        else if (op == '-') result -= temp;
        else if (op == '*') result *= temp;
        else if (op == '/') result /= temp;

        exprStream >> op;  // Get the next operator
    }

    return result;
}
*/
