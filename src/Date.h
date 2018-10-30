/*
 * Date.h
 *
 *  Created on: Oct 29, 2018
 *      Author: andrefmrocha
 */

#ifndef SRC_DATE_H_
#define SRC_DATE_H_
#include <cmath>

class Date {
	unsigned int day;
	unsigned int month;
	unsigned int year;
public:
	Date();
	Date(unsigned int day, unsigned int month, unsigned int year);
	Date operator++();
};

#endif /* SRC_DATE_H_ */
