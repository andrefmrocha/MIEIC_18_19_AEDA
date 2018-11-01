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
#include <fstream>
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
	virtual void saveClass(std::ofstream &outfile, int &indentation);
	bool operator == (const Person &p1);
private:
	std::string name;
	int age;
	std::string gender;
};
//////////////////////////////////////////////////
//////////////////////////////////////////////////
class User :public Person {
public:
	User(std::string name,int age, std::string gender, bool isGold, std::string assignedTeacher);
	void makeGold();
	void stopGold();
	bool getisGold();
	Report getReport(int month);
	void setReport(Report report, int month);
	void setReservation(Reservation* reservation);
	std::vector<Reservation*> getReservations();
	std::string getTeacher();
	void saveClass(std::ofstream &outfile, int &indentation);
private:
	bool isGold;
	std::string assignedTeacher;
	std::vector<Report*> reports;
	std::vector<Reservation*> reservations;
	std::vector<Invoice*> invoices;
};

//////////////////////////////////////////////////
//////////////////////////////////////////////////

class Teacher: public Person {
public:
	Teacher(std::string name, int age, std::string gender);
	void setLesson(Lesson lesson);
	std::vector<Lesson*> getLessons();
	void saveClass(std::ofstream &outfile, int &indentation);
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
	IncorrectMonth(){};
};

//handling errors for setReservation

class AlreadyReservedHours
{
public:
	AlreadyReservedHours(){};
};

/////
class InsideRes: public AlreadyReservedHours
{
public:
	InsideRes(){};
};

class EndHourInsideRes : public AlreadyReservedHours
{
public:
	EndHourInsideRes(){};
};

class StartHourInsideRes : public AlreadyReservedHours
{
public:
	StartHourInsideRes(){};
};

double calculateEndHour(double startinghour, int duration);
template< class t>
int CheckAvailable(std::vector<t *> res,double startingHour, double endHour,int day, int month)
{
	for(size_t i =0; i < res.size(); i++)
	{
		if(res.at(i)->getDay() == day && res.at(i)->getMonth() == month)
		{
		double resStart = res.at(i)->getStartingHour();
		double resEnd = calculateEndHour(resStart,res.at(i)->getDuration());

		if(startingHour >= resStart && endHour <= resEnd)
			// tempo da reserva esta em espaço ocupado
			throw(InsideRes());
		else if(startingHour <= resStart && endHour >= resStart)
			//tempo da reserva entra em espaço ocupado
			throw(EndHourInsideRes());
		else if(startingHour >= resStart && endHour >= resEnd && startingHour <= resEnd)
			//tempo da reserva esta a meio
			throw(StartHourInsideRes());
		}
	}
	return 0;
}


#endif /* SRC_PERSON_H_ */
