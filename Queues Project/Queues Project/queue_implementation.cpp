#include<iostream>
#include<cstdlib>
#include<string>
#include "queuetype.h"

using namespace std;

queuetype::queuetype(void)
{
	front = 1;
	rear = 0;
	count = 0;
}

queuetype::~queuetype(void)
{
	front = 1;
	rear = 0;
	count = 0;
}

bool queuetype::isemptyqueue(void)
{
	return((count == 0) ? true : false);
}

bool queuetype::isfullqueue(void)
{
	return((count == QUEUE_SIZE) ? true : false);
}

void queuetype::addqueue(el_t& e)
{
	if (isfullqueue())
		queueError("Queue is full.\n");
	else
	{
		rear = (rear + 1) % QUEUE_SIZE;
		el[rear] = e;
		count++;
	}
}

void queuetype::deletequeue(el_t& e)
{
	if (isemptyqueue())
		queueError("Queue is empty. \n");
	else
	{
		e = el[front];
		front = (front + 1) % QUEUE_SIZE;
		count--;
	}
}

void queuetype::queueError(char* errormessage)
{
	cerr << errormessage << endl;
	exit(1);
}
