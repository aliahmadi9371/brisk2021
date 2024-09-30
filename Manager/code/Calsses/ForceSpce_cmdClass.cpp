//---------------------------------------------------------------------------

#pragma hdrstop

#include "ForceSpce_cmdClass.h"
#include "mainUnit.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------

__fastcall Fs_cmdClass::Fs_cmdClass()
{
	InitClass();
	CreateClassObjects();
	ConfigCalss();
}
//---------------------------------------------------------------------------

void Fs_cmdClass::InitClass()
{
	mainForm->LogToFile("Fs_cmdClass::InitClass");
	RemoteFileZ = "";
	RemoteFileU = "";
	RemotePath = "";
	RemoteUsrName = "";
	RemotePasswd = "";
	RemoteIp = "";
	LocalFileZ = "";
	LocalFileU = "";

	RemoteFileTopo_Fw = "";
	RemoteFileTb_Fw = "";
	RemoteFileLr_Fw = "";
	RemoteFileAmp_Fw = "";
	RemoteFilePhase_Fw = "";
	RemoteFileCmAfm_Fw = "";

	LocalFileTopo_Fw = "";
	LocalFileTb_Fw = "";
	LocalFileLr_Fw = "";
	LocalFileAmp_Fw = "";
	LocalFilePhase_Fw = "";
	LocalFileCmAfm_Fw = "";

	RemoteFileTopo_Bw = "";
	RemoteFileTb_Bw = "";
	RemoteFileLr_Bw = "";
	RemoteFileAmp_Bw = "";
	RemoteFilePhase_Bw = "";
	RemoteFileCmAfm_Bw = "";

	LocalFileTopo_Bw = "";
	LocalFileTb_Bw = "";
	LocalFileLr_Bw = "";
	LocalFileAmp_Bw = "";
	LocalFilePhase_Bw = "";
	LocalFileCmAfm_Bw = "";

	SaveDirection = "";


	ConnectedToHost = false;

	UpCount = 0;
	DnCount = 0;

	UpLoad = false;
	DnLoad = false;

//	ipwFTP = NULL;
//	checkTimerUpLoader = NULL;
//	checkTimerDnLoader = NULL;
	CheckTimer = NULL;

	myUdpDataSendClass = NULL;
	myTcpDataSendClass = NULL;
	mutex = NULL;

	FsXStart = 0;
	FsYStart = 0;
	FsResolution = 0;
	FsDelay = 0;
	FsMode = 0;
	FsGoto = 0;

	tmpSeries = 0;
}
//---------------------------------------------------------------------------

void Fs_cmdClass::CreateClassObjects()
{
	mainForm->LogToFile("Fs_cmdClass::CreateClassObjects");
//	if(!ipwFTP)
//		ipwFTP = new TipwFTP(NULL);
//
//	if(!checkTimerUpLoader){
//		checkTimerUpLoader = new TTimer(NULL);
//		checkTimerUpLoader->Enabled = false;
//		checkTimerUpLoader->Interval=20;
//	}

//	if(!checkTimerDnLoader){
//		checkTimerDnLoader = new TTimer(NULL);
//		checkTimerDnLoader->Enabled = false;
//		checkTimerDnLoader->Interval=20;
//	}
	if(!CheckTimer){
		CheckTimer = new TTimer(NULL);
		CheckTimer->Enabled = false;
		CheckTimer->Interval=50;
	}

//
	if(!myUdpDataSendClass){
		myUdpDataSendClass = new UdpDataSendClass(NULL);
	}

	if(!myTcpDataSendClass){
		myTcpDataSendClass = new TcpDataSendClass;
	}
//
	if(!mutex){
		mutex = new TMutex(false);
	}
}
//---------------------------------------------------------------------------

void Fs_cmdClass::ConfigCalss()
{
	mainForm->LogToFile("Fs_cmdClass::ConfigCalss");
	CheckTimer->OnTimer = CheckTimerEvent;
}
//---------------------------------------------------------------------------

