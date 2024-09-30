//---------------------------------------------------------------------------
#include <vcl.h>
#include <System.hpp>
#include <Vcl.ActnCtrls.hpp>

#pragma hdrstop
#include "mainUnit.h"
#include "defines.h"
#include "globals.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "ipwudpport"
#pragma link "ipwipport"
#pragma link "ipwipport"
#pragma link "ipwipinfo"
#pragma link "VCLTee.TeeEdit"
#pragma link "oscClass"
#pragma link "VCLTee.TeeSurfa"
#pragma link "VCLTee.TeeComma"
#pragma link "ipwftp"
#pragma link "ipwftp"
#pragma link "AdvGroupBox"
#pragma link "AdvBadge"
#pragma link "AdvEdit"
#pragma link "AdvWiiProgressBar"
#pragma link "AdvPanel"
#pragma link "AdvSmoothPanel"
#pragma link "CalcEdit"
#pragma link "DBAdvEd"
#pragma link "AdvGlassButton"
#pragma link "CurvyControls"
#pragma link "htmlbtns"
#pragma resource "*.dfm"
TmainForm *mainForm;
//---------------------------------------------------------------------------
__fastcall TmainForm::TmainForm(TComponent* Owner)
: TForm(Owner)
{
	// version 01.00
	SoftwareVersion.major1 = 0;
	SoftwareVersion.major2 = 1;
	SoftwareVersion.minor1 = 0;
	SoftwareVersion.minor2 = 0;

//	HaveLicense = true;
	StartLogger();

	HardwareTable.LogToFile = true;

	myUniKey = new UniKeyClass;
	hid = myUniKey->FindDongle();
	myUniKey->OpenDongle();
	sid = myUniKey->ReadSoftID();
	Mode = myUniKey->ReadDongle();

	if((SoftwareVersion.major1 == myUniKey->DongleVersion.major1) &&
	   (SoftwareVersion.major2 == myUniKey->DongleVersion.major2) &&
	   (SoftwareVersion.minor1 == myUniKey->DongleVersion.minor1) &&
	   (SoftwareVersion.minor2 == myUniKey->DongleVersion.minor2))
		VersionTrue = true;
	else
		VersionTrue = false;


	mainForm->LogToFile("#########################################################");
	mainForm->LogToFile("###################START APPLICATION#####################");
	mainForm->LogToFile("#########################################################");
	mainForm->LogToFile("mainForm : TmainForm");

	MainPath = GetCurrentDir();
	LogToFile("main dir = " + MainPath);

	UploadPath = MainPath + "/" + "uploads";
	DownloadPath = MainPath + "/" + "downloads";
	if( !DirectoryExists(UploadPath) ){
		AnsiString dir = UploadPath;
		CreateDirectoryA(dir.c_str(),NULL);
	}

	if( !DirectoryExists(DownloadPath) ){
		AnsiString dir = DownloadPath;
		CreateDirectoryA(dir.c_str(),NULL);
	}

	DataBasePath = MainPath + "/Resources" + "/Images" + "/PNL_Form" + "/brk.dll";

    myDataBase = new DataBaseClass;
	myDataBase->CreateObjects();

	if(!FileExists(DataBasePath)){
		LogToFile("TmainForm :: DataBase Created");
		CreateFile2(DataBasePath.c_str(),(GENERIC_READ | GENERIC_WRITE),(FILE_SHARE_READ | FILE_SHARE_WRITE),CREATE_ALWAYS,NULL);
	}


	myDataBase->Connect();
	myDataBase->CreateTables();

	myDataBase->SelectExecute(myDataBase->myQuery->Select("License"),"License");
	myDataBase->SelectExecute(myDataBase->myQuery->Select("INFO_CONFIG"),"INFO_CONFIG");
	myDataBase->SelectExecute(myDataBase->myQuery->Select("APPLICATION_CONFIG"),"APPLICATION_CONFIG");
	myDataBase->SelectExecute(myDataBase->myQuery->Select("UDP_CONFIG"),"UDP_CONFIG");
	myDataBase->SelectExecute(myDataBase->myQuery->Select("TCP_CONFIG"),"TCP_CONFIG");
	myDataBase->SelectExecute(myDataBase->myQuery->Select("OSC_CHART_CONFIG"),"OSC_CHART_CONFIG");
	for(int i=0; i<27; i++){
		myDataBase->SelectExecute(myDataBase->myQuery->Select("OSC_CONFIG" , i),"OSC_CONFIG" , i);
	}

	myDataBase->SelectExecute(myDataBase->myQuery->Select("APPROACH_CONFIG"),"APPROACH_CONFIG");
	myDataBase->SelectExecute(myDataBase->myQuery->Select("FAST_APPROACH_DNC_CONFIG"),"FAST_APPROACH_DNC_CONFIG");
	myDataBase->SelectExecute(myDataBase->myQuery->Select("COARSEMOVE_CONFIG"),"COARSEMOVE_CONFIG");
	myDataBase->SelectExecute(myDataBase->myQuery->Select("RETRACT_CONFIG"),"RETRACT_CONFIG");
	myDataBase->SelectExecute(myDataBase->myQuery->Select("STAGE_CONFIG"),"STAGE_CONFIG");
	myDataBase->SelectExecute(myDataBase->myQuery->Select("DNC_CONFIG"),"DNC_CONFIG");
	myDataBase->SelectExecute(myDataBase->myQuery->Select("SCAN_CONFIG"),"SCAN_CONFIG");
	myDataBase->SelectExecute(myDataBase->myQuery->Select("LITHO_CONFIG"),"LITHO_CONFIG");
	myDataBase->SelectExecute(myDataBase->myQuery->Select("FORCE_CONFIG"),"FORCE_CONFIG");
	myDataBase->SelectExecute(myDataBase->myQuery->Select("KPFM_CONFIG"),"KPFM_CONFIG");
	myDataBase->SelectExecute(myDataBase->myQuery->Select("PARAMETERS"),"PARAMETERS");
	myDataBase->SelectExecute(myDataBase->myQuery->Select("HARDWARE_TYPE"),"HARDWARE_TYPE");

    LogToFile("OscChartTable.all_scale = " + BoolToStr(OscChartTable.all_scale,true));

	if(HaveLicense && ResetLicense){

		LicTable.TotalTime = LicenseTime * 3600 ;
		LicTable.WorkedTime = 0;
		LicTable.RemainedTime = LicenseTime * 3600 ;
		myDataBase->Execute("UPDATE License SET (id,TotalTime,WorkedTime,RemainedTime) = (1," + IntToStr(LicenseTime * 3600 )+",0," + IntToStr(LicenseTime * 3600 ) + ") WHERE ID = 1;");
        myUniKey->WriteResetLicence();
	}

	myUniKey->LogOff();
	myDataBase->Disconnect();


	mainForm->LogToFile("uploads dir = " + UploadPath);
	mainForm->LogToFile("downloads dir = " + DownloadPath);
	Confige();
//		LogToFile(IntToStr(i) + " : X_Range = " + FloatToStr(X_Range[i]) + " , Y_Range = " + FloatToStr(Y_Range[i]));


//	for(int i=0 ; i<Max_Range+1 ; i++){
//		if(i <= 10){
//			X_Range[i] = ColibrationTable[i].X_Range;
//			Y_Range[i] = ColibrationTable[i].Y_Range;
//		}
//		else{
//			if(i%2 == 0){
//
//			}
//			else{
//			   double x1 = ColibrationTable[i-1].X_Range;
//			   double x2 = ColibrationTable[i+1].X_Range;
//			   double y1 = ColibrationTable[i-1].Y_Range;
//			   double y2 = ColibrationTable[i+1].Y_Range;
//
//			   X_Range[i] = (x1 + x2)/2;
//			   Y_Range[i] = (y1 + y2)/2;
//			}
//		}
//	}

}
//---------------------------------------------------------------------------
void TmainForm::Confige(){
    Scanner_Type = HardwareTable.HardWare_Scanner_Type;
	Max_Range = HardwareTable.Max_Range;
	AllScale =  OscChartTable.all_scale;


	for(int i=0; i<56; i++){
		myDataBase->SelectExecute(myDataBase->myQuery->Select("Calibration" , i),"Calibration" , i);
	}

	int j=0;
	for(int i=0; i<Max_Range+1; i++){
		if (i<11){
			X_Range[i] = ColibrationTable[i].X_Range;
			Y_Range[i] = ColibrationTable[i].Y_Range;
		}
		else{
			if(i%2 == 0){
				X_Range[i] =  ColibrationTable[i - j].X_Range;
				Y_Range[i] =  ColibrationTable[i - j].Y_Range;
			}
			else{
				X_Range[i] = avg(ColibrationTable[i-j].X_Range, ColibrationTable[i-j-1].X_Range);
				Y_Range[i] = avg(ColibrationTable[i-j].Y_Range, ColibrationTable[i-j-1].Y_Range);
				j++;
			}
		}

	}
}
//---------------------------------------------------------------------------

