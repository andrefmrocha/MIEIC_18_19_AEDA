/*
 * Year.cpp
 *
 *  Created on: Oct 20, 2018
 *      Author: andrefmrocha
 */

#include "Calendar.h"
#include <cmath>
using namespace std;

Year::Year(int year)
{
	// It is first determined if it is a leap year
	bool isLeapYear = false;
	if((year % 4 == 0 && year % 100 !=0) || year % 400 == 0)
		isLeapYear = true;

	for (int i = 1; i < 13; i++)
	{
		//Checks if it's February
		if(i == 2)
		{
			if(isLeapYear)
				this->months.push_back(Month(i, 28));
			else
				this->months.push_back(Month(i, 29));
		}
		else
		{
			//Determines the number of days in a normal month
			int daysInMonth = 30 + (i + (int)floor((double)i/8))%2;
			this->months.push_back(Month(i, daysInMonth));
		}
	}
}

Month& Year::getMonth(int month)
{
	return this->months[month - 1];
}

Month::Month(int month, int days)
{
	this->month = month;
	for(int i = 0;  i < days + 1; i++)
	{
		this->days.push_back(Day(pair<int, int> (8, 20)));
	}
}

Day& Month::getDay(int day)
{
	return this->days[day - 1];
}


Day::Day(pair<int, int> workingHours)
{
	int hours = workingHours.second - workingHours.first;
	hours*=2;
	for(int i = 0;  i < hours; i++)
	{
		this->schedule.push_back(false);
	}
	this->startingHour = workingHours.first;
}

bool Day::checkSchedule(double startingHours, int duration) const
{
	if(startingHours < this->startingHour)
	{
		cout << "The court is not open at this time!" << endl;
		return false;
	}
	startingHours -= this->startingHour;
	startingHours *= 2;
	for(int i = startingHours; i < (startingHours+duration); i++)
	{
		if(this->schedule[i] == true)
		{
			return false;
		}
	}
	return true;
}

void Day::setSchedule(double startingHours, int duration)
{
	startingHours -= this->startingHour;
	startingHours*=2;
	for(int i = startingHours; i < (startingHours+duration); i++)
	{
		this->schedule[i] = true;
	}
}





