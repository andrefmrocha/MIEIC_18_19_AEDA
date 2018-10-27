/*
 * Report.h
 *
 *  Created on: 25/10/2018
 *      Author: joaomartins
 */

#ifndef SRC_REPORT_H_
#define SRC_REPORT_H_


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
	Report(std::string userName, std::string teacherName,int grade, std::string addcomm,std::vector<Lesson*> reservs);
	void showReport(std::ostream & os);

};

#endif /* SRC_REPORT_H_ */
