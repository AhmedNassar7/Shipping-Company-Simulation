#include "UI.h"
#include "Company.h"
#include <fstream>
#include "Events.h"
#include "PreparationEvent.h"
#include "PromoteEvent.h"
#include "CancelEvent.h"

Company::Company(){
	Event = new LinkedQueue<Events*>;

	WaitingNormalCargo = new LinkedQueue<Cargo*>;
	WaitingSpecialCargo = new LinkedQueue<Cargo*>;
	WaitingVIPCargo = new PriorityQueue<Cargo*>;

	WaitingNormalTruck = new LinkedQueue<Truck*>;
	WaitingSpecialTruck = new LinkedQueue<Truck*>;
	WaitingVIPTruck = new LinkedQueue<Truck*>;

	MovingTrucks = new PriorityQueue<Truck*>;

	CheckNormalTruck = new LinkedQueue<Truck*>;
	CheckSpecialTruck = new LinkedQueue<Truck*>;
	CheckVIPTruck = new LinkedQueue<Truck*>;

	DeliveredNormalTruck = new LinkedQueue<Truck*>;
	DeliveredSpecialTruck = new LinkedQueue<Truck*>;
	DeliveredVIPTruck = new PriorityQueue<Truck*>;

	DeliveredNormalCargo = new LinkedQueue<Cargo*>;
	DeliveredSpecialCargo = new LinkedQueue<Cargo*>;
	DeliveredVIPCargo = new LinkedQueue<Cargo*>;
	DeliveredAllCargo = new LinkedQueue<Cargo*>;

	LoadingNormalTruck = NULL;
	LoadingVIPTruck = NULL;
	LoadingSpecialTruck = NULL;

	NumVIP = 0;
	NumNormal = 0;
	NumSpecial = 0;
	Current_Day = 0;
	Current_Hour = 0;
	disable = 0;
	CapacityN = 0;
	CapacityS = 0;
	CapacityV = 0;
	LTS = -1;
	LTN = -1;
	LTV = -1;
	DeliveredS = 0;
	DeliveredN = 0;
	DeliveredV = 0;
	CountAutoP = 0;
	TruckActiveTime = 0;
	TotalTruckActiveTime = 0;
	TotalJournies = 0;
	last = false;
}

Company::~Company() {
	delete Event;

	delete WaitingNormalCargo;
	delete WaitingSpecialCargo;
	delete WaitingVIPCargo;

	delete WaitingNormalTruck;
	delete WaitingSpecialTruck;
	delete WaitingVIPTruck;

	delete MovingTrucks;

	delete CheckNormalTruck;
	delete CheckSpecialTruck;
	delete CheckVIPTruck;

	delete DeliveredNormalTruck;
	delete DeliveredSpecialTruck;
	delete DeliveredVIPTruck;

	delete DeliveredNormalCargo;
	delete DeliveredSpecialCargo;
	delete DeliveredVIPCargo;
}

void Company::SetDisable(bool x) {
	disable = x;
}

