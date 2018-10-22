/*
 * Court.h
 *
 *  Created on: Oct 21, 2018
 *      Author: andrefmrocha
 */

#ifndef SRC_COURT_H_
#define SRC_COURT_H_

#include "Calendar.h"


class Court {
public:
	Court(int year);
	bool reserveCourt(int month, int day, int startingHour, int duration);
	bool occupied(int month, int day, int startingHour, int duration);
private:
	Year currentYear;
	int maxUsers;
};

#endif /* SRC_COURT_H_ */
