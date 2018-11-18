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
#include <math.h>

class Report{
private:
	std::vector<Reservation*> reservations;
	std::string name;
	std::string teacherName;
	int grade;
public:
    Report() {};
	Report(std::string userName, std::string teacherName,const std::vector<Reservation*> &reservs);
	friend std::ostream & operator <<(std::ostream & os,Report r);
	std::string getName();
	std::string getTeacherName();
	int getGrade();
	std::vector<Reservation*> getLessons();
	void indentation(std::ofstream &outfile, int indent);
	void readInfo(std::ifstream &infile);
	void storeInfo(std::ofstream &outfile, int indent);

};

#endif /* SRC_REPORT_H_ */
