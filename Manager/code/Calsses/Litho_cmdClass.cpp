//---------------------------------------------------------------------------

#pragma hdrstop

#include "Litho_cmdClass.h"
#include "mainUnit.h"
#include "LitoFileCreatorUnit.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------

__fastcall Litho_cmdClass::Litho_cmdClass()
{
	InitClass();
	CreateClassObjects();
	ConfigCalss();
}
//---------------------------------------------------------------------------

void Litho_cmdClass::InitClass()
{
	mainForm->LogToFile("Litho_cmdClass::InitClass");
//	ipwFTP = NULL;
	myCoordinateClass = NULL;
	myLithoFileCreator = NULL;
	checkTimer = NULL;
	myUdpDataSendClass = NULL;
	myTcpDataSendClass = NULL;
//	LithoDesignFrm = NULL;
	mutex = NULL;

	my_scan_resolution = 0;
	my_scan_speed = 0;
	my_scan_delay = 0;
	my_scan_overscan = 0;
	my_center[0] = 0;
	my_center[1] = 0;
	my_scan_x_start = 0;
	my_scan_y_start = 0;
	my_scan_x_step = 0;
	my_scan_y_step = 0;
	my_litho_delay = 0;
	my_litho_startstop = false;
	my_overscan = 0;

	RemoteFileX = "";
	RemoteFileY = "";
	RemoteFileV = "";

	RemotePath = "";
	RemoteUsrName = "";
	RemotePasswd = "";
	RemoteIp = "";

	LocalFileX = "";
	LocalFileY = "";
	LocalFileV = "";

	ConnectedToHost = false;
	uploadCounter = 0;

}
//---------------------------------------------------------------------------

void Litho_cmdClass::CreateClassObjects()
{
//	if(!ipwFTP)
//		ipwFTP = new TipwFTP(NULL);
	mainForm->LogToFile("Litho_cmdClass::CreateClassObjects");
	if(!myCoordinateClass)
		myCoordinateClass = new CoordinateClass;

	if(!myLithoFileCreator)
		myLithoFileCreator = new LithoFileCreator;

	if(!checkTimer){
		checkTimer = new TTimer(NULL);
		checkTimer->Enabled = false;
		checkTimer->Interval=20;
	}

	if(!myUdpDataSendClass){
		myUdpDataSendClass = new UdpDataSendClass(NULL);
	}

	if(!myTcpDataSendClass){
		myTcpDataSendClass = new TcpDataSendClass;
	}

//	if(!LithoDesignFrm){
//		LithoDesignFrm = new TFormLithoDesign(this);
//	}

	if(!mutex){
		mutex = new TMutex(false);
	}
}
//---------------------------------------------------------------------------

void Litho_cmdClass::ConfigCalss()
{
	mainForm->LogToFile("Litho_cmdClass::ConfigCalss");
//	ipwFTP->OnConnectionStatus = FtpConnectionStatusEvent;
//	ipwFTP->OnError = FtpErrorEvent;
//	ipwFTP->OnStartTransfer = FtpStartTransferEvent;
//	ipwFTP->OnTransfer = FtpTransferEvent;
//	ipwFTP->OnEndTransfer = FtpEndTransferEvent;

	checkTimer->OnTimer = CheckTimerEvent;
}
//---------------------------------------------------------------------------

void Litho_cmdClass::GetFtpInfo()
{
	mainForm->LogToFile("Litho_cmdClass::GetFtpInfo");
//   RemoteFileX = "Xpoints.txt";
//   RemoteFileY = "Ypoints.txt";
//   RemoteFileV = "lithopoints.txt";
//   RemotePath = "/home";
//   RemoteUsrName = "root";
//   RemotePasswd = "root";
//   RemoteIp = mainForm->myUdpThread->ipwUDPPort->RemoteHost;

   if( !DirectoryExists(UploadPath) ){
   		AnsiString dir = UploadPath;
		CreateDirectoryA(dir.c_str(),NULL);
   }

   if( !DirectoryExists(DownloadPath) ){
		AnsiString dir = DownloadPath;
		CreateDirectoryA(dir.c_str(),NULL);
   }
   LocalFileX = UploadPath + "/litho/Xpoints.txt";
   LocalFileY = UploadPath + "/litho/Ypoints.txt";
   LocalFileV = UploadPath + "/litho/Vpoints.txt";
}
//---------------------------------------------------------------------------

