/*
 * CThreadFactory.cpp
 *
 *  Created on: Jun 8, 2014
 *      Author: ashish
 */

#include "CThreadFactory.h"

CThreadFactory::CThreadFactory() {
	// TODO Auto-generated constructor stub

}

CThreadFactory::~CThreadFactory() {
	// TODO Auto-generated destructor stub
}

Thread & CThreadFactory::getThread()
{
 CThread *ct=new CThread();
  return *ct;
}
