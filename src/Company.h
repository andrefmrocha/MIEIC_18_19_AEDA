/*
 * Company.h
 *
 *  Created on: 30/10/2018
 *      Author: joaomartins
 */

#ifndef SRC_COMPANY_H_
#define SRC_COMPANY_H_

#include "Calendar.h"
#include "Court.h"

class Company
{
private:
	std::vector<Court> tennisCourts;
	std::vector<User*> users;
	std::vector<Teacher> teachers;
	double cardValue;
	const int year;
public:
	Company(double cardValue,int year);
	int getMaxUser()const;
	void createCourt();
	bool makeLesson(int month,int day,double startingHour,std::string userName,std::string teacherName);
	bool makeFree(int month,int day, double startingHour,int duration, std::string username);
	bool registerUser(std::string name, int age,bool isGold,std::string gender);
	bool registerTeacher(std::string teacherName,int age,std::string gender);
	bool makeUserReport(int month,std::string userName,std::string teacherName, int grade,std::string addcomm);
	bool makeUserInvoice(std::string userName, std::vector<Reservation *> reservs);
	//bool updateInfoUser (std::string name, int age, bool isGold, std::string gender);
	//bool updateInfoTeacher (std::string teacherName,int age ,std::string gender);
	//std::ostream& operator <<(std::ostream & os, Company c);
	void storeInfo(std::ofstream &outfile,int identation);
	void indent(std::ofstream &outfile,int identation);
	//void showInfo();

};

class NoUserRegistered
{
private:
	std::string name;
public:
	NoUserRegistered(std::string name) { this->name=name;}
	std::string what()const;
};

class NoTeacherRegistered
{
private:
	std::string name;
public:
	NoTeacherRegistered(std::string name) {this->name = name;}
	std::string what()const;
};

#endif /* SRC_COMPANY_H_ */