bool Company::Load(UI* p) {
	ifstream InFile;
	int SpeedNormal;
	int SpeedSpecial;
	int SpeedVIP;
	int CapacityNormal;
	int CapacitySpecial;
	int CapacityVIP;
	int J;
	int DurNormal;
	int DurSpecial;
	int DurVIP;
	int PromotionLimit;
	int Max;
	int Auto;
	int NumofEvents;
	char EventType;
	char CargoType;
	int EventHour;
	int EventMinute;
	char garbage;
	int CargoID;
	int Cost;
	int LT;
	int Distance;
	UI* pUI = p;
	string file_name;
	
	file_name = pUI->GetFileName();
	InFile.open(file_name + ".txt");
	
	if (!InFile.is_open()) {
		pUI->PrintMessage("Error! File Name Does Not Exist...");
		return false;
	}
	else {
		InFile >> NumNormal;
		InFile >> NumSpecial;
		InFile >> NumVIP;
		InFile >> SpeedNormal;
		InFile >> SpeedSpecial;
		InFile >> SpeedVIP;
		InFile >> CapacityNormal;
		CapacityN = CapacityNormal;
		InFile >> CapacitySpecial;
		CapacityS = CapacitySpecial;
		InFile >> CapacityVIP;
		CapacityV = CapacityVIP;
		InFile >> J;
		InFile >> DurNormal;
		InFile >> DurSpecial;
		InFile >> DurVIP;
		InFile >> PromotionLimit;
		InFile >> Max;
		InFile >> NumofEvents;
		AutoP = PromotionLimit;
		MaxW = Max;
		for (int i = 0; i < NumNormal; i++) {
			Truck *T=new Truck(0,SpeedNormal,CapacityNormal,J,DurNormal,100+i);
			WaitingNormalTruck->enqueue(T);
		}
		for (int i = 0; i < NumSpecial; i++) {
			Truck* T = new Truck(1, SpeedSpecial, CapacitySpecial, J, DurSpecial, 200+i );
			WaitingSpecialTruck->enqueue(T);
		}
		for (int i = 0; i < NumVIP; i++) {
			Truck* T = new Truck(2, SpeedVIP, CapacityVIP, J, DurVIP, 300 + i );
			WaitingVIPTruck->enqueue(T);
		}

		for (int i = 0; i < NumofEvents; i++) {
			InFile >> EventType;

			if (EventType == 'P') {
				InFile >> EventHour;
				InFile >> garbage;
				InFile >> EventMinute;
				InFile >> CargoID;
				InFile >> Cost;
				PromoteEvent* P = new PromoteEvent(EventHour, EventMinute, CargoID, Cost);
				Event->enqueue(P);
			}
			else if (EventType == 'R') {
				InFile >> CargoType;
				InFile >> EventHour;
				InFile >> garbage;
				InFile >> EventMinute;
				InFile >> CargoID;
				InFile >> Distance;
				InFile >> LT;
				InFile >> Cost;
				if (CargoType == 'N') {
					PreparationEvent* P = new PreparationEvent(0, EventHour, EventMinute, CargoID, Distance, LT, Cost);
					Event->enqueue(P);
				}
				if (CargoType == 'S'){
					PreparationEvent* P = new PreparationEvent(1, EventHour, EventMinute, CargoID, Distance, LT, Cost);
					Event->enqueue(P);
				}
				if (CargoType == 'V') {
					PreparationEvent* P = new PreparationEvent(2, EventHour, EventMinute, CargoID, Distance, LT, Cost);
					Event->enqueue(P);
				}
				
			}
			else if (EventType == 'X') {
				InFile >> EventHour;
				InFile >> garbage;
				InFile >> EventMinute;
				InFile >> CargoID;
				CancelEvent* P = new CancelEvent(CargoID, EventHour, EventMinute);
				Event->enqueue(P);
			}
		}
	}
	return true;
}

int Company::GetMaxW() const {
	return MaxW;
}

void Company::InsertCargo(Cargo *C) {
	int type = C->GetType();
	if (type == 0) {
		WaitingNormalCargo->enqueue(C);
	}
	if (type ==1) {
		WaitingSpecialCargo->enqueue(C);
	}
	if (type == 2) {
		WaitingVIPCargo->enqueue(C,C->GetPriority());
	}
}

void Company::CancelCargo(int ID) {
	Cargo *x;
	LinkedQueue<Cargo*> *WaitingNormaltemp= new LinkedQueue<Cargo*>;
	while (!WaitingNormalCargo->isEmpty()) {
		WaitingNormalCargo->dequeue(x);
		if (x->GetID() != ID) {
			WaitingNormaltemp->enqueue(x);
		}
	}
	while (!WaitingNormaltemp->isEmpty()) {
		WaitingNormaltemp->dequeue(x);
		WaitingNormalCargo->enqueue(x);
	}
}

void Company::CheckDelivery() {
	PriorityQueue<Cargo*> C;
}

