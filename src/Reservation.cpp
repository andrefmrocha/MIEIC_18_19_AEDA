/*
 * Reservation.cpp
 *
 *  Created on: 25/10/2018
 *      Author: joaomartins
 */

#include "Reservation.h"

Reservation::Reservation(int month,int day,int startingHour,double price,unsigned int duration) : price(price)
{
	this->month = month;
	this->day = day;
	this->startingHour = startingHour;
	this->duration = duration;
}

double Reservation::getPrice()
{
	return price;
}

Lesson::Lesson(int m,int d,int strHr,double p,unsigned int dr) : Reservation(m,d,strHr,p,dr)
{}

double Lesson::getPrice()
{
	return price;
}


Free::Free(int m,int d,int strHr,double p,unsigned int dur) : Reservation(m,d,strHr,p,dur)
{

}

double Free::getPrice()
{
	return price;
}


