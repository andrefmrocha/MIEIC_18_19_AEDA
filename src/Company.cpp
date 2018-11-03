/*
 * Company.cpp
 *
 *  Created on: 30/10/2018
 *      Author: joaomartins
 */

#include "Company.h"

using namespace std;

Company::Company(double cardValue, int year) : year(year)
{
	this->cardValue = cardValue;
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


bool Company::makeLesson(int month,int day,double startingHour,string userName,string teacherName)
{
	bool flag=true;
	size_t user_i=0;
	size_t teacher_i=0;
	for(size_t j =0;j<users.size();j++)
	{
		if(users[j]->getName() == userName)
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
		if(tennisCourts[j].reserveClass(month,day,startingHour,*users[user_i],teachers[teacher_i]))
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
			if(users[j]->getName() == username)
			{
				flag=false;
				user_i=j;
			}
		}
	if(flag)
		throw(NoUserRegistered(username));
	for(size_t j =0; j<tennisCourts.size();j++)
		{
			if(tennisCourts[j].reserveFree(month,day,startingHour,duration,*users[user_i]))
				return true;
		}
		return false;
}

bool Company::registerUser(string name, int age,bool isGold,string gender)
{
	if (age <0)
		throw(InvalidAge(age));
	bool flag =false;
	cout << users.size() << endl;
	for(size_t i =0; i<users.size();i++)
	{
		if(users[i]->getName() == name){
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
	teachers[i2].addStudent();
	User newuser(name,age,gender,isGold,teachers[i2].getName());
	users.push_back(&newuser);

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

bool Company::makeUserReport(int month,string userName,string teacherName, int grade,string addcomm)
{
	bool flag=true;
	size_t user_i=0;
	size_t teacher_i=0;
	for(size_t j =0;j<users.size();j++)
	{
		if(users[j]->getName() == userName)
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

	try
	{
		Report newr(userName,teacherName,grade,addcomm,users[user_i]->getReservations());
		users[user_i]->setReport(newr,month);
	}
	catch(InvalidGrade &ig)
	{
		cout << ig ;
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
			if(users[j]->getName() == userName)
			{
				flag=false;
			user_i=j;
			}
		}
		if(flag)
			throw(NoUserRegistered(userName));
		Invoice newinvoice(users[user_i]->getName(),users[user_i]->getTeacher(),users[user_i]->getReservations());
		try
		{
			users[user_i]->setInvoice(newinvoice,month);
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
