//---------------------------------------------------------------------------

#pragma hdrstop

#include "rec_queueClass.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

__fastcall rec_queueClass::rec_queueClass(int size)
{
	arr = new DynamicArray<Byte>[size];
	capacity = size;
	front = 0;
	rear = -1;
	count = 0;
	mainArray.Length = 0;
	mutex = new TMutex(false);
}
//---------------------------------------------------------------------------

rec_queueClass::~rec_queueClass()
{
	delete arr;
}
//---------------------------------------------------------------------------

void rec_queueClass::dequeue()
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

void rec_queueClass::enqueue(DynamicArray<Byte> item)
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

DynamicArray<Byte> rec_queueClass::peek()
{
	if (!isEmpty())
		return arr[front];
	else
		return mainArray; // ?????????????????
}
//---------------------------------------------------------------------------

int rec_queueClass::size()
{
	return count;
}
//---------------------------------------------------------------------------

bool rec_queueClass::isEmpty()
{
	return (size() == 0);
}
//---------------------------------------------------------------------------

bool rec_queueClass::isFull()
{
	return (size() == capacity);
}
//---------------------------------------------------------------------------


