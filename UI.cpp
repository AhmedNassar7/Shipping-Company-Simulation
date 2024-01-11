#include "UI.h"
#include "Company.h"

void UI::GetFileNameFromUser() {
	cout << "{Welcome to Team 8_11_T04's Shipping Company}\n";
	cout << "-------------------------------------------------------\n";
	cout << "Please Enter the Input File Name: ";
	cin >> filename;
}

void UI::PrintUI(Company* PC) {
	cout << endl << "Current Time (Day:Hour):" << PC->GetCurrentDay() << ":" << PC->GetCurrentHours() << endl;
	cout << PC->GetWaitingNormalCargo().GetCount() + PC->GetWaitingVipCargo().GetCount() + PC->GetWaitingSpecialCargo().GetCount();
	cout << " Waiting Cargos:  ";
	cout << "[";
	PC->GetWaitingNormalCargo().PrintList();
	cout << "] (";
	PC->GetWaitingSpecialCargo().PrintList();
	cout << ")";
	cout << " {";
	PC->GetWaitingVipCargo().PrintList();
	cout << "} ";
	cout << endl << "-------------------------------------------------------" << endl;
	cout << "Loading Trucks:";
	if(PC->GetLoadingNormal())
		cout << PC->GetLoadingNormal()->GetIDTruck();
	cout << "[";
	if (PC->GetLoadingNormal())
		PC->GetLoadingNormal()->GetCargoQueue().PrintList();
	cout << "] ";
	if(PC->GetLoadingSpecial())
		cout << PC->GetLoadingSpecial()->GetIDTruck();
	cout << "(";
	if (PC->GetLoadingSpecial())
		PC->GetLoadingSpecial()->GetCargoQueue().PrintList();
	cout << ") ";
	if (PC->GetLoadingVIP())
		cout << PC->GetLoadingVIP()->GetIDTruck();
	cout << "{";
	if (PC->GetLoadingVIP())
		PC->GetLoadingVIP()->GetCargoQueue().PrintList();
	cout << "} ";
	cout << endl << "-------------------------------------------------------" << endl;
	cout << PC->GetWaitingNormalTruck().GetCount() + PC->GetWaitingVIPTruck().GetCount() + PC->GetWaitingSpecialTruck().GetCount();
	cout << " Empty Truck: ";
	cout << "[";
	PC->GetWaitingNormalTruck().PrintList();
	cout << "] (";
	PC->GetWaitingSpecialTruck().PrintList();
	cout << ")";
	cout << " {";
	PC->GetWaitingVIPTruck().PrintList();
	cout << "} ";
	cout << endl << "-------------------------------------------------------" << endl;
	cout << PC->GetMovingTrucks().GetCount();
	cout << " Moving Trucks:";
	PC->GetMovingTrucks().PrintList();
	cout << endl << "-------------------------------------------------------" << endl;
	cout << PC->GetCheckNormalTruck().GetCount() + PC->GetCheckSpecialTruck().GetCount() + PC->GetCheckVIPTruck().GetCount();
	cout << " In Checkup Trucks: ";
	cout << "[";
	PC->GetCheckNormalTruck().PrintList();
	cout << "] (";
	PC->GetCheckSpecialTruck().PrintList();
	cout << ")";
	cout << " {";
	PC->GetCheckVIPTruck().PrintList();
	cout << "} ";
	cout << endl << "-------------------------------------------------------" << endl;
	cout << PC->GetDeliveredNormalCargo().GetCount() + PC->GetDeliveredVIPCargo().GetCount() + PC->GetDeliveredSpecialCargo().GetCount();
	cout << " Delivered Cargo: ";
	cout << "[";
	PC->GetDeliveredNormalCargo().PrintList();
	cout << "] (";
	PC->GetDeliveredSpecialCargo().PrintList();
	cout << ")";
	cout << " {";
	PC->GetDeliveredVIPCargo().PrintList();
	cout << "} ";
	cout << endl << "-------------------------------------------------------" << endl;
}

string UI::GetFileName() const {
	return filename;
}

void UI::Interactive(Company* PC) {
	int check = cin.get();
	if (check == 10) {
		PrintUI(PC);
		cout << "Press Enter to Continue..." << endl;
	}
}

void UI::PrintMessage(string message) {
	cout << message;
}

string UI::GetUserInput() {
	string x;

	cin >> x;

	return x;
}

void UI::stepbystep(Company* PC) {
	PrintUI(PC);
	Sleep(0);
}
void UI::silent(Company* PC) {
	cout << "Silent Mode\n"
		<< "Simulation Starts...\n"
		<< "Simulation ends, Output file created\n";
};
void UI::Mode() {
	cout << "Please Choose a Mode: " << endl << "1-Interactive Mode" << endl << "2-StepByStep Mode" << endl << "3-Silent Mode " << endl << "Enter Number : " << flush;
	cin >> x;
	SetMode(x);
}
int UI::GetMode() const {
	return x;
}
void UI::SetMode(int h) {
	x = h;
}