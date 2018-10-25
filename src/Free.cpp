/*
 * Free.cpp
 *
 *  Created on: 25/10/2018
 *      Author: joaomartins
 */

#include "Free.h"


Free::Free(User u,int m,int d,int strHr,double p,unsigned int dur) : Reservation(u,m,d,strHr,p,dur)
{

}

Free::getPrice()
{
	return price;
}