void Company::WaitToLoad() {
	Cargo* C;
	Truck* T;
	if (!CheckNormalTruck->isEmpty()) {
		CheckNormalTruck->peek(T);
		T->IncrementCheckTime();
		if (T->DoneMaintenance()) {
			CheckNormalTruck->dequeue(T);
			WaitingNormalTruck->enqueue(T);
			T->SetCheckTime(0);
		}
	}
	if (!CheckSpecialTruck->isEmpty()) {
		CheckSpecialTruck->peek(T);
		T->IncrementCheckTime();
		if (T->DoneMaintenance()) {
			CheckSpecialTruck->dequeue(T);
			WaitingSpecialTruck->enqueue(T);
			T->SetCheckTime(0);
		}
	}
	if (!CheckVIPTruck->isEmpty()) {
		CheckVIPTruck->peek(T);
		T->IncrementCheckTime();
		if (T->DoneMaintenance()) {
			CheckVIPTruck->dequeue(T);
			WaitingVIPTruck->enqueue(T);
			T->SetCheckTime(0);
		}
	}

	if (Current_Hour >= 5 && Current_Hour <= 23) {
		if (WaitingNormalCargo->peek(C)) {
			if (WaitingNormalCargo->GetCount() >= CapacityN || ((C->getmaxwait() + C->GetPT() < ((Current_Day * 24) + Current_Hour)))) {
				if (!LoadingNormalTruck && !WaitingNormalTruck->isEmpty()) {
					WaitingNormalTruck->dequeue(T);
					T->setloadtime(Current_Day, Current_Hour);
					LoadingNormalTruck = T;
					T->SetStartTime(Current_Day, Current_Hour);
				}
				else if (WaitingNormalCargo->GetCount() >= CapacityV && !LoadingNormalTruck && !WaitingVIPTruck->isEmpty()) {
					WaitingVIPTruck->dequeue(T);
					T->setloadtime(Current_Day, Current_Hour);
					LoadingNormalTruck = T;
					T->SetStartTime(Current_Day, Current_Hour);
				}
			}
		}
		if (WaitingSpecialCargo->peek(C)) {
			if (WaitingSpecialCargo->GetCount() >= CapacityS || ((C->getmaxwait() + C->GetPT() < ((Current_Day * 24) + Current_Hour)))) {
				if (!LoadingSpecialTruck && !WaitingSpecialTruck->isEmpty()) {
					WaitingSpecialTruck->dequeue(T);
					T->setloadtime(Current_Day, Current_Hour);
					LoadingSpecialTruck = T;
					T->SetStartTime(Current_Day, Current_Hour);
				}
			}
		}
		if (WaitingVIPCargo->peek(C)) {
			if (WaitingVIPCargo->GetCount() >= CapacityV) {
				if (!LoadingVIPTruck && !WaitingVIPTruck->isEmpty()) {
					WaitingVIPTruck->dequeue(T);
					T->setloadtime(Current_Day, Current_Hour);
					LoadingVIPTruck = T;
					T->SetStartTime(Current_Day, Current_Hour);
					T->SetStatus(1);
				}
				else if (WaitingVIPCargo->GetCount() >= CapacityN && !LoadingVIPTruck && !WaitingNormalTruck->isEmpty()) {
					WaitingNormalTruck->dequeue(T);
					T->setloadtime(Current_Day, Current_Hour);
					LoadingVIPTruck = T;
					T->SetStartTime(Current_Day, Current_Hour);
					T->SetStatus(1);
				}
				else if (WaitingVIPCargo->GetCount() >= CapacityS && !LoadingVIPTruck && !WaitingSpecialTruck->isEmpty())
				{
					WaitingSpecialTruck->dequeue(T);
					T->setloadtime(Current_Day, Current_Hour);
					LoadingVIPTruck = T;
					T->SetStartTime(Current_Day, Current_Hour);
					T->SetStatus(1);
				}
			}
			else if (!WaitingVIPTruck->isEmpty()) {
				if (Event->isEmpty() && WaitingVIPCargo->GetCount() < CapacityV && !LoadingVIPTruck) {
					WaitingVIPTruck->dequeue(T);
					T->setloadtime(Current_Day, Current_Hour);
					LoadingVIPTruck = T;
					T->SetStartTime(Current_Day, Current_Hour);
					T->SetStatus(1);
					last = true;
				}
			}
		}
		if (!WaitingNormalTruck->isEmpty() && LoadingNormalTruck) {
			if (LoadingNormalTruck->isFull() && LTN == 0) {
				LoadingNormalTruck->SetStatus(4);
			}
		}
		if (!WaitingSpecialTruck->isEmpty() && LoadingSpecialTruck) {
			if (LoadingSpecialTruck->isFull() && LTS == 0) {
				LoadingSpecialTruck->SetStatus(4);
			}
		}
		if (!WaitingVIPTruck->isEmpty() && LoadingVIPTruck) {
			if (LoadingVIPTruck->isFull() && LTV == 0) {
				LoadingVIPTruck->SetStatus(4);
			}
		}
		
		if (LoadingNormalTruck) {
			if (LoadingNormalTruck->GetStatus() == 1) {
				if (WaitingNormalCargo->peek(C)) {
					if (LoadingNormalTruck->Assign(C)) {
						WaitingNormalCargo->dequeue(C);
						LoadingNormalTruck->SetStatus(2);
						LTN = C->GetLoad();
						LoadingNormalTruck->SetCargoType(0);
					}
				}
			}
		}
		if (LoadingSpecialTruck) {
			if (LoadingSpecialTruck->GetStatus() == 1) {
				if (WaitingSpecialCargo->peek(C)) {
					if (LoadingSpecialTruck->Assign(C)) {
						WaitingSpecialCargo->dequeue(C);
						LoadingSpecialTruck->SetStatus(2);
						LTS = C->GetLoad();
						LoadingSpecialTruck->SetCargoType(1);
					}
				}
			}
		}
		if (LoadingVIPTruck) {
			if (LoadingVIPTruck->GetStatus() == 1) {
				if (WaitingVIPCargo->peek(C)) {
					if (LoadingVIPTruck->Assign(C)) {
						WaitingVIPCargo->dequeue(C);
						LoadingVIPTruck->SetStatus(2);
						LTV = C->GetLoad();
						LoadingVIPTruck->SetCargoType(2);
					}
				}
			}
		}
	}
}

