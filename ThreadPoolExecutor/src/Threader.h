/*
 * Threader.h
 *
 *  Created on: Jun 6, 2014
 *      Author: ashish
 */

#ifndef THREADER_H_
#define THREADER_H_

#include "Threadable.h"



class Threader: public Threadable {
public:
	Threader();
	virtual ~Threader();
	virtual void threadRunner();
};

class Threader1: public Threadable {
public:
	Threader1();
	virtual ~Threader1();
	virtual void threadRunner();
};
 /* namespace datastructs */
#endif /* THREADER_H_ */
