//---------------------------------------------------------------------------

#pragma hdrstop

#include "CmdQueue.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
__fastcall CmdQueueClass::CmdQueueClass(int size)
{
	arr = new int[size];
	capacity = size;
	front = 0;
	rear = -1;
	count = 0;
	mutex = new TMutex(false);
}
//---------------------------------------------------------------------------

CmdQueueClass::~CmdQueueClass()
{
	delete arr;
}
//---------------------------------------------------------------------------

void CmdQueueClass::dequeue()
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

void CmdQueueClass::enqueue(int cmd)
{
	if (!isFull())
	{
		mutex->Acquire();
		rear = (rear + 1) % capacity;
		arr[rear] = cmd;
		count++;
		mutex->Release();
	}
	else
	{
		dequeue();
		mutex->Acquire();
		rear = (rear + 1) % capacity;
		arr[rear] = cmd;
		count++;
		mutex->Release();
	}
}
//---------------------------------------------------------------------------

int CmdQueueClass::peek()
{
	if (!isEmpty() )
		return arr[front];
	else
		return -1; // ?????????????????
}
//---------------------------------------------------------------------------

int CmdQueueClass::size()
{
	return count;
}
//---------------------------------------------------------------------------

bool CmdQueueClass::isEmpty()
{
	return (size() == 0);
}
//---------------------------------------------------------------------------

bool CmdQueueClass::isFull()
{
	return (size() == capacity);
}
//---------------------------------------------------------------------------

void CmdQueueClass::initQ()
{
    front = 0;
	rear = -1;
	count = 0;
}
//---------------------------------------------------------------------------