void Company::PrepTruck() {
	if (LTN > 0) {
		LTN--;
	}
	if (LTV > 0) {
		LTV--;
	}
	if (LTS > 0) {
		LTS--;
	}
	if (LTN == 0 && LoadingNormalTruck != nullptr) {
		LoadingNormalTruck->SetStatus(1);
	}
	if (LTS == 0 && LoadingSpecialTruck != nullptr) {
		LoadingSpecialTruck->SetStatus(1);
	}
	if (LTV == 0 && LoadingVIPTruck != nullptr) {
		LoadingVIPTruck->SetStatus(1);
	}
}

void Company::LoadtoMove() {
	Cargo* a = nullptr;
	Cargo* C;
	bool check = false;
	int x = Current_Hour + Current_Day * 24;
	if (LoadingNormalTruck) {
		if (!LoadingNormalTruck->TruckisEmpty()) {
			LoadingNormalTruck->GetCargoQueue().peek(a);
		}
	}
	if (LoadingNormalTruck != nullptr && LTN == 0) {
		if (LoadingNormalTruck->isFull()) {
			Truck* T = LoadingNormalTruck;
			LoadingNormalTruck->SetStatus(3);
			LoadingNormalTruck->SetDepDay(Current_Day);
			LoadingNormalTruck->SetDepHour(Current_Hour);
			T->DICalculation();
			T->SetMoveTime(Current_Day, Current_Hour);
			T->SetACCTforCargos();
			MovingTrucks->enqueue(T, 1 / T->GetDI());
			LoadingNormalTruck = nullptr;
		}
		else if (a) {
			if (Current_Hour + Current_Day * 24 >= (a->getmaxwait() + a->GetPT())) {
				Truck* T = LoadingNormalTruck;
				LoadingNormalTruck->SetStatus(3);
				LoadingNormalTruck->SetDepDay(Current_Day);
				LoadingNormalTruck->SetDepHour(Current_Hour);
				T->DICalculation();
				T->SetMoveTime(Current_Day, Current_Hour);
				T->SetACCTforCargos();
				MovingTrucks->enqueue(T, 1 / T->GetDI());
				LoadingNormalTruck = nullptr;
			}
		}
	}
	if (LoadingSpecialTruck) {
		if (!LoadingSpecialTruck->TruckisEmpty()) {
			LoadingSpecialTruck->GetCargoQueue().peek(a);
		}
	}
	if (LoadingSpecialTruck != nullptr && LTS == 0) {
		if (LoadingSpecialTruck->isFull()) {
			Truck* T = LoadingSpecialTruck;
			LoadingSpecialTruck->SetStatus(3);
			LoadingSpecialTruck->SetDepDay(Current_Day);
			LoadingSpecialTruck->SetDepHour(Current_Hour);
			T->DICalculation();
			T->SetMoveTime(Current_Day, Current_Hour);
			T->SetACCTforCargos();
			MovingTrucks->enqueue(T, 1 / T->GetDI());
			LoadingSpecialTruck = nullptr;
		}
		else if (a) {
			if (Current_Hour + Current_Day * 24 >= (a->getmaxwait() + a->GetPT())) {
				Truck* T = LoadingSpecialTruck;
				LoadingSpecialTruck->SetStatus(3);
				LoadingSpecialTruck->SetDepDay(Current_Day);
				LoadingSpecialTruck->SetDepHour(Current_Hour);
				T->DICalculation();
				T->SetMoveTime(Current_Day, Current_Hour);
				T->SetACCTforCargos();
				MovingTrucks->enqueue(T, 1 / T->GetDI());
				LoadingSpecialTruck = nullptr;
			}
		}

	}
	if (LoadingVIPTruck != nullptr && LTV == 0) {
		if (LoadingVIPTruck->isFull()|| last) {
			LoadingVIPTruck->SetStatus(3);
			LoadingVIPTruck->SetDepDay(Current_Day);
			LoadingVIPTruck->SetDepHour(Current_Hour);
			Truck* T = LoadingVIPTruck;
			T->DICalculation();
			T->SetMoveTime(Current_Day, Current_Hour);
			T->SetACCTforCargos();
			MovingTrucks->enqueue(T, 1 / T->GetDI());
			LoadingVIPTruck = nullptr;
		}
	}
}

