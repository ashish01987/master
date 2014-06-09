/*
 * Threadable.h
 *
 *  Created on: Jun 6, 2014
 *      Author: ashish
 */

#ifndef THREADABLE_H_
#define THREADABLE_H_

#include <iostream>

class Threadable {
public:
	virtual void threadRunner()=0;

	virtual ~Threadable(){std::cout<<" Threadable Destructor Called"<<std::endl;};
};


#endif /* THREADABLE_H_ */
