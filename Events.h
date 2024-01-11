#pragma once
#include "UI.h"
#include "Cargo.h"
#include "PriorityQueue.h"
#include "LinkedQueue.h"
#include "Company.h"
class Company;
class Events {
private:
	int EH;
	int EM;
public:
	Events() {
		EH = EM = 0;
	};
	Events(int x, int y) {
		EH = x;
		EM = y;
	}
	int getEH() const {
		return EH;
	};
	int getEM() const {
		return EM;
	};
	virtual void Execute(Company* pC) = 0;
};