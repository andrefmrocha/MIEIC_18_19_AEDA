/*
 * Free.h
 *
 *  Created on: 25/10/2018
 *      Author: joaomartins
 */

#ifndef SRC_FREE_H_
#define SRC_FREE_H_

#include "Reservation.h"

class Free : public Reservation {
public:
	Free(User u, int m,int d,int strHr,double p,unsigned int dur);
	double getPrice();
};

#endif /* SRC_FREE_H_ */
