//---------------------------------------------------------------------------

#ifndef queueClassH
#define queueClassH
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <System.SyncObjs.hpp>
//---------------------------------------------------------------------------
class queueClass
{
private:
	TMutex *mutex;

protected:
public:
	__fastcall queueClass();
	~queueClass();

	void dequeue();
	void enqueue(double x);
	int peek();
	int size();
	bool isEmpty();
	bool isFull();
	void createQueue();
	void GetNewData(unsigned char data0,unsigned char data1,unsigned char data2,unsigned char data3,double offset,double index,bool bits,bool UnSigned,int ScopIndex);
	void InitQueue();

	double *arr;		// array to store queue elements
	int _capacity;	// maximum capacity of the queue
	int _front;		// front points to front element in the queue (if any)
	int _rear;		// rear points to last element in the queue
	int _count;		// current size of the queue
	int _size;      //size of Queue
};
//---------------------------------------------------------------------------
#endif
