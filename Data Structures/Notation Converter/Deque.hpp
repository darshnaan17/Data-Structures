/*
************************************
*                                  *
*    Darshan Vala                  *
*    U39780959                     *
*                                  *
*                                  *
************************************
*/
#ifndef DEQUE_H
#define DEQUE_H
#include <string>
#include "DLinkedList.hpp"

using namespace std;

 typedef string Elem; //elem type for deque

class Deque {

    private:
    DLinkedList D; // doubly linked list of elements
    int num; // elements num
    public:
    Deque(); // constructor
    int size() const; // size of deque
    bool empty() const; // deque empty
    const Elem& front() const; //first element
    const  Elem& back() const; // last element
    void pushFront(const Elem& e); // insert new first element
    void pushBack(const Elem& e); // insert new last element
    void popFront(); // remove first element
    void popBack(); //remove last element



};
#endif