//void Litho_cmdClass::FtpLogin()
//{
//	if(!ipwFTP->Connected)
//		ipwFTP->Logon();
//}
//---------------------------------------------------------------------------

//void Litho_cmdClass::FtpLogOff()
//{
//	if(ipwFTP->Connected)
//		ipwFTP->Logoff();
//}
//---------------------------------------------------------------------------

//void Litho_cmdClass::FtpUploader(UnicodeString RemoteFileName, UnicodeString LocalFileName)
//{
//	if(ipwFTP->Connected && ipwFTP->Idle){
//		ipwFTP->RemoteFile = RemoteFileName;
//		ipwFTP->LocalFile = LocalFileName;
//		ipwFTP->Upload();
//	}
//}
//---------------------------------------------------------------------------

//void Litho_cmdClass::FtpDownloader()
//{
//	if(ipwFTP->Connected && ipwFTP->Idle)
//		ipwFTP->Download();
//}
//---------------------------------------------------------------------------

//void __fastcall Litho_cmdClass::FtpConnectionStatusEvent(TObject* Sender, TipwFTPConnectionStatusEventParams *e)
//{
//	if( e->StatusCode == 0 && uploadCounter == 0 ){
//		ConnectedToHost = true;
//	}
//	else{
//		ConnectedToHost = false;
//	}
//}
//---------------------------------------------------------------------------

//void __fastcall Litho_cmdClass::FtpErrorEvent(TObject* Sender, TipwFTPErrorEventParams *e)
//{
//	ShowMessage("FtpErrorEvent : " + e->Description);
//}
//---------------------------------------------------------------------------

//void __fastcall Litho_cmdClass::FtpStartTransferEvent(TObject* Sender, TipwFTPStartTransferEventParams *e)
//{
//
//}
//---------------------------------------------------------------------------

//void __fastcall Litho_cmdClass::FtpTransferEvent(TObject* Sender, TipwFTPTransferEventParams *e)
//{
//
//}
//---------------------------------------------------------------------------

//void __fastcall Litho_cmdClass::FtpEndTransferEvent(TObject* Sender, TipwFTPEndTransferEventParams *e)
//{
//	uploadCounter++;
//}
//---------------------------------------------------------------------------

//void Litho_cmdClass::FtpUploaderSetting(UnicodeString IP,UnicodeString UserName,UnicodeString PassWord)
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

