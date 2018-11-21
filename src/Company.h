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
#include "Date.h"

class Company
{
private:
	std::vector<Court> tennisCourts;
	std::vector<User> users;
	std::vector<Teacher> teachers;
	double cardValue;
	int year;
	Date date; // set it to static
public:
    Company() {};
	Company(double cardValue, Date d);
	int getMaxUser()const;
	void createCourt();
	std::vector<Court> getCourts();
	std::vector <User> getUsers();
	std::vector<Teacher> getTeachers();
	User& getUser(std::string userName);
	Teacher& getTeacher(std::string teacherName);
	bool makeLesson(int month,int day,double startingHour,std::string userName,std::string teacherName);
	bool makeFree(int month,int day, double startingHour,int duration, std::string username);
	bool registerUser(std::string name, int age,bool isGold,std::string gender);
	bool registerTeacher(std::string teacherName,int age,std::string gender);
	bool makeUserReport(int month,std::string userName,std::string teacherName);
	bool makeUserInvoice(std::string userName, int month, std::vector<Reservation *> reservs);
	bool showReport(std::string name, int month);
	bool showInvoice(std::string name,int month);
	void storeInfo(std::ofstream &outfile,int identation);
	void indentation(std::ofstream &outfile,int identation);
	void readInfo(std::ifstream &infile);
	Company operator++();
	void showUsers();
	void showTeachers();
	void showCourts();
    void showUser(std::string name);
    void showTeacher(std::string teacher);
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

class InvalidDate
{
	int month;
	int day;
public:
	InvalidDate(int day, int month) { this->day = day, this->month = month;}
	std::string what() const;
};

#endif /* SRC_COMPANY_H_ */
