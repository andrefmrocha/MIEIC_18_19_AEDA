/*
 * Date.h
 *
 *  Created on: Oct 29, 2018
 *      Author: andrefmrocha
 */

#ifndef SRC_DATE_H_
#define SRC_DATE_H_
#include <cmath>
#include <fstream>

class Date {
	unsigned int day;
	unsigned int month;
	unsigned int year;
public:
	Date();
	Date(unsigned int day, unsigned int month, unsigned int year);
	Date operator++();
	void storeInfo(std::ofstream &outfile, int indentation);
	void indent(std::ofstream&outfile, int identation);
	void readInfo(std::ifstream &infile);
};

#endif /* SRC_DATE_H_ */


class BadDate
{
public:
	std::string what();
};