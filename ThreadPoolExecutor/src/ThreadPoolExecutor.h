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
using namespace std::tr1;

 class ThreadPoolExecutor {
	std::tr1::weak_ptr<Queue<Threadable> > _queue;
	std::tr1::shared_ptr<ThreadDirector> d;
ThreadFactory *tf;
Thread *th;
public:
 	ThreadPoolExecutor(std::tr1::weak_ptr<Queue<Threadable> >  queue):_queue(queue)
{
 		d.reset(new ThreadDirector());
 	tf=	d->getFactory(thread_type::CTHREAD);

} ;
	virtual ~ThreadPoolExecutor();
	void startThread();
};

#endif /* THREADPOOLEXECUTOR_H_ */
