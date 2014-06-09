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
class CThread: public Thread {

	pthread_t t;


	void * param;
	Threadable* tk;
	void* (*task_wait)(void*);
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
		//void* task(void*);
private:

};

#endif /* CTHREAD_H_ */
