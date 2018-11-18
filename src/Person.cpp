/*
 * Person.cpp
 *
 *  Created on: 21/10/2018
 *      Author: anamargaridarl
 */

#include "Person.h"



using namespace std;

void indentp(std::ofstream &outfile, int &indentation)
{
	for(int i = 0; i < indentation; i++)
	{
		outfile << "\t";
	}
}


////////////////////////////////////////////////////////////////////////////
//////////////////Person////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////

Person::Person()
{

}

Person::Person(string name,int age,string gender)
{
	this->name=name;
	this->age=age;
	this->gender=gender;
}

string Person::getName() const
{
	return name;
}

int Person::getAge()
{
	return age;
}

string Person::getGender()
{
	return gender;
}

void Person::setName(string name)
{
	this->name=name;
}

void Person::setAge(int age)
{
	this->age=age;
}

void  Person::setGender(string gender)
{
	this->gender=gender;
}


void Person::storeInfo(ofstream &outfile, int &indentation)
{
	indentp(outfile,indentation);
	outfile << "{" << endl;
	indentation++;
	indentp(outfile,indentation);
	outfile << "\"name\": " << "\"" << name<<  "\"" << "," <<  endl;
	indentp(outfile,indentation);
	outfile << "\"age\": "<< "\"" << age  << "\"" << "," <<  endl;
	indentp(outfile,indentation);
	outfile << "\"gender\": "<< "\"" << gender  << "\""  << "," << endl;
}

bool Person::operator == (const Person & p1)
{
	return this->getName() == p1.getName();
}


void Person::loadClass(std::ifstream &inpfile)
{
	string savingString;

	while(getline(inpfile, savingString))
	{
		if(savingString.find("{") !=string::npos)
			continue;
		else
		{
			if(savingString.find("\"name\": ") != string::npos)
			{
				savingString = savingString.substr(savingString.find(":")+3);
				savingString = savingString.substr(0, savingString.find(",")-1);
				this->name =savingString;
			}
			if(savingString.find("\"age\"") != string::npos)
			{
				savingString = savingString.substr(savingString.find(":")+3);
				savingString = savingString.substr(0, savingString.find(",")-1);
				this->age= stoi(savingString);
			}
			if(savingString.find("\"gender\": ") != string::npos)
			{
				savingString = savingString.substr(savingString.find(":")+3);
				savingString = savingString.substr(0, savingString.find(",")-1);
				 this->gender = savingString;
				 break;
			}
		}
	}

}

void Person::show()
{
	cout << "Name: " << name << endl;
	cout << "Age: " << age << endl;
	cout << "Gender: " << gender << endl;
}

////////////////////////////////////////////////////////////////////////////
double calculateEndHour(double startinghour, int duration)
{
	return startinghour + 0.5*duration;
}



////////////////////////////////////////////////////////////////////////////
//////////////////Teacher///////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
Teacher::Teacher()
{

}

Teacher::Teacher(string name, int age, string gender):Person(name,age,gender)
{
	nStudents = 0;
}

void Teacher::setLesson(Lesson* lesson)
{
	/*
	 * startingHour and endHour are related to reservation to set in vector
	 * resStart and resEnd are related to the reservations in the vector
	 */

	double startingHour, endHour;
	int duration;

	duration = lesson->getDuration();
	startingHour = lesson->getStartingHour();

	endHour = calculateEndHour(startingHour, duration);

//	if(CheckAvailable(lessons,startingHour,endHour)==0)
	this->lessons.push_back(lesson);
}

vector<Lesson*> Teacher::getLessons()
{
	return lessons;
}

int Teacher::getnStudents()
{
	return nStudents;
}

void Teacher::addStudent()
{
	nStudents++;
}

void Teacher::storeInfo(ofstream &outfile, int &indentation)
{
	Person::storeInfo(outfile,indentation);

	indentp(outfile,indentation);
	outfile<< "\"lessons\": ";
	outfile << "["<< endl;
	for(size_t i= 0; i < lessons.size(); i++)
	{
		int in=indentation+1;;
		if(lessons.at(i) != 0)
		{
		indentp(outfile,indentation);
		lessons.at(i)->storeInfo(outfile,in);
		outfile << " , " <<endl;
		}
	}
	indentp(outfile,indentation);
	outfile << "]"<< endl;

	indentation--;
	indentp(outfile,indentation);
	outfile<<"}"<< endl;

}