void Fs_cmdClass::StartFsProcess(bool start, double startx, double starty, int resolution, int delay, int mode, int GOTO, int dz1, int dz2, int u1, int u2, int currentZ, int currentU)
{
	mainForm->LogToFile("Fs_cmdClass::StartFsProcess");
	justSet = !start;
	if(justSet , GOTO == 1 ){
		justGo = true;
	}
	else{
		justGo = false;
	}
//	mainForm->LogToFile("Fs_cmdClass::StartFsProcess : justGo = " + BoolToStr(justGo,true));
	mainForm->myTcpThread->PacketSize = (int)resolution;
//	mainForm->LogToFile("force start_stop = " + BoolToStr(startx, true));
//	mainForm->LogToFile("force justSet = " + BoolToStr(justSet, true));
//	mainForm->LogToFile("force startx = " + IntToStr(startx));
//	mainForm->LogToFile("force starty = " + IntToStr(starty));
//	mainForm->LogToFile("force resolution = " + IntToStr(resolution));
//	mainForm->LogToFile("force delay = " + IntToStr(delay));
//	mainForm->LogToFile("force mode = " + IntToStr(mode));
//	mainForm->LogToFile("force GOTO = " + IntToStr(GOTO));
//	mainForm->LogToFile("force z1 = " + IntToStr(dz1));
//	mainForm->LogToFile("force z2 = " + IntToStr(dz2));
//	mainForm->LogToFile("force u1 = " + IntToStr(u1));
//	mainForm->LogToFile("force u2 = " + IntToStr(u2));
//
//	mainForm->LogToFile("force currentZ = " + IntToStr(currentZ));
//	mainForm->LogToFile("force currentU = " + IntToStr(currentU));
//	z1 = 100 - z1;
//	z2 = 100 - z2;

//	z1 = 167772.16 * z1 - 8388608;
//	z2 = 167772.16 * z2 - 8388608;

	switch (Scanner_Type){
		case 0:{
			FsXStart =  8388607 - startx * 167772.14;
			FsYStart =  starty * 167772.14 - 8388607;
			break;
		}
		case 1:{
			FsXStart =  8388607 - startx * 167772.14;
			FsYStart =  8388607 - starty * 167772.14;
			break;
		}
		case 2:{
			FsXStart =  startx * 167772.14 - 8388607;
			FsYStart =  8388607 - starty * 167772.14;
			break;
		}
		case 3:{
			FsXStart =  startx * 167772.14 - 8388607;
			FsYStart =  starty * 167772.14 - 8388607;
			break;
		}
	}
//	FsXStart = 167772.16 * startx - 8388608;
//	FsYStart = 167772.16 * starty - 8388608;

	FsResolution = resolution;
	FsDelay = delay;
	FsMode = mode;
	FsGoto = GOTO;

	if(!justGo){
		CreateZPoints(dz1, dz2, resolution, currentZ, mode);
		CreateUPoints(u1, u2, resolution, currentU, mode);
//		CreateFsFiles(resolution, delay, mode, dz1, dz2, u1, u2, currentZ, currentU);
		GetFtpInfo();
		UploadFilesToBrisk();
	}
	else {
		SendGotoCmdStart();
	}
}
//---------------------------------------------------------------------------

