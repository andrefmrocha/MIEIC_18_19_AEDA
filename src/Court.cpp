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
	this->currentYear.getMonth(m).getDay(d).setSchedule(sH, dur);

}

bool Court::reserveClass(int m, int d, double sH, User user, Teacher teacher)
{
	int dur = 2;
	try{
		occupied(m, d, sH, dur);
	}
	catch (CourtReserved& court)
	{
		cout << court.what();
		return false;
	}
	try
	{
		CheckAvailable(user.getReservations(),sH, calculateEndHour(sH, dur));
	}
	catch(AlreadyReservedHours &e)
	{
		cout << "The user is not available at this time!" << endl;
		return false;
	}
	try
	{
		CheckAvailable(teacher.getLessons(),sH, calculateEndHour(sH, dur));
	}
	catch(AlreadyReservedHours &e)
	{
		cout << "This user's teacher is not available at this time!" << endl;
		return false;
	}
	reserveCourt(m, d, sH, dur);
	double price = 45;
	if(user.getisGold())
	{
		price*=0.85;
	}
	Reservation * lesson = new Lesson(m, d, sH, price, dur);
	Lesson teacherLesson(m, d, sH, price, dur);
	user.setReservation(lesson);
	teacher.setLesson(teacherLesson);
	return true;
}

bool Court::reserveFree(int m, int d, double sH, int dur, User user)
{
	try{
		occupied(m, d, sH, dur);
	}
	catch (CourtReserved& court)
	{
		cout << court.what();
		return false;
	}
	double price = 15;
	price*= dur;
	Reservation * reserv = new Free(m, d, sH, price, dur);
	user.setReservation(reserv);
	return true;
}

