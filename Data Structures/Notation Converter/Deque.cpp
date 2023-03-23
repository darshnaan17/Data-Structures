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
#include "Deque.hpp"
using namespace std;




Deque::Deque(){ //constructor
	num = 0; //elements at 0
}

int Deque::size() const //size of deque
{
	return num; //return num of elements
}

bool Deque::empty() const //checks if empty
{

	return (D.empty());
}

const Elem& Deque::front() const //returns element at front
{
	return D.front();

}

const Elem& Deque::back() const  //returns element at front
{
	return D.back();

}

void Deque::pushFront(const Elem& e) //push elements to front
{
	D.pushToFront(e);
	num++; //increment number of elements
}

void Deque::pushBack(const Elem& e) //push elements to back
{
	D.pushToFront(e);
	num++;//increment number of elements
}

void Deque::popFront() //remove elements from front
{
	if (empty())
		throw "Exception error: empty deque"; //throw exception if empty

	D.popFromFront();
	num--; //decrement number of elements
}

void Deque::popBack() //remove elements from back
{
	if(empty())
		throw "Exception error: empty deque";//throw exception if empty

	D.popFromBack();
	num--;//decrement number of elements
}
