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

vector<Reservation*> Invoice::getReservs()
{
	return reservs;
}
ostream & operator<<(ostream &out, Invoice inv)
{
	out << "Discrimination of every use of the court by the user:" << endl;
	for(unsigned int i = 0; i < inv.getReservs().size(); i++)
	{
		out << i << " - " << inv.getReservs()[i]->getDay() << "/" << inv.getReservs()[i]->getMonth() << " : " << inv.getReservs()[i]->getPrice() << endl;
	}
	out << "Final price:" << inv.getPrice();
	return out;
}

