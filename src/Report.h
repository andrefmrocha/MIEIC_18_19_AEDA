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
	std::vector<Reservation*> reservations;
	std::string name;
	std::string teacherName;
	std::string addcomm;
	int grade;
public:
	Report(std::string userName, std::string teacherName,int grade, std::string addcomm,const std::vector<Reservation*> &reservs);
	friend std::ostream & operator <<(std::ostream & os,Report r);
	std::string getName();
	std::string getTeacherName();
	std::string getAddComm();
	int getGrade();
	std::vector<Reservation*> getLessons();
	//void indent(std::ofstream &outfile, int indent);
	//void readInfo(std::ifstream &infile);
	//void storeInfo(std::ofstream &outfile, int indent);

};

class InvalidGrade
{
private:
	int grade;
public:
	InvalidGrade(int grade) {this->grade = grade;}
	int getGrade() const { return grade;}
	friend std::ostream & operator<<(std::ostream &os,const InvalidGrade &ig);
};

#endif /* SRC_REPORT_H_ */
