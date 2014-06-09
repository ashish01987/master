/*
 * ThreadFactory.h
 *
 *  Created on: Jun 8, 2014
 *      Author: ashish
 */

#ifndef THREADFACTORY_H_
#define THREADFACTORY_H_
class Thread;
class ThreadFactory {
public:
	virtual ~ThreadFactory(){};
	virtual Thread& getThread()=0;
};

#endif /* THREADFACTORY_H_ */
