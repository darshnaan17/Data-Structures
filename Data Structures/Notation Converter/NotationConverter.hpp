/*
************************************
*                                  *
*    Darshan Vala                  *
*    U39780959                     *
*                                  *
*                                  *
************************************
*/
#ifndef NOTATIONCONVERTER_H
#define NOTATIONCONVERTER_H

#include "NotationConverterInterface.hpp"
#include "Deque.hpp"
#include <string>


class NotationConverter: public NotationConverterInterface
{

public:
    std::string postfixToInfix(std::string inStr);
    std::string postfixToPrefix(std::string inStr);

    std::string infixToPostfix(std::string inStr);
    std::string infixToPrefix(std::string inStr);

    std::string prefixToInfix(std::string inStr);
    std::string prefixToPostfix(std::string inStr);

    //operators precedence
int ifPrecedence(char order)
{
     if (order == '*' || order == '/')
        return false;
    else if(order == '+' || order == '-')
        return true;
    else{
        return -1;
    }
}

//check letters
bool isOperand(char letter) {
	return (letter >= 'a' && letter <= 'z') | (letter >= 'A' && letter <= 'Z');
}
//find symbol or operators
bool symbol(char op) {
    return ((op == '+') | (op == '-') | (op == '*') | (op == '/') | (op == ' '));
}

};
// invalid
class InvalidCheck {
 private:
	string invalidMsg;
public:
	InvalidCheck(const string& invalid)
		: invalidMsg(invalid) {}
	string getError() { return invalidMsg; }

};

#endif
