/*
************************************
*                                  *
*    Darshan Vala                  *
*    U39780959                     *
*                                  *
*                                  *
************************************
*/
#include <iostream>
#include <sstream>
#include "NotationConverter.hpp"
#include "Deque.hpp"
using namespace std;


string NotationConverter::postfixToInfix(string inStr) {
    Deque dq; //initialize

    for (int j = 0; inStr[j] != '\0'; j++)
    {
        if (!isOperand(inStr[j]) && !symbol(inStr[j])) //checks operand and symbol
        {
            throw InvalidCheck("Wrong character");
        }

        if (inStr[j] == ' ') {
            continue; //continue thru space
        }

        if (isOperand(inStr[j])) //checks if operand is there
        {
            string test(1, inStr[j]);

            dq.pushFront(test); //put into deque
        }

        else //show front element, remove front element, show front element, remove front element, insert to the front the paranthesis, tests and element at i
        {
            string test1 = dq.front();
            dq.popFront();
            string test2 = dq.front();
            dq.popFront();
            dq.pushFront("(" + test2 + " " + inStr[j] + " " +
                test1 + ")");
        }
    }

    string final = dq.front();
    return final; //returning the final
}


string NotationConverter::postfixToPrefix(string inStr) {
    Deque dq; //initialize deque
    int sizeCheck = inStr.size(); //string size check

    for (int j = 0; j < sizeCheck; j++) //checks operand and symbol
    {
        if (!isOperand(inStr[j]) && !symbol(inStr[j])) //checks operand and symbol
        {
            throw InvalidCheck("Wrong character"); //throw exception
        }

        if (inStr[j] == ' ') {
            continue; // space check
        }
        //show front element, remove front element, show front element, remove front element, insert to the front the paranthesis, tests and element at i
        if (!isOperand(inStr[j]))
        {
            string test1 = dq.front();
            dq.popFront();
            string test2 = dq.front();
            dq.popFront();
            string space = " ";
            dq.pushFront(inStr[j] + space + test2 + space + test1);

        }

        else
        {
            string test(1, inStr[j]);

            dq.pushFront(test); //push onto the deque

        }


        if ((j == sizeCheck - 1) && (dq.size() == 2)) { //if deque has 2 elements
            string test1 = dq.front();
                dq.popFront();
                string test2 = dq.front();
                dq.popFront();
                dq.pushFront(test2 + " " +
                    test1);

        }
    }


    string final = dq.front(); //front into final
    return final; //return final
}

string NotationConverter::infixToPostfix(string inStr) {
    {
        Deque dq;
        dq.pushFront("end");


        string flag;
        for (int j = 0; inStr[j] != '\0'; j++)
        {

            if (!isOperand(inStr[j]) && !symbol(inStr[j]) &&!(inStr[j] == '(') && !(inStr[j] == ')')) //checks operand and symbol
            {
                throw InvalidCheck("Wrong character"); //throw exception
            }

            if (inStr[j] == ' ') { //check for space
                continue;
            }

            if (isOperand(inStr[j])) {
                flag += inStr[j]; flag += ' '; //add operand to string
            }


            else if (inStr[j] == '(')
                dq.pushFront("("); //if ( add to deque


            else if (inStr[j] == ')') //if )
            {
                while (dq.front() != "end" && dq.front() != "(") //while front is not at the end yet
                {
                string checker = dq.front();
                    dq.popFront();
                    flag += checker + " ";
                }
                if (dq.front() == "(") //if (
                {
                    string checker = dq.front(); //check to front
                    dq.popFront(); //remove front
                }
            }


            else {
                while (dq.front() != "end" && ifPrecedence(inStr[j]) <= ifPrecedence(dq.front()[0])) //while hasnt reached end
                {
                    string checker = dq.front(); //front into checker
                    dq.popFront();
                    flag += checker + " "; //checker plus space
                }
                string test(1, inStr[j]);
                dq.pushFront(test);
            }

        }

        while (dq.front() != "end")  //not at end
        {
            string checker = dq.front();
            dq.popFront(); //remove front
            flag += checker + " "; //checker plus space
        }

        flag.pop_back();
        return flag;

    }
}
string NotationConverter::infixToPrefix(string inStr) {

    return postfixToPrefix(infixToPostfix(inStr));

}

string NotationConverter::prefixToInfix(string inStr) {
    return postfixToInfix(prefixToPostfix(inStr)); //returning the value of pre to post of the string into post to infix
}
string NotationConverter::prefixToPostfix(string inStr) {
    Deque dq; //initialize deque

    int sizeCheck = inStr.size(); //string size check


    for (int j = sizeCheck - 1; j >= 0; j--) { //reading the string from the right side to the left side

        if (!isOperand(inStr[j]) && !symbol(inStr[j])){ //checks operand and symbol
            throw InvalidCheck("Wrong character"); //throw exception
        }
        if (inStr[j] == ' ') { //check space
            continue;
        }

        if (!isOperand(inStr[j])) { //checking operand in string

            //finding front element then removing it
            string test1 = dq.front(); dq.popFront();
            string test2 = dq.front(); dq.popFront();

            //storing the tests with spaces and the element of string at i
            string test = test1 + " " + test2 + " " + inStr[j];


            dq.pushFront(test); //inserting front of test onto deque
        }


        else {


            dq.pushFront(string(1, inStr[j])); //pushing operand back onto the deque
        }
    }

    return dq.front(); //returning front element
}
