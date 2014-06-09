/*
 * ThreadPoolExecutor.cpp
 *
 *  Created on: Jun 6, 2014
 *      Author: ashish
 */

#include "ThreadPoolExecutor.h"



ThreadPoolExecutor::~ThreadPoolExecutor() {
	// TODO Auto-generated destructor stub

}

void ThreadPoolExecutor::startThread()
{
	while(!_queue.lock()->isEmpty())
	{
 Threadable& t= _queue.lock()->DeQueue();
 th=&tf->getThread();
 std::tr1::shared_ptr<Thread> free=	getFreeThread();
  			if(free)
  			{
  		free->run();
  			}
  		//th->wait();
	}

}
void ThreadPoolExecutor::addToRunnQueue(std::tr1::weak_ptr<Thread> t)
{
	_busythreads.push(t.lock());

}

void ThreadPoolExecutor::addToWaitnQueue (std::tr1::weak_ptr<Thread> t)
{


	_idlethreads.push(t.lock());
}

void ThreadPoolExecutor::createidleThread()
{
	std::tr1::shared_ptr<Thread> t1(&tf->getThread());
	std::tr1::shared_ptr<Thread> t2(&tf->getThread());
	t1->set_notify_running_callback(*t1->isRunning());
	t1->set_notify_running_callback(*t2->isRunning());
	t1->set_notify_waiting_callback(*t1->isWaiting());
	t1->set_notify_waiting_callback(*t2->isWaiting());
	_idlethreads.push(t1);
	_idlethreads.push(t2);


}

std::tr1::shared_ptr<Thread> ThreadPoolExecutor::getFreeThread()
{
	if(_idlethreads.empty())
		return std::tr1::shared_ptr<Thread>();
	else
	{
		std::tr1::weak_ptr<Thread> t=_idlethreads.front();
		_idlethreads.pop();

		return t.lock();
	}
}