bool Fs_cmdClass::UploadFilesToBrisk()
{
	mainForm->LogToFile("Fs_cmdClass::UploadFilesToBrisk");
	if(!justSet){
		bool StartStop = justSet;
		justSet = true;
		SendForceCommand();

		CheckTimer->Enabled = false;
		delay = false;
		CheckTimer->Interval = 10;
		CheckTimer->Enabled = true;

		while(!delay){
			Application->ProcessMessages();
		}

		justSet = StartStop;


		mainForm->myTcpThread->TcpMode = 4;
		mainForm->myTcpThread->ConnectToServer();

		while(!(mainForm->myTcpThread->ClientConnected)){
			Application->ProcessMessages();
		}
		mainForm->LogToFile("Fs_cmdClass : client connected");

//		mainForm->myTcpThread->ipwTcpClient->EOL = "";
		mainForm->myTcpThread->TcpSendData(myTcpDataSendClass->ForceZFilePacket(zpoints , ZLength));

		while(!(mainForm->myTcpThread->TcpAck))
			Application->ProcessMessages();

		mainForm->LogToFile("Fs_cmdClass : get send data z ack");

//		mainForm->myTcpThread->DisConnectFromServer();
//		while(mainForm->myTcpThread->ClientConnected){
//			Application->ProcessMessages();
//		}
//		mainForm->LogToFile("Fs_cmdClass : client disconnected");
//
		mainForm->myTcpThread->ConnectToServer();
		while(!(mainForm->myTcpThread->ClientConnected)){
			Application->ProcessMessages();
		}
		mainForm->LogToFile("Fs_cmdClass : client connected");
//

		mainForm->myTcpThread->TcpSendData(myTcpDataSendClass->ForceUFilePacket(upoints , ULength));
//
		while(!(mainForm->myTcpThread->TcpAck))
			Application->ProcessMessages();
//
		mainForm->LogToFile("Fs_cmdClass : send data U");
//
//		mainForm->myTcpThread->DisConnectFromServer();
//		while(mainForm->myTcpThread->ClientConnected){
//			Application->ProcessMessages();
//		}
//		mainForm->LogToFile("Fs_cmdClass : client disconnected");
//
		SendForceCommand();
        mainForm->myForceForm->EnableFsPanel(1);
		return true;
	}
	else{
        SendForceCommand();
	}
}
//---------------------------------------------------------------------------

void __fastcall Fs_cmdClass::CheckTimerEvent(TObject *Sender)
{
	mainForm->LogToFile("Fs_cmdClass::CheckTimerEvent");
	delay = true;
	CheckTimer->Enabled = false;
}
//---------------------------------------------------------------------------

void Fs_cmdClass::SendForceCommand()
{
	mainForm->LogToFile("Fs_cmdClass::SendForceCommand : justSet = " + BoolToStr(justSet,true));
	if(justSet){		//set values on brisk
		OffFs();

	}
	else{			//start force spectroscopy command

		SendFsCmdStart();
	}


}
//---------------------------------------------------------------------------

