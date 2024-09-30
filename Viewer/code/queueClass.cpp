//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
#pragma package(smart_init)

#include "queueClass.h"
#include "mainUnit.h"
//---------------------------------------------------------------------------

__fastcall queueClass::queueClass()
{
	_front = 0;
	_rear = -1;
	_count = 0;
	mutex = new TMutex(false);
}
//---------------------------------------------------------------------------

queueClass::~queueClass()
{
	delete arr;
}
//---------------------------------------------------------------------------

void queueClass::createQueue()
{
	arr = new double[_size];
	_capacity = _size;
}
//---------------------------------------------------------------------------

void queueClass::dequeue()
{
	if (!isEmpty())
	{
		mutex->Acquire();
		_front = (_front + 1) % _capacity;
		_count--;
		mutex->Release();
	}
}
//---------------------------------------------------------------------------

void queueClass::enqueue(double item)
{
	if (!isFull())
	{
		mutex->Acquire();
		_rear = (_rear + 1) % _capacity;
		arr[_rear] = item;
		_count++;
		mutex->Release();
	}
	else
	{
		dequeue();
		mutex->Acquire();
		_rear = (_rear + 1) % _capacity;
		arr[_rear] = item;
		_count++;
		mutex->Release();
	}
}
//---------------------------------------------------------------------------

int queueClass::peek()
{
	if (!isEmpty())
		return arr[_front];
	else
		return -1; // ?????????????????
}
//---------------------------------------------------------------------------

int queueClass::size()
{
	return _count;
}
//---------------------------------------------------------------------------

bool queueClass::isEmpty()
{
	return (size() == 0);
}
//---------------------------------------------------------------------------

bool queueClass::isFull()
{
	return (size() == _capacity);
}
//---------------------------------------------------------------------------

void queueClass::GetNewData(unsigned char data0,
							unsigned char data1,
							unsigned char data2,
							unsigned char data3,
							double offset, double index, bool bits, bool UnSigned, int ScopIndex)
{
	unsigned char tmp1[4] ;
	int Sindedtmp = 0 ;
	unsigned int UnSindedtmp = 0 ;
	memset(tmp1,0x00,4);

	//LogData(17, ScopIndex, data0, data1, data2, data3);

	//32 bits to 24 bits
	if(bits){       //24bit
		if(UnSigned){
			tmp1[1] = data0;
			tmp1[2] = data1;
			tmp1[3] = data2;
			memcpy((void *)&UnSindedtmp , (void *)tmp1 , 4);
			UnSindedtmp = UnSindedtmp >> 8 ;
		}
		else{
			tmp1[1] = data0;
			tmp1[2] = data1;
			tmp1[3] = data2;
			memcpy((void *)&Sindedtmp , (void *)tmp1 , 4);
			Sindedtmp = Sindedtmp >> 8 ;
		}
	}
	else{       //32bit
		if(UnSigned){
			tmp1[0] = data0;
			tmp1[1] = data1;
			tmp1[2] = data2;
			tmp1[3] = data3;
			memcpy((void *)&UnSindedtmp , (void *)tmp1 , 4);
		}
		else{
			tmp1[0] = data0;
			tmp1[1] = data1;
			tmp1[2] = data2;
			tmp1[3] = data3;
			memcpy((void *)&Sindedtmp , (void *)tmp1 , 4);
		}
	}

	double t = 0;
	if(UnSigned)
		t = (double)UnSindedtmp;
	else
		t = (double)Sindedtmp;

	if(ScopIndex == 26){
		t = 8388607 - t;
	}
	t = index * t + offset;

	enqueue(t);
	return;
}
//---------------------------------------------------------------------------

void queueClass::InitQueue()
{
    _front = 0;
	_rear = -1;
	_count = 0;
}
//---------------------------------------------------------------------------
