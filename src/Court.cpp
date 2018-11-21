/*
 * Court.cpp
 *
 *  Created on: Oct 21, 2018
 *      Author: andrefmrocha
 */

#include "Court.h"

using namespace std;
static double courtPrice = 15;

Court::Court(int year):currentYear(Year(year))
{
	this->maxUsers = 4;
}

Court::Court() {}


void Court::occupied(int month, int day, double startingHour, int duration)
{
	if(!this->currentYear.getMonth(month).getDay(day).checkSchedule(startingHour, duration))
	{
		throw(CourtReserved(month, day, startingHour));
	}
}

CourtReserved::CourtReserved(int month, int day, double sH)
{
	this->month = month;
	this->day = day;
	this->startingHour = sH;
}

string CourtReserved::what()const{
	return "The court is not available on the day " + to_string(this->day) + "of the month " + to_string(this->month) + " at "
			+ to_string(this->startingHour);

}

void Court::reserveCourt(int m, int d, double sH, int dur)
{
	this->currentYear.getMonth(m).getDay(d).setSchedule(sH, dur);

}

void Court::setMaxUsers(int users)
{
	this->maxUsers = users;
}

bool Court::reserveClass(int m, int d, double sH, User &user, Teacher &teacher)
{
	int dur = 2;
	try{
		occupied(m, d, sH, dur);
	}
	catch (CourtReserved& court)
	{
		cout << court.what();
		return false;
	}
	try
	{
		CheckAvailable(user.getReservations(),sH, calculateEndHour(sH, dur),d,m);
	}
	catch(AlreadyReservedHours &e)
	{
		cout << "The user is not available at this time!" << endl;
		return false;
	}
	try
	{
		CheckAvailable(teacher.getLessons(),sH, calculateEndHour(sH, dur),d,m);
	}
	catch(AlreadyReservedHours &e)
	{
		cout << "This user's teacher is not available at this time!" << endl;
		return false;
	}
	reserveCourt(m, d, sH, dur);
	double price = courtPrice * dur;
	if(user.getisGold())
	{
		price*=0.85;
	}

	Reservation * lesson = new Lesson(m, d, sH, price, dur);
	Lesson* teacherLesson = new Lesson(m, d, sH, price, dur);
	user.setReservation(lesson);
	teacher.setLesson(teacherLesson);
	return true;
}

bool Court::reserveFree(int m, int d, double sH, int dur, User &user)
{
	if(dur > 4 )
	{
		cout << "You cannot reserve the court for more than 2 hours!" << endl;
		return false;
	}
	try{
		occupied(m, d, sH, dur);
	}
	catch (CourtReserved& court)
	{
		cout << court.what();
		return false;
	}
	try
	{
		CheckAvailable(user.getReservations(),sH, calculateEndHour(sH, dur),d,m);
	}
	catch(AlreadyReservedHours &e)
	{
		cout << "The user is not available at this time!" << endl;
		return false;
	}
	double price = courtPrice;
	price*= dur;
	if(user.getisGold())
	{
		price*=0.85;
	}
	reserveCourt(m, d, sH, dur);
	Reservation * reserv = new Free(m, d, sH, price, dur);
	user.setReservation(reserv);
	return true;
}

