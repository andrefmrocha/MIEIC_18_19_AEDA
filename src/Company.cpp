/*
 * Company.cpp
 *
 *  Created on: 30/10/2018
 *      Author: joaomartins
 */

#include "Company.h"

using namespace std;

Company::Company(double cardValue, Date d)
{
	this->cardValue = cardValue;
	date=d;
}

int Company::getMaxUser() const
{
	int maxusers=0;
	for(size_t i =0; i < tennisCourts.size();i++)
	{
		maxusers+=tennisCourts[i].getMaxUsers();
	}
	return maxusers;
}

void Company::createCourt()
{
	Court newcourt(year);
	tennisCourts.push_back(newcourt);

}

vector<Court> Company::getCourts()
{
	return tennisCourts;
}

vector<User> Company::getUsers()
{
	return users;
}

vector<Teacher> Company::getTeachers()
{
	return teachers;
}

int Company::getUser(string userName)
{
	for(int i = 0; i< users.size();i++)
	{
		if(users[i].getName() == userName)
			return i;
	}
	return -1;
}

bool Company::makeLesson(int month,int day,double startingHour,string userName,string teacherName)
{
	bool flag=true;
	size_t user_i=0;
	size_t teacher_i=0;
	for(size_t j =0;j<users.size();j++)
	{
		if(users[j].getName() == userName)
		{
			flag=false;
			user_i=j;
		}
	}
	if(flag)
		throw(NoUserRegistered(userName));

	flag=true;
	for(size_t j=0; j<teachers.size();j++)
	{
		if(teachers[j].getName() == teacherName)
		{
			flag=false;
			teacher_i=j;
		}
	}
	if(flag)
		throw(NoTeacherRegistered(teacherName));
	for(size_t j =0; j<tennisCourts.size();j++)
	{
		if(tennisCourts[j].reserveClass(month,day,startingHour,users[user_i],teachers[teacher_i]))
			return true;
	}
	return false;
}

bool Company::makeFree(int month,int day,double startingHour, int duration,string username)
{
	bool flag=true;
		size_t user_i=0;
		for(size_t j =0;j<users.size();j++)
		{
			if(users[j].getName() == username)
			{
				flag=false;
				user_i=j;
			}
		}
	if(flag)
		throw(NoUserRegistered(username));
	for(size_t j =0; j<tennisCourts.size();j++)
		{
			if(tennisCourts[j].reserveFree(month,day,startingHour,duration,users[user_i]))
				return true;
		}
		return false;
}

bool Company::registerUser(string name, int age,bool isGold,string gender)
{
	if (age <0)
		throw(InvalidAge(age));
	bool flag =false;
	for(size_t i = 0; i<users.size();i++)
	{
		if(users[i].getName() == name){
			flag=true;
			break;
		}
	}
	if(flag)
		throw (AlreadyRegisteredUser(name));
	size_t i2=0;
	for(size_t i = 1; i < teachers.size();i++)
	{
		if (teachers[i2].getnStudents() >= teachers[i].getnStudents())
			i2 = i;
	}
	User newuser(name,age,gender,isGold,teachers[i2].getName());
	users.push_back(newuser);
	return true;
}


bool Company::registerTeacher(string teacherName, int age,string gender)
{
	if (age <0)
		throw(InvalidAge(age));
	bool flag =false;
	for(size_t i =0; i<teachers.size();i++)
	{
		if(teachers[i].getName() == teacherName)
			flag=true;
	}
	if(flag)
		throw (AlreadyRegisteredTeacher(teacherName));

	Teacher newteacher(teacherName,age,gender);
	teachers.push_back(newteacher);

	return true;
}

bool Company::makeUserReport(int month,string userName,string teacherName)
{
	bool flag=true;
	size_t user_i=0;
	size_t teacher_i=0;
	for(size_t j =0;j<users.size();j++)
	{
		if(users[j].getName() == userName)
		{
			flag=false;
		user_i=j;
		}
	}
	if(flag)
		throw(NoUserRegistered(userName));

	flag=true;
	for(size_t j=0; j<teachers.size();j++)
	{
		if(teachers[j].getName() == teacherName)
		{
			flag=false;
			teacher_i=j;
		}
	}
	if(flag)
		throw(NoTeacherRegistered(teacherName));

	vector<Reservation*> lessons;
	for(size_t i =0; i< users[user_i].getReservations().size();i++) {
		if(users[user_i].getReservations()[i]->getPrice() > 30)
			lessons.push_back(users[user_i].getReservations()[i]);
	}

	try
	{
		Report* newr= new Report(userName,teacherName,lessons);
		users[user_i].setReport(newr,month);
	}
	catch (ReportAlreadyExists &r)
	{
		cout << r.what() << endl;
		return false;
	}
	return true;
}

bool Company::makeUserInvoice(string userName,int month, vector<Reservation *> reservs)
{
	bool flag=true;
		size_t user_i=0;
		for(size_t j =0;j<users.size();j++)
		{
			if(users[j].getName() == userName)
			{
				flag=false;
				user_i=j;
			}
		}
		if(flag)
			throw(NoUserRegistered(userName));
		Invoice* newinvoice = new Invoice(users[user_i].getName(),users[user_i].getTeacher(),users[user_i].getReservations());
		try
		{
			users[user_i].setInvoice(newinvoice,month);
		}
		catch(IncorrectMonth &e)
		{
			cout << e.what() << endl;
			return false;
		}
		catch(InvoiceAlreadyExists &e)
		{
			cout << e.what()<<endl;
			return false;
		}
		return true;
}