double TmainForm::avg(double a, double b)
{
	return (a + b) / (double)2;
}
//---------------------------------------------------------------------------

void TmainForm::StartLogger()
{
	myLoggerThread = new LoggerThread(true);
	myLoggerThread->Priority = tpNormal;
	myLoggerThread->FreeOnTerminate = true;
	myLoggerThread->thread_started = true;
	myLoggerThread->Start();
}
//---------------------------------------------------------------------------

void __fastcall TmainForm::FormCreate(TObject *Sender)
{
	this->Hide();


//	while(!myLoggerThread->started)
//		Application->ProcessMessages();

//	myLoggerThread->enqueue("mainForm : FormCreate : start application");
	mainForm->LogToFile("mainForm : FormCreate");
	firstchart = false;

	myUdpThread = NULL;
	myTcpThread = NULL;
	myImagerThread = NULL;
	myCommandCreatorThread = NULL;
	myCrossForm = NULL;
	myOscForm = NULL;
	myVideoForm = NULL;
	myImageFrom = NULL;
	myMainControlPanelForm = NULL;
	myControlPanelForm = NULL;
	myScanPanelForm = NULL;
	myApproachPanelForm = NULL;
	myDynamicCurvePanelForm = NULL;
	myMovingPanelForm = NULL;
	myPiezoFrom = NULL;
	myLithoFrm = NULL;

	//panels
	crscht_pnl->Caption = "";
	crslbl_pnl->Caption = "";
	vid_pnl->Caption = "";
	img_pnl->Caption = "";
	bot_pnl->Caption = "";
	ptz_sub_pnl->Caption = "";
	osc_sub_pnl->Caption = "";
	ctrl_pnl->Caption = "";
	ext_pnl->Caption = "";

	CurrentPicFolderName = "";

	this->Caption = "BRISK";
	MainRect = Screen->PrimaryMonitor->BoundsRect;
	this->SetBounds(0,0,MainRect.Width(),MainRect.Height());
	ext_pnl->Hide();
    crslbl_pnl_zoom->Hide();

	Approaching = false;
	Approached = false;
	Scaning = false;
	AppMode = -1;
	Forcing = false;
	CameraMoving = false;
	StageMoving = false;


	CreatePanels();
	ShowSplash();
	ShowOsc();
	ShowPiezo();

	ChartTimer = new TTimer(NULL);
	ChartTimer->OnTimer = ChartTimerTimer;
	ChartTimer->Enabled = false;
	ChartTimer->Interval = 1;


}
//---------------------------------------------------------------------------

