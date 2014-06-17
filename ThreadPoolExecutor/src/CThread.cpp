/*
 * CThread.cpp
 *
 *  Created on: Jun 8, 2014
 *      Author: ashish
 */

#include "CThread.h"
#include <iostream>
#include <tr1/memory>
using namespace std::tr1;
pthread_mutex_t CThread::SharedResoursc = PTHREAD_MUTEX_INITIALIZER;

PoolResoureSync* Thread::__poolSync=NULL;

int CThread::count=0;
void * task(void* context);
CThread::~CThread() {
	// TODO Auto-generated destructor stub

}

CThread::CThread() {
	// TODO Auto-generated constructor stub
	//create_thread();
	id=count++;
	cond = PTHREAD_COND_INITIALIZER;
		SuspendMutex = PTHREAD_MUTEX_INITIALIZER;
	if(!__poolSync)
	__poolSync=new CpoolSync();

}
void CThread::createThread() {


	 _Event.reset(new ThreadEvent(shared_from_this()));
	 pthread_attr_init(&attr);
	     pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
	     try{
	pthread_create(&t, &attr, &task, (LPVOID) this);
	     }
	     catch(...)
	     {
	    	 cout<<"Exception"<<endl;
	     }

}
Threadable* CThread::getTask() {
	return tk;
}
void CThread::terminate() {
	pthread_mutex_lock(&SuspendMutex);
	isTerminated = true;
	pthread_mutex_unlock(&SuspendMutex);
	run();
}

void CThread::wait() {
	pthread_join(t, NULL);
}
void CThread::suspend() {
	readyTorun = false;
	//cond = PTHREAD_COND_INITIALIZER;
}
void CThread::run() {

	pthread_mutex_lock(&SuspendMutex);


	if (!readyTorun)
	{
		pthread_cond_signal(&cond);
		readyTorun = true;
	}
	pthread_mutex_unlock(&SuspendMutex);

}
void CThread::setTask(Threadable &tsk) {
	//THre
	//void (Threadable::*temp)();
	//temp=&Threadable::threadRunner;
	//task=&Threadable::threadRunner;
	tk = &tsk;

}
 void CThread::cblockALLThreads()
{
	pthread_mutex_lock(&CThread::SharedResoursc);
}
void CThread::creleaseALLThreads()
{
	pthread_mutex_unlock(&CThread::SharedResoursc);
}
void * task(void* context) {

	//	while(!isTerminated)
	//{
	CThread* thread = ((CThread*) context);
	if (!thread)
		return NULL;

	thread->_isRunning = true;

	pthread_mutex_lock(&CThread::SharedResoursc);
	thread->notifyALL(thread->_Event);

	pthread_mutex_unlock(&CThread::SharedResoursc);
	try {
		while (true) {
			pthread_mutex_lock(&thread->SuspendMutex);

			while (!thread->readyTorun) {
				thread->_isRunning = false;
				pthread_mutex_lock(&CThread::SharedResoursc);
				thread->notifyALL(thread->_Event);
				pthread_mutex_unlock(&CThread::SharedResoursc);
				pthread_cond_wait(&thread->cond, &thread->SuspendMutex);

			}
			if (thread->isTerminated)
			{
				pthread_mutex_unlock(&thread->SuspendMutex);
										break;
			}
			thread->_isRunning = true;

			pthread_mutex_lock(&CThread::SharedResoursc);
			thread->notifyALL(thread->_Event);
			pthread_mutex_unlock(&CThread::SharedResoursc);
			cout<<"Thread id:-"<<thread->getThreadId()<<" Executes:- "<<endl;
			Threadable* th=thread->getTask();
			if(th)
			th->threadRunner();
//			thread->_isRunning = false;
//			//thread->cond = PTHREAD_COND_INITIALIZER;
//			pthread_mutex_lock(&CThread::SharedResoursc);
//			thread->notifyALL(thread->_Event);
//			pthread_mutex_unlock(&CThread::SharedResoursc);


			thread->suspend();
			pthread_mutex_unlock(&thread->SuspendMutex);

		}	//}
	} catch (...) {
		cout << "Thread exception" << endl;
	}
}

