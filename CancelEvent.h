#pragma once
#include "Events.h"
#include "Cargo.h"
class CancelEvent : public Events {
	char type;
	int ID;
public:
	CancelEvent(int C, int h, int m);
	void Execute(Company* pC);
};