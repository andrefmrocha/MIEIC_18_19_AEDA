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

User& Company::getUser(string userName)
{
	User u(userName,0,"",false,"");
	vector<User>::iterator it = find(users.begin(),users.end(),u);
	if(it != users.end())
		return *it;
	else
		throw NoUserRegistered(userName);
}

Teacher& Company::getTeacher(std::string teacherName) {
	Teacher t(teacherName,0,"");
	vector<Teacher>::iterator it = find(teachers.begin(),teachers.end(),t);
	if(it != teachers.end())
		return *it;
	else
		throw NoTeacherRegistered(teacherName);
}

bool Company::makeLesson(int month,int day,double startingHour,string userName,string teacherName)
{
	if(month < date.getMonth() || (month >= date.getMonth() && day < date.getDay())) {
		throw(InvalidDate(day,month));
	}

	try {
		User& u = getUser(userName);
		Teacher& t = getTeacher(teacherName);
		for(size_t j =0; j<tennisCourts.size();j++)
		{
			if(tennisCourts[j].reserveClass(month,day,startingHour,u,t))
				return true;
		}
		return false;
	}
	catch(NoUserRegistered &u) {
		cout << u.what() << endl;
		return false;
	}
	catch(NoTeacherRegistered &t)
	{
		cout << t.what() << endl;
		return false;
	}
}

bool Company::makeFree(int month,int day,double startingHour, int duration,string username)
{
	if(month < date.getMonth() || (month >= date.getMonth() && day < date.getDay())) {
		throw(InvalidDate(day,month));
	}

	try {
		User& u = getUser(username);
		for(size_t j =0; j<tennisCourts.size();j++)
		{
			if(tennisCourts[j].reserveFree(month,day,startingHour,duration,u))
				return true;
		}
		return false;
	}
	catch(NoUserRegistered &u) {
		cout << u.what() << endl;
		return false;
	}
}

bool Company::registerUser(string name, int age,bool isGold,string gender)
{
	if (age <0)
		throw(InvalidAge(age));
	try {
		User& u = getUser(name);
		throw(AlreadyRegisteredUser(name));
	}
	catch(NoUserRegistered &u) {
		size_t i2=0;
		for(size_t i = 1; i < teachers.size();i++)
		{
			if (teachers[i2].getnStudents() >= teachers[i].getnStudents())
				i2 = i;
		}
		teachers[i2].addStudent();
		User newuser(name,age,gender,isGold,teachers[i2].getName());
		users.push_back(newuser);
		return true;
	}
	catch(AlreadyRegisteredUser &u) {
		cout << u.what() << endl;
		return false;
	}
}


bool Company::registerTeacher(string teacherName, int age,string gender)
{
	if (age <0)
		throw(InvalidAge(age));
	try {
		Teacher& t = getTeacher(teacherName);
		throw(AlreadyRegisteredTeacher(teacherName));
	}
	catch(NoTeacherRegistered &t) {
		Teacher newteacher(teacherName,age,gender);
		teachers.push_back(newteacher);
		return true;
	}
	catch(AlreadyRegisteredTeacher &u) {
		cout << u.what() << endl;
		return false;
	}
}

bool Company::makeUserReport(int month,string userName,string teacherName)
{
	try
	{
	 	User& u = getUser(userName);
	 	Teacher& t = getTeacher(teacherName);
		vector<Reservation*> lessons;
		for(size_t i =0; i< u.getReservations().size();i++) {
			if(u.getReservations()[i]->getPrice() > 30)
				lessons.push_back(u.getReservations()[i]);
		}
		Report* newr = new Report(userName,teacherName,lessons);
		u.setReport(newr,month);
	}
	catch(NoUserRegistered &u)
	{
		cout << u.what() << endl;
		return false;
	}
	catch(NoTeacherRegistered &t)
	{
		cout << t.what() << endl;
		return false;
	}
	catch(IncorrectMonth &e)
	{
		cout << e.what() << endl;
		return false;
	}
	catch (ReportAlreadyExists &r)
	{
		cout << r.what() << endl;
		return false;
	}
	return true;
}

