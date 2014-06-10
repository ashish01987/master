/*
 * EventListener.h
 *
 *  Created on: Jun 10, 2014
 *      Author: ashish
 */

#ifndef EVENTLISTENER_H_
#define EVENTLISTENER_H_
#include <tr1/memory>
class Event;
class EventListener {
public:
	EventListener();
	virtual ~EventListener();
	virtual void handle_event(std::tr1::weak_ptr<Event> e){};

};

#endif /* EVENTLISTENER_H_ */
