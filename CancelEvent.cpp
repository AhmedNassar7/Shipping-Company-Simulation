#pragma once
#include "CancelEvent.h"

CancelEvent::CancelEvent(int C, int h, int m): Events(h,m) {
	ID = C;
	type = 'X';
}

void CancelEvent::Execute(Company* pC) {
	pC->CancelCargo(ID);	
}