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

void ThreadPoolExecutor::startThread() {
	while (!_queue.lock()->isEmpty()) {


		std::tr1::shared_ptr<Thread> free = getFreeThread();
		if (free) {
			Threadable& thl = _queue.lock()->DeQueue();
			free->setTask(thl);
			free->run();
		}
		//th->wait();
	}
	for (vector<std::tr1::shared_ptr<Thread> >::iterator it =
			_liveThread.begin(); it != _liveThread.end(); ++it) {
		(*it)->wait();

	}
}
void ThreadPoolExecutor::addToRunnQueue(std::tr1::weak_ptr<Thread> t) {
	_busythreads.push(t.lock());

}

void ThreadPoolExecutor::addToWaitnQueue(std::tr1::weak_ptr<Thread> t) {

	_idlethreads.push(t.lock());
}
void ThreadPoolExecutor::handle_event(std::tr1::weak_ptr<Event> e) {
	if(!e.lock())
		return;
	std::tr1::shared_ptr<ThreadEvent> tevent = std::tr1::dynamic_pointer_cast<
			ThreadEvent>(e.lock());
	std::tr1::shared_ptr<Thread> th((Thread*) tevent->getSource());
	if (th->isRunning())
		_busythreads.push(th);
	else {
		_busythreads.pop();
		_idlethreads.push(th);
	}
}

void ThreadPoolExecutor::createidleThread() {
	std::tr1::shared_ptr<Thread> t1(&tf->getThread());
	std::tr1::shared_ptr<Thread> t2(&tf->getThread());

	t1->addListener(this);
	t2->addListener(this);
	_idlethreads.push(t1);
	_idlethreads.push(t2);
	_liveThread.push_back(t1);
	_liveThread.push_back(t2);

}

std::tr1::shared_ptr<Thread> ThreadPoolExecutor::getFreeThread() {
	if (_idlethreads.empty())
		return std::tr1::shared_ptr<Thread>();
	else {
		std::tr1::weak_ptr<Thread> t = _idlethreads.front();
		_idlethreads.pop();

		return t.lock();
	}
}