void Company::Save() {
	ofstream OutFile;
	Cargo* C;
	int TotalCargoWait = 0;
	int CargoCount = 0;
	OutFile.open("OutputFile.txt");
	OutFile.close();
	OutFile.open("OutputFile.txt", ios::app);
	OutFile << "CDT		ID		PT		WT		TID\n";
	while (!DeliveredAllCargo->isEmpty()) {
		DeliveredAllCargo->dequeue(C);
		int d, h;
		d = C->GetDeliveryDay();
		h = C->GetDeliveryHour();

		OutFile << d << ":" << h << "		" << C->GetID() << "		" << C->GetPTd() << ":" << C->GetPTh() << "		" << C->GetWaitDay() << ":" << C->GetWaitHour() << "		" << C->GetTruckID() << endl;
		CargoCount++;
		TotalCargoWait += C->GetWaitDay() * 24 + C->GetWaitHour();
	}
	int AverageWait = TotalCargoWait / CargoCount;
	int AverageCargoWaitD = AverageWait / 24;
	int AverageCargoWaitH = AverageWait % 24;
	double AutoPpercent = 0;
	if (DeliveredN != 0) {
		AutoPpercent = (CountAutoP * 100.0 / (DeliveredN));
	}
	double AvgTruckUtil = GetAvgTruckUtil();
	double AvgActivePercent = ((1.0*TotalTruckActiveTime) / (((Current_Day * 24.0) + Current_Hour-1)));
	AvgActivePercent = AvgActivePercent / ((NumNormal + NumSpecial + NumVIP)*1.0);
	OutFile << "---------------------------------------------------------------------------\n";
	OutFile << "---------------------------------------------------------------------------\n";
	OutFile << "Cargos: " << DeliveredN + DeliveredS + DeliveredV << " [N: " << DeliveredN << ", S: " << DeliveredS << ", V: " << DeliveredV << "]\n";
	OutFile << "Cargo Avg Wait = " << AverageCargoWaitD << ":" << AverageCargoWaitH << endl;
	OutFile << "Auto-promoted Cargos: " << AutoPpercent << "%\n";
	OutFile << "Trucks: " << NumNormal + NumSpecial + NumVIP << "  [N: " << NumNormal << ", S: " << NumSpecial << ", V: " << NumVIP << "]\n";
	OutFile << "Avg Active Time = " << AvgActivePercent*100 << "%\n";
	OutFile << "Avg Utilization = " << AvgTruckUtil << "%\n";
	
}

