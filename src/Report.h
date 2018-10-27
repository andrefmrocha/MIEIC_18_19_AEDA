/*
 * Report.h
 *
 *  Created on: 25/10/2018
 *      Author: joaomartins
 */

#ifndef SRC_REPORT_H_
#define SRC_REPORT_H_

#include <iostream>
#include <string>
#include <vector>
#include "Reservation.h"


class Report{
private:
	std::vector<Lesson*> reservations;
	std::string name;
	std::string teacherName;
	std::string addcomm;
	int grade;
public:
	Report(std::string userName, std::string teacherName,int grade, std::string addcomm,const std::vector<Lesson*> &reservs);
	friend std::ostream & operator <<(std::ostream & os,Report r);
	std::string getName();
	std::string getTeacherName();
	std::string getAddComm();
	int getGrade();
	std::vector<Lesson*> getLessons();

};

class InvalidGrade
{
private:
	int grade;
public:
	InvalidGrade(int grade) {this->grade = grade;}
	int getGrade() const { return grade;}
};



#endif /* SRC_REPORT_H_ */
