/*
 * ThreadFactory.h
 *
 *  Created on: Jun 8, 2014
 *      Author: ashish
 */

#ifndef THREADFACTORY_H_
#define THREADFACTORY_H_
#include <tr1/memory>
class Thread;
class ThreadFactory {
public:
	virtual ~ThreadFactory(){};
	virtual std::tr1::shared_ptr<Thread> getThread()=0;
};

#endif /* THREADFACTORY_H_ */
