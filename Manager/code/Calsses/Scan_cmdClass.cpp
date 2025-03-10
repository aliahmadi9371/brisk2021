﻿//---------------------------------------------------------------------------
#pragma hdrstop
#include "Scan_cmdClass.h"
#pragma package(smart_init)
#include "mainUnit.h"
//---------------------------------------------------------------------------

__fastcall Scan_cmdClass::Scan_cmdClass()
{
	InitClass();
	CreateClassObjects();
	ConfigCalss();
}
//---------------------------------------------------------------------------

void Scan_cmdClass::ConfigCalss()
{
	mainForm->LogToFile("Scan_cmdClass::ConfigCalss");
//	ipwFTP->OnConnectionStatus = FtpConnectionStatusEvent;
//	ipwFTP->OnError = FtpErrorEvent;
//	ipwFTP->OnStartTransfer = FtpStartTransferEvent;
//	ipwFTP->OnTransfer = FtpTransferEvent;
//	ipwFTP->OnEndTransfer = FtpEndTransferEvent;

	checkTimer->OnTimer = CheckTimerEvent;
}
//---------------------------------------------------------------------------

void Scan_cmdClass::InitClass()
{
	mainForm->LogToFile("Scan_cmdClass::InitClass");
	ConnectedToHost = false;
	count = 0;
	OverScanCount = 0;
//	ipwFTP = NULL;
	myCoordinateClass = NULL;
	myScanFileCreator = NULL;
	checkTimer = NULL;
	myUdpDataSendClass = NULL;
	myTcpDataSendClass = NULL;
	mutex = NULL;
	justSet = false;
	Continues = false;
}
//---------------------------------------------------------------------------

