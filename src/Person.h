/*
 * Person.h
 *
 *  Created on: 21/10/2018
 *      Author: anamargaridarl
 */

#ifndef SRC_PERSON_H_
#define SRC_PERSON_H_

#include <string>
#include <vector>
#include "Report.h"
#include "Reservation.h"
#include "Invoice.h"

class Person
{
public:
	Person(std::string name,int age, std::string gender);
	std::string getName();
	int getAge();
	std::string getGender();
	void setName(std::string name);
	void setAge(int age);
	void setGender(std::string gender);
private:
	std::string name;
	int age;
	std::string gender;
};
//////////////////////////////////////////////////
//////////////////////////////////////////////////
class User :public Person {
public:
	User(std::string name,int age, std::string gender, bool isGold);
	void makeGold();
	void stopGold();
	Report getReport(int month);
	void setReport(Report report, int month);
private:
	bool isGold;
	std::vector<Report*> reports;
	std::vector<Reservation*> reservations;
	std::vector<Invoice*> invoices;
};

//////////////////////////////////////////////////
//////////////////////////////////////////////////

class Teacher: public Person {
public:
	Teacher(std::string name, int age, std::string gender);
	void makeReport(User user);
private:
	std::vector<Lesson*> lessons;
};

////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////

//handling error for setReport
class ReportAlreadyExists
{
public:
	ReportAlreadyExists(int month){ this->month =month;}
	int month;
	int getMonth(){return month;}
};

//handling error for getReport
class ReportNotAvailable
{
public:
	ReportNotAvailable(int month){ this->month =month;}
	int month;
	int getMonth(){return month;}
};

class IncorrectMonth
{
public:
	IncorrectMonth();
};

#endif /* SRC_PERSON_H_ */
