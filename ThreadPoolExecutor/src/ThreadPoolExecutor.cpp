/*
 * ThreadPoolExecutor.cpp
 *
 *  Created on: Jun 6, 2014
 *      Author: ashish
 */

#include "ThreadPoolExecutor.h"

ThreadPoolExecutor::~ThreadPoolExecutor() {
	// TODO Auto-generated destructor stub
cout<<"Pool Destroyed"<<endl;
}

void ThreadPoolExecutor::shutdown()
{
	_terminate=true;
	schedule();
}
void ThreadPoolExecutor::schedule() {

	while (!_queue.lock()->isEmpty()) {


		std::tr1::weak_ptr<Thread> free = getFreeThread();
		if (free.lock()) {
			Threadable& thl = _queue.lock()->DeQueue();
			free.lock()->setTask(thl);
			free.lock()->run();
		}
		//th->wait();
	}
if(_terminate)
	terminate();

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
	std::tr1::weak_ptr<Thread> th=std::tr1::dynamic_pointer_cast<Thread> (tevent->getSource().lock());

	if (th.lock()->isRunning())
	{
		std::tr1::weak_ptr<Thread> t(th);
		//th.lock()->run();
		_busythreads.push(t);
	}
	else {
	std::tr1::weak_ptr<Thread> tidle=	_busythreads.top();
	tidle.lock()->suspend();
	_idlethreads.push(tidle);
		_busythreads.pop();


		//cout<<tidle.use_count()<<endl;
	}
}

void ThreadPoolExecutor::createidleThread(int i) {
	for(int c=0;c<i;c++)
	{
	std::tr1::shared_ptr<Thread> t1(tf->getThread());


	t1->addListener(this);

	_idlethreads.push(t1);

	_liveThread.push_back(t1);

	}

}

std::tr1::weak_ptr<Thread> ThreadPoolExecutor::getFreeThread() {
	if (_idlethreads.empty())
		return std::tr1::shared_ptr<Thread>();
	else {
		std::tr1::weak_ptr<Thread> t = _idlethreads.front();

		_idlethreads.pop();
	//	cout<<t.use_count()<<endl;
		return t;
	}
}

void ThreadPoolExecutor::terminate()
{
	_terminate=true;
	for (vector<std::tr1::shared_ptr<Thread> >::iterator it =
						_liveThread.begin(); it != _liveThread.end(); ++it) {
					(*it)->terminate();

				}
}
void ThreadPoolExecutor::wait()
{
	for (vector<std::tr1::shared_ptr<Thread> >::iterator it =
					_liveThread.begin(); it != _liveThread.end(); ++it) {
				(*it)->wait();

			}
}
