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
	Invoice(){};
	Invoice(std::string name, std::string teacherName, std::vector<Reservation *> reservs);
	double getPrice() const;
	std::vector<Reservation *> getReservs();
	friend std::ostream& operator<<(std::ostream &out, Invoice inv);
    void storeInfo(std::ofstream &outfile, int indent);
    void indentation(std::ofstream &outfile, int indent);
    void readInfo(std::ifstream &infile);
};


#endif /* SRC_INVOICE_H_ */