void __fastcall Litho_cmdClass::CheckTimerEvent(TObject *Sender)
{
	mainForm->LogToFile("Litho_cmdClass::CheckTimerEvent");
    delay = true;
	checkTimer->Enabled = false;
//	if( (ipwFTP->Connected) && (ipwFTP->Idle) ){
//		if(uploadCounter == 0){
//			FtpUploader(RemoteFileX,LocalFileX);
//			mainForm->LogToFile("litho_cmdClass : CheckTimerEvent : litho x file uploaded");
//		}
//		if(uploadCounter == 1){
//			FtpUploader(RemoteFileY,LocalFileY);
//			mainForm->LogToFile("litho_cmdClass : CheckTimerEvent : litho y file uploaded");
//		}
//		if(uploadCounter == 2){
//			FtpUploader(RemoteFileV,LocalFileV);
//			mainForm->LogToFile("litho_cmdClass : CheckTimerEvent : litho v file uploaded");
//		}
//		if(uploadCounter == 3){
//			FtpLogOff();
//			mainForm->LogToFile("Litho_cmdClass : CheckTimerEvent : litho ftp log off");
//			checkTimer->Enabled = false;
////			ipwFTP->Connected = false;
//			uploadCounter = 0;
////			mainForm->LogToFile("Litho_cmdClass : CheckTimerEvent : " + IntToStr((int)my_litho_startstop));
//
//
//			mainForm->myTcpThread->TcpMode = 3;
//			if(my_litho_startstop){
//				mutex->Acquire();
//				mainForm->myUdpThread->SetUdpSendData(myUdpDataSendClass->LithoPacket(
//													  1,
//													  my_scan_resolution,
//													  my_scan_delay,
//													  my_litho_delay,
//													  my_overscan_count,
//													  myCoordinateClass->FinalRealTL[0],
//													  myCoordinateClass->FinalRealTL[1],
//													  myCoordinateClass->StepVer[0],
//													  myCoordinateClass->StepVer[1],
//													  1
//													  ));
//				mainForm->myUdpThread->SetSendDataTrue();
//				Sleep(100);
//				mutex->Release();
//			}
//			else{
//				mutex->Acquire();
//				mainForm->myUdpThread->SetUdpSendData(myUdpDataSendClass->LithoPacket(
//													  0,
//													  my_scan_resolution,
//													  my_scan_delay,
//													  my_litho_delay,
//													  my_overscan_count,
//													  myCoordinateClass->FinalRealTL[0],
//													  myCoordinateClass->FinalRealTL[1],
//													  myCoordinateClass->StepVer[0],
//													  myCoordinateClass->StepVer[1],
//													  0
//													  ));
//				mainForm->myUdpThread->SetSendDataTrue();
//				Sleep(20);
//				mutex->Release();
//			}
//		}
//	}
}
//---------------------------------------------------------------------------

void Litho_cmdClass::SendLithoPacket()
{
	mainForm->LogToFile("Litho_cmdClass::SendLithoPacket , my_litho_startstop = " + BoolToStr(my_litho_startstop,true));
	if(my_litho_startstop){
		mutex->Acquire();
		mainForm->myUdpThread->SetUdpSendData(myUdpDataSendClass->LithoPacket(
											  1,
											  my_scan_resolution,
											  my_scan_delay,
											  my_litho_delay,
											  my_overscan_count,
											  myCoordinateClass->FinalRealTL[0],
											  myCoordinateClass->FinalRealTL[1],
											  myCoordinateClass->StepVer[0],
											  myCoordinateClass->StepVer[1],
											  1
											  ));
		mainForm->myUdpThread->SetSendDataTrue();
		Sleep(100);
		mutex->Release();
	}
	else{
		mutex->Acquire();
		mainForm->myUdpThread->SetUdpSendData(myUdpDataSendClass->LithoPacket(
											  0,
											  my_scan_resolution,
											  my_scan_delay,
											  my_litho_delay,
											  my_overscan_count,
											  myCoordinateClass->FinalRealTL[0],
											  myCoordinateClass->FinalRealTL[1],
											  myCoordinateClass->StepVer[0],
											  myCoordinateClass->StepVer[1],
											  0
											  ));
		mainForm->myUdpThread->SetSendDataTrue();
		Sleep(20);
		mutex->Release();
	}


}
//---------------------------------------------------------------------------