bool Company::makeUserInvoice(string userName,int month)
{
	try
	{
		User& u = getUser(userName);
		Invoice* newinvoice = new Invoice(u.getName(),u.getTeacher(),u.getReservations(), u.getisGold());
		u.setInvoice(newinvoice,month);
	}
	catch(NoUserRegistered &u)
	{
		cout << u.what() << endl;
		return false;
	}
	catch(NoTeacherRegistered &t)
	{
		cout << t.what() << endl;
		return false;
	}
	catch(IncorrectMonth &e)
	{
		cout << e.what() << endl;
		return false;
	}
	catch (InvoiceAlreadyExists &i)
	{
		cout << i.what() << endl;
		return false;
	}
	return true;
}

bool Company::showReport(string name, int month)
{
	User u;
	try {
		u = getUser(name);
	}
	catch(NoUserRegistered &e) {
		cout << e.what() << endl;
		return false;
	}

	try
	{
		cout << u.getReport(month);
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
	User u;
	try {
		u = getUser(name);
	}
	catch(NoUserRegistered &e) {
		cout << e.what() << endl;
		return false;
	}
	try
	{
		cout << u.getInvoice(month) << endl;
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

void Company::indentation(std::ofstream &outfile, int indentation)
{
    for(int i = 0; i < indentation; i++)
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
				if (savingString.find(']') != string::npos) {
					break;
				}
				User u;
				u.loadClass(infile);
				users.push_back(u);
			}
		}

		if (savingString.find("teachers") != string::npos) {
			while (getline(infile, savingString)) {
				if (savingString.find(']') != string::npos) {
					break;
				}
				Teacher t;
				t.loadClass(infile);
				teachers.push_back(t);
				getline(infile,savingString);

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
			if(date.getMonth() == 1) {
				users[i].cleanVectors();
			}

			makeUserReport(date.getMonth()-1,users[i].getName(),users[i].getTeacher());
			makeUserInvoice(users[i].getName(),date.getMonth()-1);
			users[i].cleanReservations();
		}
		for(size_t i = 0; i<teachers.size();i++) {
			teachers[i].cleanVectors();
		}
	}
	return *this;
}

bool compareUser (User &u1,User &u2) {
    return u1.getName() < u2.getName();
}
void Company::showUsers() {

    sort(users.begin(),users.end(),compareUser);
	for(size_t i = 0; i< users.size();i++) {
		cout << "User no. " << i+1 << ":" << endl;
		users[i].show();
		cout << endl;
	}
}

bool compareTeacher (Teacher &t1,Teacher &t2) {
    return t1.getName() < t2.getName();
}
void Company::showTeachers() {

    sort(teachers.begin(),teachers.end(),compareTeacher);
	for(size_t i = 0; i< teachers.size();i++) {
		cout << "Teacher no. " << i+1 << ":" << endl;
		teachers[i].show();
		cout << endl;
	}
}

void Company::showTeacher(std::string teacher) {
	try {
		Teacher t = getTeacher(teacher);
		t.show();
	}
	catch (NoTeacherRegistered &e)
	{
		cout << e.what() << endl;
	}
}

void Company::showUser(std::string name) {
	try {
		User u = getUser(name);
		u.show();
	}
	catch (NoUserRegistered &e)
	{
		cout << e.what() << endl;
	}
}

void Company::showCourts() {
	int n=0;
	for(size_t i=0; i<tennisCourts.size();i++) {
		try{
			tennisCourts[i].occupied(date.getMonth(),date.getDay(),8,12);
			n++;
		}
		catch(CourtReserved &c)
		{}
	}
	cout << "There are " << n << " courts available for today." << endl;
	cout << "There is a maximum of " << tennisCourts[0].getMaxUsers() << " per court." << endl;
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

std::string InvalidDate::what() const {
	return "The date given is invalid. Day " + to_string(day) + " of month " + to_string(month) + " has passed.";
}
