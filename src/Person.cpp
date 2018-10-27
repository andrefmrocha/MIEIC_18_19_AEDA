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
Teacher::Teacher(string name, int age, string gender):Person(name,age,gender)
{}

void Teacher::makeReport(User user, int month,int grade, string addcomm)
{
	//Report a(user.getName(), this->getName(),grade, addcomm); PRECISO VER SE O REPORT INCLUI VETOR DE LESSONS
	//user.setReport(a,month);//coloca report no user respetivo
}

////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////

User::User(string name,int age,string gender, bool isGold):Person(name,age,gender)
{
	this->isGold = isGold;
	reports.resize(12); //necessario nalgum momento definir o tamanho do vetor para 12
}

void User::makeGold()
{
	isGold = true;
}

void User::stopGold()
{
	isGold = false;
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








