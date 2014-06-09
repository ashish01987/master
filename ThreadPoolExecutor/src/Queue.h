/*
 * Queue.h
 *
 *  Created on: Jun 6, 2014
 *      Author: ashish
 */

#ifndef QUEUE_H_
#define QUEUE_H_
#include <queue>

using namespace std;
template<typename T>
class Queue {

	queue<T*> _queue;
public:
	Queue(){};
	virtual ~Queue(){};
	void Enqueue( T& item)
	{
		_queue.push(&item);
	}

	T& DeQueue()
	{
		T& item=*_queue.front();
		_queue.pop();
		return item;
	}

	bool isEmpty()
	{
		return _queue.empty();
	}
};

 /* namespace datastructs */
#endif /* QUEUE_H_ */
