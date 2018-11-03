/*
 * Invoice.h
 *
 *  Created on: Oct 21, 2018
 *      Author: andrefmrocha
 */

#ifndef SRC_INVOICE_H_
#define SRC_INVOICE_H_
#include <vector>
#include <string>
#include <iostream>
#include "Reservation.h"

class Invoice {
	std::vector<Reservation *> reservs;
	double totalPrice;
	std::string name;
	std::string assignedTeacher;
public:
	Invoice(std::string name, std::string teacherName, std::vector<Reservation *> reservs);
	double getPrice() const;
	std::vector<Reservation *> getReservs();
	friend std::ostream& operator<<(std::ostream &out, Invoice inv);
};


#endif /* SRC_INVOICE_H_ */
