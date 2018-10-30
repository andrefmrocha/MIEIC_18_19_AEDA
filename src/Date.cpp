/*
 * Date.cpp
 *
 *  Created on: Oct 29, 2018
 *      Author: andrefmrocha
 */

#include "Date.h"
using namespace std;

Date::Date() {
	this->day = 1;
	this->month = 1;
	this->year = 1;
}


Date::Date(unsigned int day, unsigned int month, unsigned int year)
{
	this->day = day;
	this->month = month;
	this->year = year;
}

Date Date::operator ++()
{
	if(month != 2)
	{
		if((((this->month + (int)floor((double)this->month/8))%2)+ 30 - this->day) == 0)
		{
			if(this->month == 12)
			{
				this->year++;
				this->month = 1;
				this->day = 1;
			}
			else
			{
				this->month++;
				this->day = 1;
			}
		}
		else
		{
			this->day++;
		}
	}
	else
	{
		bool isLeapYear = false;
		if((year % 4 == 0 && year % 100 !=0) || year % 400 == 0)
			isLeapYear = true;
		if(isLeapYear)
		{
			if(this->day == 29)
			{
				this->month++;
				this->day = 1;
			}
			else
			{
				this->day++;
			}
		}
		else
		{
			if(this->day == 28)
			{
			this->month++;
			this->day = 1;
			}
			else
			{
			this->day++;
			}
		}
	}
	return *this;
}
