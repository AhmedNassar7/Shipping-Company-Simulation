#include "UI.h"
#include <iostream>
#include "PriorityQueue.h"
#include "Cargo.h"
#include "LinkedQueue.h"
#include "Truck.h"
#include "Company.h"
using namespace std;

int main() {
	Company* C = new Company;
	UI* A = new UI;
	A->GetFileNameFromUser();
	if (C->Load(A)) {
		A->Mode();
		C->InteractiveSim(A);
		C->Save();
		int x;
		cin >> x;
	}
	delete C;
	delete A;
	return 0;
}