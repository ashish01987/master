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

using namespace std;
class CThread: public Thread{

	pthread_t t;


	void * param;
	Threadable* tk;
	void* (*task_wait)(void*);
	ThreadNotify * _running;
	ThreadNotify * _waiting;
protected :
	virtual void create_thread();

public:
	virtual ~CThread();
	CThread();
	virtual void setTask(Threadable &th);
		virtual void wait();
		virtual void run();
		virtual void terminate();
		Threadable* getTask(){return tk;};
		virtual void notify_running();
		virtual void notify_wating();
		virtual void set_notify_running_callback(ThreadNotify& ev){_running=&ev;};
			virtual void set_notify_waiting_callback(ThreadNotify& ev){_waiting=&ev;};
			ThreadNotify * isRunning(){return _running;};
				ThreadNotify * isWaiting(){return _waiting;};
		//void* task(void*);
private:

};

#endif /* CTHREAD_H_ */
