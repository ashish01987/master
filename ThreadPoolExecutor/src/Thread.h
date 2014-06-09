/*
 * Thread.h
 *
 *  Created on: Jun 8, 2014
 *      Author: ashish
 */

#ifndef THREAD_H_
#define THREAD_H_
#include "Threadable.h"
#include "NotifyEvent.h"
#include <tr1/memory>

class Thread  {
public:
	virtual ~Thread(){};
	virtual void setTask(Threadable& t)=0;
	virtual void wait()=0;
	virtual void run()=0;
	virtual void terminate()=0;
	virtual void set_notify_running_callback(ThreadNotify&)=0;
	virtual void set_notify_waiting_callback(ThreadNotify&)=0;
	virtual ThreadNotify * isRunning()=0;
		virtual ThreadNotify * isWaiting()=0;
};

#endif /* THREAD_H_ */
