#include "Cargo.h"

Cargo::Cargo(int id, int prepd, int preph, int load, int type, int dist, int cost,int maxw) {
	
	ID = id;
	SetPT(prepd, preph);
	SetCost(cost);
	SetDeliveryDist(dist);
	SetLoad(load);
	SetType(type);
	SetPriority();
	maxwait = maxw;
	ACCUnloadTime = 0;
}
Cargo::Cargo(){};
void Cargo:: SetPT(int prepd, int preph) {
	PTd = prepd;
	PTh = preph;
}

void Cargo::SetMoveTime(int moved, int moveh)
{
	MoveDay = moved;
	MoveHour = moveh;
}
void Cargo::setACCT(int x) {
	ACCUnloadTime = x;
}
int Cargo::getACCT() {
	return ACCUnloadTime;
}
int Cargo::GetWaitDay(){
	int x = MoveDay * 24 + MoveHour;
	int y = PTd * 24 + PTh;

	return int((x - y) / 24);
}

void Cargo::SetTruckID(int id)
{
	TruckID = id;
}

int Cargo::GetTruckID() const
{
	return TruckID;
}

int Cargo::GetWaitHour(){
	int x = MoveDay * 24 + MoveHour;
	int y = PTd * 24 + PTh;

	return (x - y) % 24;
}

int Cargo::GetPT() const {
	return PTd * 24 + PTh;
}

int Cargo::GetPTd() const {
	return PTd;
}
int Cargo::getmaxwait() {
	return maxwait;
}
void Cargo::setmaxwait(int x) {
	maxwait = x;
}
int Cargo::GetPTh() const
{
	return PTh;
}
void Cargo::SetLoad(int load_time) {
	Load = load_time;
}

int Cargo::GetLoad() const {
	return Load;
}

void Cargo::SetType(int type) {
	C_Type = type;
}

void Cargo::SetDeliveryTime(int d, int h) {
	DeliveryDay = d;
	DeliveryHour = h;
}

int Cargo::GetDeliveryDay() const {
	return DeliveryDay;
}

int Cargo::GetDeliveryHour() const {
	return DeliveryHour;
}

int Cargo::GetType() const {
	return C_Type;
}

void Cargo::SetDeliveryDist(int dist) {
	DeliveryDistance = dist;
}

double Cargo::GetDeliveryDist() const {
	return DeliveryDistance;
}

void Cargo::SetCost(int c) {
	Cost = c;
}

int Cargo::GetCost() const {
	return Cost;
}

float Cargo::GetPriority() const{
	return Priority;
}

void Cargo::SetPriority() {
	Priority = ((float)Cost) / (DeliveryDistance * Load);
}

float  Cargo::Promote(int Extra_Money) {
	C_Type = 2;

	SetCost(GetCost() + Extra_Money);

	SetPriority();

	return GetPriority();
}

void Cargo::SetID(int id) {
	ID = id;
}

int Cargo::GetID() const {
	return ID;
}
 ostream& operator << (ostream& out, const Cargo *c) {
	 out << c->GetID();
	 return out;
}