void Teacher::loadClass(std::ifstream &inpfile)
{
	Person::loadClass(inpfile);

	string savingString;

	getline(inpfile, savingString); //lessons

		if(savingString.find("lessons") != string::npos)
		{
		while(getline(inpfile, savingString) && savingString.find("]") )
		{
			getline(inpfile, savingString); //linha type
			Lesson *A = new Lesson();
			getline(inpfile, savingString);
			A->readInfo(inpfile);
			lessons.push_back(A);
			getline(inpfile, savingString); //}

		}
		}

}

void Teacher::show()
{
	Person::show();
	cout << "Number of students: "<< nStudents << endl;
}

void Teacher::cleanVectors()
{
	lessons.clear();
}



////////////////////////////////////////////////////////////////////////////
//////////////////User//////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
User::User()
{

}


User::User(string name,int age,string gender, bool isGold, string assignedTeacher):Person(name,age,gender)
{
	this->isGold = isGold;
	this->assignedTeacher = assignedTeacher;
	reports.resize(12);
	invoices.resize(12);
}

void User::makeGold()
{
	isGold = true;
}

void User::stopGold()
{
	isGold = false;
}

bool User::getisGold()
{
	return isGold;
}

Report User::getReport(int month)
{
	if(month > 12)
		throw(IncorrectMonth());

	if(reports.at(month -1) == 0)
	{
		throw(ReportNotAvailable(month));
	}
	else
		return *reports.at(month -1);
}

Invoice User::getInvoice(int month)
{
	if(month > 12)
			throw(IncorrectMonth());

		if(invoices.at(month -1) == 0)
		{
			throw(InvoiceNotAvailable(month));
		}
		else
			return *invoices.at(month -1);
}

void User::setReport(Report* report, int month)
{
	if(month > 12)
			throw(IncorrectMonth());

	if(reports.at(month-1)!=0)
	{
		throw(ReportAlreadyExists(month));
	}
	else
	{
		reports.at(month-1)= report;
	}
}

void User::setInvoice(Invoice* invoice, int month)
{
	if(month > 12)
				throw(IncorrectMonth());

		if(invoices.at(month-1)!=0)
		{
			throw(InvoiceAlreadyExists(month));
		}
		else
		{
			invoices.at(month-1)= invoice;
		}
}

void User::setReservation(Reservation* reservation)
{
	/*
	 * startingHour and endHour are related to reservation to set in vector
	 * resStart and resEnd are related to the reservations in the vector
	 */

	double startingHour, endHour;
	int duration;

	duration = reservation->getDuration();
	startingHour = reservation->getStartingHour();

	endHour = calculateEndHour(startingHour, duration);

	if(CheckAvailable(reservations,startingHour,endHour, reservation->getDay(), reservation->getMonth())==0)
		reservations.push_back(reservation);
}

vector<Reservation*> User::getReservations()
{
	return reservations;
}

string User::getTeacher()
{
	return this->assignedTeacher;
}

vector<Invoice*> User::getInvoices()
{
	return invoices;
}

void User::storeInfo(ofstream &outfile, int &indentation)
{
	Person::storeInfo(outfile, indentation);

	indentp(outfile,indentation);
	outfile << "\"isGold\": "<< "\""<< isGold << "\""<< "," << endl;
	indentp(outfile,indentation);
	outfile << "\"assigned Teacher\": "<< "\""<< assignedTeacher <<"\"" << "," <<  endl;
	indentp(outfile,indentation);

	outfile<< "\"reports\": ";
	outfile << "["<< endl;
	int in=indentation+1;
	for(size_t i =0; i < reports.size(); i++)
	{
		if(reports.at(i) != 0)
		{
		indentp(outfile,in);
		reports.at(i)->storeInfo(outfile,in);
		outfile << " , " <<endl;
		}
	}
	indentp(outfile,indentation);
	outfile << "]"<<","<<endl;

	indentp(outfile,indentation);
	outfile<< "\"reservations\": ";
	outfile << "["<< endl;
	for(size_t i =0; i < reservations.size(); i++)
	{
		if(reservations.at(i) != 0)
		{
		indentp(outfile,in);
		reservations.at(i)->storeInfo(outfile,in);
		outfile << " , " <<endl;
		}
	}
	indentp(outfile,indentation);
	outfile << "]"<< ","<<endl;

	indentp(outfile,indentation);
	outfile<< "\"invoices\": ";
	outfile << "["<< endl;
	for(size_t i =0; i < invoices.size(); i++)
	{
		if(invoices.at(i) != 0)
		{
		indentp(outfile,in);
		invoices.at(i)->storeInfo(outfile,in);
		outfile << " , " <<endl;
		}
	}

	indentp(outfile,indentation);
	outfile << "]"<< endl;

	indentation--;
	indentp(outfile,indentation);
	outfile<<"}"<< endl;

}



