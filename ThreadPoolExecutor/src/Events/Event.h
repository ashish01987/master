/*
 * Event.h
 *
 *  Created on: Jun 10, 2014
 *      Author: ashish
 */

#ifndef EVENT_H_
#define EVENT_H_
#include "EventDispatcher.h"
#include "../Thread.h"
#include <tr1/shared_ptr.h>
#include <tr1/memory>
using namespace std::tr1;

class Event {

public:
	Event();
	virtual ~Event();
	//virtual void setSource(weak_ptr<void>source){};
	virtual void* getSource(){return NULL;};
};

class EventSource
{

};
class ThreadEvent:public Event{
private:
	std::tr1::weak_ptr<Thread> source;
public:
	ThreadEvent(){};
	ThreadEvent(const void *source)
	{
		std::tr1::shared_ptr<Thread> t((Thread*) (source));
				this->source=t;
	}

	virtual void* getSource()  {
		return (void*)source.lock().get();
	}

	void setSource(const std::tr1:: weak_ptr<void>source) {
		std::tr1::shared_ptr<Thread> t =std::tr1::static_pointer_cast<Thread> (source.lock());
		this->source=t;
	}


};
#endif /* EVENT_H_ */
