/*
 * EventDispatcher.h
 *
 *  Created on: Jun 10, 2014
 *      Author: ashish
 */

#ifndef EVENTDISPATCHER_H_
#define EVENTDISPATCHER_H_
#include "EventListener.h"
#include<set>
#include <algorithm>
class EventDispatcher{
	std::vector<EventListener*> _listerns;
public:
	EventDispatcher();
	virtual ~EventDispatcher();
	void addListener(EventListener*e) {
		_listerns.push_back(e);
	}
	;
	void removeListener(EventListener*e) {
		//_listerns.erase(_listerns.find(e));
	}
	;

	void removeAll() {
		_listerns.clear();
	}
	;

	void notifyALL(std::tr1::weak_ptr<Event> e) {
		if (_listerns.empty())
			return;
		for (std::vector<EventListener*>::iterator it = _listerns.begin();
				it != _listerns.end(); ++it) {
			if (*it) {
				int i=_listerns.size();
				EventListener* evntL = *it;
				evntL->handle_event(e);
			}
		}

	}
};

#endif /* EVENTDISPATCHER_H_ */