void Fs_cmdClass::GetFtpInfo()
{
	mainForm->LogToFile("Fs_cmdClass::GetFtpInfo");
	LocalFileZ = UploadPath + "/force/Zpoints.txt";
	LocalFileU = UploadPath + "/force/Upoints.txt";


	RemoteFileTopo_Fw = "Fw_Fs_Topo.txt";
	RemoteFileTb_Fw = "Fw_Fs_Tb.txt";
	RemoteFileLr_Fw = "Fw_Fs_Lr.txt";
	RemoteFileAmp_Fw = "Fw_Fs_Amp.txt";
	RemoteFilePhase_Fw = "Fw_Fs_Phase.txt";
	RemoteFileCmAfm_Fw = "Fw_Fs_CmAfm.txt";


	UnicodeString FsPath = DownloadPath;
	if( !DirectoryExists(FsPath) ){
		AnsiString dir = FsPath;
		CreateDirectoryA(dir.c_str(),NULL);
	}

	FsPath = FsPath + "/" + mainForm->myForceForm->FsFolder;
	if( !DirectoryExists(FsPath) ){
		AnsiString dir = FsPath;
		CreateDirectoryA(dir.c_str(),NULL);
	}

	FsPath = FsPath + "/" + mainForm->myForceForm->DateFolder;
	if( !DirectoryExists(FsPath) ){
		AnsiString dir = FsPath;
		CreateDirectoryA(dir.c_str(),NULL);
	}
	if(!mainForm->myTcpThread->fs_set){
		FsPath = FsPath + "/" +  mainForm->myForceForm->TimeFolder;
		if( !DirectoryExists(FsPath) ){
			AnsiString dir = FsPath;
			CreateDirectoryA(dir.c_str(),NULL);
		}
	}

	LocalFileTopo_Fw = FsPath + "/" + mainForm->myForceForm->TimeFolder + "_Fw_Fs_Topo.txt";
	LocalFileTb_Fw = FsPath + "/" + mainForm->myForceForm->TimeFolder + "_Fw_Fs_Tb.txt";
	LocalFileLr_Fw = FsPath + "/" + mainForm->myForceForm->TimeFolder + "_Fw_Fs_Lr.txt";
	LocalFileAmp_Fw = FsPath + "/" + mainForm->myForceForm->TimeFolder + "_Fw_Fs_Amp.txt";
	LocalFilePhase_Fw = FsPath + "/" + mainForm->myForceForm->TimeFolder + "_Fw_Fs_Phase.txt";
	LocalFileCmAfm_Fw = FsPath + "/" + mainForm->myForceForm->TimeFolder + "_Fw_Fs_CmAfm.txt";
	SaveDirection = FsPath;

	RemoteFileTopo_Bw = "Bw_Fs_Topo.txt";
	RemoteFileTb_Bw = "Bw_Fs_Tb.txt";
	RemoteFileLr_Bw = "Bw_Fs_Lr.txt";
	RemoteFileAmp_Bw = "Bw_Fs_Amp.txt";
	RemoteFilePhase_Bw = "Bw_Fs_Phase.txt";
	RemoteFileCmAfm_Bw = "Bw_Fs_CmAfm.txt";

	LocalFileTopo_Bw = FsPath + "/" + mainForm->myForceForm->TimeFolder + "_Bw_Fs_Topo.txt";
	LocalFileTb_Bw = FsPath + "/" + mainForm->myForceForm->TimeFolder + "_Bw_Fs_Tb.txt";
	LocalFileLr_Bw = FsPath + "/" + mainForm->myForceForm->TimeFolder + "_Bw_Fs_Lr.txt";
	LocalFileAmp_Bw = FsPath + "/" + mainForm->myForceForm->TimeFolder + "_Bw_Fs_Amp.txt";
	LocalFilePhase_Bw = FsPath + "/" + mainForm->myForceForm->TimeFolder + "_Bw_Fs_Phase.txt";
	LocalFileCmAfm_Bw = FsPath + "/" + mainForm->myForceForm->TimeFolder + "_Bw_Fs_CmAfm.txt";


	mainForm->myTcpThread->LocalFileTopo_Fw = LocalFileTopo_Fw;
	mainForm->myTcpThread->LocalFileTb_Fw = LocalFileTb_Fw;
	mainForm->myTcpThread->LocalFileLr_Fw = LocalFileLr_Fw;
	mainForm->myTcpThread->LocalFileAmp_Fw = LocalFileAmp_Fw;
	mainForm->myTcpThread->LocalFilePhase_Fw = LocalFilePhase_Fw;
	mainForm->myTcpThread->LocalFileCmAfm_Fw = LocalFileCmAfm_Fw;

	mainForm->myTcpThread->LocalFileTopo_Bw = LocalFileTopo_Bw;
	mainForm->myTcpThread->LocalFileTb_Bw = LocalFileTb_Bw;
	mainForm->myTcpThread->LocalFileLr_Bw = LocalFileLr_Bw;
	mainForm->myTcpThread->LocalFileAmp_Bw = LocalFileAmp_Bw;
	mainForm->myTcpThread->LocalFilePhase_Bw = LocalFilePhase_Bw;
	mainForm->myTcpThread->LocalFileCmAfm_Bw = LocalFileCmAfm_Bw;
	mainForm->myTcpThread->SaveDirection = SaveDirection;

}
//---------------------------------------------------------------------------

