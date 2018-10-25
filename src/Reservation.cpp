/*
 * Reservation.cpp
 *
 *  Created on: 25/10/2018
 *      Author: joaomartins
 */

#include "Reservation.h"

Reservation::Reservation(User user,int month,int day,int startingHour,double price,unsigned int duration)
{
	this->user = user;
	this->month = month;
	this->day = day;
	this->startingHour = startingHour;
	this->price = price;
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