void TmainForm::ShowSplash()
{
//	mySplashForm = new TSplashForm(this);
	LogToFile("mainForm : ShowSplash");
	Application->CreateForm(__classid(TSplashForm), &SplashForm);
	SplashForm->SetMainSize(480,270);
	SplashForm->SetMainGeo(MainRect.Height()/2 - SplashForm->Height/2, MainRect.Width()/2 - SplashForm->Width/2);
	SplashForm->SetOtherGeo();
	SplashForm->Show();
}
//---------------------------------------------------------------------------

__fastcall TmainForm::~TmainForm()
{
	Application->Terminate();
}

//---------------------------------------------------------------------------
void TmainForm::ShowAfrerSpalsh()
{
	RunApplication();
}

//---------------------------------------------------------------------------

void TmainForm::RunApplication()
{
	LogToFile("mainForm : RunApplication");

	data_queue = new queueClassUdp[27];
	img_queue = new queueClassTcp;
	dnc_queue = new queueClassTcpDnc;

	RunCommanderThread();
	ShowImageBox();
	ShowControlPanel();

	ShowCamera();
	RunOsc();
	RunUdpThread();
	RunTCPThread();
}
//---------------------------------------------------------------------------

void TmainForm::RunUdpThread()
{
	LogToFile("mainForm : RunUdpThread");
	myUdpThread = new UdpThread(true);
	myUdpThread->Priority = tpNormal;
	myUdpThread->FreeOnTerminate = true;
	myUdpThread->Start();
}
//---------------------------------------------------------------------------

void TmainForm::ShowOsc()
{
	LogToFile("mainForm : ShowOsc");
	myCrossForm = new TCrossForm(this);
//	Application->CreateForm(__classid(TCrossForm), &CrossForm);
	myCrossForm->Parent = crscht_pnl;
	myCrossForm->SetParentComponent(crscht_pnl);
	myCrossForm->Show();

	myOscForm = new ToscForm(this);
//	Application->CreateForm(__classid(ToscForm), &oscForm);
	myOscForm->Parent = osc_sub_pnl;
	myOscForm->SetParentComponent(osc_sub_pnl);
	myOscForm->Show();
}
//---------------------------------------------------------------------------

