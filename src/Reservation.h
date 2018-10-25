/*
 * Reservation.h
 *
 *  Created on: 25/10/2018
 *      Author: joaomartins
 */

#ifndef SRC_RESERVATION_H_
#define SRC_RESERVATION_H_


#include "User.h"

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


#endif /* SRC_RESERVATION_H_ */
