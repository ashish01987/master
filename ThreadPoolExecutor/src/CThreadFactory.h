/*
 * CThreadFactory.h
 *
 *  Created on: Jun 8, 2014
 *      Author: ashish
 */

#ifndef CTHREADFACTORY_H_
#define CTHREADFACTORY_H_

#include "ThreadFactory.h"

class Thread;
class CThreadFactory: public ThreadFactory {

public:
	CThreadFactory();
	virtual ~CThreadFactory();
	virtual std::tr1::shared_ptr<Thread> getThread();
};

#endif /* CTHREADFACTORY_H_ */
