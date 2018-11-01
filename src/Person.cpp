/*
 * Person.cpp
 *
 *  Created on: 21/10/2018
 *      Author: anamargaridarl
 */

#include "Person.h"
#include <iostream>

using namespace std;

void indentp(std::ofstream &outfile, int &indentation)
{
	for(int i = 0; i < indentation; i++)
	{
		outfile << "\t";
	}
}


////////////////////////////////////////////////////////////////////////////
//////////////////Person////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
Person::Person(string name,int age,string gender)
{
	this->name=name;
	this->age=age;
	this->gender=gender;
}

string Person::getName()
{
	return name;
}

int Person::getAge()
{
	return age;
}

string Person::getGender()
{
	return gender;
}

void Person::setName(string name)
{
	this->name=name;
}

void Person::setAge(int age)
{
	this->age=age;
}

void  Person::setGender(string gender)
{
	this->gender=gender;
}


void Person::saveClass(ofstream &outfile, int &indentation)
{
	indentp(outfile,indentation);
	outfile << "{" << endl;
	indentation++;
	indentp(outfile,indentation);
	outfile << "\"Name\": " << "\"" << name<<  "\"" << "," <<  endl;
	indentp(outfile,indentation);
	outfile << " \"Age\": "<< "\"" << age  << "\"" << "," <<  endl;
	indentp(outfile,indentation);
	outfile << " \"Gender\": "<< "\"" << gender  << "\""  << "," << endl;
}

////////////////////////////////////////////////////////////////////////////
double calculateEndHour(double startinghour, int duration)
{
	return startinghour + 0.5*duration;
}



////////////////////////////////////////////////////////////////////////////
//////////////////Teacher///////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////

Teacher::Teacher(string name, int age, string gender):Person(name,age,gender)
{}

void Teacher::setLesson(Lesson lesson)
{
	/*
	 * startingHour and endHour are related to reservation to set in vector
	 * resStart and resEnd are related to the reservations in the vector
	 */

	double startingHour, endHour;
	int duration;

	duration = lesson.getDuration();
	startingHour = lesson.getStartingHour();

	endHour = calculateEndHour(startingHour, duration);

//	if(CheckAvailable(lessons,startingHour,endHour)==0)
	this->lessons.push_back(&lesson);
}

vector<Lesson*> Teacher::getLessons()
{
	return lessons;
}


void Teacher::saveClass(ofstream &outfile, int &indentation)
{
	Person::saveClass(outfile,indentation);

	indentation++;
	indentp(outfile,indentation);
	outfile<< "\"lessons\": ";
	outfile << "["<< endl;
	for(size_t i= 0; i < lessons.size(); i++)
	{
		int in  = indentation;
		//reservations.at(i)->loadClass();
		indentp(outfile,in);
		outfile << " , ";
		in++;
	}
	indentp(outfile,indentation);
	outfile << "]"<< endl;

	indentation--;
	indentp(outfile,indentation);
	outfile<<"}"<< endl;

}

////////////////////////////////////////////////////////////////////////////
//////////////////User//////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////

User::User(string name,int age,string gender, bool isGold, string assignedTeacher):Person(name,age,gender)
{
	this->isGold = isGold;
	this->assignedTeacher = assignedTeacher;
	reports.resize(12);
}

void User::makeGold()
{
	isGold = true;
}

void User::stopGold()
{
	isGold = false;
}

bool User::getisGold()
{
	return isGold;
}

Report User::getReport(int month)
{
	if(month > 12)
		throw(IncorrectMonth());

	if(reports.at(month -1) == 0)
	{
		throw(ReportNotAvailable(month));
	}
	else
		return *reports.at(month -1);
}

void User::setReport(Report report, int month)
{
	if(month > 12)
			throw(IncorrectMonth());

	if(reports.at(month-1)!=0)
	{
		throw(ReportAlreadyExists(month));
	}
	else
	{
		reports.at(month-1)= &report;
	}
}


void User::setReservation(Reservation* reservation)
{
	/*
	 * startingHour and endHour are related to reservation to set in vector
	 * resStart and resEnd are related to the reservations in the vector
	 */

	double startingHour, endHour;
	int duration;

	duration = reservation->getDuration();
	startingHour = reservation->getStartingHour();

	endHour = calculateEndHour(startingHour, duration);

	if(CheckAvailable(reservations,startingHour,endHour, reservation->getDay(), reservation->getMonth())==0)
		reservations.push_back(reservation);
}

vector<Reservation*> User::getReservations()
{
	return reservations;
}

string User::getTeacher()
{
	return this->assignedTeacher;
}


void User::saveClass(ofstream &outfile, int &indentation)
{
	Person::saveClass(outfile, indentation);

	indentp(outfile,indentation);
	outfile << "\"isGold\": "<< "\""<< isGold << "\""<< "," << endl;
	indentp(outfile,indentation);
	outfile << "\"Assigned Teacher\": "<< "\""<< assignedTeacher <<"\"" << "," <<  endl;
	indentation++;

	indentp(outfile,indentation);
	outfile<< "\"reports\": ";
	outfile << "["<< endl;
	for(size_t i =0; i < reports.size(); i++)
	{
		int in = indentation;
		if(reports.at(i) != 0)
		{
		//reports.at(i)->loadClass();
		indentp(outfile,in);
		outfile << " , ";
		in++;
		}
	}
	outfile << "]"<< endl;

	indentp(outfile,indentation);
	outfile<< "\"reservations\": ";
	outfile << "["<< endl;
	for(size_t i =0; i < reservations.size(); i++)
	{
		int in  = indentation;
		//reservations.at(i)->loadClass();
		indentp(outfile,in);
		outfile << " , ";
		in++;
	}
	indentp(outfile,indentation);
	outfile << "]"<< endl;

	indentp(outfile,indentation);
	outfile<< "\"invoices\": ";
	outfile << "["<< endl;
	for(size_t i =0; i < invoices.size(); i++)
	{
		int in  = indentation;
		//invoices.at(i)->loadClass();
		indentp(outfile,in);
		outfile << " , ";
		in++;
	}
	indentp(outfile,indentation);
	outfile << "]"<< endl;

	indentation--;
	indentation--;
	indentp(outfile,indentation);
	outfile<<"}"<< endl;

}




