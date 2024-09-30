//---------------------------------------------------------------------------
#ifndef rec_queueClassH
#define rec_queueClassH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <System.SyncObjs.hpp>
#include <System.SysUtils.hpp>

#include "defines.h"
//---------------------------------------------------------------------------
class rec_queueClass
{
private:
	TMutex *mutex;

protected:
public:
	__fastcall rec_queueClass(int size = QueueSize);
	~rec_queueClass();

	void dequeue();
	void enqueue(DynamicArray<Byte> item);
	DynamicArray<Byte> peek();
	int size();
	bool isEmpty();
	bool isFull();

	DynamicArray<Byte> mainArray;

	DynamicArray<Byte> *arr;		// array to store queue elements
	int capacity;	// maximum capacity of the queue
	int front;		// front points to front element in the queue (if any)
	int rear;		// rear points to last element in the queue
	int count;		// current size of the queue
};
//---------------------------------------------------------------------------
#endif
