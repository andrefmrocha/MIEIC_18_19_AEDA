/*
 * Lesson.cpp
 *
 *  Created on: 25/10/2018
 *      Author: joaomartins
 */

#include "Lesson.h"

Lesson::Lesson(User u,int m,int d,int strHr,double p,unsigned int dr,Teacher t) : Reservation(u,m,d,strHr,p,dr)
{
	teacher = t;
}

double Lesson::getPrice()
{
	return price;
}

Teacher Lesson::getTeacher()
{
	return teacher;
}

void Lesson::setTeacher(Teacher teacher)
{
	this->teacher = teacher;
}

