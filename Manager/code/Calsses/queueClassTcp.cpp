//---------------------------------------------------------------------------
#pragma hdrstop

#include "queueClassTcp.h"
#include "mainUnit.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

__fastcall queueClassTcp::queueClassTcp(int size)
{
	arr = new NonExtractedLine[size];
	capacity = size;
	front = 0;
	rear = -1;
	count = 0;
	mutex = new TMutex(false);
}
//---------------------------------------------------------------------------

queueClassTcp::~queueClassTcp()
{
	delete arr;
}
//---------------------------------------------------------------------------

void queueClassTcp::dequeue()
{
	if (!isEmpty())
	{
		mutex->Acquire();
		arr[front].resetData();
		front = (front + 1) % capacity;
		count--;
		mutex->Release();
	}
}
//---------------------------------------------------------------------------

void queueClassTcp::enqueue(TByteDynArray myData,int myResolution)
{
	if (!isFull())
	{
		mutex->Acquire();
		rear = (rear + 1) % capacity;
		arr[rear].newData(myData,myResolution);
		count++;
		mutex->Release();
	}
	else
	{
		dequeue();
		mutex->Acquire();
		rear = (rear + 1) % capacity;
		arr[rear].newData(myData,myResolution);
		count++;
		mutex->Release();
	}
}
//---------------------------------------------------------------------------

NonExtractedLine queueClassTcp::peek()
{
	if (!isEmpty())
		return arr[front];
	else
		return mainItem; // ?????????????????
}
//---------------------------------------------------------------------------

int queueClassTcp::size()
{
	return count;
}
//---------------------------------------------------------------------------

bool queueClassTcp::isEmpty()
{
	return (size() == 0);
}
//---------------------------------------------------------------------------

bool queueClassTcp::isFull()
{
	return (size() == capacity);
}
//---------------------------------------------------------------------------

void queueClassTcp::initQ()
{
	for(int i=0; i<count; i++)
		arr[i].resetData();
	front = 0;
	rear = -1;
	count = 0;
}
//---------------------------------------------------------------------------
