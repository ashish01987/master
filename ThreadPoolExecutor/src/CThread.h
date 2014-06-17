/*
 * CThread.h
 *
 *  Created on: Jun 8, 2014
 *      Author: ashish
 */

#ifndef CTHREAD_H_
#define CTHREAD_H_
#include <pthread.h>
#include "Thread.h"
#include "Threadable.h"
#include "Events/Event.h"
using namespace std;
class CThread;
class CThread: public Thread {

	pthread_t t;

	void * param;
	Threadable* tk = NULL;
	void* (*task_wait)(void*);
	static int count;
	int id;
	pthread_attr_t attr;
protected:


public:
	 int getThreadId(){return id;};
	pthread_mutex_t SuspendMutex = PTHREAD_MUTEX_INITIALIZER;
	pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
	bool readyTorun, isTerminated = false, _isRunning;
	virtual ~CThread();
	CThread();
	virtual void setTask(Threadable &th);
	virtual void wait();
	virtual void run();
	virtual void terminate();
	Threadable* getTask();
	virtual void suspend();
	virtual bool isRunning() {
		return _isRunning;
	}
	;
	virtual Thread& getThread() {
		return *this;
	}
	;
	static pthread_mutex_t SharedResoursc;
	virtual void createThread();
	static void cblockALLThreads();
	static void creleaseALLThreads();
	//void* task(void*);
	std::tr1::shared_ptr<Event> _Event;
private:


};
class CpoolSync:public PoolResoureSync
{
public:
	void blockAllThreads()
	{
		pthread_mutex_lock(&CThread::SharedResoursc);
	}
	void releaseAllThreads()
	{
		pthread_mutex_unlock(&CThread::SharedResoursc);
	}
	virtual ~CpoolSync(){};
};

#endif /* CTHREAD_H_ */