void TmainForm::CreatePanels()
{
	//Full Screen
//	ExitAdvWiiProgressBar->Width = ExitAdvWiiProgressBar->Width*3;
//	ExitAdvWiiProgressBar->Height = ExitAdvWiiProgressBar->Height*3;

	LogToFile("mainForm : CreatePanels");

	ext_pnl->Width = ExitAdvWiiProgressBar->Width*3;
	ext_pnl->Height = ExitAdvWiiProgressBar->Height*3;



	ext_pnl->Width = ext_pnl->Width * 4;
	mainForm->ext_pnl->Height = ext_pnl->Height * 4;

	ExitAdvWiiProgressBar->Width = ext_pnl->Width/4;
	ExitAdvWiiProgressBar->Height = ext_pnl->Height/4;

	ExitAdvWiiProgressBar->Left = ext_pnl->Width/2 - ExitAdvWiiProgressBar->Width/2;
	ExitAdvWiiProgressBar->Top = ext_pnl->Height/2 - ExitAdvWiiProgressBar->Height/2;
	ext_pnl->Left = MainRect.Width()/2 - ext_pnl->Width/2;
	ext_pnl->Top = MainRect.Height()/2 - ext_pnl->Height/2;



	//oscc panel albuttom
	bot_pnl->Width = (MainRect.Width()/4)*3;
	bot_pnl->Height = (MainRect.Height()/5)*2;
	osc_sub_pnl->Width = bot_pnl->Width * 19 / 20;
	ptz_sub_pnl->Width =  bot_pnl->Width - osc_sub_pnl->Width;


	int length =  this->Height - bot_pnl->Height;

	//Image panel
	img_pnl->Top = 0;
	img_pnl->Height = length;
	img_pnl->Width = length;
	img_pnl->Left = MainRect.Width() - img_pnl->Width;

	//video pannel
	vid_pnl->Top = 0;
	vid_pnl->Height = length;
	vid_pnl->Width = length;
	vid_pnl->Left = img_pnl->Left - vid_pnl->Width;

	//control pannel
	ctrl_pnl->Top = 0;
	ctrl_pnl->Left = 0;
	ctrl_pnl->Width = this->Width - (img_pnl->Width + vid_pnl->Width);
	ctrl_pnl->Height = img_pnl->Height;


	//cross hair panel
	crscht_pnl->Height = (MainRect.Width()/15);
	crscht_pnl->Width = crscht_pnl->Height;
	crscht_pnl->Top = vid_pnl->Height - crscht_pnl->Height - 10;
	crscht_pnl->Left = ctrl_pnl->Width + vid_pnl->Width - crscht_pnl->Width - 20;


	Label1->Height = 25;
	Label2->Height = 25;
	Label3->Height = 25;

	Label1->Width = 200;
	Label2->Width = 200;
	Label3->Width = 200;



    crslbl_pnl->Height = 90;
	crslbl_pnl->Width = 250;
	crslbl_pnl->Top = vid_pnl->Height - crslbl_pnl->Height - 10;
	crslbl_pnl->Left = ctrl_pnl->Width + 20;

	Label3->Left =  5;
	Label3->Width = 170;
	Label3->Top =  3;

	Label2->Left = 5;
	Label2->Width = 170;
	Label2->Top = 33;

	Label1->Left = 5;
	Label1->Width = 170;
	Label1->Top = 63;


	crslbl_pnl_zoom->Height = img_pnl->Height / 3;
	crslbl_pnl_zoom->Width = img_pnl->Width - 140;
	crslbl_pnl_zoom->Top = img_pnl->Height - crslbl_pnl_zoom->Height - 50;
	crslbl_pnl_zoom->Left = img_pnl->Left + 20;

	Label5->Left =  5;
	Label5->Height = 66;
	Label5->Width = crslbl_pnl_zoom->Width - 10;
	Label5->Top =  3;

	Label6->Left = 5;
	Label6->Height = 66;
	Label6->Width = crslbl_pnl_zoom->Width - 10;
	Label6->Top = crslbl_pnl_zoom->Height / 2 - 33;

	Label7->Left = 5;
	Label7->Height = 66;
	Label7->Width = crslbl_pnl_zoom->Width - 10;
	Label7->Top = crslbl_pnl_zoom->Height - 70;




	Gain1->Left = 185;
	Gain1->Top = 63;

	Gain10->Left = 185;
	Gain10->Top = 33;

	Gain100->Left = 185;
	Gain100->Top = 3;

//	Panel1->Left = Label3->Left + Label3->Width + 10;
//	Panel1->Top = Label3->Top;
}
//---------------------------------------------------------------------------

void TmainForm::RunOsc()
{
	LogToFile("mainform : RunOsc");
	myOscForm->CrossTimer->Enabled = true;
	myOscForm->RunChart(true);
	myOscForm->RecordTimer->Enabled = false;
}
//---------------------------------------------------------------------------

