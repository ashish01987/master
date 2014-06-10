/*
 * CThreadFactory.h
 *
 *  Created on: Jun 8, 2014
 *      Author: ashish
 */

#ifndef CTHREADFACTORY_H_
#define CTHREADFACTORY_H_

#include "ThreadFactory.h"
#include "CThread.h"
class Thread;
class CThreadFactory: public ThreadFactory {

public:
	CThreadFactory();
	virtual ~CThreadFactory();
	virtual Thread& getThread();
};

#endif /* CTHREADFACTORY_H_ */