//void Fs_cmdClass::FtpUploaderSetting(UnicodeString IP,UnicodeString UserName,UnicodeString PassWord)
//{
//	if(ipwFTP){
//		try{
//			ipwFTP->TransferMode = 2 ;
//
//			ipwFTP->LocalHost = "0.0.0.0";
////			mainForm->LogToFile("force LocalHost = " + ipwFTP->LocalHost);
//
//			ipwFTP->RemoteHost = IP;
////			mainForm->LogToFile("force RemoteHost = " + ipwFTP->RemoteHost);
//
//			ipwFTP->RemotePath = RemotePath;
////			mainForm->LogToFile("force RemotePath = " + ipwFTP->RemotePath);
//
//			ipwFTP->User = UserName;
////			mainForm->LogToFile("force User = " + ipwFTP->User);
//
//			ipwFTP->Password = PassWord;
////			mainForm->LogToFile("force Password = " + ipwFTP->Password);
//
//			ipwFTP->Overwrite = true;
////			mainForm->LogToFile("force Overwrite = " + BoolToStr(ipwFTP->Overwrite,true));
//
//		}
//		catch(Exception &exception){}
//	}
//}
//---------------------------------------------------------------------------

//void Fs_cmdClass::FtpLogin()
//{
//	if( (!ipwFTP->Connected) )
//		ipwFTP->Logon();
//}
//---------------------------------------------------------------------------

//void Fs_cmdClass::FtpLogOff()
//{
//	if( (ipwFTP->Connected) )
//		ipwFTP->Logoff();
//}
//---------------------------------------------------------------------------

//void Fs_cmdClass::FtpUploader(UnicodeString RemoteFileName, UnicodeString LocalFileName)
//{
//	if( (ipwFTP->Connected) && (ipwFTP->Idle) ){
//		ipwFTP->RemoteFile = RemoteFileName;
//		ipwFTP->LocalFile = LocalFileName;
//		ipwFTP->Upload();
//	}
//}
//---------------------------------------------------------------------------



//void __fastcall Fs_cmdClass::FtpConnectionStatusEvent(TObject* Sender, TipwFTPConnectionStatusEventParams *e)
//{
//	if( (e->StatusCode == 0) && (UpCount == 0) ){
////		mainForm->LogToFile("force ftp connected to host: " + e->Description);
//		ConnectedToHost = true;
//	}
//	else{
////		mainForm->LogToFile("force ftp connecttion status to host: " + e->Description);
//		ConnectedToHost = false;
//	}
//}
//---------------------------------------------------------------------------

//void __fastcall Fs_cmdClass::FtpErrorEvent(TObject* Sender, TipwFTPErrorEventParams *e)
//{
//	mainForm->LogToFile("Fs_cmdClass : FtpErrorEvent : " + e->Description);
//}
//---------------------------------------------------------------------------

//void Fs_cmdClass::CreateFsFiles(int resolution, int delay, int mode, int dz1, int dz2, int u1, int u2, int currentZ, int currentU)
//{
//	CreateZPoints(dz1, dz2, resolution, currentZ, mode);
//	CreateUPoints(u1, u2, resolution, currentU, mode);
//	mainForm->LogToFile("Fs_cmdClass::CreateFsFiles");
//	if( !DirectoryExists(UploadPath) ){
//		AnsiString dir = UploadPath;
//		CreateDirectoryA(dir.c_str(),NULL);
//	}
//
//	if( !DirectoryExists(DownloadPath) ){
//		AnsiString dir = DownloadPath;
//		CreateDirectoryA(dir.c_str(),NULL);
//	}
//
//	if(!DirectoryExists(UploadPath + "/force")){
//		AnsiString dir = UploadPath + "/force";
//		CreateDirectoryA(dir.c_str(),NULL);
//	}

//	AnsiString name_z = UploadPath + "/force/Zpoints.txt";
//	AnsiString name_u = UploadPath + "/force/Upoints.txt";
//	DeleteFileW(name_z);
//	DeleteFileW(name_u);

//	ofstream *zfile;
//	zfile = new ofstream(name_z.c_str(), ios::out);
//	AnsiString tmp;
//	for(int i=0; i < 2 * resolution; i++){
//		tmp = IntToStr((int)(zpoints[i]))+'\n';
//		zfile->write(tmp.c_str(), tmp.Length());
//	}
//	zfile->close();
//	delete[] zpoints;

