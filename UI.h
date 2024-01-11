#pragma once
#include <iostream>
#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif
#include <iostream>
#include <cstdlib>
using namespace std;
/*
Current Time (Day:Hour):70:9
7 Waiting Cargos: [110,113] (116,118) {119,112,114}
-------------------------------------------------------
4 Loading Trucks: 5[3,4,12,15] 1(6) 7{9,11} 2[5,7]
-------------------------------------------------------
4 Empty Trucks: [4], (10), [6], {8}
-------------------------------------------------------
5 Moving Cargos: 7[45, 52] 12{34, 77, 80}
-------------------------------------------------------
2 In-Checkup Trucks: [2] {3}
-------------------------------------------------------
3 Delivered Cargos: {5} [4] (1)
*/
class Company;
class UI{
	int x;
	string filename;
public:

	void PrintUI(Company* PC);
	
	void Interactive(Company* PC);

	void PrintMessage(string message);

	string GetUserInput();

	void stepbystep(Company* PC);

	void silent(Company* PC);

	void Mode();

	int GetMode() const;

	void SetMode(int h);

	string GetFileName() const;

	void GetFileNameFromUser();
};