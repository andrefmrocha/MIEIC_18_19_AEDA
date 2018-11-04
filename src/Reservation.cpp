/*
 * Reservation.cpp
 *
 *  Created on: 25/10/2018
 *      Author: joaomartins
 */

#include "Reservation.h"
#include <iostream>
using namespace std;

Reservation::Reservation(int month,int day,int startingHour,double price,unsigned int duration) : price(price)
{
	this->month = month;
	this->day = day;
	this->startingHour = startingHour;
	this->duration = duration;
}

double Reservation::getPrice()
{
	return price;
}

double Reservation::getStartingHour()
{
	return startingHour;
}

int Reservation::getDuration()
{
	return duration;
}

int Reservation::getMonth()
{
	return month;
}

int Reservation::getDay()
{
	return day;
}
bool Reservation::operator ==(Reservation &r) const
	{
		return (this->day == r.getDay() && this->month == r.getMonth() && this->startingHour == r.getStartingHour());
	}

Lesson::Lesson(int m,int d,int strHr,double p,unsigned int dr) : Reservation(m,d,strHr,p,dr)
{}

double Lesson::getPrice()
{
	return price;
}


Free::Free(int m,int d,int strHr,double p,unsigned int dur) : Reservation(m,d,strHr,p,dur)
{

}

double Free::getPrice()
{
	return price;
}


void Reservation::indent(std::ofstream &outfile, int indent)
{
	for(int i = 0; i < indent; i++)
	{
		outfile << "\t";
	}
}

void Reservation::storeInfo(std::ofstream &outfile, int indent)
{
	Reservation::indent(outfile, indent);
	outfile << "{" << endl;
	indent++;
	Reservation::indent(outfile, indent);
	outfile << "\"price\": " << this->price << "," << endl;
	Reservation::indent(outfile, indent);
	outfile << "\"duration\": " << this->duration<< "," << endl;
	Reservation::indent(outfile, indent);
	outfile << "\"month\": " << this->month << "," << endl;
	Reservation::indent(outfile, indent);
	outfile << "\"day\": " << this->day << "," << endl;
	Reservation::indent(outfile, indent);
	outfile << "\"startingHour\": " << this->startingHour << endl;
	indent--;
	Reservation::indent(outfile, indent);
	outfile << "}";
}


void Reservation::readInfo(std::ifstream &infile)
{
	string savingString;
	bool flag = false;
	while (getline(infile, savingString))
	{
		if(savingString.find("price") != string::npos)
		{
			this->price = stod(savingString.substr(savingString.find("price") + 8, 2));
		}

		if(savingString.find("duration") != string::npos)
		{
			this->duration = (unsigned  int) stoul(savingString.substr(savingString.find("duration") + 11, 1));
		}


		if(savingString.find("month") != string::npos)
		{
			savingString = savingString.substr(savingString.find("month") + 8, 2);
			if(savingString.find(',')) {
				savingString = savingString.substr(0, 1);
			}
			this->month = stoi(savingString);
		}


		if(savingString.find("day") != string::npos)
		{
			savingString = savingString.substr(savingString.find("day") + 6, 2);
			if(savingString.find(',')) {
				savingString = savingString.substr(0, 1);
			}
			this->day = stoi(savingString);
		}


		if(savingString.find("startingHour") != string::npos)
		{
			flag = true;
			savingString = savingString.substr(savingString.find("startingHour") + 15, 2);
			if(savingString.find(',')) {
				savingString = savingString.substr(0, 1);
			}
			cout << savingString;
			this->startingHour = stoi(savingString);
		}

		if(flag)
		{
			break;
		}
	}
}
