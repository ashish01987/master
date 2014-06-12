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

void * task(void* context);
CThread::~CThread() {
	// TODO Auto-generated destructor stub

}

CThread::CThread() {
	// TODO Auto-generated constructor stub
	create_thread();

}
Threadable* CThread::getTask()
{
	return tk;
}
void CThread::terminate() {
	isTerminated = true;
}
void CThread::create_thread() {
	//pthread_create(&t, NULL,(void*(*)(void*))&CThread::task, NULL);
	//pthread_mutex_init(&SuspendMutex, NULL);
	//pthread_cond_init(&cond, NULL);
	cond = PTHREAD_COND_INITIALIZER;
	SuspendMutex = PTHREAD_MUTEX_INITIALIZER;
	pthread_create(&t, NULL, &task, (void*) this);

}

void CThread::wait() {
	pthread_join(t, NULL);
}

void CThread::run() {

	pthread_mutex_lock(&SuspendMutex);

	pthread_cond_signal(&cond);
	if (!readyTorun)
		readyTorun = true;
	pthread_mutex_unlock(&SuspendMutex);

}
void CThread::setTask(Threadable &tsk) {
	//THre
	//void (Threadable::*temp)();
	//temp=&Threadable::threadRunner;
	//task=&Threadable::threadRunner;
	tk = &tsk;

}


void * task(void* context) {
//	while(!isTerminated)
	//{
	CThread* thread=((CThread*) context);
	if(!thread)
		return NULL;
	while (true) {
		pthread_mutex_lock(&thread->SuspendMutex);



			if(!thread->readyTorun)
			{
				thread->_isRunning = false;

			pthread_cond_wait(&thread->cond, &thread->SuspendMutex);
			}
		thread->_isRunning = true;

		std::tr1::shared_ptr<ThreadEvent> ev (new ThreadEvent(thread));
		std::tr1::shared_ptr<Event> _Event=std::tr1::static_pointer_cast<Event> (ev);
		thread->notifyALL(_Event);
		thread->getTask()->threadRunner();

		thread->_isRunning = false;
		thread->cond = PTHREAD_COND_INITIALIZER;
		thread->notifyALL(_Event);

		pthread_mutex_unlock(&thread->SuspendMutex);

	}	//}

}

