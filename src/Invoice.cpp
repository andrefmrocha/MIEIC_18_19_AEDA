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
	if(inv.getReservs().empty()) {
		out << "There were no reservations made by the user for this month." << endl;
		//Check if user is gold  and put monthly fee
	}
	out << "Discrimination of every use of the court by the user:" << endl;
	for(unsigned int i = 0; i < inv.getReservs().size(); i++)
	{
		out << i +1 << " - " << inv.getReservs()[i]->getDay() << "/" << inv.getReservs()[i]->getMonth() << " : " << inv.getReservs()[i]->getPrice() << endl;
	}
	out << "Final price:" << inv.getPrice();
	return out;
}

void Invoice::indentation(std::ofstream &outfile, int indent)
{
	for(int i = 0; i < indent; i++)
	{
		outfile << "\t";
	}
}


void Invoice::storeInfo(std::ofstream &outfile, int indent)
{
	indentation(outfile, indent);
	outfile << "{" << endl;
	indent++;
	indentation(outfile, indent);
	outfile << "\"reservs\": [" << endl;
	indent++;
	for(unsigned int i = 0; i < this->reservs.size(); i++)
	{
		this->reservs[i]->storeInfo(outfile, indent);
		if(i+1 != this->reservs.size())
			outfile << "," << endl;
		else
		{
			outfile << endl;
		}
	}
	indent--;
	indentation(outfile, indent);
	outfile << "]," << endl;
	indentation(outfile, indent);
	outfile << "\"totalPrice\": " << this->totalPrice <<  "," << endl;
	indentation(outfile, indent);
	outfile << "\"name\": " << "\"" << this->name << "\"" << "," << endl;
	indentation(outfile, indent);
	outfile << "\"assignedTeacher\": " << "\"" << this->assignedTeacher << "\""<< endl;
	indent--;
	indentation(outfile, indent);
	outfile << "}";
}


void Invoice::readInfo(std::ifstream &infile)
{
	string savingString;
	while (getline(infile, savingString))
	{
		if(savingString.find("reservs") != string::npos)
		{
			while (getline(infile, savingString))
			{
				if(savingString.find("free") != string::npos)
				{
					Reservation * free = new Free();
					free->readInfo(infile);
					reservs.push_back(free);
				}

				if(savingString.find("lesson") != string::npos)
				{
					Reservation * free = new Lesson();
					free->readInfo(infile);
					reservs.push_back(free);
				}

				if(savingString.find(']') != string::npos)
				{
					break;
				}
			}
		}

		if(savingString.find("totalPrice") != string::npos)
		{
			savingString = savingString.substr(savingString.find("totalPrice") + 12);
			savingString = savingString.substr(0, savingString.find(','));
			this->totalPrice = stoi(savingString);
		}

		if(savingString.find("name") != string::npos)
		{
			savingString = savingString.substr(savingString.find("name") + 7);
			savingString = savingString.substr(1, savingString.find_last_of('\"') - 1);
			this->name = savingString;
		}

		if(savingString.find("assignedTeacher") != string::npos)
		{
			savingString = savingString.substr(savingString.find("assignedTeacher") + 18);
			savingString = savingString.substr(1, savingString.find_last_of('\"') - 1);
			this->assignedTeacher = savingString;
		}
	}
}