void TmainForm::RunMainChart()
{
	myOscForm->AdvUpDownEdit1ClickAdd(NULL);
}
//---------------------------------------------------------------------------

void TmainForm::ShowCamera()
{
	LogToFile("mainForm : ShowCamera");
	myVideoForm = new TVidForm(this);
//	Application->CreateForm(__classid(TVidForm), &VidForm);
	myVideoForm->Parent = vid_pnl;
	myVideoForm->SetParentComponent(vid_pnl);
	myVideoForm->Show();
}
//---------------------------------------------------------------------------


void TmainForm::ShowImageBox()
{
	LogToFile("mainForm : ShowImageBox");
	myImageFrom = new TImgForm(this);
//	Application->CreateForm(__classid(TImgForm), &ImgForm);
	myImageFrom->Parent = img_pnl;
	myImageFrom->SetParentComponent(img_pnl);
	myImageFrom->Show();
}
//---------------------------------------------------------------------------

void TmainForm::RunTCPThread()
{
	LogToFile("mainForm : RunTCPThread");
	myTcpThread = new TcpThread(true);
	myTcpThread->Priority = tpNormal;
	myTcpThread->FreeOnTerminate = true;
	myTcpThread->Start();
}
//---------------------------------------------------------------------------

void TmainForm::RunImagerThread()
{
	myImagerThread = NULL;
	LogToFile("TmainForm::RunImagerThread");
//	myImagerThread = NULL;
	myImagerThread = new ImagerThread(true);
	myImagerThread->Priority = tpNormal;
	myImagerThread->FreeOnTerminate = true;
	myImagerThread->Start();
}
//---------------------------------------------------------------------------

void TmainForm::ShowControlPanel()
{
	LogToFile("mainForm : ShowControlPanel");
	myMainControlPanelForm = new TCtrlForm(this);
//	Application->CreateForm(__classid(TCtrlForm), &CtrlForm);
	myMainControlPanelForm->Parent = ctrl_pnl;
	myMainControlPanelForm->SetParentComponent(ctrl_pnl);
//	myMainControlPanelForm->Show();

	myControlPanelForm = new  TControlPanelForm(this)  ;
//	Application->CreateForm(__classid(TControlPanelForm), &ControlPanelForm);
	myControlPanelForm->Parent = myMainControlPanelForm->MainPanel;
	myControlPanelForm->SetParentComponent(myMainControlPanelForm->MainPanel);
//	myControlPanelForm->Show();

	myScanPanelForm = new  TScanPanelForm(this);
//	Application->CreateForm(__classid(TScanPanelForm), &ScanPanelForm);
	myScanPanelForm->Parent = myMainControlPanelForm->MainPanel;
	myScanPanelForm->SetParentComponent(myMainControlPanelForm->MainPanel);


	myApproachPanelForm = new TApproachPanelForm(this);
//	Application->CreateForm(__classid(TApproachPanelForm), &ApproachPanelForm);
	myApproachPanelForm->Parent = myMainControlPanelForm->MainPanel;
	myApproachPanelForm->SetParentComponent(myMainControlPanelForm->MainPanel);

	myDynamicCurvePanelForm = new TDynamicCurveForm(this);
//	Application->CreateForm(__classid(TDynamicCurveForm), &DynamicCurveForm);
	myDynamicCurvePanelForm->Parent = myMainControlPanelForm->MainPanel;
	myDynamicCurvePanelForm->SetParentComponent(myMainControlPanelForm->MainPanel);

	myMovingPanelForm = new TMvFrm(this) ;
//	Application->CreateForm(__classid(TMvFrm), &MvFrm);
	myMovingPanelForm->Parent = myMainControlPanelForm->MainPanel;
	myMovingPanelForm->SetParentComponent(myMainControlPanelForm->MainPanel);

	myForceForm = new TForceFrm(this);
//	Application->CreateForm(__classid(TForceFrm), &ForceFrm);
	myForceForm->Parent = myMainControlPanelForm->MainPanel;
	myForceForm->SetParentComponent(myMainControlPanelForm->MainPanel);


	mySettingForm = new TSettingFrm(this);
//	Application->CreateForm(__classid(TSettingFrm), &SettingFrm);
	mySettingForm->Parent = myMainControlPanelForm->MainPanel;
	mySettingForm->SetParentComponent(myMainControlPanelForm->MainPanel);

	myLithoFrm = new TLithoFrm(this);
//	Application->CreateForm(__classid(TSettingFrm), &SettingFrm);
	myLithoFrm->Parent = myMainControlPanelForm->MainPanel;
	myLithoFrm->SetParentComponent(myMainControlPanelForm->MainPanel);


	GalFrm = new TGalleyForm(this);
//	Application->CreateForm(__classid(TGalleyForm), &GalFrm);
	GalFrm->Parent = myMainControlPanelForm->MainPanel;
	GalFrm->SetParentComponent(myMainControlPanelForm->MainPanel);

	myKpfmFrm = new TKpfmFrm(this);
//	Application->CreateForm(__classid(TGalleyForm), &KpfmFrm);
	myKpfmFrm->Parent = myMainControlPanelForm->MainPanel;
	myKpfmFrm->SetParentComponent(myMainControlPanelForm->MainPanel);
}
//---------------------------------------------------------------------------

