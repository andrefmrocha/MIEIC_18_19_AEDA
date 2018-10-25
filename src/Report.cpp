/*
 * Report.cpp
 *
 *  Created on: 25/10/2018
 *      Author: joaomartins
 */

#include "Report.h"
#include "Gradetempl.h"

using namespace std;

// exceptions for invalid arguments
Report::Report(User user,string teacherName,int grade, string addcomm)
{
	name = user.getName();
	this->teacherName = teacherName;
	this->grade = grade;
	this->addcomm = addcomm;
}

void Report::showReport(ostream &os)
{
	os << "Name: " << name << endl
		<< "Teacher: " << teacherName << endl
		<< "Report details: " << endl;
	switch(grade)
	{
	case 1:
		grade_1(os,addcomm);
		break;
	case 2:
		grade_2(os,addcomm);
		break;
	case 3:
		grade_3(os,addcomm);
		break;
	case 4:
		grade_4(os,addcomm);
		break;
	case 5:
		grade_5(os,addcomm);
		break;
	default:
		break;
	}
}



