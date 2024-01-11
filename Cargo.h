#pragma once
#include <iostream>
using namespace std;

class Cargo {
	int ID;
	int PTd;
	int PTh;
	int Load;
	int C_Type; // (0) Normal (1) Special (2) VIP
	int DeliveryDistance;
	int Cost;
	float Priority;
    int maxwait;
	int DeliveryDay;
	int DeliveryHour;
	int MoveDay;
	int MoveHour;
	int WaitDay;
	int WaitHour;
	int TruckID;
	int ACCUnloadTime;

public:
	Cargo();
	Cargo(int id, int prepd, int preph,int load, int type, int dist, int cost, int maxw=20);
	void setACCT(int x);
	int getACCT();

	void SetPT(int prepd, int preph);

	void SetMoveTime(int moved, int moveh);

	int GetWaitDay();

	void SetTruckID(int id);

	int GetTruckID() const;

	int GetWaitHour();

	int GetPT() const;

	int GetPTd() const;

	int GetPTh() const;

	void SetLoad(int load_time);

	int GetLoad() const;

	void SetType(int type);

	int GetType() const;

	void SetDeliveryDist(int dist);

	double GetDeliveryDist() const;

	void SetCost(int c);

	float Promote(int Extra_Money);

	float GetPriority() const;

	void SetPriority();

	int GetCost() const;

	void SetID(int id);

	void SetDeliveryTime(int d, int h);

	int GetDeliveryHour() const;

	int GetDeliveryDay() const;

	int GetID() const;
	int getmaxwait();
	void setmaxwait(int x);
	friend ostream & operator << (ostream& out, const Cargo* c);
};