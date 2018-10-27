/*
 * Invoice.cpp
 *
 *  Created on: Oct 21, 2018
 *      Author: andrefmrocha
 */

#include "Invoice.h"

using namespace std;

Invoice::Invoice(string name, string teacher, vector<Reservation *> reservs)
{
	this->name = name;
	this->assignedTeacher = teacher;
	this->reservs  = reservs;
	this->totalPrice = 0;
	for(auto i : reservs)
	{
		this->totalPrice+= i->getPrice();
	}
}


double Invoice::getPrice() const
{
	return this->totalPrice;
}

ostream & operator<<(ostream out, Invoice inv)
{
	out << "Descrimination of every use of the court by the user:" << endl;
	for(unsigned int i = 0; i < inv.reservs.size(); i++)
	{
		out << i << " - " << inv.reservs[i]->day << "/" << inv.reservs[i]->month << " : " << inv.reservs[i]->getPrice() << endl;
	}
	out << "Final price:" << inv.getPrice();
}
