/*
 * ThreadDirector.h
 *
 *  Created on: Jun 8, 2014
 *      Author: ashish
 */

#ifndef THREADDIRECTOR_H_
#define THREADDIRECTOR_H_
#include "CThreadFactory.h"

class ThreadFactory;
class Thread;
enum thread_type {CTHREAD};
class ThreadDirector {
	ThreadFactory*_tf;

public:
	ThreadDirector()
{


}
	virtual ~ThreadDirector();
ThreadFactory* getFactory(thread_type t)
{
	if(t==thread_type::CTHREAD)
	{
		_tf=new CThreadFactory();
	}
	return _tf;
}
};

#endif /* THREADDIRECTOR_H_ */