double Company::GetAvgTruckUtil() {
	float TotalTruckUtil = 0;
	int TruckCount = NumNormal + NumSpecial + NumVIP;
	Truck* T;
	while (!WaitingNormalTruck->isEmpty()) {
		WaitingNormalTruck->dequeue(T);
		TotalTruckUtil += T->GetTruckUtil(Current_Day, Current_Hour);
		TotalTruckActiveTime += T->GetActiveTime();
	}
	while (!WaitingSpecialTruck->isEmpty()) {
		WaitingSpecialTruck->dequeue(T);
		TotalTruckUtil += T->GetTruckUtil(Current_Day, Current_Hour);
		TotalTruckActiveTime += T->GetActiveTime();
	}
	while (!WaitingVIPTruck->isEmpty()) {
		WaitingVIPTruck->dequeue(T);
		TotalTruckUtil += T->GetTruckUtil(Current_Day, Current_Hour);
		TotalTruckActiveTime += T->GetActiveTime();
	}
	return (TotalTruckUtil * 100.0) / TruckCount;
}

void Company::MovetoWait() {
	Truck* T;
	Cargo* C;
	PriorityQueue<Truck*>* temp=new PriorityQueue<Truck*>;
	if (MovingTrucks->isEmpty()) return;
	while (!MovingTrucks->isEmpty()) {
		MovingTrucks->dequeue(T);
		temp->enqueue(T,1/T->GetDI());
		while (T->DeliverCargoList(Current_Day, Current_Hour)) {
			T->GetCargoQueue().dequeue(C);
			T->IncrementDeliveredCargos();
			C->SetDeliveryTime(Current_Day, Current_Hour);
			if (C->GetType() == 0) {
				DeliveredNormalCargo->enqueue(C);
				DeliveredAllCargo->enqueue(C);
				DeliveredN++;
			}
			if (C->GetType() == 1) {
				DeliveredSpecialCargo->enqueue(C);
				DeliveredAllCargo->enqueue(C);
				DeliveredS++;
			}
			if (C->GetType() == 2) {
				DeliveredVIPCargo->enqueue(C);
				DeliveredAllCargo->enqueue(C);
				DeliveredV++;
			}
		}
	}
	while (!temp->isEmpty()) {
		temp->dequeue(T);
		MovingTrucks->enqueue(T, 1 / T->GetDI());
	}
	MovingTrucks->peek(T);
	if (T->TruckisEmpty()&& !T->getarrived()) {
		T->SetArrivalTime(Current_Day, Current_Hour);
		T->setarrived(true);
	}
	if (T->TruckisEmpty() && T->HasReturned(Current_Day, Current_Hour)) {
		MovingTrucks->dequeue(T);
		T->SetStatus(1);
		T->IncrementJournies();
		int c = T->Gettype();
		T->SetCargoType(-1);
		if (c == 0 && !T->GetCheckUp()) {
			WaitingNormalTruck->enqueue(T);
			T->setarrived(false);
		}
		else if (c == 0 && T->GetCheckUp()) {
			CheckNormalTruck->enqueue(T);
			T->SetCurrentJournies(0);
		}
		if (c == 1 && !T->GetCheckUp()) {
			WaitingSpecialTruck->enqueue(T);
			T->setarrived(false);
		}
		else if (c == 1 && T->GetCheckUp()) {
			CheckSpecialTruck->enqueue(T);
			T->SetCurrentJournies(0);
		}
		if (c == 2 && !T->GetCheckUp()) {
			WaitingVIPTruck->enqueue(T);
			T->setarrived(false);
		}
		else if (c == 2 && T->GetCheckUp()) {
			CheckVIPTruck->enqueue(T);
			T->SetCurrentJournies(0);
		}
	}
}