void TmainForm::RunCommanderThread()
{
	LogToFile("mainForm : RunCommanderThread");
	myCommandCreatorThread = new CommandCreatorThread(true);
	myCommandCreatorThread->Priority = tpNormal;
	myCommandCreatorThread->FreeOnTerminate = true;
	myCommandCreatorThread->Start();
}
//---------------------------------------------------------------------------


void __fastcall TmainForm::FormCloseQuery(TObject *Sender, bool &CanClose)
{
	CanClose = false;
//	this->myOscForm->pOffButClick(NULL);
}
//---------------------------------------------------------------------------



void __fastcall TmainForm::ChartTimerTimer(TObject *Sender)
{
	LogToFile("mainForm : ChartTimerTimer : connect to brisk hardware");
	ChartTimer->Enabled = false;

	myOscForm->LoadOscConfig();
	ChartTimer2->Enabled = true;
}
//---------------------------------------------------------------------------

void TmainForm::ExitApp()
{
	SplashForm->Close();
}
//---------------------------------------------------------------------------

void __fastcall TmainForm::FormDestroy(TObject *Sender)
{
	Application->Terminate();
}
//---------------------------------------------------------------------------

void TmainForm::LogToFile(AnsiString Message)
{
//	Message = "Debug Brisk - " + TDateTime::CurrentDateTime().FormatString("yyyymmdd-hh:MM:ss.zzz") + " - " + Message;
	if(HardwareTable.LogToFile)
		myLoggerThread->enqueue(Message);
	else
		OutputDebugStringA(Message.c_str());
}
//---------------------------------------------------------------------------

void __fastcall TmainForm::ChartTimer2Timer(TObject *Sender)
{
	mainForm->LogToFile("mainForm : ChartTimer2Timer : start all");
	ChartTimer2->Enabled = false;
	this->Show();

    SplashForm->Visible = false;
	SplashForm->Hide();


	myMainControlPanelForm->Show();

	mainForm->myVideoForm->LeftButton->BringToFront();
	mainForm->myVideoForm->RightButton->BringToFront();
	mainForm->myVideoForm->FrontButton->BringToFront();
	mainForm->myVideoForm->BackButton->BringToFront();
	mainForm->myVideoForm->SetButton->BringToFront();
	mainForm->myVideoForm->ShotButton->BringToFront();

	mainForm->myCrossForm->transparent = true;

}
//---------------------------------------------------------------------------

