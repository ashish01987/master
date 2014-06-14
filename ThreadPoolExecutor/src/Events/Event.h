/*
 * Event.h
 *
 *  Created on: Jun 10, 2014
 *      Author: ashish
 */

#ifndef EVENT_H_
#define EVENT_H_
#include "EventDispatcher.h"

#include <tr1/shared_ptr.h>
#include <tr1/memory>
using namespace std::tr1;

class Event {

public:
	Event();
	virtual ~Event();
	//virtual void setSource(weak_ptr<void>source){};
	 virtual std::tr1::weak_ptr<EventDispatcher> getSource(){return std::tr1::shared_ptr<EventDispatcher>();};
};

class EventSource
{

};
class ThreadEvent:public Event{
private:
	std::tr1::weak_ptr<EventDispatcher> source;
public:
	ThreadEvent(){};
	ThreadEvent( std::tr1::weak_ptr<EventDispatcher> source)
	{

				this->source=source;
	}

	virtual std::tr1::weak_ptr<EventDispatcher>  getSource()  {
		return  source;
	}

	void setSource(const std::tr1:: weak_ptr<void>source) {
		std::tr1::shared_ptr<EventDispatcher> t =std::tr1::static_pointer_cast<EventDispatcher> (source.lock());
		this->source=t;
	}


};
#endif /* EVENT_H_ */
