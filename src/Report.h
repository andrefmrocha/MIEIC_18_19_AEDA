/*
 * Report.h
 *
 *  Created on: 25/10/2018
 *      Author: joaomartins
 */

#ifndef SRC_REPORT_H_
#define SRC_REPORT_H_



#include "Person.h"
#include "Reservation.h"


class Report{
private:
	std::vector<Lesson*> reservations;
	std::string name;
	std::string userReport;
	std::string teacherName;
	std::string addcomm;
	int grade;
public:
	Report(User user, std::string teacherName,int grade, std::string addcomm);
	void showReport(std::ostream & os);

};

#endif /* SRC_REPORT_H_ */
