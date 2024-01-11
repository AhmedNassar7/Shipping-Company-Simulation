#pragma once
#include "Events.h"
#include "Cargo.h"
#include "PriorityQueue.h"
#include "LinkedQueue.h"
#include "Company.h"

//template <typename T>
class PromoteEvent : public Events {
	int type;
	int Promote;
	int ExtraMoney;
	int distance;
	int LT;
public:
	PromoteEvent(int h, int m, int C, int cost);
	void setExtra(int e);
	int getExtra();
	void Execute(Company* pC);
};