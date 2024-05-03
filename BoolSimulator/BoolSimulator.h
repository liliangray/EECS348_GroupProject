#ifndef _BOOL_SIMULATOR_H_
#define _BOOL_SIMULATOR_H_

#include <iostream>
#include <vector>
#include <stack>
#include <string>
#include <algorithm>

class BoolSimulator {

    public:

        BoolSimulator() {} // Constructor

        ~BoolSimulator() {} // Destructor

        
        bool calculate(const std::string& str)
        {
            std::vector<char> vec1; // infix token set
            std::vector<char> vec2; // postfix token set

            tokenize(str, vec1); // tokenize input string
            infixToPostfix(vec1, vec2); // create postfix set from infix set

            bool result = calPostfix(vec2); // evaluate postfix set
            return result;
        }

    private:

        // checks if character is valid boolean value
        bool isBool(const char c) {
            if (c == 'T' || c == 'F' || c == 't' || c == 'f') {
                return true; // return true if valid
            } else {
                return false; // else return false
            }
        }

        // tokenizes input string into infix set of tokens
        void tokenize(const std::string& inp, std::vector<char>& tokens) {
            std::string str = inp; // copy input string
            str.erase(remove_if(str.begin(), str.end(), isspace), str.end()); // remove spaces from string

            for (auto it = str.begin(); it != str.end(); it++) { // iterate through string
                char c = *it; // get char value
                if (*it == '!') { // if 'NOT'
                    if (isBool(*(it+1))) { // if next iterator is bool
                        c = ((*(it+1) == 'T') || (*(it+1) == 't') ? 'F' : 'T'); // negate char value
                        it++; // increment iterator
                    }
                }
                tokens.push_back(c); // push char onto tokens 
            }
        }

        // converts a set of infix tokens to a set of postfix tokens
        void infixToPostfix(std::vector<char>& infix_tokens, std::vector<char>& postfix_tokens) {
            std::stack<char> stack; // stack to hold operators 

            for (auto &e : infix_tokens) {
                // for every element in infix set
                if (isBool(e)) { // if e is an operand
                    postfix_tokens.push_back(e); // add to postfix set
                } else if (e == ')') { // if e is ')'
                    while (!stack.empty() && stack.top() != '(') {
                        // while stack is not empty and top is not '('
                        postfix_tokens.push_back(stack.top()); // add stack top to postfix set
                        stack.pop(); // pop stack
                    }
                    stack.pop(); // pop stack
                } else {
                    stack.push(e); // push e onto stack
                }
            }

            while (!stack.empty()) {
                // while stack is not empty
                postfix_tokens.push_back(stack.top()); // add stack top to postfix set
                stack.pop(); // pop stack
            }
        }

        // computes boolean operation given two operands and one operator 
        bool evalBooleanOperation (const char t1, const char t2, const char opt) {
            // handle unrecognized operands
            if (opt == '!') { // if 'NOT'
                if (!isBool(t2)) { // check t2
                    std::cout << "<Error> Unrecognized operand." << std::endl; // print error msg
                    std::cout << "Goodbye...\n" << std::endl;
                    exit(0); // quit program
                }
            } else { // all other operators
                if (!isBool(t1)) { // check t1
                    std::cout << "<Error> Unrecognized operand." << std::endl; // print error msg
                    std::cout << "Goodbye...\n" << std::endl;
                    exit(0); // quit program
                }
            }
        
            bool o1 = ((t1 == 'T') || (t1 == 't') ? 1 : 0); // convert first token to bool
            bool o2 = ((t2 == 'T') || (t2 == 't') ? 1 : 0); // convert second token to bool

            // switch case for operators
            switch (opt) {
                case ('!'):
                    return !o2; // NOT
                case ('&'):
                    return o1 & o2; // AND
                case('|'):
                    return o1 | o2; // OR
                case('$'):
                    return o1 ^ o2; // XOR
                case('@'):
                    return (o1 == 0 && o2 == 0) ? 1 : (o1 == 1 && o2 == 1) ? 0 : 1; // NAND
                default:
                    // handle unrecognized operators
                    std::cout << "<Error> Unrecognized operator: " << opt << std::endl; // print error msg
                    return 0;
            }
        }

        // calculates the final result from postfix vector
        bool calPostfix(std::vector<char>& postfix_tokens) {
            bool res = (postfix_tokens[0] == 'T') ? 1 : 0; // initialize result to first token in vector

            for (auto it = postfix_tokens.begin(); it != postfix_tokens.end();) { // iterate through postfix vector
                if (!isBool(*it)) { // if operator is found
                    char t1 = *(it-2); // capture operand 1
                    char t2 = *(it-1); // capture operand 2
                    char opt = *it; // capture operator

                    res = evalBooleanOperation(t1, t2, opt); // evaluate boolean expression
                    if (opt == '!') { // if operator is 'NOT'
                        *(it-1) = res ? 'T' : 'F'; // place result before iterator in vec
                    } else {
                        *(it-2) = res ? 'T' : 'F'; // place result 2 spaces before iterator in vec
                        it = postfix_tokens.erase(it-1); // erase index before iterator, increment iterator
                    }   
                    it = postfix_tokens.erase(it); // erase index at iterator, increment iterator
                } else {
                    it++; // increment iterator
                }
            }

            return res;
        }
};

#endif // __BOOL_SIMULATOR_H__
