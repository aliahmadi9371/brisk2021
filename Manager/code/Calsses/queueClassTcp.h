//---------------------------------------------------------------------------
#ifndef queueClassTcpH
#define queueClassTcpH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <System.SyncObjs.hpp>

#include "NonExtractedLine.h"
#include "defines.h"
//---------------------------------------------------------------------------
class queueClassTcp
{
private:
	TMutex *mutex;
public:
	__fastcall queueClassTcp(int size = MAX_TCP_RESOLUTION * IMAGE_INDEX_COUNT);
	~queueClassTcp();

	void dequeue();
	void enqueue(TByteDynArray myData,int myResolution);
	NonExtractedLine peek();

	int size();
	bool isEmpty();
	bool isFull();
	void initQ();

	NonExtractedLine *arr;
	NonExtractedLine mainItem;		// array to store queue elements
	int capacity;	// maximum capacity of the queue
	int front;		// front points to front element in the queue (if any)
	int rear;		// rear points to last element in the queue
	int count;		// current size of the queue
};
#endif