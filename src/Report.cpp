/*
 * Report.cpp
 *
 *  Created on: 25/10/2018
 *      Author: joaomartins
 */

#include "Report.h"
#include "Gradetempl.h"

using namespace std;




Report::Report(string userName,string teacherName,const vector<Reservation*> &reservs)
{
    int grade = (int)(ceil(reservs.size() /1.5));
	if(grade ==0)
	    grade++;
	else if(grade>5)
	    grade =5;
    name = userName;
	this->teacherName = teacherName;
	this->grade = grade;
	this->reservations = reservs;
}

string Report::getName()
{
	return name;
}
string Report::getTeacherName()
{
	return teacherName;
}

int Report::getGrade()
{
	return grade;
}
vector<Reservation*> Report::getLessons()
{
	return reservations;
}
string getHourFormat(double hour) {
	string hr = to_string((int)(ceil(hour -0.5)));
	hr += ":";
	if((hour - floor(hour)) == 0)
	    hr += "00";
	else
	    hr+= "30";
	return hr;
}

ostream & operator <<(ostream &os,Report r)
{
	os << "Name: " << r.getName() << endl
		<< "Teacher: " << r.getTeacherName() << endl
		<< "Report details: " << endl << endl
		<< "Classes attended this month: " << endl;
	for (size_t i =0; i < r.getLessons().size();i++)
	{
		os << " \t Date: " << r.getLessons()[i]->getDay() << "/" << r.getLessons()[i]->getMonth() << endl
		<< " \t Period of class: " << getHourFormat(r.getLessons()[i]->getStartingHour()) << " - " << getHourFormat(r.getLessons()[i]->getStartingHour()+r.getLessons()[i]->getDuration()) << endl << endl;
	}
	switch(r.getGrade())
	{
	case 1:
		grade_1(os);
		break;
	case 2:
		grade_2(os);
		break;
	case 3:
		grade_3(os);
		break;
	case 4:
		grade_4(os);
		break;
	case 5:
		grade_5(os);
		break;
	default:
		break;
	}
	return os;
}

void Report::indentation(std::ofstream &outfile, int indent)
{
	for(int i = 0; i < indent; i++)
	{
		outfile << "\t";
	}
}

void Report::storeInfo(ofstream &outfile, int indent)
{
	indentation(outfile, indent);
	outfile << "{" << endl;
	indent++;
	indentation(outfile, indent);
	outfile << "\"reservations\": [" << endl;
	indent++;
	for(unsigned int i = 0; i < this->reservations.size(); i++)
	{
		this->reservations[i]->storeInfo(outfile, indent);
		if(i+1 != this->reservations.size())
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
	outfile << "\"name\": " << "\""<< this->name << "\""<<  "," << endl;
	indentation(outfile, indent);
	outfile << "\"teacherName\": " << "\"" << this->teacherName << "\"" << "," << endl;
	indentation(outfile, indent);
	outfile << "\"grade\": " << this->grade <<  "," << endl;
	indent--;
	indentation(outfile, indent);
	outfile << "}";
}

void Report::readInfo(std::ifstream &infile)
{
	bool flag = false;
	string savingString;
	while (getline(infile, savingString))
	{
		if(savingString.find("reservations") != string::npos)
		{
			while (getline(infile, savingString))
			{
				if(savingString.find("free") != string::npos)
				{
					Reservation * free = new Free();
					free->readInfo(infile);
					reservations.push_back(free);
				}

				if(savingString.find("lesson") != string::npos)
				{
					Reservation * free = new Lesson();
					free->readInfo(infile);
					reservations.push_back(free);
				}

				if(savingString.find(']') != string::npos)
				{
					break;
				}
			}
		}

		if(savingString.find("name") != string::npos)
		{
			savingString = savingString.substr(savingString.find("name") + 7);
			savingString = savingString.substr(1, savingString.find_last_of('\"') - 1);
			this->name = savingString;
		}

		if(savingString.find("teacherName") != string::npos)
		{
			savingString = savingString.substr(savingString.find("teacherName") + 14);
			savingString = savingString.substr(1, savingString.find_last_of('\"') - 1);
			this->teacherName = savingString;
		}

		if(savingString.find("grade") != string::npos)
		{
			flag = true;
			savingString = savingString.substr(savingString.find("grade") + 7);
			savingString = savingString.substr(0, savingString.find(','));
			this->grade = stoi(savingString);
		}

		if(flag)
		{
			break;
		}
	}
}
