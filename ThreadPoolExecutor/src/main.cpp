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

struct A: public std::tr1::enable_shared_from_this<A> {
	virtual ~A() {
	}
	;
};
struct C: public virtual A {
	virtual void f2()=0;
	virtual ~C() {
	}
	;
};
struct B: public C {
	void f2() {
	}
	;
	virtual ~B() {
	}
	;
};
int main() {
	//cout << "!!!Hello World!!!" << endl; // prints !!!Hello World!!!


	std::tr1::shared_ptr<Queue<Threadable> > p(new Queue<Threadable>());
	ThreadPoolExecutor tex(p);

	Threader th1[2000];
	Threader1 th2[2000];
	for (int i = 0; i < 2000; i++) {
		p->Enqueue(th1[i]);
		p->Enqueue(th2[i]);
	}

	tex.schedule();
	Threader th3[20];
	Threader1 th4[20];
	for (int i = 0; i < 20; i++)

		p->Enqueue(th3[i]);
	for (int i = 0; i < 20; i++)
		p->Enqueue(th4[i]);

	tex.schedule();
	tex.shutdown();

	tex.wait();
	return 0;
}
