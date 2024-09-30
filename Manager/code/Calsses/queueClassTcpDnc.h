//---------------------------------------------------------------------------
#ifndef queueClassTcpDncH
#define queueClassTcpDncH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <System.SyncObjs.hpp>

#include "defines.h"
//---------------------------------------------------------------------------
class queueClassTcpDnc
{
private:
	TMutex *mutex;
public:
	__fastcall queueClassTcpDnc(int size = MAX_TCP_RESOLUTION);
	~queueClassTcpDnc();

	void dequeue();
	void enqueue(double data);
	double peek();
	int size();
	bool isEmpty();
	bool isFull();
	void initQ();

	double *arr;
	bool* checked;
	int capacity;	// maximum capacity of the queue
	int front;		// front points to front element in the queue (if any)
	int rear;		// rear points to last element in the queue
	int count;		// current size of the queue
};
//---------------------------------------------------------------------------
#endif
