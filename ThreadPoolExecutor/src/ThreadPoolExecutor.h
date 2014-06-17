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
#include <map>
using namespace std::tr1;

class ThreadPoolExecutor: public EventListener {
	std::tr1::weak_ptr<Queue<Threadable> > _queue;
	std::tr1::shared_ptr<ThreadDirector> d;
	std::queue<std::tr1::weak_ptr<Thread> > _idlethreads;
	std::vector<std::tr1::shared_ptr<Thread> > _liveThread;
	std::map<int, std::tr1::weak_ptr<Thread> > _busythreads;
	ThreadFactory *tf;

	void terminate();
	bool _terminate = false;
public:
	ThreadPoolExecutor(std::tr1::weak_ptr<Queue<Threadable> > queue) :
			_queue(queue) {
		d.reset(new ThreadDirector());
		tf = d->getFactory(thread_type::CTHREAD);
		createidleThread(5);

	}
	;
	virtual ~ThreadPoolExecutor();
	void schedule();
	void createidleThread(int i);
	std::tr1::weak_ptr<Thread> getFreeThread();

	virtual void handle_event(std::tr1::weak_ptr<Event> e);
	void wait();
	void shutdown();
};

#endif /* THREADPOOLEXECUTOR_H_ */
