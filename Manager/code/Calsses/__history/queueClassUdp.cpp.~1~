//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
#pragma package(smart_init)

#include "queueClassUdp.h"
//---------------------------------------------------------------------------

__fastcall queueClassUdp::queueClassUdp(int size)
{
	arr = new double[size];
	capacity = size;
	front = 0;
	rear = -1;
	count = 0;
	srDev = BufferSize;
	mutex = new TMutex(false);
}
//---------------------------------------------------------------------------

queueClassUdp::~queueClassUdp()
{
	delete arr;
}
//---------------------------------------------------------------------------

void queueClassUdp::dequeue()
{
	if (!isEmpty())
	{
		mutex->Acquire();
		front = (front + 1) % capacity;
		count--;
		mutex->Release();
	}
}
//---------------------------------------------------------------------------

void queueClassUdp::enqueue(double item)
{
	if (!isFull())
	{
		mutex->Acquire();
		rear = (rear + 1) % capacity;
		arr[rear] = item;
		count++;
		mutex->Release();
	}
	else
	{
		dequeue();
		mutex->Acquire();
		rear = (rear + 1) % capacity;
		arr[rear] = item;
		count++;
		mutex->Release();
	}
}
//---------------------------------------------------------------------------

double queueClassUdp::peek()
{
	if (!isEmpty() )
		return arr[front];
	else
		return -1; // ?????????????????
}
//---------------------------------------------------------------------------

int queueClassUdp::size()
{
	return count;
}
//---------------------------------------------------------------------------

bool queueClassUdp::isEmpty()
{
	return (size() == 0);
}
//---------------------------------------------------------------------------

bool queueClassUdp::isFull()
{
	return (size() == capacity);
}
//---------------------------------------------------------------------------

void queueClassUdp::initQ()
{
    front = 0;
	rear = -1;
	count = 0;
}
//---------------------------------------------------------------------------

void queueClassUdp::ChangeSampleRate(int dev)
{
	srDev = BufferSize/dev;
}
//---------------------------------------------------------------------------
