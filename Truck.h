#pragma once
#include "PriorityQueue.h"
#include "Cargo.h"
#include <iostream>
using namespace std;
class Company;
class Truck {
	int Type; //(0) Normal (1) Special (2) VIP

	int TruckCapacity, MaintenanceTime, Speed, Journies, DeliveryInterval;

	int IDTruck;

	int J_Count;

	int CargoType;

	int status; // (1) available (2) Loading (3) Maintenance

	int DepartureHour;

	int DepartureDay;

	int ArrivalDay;

	int ArrivalHour;

	int CargoCount;

	int CheckTime;

	PriorityQueue<Cargo*>* Cargos;

	Company* pC;

	int Distance;

	int LoadTime;

	int FurthestDist;

	int TotalDeliveredCargos;

	int TotalJournies;

	int TotalTruckActiveTime;

	int StartDay, StartHour;
	int LoadDay, LoadHour;
	bool arrivaled;

public:

	~Truck();

	Truck(int t, int s, int capacity, int j, int time,int id=0);

	void SetStatus(int S);

	int GetTotalJournies() const;

	double GetActiveTime() const;

	int GetStatus() const;

	void SetType(int a);

	int Gettype()const;

	bool HasReturned(int d, int h);

	void SetStartTime(int d, int h);

	void SetACCTforCargos();

	void SetTruckCapacity(int x);

	int GetTruckCapacity()const;

	void SetMaintainceTime(int x);

	int GetMaintainceTime()const;

	void SetSpeed(int x);

	void IncrementDeliveredCargos();

	int GetCountDeliveredCargos();

	int GetSpeed()const;

	void DICalculation();

	int GetDI() const;
	int GetFurthestTime() const;

	int GetIDTruck() const;

	void SetJournies(int j);

	int GetJournies() const;

	bool Assign(Cargo* C);

	int GetCargoType() const;

	bool ModifyCargoType(int t);

	bool DeliverCargoList(int d,int h);

	int GetCargoTime() const;

	void SetMoveTime(int moved, int moveh);

	PriorityQueue<Cargo*>& GetCargoQueue();

	void SetDepHour(int h);

	void SetDepDay(int d);

	void SetArrivalTime(int d, int h);
	
	bool TruckisEmpty();

	bool isFull();
	
	void SetCargoType(int t);

	void IncrementJournies();

	bool GetCheckUp();

	void SetCurrentJournies(int J);

	void IncrementCheckTime();

	void SetCheckTime(int t);

	bool DoneMaintenance();

	void setloadtime(int d, int h);

	void setarrived(bool f);

	bool getarrived();

	float GetTruckUtil(int d, int h);

	friend ostream& operator << (ostream& out, Truck* c);
};