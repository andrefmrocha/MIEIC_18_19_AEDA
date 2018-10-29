/*
 * Report.cpp
 *
 *  Created on: 25/10/2018
 *      Author: joaomartins
 */

#include "Report.h"
#include "Gradetempl.h"

using namespace std;




Report::Report(string userName,string teacherName,int grade, string addcomm, const vector<Lesson*> &reservs)
{
	if (grade > 5 || grade < 1)
		throw (InvalidGrade(grade));
	name = userName;
	this->teacherName = teacherName;
	this->grade = grade;
	this->addcomm = addcomm;
	this->reservations = reservs;
}
string Report::getName()
{
	return name;
}
string Report::getTeacherName()
{
	return teacherName;
}

string Report::getAddComm()
{
	return addcomm;
}

int Report::getGrade()
{
	return grade;
}
vector<Lesson*> Report::getLessons()
{
	return reservations;
}

ostream & operator <<(ostream &os,Report r)
{
	os << "Name: " << r.getName() << endl
		<< "Teacher: " << r.getTeacherName() << endl
		<< "Report details: " << endl << endl
		<< "Classes attended this month: " << endl;
	for (size_t i =0; i < r.getLessons().size();i++)
	{
		os << " \t Date: " << r.getLessons()[i]->getDay() << "/" << r.getLessons()[i]->getMonth() << endl
		<< " \t Period of class: " << " TO BE IMPLEMENTED" << endl << endl;
	}
	switch(r.getGrade())
	{
	case 1:
		grade_1(os,r.getAddComm());
		break;
	case 2:
		grade_2(os,r.getAddComm());
		break;
	case 3:
		grade_3(os,r.getAddComm());
		break;
	case 4:
		grade_4(os,r.getAddComm());
		break;
	case 5:
		grade_5(os,r.getAddComm());
		break;
	default:
		break;
	}
	return os;
}


std::ostream & operator << (std::ostream &os,const InvalidGrade &ig)
{
	os << "Invalid grade: " << ig.getGrade() << std::endl;
	return os;
}


