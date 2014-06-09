/*
 * ThreadPoolExecutor.h
 *
 *  Created on: Jun 6, 2014
 *      Author: ashish
 */

#ifndef THREADPOOLEXECUTOR_H_
#define THREADPOOLEXECUTOR_H_
#include "Queue.h"
#include <tr1/memory>
#include "Threadable.h"
#include "ThreadDirector.h"
#include "Thread.h"
#include "ThreadFactory.h"
#include <vector>
using namespace std::tr1;

 class ThreadPoolExecutor {
	std::tr1::weak_ptr<Queue<Threadable> > _queue;
	std::tr1::shared_ptr<ThreadDirector> d;
	std::queue<std::tr1::shared_ptr<Thread> > _idlethreads;
	queue<std::tr1::shared_ptr<Thread> > _busythreads;
ThreadFactory *tf;
Thread *th;

public:
 	ThreadPoolExecutor(std::tr1::weak_ptr<Queue<Threadable> >  queue):_queue(queue)
{
 		d.reset(new ThreadDirector());
 	tf=	d->getFactory(thread_type::CTHREAD);
 	createidleThread();

} ;
	virtual ~ThreadPoolExecutor();
	void startThread();
	void createidleThread();
	std::tr1::shared_ptr<Thread> getFreeThread();
	void addToWaitnQueue(std::tr1::weak_ptr<Thread>);
	void addToRunnQueue(std::tr1::weak_ptr<Thread>);
};

#endif /* THREADPOOLEXECUTOR_H_ */
