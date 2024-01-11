#pragma once
#include "PromoteEvent.h"
#include "Company.h"

PromoteEvent::PromoteEvent(int h, int m, int C, int cost):Events(h,m) {
	Promote = C;

	setExtra(cost);
}

void PromoteEvent::setExtra(int e) {
	if (e > 0) {
		ExtraMoney = e;
	}
}
int PromoteEvent::getExtra() {
	return ExtraMoney;
}
void PromoteEvent::Execute(Company* pC) {
	pC->PromoteCargo(Promote, ExtraMoney);
}