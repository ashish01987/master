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
class CThread: public Thread{

	pthread_t t;


	void * param;
	Threadable* tk=NULL;
	void* (*task_wait)(void*);

protected :
	virtual void create_thread();

public:
	std::tr1::shared_ptr<ThreadEvent> ev;
	pthread_mutex_t SuspendMutex = PTHREAD_MUTEX_INITIALIZER;
	pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
	bool readyTorun, isTerminated=false,_isRunning;
	virtual ~CThread();
	CThread();
	virtual void setTask(Threadable &th);
		virtual void wait();
		virtual void run();
		virtual void terminate();
		Threadable* getTask();
		virtual void suspend();
		virtual bool isRunning(){return _isRunning;};
		virtual Thread& getThread(){return *this;};
	static	pthread_mutex_t SharedResoursc;
		//void* task(void*);
private:

};

#endif /* CTHREAD_H_ */
