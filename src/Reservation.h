/*
 * Reservation.h
 *
 *  Created on: 25/10/2018
 *      Author: joaomartins
 */

#ifndef SRC_RESERVATION_H_
#define SRC_RESERVATION_H_

#include <fstream>


class Reservation {
protected:
	double price;
	unsigned int duration;
private:
	int month;
	int day;
	double startingHour;
public:
	Reservation(){};
	Reservation(int month,int day,int startingHour,double price,unsigned int duration);
	virtual double getPrice();
	double getStartingHour();
	int getDuration();
	int getMonth();
	int getDay();
	bool operator ==(Reservation &r) const;
	virtual void storeInfo(std::ofstream &outfile, int indent);
	void indent(std::ofstream &outfile, int indent);
	void readInfo(std::ifstream &infile);
};

class Lesson : public Reservation {
public:
	Lesson(){};
	Lesson(int m,int d,int strHr,double price,unsigned int dr);
	double getPrice();
	void storeInfo(std::ofstream &outfile,int indent);
};

class Free : public Reservation {
public:
	Free(){};
	Free(int m,int d,int strHr,double p,unsigned int dur);
	double getPrice();
	void storeInfo(std::ofstream &outfile,int indent);
};



#endif /* SRC_RESERVATION_H_ */