void Company::InteractiveSim(UI* p) {
	Events* ptr = nullptr;
	UI* pUI = p;
	if (pUI->GetMode() == 3) {
		pUI->silent(this);
	}
	while (!EndSim()) {
		if (!Event->isEmpty()) {
			while (Event->peek(ptr) && ptr->getEH() == Current_Day && ptr->getEM() == Current_Hour) {
				ptr->Execute(this);
				Event->dequeue(ptr);
			}
		}
		if (Current_Day == 0 && Current_Hour == 5) {
			cout << "";
		}
		AutoPo();
		WaitToLoad();
		LoadtoMove();
		MovetoWait();
		PrepTruck();
		if (pUI->GetMode() == 1) {
			pUI->Interactive(this);
		}
		else if (pUI->GetMode() == 2) {
			pUI->stepbystep(this);
		}
		
		if (Current_Hour != 23) {
			Current_Hour++;
		}
		else {
			Current_Hour = 0;
			Current_Day++;
		}	
	}
}

void Company::MaxLoad() {
	Cargo* C;
	int x = Current_Hour + Current_Day * 24;
	if (!WaitingNormalCargo->isEmpty()) {
		WaitingNormalCargo->peek(C);
		int y = C->GetPT();
		if (x - y >= MaxW) { 
			 
			if (!WaitingNormalTruck->isEmpty() && LoadingNormalTruck->GetStatus() == 1 && LoadingNormalTruck->ModifyCargoType(0) && !LoadingNormalTruck->isFull()) {
				WaitingNormalCargo->dequeue(C);
				LoadingNormalTruck->Assign(C);
				LoadingNormalTruck->SetStatus(2);
				LoadingNormalTruck->SetCargoType(0);
				LTN = C->GetLoad();
			}
			else if (!WaitingVIPTruck->isEmpty() && LoadingVIPTruck->GetStatus() == 1 && LoadingVIPTruck->ModifyCargoType(0) && !LoadingVIPTruck->isFull()) {
				WaitingNormalCargo->dequeue(C);
				LoadingVIPTruck->Assign(C);
				LoadingVIPTruck->SetStatus(2);
				LoadingVIPTruck->SetCargoType(0);
				LTV = C->GetLoad();
			}

			else if (LoadingSpecialTruck->GetStatus() == 1 && LoadingSpecialTruck->ModifyCargoType(1) && !LoadingSpecialTruck->isFull()) {
				WaitingSpecialCargo->dequeue(C);
				LoadingSpecialTruck->Assign(C);
				LoadingSpecialTruck->SetStatus(2);
				LoadingSpecialTruck->SetCargoType(1);
				LTS = C->GetLoad();
			  }
		}
	}
	if (!WaitingSpecialCargo->isEmpty() ) {
		WaitingSpecialCargo->peek(C);
		int y = C->GetPT();
		if (x - y >= MaxW) {
			if (!WaitingSpecialTruck->isEmpty() && LoadingSpecialTruck->GetStatus() == 1 && LoadingSpecialTruck->ModifyCargoType(1) && !LoadingSpecialTruck->isFull() ) {
				WaitingSpecialCargo->dequeue(C);
				LoadingSpecialTruck->Assign(C);
				LoadingSpecialTruck->SetStatus(2);
				LoadingSpecialTruck->SetCargoType(1);
				LTS = C->GetLoad();
			}
		}
	}
	
}

