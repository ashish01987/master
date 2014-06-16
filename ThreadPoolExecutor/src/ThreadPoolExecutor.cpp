/*
 * ThreadPoolExecutor.cpp
 *
 *  Created on: Jun 6, 2014
 *      Author: ashish
 */

#include "ThreadPoolExecutor.h"
#include "Events/Event.h"
ThreadPoolExecutor::~ThreadPoolExecutor() {
	// TODO Auto-generated destructor stub
	cout << "Pool Destroyed" << endl;
}

void ThreadPoolExecutor::shutdown() {
	_terminate = true;
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
	if (_terminate)
		terminate();

}

void ThreadPoolExecutor::handle_event(std::tr1::weak_ptr<Event> e) {
	if (!e.lock())
		return;
	std::tr1::shared_ptr<ThreadEvent> tevent = std::tr1::dynamic_pointer_cast<
			ThreadEvent>(e.lock());

	std::tr1::weak_ptr<Thread> th = std::tr1::dynamic_pointer_cast<Thread>(
			tevent->getSource().lock());

	if (th.lock()->isRunning()) {

		_busythreads[th.lock()->getThreadId()] = th;
	} else {

		_idlethreads.push(th);

		map<int, std::tr1::weak_ptr<Thread> >::iterator it = _busythreads.find(
				th.lock()->getThreadId());
		if (it != _busythreads.end())
			_busythreads.erase(it);
		else {
			cout << "thread not present" << endl;
		}

		//cout<<tidle.use_count()<<endl;
	}
//	cout<<"Thread id:-"<<th.lock()->getThreadId()<<" is "; ((th.lock()->isRunning())?cout<<" busy ":cout<<" ideal ")<<std::endl;
	//cout<<"idle:-"<<_idlethreads.size()<<endl;
}

void ThreadPoolExecutor::createidleThread(int i) {
	for (int c = 0; c < i; c++) {
		std::tr1::shared_ptr<Thread> t1(tf->getThread());

		t1->addListener(this);

		//_idlethreads.push(t1);
		t1->createThread();
		_liveThread.push_back(t1);

	}

}

std::tr1::weak_ptr<Thread> ThreadPoolExecutor::getFreeThread() {

	std::tr1::weak_ptr<Thread> t;
	Thread::__poolSync->blockAllThreads();
	if (!_idlethreads.empty()) {

		t = _idlethreads.front();

		_idlethreads.pop();

		//cout<<_idlethreads.size()<<endl;

	}
	Thread::__poolSync->releaseAllThreads();
	return t;

}

void ThreadPoolExecutor::terminate() {
	_terminate = true;
	while(true){
	Thread::__poolSync->blockAllThreads();
	if(_busythreads.empty())
	{
		break;
	}
	Thread::__poolSync->releaseAllThreads();
	}
	for (vector<std::tr1::shared_ptr<Thread> >::iterator it =
			_liveThread.begin(); it != _liveThread.end(); ++it) {
		Threadable * t=NULL;
		(*it)->removeAll();
		//(*it)->setTask(*t);
		(*it)->terminate();
		(*it)->wait();
	}
}
void ThreadPoolExecutor::wait() {
	for (vector<std::tr1::shared_ptr<Thread> >::iterator it =
			_liveThread.begin(); it != _liveThread.end(); ++it) {


	}
}