bool Company::showReport(string name, int month)
{
		int i = getUser(name);
		if (i == -1)
			throw(NoUserRegistered(name));
		try
		{
			cout << users[i].getReport(month);
		}
		catch (IncorrectMonth &e)
		{
			cout << e.what() << endl;
			return false;
		}
		catch (ReportNotAvailable &e)
		{
			cout << e.what() << endl;
			return false;
		}
		return true;
}

bool Company::showInvoice(string name,int month)
{
		int i = getUser(name);
		if (i == -1)
			throw(NoUserRegistered(name));
		try
		{
			cout << users[i].getInvoice(month);
		}
		catch (IncorrectMonth &e)
		{
			cout << e.what() << endl;
			return false;
		}
		catch (InvoiceNotAvailable &e)
		{
			cout << e.what() << endl;
			return false;
		}
		return true;
}

void Company::indentation(std::ofstream &outfile, int indent)
{
    for(int i = 0; i < indent; i++)
    {
        outfile << "\t";
    }
}

void Company::storeInfo(std::ofstream &outfile, int indent) {
	indentation(outfile, indent);
	outfile << "{" << endl;
	indent++;
	indentation(outfile, indent);
	outfile << "\"tennisCourts\": [" << endl;
	indent++;
	for(unsigned int i = 0; i < this->tennisCourts.size(); i++)
	{
		this->tennisCourts[i].storeInfo(outfile, indent);
		if(i+1 != this->tennisCourts.size())
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
	outfile << "\"users\": [" << endl;
	indent++;
	for(unsigned int i = 0; i < this->users.size(); i++)
	{
		this->users[i].storeInfo(outfile, indent);
		if(i+1 != this->users.size()) {
			indentation(outfile, indent);
			outfile << "," << endl;
		}
		else
		{
			//outfile << endl;
		}
	}
	indent--;
	indentation(outfile, indent);
	outfile << "]," << endl;
	indentation(outfile, indent);
	outfile << "\"teachers\": [" << endl;
	indent++;
	for(unsigned int i = 0; i < this->teachers.size(); i++)
	{
		this->teachers[i].storeInfo(outfile, indent);
		if(i+1 != this->teachers.size()) {
			indentation(outfile, indent);
			outfile << "," << endl;
		}
		else
		{
			//outfile << endl;
		}
	}
	indent--;
	indentation(outfile, indent);
	outfile << "]," << endl;
	indentation(outfile, indent);
	outfile << "\"cardValue\": " << this->cardValue <<  "," << endl;
	indentation(outfile, indent);
	outfile << "\"Date\": " << endl;
	indent++;
	date.storeInfo(outfile,indent);
	outfile << endl;
	indent--;
	indentation(outfile, indent);
	outfile << "}";
}

void Company::readInfo(std::ifstream &infile) {
	string savingString;
	while (getline(infile, savingString)) {
		if (savingString.find("tennisCourts") != string::npos) {
			while (getline(infile, savingString)) {
				Court c;
				c.readInfo(infile);
				tennisCourts.push_back(c);
				if (savingString.find(']') != string::npos) {
					break;
				}
			}
		}

		if (savingString.find("users") != string::npos) {
			while (getline(infile, savingString)) {
				User u;
				u.loadClass(infile);
				users.push_back(u);
				if (savingString.find(']') != string::npos) {
					break;
				}
			}
		}

		if (savingString.find("teachers") != string::npos) {
			while (getline(infile, savingString)) {
				Teacher t;
				t.loadClass(infile);
				teachers.push_back(t);
				if (savingString.find(']') != string::npos) {
					break;
				}
			}
		}

		if (savingString.find("cardValue") != string::npos) {
			savingString = savingString.substr(savingString.find("cardValue") + 11);
			savingString = savingString.substr(0, savingString.find(','));
			this->cardValue = stod(savingString);
		}

		if (savingString.find("year") != string::npos) {
			savingString = savingString.substr(savingString.find("year") + 7);
			savingString = savingString.substr(0, savingString.find_last_of(','));
			this->year = stoi(savingString);
		}

		if (savingString.find("Date") != string::npos) {
			Date d;
			d.readInfo(infile);
			this->date = d;
		}
	}
}

Company Company::operator++() {
	++this->date;
	if(date.getDay() == 1) {
		for(size_t i = 0; i < users.size();i++) {
			 /* if(date.getMonth() == 1) {
			 * users[i].clearReservations();
			 * users[i].clearInvoices();
			 * }*/
			makeUserReport(date.getMonth(),users[i].getName(),users[i].getTeacher());
			makeUserInvoice(users[i].getName(),date.getMonth(),users[i].getReservations());
		}
	}
	return *this;
}

//Exception Handling

string NoUserRegistered::what() const
{
	return "The user with name: " + name + ", is not registered in the system. Please register first.";
}

string NoTeacherRegistered::what() const
{
	return "The teacher with name: " + name + ", is not registered in the system. Please register first.";
}

string InvalidAge::what() const
{
	return "This age is invalid: " + to_string(this->age);
}

string AlreadyRegisteredUser::what() const
{
	return "There is already a registered user with the name: " + this->name;
}

string AlreadyRegisteredTeacher::what() const
{
	return "There is already a registered teacher with the name: " + this->name;
}