void Company::AutoPo() {
	Cargo* C;
	int x = Current_Hour + Current_Day * 24;
	while (WaitingNormalCargo->peek(C)) {
		int y = C->GetPT();
		if (x - y >= AutoP*24) {
			PromoteCargo(C->GetID(), 0);
			CountAutoP++;
		}
		else {
			break;
		}
	}
}

bool Company::EndSim() {
	return (Event->isEmpty() && WaitingNormalCargo->isEmpty() && WaitingSpecialCargo->isEmpty() && WaitingVIPCargo->isEmpty() && MovingTrucks->isEmpty() && !LoadingSpecialTruck && !LoadingNormalTruck && !LoadingVIPTruck && CheckNormalTruck->isEmpty() && CheckSpecialTruck->isEmpty() && CheckVIPTruck->isEmpty());
}

int Company::GetCurrentDay() {
	return Current_Day;
};

int Company::GetCurrentHours() {
	return Current_Hour;
};

void Company::PromoteCargo(int id, int extra) {
	Cargo *C;
	LinkedQueue<Cargo*>* Temp_Normal=new LinkedQueue<Cargo*>;
	while (!WaitingNormalCargo->isEmpty()) {
		WaitingNormalCargo->dequeue(C);
		if (C->GetID() == id) {
			float priority = C->Promote(extra);
			WaitingVIPCargo->enqueue(C, priority);
		}
		else
		{
			Temp_Normal->enqueue(C);
		}
	}
	while (!Temp_Normal->isEmpty()) {
		Temp_Normal->dequeue(C);
		WaitingNormalCargo->enqueue(C);
	}
}

LinkedQueue<Cargo*>& Company::GetWaitingNormalCargo() {
	return *WaitingNormalCargo;
}

LinkedQueue<Cargo*>& Company::GetWaitingSpecialCargo() {
	return *WaitingSpecialCargo;
}

PriorityQueue<Cargo*>& Company::GetWaitingVipCargo() {
	return *WaitingVIPCargo;
}

LinkedQueue<Truck*>& Company::GetWaitingNormalTruck() {
	return *WaitingNormalTruck;
}

LinkedQueue<Truck*>& Company::GetWaitingSpecialTruck() {
	return *WaitingSpecialTruck;
}

LinkedQueue<Truck*>& Company::GetWaitingVIPTruck() {
	return *WaitingVIPTruck;
}

LinkedQueue<Truck*>& Company::GetDeliveredNormalTruck() {
	return *DeliveredNormalTruck;
}

LinkedQueue<Truck*>& Company::GetDeliveredSpecialTruck() {
	return *DeliveredSpecialTruck;
}

PriorityQueue<Truck*>& Company::GetDeliveredVIPTruck() {
	return *DeliveredVIPTruck;
}

LinkedQueue<Cargo*>& Company::GetDeliveredNormalCargo() {
	return *DeliveredNormalCargo;
}

LinkedQueue<Cargo*>& Company::GetDeliveredSpecialCargo() {
	return *DeliveredSpecialCargo;
}

LinkedQueue<Cargo*>& Company::GetDeliveredVIPCargo() {
	return *DeliveredVIPCargo;
}

LinkedQueue<Cargo*>& Company::GetDeliveredAllCargo() {
	return *DeliveredAllCargo;
}

LinkedQueue<Truck*>& Company::GetCheckNormalTruck() {
	return *CheckNormalTruck;
}

LinkedQueue<Truck*>& Company::GetCheckSpecialTruck() {
	return *CheckSpecialTruck;
}

LinkedQueue<Truck*>& Company::GetCheckVIPTruck() {
	return *CheckVIPTruck;
}

PriorityQueue<Truck*>& Company::GetMovingTrucks() {
	return *MovingTrucks;
}

Truck* Company::GetLoadingNormal() {
	return LoadingNormalTruck;
}

Truck* Company::GetLoadingSpecial() {
	return LoadingSpecialTruck;
}

Truck* Company::GetLoadingVIP() {
	return LoadingVIPTruck;
}