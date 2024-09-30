//---------------------------------------------------------------------------

#pragma hdrstop

#include "LitoFileCreatorUnit.h"
#include "mainUnit.h"
#include "globals.h"
#include "defines.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)


__fastcall LithoFileCreatorThread::LithoFileCreatorThread(bool CreateSuspended)
	: TThread(CreateSuspended)
{
	litho_file = false;
	progress = false;
	litho_file2 = false;




}
//---------------------------------------------------------------------------
void __fastcall LithoFileCreatorThread::Execute()
{
	//---- Place thread code here ----
	NameThreadForDebugging(System::String(L"LithoFileCreatorThread"));
	if(litho_file && !progress){
		CreateVfile(mainForm->myLithoFrm->LithoConfigFrm->scan_resolution);
	}
	else if(litho_file2  && !progress){
		CreateVfile(
					mainForm->myLithoFrm->LithoConfigFrm->scan_resolution,
					mainForm->myLithoFrm->LithoDesignFrm->myPaintForm->GrayBitmap
				   );

	}

}
//---------------------------------------------------------------------------

void LithoFileCreatorThread::CloseLithoThread()
{
	mainForm->LogToFile("LithoFileCreatorThread::CloseLithoThread");
	this->Terminate();
	delete this;
}
//---------------------------------------------------------------------------

void LithoFileCreatorThread::CreateVfile(int resolution)
{
	myTcpDataSendClass = new TcpDataSendClass;
	myTcpDataSendClass = NULL;

	mainForm->LogToFile("LithoFileCreatorThread: CreateVfile: Create Null Vfile");
//	if(!DirectoryExists(UploadPath + "/litho")){
//		AnsiString dir = UploadPath + "/litho";
//		CreateDirectoryA(dir.c_str(),NULL);
//	}
//	AnsiString name = UploadPath + "/litho/Vpoints.txt";
//	ofstream *file;
//	file = new ofstream(name.c_str(), ios::out);
//	AnsiString tmp;



	for(int i=0; i<resolution; i++){
//		mainForm->LogToFile("______________________________ "+ IntToStr(i) +" _____________________________");
//		Application->ProcessMessages();
		LineNumber = i;
		VLength = resolution;
		LithoVFile = new int[VLength];
		for(int j=0; j<resolution; j++){
//			Application->ProcessMessages();
			int num = 0;
			LithoVFile[j] = num;
//			tmp = IntToStr(num);
//			file->write(tmp.c_str(), tmp.Length());
//			if(j < resolution - 1){
//				tmp = " ";
//				file->write(tmp.c_str(), tmp.Length());
//			}
//			else{
//				tmp = "\n";
//				file->write(tmp.c_str(), tmp.Length());
//			}
		}

        mainForm->myTcpThread->TcpMode = 4;
		mainForm->myTcpThread->ConnectToServer();
		while(!(mainForm->myTcpThread->ClientConnected)){
			Application->ProcessMessages();
		}
//		mainForm->LogToFile("LithoFileCreatorThread : client connected");

		///////////////////////////////
		mainForm->myTcpThread->TcpSendData(myTcpDataSendClass->LithoVFilePacket(LithoVFile , VLength ,LineNumber));
		while(!(mainForm->myTcpThread->TcpAck))
			Application->ProcessMessages();
		///////////////////////////////
		mainForm->myTcpThread->TcpAck = false;
//		mainForm->LogToFile("LithoFileCreatorThread : send data V");

//

		delete LithoVFile;
		mainForm->myLithoFrm->LithoConfigFrm->Label1->Caption ="Preparation for lithography : " + FloatToStr( floor(((double)i / (double)resolution) * (double)1000) / (double)10 ) + " %";
	}
	mainForm->LogToFile("LithoFileCreatorThread : litho send");

//	mainForm->myTcpThread->DisConnectFromServer();
//	while(mainForm->myTcpThread->ClientConnected){
//		Application->ProcessMessages();
//	}
//	mainForm->LogToFile("LithoFileCreatorThread : client disconnected");

	delete myTcpDataSendClass;
//	file->close();
	progress = true;
	litho_file = false;
	progress = false;

	CloseLithoThread();
}
//---------------------------------------------------------------------------

void LithoFileCreatorThread::CreateVfile(int resolution, TBitmap* bitmap)
{
	myTcpDataSendClass = new TcpDataSendClass;
	myTcpDataSendClass = NULL;

	mainForm->LogToFile("LithoFileCreatorThread: CreateVfile: Create bitmap Vfile");
//	if(!DirectoryExists(UploadPath + "/litho")){
//		AnsiString dir = UploadPath + "/litho";
//		CreateDirectoryA(dir.c_str(),NULL);
//	}
//	AnsiString name = UploadPath + "/litho/Vpoints.txt";
//	DeleteFileW(name);
//	ofstream *file;
//	file = new ofstream(name.c_str(), ios::out);
//	AnsiString tmp;

//	mainForm->LogToFile("pixels = " + IntToStr(bitmap->Width) + " * " + IntToStr(bitmap->Height));



	for(int i=0; i<resolution; i++){
//		mainForm->LogToFile("______________________________ "+ IntToStr(i) +" _____________________________");
//		Application->ProcessMessages();
		LineNumber = i;
		VLength = resolution;
		LithoVFile = new int[VLength];
		ptr2 = (TRGBQuad*)bitmap->ScanLine[i];
		for(int j=0; j<resolution ; j++){
//			Application->ProcessMessages();
			int num = 255 - ptr2[j].rgbRed;
			num = floor( (( ((double)num/(double)255) * 100 * 83886.07)) + 0.5);
//			tmp = num;
			LithoVFile[j] = num;
//			file->write(tmp.c_str(), tmp.Length());

//			if(j != resolution - 1){
//				tmp = " ";
//				file->write(tmp.c_str(), tmp.Length());
//			}
//			else{
//				tmp = "\n";
//				file->write(tmp.c_str(), tmp.Length());
//
//			}
		}

		mainForm->myTcpThread->TcpMode = 4;
		mainForm->myTcpThread->ConnectToServer();
		while(!(mainForm->myTcpThread->ClientConnected)){
			Application->ProcessMessages();
		}
//		mainForm->LogToFile("LithoFileCreatorThread : client connected");

		///////////////////////////////
		mainForm->myTcpThread->TcpSendData(myTcpDataSendClass->LithoVFilePacket(LithoVFile , VLength ,LineNumber));

		while(!(mainForm->myTcpThread->TcpAck))
			Application->ProcessMessages();
		///////////////////////////////
//		mainForm->LogToFile("LithoFileCreatorThread : send data V");
		mainForm->myTcpThread->TcpAck = false;

		delete LithoVFile;

		mainForm->myLithoFrm->LithoConfigFrm->Label1->Caption = "Preparation for lithography : " + FloatToStr( floor(((double)i / (double)resolution) * (double)1000) / (double)10 ) + " %";
	}
	mainForm->LogToFile("LithoFileCreatorThread : litho send");

//	mainForm->myTcpThread->DisConnectFromServer();
//	while(mainForm->myTcpThread->ClientConnected){
//		Application->ProcessMessages();
//	}
//	mainForm->LogToFile("LithoFileCreatorThread : client disconnected");

	delete myTcpDataSendClass;
//	file->close();
	progress = true;
	litho_file2 = false;
	progress = false;
	CloseLithoThread();

}

