//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
#pragma package(smart_init)

#include "queueClassTcpDnc.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------

__fastcall queueClassTcpDnc::queueClassTcpDnc(int size)
{
	arr = new double[size];
	checked = new bool[size];
	for(int i=0; i<size; i++)
		checked[i] = false;
	capacity = size;
	front = 0;
	rear = -1;
	count = 0;
	mutex = new TMutex(false);
}
//---------------------------------------------------------------------------

queueClassTcpDnc::~queueClassTcpDnc()
{
	delete arr;
}
//---------------------------------------------------------------------------

void queueClassTcpDnc::dequeue()
{
	if (!isEmpty())
	{
		mutex->Acquire();
		checked[front] = false;
		front = (front + 1) % capacity;
		count--;
		mutex->Release();
	}
}
//---------------------------------------------------------------------------

void queueClassTcpDnc::enqueue(double item)
{
	if (!isFull())
	{
		mutex->Acquire();
		rear = (rear + 1) % capacity;
		arr[rear] = item;
		checked[rear] = true;
		count++;
		mutex->Release();
	}
	else
	{
		dequeue();
		mutex->Acquire();
		rear = (rear + 1) % capacity;
		arr[rear] = item;
		checked[rear] = true;
		count++;
		mutex->Release();
	}
}
//---------------------------------------------------------------------------

double queueClassTcpDnc::peek()
{
	if (!isEmpty() )
		return arr[front];
	else
		return -1; // ?????????????????
}
//---------------------------------------------------------------------------

int queueClassTcpDnc::size()
{
	return count;
}
//---------------------------------------------------------------------------

bool queueClassTcpDnc::isEmpty()
{
	return (size() == 0);
}
//---------------------------------------------------------------------------

bool queueClassTcpDnc::isFull()
{
	return (size() == capacity);
}
//---------------------------------------------------------------------------

void queueClassTcpDnc::initQ()
{
    front = 0;
	rear = -1;
	count = 0;
	for(int i=0; i<capacity; i++)
		checked[i] = false;
}
//---------------------------------------------------------------------------
