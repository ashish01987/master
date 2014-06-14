/*
 * Thread.h
 *
 *  Created on: Jun 8, 2014
 *      Author: ashish
 */

#ifndef THREAD_H_
#define THREAD_H_
#include "Threadable.h"
#include "Events/EventDispatcher.h"
#include <tr1/memory>

class Thread:public  virtual EventDispatcher  {
public:

	virtual ~Thread(){};
	virtual void setTask(Threadable& t)=0;
	virtual void wait()=0;
	virtual void run()=0;
	virtual void terminate()=0;
virtual void suspend()=0;
	virtual bool isRunning()=0;
};

#endif /* THREAD_H_ */