void TmainForm::ShowPiezo()
{
	mainForm->LogToFile("mainForm :ShowPiezo");
	myPiezoFrom = new TPiezoFrm(this) ;
//    Application->CreateForm(__classid(TPiezoFrm), &PiezoFrm);
	myPiezoFrom->Parent = ptz_sub_pnl;
	myPiezoFrom->SetParentComponent(ptz_sub_pnl);
	ptz_sub_pnl->Enabled = false;
	myPiezoFrom->Show();
}//---------------------------------------------------------------------------void TmainForm::CreateLoger(){}//---------------------------------------------------------------------------int TmainForm::GetSecure(){	if(!myUdpThread->ConnectionState){		if(Approaching){//			LogToFile("mainForm : GetSecure : Approaching....");			myVideoForm->BackButton->Enabled = false;			myVideoForm->RightButton->Enabled = false;			myVideoForm->FrontButton->Enabled = false;			myVideoForm->LeftButton->Enabled = false;			myControlPanelForm->ApproachPanel->Enabled = true;
			myControlPanelForm->ScanPanel->Enabled = false;
			myControlPanelForm->RetractPanel->Enabled = false;
			myScanPanelForm->Enabled = false;
			myDynamicCurvePanelForm->Enabled = false;;
			myMovingPanelForm->StagePanel->Enabled = false;
			myMovingPanelForm->CoarsePanel->Enabled = false;
			myForceForm->Enabled = false;
			myLithoFrm->Enabled = false;
			myKpfmFrm->Enabled = false;            mySettingForm->Enabled = false;			return 1;		}		else if(Scaning){//			LogToFile("mainForm : GetSecure : Scaning....");						myVideoForm->BackButton->Enabled = false;			myVideoForm->RightButton->Enabled = false;			myVideoForm->FrontButton->Enabled = false;			myVideoForm->LeftButton->Enabled = false;			if(Approached){
//				LogToFile("mainForm : GetSecure :scaning approched");				myControlPanelForm->ApproachPanel->Enabled = true;			}
			else{
//				LogToFile("mainForm : GetSecure :scaning !approched");
				myControlPanelForm->ApproachPanel->Enabled = false;
			}
			myControlPanelForm->ScanPanel->Enabled = true;
			myControlPanelForm->RetractPanel->Enabled = false;
			myScanPanelForm->Enabled = false;
			myApproachPanelForm->Enabled = false;
			myDynamicCurvePanelForm->Enabled = false;;
			myMovingPanelForm->StagePanel->Enabled = false;
			myMovingPanelForm->CoarsePanel->Enabled = false;
			myForceForm->Enabled = false;
			myLithoFrm->Enabled = false;
			myKpfmFrm->Enabled = false;			mySettingForm->Enabled = false;			return 2;		}		else if(StageMoving){//			LogToFile("mainForm : GetSecure : StageMoving....");			myVideoForm->BackButton->Enabled = false;			myVideoForm->RightButton->Enabled = false;			myVideoForm->FrontButton->Enabled = false;			myVideoForm->LeftButton->Enabled = false;			myControlPanelForm->ApproachPanel->Enabled = false;			myControlPanelForm->ScanPanel->Enabled = false;
			myControlPanelForm->RetractPanel->Enabled = true;
			myScanPanelForm->Enabled = false;
			myApproachPanelForm->Enabled = false;
			myDynamicCurvePanelForm->Enabled = false;;
			myMovingPanelForm->StagePanel->Enabled = false;
			myMovingPanelForm->CoarsePanel->Enabled = true;
			myForceForm->Enabled = false;
			myLithoFrm->Enabled = false;
			myKpfmFrm->Enabled = false;			mySettingForm->Enabled = false;			return 3;		}		else if(CameraMoving){//			LogToFile("mainForm : GetSecure : CameraMoving....");			myVideoForm->BackButton->Enabled = true;			myVideoForm->RightButton->Enabled = true;			myVideoForm->FrontButton->Enabled = true;			myVideoForm->LeftButton->Enabled = true;			myControlPanelForm->ApproachPanel->Enabled = false;
			myControlPanelForm->ScanPanel->Enabled = false;
			myControlPanelForm->RetractPanel->Enabled = false;
			myScanPanelForm->Enabled = false;
			myApproachPanelForm->Enabled = false;
			myDynamicCurvePanelForm->Enabled = false;;
			myMovingPanelForm->StagePanel->Enabled = true;
			myMovingPanelForm->CoarsePanel->Enabled = false;
			myForceForm->Enabled = false;
			myLithoFrm->Enabled = false;
			myKpfmFrm->Enabled = false;			mySettingForm->Enabled = false;			return 4;		}		else if(Forcing) {//			LogToFile("mainForm : GetSecure : Forcing....");			myVideoForm->BackButton->Enabled = false;			myVideoForm->RightButton->Enabled = false;			myVideoForm->FrontButton->Enabled = false;			myVideoForm->LeftButton->Enabled = false;			myControlPanelForm->ApproachPanel->Enabled = false;
			myControlPanelForm->ScanPanel->Enabled = false;
			myControlPanelForm->RetractPanel->Enabled = false;
			myScanPanelForm->Enabled = false;
			myApproachPanelForm->Enabled = false;
			myDynamicCurvePanelForm->Enabled = false;;
			myMovingPanelForm->StagePanel->Enabled = false;
			myMovingPanelForm->CoarsePanel->Enabled = false;
			myForceForm->Enabled = true;
			myLithoFrm->Enabled = false;
			myKpfmFrm->Enabled = false;			mySettingForm->Enabled = false;			return 5;		}		else if(Lithoing){//			LogToFile("mainForm : GetSecure : Lithoing....");			myVideoForm->BackButton->Enabled = false;			myVideoForm->RightButton->Enabled = false;			myVideoForm->FrontButton->Enabled = false;			myVideoForm->LeftButton->Enabled = false;			myControlPanelForm->ApproachPanel->Enabled = false;
			myControlPanelForm->ScanPanel->Enabled = false;
			myControlPanelForm->RetractPanel->Enabled = false;
			myScanPanelForm->Enabled = false;
			myApproachPanelForm->Enabled = false;
			myDynamicCurvePanelForm->Enabled = false;;
			myMovingPanelForm->StagePanel->Enabled = false;
			myMovingPanelForm->CoarsePanel->Enabled = false;
			myForceForm->Enabled = false;
			myLithoFrm->Enabled = true;
			myKpfmFrm->Enabled = false;			mySettingForm->Enabled = false;			return 6;		}		else if(Kpfming){//			LogToFile("mainForm : GetSecure : Kpfming....");			myVideoForm->BackButton->Enabled = false;			myVideoForm->RightButton->Enabled = false;			myVideoForm->FrontButton->Enabled = false;			myVideoForm->LeftButton->Enabled = false;			myControlPanelForm->ApproachPanel->Enabled = false;
			myControlPanelForm->ScanPanel->Enabled = false;
			myControlPanelForm->RetractPanel->Enabled = false;
			myScanPanelForm->Enabled = false;
			myApproachPanelForm->Enabled = false;
			myDynamicCurvePanelForm->Enabled = false;;
			myMovingPanelForm->StagePanel->Enabled = false;
			myMovingPanelForm->CoarsePanel->Enabled = false;
			myForceForm->Enabled = false;
			myLithoFrm->Enabled = false;
			myKpfmFrm->Enabled = true;			mySettingForm->Enabled = false;			return 7;		}		else if(Approached){//			LogToFile("mainForm : GetSecure : Approached....");			myVideoForm->BackButton->Enabled = false;			myVideoForm->RightButton->Enabled = false;			myVideoForm->FrontButton->Enabled = false;			myVideoForm->LeftButton->Enabled = false;			myControlPanelForm->ApproachPanel->Enabled = true;
			myControlPanelForm->ScanPanel->Enabled = true;
			myControlPanelForm->RetractPanel->Enabled = true;
			myScanPanelForm->Enabled = true;
			myDynamicCurvePanelForm->Enabled = false;;
			myMovingPanelForm->StagePanel->Enabled = false;
			myMovingPanelForm->CoarsePanel->Enabled = false;
			myForceForm->Enabled = true;
			myLithoFrm->Enabled = false;
			myKpfmFrm->Enabled = false;			mySettingForm->Enabled = false;			return 8;		}		else {//			LogToFile("mainForm : GetSecure : Free....");			myVideoForm->BackButton->Enabled = true;			myVideoForm->RightButton->Enabled = true;			myVideoForm->FrontButton->Enabled = true;			myVideoForm->LeftButton->Enabled = true;			myControlPanelForm->ApproachPanel->Enabled = true;
			myControlPanelForm->ScanPanel->Enabled = true;
			myControlPanelForm->RetractPanel->Enabled = true;
			myScanPanelForm->Enabled = true;
			myApproachPanelForm->Enabled = true;
			myDynamicCurvePanelForm->Enabled = true;
			myMovingPanelForm->StagePanel->Enabled = true;
			myMovingPanelForm->CoarsePanel->Enabled = true;
			myForceForm->Enabled = true;
			myLithoFrm->Enabled = true;
			myKpfmFrm->Enabled = true;			mySettingForm->Enabled = true;			return 0;		}	}	else{		myMainControlPanelForm->PanelAdvScrollBox->Enabled = false;        myControlPanelForm->ApproachPanel->Enabled = true;		myControlPanelForm->ScanPanel->Enabled = false;
		myControlPanelForm->RetractPanel->Enabled = true;
		mySettingForm->Enabled = false;
		return 9;	}}//---------------------------------------------------------------------------void __fastcall TmainForm::Gain100Click(TObject *Sender){	myCrossForm->Gain = 100;	myCrossForm->GainChainge = true;}//---------------------------------------------------------------------------void __fastcall TmainForm::Gain10Click(TObject *Sender)
{
	myCrossForm->Gain = 1000;
	myCrossForm->GainChainge = true;
}
//---------------------------------------------------------------------------

void __fastcall TmainForm::Gain1Click(TObject *Sender){	myCrossForm->Gain = 10000;	myCrossForm->GainChainge = true;}//---------------------------------------------------------------------------
void __fastcall TmainForm::Label1Click(TObject *Sender){
	crslbl_pnl_zoom->Show();
}
//---------------------------------------------------------------------------
void __fastcall TmainForm::Label2Click(TObject *Sender){
	crslbl_pnl_zoom->Show();
}
//---------------------------------------------------------------------------
void __fastcall TmainForm::Label3Click(TObject *Sender){
	crslbl_pnl_zoom->Show();
}
//---------------------------------------------------------------------------
void __fastcall TmainForm::crslbl_pnlClick(TObject *Sender){
    crslbl_pnl_zoom->Show();
}
//---------------------------------------------------------------------------
