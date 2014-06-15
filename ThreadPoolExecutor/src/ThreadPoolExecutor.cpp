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

void ThreadPoolExecutor::handle_event(std::tr1::weak_ptr<Event> e) {
	if(!e.lock())
		return;
	std::tr1::shared_ptr<ThreadEvent> tevent = std::tr1::dynamic_pointer_cast<
			ThreadEvent>(e.lock());
	std::tr1::weak_ptr<Thread> th=std::tr1::dynamic_pointer_cast<Thread> (tevent->getSource().lock());

	if (th.lock()->isRunning())
	{
		cout<<"busy Thread:-"<<th.lock()->getThreadId()<<endl;
		_busythreads[th.lock()->getThreadId()]=th;
	}
	else {
		cout<<"idle Thread:-"<<th.lock()->getThreadId()<<endl;


	_idlethreads.push(th);
	cout<<"Total ideal"<<_idlethreads.size();
map<int,std::tr1::weak_ptr<Thread> >::iterator it=	_busythreads.find(th.lock()->getThreadId());
if(it!=_busythreads.end())
		_busythreads.erase(it);


		//cout<<tidle.use_count()<<endl;
	}
	//cout<<"busy:-"<<_busythreads.size()<<endl;
	//cout<<"idle:-"<<_idlethreads.size()<<endl;
}

void ThreadPoolExecutor::createidleThread(int i) {
	for(int c=0;c<i;c++)
	{
	std::tr1::shared_ptr<Thread> t1(tf->getThread());


	t1->addListener(this);

	//_idlethreads.push(t1);
t1->createThread();
	_liveThread.push_back(t1);

	}

}

std::tr1::weak_ptr<Thread> ThreadPoolExecutor::getFreeThread() {
	Thread::__poolSync->blockAllThreads() ;
	std::tr1::weak_ptr<Thread> t;
	if (!_idlethreads.empty())
		{

		 t = _idlethreads.front();

		_idlethreads.pop();


		//cout<<_idlethreads.size()<<endl;

	}
	Thread::__poolSync->releaseAllThreads();
	return t;

}

void ThreadPoolExecutor::terminate()
{
	_terminate=true;
	while(!_busythreads.empty());
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
