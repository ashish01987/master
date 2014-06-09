/*
 * ThreadPoolExecutor.cpp
 *
 *  Created on: Jun 6, 2014
 *      Author: ashish
 */

#include "ThreadPoolExecutor.h"



ThreadPoolExecutor::~ThreadPoolExecutor() {
	// TODO Auto-generated destructor stub
	th->wait();
}

void ThreadPoolExecutor::startThread()
{
	while(!_queue.lock()->isEmpty())
	{
 Threadable& t= _queue.lock()->DeQueue();
 th=&tf->getThread();
  		th->setTask(t);
  		th->run();
  		th->wait();
	}

}
