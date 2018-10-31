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
    Day(){};
	Day(std::pair<int, int> workHours);
	bool checkSchedule(double startingHours, int duration) const;
	void setSchedule(double startingHours, int duration);
	void setSchedule(std::vector<bool> schedule);
	void setSH(int sH);
	std::vector<bool> getSchedule();
	int getSH() const;
private:
	int startingHour;
	std::vector<bool> schedule;
};

class Month {
public:
    Month(){};
	Month(int month, int days);
	Day& getDay(int day);
	int getMonth();
	int getNoDays();
	void setDays(std::vector<Day> days);
	void setMonth(int month);
private:
	int month;
	std::vector<Day> days;
};

class Year {
public:
    Year(){};
	Year(int year);
	Month& getMonth(int month);
	void setMonths(std::vector<Month> months);
private:
	std::vector<Month> months;
};

#endif /* SRC_YEAR_H_ */





