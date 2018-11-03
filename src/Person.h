/*
 * Person.h
 *
 *  Created on: 21/10/2018
 *      Author: anamargaridarl
 */

#ifndef SRC_PERSON_H_
#define SRC_PERSON_H_

#include "Report.h"
#include "Reservation.h"
#include "Invoice.h"

#include <string>
#include <vector>
#include <fstream>
#include <iostream>

class Person
{
public:
	Person(std::string name,int age, std::string gender);
	std::string getName() const;
	int getAge();
	std::string getGender();
	void setName(std::string name);
	void setAge(int age);
	void setGender(std::string gender);
	virtual void saveClass(std::ofstream &outfile, int &indentation);
	//virtual void loadClass(std::ifstream &inpfile);
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
	std::vector<Invoice*> getInvoices();
	std::vector<Reservation*> getReservations();
	std::string getTeacher();
	void setInvoice(Invoice invoice, int month);
	void setReport(Report report, int month);
	void setReservation(Reservation* reservation);
	void saveClass(std::ofstream &outfile, int &indentation);
	//void loadClass(std::ifstream &inpfile);
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
	void setLesson(Lesson* lesson);
	std::vector<Lesson*> getLessons();
	void saveClass(std::ofstream &outfile, int &indentation);
	void addStudent();
	int getnStudents();
	//void loadClass(std::ifstream &inpfile);
private:
	std::vector<Lesson*> lessons;
	int nStudents;
};

////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////

//handling error for setReport
class ReportAlreadyExists
{
private:
	int month;
public:
	ReportAlreadyExists(int month){ this->month =month;}
	int getMonth(){return month;}
	std::string what() const;
};

class InvoiceAlreadyExists
{
private:
	int month;
public:
	InvoiceAlreadyExists(int month){ this->month =month;}
	int getMonth(){return month;}
	std::string what() const;
};

//handling error for getReport
class ReportNotAvailable
{
public:
	ReportNotAvailable(int month){ this->month =month;}
	int month;
	int getMonth(){return month;}
	std::string what() const;
};

//setReport getReport setInvoice
class IncorrectMonth
{
public:
	IncorrectMonth(){};
	std::string what() const;
};

//handling errors for setReservation

class AlreadyReservedHours
{
public:
	AlreadyReservedHours(){};
	virtual std::string what() const{}

};


/////
class InsideRes: public AlreadyReservedHours
{
private:
	double resStart,endHour;
public:
	InsideRes(double resStart, double endHour){
		this->resStart = resStart;
		this->endHour=endHour;
	}
	std::string what() const;
};

class EndHourInsideRes : public AlreadyReservedHours
{
private:
	double resStart,resEnd;
public:
	EndHourInsideRes(double resStart, double resEnd){
		this->resStart = resStart;
		this->resEnd=resEnd;
	}
	std::string what() const;
};

class StartHourInsideRes : public AlreadyReservedHours
{
private:
	double StartingHour, endHour;
public:
	StartHourInsideRes(double StartingHour, double endHour){
		this->StartingHour = StartingHour;
		this->endHour=endHour;
	}
	std::string what() const;
};

double calculateEndHour(double startinghour, int duration);

template< class t>
int CheckAvailable(std::vector<t *> res,double startingHour, double endHour,int day, int month)
{
	for(size_t i =0; i < res.size(); i++)
	{
		if(res.at(i)->getDay() == day && res.at(i)->getMonth() == month)
		{
			//res- values from reservation already made
		double resStart = res.at(i)->getStartingHour();
		double resEnd = calculateEndHour(resStart,res.at(i)->getDuration());

		if(startingHour >= resStart && endHour <= resEnd)
			// tempo da reserva esta em espaço ocupado
			throw(InsideRes(resStart,endHour));
		else if(startingHour <= resStart && endHour >= resStart)
			//tempo da reserva entra em espaço ocupado
			throw(EndHourInsideRes(resStart,resEnd));
		else if(startingHour >= resStart && endHour >= resEnd && startingHour <= resEnd)
			//tempo da reserva esta a meio
			throw(StartHourInsideRes(startingHour, endHour));
		}
	}
	return 0;
}


#endif /* SRC_PERSON_H_ */
