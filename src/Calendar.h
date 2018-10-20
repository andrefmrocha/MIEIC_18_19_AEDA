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

using namespace std;

class Day{
public:
	Day(pair<int, int> workHours);

private:
	vector<bool> schedule;
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
	vector<Month> months;
};

#endif /* SRC_YEAR_H_ */




