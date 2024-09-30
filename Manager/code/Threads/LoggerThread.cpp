//---------------------------------------------------------------------------

#include <System.hpp>
#pragma hdrstop

#include "LoggerThread.h"
#pragma package(smart_init)
#include "mainUnit.h"
//---------------------------------------------------------------------------

//   Important: Methods and properties of objects in VCL can only be
//   used in a method called using Synchronize, for example:
//
//      Synchronize(&UpdateCaption);
//
//   where UpdateCaption could look like:
//
//      void __fastcall LoggerThread::UpdateCaption()
//      {
//        Form1->Caption = "Updated in a thread";
//      }
//---------------------------------------------------------------------------

__fastcall LoggerThread::LoggerThread(bool CreateSuspended)
	: TThread(CreateSuspended)
{


	arr = new AnsiString[CMD_QUEUE_SIZE];
	capacity = CMD_QUEUE_SIZE;
	initQ();
	mutex = new TMutex(false);

	thread_started = false;
	started = false;

	MainLogFolder = "logs";
	LogFile = false;
}
//---------------------------------------------------------------------------
void __fastcall LoggerThread::Execute()
{

	//---- Place thread code here ----
	started = true;
	while(thread_started){
		Application->ProcessMessages();
		if(!isEmpty()){
			AddLogToFile(peek());
			dequeue();
		}
		Sleep(10);
	}
}
//---------------------------------------------------------------------------

void LoggerThread::initQ()
{

	front = 0;
	rear = -1;
	count = 0;
}
//---------------------------------------------------------------------------

void LoggerThread::dequeue()
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

void LoggerThread::enqueue(AnsiString log)
{

	if (!isFull())
	{
		mutex->Acquire();
		rear = (rear + 1) % capacity;
		arr[rear] = log;
		count++;
		mutex->Release();
	}
	else
	{
		dequeue();
		mutex->Acquire();
		rear = (rear + 1) % capacity;
		arr[rear] = log;
		count++;
		mutex->Release();
	}
}
//---------------------------------------------------------------------------

AnsiString LoggerThread::peek()
{
	if (!isEmpty() ){
		return arr[front];
	}
	else
		return ""; // ?????????????????
}
//---------------------------------------------------------------------------

int LoggerThread::size()
{
	return count;
}
//---------------------------------------------------------------------------

bool LoggerThread::isEmpty()
{
	return (size() == 0);
}
//---------------------------------------------------------------------------

bool LoggerThread::isFull()
{
	return (size() == capacity);
}
//---------------------------------------------------------------------------

void LoggerThread::AddLogToFile(AnsiString log)
{

	CreateMainLogFolder();

	CreateLogFileName();

	std::ofstream ofs;
	ofs.open (name.c_str(), std::ofstream::out | std::ofstream::app);

	AnsiString tmp = TDateTime::CurrentTime().FormatString("hh-MM-sss.zzz") + " - " + log;
	ofs.write(tmp.c_str(),tmp.Length());
	ofs.write("\r\n",1);
	ofs.close();

#ifdef __DEBUG
//	OutputDebugStringA(log.c_str());
#endif
}
//---------------------------------------------------------------------------

void LoggerThread::CreateMainLogFolder()
{

	if(!DirectoryExists(MainLogFolder)){
		CreateDirectoryA(MainLogFolder.c_str(),NULL);
	}

}
//---------------------------------------------------------------------------

void LoggerThread::CreateSubLogFolder()
{

	switch(mainForm->AppMode){
		case 1:{
			SubLogFolder = MainLogFolder + "/" + "contact";
			if(!DirectoryExists(SubLogFolder)){
				CreateDirectoryA(SubLogFolder.c_str(),NULL);
			}
			break;
		}
		case 2:{
			SubLogFolder = MainLogFolder + "/" + "non-contact";
			if(!DirectoryExists(SubLogFolder)){
				CreateDirectoryA(SubLogFolder.c_str(),NULL);
			}
			break;
		}
		case 3:{
			SubLogFolder = MainLogFolder + "/" + "EFM";
			if(!DirectoryExists(SubLogFolder)){
				CreateDirectoryA(SubLogFolder.c_str(),NULL);
			}
			break;
		}
		case 4:{
			SubLogFolder = MainLogFolder + "/" + "MFM";
			if(!DirectoryExists(SubLogFolder)){
				CreateDirectoryA(SubLogFolder.c_str(),NULL);
			}
			break;
		}
		case 5:{
			SubLogFolder = MainLogFolder + "/" + "force-spectroscopy";
			if(!DirectoryExists(SubLogFolder)){
				CreateDirectoryA(SubLogFolder.c_str(),NULL);
			}
			break;
		}
		case 6:{
			SubLogFolder = MainLogFolder + "/" + "KPFM";
			if(!DirectoryExists(SubLogFolder)){
				CreateDirectoryA(SubLogFolder.c_str(),NULL);
			}
			break;
		}
		case 7:{
			SubLogFolder = MainLogFolder + "/" + "lithography";
			if(!DirectoryExists(SubLogFolder)){
				CreateDirectoryA(SubLogFolder.c_str(),NULL);
			}
			break;
		}
	}
}
//---------------------------------------------------------------------------

void LoggerThread::CreateLogFileName()
{

	LogFileName = MainLogFolder + "/" + TDateTime::CurrentDateTime().FormatString("yyyymmddhhnnss") + ".txt";
	if(!LogFile){
		if(!FileExists(LogFileName)){
			CreateFile2(LogFileName.c_str(),(GENERIC_READ | GENERIC_WRITE),(FILE_SHARE_READ | FILE_SHARE_WRITE),CREATE_ALWAYS,NULL);
			name = LogFileName;
			LogFile = true;
		}
	}
	else if(!FileExists(name)){
		CreateFile2(name.c_str(),(GENERIC_READ | GENERIC_WRITE),(FILE_SHARE_READ | FILE_SHARE_WRITE),CREATE_ALWAYS,NULL);
	}


}
//---------------------------------------------------------------------------

