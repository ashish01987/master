//============================================================================
// Name        : ThreadPoolExecutor.cpp
// Author      : Ashish shah
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
using namespace std;
#include "Threader.h"
#include "Queue.h"
#include "Threadable.h"
#include "ThreadPoolExecutor.h"
#include "ThreadDirector.h"
#include <tr1/memory>
using namespace std::tr1;

int main() {
	//cout << "!!!Hello World!!!" << endl; // prints !!!Hello World!!!
	Queue<Threadable> queue;
	std::tr1::shared_ptr<Queue<Threadable> > p(&queue);
	ThreadPoolExecutor tex(p);


	Threader th1;
	Threader1 th2;
	queue.Enqueue(th1);
	queue.Enqueue(th2);

	tex.startThread();
	return 0;
}
