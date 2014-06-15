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
	class PoolResoureSync{
	public:
	virtual	void blockAllThreads()=0;
	virtual	void releaseAllThreads()=0;
	virtual ~PoolResoureSync(){};
	};
class Thread:public  virtual EventDispatcher,public virtual std::tr1::enable_shared_from_this<Thread>  {
public:
	virtual int getThreadId()=0;
	static PoolResoureSync* __poolSync;
	virtual ~Thread(){};
	virtual void setTask(Threadable& t)=0;
	virtual void wait()=0;
	virtual void run()=0;
	virtual void terminate()=0;
virtual void suspend()=0;
	virtual bool isRunning()=0;
	virtual void createThread()=0;

};

#endif /* THREAD_H_ */