void Litho_cmdClass::LithoProc(int scan_resolution, int scan_speed, int scan_overscan, double scan_x_center, double scan_y_center, double scan_Xrange, double scan_Yrange, int litho_delay, bool litho_startstop, int Changer)
{
	//get litho config
	mainForm->LogToFile("Litho_cmdClass::LithoProc");
	my_scan_resolution = scan_resolution;
	my_scan_speed = scan_speed;
	my_scan_overscan = scan_overscan;
	my_center[0] = scan_x_center;
	my_center[1] = scan_y_center;
	my_scan_Xrange = scan_Xrange;
	my_scan_Yrange = scan_Xrange;
	my_litho_delay = litho_delay;
	my_litho_startstop = litho_startstop;



//	mainForm->LogToFile("my_scan_resolution = " + IntToStr((int)my_scan_resolution));
//	mainForm->LogToFile("my_scan_speed = " + IntToStr((int)my_scan_speed));
//	mainForm->LogToFile("my_scan_overscan = " + IntToStr((int)my_scan_overscan));
//	mainForm->LogToFile("my_center[0] = " + IntToStr((int)scan_x_center));
//	mainForm->LogToFile("my_center[1] = " + IntToStr((int)scan_y_center));
//	mainForm->LogToFile("my_scan_range = " + IntToStr((int)my_scan_range));
//	mainForm->LogToFile("my_litho_delay = " + IntToStr((int)my_litho_delay));
//	mainForm->LogToFile("my_litho_startstop = " + IntToStr((int)my_litho_startstop));

	//get ftp info
	GetFtpInfo();

	//create files
	my_overscan = (double)((double)my_scan_overscan)/100;
	my_overscan_count = floor( (my_overscan * my_scan_resolution) + 0.5 );
//	mainForm->LogToFile("my_overscan_count = " + IntToStr((int)my_overscan_count));
	my_scan_delay = (int)(pow((double)10,(double)9) / (my_scan_speed * my_scan_resolution * (float)25));
//	mainForm->LogToFile("my_litho_delay = " + IntToStr((int)my_litho_delay));
	int PO = floor(my_scan_resolution * my_overscan + 0.5);
//	mainForm->LogToFile("PO = " + IntToStr((int)PO));

	myCoordinateClass->StartScan(my_center,my_scan_Xrange,my_scan_Yrange,0,my_scan_resolution,PO);

//		mainForm->LogToFile("FinalRealTL[0] = " + IntToStr((int)myCoordinateClass->FinalRealTL[0]));
//		mainForm->LogToFile("FinalRealTL[1] = " + IntToStr((int)myCoordinateClass->FinalRealTL[1]));
//
//		mainForm->LogToFile("FinalRealTR[0] = " + IntToStr((int)myCoordinateClass->FinalRealTR[0]));
//		mainForm->LogToFile("FinalRealTR[1] = " + IntToStr((int)myCoordinateClass->FinalRealTR[1]));
//
//		mainForm->LogToFile("FinalRealBL[0] = " + IntToStr((int)myCoordinateClass->FinalRealBL[0]));
//		mainForm->LogToFile("FinalRealBL[1] = " + IntToStr((int)myCoordinateClass->FinalRealBL[1]));
//
//		mainForm->LogToFile("FinalRealBR[0] = " + IntToStr((int)myCoordinateClass->FinalRealBR[0]));
//		mainForm->LogToFile("FinalRealBR[1] = " + IntToStr((int)myCoordinateClass->FinalRealBR[1]));

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
		mainForm->LogToFile("Litho_cmdClass : LithoProc : litho fault");
		mainForm->myLithoFrm->LithoConfigFrm->EnabledPanels(0);
		mainForm->myLithoFrm->LithoConfigFrm->HighLightChanger(Changer,true);
	}
	else{
		try{
			mainForm->myLithoFrm->LithoConfigFrm->HighLightChanger(-1,false);
			myLithoFileCreator->CreateXfile((int)myCoordinateClass->FinalRealTL[0],(int)myCoordinateClass->StepHor[0],(int)myCoordinateClass->StepVer[0],(int)my_scan_resolution,PO);
			myLithoFileCreator->CreateYfile((int)myCoordinateClass->FinalRealTL[1],(int)myCoordinateClass->StepHor[1],(int)myCoordinateClass->StepVer[1],(int)my_scan_resolution,PO);
//			myLithoFileCreator->CreateVfile((int)my_scan_resolution);
			mainForm->LogToFile("Litho_cmdClass : LithoProc : litho true");
			//create voltage file

			if(my_litho_startstop){
				my_litho_startstop = false;
				SendLithoPacket();
				checkTimer->Enabled = false;
				delay = false;
				checkTimer->Interval = 10;
				checkTimer->Enabled = true;

				while(!delay){
					Application->ProcessMessages();
				}
				my_litho_startstop = litho_startstop;

				mainForm->myLithoFrm->LithoConfigFrm->AdvWiiProgressBar->Show();
				mainForm->myLithoFrm->LithoConfigFrm->Label1->Visible = true;
//
				mainForm->myTcpThread->TcpMode = 4;
				mainForm->myTcpThread->ConnectToServer();
				while(!(mainForm->myTcpThread->ClientConnected)){
					Application->ProcessMessages();
				}
				mainForm->LogToFile("Litho_cmdClass : client connected");
//
//				///////////////////////////////
				mainForm->myTcpThread->TcpSendData(myTcpDataSendClass->LithoXFilePacket(myLithoFileCreator->LithoXFile , myLithoFileCreator->XLength));
//
				while(!(mainForm->myTcpThread->TcpAck))
					Application->ProcessMessages();
				///////////////////////////////
				mainForm->LogToFile("Litho_cmdClass : send data x");

//				mainForm->myTcpThread->DisConnectFromServer();
//				while(mainForm->myTcpThread->ClientConnected){
//					Application->ProcessMessages();
//				}
//				mainForm->LogToFile("Litho_cmdClass : client disconnected");

//				mainForm->myLithoFrm->LithoConfigFrm->Label1->Caption = FloatToStr(((int)((1 / (my_scan_resolution+2)) *10))/10) + " %";
				///////////////////////////////

				mainForm->myTcpThread->ConnectToServer();
				while(!(mainForm->myTcpThread->ClientConnected)){
					Application->ProcessMessages();
				}
				mainForm->LogToFile("Litho_cmdClass : client connected");

				///////////////////////////////

				mainForm->myTcpThread->TcpSendData(myTcpDataSendClass->LithoYFilePacket(myLithoFileCreator->LithoYFile , myLithoFileCreator->YLength));
//				///////////////////////////////
//
				while(!(mainForm->myTcpThread->TcpAck))
					Application->ProcessMessages();
//				///////////////////////////////
//
				mainForm->LogToFile("Litho_cmdClass : send data Y");
//
//				mainForm->myTcpThread->DisConnectFromServer();
//				while(mainForm->myTcpThread->ClientConnected){
//					Application->ProcessMessages();
//				}
//				mainForm->LogToFile("Litho_cmdClass : client disconnected");
//
//				mainForm->myLithoFrm->LithoConfigFrm->Label1->Caption = FloatToStr(((int)((2 / (my_scan_resolution+2)) *10))/10) + " %";
//
				if(mainForm->myLithoFrm->LithoDesignFrm->myPaintForm->BitMapSaved){
					LithoFileCreatorThread *myLithoThread;
					myLithoThread = new LithoFileCreatorThread(true);
					myLithoThread->Priority = tpNormal;
					myLithoThread->FreeOnTerminate = true;
					myLithoThread->litho_file2 = true;
					myLithoThread->Start();
					while(myLithoThread->litho_file2){
						Application->ProcessMessages();
					}
				}
				else{
					LithoFileCreatorThread *myLithoThread;
					myLithoThread = new LithoFileCreatorThread(true);
                    myLithoThread->Priority = tpNormal;
					myLithoThread->FreeOnTerminate = true;
					myLithoThread->litho_file = true;
					myLithoThread->Start();
					while(myLithoThread->litho_file && !myLithoThread->progress){
						Application->ProcessMessages();
					}
				}
//
				mainForm->myLithoFrm->LithoConfigFrm->AdvWiiProgressBar->Hide();
				mainForm->myLithoFrm->LithoConfigFrm->Label1->Visible = false;
                mainForm->myLithoFrm->LithoConfigFrm->Label1->Caption = "Preparation for lithography : 0 %";

				mainForm->myLithoFrm->LithoConfigFrm->EnabledPanels(1);
				SendLithoPacket();
//				FtpUploaderSetting(RemoteIp,RemoteUsrName,RemotePasswd);
//				uploadCounter = 0;
//				FtpLogin();
//				checkTimer->Interval = 5;
//				checkTimer->Enabled = true;
			}
			else{
				SendLithoPacket();
			}
		}
		catch (Exception &exception){
				mainForm->myLithoFrm->LithoConfigFrm->EnabledPanels(0);
				ShowMessage("CreateXfile , or CreateYfile Exception : " + exception.Message + " _ " + exception.StackTrace);
		}
	}

}
//---------------------------------------------------------------------------

