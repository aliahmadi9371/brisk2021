//---------------------------------------------------------------------------
#include <vcl.h>
#include <System.hpp>
#pragma hdrstop

#include "ScanUnit.h"
#include "mainUnit.h"
#pragma package(smart_init)

//---------------------------------------------------------------------------

//   Important: Methods and properties of objects in VCL can only be
//   used in a method called using Synchronize, for example:
//
//      Synchronize(&UpdateCaption);
//
//   where UpdateCaption could look like:
//
//      void __fastcall ScanFileCreatorUploader::UpdateCaption()
//      {
//        Form1->Caption = "Updated in a thread";
//      }
//---------------------------------------------------------------------------
__fastcall ScanThread::ScanThread(bool CreateSuspended)
	: TThread(CreateSuspended)
{
}
//---------------------------------------------------------------------------
void __fastcall ScanThread::Execute()
{
	//---- Place thread code here ----

	CreateClassObjects();
	ConfigCalss();
	InitClass();
	GetScanInfoFromUi();
	myCoordinateClass->StartScan(Center,Range,Angle);
	myScanFileCreator->CreateXfile(myCoordinateClass->FinalRealTL[0],myCoordinateClass->StepHor[0],myResolution, myOverScan);
	myScanFileCreator->CreateYfile(myCoordinateClass->FinalRealTL[1],myCoordinateClass->StepHor[1],myResolution, myOverScan);
	GetFtpInfo();
	FtpUploaderSetting(RemoteIp,RemoteUsrName,RemotePasswd);
	checkTimer->Enabled = true;
	FtpLogin();

	while(ThreadStarted){
		Application->ProcessMessages();
	}
}
//---------------------------------------------------------------------------

void ScanThread::ConfigCalss()
{
	ipwFTP->OnConnectionStatus = FtpConnectionStatusEvent;
	ipwFTP->OnError = FtpErrorEvent;
	ipwFTP->OnStartTransfer = FtpStartTransferEvent;
	ipwFTP->OnTransfer = FtpTransferEvent;
	ipwFTP->OnEndTransfer = FtpEndTransferEvent;

	checkTimer->OnTimer = CheckTimerEvent;
}
//---------------------------------------------------------------------------

void __fastcall ScanThread::CheckTimerEvent(TObject *Sender)
{
	if(ipwFTP->Connected && Checker){
		if(count == 0)
			FtpUploader(RemotAddressX,LocalFileX);
		if(count == 1)
			FtpUploader(RemotAddressY,LocalFileY);



	}
}

void ScanThread::InitClass()
{
	Checker = false;
	count = 0;
}
//---------------------------------------------------------------------------

void ScanThread::CreateClassObjects()
{
	if(!ipwFTP)
		ipwFTP = new TipwFTP(NULL);

	if(!myCoordinateClass)
		myCoordinateClass = new CoordinateClass;

	if(!myScanFileCreator)
		myScanFileCreator = new ScanFileCreator;

	if(!checkTimer)
		checkTimer = new TTimer(NULL);
}
//---------------------------------------------------------------------------
void ScanThread::GetScanInfoFromUi(){	Resolution = mainForm->myControlFrm->AdvEditScanResolution->Text.ToDouble();	Range = mainForm->myControlFrm->AdvEditRange->Text.ToDouble();	Angle = mainForm->myControlFrm->AdvEditAngle->Text.ToDouble();	Center[0] = mainForm->myControlFrm->AdvEditCenterX->Text.ToDouble();	Center[1] = mainForm->myControlFrm->AdvEditCenterY->Text.ToDouble();	OverScan = mainForm->myControlFrm->AdvEditOverScan->Text.ToDouble();}//---------------------------------------------------------------------------void ScanThread::Calibration(bool calc){	if(calc){	}}//---------------------------------------------------------------------------

void ScanThread::FtpUploaderSetting(UnicodeString IP,UnicodeString UserName,UnicodeString PassWord)
{
	if(ipwFTP){
		ipwFTP->LocalHost = "0,0,0,0";
		ipwFTP->RemoteHost = IP;
		ipwFTP->User = UserName;
		ipwFTP->Password = PassWord;
	}

}
//---------------------------------------------------------------------------

void ScanThread::GetFtpInfo()
{
   RemotAddressX = "scanfiles/Xpoints.txt";
   RemotAddressY = "scanfiles/Ypoints.txt";
   RemoteUsrName = "asarad";
   RemotePasswd = "1234";
   RemoteIp = mainForm->myUdpThread->ipwUDPPort->RemoteHost;
   LocalFileX = "scanfile/Xpoints.txt";
   LocalFileY = "scanfile/Ypoints.txt";
}
//---------------------------------------------------------------------------

void ScanThread::FtpLogin()
{
	if( !ConnectedToHost && !(ipwFTP->Connected) )
		ipwFTP->Logon();
}
//---------------------------------------------------------------------------

void ScanThread::FtpLogOff()
{
	if( ConnectedToHost && (ipwFTP->Connected) )
		ipwFTP->Logoff();
}
//---------------------------------------------------------------------------

void ScanThread::FtpUploader(UnicodeString RemoteFileName, UnicodeString LocalFileName)
{
	if( ConnectedToHost && (ipwFTP->Connected) ){
		Checker = false;
		ipwFTP->RemoteFile = RemoteFileName;
		ipwFTP->LocalFile = LocalFileName;
		ipwFTP->Upload();
	}
}
//---------------------------------------------------------------------------

void ScanThread::FtpDownloader()
{
    if( ConnectedToHost && (ipwFTP->Connected) )
		ipwFTP->Download();
}
//---------------------------------------------------------------------------

void __fastcall ScanThread::FtpConnectionStatusEvent(TObject* Sender, TipwFTPConnectionStatusEventParams *e)
{
	if( e->StatusCode == 0 ){
		ConnectedToHost = true;
		Checker = true;
	}
	else{
		ConnectedToHost = false;
		Checker = false;
	}
}
//---------------------------------------------------------------------------

void __fastcall ScanThread::FtpErrorEvent(TObject* Sender, TipwFTPErrorEventParams *e)
{

}
//---------------------------------------------------------------------------

void __fastcall ScanThread::FtpStartTransferEvent(TObject* Sender, TipwFTPStartTransferEventParams *e)
{

}
//---------------------------------------------------------------------------

void __fastcall ScanThread::FtpTransferEvent(TObject* Sender, TipwFTPTransferEventParams *e)
{

}
//---------------------------------------------------------------------------

void __fastcall ScanThread::FtpEndTransferEvent(TObject* Sender, TipwFTPEndTransferEventParams *e)
{
	Checker = true;
	count++;
	if(count == 2){
		//run TCP and Imager
		//send upd scan command
		//terminate thread
	}
}
//---------------------------------------------------------------------------