//	ofstream *ufile;
//	ufile = new ofstream(name_u.c_str(), ios::out);
//	for(int i=0; i < 2 * resolution; i++){
//		tmp = IntToStr((int)(upoints[i]))+'\n';
//		ufile->write(tmp.c_str(), tmp.Length());
//	}
//	ufile->close();
//	delete[] upoints;
//}
//---------------------------------------------------------------------------

void Fs_cmdClass::CreateZPoints(int dz1, int dz2, int resolution, int currentZ, int mode)
{
	mainForm->LogToFile("Fs_cmdClass::CreateZPoints");
	ZLength = 2*resolution;
	zpoints = new int[ZLength];
	int dz = dz2;
	double zstep = (double)dz/(double)resolution;

	if(mode == 2 || mode == 3 || mode == 6 || mode == 7 || mode == 8 )
		zstep = 0;

	zpoints[0] = dz1;
//	mainForm->LogToFile("force zpoints[0] = " + IntToStr(zpoints[0]));

	for(int i=0; i<resolution; i++)
		zpoints[i+1] = zstep;

	for(int i=0; i<resolution-1; i++)
		zpoints[(i+1)+resolution] = -(zstep);



}
//---------------------------------------------------------------------------

void Fs_cmdClass::CreateUPoints(int u1, int u2, int resolution, int currentU, int mode)
{
	mainForm->LogToFile("Fs_cmdClass::CreateUPoints");
	ULength = 2*resolution;
	upoints = new int[ULength];
	int du = u2-u1;
	double ustep = (double)du/(double)resolution;

	if(mode == 1 || mode == 4 || mode == 5)
		ustep = 0;

	upoints[0] = u1 - currentU;
//	mainForm->LogToFile("force upoints[0] = " + IntToStr(upoints[0]));

	for(int i=0; i<resolution; i++)
		upoints[i+1] = ustep;

	for(int i=0; i<resolution-1; i++)
		upoints[(i+1)+resolution] = -(ustep);

}
//---------------------------------------------------------------------------

//void __fastcall Fs_cmdClass::checkTimerUpLoaderEvent(TObject *Sender)
//{
//	if( (ipwFTP->Connected) && (ipwFTP->Idle) ){
//		switch(UpCount){
//			case 0: {
//				FtpUploader(RemoteFileZ,LocalFileZ);
//				mainForm->LogToFile("Fs_cmdClass : checkTimerUpLoaderEvent : force z file uploaded");
//				break;
//			}
//			case 1:{
//				FtpUploader(RemoteFileU,LocalFileU);
//				mainForm->LogToFile("Fs_cmdClass : checkTimerUpLoaderEvent : force u file uploaded");
//				break;
//			}
//			case 2:{
//				checkTimerUpLoader->Enabled = false;
//				UpCount = 0;
//				UpLoad = false;
//
//				if(justSet){		//set values on brisk
//					OffFs();
//					if(!mainForm->myTcpThread->fs_set){
//						mainForm->myForceForm->EnableFsPanel(0);
//					}
//					else
//						mainForm->myForceForm->EnableFsPanel(2);
//				}
//				else{			//start force spectroscopy command
//					SendFsCmdStart();
//					mainForm->myForceForm->EnableFsPanel(1);
//					DnCount = 0;
//				}
//				break;
//			}
//		}
//	}
//}
//---------------------------------------------------------------------------

void Fs_cmdClass::SendFsCmdStart()
{
	mainForm->LogToFile("Fs_cmdClass::SendFsCmdStart");
	mainForm->myTcpThread->TcpMode = 2;
	mutex->Acquire();
	mainForm->myUdpThread->SetUdpSendData(mainForm->myUdpThread->SendData = myUdpDataSendClass->FsPacket(
											  FsResolution,
											  FsDelay,
											  FsXStart,
											  FsYStart,
											  FsMode,
											  1,
											  1
											  ));
	mainForm->myUdpThread->SetSendDataTrue();
	Sleep(100);
	mutex->Release();
}
//---------------------------------------------------------------------------

