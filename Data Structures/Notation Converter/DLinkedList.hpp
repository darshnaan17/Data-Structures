/*
************************************
*                                  *
*    Darshan Vala                  *
*    U39780959                     *
*                                  *
*                                  *
************************************
*/
#ifndef DLINKEDLIST_H
#define DLINKEDLIST_H

#include <iostream>
#include <string>

using namespace std;
typedef string Elem; //elem type for deque

class Node { // doubly linked list node
private:
Elem elem; // node element value

//prev and next node
Node* prev;
Node* next;

friend class DLinkedList; // allow DLinkedList access
};




class DLinkedList { // doubly linked list

private:

//head and tail nodes
Node* head;
Node* tail;

protected:
void add(Node* v, const Elem& e); //insert new node before v
void remove(Node* v); // remove node v

public:

DLinkedList(); // constructor
~DLinkedList(); // destructor
void pushToFront(const Elem& e); // add to front of list
void pushToBack(const Elem& e); // add to back of list
bool empty() const; // empty list check
void popFromFront(); // remove from front
void popFromBack(); // remove from back
const Elem& front() const; // get front element
const Elem& back() const; // get back element


};
#endif
