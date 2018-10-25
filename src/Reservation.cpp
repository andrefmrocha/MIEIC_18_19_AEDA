/*
 * Reservation.cpp
 *
 *  Created on: 25/10/2018
 *      Author: joaomartins
 */

#include "Reservation.h"

Reservation::Reservation(User user,int month,int day,int startingHour,double price,unsigned int duration) : price(price)
{
	this->user = user;
	this->month = month;
	this->day = day;
	this->startingHour = startingHour;
	this->duration = duration;
}

double Reservation::getPrice()
{
	return price;
}

User Reservation::getUser()
{
	return user;
}

void Reservation::setUser(User user)
{
	this->user = user;
}

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

Free::Free(User u,int m,int d,int strHr,double p,unsigned int dur) : Reservation(u,m,d,strHr,p,dur)
{

}

Free::getPrice()
{
	return price;
}


