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

class User :public Person {
public:
	User(std::string name,int age, std::string gender, bool isGold);
	void makeGold();
	void stopGold();
	//Report getReport(int month);
	//void setReport(Report report, int month);
private:
	bool isGold;
	//std::vector<Report*> reports;
	//std::vector<Reservation*> reservations;
	//std::vector<Invoice*> invoices;
//	Report getReport(int month);
//	void setReport(Report report, int month);
};

class Teacher: public Person {
public:
	Teacher(std::string name, int age, std::string gender);
	void makeReport(User user);
private:
	//std::vector<Lesson*> lessons;
};

#endif /* SRC_PERSON_H_ */
