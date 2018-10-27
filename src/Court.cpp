/*
 * Court.cpp
 *
 *  Created on: Oct 21, 2018
 *      Author: andrefmrocha
 */

#include "Court.h"

using namespace std;

Court::Court(int year):currentYear(Year(year))
{
	this->maxUsers = 4;
}


void Court::occupied(int month, int day, double startingHour, int duration)
{
	if(!this->currentYear.getMonth(month).getDay(day).checkSchedule(startingHour, duration))
	{
		throw(CourtReserved(month, day, startingHour));
	}
}

CourtReserved::CourtReserved(int month, int day, double sH)
{
	this->month = month;
	this->day = day;
	this->startingHour = sH;
}

string CourtReserved::what()const{
	return "The court is not available on the day " + to_string(this->day) + "of the month " + to_string(this->month) + " at "
			+ to_string(this->startingHour);

}

void Court::reserveCourt(int m, int d, double sH, int dur)
{
	occupied(m, d, sH, dur);
	this->currentYear.getMonth(m).getDay(d).setSchedule(sH, dur);

}

void Court::reserveClass(int m, int d, double sH, int dur, User user)
{
	try{
		reserveCourt(m, d, sH, dur);
	}
	catch (CourtReserved& court)
	{
		cout << court.what();
	}
}



