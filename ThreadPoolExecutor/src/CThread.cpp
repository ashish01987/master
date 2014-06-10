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
pthread_mutex_t SuspendMutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
bool readyTorun, isTerminated;
void * task(void* context);
CThread::~CThread() {
	// TODO Auto-generated destructor stub

}

CThread::CThread() {
	// TODO Auto-generated constructor stub
	create_thread();

}

void CThread::terminate() {
	isTerminated = true;
}
void CThread::create_thread() {
	//pthread_create(&t, NULL,(void*(*)(void*))&CThread::task, NULL);
	//pthread_mutex_init(&SuspendMutex, NULL);
	//pthread_cond_init(&cond, NULL);
	readyTorun = false;
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

void CThread::notify_running()
{
	//Thread * t= (Thread*)this;

}

void CThread::notify_wating()
{
	pthread_cond_signal(&cond);

}

void * task(void* context) {
//	while(!isTerminated)
	//{
	while (true) {
		pthread_mutex_lock(&SuspendMutex);

		while (!readyTorun)
			pthread_cond_wait(&cond, &SuspendMutex);
		std::tr1::weak_ptr<Thread> sr;
		sr.lock().reset(((CThread*) context));
		((CThread*) context)->_dispatcher->notifyALL(std::tr1::shared_ptr<Event>(new ThreadEvent(sr)));
		((CThread*) context)->getTask()->threadRunner();

		readyTorun = false;
		((CThread*) context)->_dispatcher->notifyALL(std::tr1::shared_ptr<Event>(new ThreadEvent(sr)));

		pthread_mutex_unlock(&SuspendMutex);

	}	//}

}

