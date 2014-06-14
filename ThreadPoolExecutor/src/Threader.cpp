/*
 * Threader.cpp
 *
 *  Created on: Jun 6, 2014
 *      Author: ashish
 */

#include "Threader.h"
#include <iostream>

 int  Threader::count=0;
 int  Threader1::count=0;
Threader::Threader() {
	// TODO Auto-generated constructor stub
	_id=count;
count++;
}

Threader::~Threader() {
	// TODO Auto-generated destructor stub
//	{std::cout<<" Threadable Destructor Called"<<std::endl;};
}

void Threader::threadRunner()
{
	std::cout<<"Hi task1 "<<_id<<std::endl;
}
 /* namespace datastructs */
Threader1::Threader1() {
	// TODO Auto-generated constructor stub
	_id=count;
count++;
}

Threader1::~Threader1() {
	// TODO Auto-generated destructor stub

}

void Threader1::threadRunner()
{
	std::cout<<"Hi task2 "<<_id<<std::endl;
}
