/*
 * Year.h
 *
 *  Created on: Oct 20, 2018
 *      Author: andrefmrocha
 */

#ifndef SRC_YEAR_H_
#define SRC_YEAR_H_
#include <utility>
#include<vector>
#include<iostream>
#include <algorithm>

class Day{
public:
	Day(std::pair<int, int> workHours);
	bool checkSchedule(double startingHours, int duration) const;
	void setSchedule(double startingHours, int duration);

private:
	int startingHour;
	std::vector<bool> schedule;
};

class Month {
public:
	Month(int month, int days);
	Day& getDay(int day);
private:
	int month;
	std::vector<Day> days;
};

class Year {
public:
	Year(int year);
	Month& getMonth(int month);
private:
	std::vector<Month> months;
};

#endif /* SRC_YEAR_H_ */