void User::loadClass(std::ifstream &inpfile) {
	Person::loadClass(inpfile);
	bool flag = true;
	string savingString;

	while (getline(inpfile, savingString) && flag) {
		if (savingString.find("\"isGold\": ") != string::npos) {
			savingString = savingString.substr(savingString.find(":") + 3);
			savingString = savingString.substr(0, savingString.find(",") - 1);

			int i = stoi(savingString);
			if (i == 1)
				this->isGold = true;
			else
				this->isGold = false;
		}

		if (savingString.find("\"assigned Teacher\": ") != string::npos) {
			savingString = savingString.substr(savingString.find(":") + 3);
			savingString = savingString.substr(0, savingString.find(",") - 1);
			this->assignedTeacher = savingString;
		}

		if (savingString.find("\"reports\": ") != string::npos) {
			while (getline(inpfile, savingString) && !savingString.find("]")) {
				Report *I = new Report();
				I->readInfo(inpfile);
				reports.push_back(I);
				//getline(inpfile, savingString);
			}
			flag = false;
		}
	}

	if (savingString.find("\"reservations\": ") != string::npos) {

		while (getline(inpfile, savingString) && !savingString.find("]")) {
			//getline(inpfile, savingString);// type
			if (savingString.find("\"free\"") != string::npos) {
				Free *F = new Free();
				F->readInfo(inpfile);
				reservations.push_back(F);
				getline(inpfile, savingString);
			}
			else if (savingString.find("\"lesson\"") != string::npos) {
				Lesson *L = new Lesson();
				L->readInfo(inpfile);
				reservations.push_back(L);
				getline(inpfile, savingString); //}
			}
		}
	}

	if (savingString.find("\"invoices\": ") != string::npos) {
		while (getline(inpfile, savingString) && !savingString.find("]")) {
			Invoice *I = new Invoice();
			I->readInfo(inpfile);
			invoices.push_back(I);
			//getline(inpfile, savingString);
		}
		flag = false;
	}
}



void User::show()
{
	string a;

	Person::show();
	if(isGold)
	{
		a = "yes";
	}
	else
		a = "no";

	cout << "isGold: " << a<< endl;
	cout <<"Assigned Teacher: "<< assignedTeacher << endl;

}

void User::cleanVectors()
{
	reservations.clear();
	invoices.clear();
	invoices.resize(12);

}

void User::cleanReports()
{
	reports.clear();
}

/*
void User::showReports(int month)
{
	reports.at(month-1)->showReport();
}

void User::showInvoices(int month)
{
	invoices.at(month-1)->showReport();
}
*/



/////////////////////////////////////////////////////////////////////////////////////////
//Handling exceptions
string ReportAlreadyExists::what() const
{
	return "The Report of month " + to_string(month) + " is already associated with the user";
}

string InvoiceAlreadyExists::what() const
{
	return "The Invoice of month " + to_string(month) + " is already associated with the user";
}


string ReportNotAvailable::what() const
{
	return "There is no report available of month " + to_string(month)  + " associated with the user";
}

string InvoiceNotAvailable::what() const
{
	return "There is no invoice available of month " + to_string(month)  + " associated with the user";
}
string IncorrectMonth::what() const
{
	return "Incorrect month ";
}

string InsideRes::what() const
{
	return "Schedule unavailable. A reservation is already made between " + to_string(resStart) + " and " + to_string(endHour);
}

string EndHourInsideRes::what() const
{
	return "Schedule unavailable. A reservation is already made  between " + to_string(resStart) + " and " + to_string(resEnd);
}

string StartHourInsideRes::what() const
{
	return "Schedule unavailable. A reservation is already made  between " + to_string(StartingHour) + " and " + to_string(endHour);
}

