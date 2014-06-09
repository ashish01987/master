/*
 * Threader.cpp
 *
 *  Created on: Jun 6, 2014
 *      Author: ashish
 */

#include "Threader.h"
#include <iostream>


Threader::Threader() {
	// TODO Auto-generated constructor stub

}

Threader::~Threader() {
	// TODO Auto-generated destructor stub
	{std::cout<<" Threadable Destructor Called"<<std::endl;};
}

void Threader::threadRunner()
{
	std::cout<<"Hi"<<std::endl;
}
 /* namespace datastructs */
Threader1::Threader1() {
	// TODO Auto-generated constructor stub

}

Threader1::~Threader1() {
	// TODO Auto-generated destructor stub

}

void Threader1::threadRunner()
{
	std::cout<<"Hi thread2"<<std::endl;
}
