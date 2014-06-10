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
	virtual void setSource(weak_ptr<void>source){};
	virtual weak_ptr<void> getSource(){return weak_ptr<void>();};
};

class EventSource
{

};
class ThreadEvent{
public:
	ThreadEvent(){};
	ThreadEvent(const weak_ptr<void>source)
	{
		std::tr1::shared_ptr<Thread> t =std::tr1::static_pointer_cast<Thread> (source.lock());
				this->source=t;
	}

	const weak_ptr<void> getSource()  {
		return source;
	}

	void setSource(const weak_ptr<void>source) {
		std::tr1::shared_ptr<Thread> t =std::tr1::static_pointer_cast<Thread> (source.lock());
		this->source=t;
	}

private:
	weak_ptr<Thread> source;
};
#endif /* EVENT_H_ */
