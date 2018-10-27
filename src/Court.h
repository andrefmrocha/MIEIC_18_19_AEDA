/*
 * Court.h
 *
 *  Created on: Oct 21, 2018
 *      Author: andrefmrocha
 */

#ifndef SRC_COURT_H_
#define SRC_COURT_H_

#include "Calendar.h"
#include "Person.h"
#include "Reservation.h"
#include <iostream>
#include <string>

class Court {
public:
	Court(int year);
	bool reserveClass(int month, int day, double startingHour, User user, Teacher teacher);
	bool reserveFree(int month, int day, double startingHour, int duration, User user);
private:
	void reserveCourt(int month, int day, double startingHour, int duration);
	void occupied(int month, int day, double startingHour, int duration);
	Year currentYear;
	int maxUsers;
};

class CourtReserved{
private:
	double startingHour;
	int month;
	int day;

public:
	CourtReserved(int month, int day, double StartingHour);
	std::string what() const;
};

#endif /* SRC_COURT_H_ */