void Fs_cmdClass::SendGotoCmdStart()
{
	mainForm->LogToFile("Fs_cmdClass::SendGotoCmdStart");
	mainForm->myTcpThread->TcpMode = 2;
	mutex->Acquire();
	mainForm->myUdpThread->SetUdpSendData(mainForm->myUdpThread->SendData = myUdpDataSendClass->FsPacket(
											  FsResolution,
											  FsDelay,
											  FsXStart,
											  FsYStart,
											  FsMode,
											  0,
											  1
											  ));
	mainForm->myUdpThread->SetSendDataTrue();
	Sleep(100);
	mutex->Release();
}
//---------------------------------------------------------------------------
void Fs_cmdClass::SendFsCmdSotp()
{
	mainForm->LogToFile("Fs_cmdClass::SendFsCmdSotp");
	mainForm->myTcpThread->TcpMode = 2;
    mutex->Acquire();
	;

//	TThread::Synchronize(mainForm->myUdpThread,SendFsPacket);
	mainForm->myUdpThread->SetUdpSendData(mainForm->myUdpThread->SendData = myUdpDataSendClass->FsPacket(
											  FsResolution,
											  FsDelay,
											  FsXStart,
											  FsYStart,
											  FsMode,
											  0,
											  0
											  ));
	mainForm->myUdpThread->SetSendDataTrue();
	Sleep(100);
	mutex->Release();
}
//---------------------------------------------------------------------------

void __fastcall Fs_cmdClass::SendFsPacket()
{
	mainForm->LogToFile("Fs_cmdClass::SendFsPacket");
	mainForm->myUdpThread->SendBytes();
}
//---------------------------------------------------------------------------

//void __fastcall Fs_cmdClass::FtpEndTransferEvent(TObject* Sender, TipwFTPEndTransferEventParams *e)
//{
//	if(UpLoad){
////		mainForm->LogToFile("UpCount = " + IntToStr(UpCount));
//		UpCount++;
//	}
//	if(DnLoad){
//		DnCount++;
////		if(DnCount == 12)
////			mainForm->LogToFile("DnCount = " + IntToStr(DnCount));
//	}
//}
//---------------------------------------------------------------------------

//void __fastcall Fs_cmdClass::StartDownloadFiles()
//{
//	DnLoad = true;
//	UpLoad = false;
//	DnCount = 0;
//
//
//	checkTimerDnLoader->Interval = 20;
//	checkTimerDnLoader->Enabled = true;
//}
//---------------------------------------------------------------------------

