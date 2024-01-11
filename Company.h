#pragma once
#include "UI.h"
#include "Truck.h"
#include "Cargo.h"
#include "Events.h"
#include "PriorityQueue.h"
#include "LinkedQueue.h"
#include <fstream>
class Events;
class UI;
class Company {

    LinkedQueue<Events*>* Event;

    LinkedQueue<Truck*>* WaitingVIPTruck;
    LinkedQueue<Truck*>* WaitingNormalTruck;
    LinkedQueue<Truck*>* WaitingSpecialTruck;

    LinkedQueue<Truck*>* CheckVIPTruck;
    LinkedQueue<Truck*>* CheckNormalTruck;
    LinkedQueue<Truck*>* CheckSpecialTruck;

    PriorityQueue<Truck*>* MovingTrucks;

    PriorityQueue<Truck*>* DeliveredVIPTruck;
    LinkedQueue<Truck*>* DeliveredNormalTruck;
    LinkedQueue<Truck*>* DeliveredSpecialTruck;

    PriorityQueue<Cargo*>* WaitingVIPCargo;
    LinkedQueue<Cargo*>* WaitingNormalCargo;
    LinkedQueue<Cargo*>* WaitingSpecialCargo;

    LinkedQueue<Cargo*>* DeliveredVIPCargo;
    LinkedQueue<Cargo*>* DeliveredNormalCargo;
    LinkedQueue<Cargo*>* DeliveredSpecialCargo;

    LinkedQueue<Cargo*>* DeliveredAllCargo;

    Truck* LoadingNormalTruck;
    Truck* LoadingSpecialTruck;
    Truck* LoadingVIPTruck;

    int NumVIP;
    int NumSpecial;
    int NumNormal;
    int Current_Day;
    int Current_Hour;
    int MaxW;
    bool disable;
    int CapacityN;
    int CapacityS;
    int CapacityV;
    int LTN;
    int LTS;
    int LTV;
    int AutoP;
    int DeliveredN;
    int DeliveredS;
    int DeliveredV;
    int CountAutoP;
    int TruckActiveTime;
    int TotalTruckActiveTime;
    int TotalJournies;
    bool last;
   
public:
	
    Company();

    void SetDisable(bool x);

    void Save();

    bool EndSim();

    bool Load(UI* p);

    double GetAvgTruckUtil();

    void InteractiveSim(UI* p);

    int GetCurrentDay() ;

    int GetCurrentHours();

    void CancelCargo(int ID);

    void PromoteCargo(int id, int extra);

    void InsertCargo(Cargo *C);

    int GetMaxW() const;

    void CheckDelivery();

    void WaitToLoad();

    void MovetoWait();
     
    void MaxLoad();
    void AutoPo();
    LinkedQueue<Cargo*>& GetWaitingNormalCargo();

    LinkedQueue<Cargo*>& GetWaitingSpecialCargo();

    PriorityQueue<Cargo*>& GetWaitingVipCargo();

    LinkedQueue<Truck*>& GetWaitingNormalTruck();

    LinkedQueue<Truck*>& GetWaitingSpecialTruck();

    LinkedQueue<Truck*>& GetWaitingVIPTruck();

    PriorityQueue<Truck*>& GetMovingTrucks();

    LinkedQueue<Truck*>& GetDeliveredNormalTruck();

    LinkedQueue<Truck*>& GetDeliveredSpecialTruck();

    PriorityQueue<Truck*>& GetDeliveredVIPTruck();

    LinkedQueue<Cargo*>& GetDeliveredNormalCargo();

    LinkedQueue<Cargo*>& GetDeliveredSpecialCargo();
        
    LinkedQueue<Cargo*>& GetDeliveredVIPCargo();
    LinkedQueue<Cargo*>& GetDeliveredAllCargo();

    LinkedQueue<Truck*>& GetCheckNormalTruck();

    LinkedQueue<Truck*>& GetCheckSpecialTruck();

    LinkedQueue<Truck*>& GetCheckVIPTruck();

    Truck* GetLoadingNormal();

    Truck* GetLoadingSpecial();

    Truck* GetLoadingVIP();

    void LoadtoMove();

    void PrepTruck();

    ~Company();
};