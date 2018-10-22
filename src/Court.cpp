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

bool Court::occupied(int month, int day, int startingHour, int duration)
{
	return this->currentYear.getMonth(month).getDay(day).checkSchedule(startingHour, duration);
}
