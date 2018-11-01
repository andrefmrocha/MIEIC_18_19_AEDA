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
//Needs: check error using reserveClass function
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
		//if(tennisCourts[j].reserveClass(month,day,startingHour,users[user_i],teachers[teacher_i]))
			return true;
	}
	return false;
}
//Needs: check error using reserveFree function
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
			//if(tennisCourts[j].reserveFree(month,day,startingHour,duration,users[user_i]))
				return true;
		}
		return false;
}

//Needs: teacher method to assign, create exceptions
bool Company::registerUser(string name, int age,bool isGold,string gender)
{
	/*if (age <0)
		throw(InvalidAge(int age));
	bool flag =false;
	for(size_t i =0; i<users.size();i++)
	{
		if(users[i]->getName() == name)
			flag=true;
	}
	if(flag)
		throw (AlreadyRegisteredUser(name));
	//here check which teacher to assign
	User newuser(name,age,gender);
	users.push_back(&newuser);
	*/
	return true;
}

//Needs: create exceptions
bool Company::registerTeacher(string teacherName, int age,string gender)
{
	/*if (age <0)
		throw(InvalidAge(int age));
	bool flag =false;
	for(size_t i =0; i<users.size();i++)
	{
		if(users[i]->getName() == name)
			flag=true;
	}
	if(flag)
		throw (AlreadyRegisteredUser(name));

	Teacher newteacher(name,age,gender);
	teachers.push_back(newteacher);
	*/
	return true;
}

//Needs: get vector of lessons from user's reservation, needs what() for ReportAlreadyExists exception
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
	/*
	try
	{
		Report newr(userName,teacherName,grade,addcomm,COLOCAR_VETOR_LESSONS);
	}
	catch(InvalidGrade &ig)
	{
		cout << ig ;
	}
	try
	{
		users[user_i]->setReport(newr,month);
	}
	catch (ReportAlreadyExists &r)
	{
		cout << r.what() << endl;
		return false;
	}*/
	return true;
}

//Needs: setInvoice for user
bool Company::makeUserInvoice(string userName,vector<Reservation *> reservs)
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
		//users[user_i]->setInvoice(newinvoice);
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
