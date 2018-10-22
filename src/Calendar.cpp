/*
 * Year.cpp
 *
 *  Created on: Oct 20, 2018
 *      Author: andrefmrocha
 */

#include "Calendar.h"

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
			int daysInMonth = 31 - ((i -1) % 7) % 2;
			this->months.push_back(Month(i, daysInMonth));
		}
	}
}

Month::Month(int month, int days)
{
	this->month = month;
	for(int i = 1;  i < days + 1; i++)
	{
		this->days.push_back(Day(pair<int, int> (8, 10)));
	}
}



Day::Day(pair<int, int> workingHours)
{
	int hours = workingHours.second - workingHours.first;
	hours*=2;
	this->schedule = vector<bool> (false, hours);
	this->startingHour = workingHours.first;
}

bool Day::checkSchedule(int startingHours, int duration) const
{
	if(startingHours < this->startingHour)
	{
		cout << "The court is not open at this time!" << endl;
		return false;
	}
	startingHours -= this->startingHour;
	for(int i = startingHours; i < (startingHours+duration); i++)
	{
		if(this->schedule[i] == true)
		{
			cout << "The court is not available during this time period!" << endl;
			return false;
		}
	}
	return true;
}

bool Day::setSchedule(int startingHours, int duration)
{
	if(checkSchedule(startingHours, duration))
	{
		startingHours -= this->startingHour;
		for(int i = startingHours; i < (startingHours+duration); i++)
		{
			this->schedule[i] = true;
		}
		return true;
	}
	else
	{
		return false;
	}
}





