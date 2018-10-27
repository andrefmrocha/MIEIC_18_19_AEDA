/*
 * Reservation.h
 *
 *  Created on: 25/10/2018
 *      Author: joaomartins
 */

#ifndef SRC_RESERVATION_H_
#define SRC_RESERVATION_H_




class Reservation {
protected:
	const double price;
	unsigned int duration;
private:
	int month;
	int day;
	double startingHour;
public:
	Reservation(int month,int day,int startingHour,double price,unsigned int duration);
	virtual double getPrice();
	double getStartingHour();
	int getDuration();
};

class Lesson : public Reservation {
public:
	Lesson(int m,int d,int strHr,double price,unsigned int dr);
	double getPrice();
};

class Free : public Reservation {
public:
	Free(int m,int d,int strHr,double p,unsigned int dur);
	double getPrice();
};



#endif /* SRC_RESERVATION_H_ */
