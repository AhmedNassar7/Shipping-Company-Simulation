#ifndef _NODE
#define _NODE

//First let's declare a single node in the list
template<typename T>
class Node
{
private:
	T item;	// A data item (can be any complex sturcture)
	Node<T>* next;	// Pointer to next node
	float priority; //0->normal 1->special 2->VIP

public:

	Node() //default constructor
	{
		next = nullptr;
		priority = 0;
	}

	Node(T newItem, float p = 0) //non-default constructor
	{
		item = newItem;
		next = nullptr;
		priority = p;
	}

	void setPriority(float p) {
		priority = p;
	}

	float getpriority() const {
		return priority;
	}

	void setItem(T newItem)
	{
		item = newItem;
	} // end setItem

	void setNext(Node<T>* nextNodePtr)
	{
		next = nextNodePtr;
	} // end setNext

	T getItem() const
	{
		return item;
	} // end getItem

	Node<T>* getNext() const
	{
		return next;
	}
}; // end Node

#endif	
