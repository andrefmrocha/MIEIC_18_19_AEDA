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
#include "Person.h"
#include "Lesson.h"


class Report {
private:
	std::vector<Lesson*> reservations;
	std::string name;
	std::string userReport;
	std::string teacherName;
public:
	Report(User user,std::string teacherName,std::string userReport);
	std::string showReport();

};

#endif /* SRC_REPORT_H_ */
