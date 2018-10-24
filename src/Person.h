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
<<<<<<< Updated upstream
	//Report getReport(int month);
	//void setReport(Report report, int month);
private:
	bool isGold;
	//std::vector<Report*> reports;
	//std::vector<Reservation*> reservations;
	//std::vector<Invoice*> invoices;
=======
//	Report getReport(int month);
//	void setReport(Report report, int month);
private:
	bool isGold();
//	std::vector<Report*> reports;
//	std::vector<Reservation*> reservations;
//	std::vector<Invoice*> invoices;
>>>>>>> Stashed changes
};

class Teacher: public Person {
public:
	Teacher(std::string name, int age, std::string gender);
	void makeReport(User user);
<<<<<<< Updated upstream
private:
	//std::vector<Lesson*> lessons;
};

=======
};
//	std::vector<Lesson*> lessons;
>>>>>>> Stashed changes
#endif /* SRC_PERSON_H_ */
