#include "Truck.h"
#include "Company.h"
#include <cmath>

Truck::Truck(int t, int s, int capacity, int j, int time,int id) {
	SetType(t);
	SetMaintainceTime(time);
	SetTruckCapacity(capacity);
	SetJournies(j);
	SetSpeed(s);
	IDTruck = id;
	status = 1;
	CargoType = -1;
	Cargos = new PriorityQueue<Cargo*>;
	pC = new Company;
	DepartureHour = 0;
	DepartureDay = 0;
	CargoCount = 0;
	Distance = 0;
	LoadTime = 0;
	J_Count = 0;
	CheckTime = 0;
	TotalDeliveredCargos = 0;
	LoadDay = 0;
	LoadHour = 0;
	arrivaled = false;

}
Truck::~Truck() {
	delete Cargos;
	delete pC;
}
bool Truck::GetCheckUp() {
	return (J_Count == Journies);
}
void Truck::SetCurrentJournies(int J)
{
	J_Count = J;
}
void Truck::IncrementCheckTime()
{
	CheckTime++;
}
void Truck::SetCheckTime(int t)
{
	CheckTime = t;
}
bool Truck::DoneMaintenance()
{
	return CheckTime == MaintenanceTime;
}
void Truck::SetJournies(int j) {
	Journies = j;
}
int Truck::GetJournies()const { return Journies; }

bool Truck::Assign(Cargo* C){
	if (TruckCapacity == Cargos->GetCount()) return false;
	bool check = 0;
	if (Cargos->GetCount() == 0) {
		check = 1;
	}
	C->SetTruckID(IDTruck);
	Cargos->enqueue(C, (1 / C->GetDeliveryDist()));
	if (check) {
		LoadTime = 0;
	}
	Distance += C->GetDeliveryDist();
	LoadTime += C->GetLoad();
	CargoCount++;
	return true;
}



PriorityQueue<Cargo*>& Truck::GetCargoQueue() {
	return *Cargos;
}

bool Truck::isFull() {
	if (Cargos->isEmpty()) {
		return false;
	}
	return Cargos->GetCount() == TruckCapacity;
}

bool Truck::ModifyCargoType(int t) {
	if (CargoType == -1) {
		return true;
	}
	else {
		return (CargoType == t);
	}
}
void Truck::SetCargoType(int t) {
	CargoType = t;
}
void Truck::IncrementJournies()
{
	J_Count++;
	TotalJournies++;
}
int Truck::GetTotalJournies() const {
	return TotalJournies;
}
double Truck::GetActiveTime() const
{
	return TotalTruckActiveTime;
}
void Truck::SetDepDay(int d) {
	DepartureDay = d;
}

void Truck::SetArrivalTime(int d, int h)
{
	ArrivalDay = d;
	ArrivalHour = h;

	TotalTruckActiveTime += ((ArrivalDay * 24) + ArrivalHour) - ((LoadDay * 24) + LoadHour);

}

void Truck::SetDepHour(int h) {
	DepartureHour = h;
}

void Truck::SetStatus(int S) {
	status = S;
}

int Truck::GetStatus() const {
	return status;
}

void Truck::SetType(int a)
{
	Type = a;

}
int Truck::Gettype()const
{
	return Type;
}
bool Truck::HasReturned(int d, int h)
{
	int Time = (DepartureDay * 24 + DepartureHour + DeliveryInterval) - (d * 24 + h);
	if (Time <= 0) {
		return true;
	}
	return false;
}
void Truck::SetTruckCapacity(int x)
{
	TruckCapacity = x;
}
int Truck::GetTruckCapacity()const
{
	return TruckCapacity;
}
void Truck::SetMaintainceTime(int x)
{
	MaintenanceTime = x;
}
int Truck::GetMaintainceTime()const
{
	return MaintenanceTime;
}
void Truck::SetSpeed(int x)
{
	Speed = x;
}
void Truck::IncrementDeliveredCargos()
{
	TotalDeliveredCargos++;
}
int Truck::GetCountDeliveredCargos()
{
	return TotalDeliveredCargos;
}
int Truck::GetSpeed()const
{
	return Speed;
}
void Truck::DICalculation() {
	PriorityQueue<Cargo*>* Temp = new PriorityQueue<Cargo*>;
	Cargo* C = new Cargo;
	while (!Cargos->isEmpty()) {
		Cargos->dequeue(C);
		Temp->enqueue(C, 1 / C->GetDeliveryDist());
	}
	FurthestDist = C->GetDeliveryDist();
	DeliveryInterval = round(LoadTime + (2.0 * FurthestDist/Speed));
	while (!Temp->isEmpty()) {
		Temp->dequeue(C);
		Cargos->enqueue(C, 1/C->GetDeliveryDist());
	}
}

