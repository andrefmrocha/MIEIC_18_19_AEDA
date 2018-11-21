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
/**
 * The company itself, operation all of the rest
 */


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

	/**
	 * @brief Class Constructor.
	 * @param cardValue - the value of the Gold Card
	 * @param year - Current year
	 */
	Company(double cardValue,int year);
	//tested

	/**
	 * @brief Getter of the current Courts.
	 * @return number of max Users
	 */
    Company() {};
	Company(double cardValue, Date d);
	int getMaxUser()const;
	//tested

	/**
	 * @brief Creating a new Court
	 */
	void createCourt();
	//tested

	/**
	 * @brief Getter of the current Courts.
	 * @return vector of Courts
	 */
	std::vector<Court> getCourts();
	//tested

	/**
	 * @brief Getter of the current Users.
	 * @return vector of Users
	 */
	std::vector <User> getUsers();
	//tested

	/**
	 * @brief Getter of the current Teachers.
	 * @return vector of Teachers
	 */
	std::vector<Teacher> getTeachers();
	User& getUser(std::string userName);
	Teacher& getTeacher(std::string teacherName);

	/**
	 * Reserving the Court, User and Teacher for a new Lesson.
	 * @param month - the month of the lesson
	 * @param day - the day of the lesson
	 * @param startingHour - the starting Hour for it
	 * @param userName - the name of the User
	 * @param teacherName - the name of the Teacher
	 * @return if it was successful created
	 */
	bool makeLesson(int month,int day,double startingHour,std::string userName,std::string teacherName);
	//tested

	/**
	 * @brief Reserving the Court, User and Teacher for a new Reservation.
	 * @param month - the month of the lesson
	 * @param day - the day of the lesson
	 * @param startingHour - the starting Hour for it
	 * @param duration - the duration it
	 * @param username - the name of the User
	 * @return if it was successful created
	 */
	bool makeFree(int month,int day, double startingHour,int duration, std::string username);
	//tested

	/**
	 * @brief Register a new User to the system.
	 * @param name - the name of the user
	 * @param age - the age of the user
	 * @param isGold - if he wants to have the Gold card or not
	 * @param gender - the gender of the User
	 * @return if the user was succesfully created
	 */
	bool registerUser(std::string name, int age,bool isGold,std::string gender);
	//tested

	/**
	 * @brief - Register a new Teacher to the system.
	 * @param teacherName - the name of the Teacher
	 * @param age - the age of the Teacher
	 * @param gender - the gender of the Teacher
	 * @return if the Teacher was succesfully created
	 */
	bool registerTeacher(std::string teacherName,int age,std::string gender);
	bool makeUserReport(int month,std::string userName,std::string teacherName);
	//partially tested, needs to verify that invoice is saved properly

	/**
	 * @brief Make a Report for a specific user.
	 * @param month - month it relates to
	 * @param userName - the name of the user
	 * @return if if was made sucessfuly
	 */
	bool makeUserReport(int month,std::string userName,std::string teacherName, int grade,std::string addcomm);

	/**
	 * @brief Make an Invoice for a specific user.
	 * @param userName -  month it relates to
	 * @param month - the name of the user
	 * @param reservs - the reservations for that user
	 * @return if if was made sucessfuly
	 */

	//partially tested, needs to verify that invoice is saved properly
	bool makeUserInvoice(std::string userName, int month, std::vector<Reservation *> reservs);

	/**
	 * @brief Method to show a specific Report.
	 * @param name - name of the User
	 * @param month - month they want
	 * @return if it was properly shown
	 */
	//needs reports to be properly saved to be tested
	bool showReport(std::string name, int month);

	/**
	 * @brief Method to show a specific Invoice.
	 * @param name - name of the User
	 * @param month - month they want
	 * @return if it was properly shown
	 */
	//needs invoices to be prpperly saved to be tested
	bool showInvoice(std::string name,int month);
	//to implement

	/**
	 * @brief Store in the information of the Company to a file.
	 * @param outfile - the file to write information
	 * @param identation - current indentation
	 */
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

/**
 * When a user does not exist
 */

class NoUserRegistered
{
private:
	std::string name;
public:
	NoUserRegistered(std::string name) { this->name=name;}
	std::string what()const;
};


/**
 * When a Teacher does not exist
 */
class NoTeacherRegistered
{
private:
	std::string name;
public:
	NoTeacherRegistered(std::string name) {this->name = name;}
	std::string what()const;
};


/**
 * When the age is not valid
 */
class InvalidAge
{
private:
	int age;
public:
	InvalidAge(int age) { this->age=age;}
	std::string what()const;
};


/**
 * When that name is already in the system
 */

class AlreadyRegisteredUser
{
private:
	std::string name;
public:
	AlreadyRegisteredUser(std::string name) { this->name=name;}
	std::string what()const;
};

/**
 * When that name is already in the system
 */
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
