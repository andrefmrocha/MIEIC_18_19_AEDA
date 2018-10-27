/*
 * Person.cpp
 *
 *  Created on: 21/10/2018
 *      Author: anamargaridarl
 */

#include "Person.h"
#include <iostream>

using namespace std;

////////////////////////////////////////////////////////////////////////////
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

////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
double calculateEndHour(double startinghour, int duration)
{
	return startinghour + 0.5*duration;
}

template< class t>
int CheckAvailable(vector<t *> res,double startingHour, double endHour)
{
	for(size_t i =0; i < res.size(); i++)
	{
	double resStart = res.at(i)->getStartingHour();
	double resEnd = calculateEndHour(resStart,res.at(i)->getDuration());

	if(startingHour >= resStart && endHour <= resEnd)
		// tempo da reserva esta em espaço ocupado
		throw(InsideRes());
	else if(startingHour <= resStart && endHour >= resStart)
		//tempo da reserva entra em espaço ocupado
		throw(EndHourInsideRes());
	else if(startingHour >= resStart && endHour >= resEnd)
		//tempo da reserva esta a meio
		throw(StartHourInsideRes());
}
	return 0;
}

////////////////////////////////////////////////////////////////////////////
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

	if(CheckAvailable(lessons,startingHour,endHour)==0)
		lessons.push_back(&lesson);
}

vector<Lesson*> Teacher::getLessons()
{
	return lessons;
}

////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////

User::User(string name,int age,string gender, bool isGold):Person(name,age,gender)
{
	this->isGold = isGold;
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


void User::setReservation(Reservation reservation)
{
	/*
	 * startingHour and endHour are related to reservation to set in vector
	 * resStart and resEnd are related to the reservations in the vector
	 */

	double startingHour, endHour;
	int duration;

	duration = reservation.getDuration();
	startingHour = reservation.getStartingHour();

	endHour = calculateEndHour(startingHour, duration);

	if(CheckAvailable(reservations,startingHour,endHour)==0)
		reservations.push_back(&reservation);
}

vector<Reservation*> User::getReservations()
{
	return reservations;
}








