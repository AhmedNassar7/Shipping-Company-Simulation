#pragma once
template<class T>

class PriorityQueueADT
{
public:
	virtual bool isEmpty() const = 0;
	/*virtual bool enqueue(const T& newEntry, const int& priority) = 0;*/
	
	virtual bool enqueue(const T& item, float priority) = 0;
	virtual bool dequeue(T& FrontEntry) = 0;
	virtual bool peek(T& FrontEntry) const = 0;
	virtual ~PriorityQueueADT() { }
};