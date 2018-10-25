/*
 * Reservation.h
 *
 *  Created on: 25/10/2018
 *      Author: joaomartins
 */

#ifndef SRC_RESERVATION_H_
#define SRC_RESERVATION_H_


#include "Person.h"

class Reservation {
protected:
	const double price;
	unsigned int duration;
private:
	User user;
	int month;
	int day;
	int startingHour;
public:
	Reservation(User user,int month,int day,int startingHour,double price,unsigned int duration);
	virtual double getPrice();
	User getUser();
	void setUser(User user);

};

class Lesson : public Reservation {
private:
	Teacher teacher;
public:
	Lesson(User u,int m,int d,int strHr,double price,unsigned int dr,Teacher t);
	double getPrice();
	Teacher getTeacher();
	void setTeacher(Teacher teacher);
};

class Free : public Reservation {
public:
	Free(User u, int m,int d,int strHr,double p,unsigned int dur);
	double getPrice();
};



#endif /* SRC_RESERVATION_H_ */
