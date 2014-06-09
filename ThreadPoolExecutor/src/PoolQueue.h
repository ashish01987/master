/*
 * PoolQueue.h
 *
 *  Created on: Jun 7, 2014
 *      Author: ashish
 */

#ifndef POOLQUEUE_H_
#define POOLQUEUE_H_
#include ""
template<class T>
class Queue;

/*template <typename T>
class PoolQueueIns:PoolQueue
{

	 void setQueue(Queue<T>& _q){_queue=&_q;};
		Queue<T>& getQueue(){return *_queue;};
private:
	Queue<T>* _queue;
};
class PoolQueue {
public:
	template <typename T> void setQueue(Queue<T>& _q)
	{
		dynamic_cast<PoolQueueIns<T>&>(*this).setQueue(_q);
	}
	template <typename U> Queue<U>& getQueue()
			{
		return dynamic_cast<const PoolQueueIns<U>&>(*this).getQueue();
			};
	virtual ~PoolQueue();
};*/
class PoolQueue
{
public:

};



#endif /* POOLQUEUE_H_ */
