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

class Day{
public:
	Day(std::pair<int, int> workHours);
	bool checkSchedule(int startingHours, int duration) const;
	bool setSchedule(int startingHours, int duration);

private:
	int startingHour;
	std::vector<bool> schedule;
};

class Month {
public:
	Month(int month, int days);

private:
	int month;
	std::vector<Day> days;
};

class Year {
public:
	Year(int year);

private:
	std::vector<Month> months;
};

#endif /* SRC_YEAR_H_ */





