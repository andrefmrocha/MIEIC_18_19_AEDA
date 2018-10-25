/*
 * Lesson.h
 *
 *  Created on: 25/10/2018
 *      Author: joaomartins
 */

#ifndef SRC_LESSON_H_
#define SRC_LESSON_H_

#include "Reservation.h"
#include "Person.h"

class Lesson : public Reservation {
private:
	Teacher teacher;
public:
	Lesson(User u,int m,int d,int strHr,double price,unsigned int dr,Teacher t);
	double getPrice();
	Teacher getTeacher();
	void setTeacher(Teacher teacher);
};




#endif /* SRC_LESSON_H_ */
