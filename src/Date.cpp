/*
 * Date.cpp
 *
 *  Created on: Oct 29, 2018
 *      Author: andrefmrocha
 */

#include "Date.h"
using namespace std;

Date::Date() {
	this->day = 1;
	this->month = 1;
	this->year = 1;
}


Date::Date(unsigned int day, unsigned int month, unsigned int year)
{
	// Checks if the day and month are valid
    if(month > 12 || day > (month + (int)floor((double)month/8))%2+ 30)
    {
		throw(BadDate());
    }
    else if(month == 2) // Checks it is February, in order to take care if it is Leap or not
	{
		if((year % 4 == 0 && year % 100 !=0) || year % 400 == 0)
		{
			if(day > 28)
				throw(BadDate());
		} else
		{
			if(day > 27)
				throw(BadDate());
		}
	}
	this->day = day;
	this->month = month;
	this->year = year;
}

Date Date::operator ++()
{
	if(month != 2) // When the month is not February, it can be incremented using
	{			   // a generalistic algorithm for all months but February
		if((((this->month + (int)floor((double)this->month/8))%2)+ 30 - this->day) == 0)
		{
			if(this->month == 12)
			{
				this->year++;
				this->month = 1;
				this->day = 1;
			}
			else
			{
				this->month++;
				this->day = 1;
			}
		}
		else
		{
			this->day++;
		}
	}
	else
	{  	//When it is February it checks it is a Leap Year in order to save the information better
		bool isLeapYear = false;
		if((year % 4 == 0 && year % 100 !=0) || year % 400 == 0)
			isLeapYear = true;
		if(isLeapYear)
		{
			if(this->day == 29)
			{
				this->month++;
				this->day = 1;
			}
			else
			{
				this->day++;
			}
		}
		else
		{
			if(this->day == 28)
			{
			this->month++;
			this->day = 1;
			}
			else
			{
			this->day++;
			}
		}
	}
	return *this;
}

void Date::indent(std::ofstream &outfile, int identation)
{
	for(int i = 0; i < identation; i++)
	{
		outfile << "\t";
	}
}


void Date::storeInfo(std::ofstream &outfile, int indentation)
{
	indent(outfile, indentation);
	outfile << "{" << endl;
	indentation++;
	indent(outfile, indentation); //Stores the day
	outfile << "\"day\": " << this->day <<  "," <<endl;
	indent(outfile, indentation); //Stores the month
	outfile << "\"month\": " << this->month << "," << endl;
	indent(outfile, indentation); // Stores the years
	outfile << "\"year\": " << this->year << endl;
	indentation--;
	indent(outfile, indentation);
	outfile <<"}";
}

void Date::readInfo(std::ifstream &infile)
{
    string savingString;
    while (getline(infile, savingString))
    {
        if(savingString.find("day") != string::npos) // Reads the day
        {
            savingString = savingString.substr(savingString.find("day") + 6);
            savingString = savingString.substr(0, savingString.find(','));
            this->day = (unsigned  int) stoul(savingString);
        }

        if(savingString.find("month") != string::npos) // Reads the month
        {
            savingString = savingString.substr(savingString.find("month") + 8);
            savingString = savingString.substr(0, savingString.find(','));
            this->month = (unsigned  int) stoul(savingString);
        }

        if(savingString.find("year") != string::npos) // Reads the year and stops
        {
            savingString = savingString.substr(savingString.find("year") + 7);
            this->year = (unsigned  int) stoul(savingString);
            break;
        }
    }
}

unsigned int Date::getDay() {
	return day;
}

unsigned int Date::getMonth() {
	return month;
}

unsigned int Date::getYear() {
	return year;
}

std::string BadDate::what()
{
	return "Data does not exist!";
}