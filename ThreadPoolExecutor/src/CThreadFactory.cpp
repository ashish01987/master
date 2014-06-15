/*
 * CThreadFactory.cpp
 *
 *  Created on: Jun 8, 2014
 *      Author: ashish
 */

#include "CThreadFactory.h"
#include "CThread.h"
CThreadFactory::CThreadFactory() {
	// TODO Auto-generated constructor stub

}

CThreadFactory::~CThreadFactory() {
	// TODO Auto-generated destructor stub
}

std::tr1::shared_ptr<Thread> CThreadFactory::getThread()
{
	std::tr1::shared_ptr<CThread> ct;
	ct.reset(new CThread());

  return std::tr1::static_pointer_cast<Thread>(ct);
}
