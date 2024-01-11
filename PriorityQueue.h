#pragma once
#include "PriorityQueueADT.h"
#include "LinkedList.h"
#include "Node.h"
#include <iostream>
using namespace std;

template <typename T>

class PriorityQueue : public PriorityQueueADT<T>{
	Node<T>* rearPtr;
	Node<T>* frontPtr;
	int count = 0;
public:
	bool peek(T& it) const {
		if (isEmpty()) {
			return false;
		}
		it = frontPtr->getItem();
		return true;
	}
	int GetCount() {
		return count;
	}
	PriorityQueue() {
		frontPtr = nullptr;
		rearPtr = nullptr;
	}
	PriorityQueue(const PriorityQueue<T>& LQ)
	{
		Node<T>* NodePtr = LQ.frontPtr;
		if (!NodePtr) 
		{
			frontPtr = rearPtr = nullptr;
			return;
		}
		Node<T>* ptr = new Node<T>(NodePtr->getItem());
		frontPtr = rearPtr = ptr;
		NodePtr = NodePtr->getNext();

		while (NodePtr)
		{
			Node<T>* ptr = new Node<T>(NodePtr->getItem());
			rearPtr->setNext(ptr);
			rearPtr = ptr;
			NodePtr = NodePtr->getNext();
		}
	}
	bool enqueue(const T& it, float priority) {
		Node<T>* newnodePPtr = new Node<T>(it, priority);

		// Insert the new nodeP
		if (isEmpty())
		{
			frontPtr = newnodePPtr;// The PQueue is empty
			rearPtr = newnodePPtr;
			count++;
			return true;
		}

		Node<T>* tmp1 = frontPtr;
		Node<T>* tmp2 = frontPtr->getNext();
		if (tmp1 && !tmp2)// special case if the queue has only one node
		{
			if (tmp1->getpriority() < newnodePPtr->getpriority())
			{
				newnodePPtr->setNext(tmp1);
				frontPtr = newnodePPtr;
				rearPtr = tmp1;
			}
			else
			{
				tmp1->setNext(newnodePPtr);
				rearPtr = newnodePPtr;
			}
		}
		else
		{
			if (newnodePPtr->getpriority() > frontPtr->getpriority())// if number is already bigger than all the numbers insert first
			{
				newnodePPtr->setNext(tmp1);
				frontPtr = newnodePPtr;
				count++;
				return true;
			}
			while (tmp1 && tmp2 && (tmp1->getpriority()) >= (newnodePPtr->getpriority()) && (tmp2->getpriority()) >= (newnodePPtr->getpriority()))// the queue is this condition is already sorted 
			{
				tmp1 = tmp1->getNext();
				tmp2 = tmp2->getNext();
			}
			newnodePPtr->setNext(tmp2);
			tmp1->setNext(newnodePPtr);
		}
		count++;
		return true;
	}
	
	bool isEmpty() const {
		return (frontPtr == nullptr);
	}

	bool dequeue(T& it) {
		if (isEmpty())
			return false;

		Node<T>* nodetobedeleted = frontPtr;
		it = frontPtr->getItem();
		frontPtr = frontPtr->getNext();

		if (nodetobedeleted == rearPtr) {
			rearPtr = nullptr;
		}

		delete nodetobedeleted;
		count--;
		return true;
	}
	void PrintList()
	{
		int i = 0;
		Node<T>* p = frontPtr;
		while (p)
		{
			cout << p->getItem();
			if (count - 1 != i && count != 1) {
				cout << ",";
			}
			p = p->getNext();
			i++;
		}
	}
};