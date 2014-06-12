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
class mycomparison
{

public:

  bool operator() ( std::tr1::shared_ptr<Thread> lhs,  std::tr1::shared_ptr<Thread> rhs) const
  {
	  if(lhs->isRunning() && rhs->isRunning())
		  return false;
	  else if(!lhs->isRunning())
		  return true;
	  else return false;

  }
};
 class ThreadPoolExecutor:public EventListener {
	std::tr1::weak_ptr<Queue<Threadable> > _queue;
	std::tr1::shared_ptr<ThreadDirector> d;
	std::queue<std::tr1::shared_ptr<Thread> > _idlethreads;
	std::vector<std::tr1::shared_ptr<Thread> >_liveThread;
	priority_queue <std::tr1::shared_ptr<Thread>,vector<std::tr1::shared_ptr<Thread> >,mycomparison > _busythreads;
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
	virtual void handle_event(std::tr1::weak_ptr<Event> e);
};

#endif /* THREADPOOLEXECUTOR_H_ */
