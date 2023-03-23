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
#include "DLinkedList.hpp"
using namespace std;


DLinkedList::DLinkedList() { // constructor

//new for head and tail
head = new Node;
tail = new Node;
head->next = tail; //points to eachother
tail->prev = head;
}
DLinkedList::~DLinkedList() { // destructor
while (!empty()) popFromFront();
delete head; //delete nodes
delete tail;
}
bool DLinkedList::empty() const { //checks if empty
    return (head->next == tail);  //head points to next, equal to tail
}
const Elem& DLinkedList::front() const {
    return head->next->elem; //gets front element
}
const Elem& DLinkedList::back() const {
    return tail->prev->elem; //gets back element
}

// insert new node before v
void DLinkedList::add(Node* v, const Elem& e) {
     Node* u = new Node;
     u->elem = e; // new node for e
     u->next = v; //u points to next stored into v
     u->prev = v->prev; //v prev set to u prev
     v->prev->next= u; //all stored into u
}
void DLinkedList::pushToFront(const Elem& e) {
    add(head->next, e);  //add to front of list
}
void DLinkedList::pushToBack(const Elem& e) {
    add(tail, e); // add to back of list
}

void DLinkedList::remove(Node* v) { // remove node v
Node* u = v->prev; // prev
Node* w = v->next; // after
u->next = w; // u to next is w
w->prev = u; //w to prev is y
delete v;// remove
}

void DLinkedList::popFromFront() { //remove from front
    remove(head->next);
}
void DLinkedList::popFromBack() { // remove from back
remove(tail->prev);
}
