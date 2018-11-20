/*
 * TestesAna.cpp
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
#include <vector>
#include <fstream>

#include <iostream>

using namespace std;

int main()
{
	User Serena("Serena Williams", 37, "feminino", 0, "Naomi Osaka");
	User Ana("Ana Loureiro", 19, "feminino", 1, "Rafael Nadal");
	Teacher Naomi("Naomi Osaka", 21, "feminino");
	Teacher Rafael("Rafael Nadal", 32, "masculino");
	User Ricardo("Ricardo Maria", 23, "masculino", 0, "Rafael Nadal");
	Year A(2018);

	Free *AnaF1 = new Free(2,14,15,2,4);
	Free *AnaF2e1 = new Free(2,14,16,2,3);
	Free *AnaF3 = new Free(1,14,16,3,3);
	Lesson *AnaL1 = new Lesson(1,3,10,2,3);
	Lesson *AnaL2eF1 = new Lesson(2,14,16,2,3);
	Lesson *AnaL3e2 = new Lesson(2,14,15,3,3);

	Lesson *RicardoL1eAL1 = new Lesson(1,3,10,2,3);
	Lesson *RicardoL2 = new Lesson(5,2,10,2,3);

	cout << Ana.getName()<< endl;
	cout << Ana.getisGold()<< endl;
	Ana.setReservation(AnaF3);
	Ana.setReservation(AnaL2eF1);
	Rafael.setLesson(AnaL2eF1);
	//Ana.setReservation(AnaF1);
	Ana.setReservation(AnaL1);
	Rafael.setLesson(AnaL2eF1);
	vector<Reservation *>a;
	vector<Invoice *>b;
	a.push_back(AnaL2eF1);
	a.push_back(AnaL1);
	Invoice *I = new Invoice("Ana Loureiro","Rafael Nadal",a);
	b.push_back(I);


	Report *AnaR1 = new Report("Ana Loureiro","Rafael Nadal",a );
	Ana.setReport(AnaR1,5);
	cout << Ana.getTeacher()<< endl;

	Ricardo.setReservation(RicardoL1eAL1);
	Ricardo.setReservation(RicardoL2);

	ofstream outfile, outfile2;

	outfile.open((Ana.getName() + ".json").c_str());
	outfile2.open((Rafael.getName() + ".json").c_str());

	int indentation = 0;
	Ana.storeInfo(outfile,indentation);
	indentation = 0;
	Rafael.storeInfo(outfile2, indentation);

	ifstream infile, infile2;

	infile.open((Ana.getName() + ".json").c_str());
	infile2.open((Rafael.getName() + ".json").c_str());

	Ana.show();
	Naomi.show();

	User B;
	Teacher T;

	B.loadClass(infile);
	T.loadClass(infile2);

	cout<< B.getName()<< endl;
	cout << T.getName() << endl;

	cout << T.getnStudents() <<endl;
	}




