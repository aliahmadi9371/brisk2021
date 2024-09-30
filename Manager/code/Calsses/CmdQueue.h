//---------------------------------------------------------------------------
#ifndef CmdQueueH
#define CmdQueueH

#include <System.Classes.hpp>
#include <System.SyncObjs.hpp>
#include "defines.h"
//---------------------------------------------------------------------------
class CmdQueueClass
{
private:
	TMutex *mutex;
public:
	__fastcall CmdQueueClass(int size = CMD_QUEUE_SIZE);
	~CmdQueueClass();

	void enqueue(int cmd);
	void dequeue();
	int peek();

	int size();
	bool isEmpty();
	bool isFull();
	void initQ();

	int *arr;
	int capacity;	// maximum capacity of the queue
	int front;		// front points to front element in the queue (if any)
	int rear;		// rear points to last element in the queue
	int count;      // current size of the queue
};
#endif