//void __fastcall Fs_cmdClass::checkTimerDnloaderEvent(TObject *Sender)
//{
//	if( (ipwFTP->Connected) && (ipwFTP->Idle) ){
//		switch(DnCount){
//			case 0:{
//				FtpDownloader(RemoteFileTopo_Fw, LocalFileTopo_Fw);
//				mainForm->LogToFile("Fs_cmdClass : checkTimerDnloaderEvent : Topo_Fw file downloaded");
//				break;
//			}
//			case 1:{
//				FtpDownloader(RemoteFileTb_Fw, LocalFileTb_Fw);
//				mainForm->LogToFile("Fs_cmdClass : checkTimerDnloaderEvent : Tb_Fw file downloaded");
//				break;
//			}
//			case 2:{
//				FtpDownloader(RemoteFileLr_Fw, LocalFileLr_Fw);
//				mainForm->LogToFile("Fs_cmdClass : checkTimerDnloaderEvent : Lr_Fw file downloaded");
//				break;
//			}
//			case 3:{
//				FtpDownloader(RemoteFileAmp_Fw, LocalFileAmp_Fw);
//				mainForm->LogToFile("Fs_cmdClass : checkTimerDnloaderEvent : Amp_Fw file downloaded");
//				break;
//			}
//			case 4:{
//				FtpDownloader(RemoteFilePhase_Fw, LocalFilePhase_Fw);
//				mainForm->LogToFile("Fs_cmdClass : checkTimerDnloaderEvent : Phase_Fw file downloaded");
//				break;
//			}
//			case 5:{
//				FtpDownloader(RemoteFileCmAfm_Fw, LocalFileCmAfm_Fw);
//				mainForm->LogToFile("Fs_cmdClass : checkTimerDnloaderEvent : CmAfm_Fw file downloaded");
//				break;
//			}
//			case 6:{
//				FtpDownloader(RemoteFileTopo_Bw, LocalFileTopo_Bw);
//				mainForm->LogToFile("Fs_cmdClass : checkTimerDnloaderEvent : Topo_Bw file downloaded");
//				break;
//			}
//			case 7:{
//				FtpDownloader(RemoteFileTb_Bw, LocalFileTb_Bw);
//				mainForm->LogToFile("Fs_cmdClass : checkTimerDnloaderEvent : Tb_Bw file downloaded");
//				break;
//			}
//			case 8:{
//				FtpDownloader(RemoteFileLr_Bw, LocalFileLr_Bw);
//				mainForm->LogToFile("Fs_cmdClass : checkTimerDnloaderEvent : Lr_Bw file downloaded");
//				break;
//			}
//			case 9:{
//				FtpDownloader(RemoteFileAmp_Bw, LocalFileAmp_Bw);
//				mainForm->LogToFile("Fs_cmdClass : checkTimerDnloaderEvent : Amp_Bw file downloaded");
//				break;
//			}
//			case 10:{
//				FtpDownloader(RemoteFilePhase_Bw, LocalFilePhase_Bw);
//				mainForm->LogToFile("Fs_cmdClass : checkTimerDnloaderEvent : Phase_Bw file downloaded");
//				break;
//			}
//			case 11:{
//				FtpDownloader(RemoteFileCmAfm_Bw, LocalFileCmAfm_Bw);
//				mainForm->LogToFile("Fs_cmdClass : checkTimerDnloaderEvent : CmAfm_Bw file downloaded");
//				break;
//			}
//			default:{
//				mainForm->LogToFile("Fs_cmdClass : checkTimerDnloaderEvent : finish file downloaded");
//				OffFs();
//				mainForm->myTcpThread->CurrentFsResolution = FsResolution;
//				mainForm->myTcpThread->FsChartsTimer->Interval = 20;
//				mainForm->myTcpThread->FsChartsTimer->Enabled = true;
//				break;
//			}
//		}
//	}
//}
//---------------------------------------------------------------------------

//void Fs_cmdClass::FtpDownloader(UnicodeString RemoteFileName, UnicodeString LocalFileName)
//{
//	if( (ipwFTP->Connected) && (ipwFTP->Idle) ){
//		ipwFTP->RemoteFile = RemoteFileName;
//		ipwFTP->LocalFile = LocalFileName;
//
//
////		mainForm->LogToFile("RemoteFile = " + ipwFTP->RemoteFile);
//		try{
//
//			ipwFTP->Download();
//		}
//		catch(Exception &exception){
//			mainForm->LogToFile(exception.Message);
//		}
//	}
//}
//---------------------------------------------------------------------------

void __fastcall Fs_cmdClass::OffFs()
{
	mainForm->LogToFile("Fs_cmdClass::OffFs");
//	FtpLogOff();
//	ipwFTP->Connected = false;
//	mainForm->LogToFile("force ftp log off");

//	checkTimerDnLoader->Enabled = false;
//	DnLoad = false;
//	DnLoad = 0;

//	UpLoad = false;
//	UpCount = 0;


	mainForm->LogToFile("Fs_cmdClass : OffFs : stop force spectroscopy");
	SendFsCmdSotp();

//	mainForm->Forcing = false;
//	mainForm->GetSecure();
}
//---------------------------------------------------------------------------


