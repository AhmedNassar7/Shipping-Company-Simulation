#pragma once
#include "Events.h"
#include "Cargo.h"
class PreparationEvent : public Events {
	int type;
	int ID;
	int distance;
	int LT;
	int cost;
	
public:
	PreparationEvent(int type,int h, int m, int C, int dist, int load, int cost);
	void Execute(Company* pC);
};