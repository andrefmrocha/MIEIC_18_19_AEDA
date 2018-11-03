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
	std::vector<User> users;
	std::vector<Teacher> teachers;
	double cardValue;
	const int year;
public:
	Company(double cardValue,int year);
	//tested
	int getMaxUser()const;
	//tested
	void createCourt();
	//tested
	std::vector<Court> getCourts();
	//tested
	std::vector <User> getUsers();
	//tested
	std::vector<Teacher> getTeachers();
	//tested
	int getUser(std::string userName);
	//tested
	bool makeLesson(int month,int day,double startingHour,std::string userName,std::string teacherName);
	//tested
	bool makeFree(int month,int day, double startingHour,int duration, std::string username);
	//tested
	bool registerUser(std::string name, int age,bool isGold,std::string gender);
	//tested
	bool registerTeacher(std::string teacherName,int age,std::string gender);
	//partially tested, needs to verify that invoice is saved properly
	bool makeUserReport(int month,std::string userName,std::string teacherName, int grade,std::string addcomm);
	//partially tested, needs to verify that invoice is saved properly
	bool makeUserInvoice(std::string userName, int month, std::vector<Reservation *> reservs);
	//needs reports to be properly saved to be tested
	bool showReport(std::string name, int month);
	//needs invoices to be prpperly saved to be tested
	bool showInvoice(std::string name,int month);
	//to implement
	void storeInfo(std::ofstream &outfile,int identation);
	//to implemente
	void indent(std::ofstream &outfile,int identation);
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

class InvalidAge
{
private:
	int age;
public:
	InvalidAge(int age) { this->age=age;}
	std::string what()const;
};

class AlreadyRegisteredUser
{
private:
	std::string name;
public:
	AlreadyRegisteredUser(std::string name) { this->name=name;}
	std::string what()const;
};

class AlreadyRegisteredTeacher
{
private:
	std::string name;
public:
	AlreadyRegisteredTeacher(std::string name) { this->name=name;}
	std::string what()const;
};

#endif /* SRC_COMPANY_H_ */