int Truck::GetDI() const {
	return DeliveryInterval;
}
ostream& operator << (ostream& out, Truck* c) {
	out << c->GetIDTruck();
	if (c->GetStatus() == 3) {
		if (c->GetCargoType() == 0) {
			out << " [";
			c->GetCargoQueue().PrintList();
			out << "]";
		}
		else if (c->GetCargoType() == 1) {
			out << " (";
			c->GetCargoQueue().PrintList();
			out << ")";
		}
		else {
			out << " {";
			c->GetCargoQueue().PrintList();
			out << "}";
		}
	}
	return out;
}
int Truck::GetIDTruck() const {
	return IDTruck;
}

int Truck::GetCargoType() const {
	return CargoType;
}

int Truck::GetCargoTime() const {
	Cargo* C;
	Cargos->peek(C);
	return C->GetDeliveryDist() / Speed;
}

void Truck::SetStartTime(int d, int h)
{
	StartDay = d;
	StartHour = h;
}

void Truck::SetACCTforCargos()
{
	int Load = 0;
	PriorityQueue<Cargo*> temp;
	Cargo* C;
	while (!Cargos->isEmpty()) {
		Cargos->dequeue(C);
		temp.enqueue(C, (1 / (C->GetDeliveryDist())));
		Load += C->GetLoad();
		C->setACCT(Load);
	}
	while (!temp.isEmpty()) {
		temp.dequeue(C);
		Cargos->enqueue(C, (1 / (C->GetDeliveryDist())));
	}


}

void Truck::SetMoveTime(int moved, int moveh)
{
	Cargo* C;
	PriorityQueue<Cargo*> temp;
	while (!Cargos->isEmpty()) {
		Cargos->dequeue(C);
		C->SetMoveTime(moved, moveh);
		temp.enqueue(C, 1 / GetDI());
	}
	while (!temp.isEmpty()) {
		temp.dequeue(C);
		Cargos->enqueue(C, 1 / GetDI());
	}
}

bool Truck::DeliverCargoList(int d , int h) {
	Cargo* C;
	Truck* T;
	if (CargoCount == 0)return false;
	PriorityQueue<Cargo*> temp = GetCargoQueue();
	if (temp.isEmpty()) {
		return false;
	}
	temp.peek(C);
	double x = d * 24 + h;
	double y = (DepartureHour + 24 * DepartureDay) + ((1.0*C->GetDeliveryDist() / Speed)*1.0)+C->getACCT();
	if ((y-x)<=0) {
		return true;
	}
	return false;
}
bool Truck::TruckisEmpty() {
	if (Cargos->isEmpty()) {
		return true;
	}
	return false;
}
void Truck::setloadtime(int d,int h){
	LoadDay = d;
	LoadHour = h;
}
int Truck::GetFurthestTime() const {
	int time=((LoadDay*24)+LoadHour)+ LoadTime +  (FurthestDist / Speed);
	return time+1;
}
void Truck::setarrived(bool x) {
	arrivaled = x;
}
bool Truck::getarrived() {
	return arrivaled;
}

float Truck::GetTruckUtil(int d, int h)
{
	int N = GetTotalJournies();
	int Current_Day = d;
	int Current_Hour = h;
	float TotalTruckUtil = 0;
	if (N != 0) {
		int tDC = GetCountDeliveredCargos();
		int TC = GetTruckCapacity();
		double tAT = GetActiveTime();
		TotalJournies += N;
		double TSim = double(Current_Day) * 24 + Current_Hour - 1;
		TotalTruckUtil = 1.0 * (tDC * 1.0 / (TC * N * 1.0)) * 1.0 * (tAT / TSim);
	}
	return TotalTruckUtil;
}
