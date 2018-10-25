/*
 * Report.cpp
 *
 *  Created on: 25/10/2018
 *      Author: joaomartins
 */

#include "Report.h"

using namespace std;

Report::Report(User user,string teacherName,string userReport)
{
	name = user.getName();
	this->teacherName = teacherName;
	this->userReport = userReport;
}

string Report::showReport()
{
	return userReport;
}



