//---------------------------------------------------------------------------

#ifndef queueClassUdpH
#define queueClassUdpH
//---------------------------------------------------------------------------

#include <System.Classes.hpp>
#include <System.SyncObjs.hpp>

#include "defines.h"
//---------------------------------------------------------------------------
class queueClassUdp
{
private:
	TMutex *mutex;

protected:
public:
	__fastcall queueClassUdp(int size = QueueSize);
	~queueClassUdp();

	void dequeue();
	void enqueue(double x);
	double peek();
	int size();
	bool isEmpty();
	bool isFull();
	void initQ();

	double *arr;		// array to store queue elements
	int capacity;	// maximum capacity of the queue
	int front;		// front points to front element in the queue (if any)
	int rear;		// rear points to last element in the queue
	int count;		// current size of the queue
	int srDev;
	void ChangeSampleRate(int dev);
};
//---------------------------------------------------------------------------
#endif
