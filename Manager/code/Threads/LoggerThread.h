//---------------------------------------------------------------------------

#ifndef LoggerThreadH
#define LoggerThreadH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <System.SyncObjs.hpp>
#include "defines.h"
#include <fstream>
//---------------------------------------------------------------------------
class LoggerThread : public TThread
{
private:
	TMutex *mutex;
protected:
	void __fastcall Execute();
public:
	__fastcall LoggerThread(bool CreateSuspended);

	bool started;
	bool thread_started;

	void enqueue(AnsiString log);
	void dequeue();
	AnsiString peek();

	int size();
	bool isEmpty();
	bool isFull();
	void initQ();

	AnsiString *arr;
	int capacity;	// maximum capacity of the queue
	int front;		// front points to front element in the queue (if any)
	int rear;		// rear points to last element in the queue
	int count;      // current size of the queue


	AnsiString MainLogFolder;
	AnsiString SubLogFolder;
	UnicodeString LogFileName;
	void AddLogToFile(AnsiString log);
	void CreateMainLogFolder();
	void CreateSubLogFolder();
	void CreateLogFileName();

	bool LogFile;
	UnicodeString name;


};
//---------------------------------------------------------------------------
#endif
