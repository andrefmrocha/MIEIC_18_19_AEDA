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
#include "Company.h"

#include <iostream>

using namespace std;

int MainIntro()
{
	cout << "-------------Tenis Company---------------"<< endl;
	cout << "                                         "<< endl;
	cout << "Choose option:                           "<< endl;
	cout << "                                         "<< endl;
	cout << "1.New Company                           "<< endl;
	cout << "2.Load Company                            "<< endl;
	cout << "3.Exit                                   "<< endl;
	cout<< "------------------------------------------"<< endl;

	int flag;
	cin>> flag;

	while(flag != 1 && flag != 2 && flag != 3)
	{
		cin.clear();
		cin.ignore(1000, '\n');
		cout << "Error...Try again: "<< endl;
		cin>>flag;
	}

	return flag;

}

int Menu(const int cardValue)
{
	cout << "-------------Company" << cardValue << "---------------" << endl;
	cout << "                                         "<< endl;
	cout << "Choose option:                           "<< endl;
	cout << "                                         "<< endl;
	cout << "1.Add Person                             "<< endl;
	cout << "2.Add Reservation                        "<< endl;
	cout << "3.Increment day                          "<<endl;
    cout << "4.Exit                                   "<<endl;
    cout << "-----------------------------------------"<< endl;

	//cout << "5.Go back--------------------------------"<<endl;


	int flag;
	cin>> flag;

	while(flag!=1 && flag!=2 && flag!=3 && flag !=4)
	{
		cin.clear();
		cin.ignore(1000, '\n');
		cout << "Error...Try again: "<< endl;
		cin>>flag;
	}

	return flag;

}

void DevelopCompany(Company &C)
{

	while (flagMenu != 5) {
		/*if (flagMenu == 4) {
		 flag = 4;
		 break;
		 }*/

		flagMenu = Menu(cardValue);

		//* 1.Person
		//* 2.Reservation
		//* 3.Increment day
		//
		switch (flagMenu) {
		case 1: {
			int flagP;

			cout << "1.Add User" << endl;
			cout << "2.Add Teacher" << endl;
			cout << "3.Go back" << endl;

			cin >> flagP;

			while (flagP != 1 && flagP != 2 && flagP != 3) {
				cin.clear();
				cin.ignore(1000, '\n');
				cout << "Error...Try again: " << endl;
				cin >> flagP;
			}

			if (flagP != 3) {

				cout << "Name: " << endl;
				cin >> name;
				cout << "Age: " << endl;
				cin >> age;
				cout << "Gender" << endl;
				cin >> gender;

				if (flagP == 1) {
					cout << "Gold Card?" << endl;
					cout << "Option: 0.yes 1.no " << endl; //need to add go back

					cin >> isGold;

					if (C.getTeachers().empty()) {
						cout
								<< "Can't added Users.Company needs teachers first."
								<< endl;
						cout << "                                         "
								<< endl;
					} else if (!(C.registerUser(name, age, isGold, gender)))
						cout << "Error adding User. Try again" << endl;

				} else if (flagP == 2) {
					if (!(C.registerTeacher(name, age, gender)))
						cout << "Error adding User. Try again" << endl;
				}
			}

			break;
		}
		case 2: {
			int flagR;

			cout << "1.Add Free class" << endl;
			cout << "2.Add Lesson" << endl;
			cout << "3.Go back" << endl;

			cin >> flagR;

			while (flagR != 1 && flagR != 2 && flagR != 3) {
				cin.clear();
				cin.ignore(1000, '\n');
				cout << "Error...Try again: " << endl;
				cin >> flagR;
			}

			if (flagR == 3)
				break;

			cout << "Month: " << endl;
			cin >> m;
			cout << "Day: " << endl;
			cin >> d;
			cout << "Starting Hour: " << endl;
			cin >> strH;
			cout << "Name of User: " << endl;
			cin >> name;

			if (flagR == 1) {
				//need to choose hot to handle price
				cout << "Duration: " << endl;
				cin >> duration;
				//necessary to handle value entered in duration
				if (!C.makeFree(m, d, strH, duration, name))
					cout << "Error adding Free class. Try again" << endl;

				/*} else if (flagR == 2) {
				 int i = C.getUser(name);

				 //need to choose hot to handle price

				 if(! C.makeLesson(month,day,strHr,name,C.getUsers().at(i)->getTeacher()))
				 cout << "Error adding Lesson. Try again"<< endl;*/

			}

			break;

		}
		case 3: {
			++D;
			break;
		}
		case 4: {
			cout << "Save and exit? " << endl;
			cout << "1.Yes 0.No" << endl;
			cin >> save;

			if (save == 1) {
				//save function
			}
			return 0;

		}
		}

	}

}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



int main()
{
	int cardValue = 1;

	////////////////////////////////////
	///////////////////
	string name,gender;
	int age;
	bool isGold;
	//////////////////
	int m,d,strH, dur;
	//double price;
	//duration -- unsigned int --problem?
	int duration;
    /////////////////
    int save;
    unsigned int year, day,month;
	////////////////////////////////////
	int flag = MainIntro();

	switch (flag)
	{
	case 1:
	{
		cout << "Please enter date (day month year): "<< endl;
		cin>> day;
		cin>> month;
		cin>> year;

		Date D(day,month,year);

		int flagMenu = 0;

		Company C(cardValue, year);
		cardValue++;

		break;

	}
	case 2:
	{
		//load
		break;
	}
	case 3:
	{
		return 0;
		break;
	}
	}

	DevelopCompany(C);

}