void Scan_cmdClass::CreateClassObjects()
{
	mainForm->LogToFile("Scan_cmdClass::CreateClassObjects");
//	if(!ipwFTP)
//		ipwFTP = new TipwFTP(NULL);

	if(!myCoordinateClass)
		myCoordinateClass = new CoordinateClass;

	if(!myScanFileCreator)
		myScanFileCreator = new ScanFileCreator;

	if(!checkTimer){
		checkTimer = new TTimer(NULL);
		checkTimer->Enabled = false;
		checkTimer->Interval = 50;
	}

	if(!myUdpDataSendClass){
		myUdpDataSendClass = new UdpDataSendClass(NULL);
	}

	if(!myTcpDataSendClass){
		myTcpDataSendClass = new TcpDataSendClass;
	}

	if(!mutex){
		mutex = new TMutex(false);
	}
}
//---------------------------------------------------------------------------
void Scan_cmdClass::GetScanInfoFromUi(int resolution, double xrange, double yrange, int angle, double centerX, double centerY, double over_scan, double speed, int offset){	mainForm->LogToFile("Scan_cmdClass::GetScanInfoFromUi");//	mainForm->LogToFile("scan parameters");//	mainForm->LogToFile("resolution = " + IntToStr(resolution));//	mainForm->LogToFile("range = " + IntToStr(range));//	mainForm->LogToFile("angle = " + IntToStr(angle));//	mainForm->LogToFile("centerX = " + IntToStr(centerX));//	mainForm->LogToFile("centerY = " + IntToStr(centerY));//	mainForm->LogToFile("over_scan = " + IntToStr(over_scan));//	mainForm->LogToFile("speed = " + IntToStr(speed));	Resolution = resolution;	X_Range = xrange;    Y_Range = yrange;	Angle = angle;	Center[0] = centerX;	Center[1] = centerY;	OverScan = (double)((double)over_scan)/100;	FlyDis = offset;	OverScanCount = floor( (OverScan * Resolution) + 0.5 );//	mainForm->LogToFile("OverScanCount = " + IntToStr(OverScanCount));//	mainForm->LogToFile( "real overscan = " + FloatToStr(OverScan) );	Speed = speed;}//---------------------------------------------------------------------------void Scan_cmdClass::Calibration(bool calc){	if(calc){	}}//---------------------------------------------------------------------------

//void Scan_cmdClass::FtpUploaderSetting(UnicodeString IP,UnicodeString UserName,UnicodeString PassWord)
//{
//	if(ipwFTP){
//		try{
//			ipwFTP->LocalHost = "0.0.0.0";
//			ipwFTP->RemoteHost = IP;
//			ipwFTP->User = UserName;
//			ipwFTP->RemotePath = RemotePath;
//			ipwFTP->Password = PassWord;
//			ipwFTP->Overwrite = true;
//		}
//		catch(Exception &exception){}
//	}
//}

//---------------------------------------------------------------------------

void Scan_cmdClass::GetFtpInfo(UnicodeString remote_ip)
{
	mainForm->LogToFile("Scan_cmdClass::GetFtpInfo");
//   RemoteFileX = "Xpoints.txt";
//   RemoteFileY = "Ypoints.txt";
//   RemotePath = "/home";
//   RemoteUsrName = "root";
//   RemotePasswd = "root";
//   RemoteIp = remote_ip;
   LocalFileX = UploadPath + "/scan/Xpoints.txt";
   LocalFileY = UploadPath + "/scan/Ypoints.txt";
}
//---------------------------------------------------------------------------

//void Scan_cmdClass::FtpLogin()
//{
//	if( (!ipwFTP->Connected) )
//		ipwFTP->Logon();
//}
//---------------------------------------------------------------------------

//void Scan_cmdClass::FtpLogOff()
//{
//	if( (ipwFTP->Connected) )
//		ipwFTP->Logoff();
//}
//---------------------------------------------------------------------------

void __fastcall Scan_cmdClass::CheckTimerEvent(TObject *Sender)
{
	mainForm->LogToFile("Scan_cmdClass::CheckTimerEvent");
	delay = true;
	checkTimer->Enabled = false;
}

//---------------------------------------------------------------------------

//void Scan_cmdClass::FtpUploader(UnicodeString RemoteFileName, UnicodeString LocalFileName)
//{
//	if( (ipwFTP->Connected) && (ipwFTP->Idle) ){
//		ipwFTP->RemoteFile = RemoteFileName;
//		ipwFTP->LocalFile = LocalFileName;
//		ipwFTP->Upload();
//	}
//}
//---------------------------------------------------------------------------

//void Scan_cmdClass::FtpDownloader()
//{
//	if( (ipwFTP->Connected) && (ipwFTP->Idle) )
//		ipwFTP->Download();
//}
//---------------------------------------------------------------------------

//void __fastcall Scan_cmdClass::FtpConnectionStatusEvent(TObject* Sender, TipwFTPConnectionStatusEventParams *e)
//{
//	if( (e->StatusCode == 0) && (count == 0) ){
////		mainForm->LogToFile("ftp connected to host: " + e->Description);
//		ConnectedToHost = true;
//	}
//	else{
////		mainForm->LogToFile("ftp connecttion status to host: " + e->Description);
//		ConnectedToHost = false;
//	}
//}
//---------------------------------------------------------------------------

//void __fastcall Scan_cmdClass::FtpErrorEvent(TObject* Sender, TipwFTPErrorEventParams *e)
//{
//	ShowMessage("FtpErrorEvent : " + e->Description);
//}
//---------------------------------------------------------------------------

//void __fastcall Scan_cmdClass::FtpStartTransferEvent(TObject* Sender, TipwFTPStartTransferEventParams *e)
//{
//
//}
//---------------------------------------------------------------------------

//void __fastcall Scan_cmdClass::FtpTransferEvent(TObject* Sender, TipwFTPTransferEventParams *e)
//{
//
//}
//---------------------------------------------------------------------------

//void __fastcall Scan_cmdClass::FtpEndTransferEvent(TObject* Sender, TipwFTPEndTransferEventParams *e)
//{
//	count++;
////	mainForm->myControlPanelForm->Memo1->Lines->Add("ftp transfered file");
////	mainForm->myControlPanelForm->Memo1->Lines->Add("count " + IntToStr(count));
//}
//---------------------------------------------------------------------------

void Scan_cmdClass::ScanProc(bool set, int Changer)
{
	mainForm->LogToFile("Scan_cmdClass::ScanProc , set = " + BoolToStr(set,true) + " , Chamger = " + IntToStr(Changer));
	Delay = (int)(pow((double)10,(double)9) / ((double)Speed * (double)Resolution * (double)25));
	int PO = floor(Resolution * OverScan + 0.5) ;
    justSet = set;
	myCoordinateClass->StartScan(Center,X_Range,Y_Range,Angle,Resolution,PO);

	if (mainForm->AppMode == 3 || mainForm->AppMode == 4) {
		if( ((int)myCoordinateClass->FinalRealTL[0] < -8388607) ||
			((int)myCoordinateClass->FinalRealTL[0] > 8388607 ) ||
			((int)myCoordinateClass->FinalRealTL[1] < -8388607) ||
			((int)myCoordinateClass->FinalRealTL[1] > 8388607 ) ||

			((int)myCoordinateClass->FinalRealTR[0] < -8388607) ||
			((int)myCoordinateClass->FinalRealTR[0] > 8388607 ) ||
			((int)myCoordinateClass->FinalRealTR[1] < -8388607) ||
			((int)myCoordinateClass->FinalRealTR[1] > 8388607 ) ||

			((int)myCoordinateClass->FinalRealBL[0] < -8388607) ||
			((int)myCoordinateClass->FinalRealBL[0] > 8388607 ) ||
			((int)myCoordinateClass->FinalRealBL[1] < -8388607) ||
			((int)myCoordinateClass->FinalRealBL[1] > 8388607 ) ||

			((int)myCoordinateClass->FinalRealBR[0] < -8388607) ||
			((int)myCoordinateClass->FinalRealBR[0] > 8388607 ) ||
			((int)myCoordinateClass->FinalRealBR[1] < -8388607) ||
			((int)myCoordinateClass->FinalRealBR[1] > 8388607 ) ||
			(!mainForm->myScanPanelForm->checkPermission() && mainForm->Scaning)
		){
	//		mainForm->LogToFile("FinalRealTL[0] = " + IntToStr((int)myCoordinateClass->FinalRealTL[0]));
	//		mainForm->LogToFile("FinalRealTL[1] = " + IntToStr((int)myCoordinateClass->FinalRealTL[1]));

	//		mainForm->LogToFile("FinalRealTR[0] = " + IntToStr((int)myCoordinateClass->FinalRealTR[0]));
	//		mainForm->LogToFile("FinalRealTR[1] = " + IntToStr((int)myCoordinateClass->FinalRealTR[1]));

	//		mainForm->LogToFile("FinalRealBL[0] = " + IntToStr((int)myCoordinateClass->FinalRealBL[0]));
	//		mainForm->LogToFile("FinalRealBL[1] = " + IntToStr((int)myCoordinateClass->FinalRealBL[1]));

	//		mainForm->LogToFile("FinalRealBR[0] = " + IntToStr((int)myCoordinateClass->FinalRealBR[0]));
	//		mainForm->LogToFile("FinalRealBR[1] = " + IntToStr((int)myCoordinateClass->FinalRealBR[1]));

			mainForm->LogToFile("Scan_cmdClass : ScanProc : scan fault");
			mainForm->myTcpThread->tcp_imaging = false;
			mainForm->Scaning = false;
			mainForm->myControlPanelForm->EnableScanPanel(0);
			mainForm->myControlPanelForm->scan_selcet = false;
			if(!mainForm->myScanPanelForm->checkPermission())
				Changer = 10;
			else{
				if(Changer == -1 || Changer == 10)
					Changer = 2;
			}

			mainForm->myScanPanelForm->HighLightChanger(Changer,true);
			if(!justSet){
				if(mainForm->myOscForm->FlyError){
					mainForm->myOscForm->FlyError = false;
					ShowMessage("Please Readjust Z-Piezo position ");
				}
				else
					ShowMessage("Please Check Scan Parameters");
			}
			mainForm->Scaning = false;
			mainForm->GetSecure();

		}
		else{
			mainForm->LogToFile("Scan_cmdClass : ScanProc : scan true");
			mainForm->myScanPanelForm->HighLightChanger(-1,false);
//			mainForm->LogToFile("FinalRealTL[0] = " + IntToStr((int)myCoordinateClass->FinalRealTL[0]));
//			mainForm->LogToFile("FinalRealTL[1] = " + IntToStr((int)myCoordinateClass->FinalRealTL[1]));
////
//			mainForm->LogToFile("FinalRealTR[0] = " + IntToStr((int)myCoordinateClass->FinalRealTR[0]));
//			mainForm->LogToFile("FinalRealTR[1] = " + IntToStr((int)myCoordinateClass->FinalRealTR[1]));
////
//			mainForm->LogToFile("FinalRealBL[0] = " + IntToStr((int)myCoordinateClass->FinalRealBL[0]));
//			mainForm->LogToFile("FinalRealBL[1] = " + IntToStr((int)myCoordinateClass->FinalRealBL[1]));
////
//			mainForm->LogToFile("FinalRealBR[0] = " + IntToStr((int)myCoordinateClass->FinalRealBR[0]));
//			mainForm->LogToFile("FinalRealBR[1] = " + IntToStr((int)myCoordinateClass->FinalRealBR[1]));
			try{
				bool XpointCreated = myScanFileCreator->CreateXfile((int)myCoordinateClass->FinalRealTL[0],(int)myCoordinateClass->StepHor[0],(int)myCoordinateClass->StepVer[0],(int)Resolution,PO);
				bool YpointCreated = myScanFileCreator->CreateYfile((int)myCoordinateClass->FinalRealTL[1],(int)myCoordinateClass->StepHor[1],(int)myCoordinateClass->StepVer[1],(int)Resolution,PO);
				if(!XpointCreated || !YpointCreated){
					mainForm->LogToFile("Scan_cmdClass : ScanProc : scan fault");
					mainForm->myTcpThread->tcp_imaging = false;
					mainForm->Scaning = false;
					mainForm->myControlPanelForm->EnableScanPanel(0);
					mainForm->myControlPanelForm->scan_selcet = false;
					mainForm->myScanPanelForm->HighLightChanger(Changer,true);
				}
				else{
//					FtpUploaderSetting(RemoteIp,RemoteUsrName,RemotePasswd);
//					count = 0;
//					FtpLogin();
//					checkTimer->Interval = 20;
//					checkTimer->Enabled = true;
				   	if(!set){
						justSet = true;
						SendScanCommand();
						checkTimer->Enabled = false;
						delay = false;
						checkTimer->Interval = 10;
						checkTimer->Enabled = true;

						while(!delay){
							Application->ProcessMessages();
						}

						justSet = set;
						if(!Continues){
							mainForm->myTcpThread->TcpMode = 4;
							mainForm->myTcpThread->ConnectToServer();
							while(!(mainForm->myTcpThread->ClientConnected)){
								Application->ProcessMessages();
							}

							mainForm->LogToFile("client connected");
							///////////////////////////////
							mainForm->myTcpThread->TcpSendData(myTcpDataSendClass->ScanXFilePacket(myScanFileCreator->XFileTcpData , myScanFileCreator->XLength));

							while(!(mainForm->myTcpThread->TcpAck))
								Application->ProcessMessages();

							mainForm->LogToFile("send data x");
							///////////////////////////////
							mainForm->myTcpThread->DisConnectFromServer();
							while(mainForm->myTcpThread->ClientConnected){
								Application->ProcessMessages();
							}
							mainForm->LogToFile("client disconnected");

							///////////////////////////////


							mainForm->myTcpThread->ConnectToServer();
							while(!(mainForm->myTcpThread->ClientConnected)){
								Application->ProcessMessages();
							}
							mainForm->LogToFile("client connected");

							///////////////////////////////

							mainForm->myTcpThread->TcpSendData(myTcpDataSendClass->ScanYFilePacket(myScanFileCreator->YFileTcpData , myScanFileCreator->YLength));

							while(!(mainForm->myTcpThread->TcpAck))
								Application->ProcessMessages();

							mainForm->LogToFile("send data Y");
							///////////////////////////////

							mainForm->myTcpThread->DisConnectFromServer();
							while(mainForm->myTcpThread->ClientConnected){
								Application->ProcessMessages();
							}
							mainForm->LogToFile("client disconnected");


							///////////////////////////////
						}


						SendScanCommand();
					}
					else{

						SendScanCommand();
					}

				}
			}
			catch (Exception &exception){
				mainForm->myControlPanelForm->EnableScanPanel(0);
				ShowMessage("CreateXfile , or CreateYfile Exception : " + exception.Message + " _ " + exception.StackTrace);
			}
		}
	}
	else{
		if( ((int)myCoordinateClass->FinalRealTL[0] < -8388607) ||
			((int)myCoordinateClass->FinalRealTL[0] > 8388607 ) ||
			((int)myCoordinateClass->FinalRealTL[1] < -8388607) ||
			((int)myCoordinateClass->FinalRealTL[1] > 8388607 ) ||

			((int)myCoordinateClass->FinalRealTR[0] < -8388607) ||
			((int)myCoordinateClass->FinalRealTR[0] > 8388607 ) ||
			((int)myCoordinateClass->FinalRealTR[1] < -8388607) ||
			((int)myCoordinateClass->FinalRealTR[1] > 8388607 ) ||

			((int)myCoordinateClass->FinalRealBL[0] < -8388607) ||
			((int)myCoordinateClass->FinalRealBL[0] > 8388607 ) ||
			((int)myCoordinateClass->FinalRealBL[1] < -8388607) ||
			((int)myCoordinateClass->FinalRealBL[1] > 8388607 ) ||

			((int)myCoordinateClass->FinalRealBR[0] < -8388607) ||
			((int)myCoordinateClass->FinalRealBR[0] > 8388607 ) ||
			((int)myCoordinateClass->FinalRealBR[1] < -8388607) ||
			((int)myCoordinateClass->FinalRealBR[1] > 8388607 )
		){
//			mainForm->LogToFile("FinalRealTL[0] = " + IntToStr((int)myCoordinateClass->FinalRealTL[0]));
//			mainForm->LogToFile("FinalRealTL[1] = " + IntToStr((int)myCoordinateClass->FinalRealTL[1]));
////
//			mainForm->LogToFile("FinalRealTR[0] = " + IntToStr((int)myCoordinateClass->FinalRealTR[0]));
//			mainForm->LogToFile("FinalRealTR[1] = " + IntToStr((int)myCoordinateClass->FinalRealTR[1]));
////
//			mainForm->LogToFile("FinalRealBL[0] = " + IntToStr((int)myCoordinateClass->FinalRealBL[0]));
//			mainForm->LogToFile("FinalRealBL[1] = " + IntToStr((int)myCoordinateClass->FinalRealBL[1]));
////
//			mainForm->LogToFile("FinalRealBR[0] = " + IntToStr((int)myCoordinateClass->FinalRealBR[0]));
//			mainForm->LogToFile("FinalRealBR[1] = " + IntToStr((int)myCoordinateClass->FinalRealBR[1]));

			mainForm->LogToFile("Scan_cmdClass : ScanProc : scan fault");
			mainForm->myTcpThread->tcp_imaging = false;
			mainForm->Scaning = false;
			mainForm->myControlPanelForm->EnableScanPanel(0);
			mainForm->myControlPanelForm->scan_selcet = false;
			if(Changer == -1)
				Changer = 2;
			mainForm->myScanPanelForm->HighLightChanger(Changer,true);
			if(!justSet)
				ShowMessage("Please Check Scan Parameters");
            mainForm->Scaning = false;
			mainForm->GetSecure();
		}
		else{
			mainForm->LogToFile("Scan_cmdClass : ScanProc : scan true");
			mainForm->myScanPanelForm->HighLightChanger(-1,false);
//			mainForm->LogToFile("FinalRealTL[0] = " + IntToStr((int)myCoordinateClass->FinalRealTL[0]));
//			mainForm->LogToFile("FinalRealTL[1] = " + IntToStr((int)myCoordinateClass->FinalRealTL[1]));
////
//			mainForm->LogToFile("FinalRealTR[0] = " + IntToStr((int)myCoordinateClass->FinalRealTR[0]));
//			mainForm->LogToFile("FinalRealTR[1] = " + IntToStr((int)myCoordinateClass->FinalRealTR[1]));
////
//			mainForm->LogToFile("FinalRealBL[0] = " + IntToStr((int)myCoordinateClass->FinalRealBL[0]));
//			mainForm->LogToFile("FinalRealBL[1] = " + IntToStr((int)myCoordinateClass->FinalRealBL[1]));
////
//			mainForm->LogToFile("FinalRealBR[0] = " + IntToStr((int)myCoordinateClass->FinalRealBR[0]));
//			mainForm->LogToFile("FinalRealBR[1] = " + IntToStr((int)myCoordinateClass->FinalRealBR[1]));
			try{
				bool XpointCreated = myScanFileCreator->CreateXfile((int)myCoordinateClass->FinalRealTL[0],(int)myCoordinateClass->StepHor[0],(int)myCoordinateClass->StepVer[0],(int)Resolution,PO);
				bool YpointCreated = myScanFileCreator->CreateYfile((int)myCoordinateClass->FinalRealTL[1],(int)myCoordinateClass->StepHor[1],(int)myCoordinateClass->StepVer[1],(int)Resolution,PO);
				if(!XpointCreated || !YpointCreated)
				{
					mainForm->LogToFile("Scan_cmdClass : ScanProc : scan fault");
					mainForm->myTcpThread->tcp_imaging = false;
					mainForm->Scaning = false;
					mainForm->myControlPanelForm->EnableScanPanel(0);
					mainForm->myControlPanelForm->scan_selcet = false;
					mainForm->myScanPanelForm->HighLightChanger(Changer,true);
				}
				else
				{
//					FtpUploaderSetting(RemoteIp,RemoteUsrName,RemotePasswd);
//					count = 0;
//					FtpLogin();
//					checkTimer->Interval = 20;
//					checkTimer->Enabled = true;
					if(!set){
						justSet = true;
						SendScanCommand();
						checkTimer->Enabled = false;
						delay = false;
						checkTimer->Interval = 10;
						checkTimer->Enabled = true;

						while(!delay){
							Application->ProcessMessages();
						}

						justSet = set;
//						mainForm->LogToFile("Scan_cmdClass::ScanProc : ________________________________________ Continues =  " + BoolToStr(Continues,true));
						if(!Continues){
							mainForm->myTcpThread->TcpMode = 4;
							mainForm->myTcpThread->ConnectToServer();
							while(!(mainForm->myTcpThread->ClientConnected)){
								Application->ProcessMessages();
							}

							mainForm->LogToFile("client connected");
							///////////////////////////////
							mainForm->myTcpThread->TcpSendData(myTcpDataSendClass->ScanXFilePacket(myScanFileCreator->XFileTcpData , myScanFileCreator->XLength));

							while(!(mainForm->myTcpThread->TcpAck))
								Application->ProcessMessages();

							mainForm->LogToFile("send data x");
							///////////////////////////////
							mainForm->myTcpThread->DisConnectFromServer();
							while(mainForm->myTcpThread->ClientConnected){
								Application->ProcessMessages();
							}
							mainForm->LogToFile("client disconnected");

							///////////////////////////////


							mainForm->myTcpThread->ConnectToServer();
							while(!(mainForm->myTcpThread->ClientConnected)){
								Application->ProcessMessages();
							}
							mainForm->LogToFile("client connected");

							///////////////////////////////

							mainForm->myTcpThread->TcpSendData(myTcpDataSendClass->ScanYFilePacket(myScanFileCreator->YFileTcpData , myScanFileCreator->YLength));

							while(!(mainForm->myTcpThread->TcpAck))
								Application->ProcessMessages();

							mainForm->LogToFile("send data Y");
							///////////////////////////////

							mainForm->myTcpThread->DisConnectFromServer();
							while(mainForm->myTcpThread->ClientConnected){
								Application->ProcessMessages();
							}
							mainForm->LogToFile("client disconnected");


							///////////////////////////////
                        }


						SendScanCommand();
					}
					else{

						SendScanCommand();
					}
				}
			}
			catch (Exception &exception){
				mainForm->myControlPanelForm->EnableScanPanel(0);
				ShowMessage("CreateXfile , or CreateYfile Exception : " + exception.Message + " _ " + exception.StackTrace);
			}
		}
	}

}
//---------------------------------------------------------------------------

void Scan_cmdClass::SendScanCommand()
{
	mainForm->LogToFile("Scan_cmdClass::SendScanCommand , justSet = " + BoolToStr(justSet,true));
    if(justSet){
		mainForm->LogToFile("Scan_cmdClass : SendScanCommand : scan stop");
		mutex->Acquire();
		mainForm->myUdpThread->SetUdpSendData(myUdpDataSendClass->ScanPacket(
											  Resolution,
											  Delay,
											  OverScanCount,
											  myCoordinateClass->FinalRealTL[0],
											  myCoordinateClass->FinalRealTL[1],
											  myCoordinateClass->StepVer[0],
											  myCoordinateClass->StepVer[1],
											  FlyDis,
											  0
											  ));
		mainForm->myUdpThread->SetSendDataTrue();
		Sleep(100);
		mutex->Release();
	}
	else{
//				mainForm->RunTCPThread( (int)Resolution );
		mainForm->LogToFile("Scan_cmdClass : SendScanCommand : scan start");
		mainForm->myScanPanelForm->AddToHistory();

		img_queue->initQ();
		mainForm->myTcpThread->PacketSize = (int)Resolution;
		mainForm->myTcpThread->FirstTcpMode = false; // just log first connection
		mainForm->myTcpThread->bytes.Length = Resolution*4 + HEADER_COUNT_IMAGE;
		mainForm->myTcpThread->TcpMode = 0;
		mainForm->myTcpThread->CurrentResolution = (int)Resolution;
		img_queue->initQ();


		mainForm->RunImagerThread();
		mutex->Acquire();
		mainForm->myUdpThread->SetUdpSendData(myUdpDataSendClass->ScanPacket(
											  Resolution,
											  Delay,
											  OverScanCount,
											  myCoordinateClass->FinalRealTL[0],
											  myCoordinateClass->FinalRealTL[1],
											  myCoordinateClass->StepVer[0],
											  myCoordinateClass->StepVer[1],
											  FlyDis,
											  1
											  ));
		mainForm->myUdpThread->SetSendDataTrue();
		Sleep(100);
		mutex->Release();
        mainForm->myControlPanelForm->EnableScanPanel(2);
	}
}
//---------------------------------------------------------------------------

void __fastcall Scan_cmdClass::SendScanPacket()
{
	mainForm->LogToFile("Scan_cmdClass::SendScanPacket");
	mainForm->myUdpThread->SendBytes();
}
//---------------------------------------------------------------------------

