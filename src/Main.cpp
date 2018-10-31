/*
 * Main.cpp
 *
 *  Created on: 31/10/2018
 *      Author: anamargaridarl
 */

#include "Person.h"
#include "Court.h"
#include "Calendar.h"
#include "Date.h"
#include "Invoice.h"
#include "Report.h"
#include "Reservation.h"

#include <iostream>

using namespace std;

int MainIntro()
{
	cout << "-------------Tenis Company---------------"<< endl;
	cout << "-----------------------------------------"<< endl;
	cout << "Choose option: --------------------------"<< endl;
	cout << "-----------------------------------------"<< endl;
	cout << "1.Load Company --------------------------"<< endl;
	cout << "2.New Company  --------------------------"<< endl;
	cout << "3.Exit-----------------------------------"<< endl;
	cout<< "------------------------------------------"<< endl;

	int flag;
	cin>> flag;

	while(flag!=1||flag!=2 ||flag!=3)
	{
		cin.clear();
		cin.ignore(1000, '\n');
		cout << "Error...Try again: "<< endl;
		cin>>flag;
	}

	return flag;

}

int main()
{
	int flag = MainIntro();

	switch(flag)
	{
	case 1:
	{
		//load company
		break;
	}
	case 2:
	{
		//new company
		break;
	}
	case 3:
	{
		return 0;
	}
	}

}