void Court::storeInfo(ofstream &outfile, int indentation)
{
    indent(outfile, indentation);
	outfile << "{ " << endl;
	indent(outfile, indentation);
	outfile << "\"maxUsers\": "<< this->maxUsers <<"," << endl;
	indent(outfile, indentation);
	outfile<< "\"months\": [" << endl;
	indentation++;
	for(unsigned int i = 1; i < 13; i++)
	{
		indent(outfile,indentation);
		outfile << "{ " << endl;
		indentation++;
		indent(outfile, indentation);
		outfile << "\"month\": " << to_string(this->currentYear.getMonth(i).getMonth()) << "," << endl;
		indent(outfile,indentation);
		outfile << " \"days\": [" << endl;
		indentation++;
		for(unsigned j = 1; j < this->currentYear.getMonth(i).getNoDays(); j++)
		{
			indent(outfile,indentation);
			outfile << endl;
			indent(outfile,indentation);
			outfile << "{" << endl;
			indentation++;
			indent(outfile,indentation);
			outfile << "\"startingHour\": " << this->currentYear.getMonth(i).getDay(j).getSH() << "," << endl;
			indent(outfile,indentation);
			outfile << "\"schedule\": [";
			indentation++;
//			vector<bool>::iterator z = this->currentYear.getMonth(i).getDay(j).getSchedule().begin();

			for(unsigned int z = 0 ; z < this->currentYear.getMonth(i).getDay(j).getSchedule().size(); ++z)
			{
				if(z+1 == this->currentYear.getMonth(i).getDay(j).getSchedule().size())
				{
					outfile << this->currentYear.getMonth(i).getDay(j).getSchedule()[z];
				}
				else
				{
					outfile << this->currentYear.getMonth(i).getDay(j).getSchedule()[z] << ",";
				}
			}
			outfile << "]" << endl;
			indentation--;
			indentation--;
			indent(outfile,indentation);
			if(j + 1 == this->currentYear.getMonth(i).getNoDays())
			{
				outfile << "}" << endl;
			}
			else
			{
				outfile << "}," << endl;
			}
			indent(outfile,indentation);
		}
		outfile << "]" << endl;
		indentation--;
		indent(outfile,indentation);
		if(i+1 == 13)
		{
			outfile<< "}" << endl;
		}
		else
		{
			outfile<< "}," << endl;
		}
		indentation--;
		indent(outfile,indentation);
//		indentation--;
	}
	outfile << "]" << endl;
    indentation--;
    indent(outfile,indentation);
	outfile << "}";
}

void Court::indent(std::ofstream &outfile, int identation)
{
	for(int i = 0; i < identation; i++)
	{
		outfile << "\t";
	}
}

void Court::readInfo(std::ifstream &infile)
{
	string savingString;
	while (getline(infile, savingString))
	{
		if(savingString.find("maxUsers") != string::npos)
		{
			this->maxUsers = stoi(savingString.substr(savingString.find("maxUsers") + 11,1));
		}
		if (savingString.find('{') != string::npos)
			continue;
		if (savingString.find("months") != string::npos)
			break;
	}
	Year year;
	vector<Month> months;
	int monthCounter = 0;
	while (getline(infile, savingString))
	{
		months.clear();
		vector<Day> days;
		Month savingMonth;
		bool flag;
		while (getline(infile, savingString))
		{
			if (savingString.find("\"month\":") != string::npos)
			{
				monthCounter++;
				flag = true;
				savingString = savingString.substr(
						savingString.find("\"month\":") + 9, 2);
				if (savingString.find(',') != string::npos)
				{
					savingString = savingString.substr(0, 1);
				}
				savingMonth.setMonth(stoi(savingString));
				continue;
			}
			else if (savingString.find("\"days\"") != string::npos)
			{
				days.clear();
				while (getline(infile, savingString))
				{
					Day savingDay;
					vector<bool> savingSchedule;
					if (savingString.find("\"startingHour\"") != string::npos)
					{
						savingString = savingString.substr(savingString.find("\"startingHour\"") + 16);
						if (savingString.find(',') != string::npos)
						{
							savingString = savingString.substr(0, 1);
						}
						savingDay.setSH(stoi(savingString));
					}
					else if (savingString.find("\"schedule\"")!= string::npos)
					{
						savingString = savingString.substr(savingString.find("\"schedule\"") + 13);
						for (auto i : savingString)
						{
							if (i == ']')
							{
								break;
							}
							else if (i == ',')
							{
								continue;
							}
							else if (i == '0')
							{
								savingSchedule.push_back(false);
							}
							else
							{
								savingSchedule.push_back(true);
							}
						}
						savingDay.setSchedule(savingSchedule);
						days.push_back(savingDay);
					}
					else if (savingString.find('}') != string::npos && savingString.find("},") == string::npos)
					{
						savingDay.setSchedule(savingSchedule);
						days.push_back(savingDay);
						break;
					}
				}
			}
			if (flag) {
				flag = false;
				savingMonth.setDays(days);
				months.push_back(savingMonth);
			}
			if(monthCounter == 12)
			{
				break;
			}
		}
		break;
	}
	this->currentYear.setMonths(months);
}

int Court::getMaxUsers() const
{
	return maxUsers;
}
