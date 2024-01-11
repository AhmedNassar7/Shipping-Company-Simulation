#pragma once
#include "PreparationEvent.h"
#include "Cargo.h"

PreparationEvent::PreparationEvent( int t,int h, int m, int id1, int dist, int load, int cost1): Events(h,m) {
	type= t;
	ID=id1;
	cost=cost1;
	LT=load;
	distance=dist;

}
void PreparationEvent::Execute(Company* pC){
	Cargo *temp= new Cargo(ID,getEH(), getEM(), LT, type, distance, cost,pC->GetMaxW());
	pC->InsertCargo(temp);
	pC->SetDisable(1);
}
