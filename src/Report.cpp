/*
 * Report.cpp
 *
 *  Created on: 25/10/2018
 *      Author: joaomartins
 */

#include "Report.h"
#include "Gradetempl.h"

using namespace std;




Report::Report(string userName,string teacherName,int grade, string addcomm, const vector<Reservation*> &reservs)
{
	if (grade > 5 || grade < 1)
		throw (InvalidGrade(grade));
	name = userName;
	this->teacherName = teacherName;
	this->grade = grade;
	this->addcomm = addcomm;
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

string Report::getAddComm()
{
	return addcomm;
}

int Report::getGrade()
{
	return grade;
}
vector<Reservation*> Report::getLessons()
{
	return reservations;
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
		<< " \t Period of class: " << " TO BE IMPLEMENTED" << endl << endl;
	}
	switch(r.getGrade())
	{
	case 1:
		grade_1(os,r.getAddComm());
		break;
	case 2:
		grade_2(os,r.getAddComm());
		break;
	case 3:
		grade_3(os,r.getAddComm());
		break;
	case 4:
		grade_4(os,r.getAddComm());
		break;
	case 5:
		grade_5(os,r.getAddComm());
		break;
	default:
		break;
	}
	return os;
}


std::ostream & operator << (std::ostream &os,const InvalidGrade &ig)
{
	os << "Invalid grade: " << ig.getGrade() << std::endl;
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
	outfile << "\"addcomm\": " << "\"" << this->addcomm << "\""<< endl;
	indentation(outfile, indent);
	outfile << "\"grade\": " << this->grade <<  "," << endl;
	indent--;
	indentation(outfile, indent);
	outfile << "}";
}

void Report::readInfo(std::ifstream &infile)
{
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

		if(savingString.find("addcomm") != string::npos)
		{
			savingString = savingString.substr(savingString.find("addcomm") + 10);
			savingString = savingString.substr(1, savingString.find_last_of('\"') - 1);
			this->addcomm = savingString;
		}

		if(savingString.find("grade") != string::npos)
		{
			savingString = savingString.substr(savingString.find("grade") + 7);
			savingString = savingString.substr(0, savingString.find(','));
			this->grade = stoi(savingString);
		}
	}
}
