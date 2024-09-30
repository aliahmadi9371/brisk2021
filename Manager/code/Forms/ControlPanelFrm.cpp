//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "ControlPanelFrm.h"
#include "mainUnit.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "AdvBadge"
#pragma link "AdvEdit"
#pragma link "AdvCombo"
#pragma link "AdvGlassButton"
#pragma link "AdvShape"
#pragma link "AdvShapeButton"
#pragma link "AdvGlowButton"
#pragma link "CurvyControls"
#pragma link "htmlbtns"
#pragma link "AdvTrackBar"
#pragma link "DBAdvTrackBar"
#pragma link "AdvPanel"
#pragma resource "*.dfm"
TControlPanelForm *ControlPanelForm;
//---------------------------------------------------------------------------
__fastcall TControlPanelForm::TControlPanelForm(TComponent* Owner)
	: TForm(Owner)
{
	resolution = 0;
	sstart = false;

	approached = false;
	approaching = false;

	RetractStep = 1;

	FarNear = false;
	StatusFarNear = 0;
	fast = false;
	CountFarNear = 0;

	myUdpDataSendClass = NULL;
	myUdpDataSendClass = new UdpDataSendClass(NULL);
	scanning = false;

	RetractPanel->Caption = "";
	PanelOneStep->Caption = "";
//	RetPanel->Caption = "";

	ImageFolderUser = "";
	FolderCreated = false;

	PicFolder = "";
	DateFolder = "";
	TimeFolder = "";

	dnc = false;
	fastfast = true;
	StopFastState = 0;

	scan_selcet = false;
	continuos_select = false;
	approach_selcet = false;
	StWatchStarted = false;
	AgainScan = false;
}
//---------------------------------------------------------------------------

void __fastcall TControlPanelForm::FormCreate(TObject *Sender)
{
	this->Hide();

	ScanPic = new TGDIPPicture;
	ScanPic->LoadFromFile(MainPath + "/Resources/Images/CTRL_Form/scan.png");

	ScanPicHover = new TGDIPPicture;
	ScanPicHover->LoadFromFile(MainPath + "/Resources/Images/CTRL_Form/scan_hover.png");

	ContinuousPic = new TGDIPPicture;
	ContinuousPic->LoadFromFile(MainPath + "/Resources/Images/CTRL_Form/continuous.png");

	ContinuousPicHover = new TGDIPPicture;
	ContinuousPicHover->LoadFromFile(MainPath + "/Resources/Images/CTRL_Form/continuous_hover.png");


	ApproachPic = new TGDIPPicture;
	ApproachPic->LoadFromFile(MainPath + "/Resources/Images/CTRL_Form/approach.png");

	ApproachPicHover = new TGDIPPicture;
	ApproachPicHover->LoadFromFile(MainPath + "/Resources/Images/CTRL_Form/approach_hover.png");

    StWatch = new TStopwatch;



}
//---------------------------------------------------------------------------

void __fastcall TControlPanelForm::FormShow(TObject *Sender)
{
	if(!sstart){

		EnableApproachPanel(1);
		EnableScanPanel(0);
		EnableOneStep(false);


		int width = mainForm->myMainControlPanelForm->MainPanel->Width;
		int height = mainForm->myMainControlPanelForm->MainPanel->Height;

		//retract
		RetractPanel->Height = height/2;
		RetractPanel->Top = height/2;

		//approach
		ApproachPanel->Left = 0;
		ApproachPanel->Top = 0;
		ApproachPanel->Width = width/2;
		ApproachPanel->Height = RetractPanel->Height - RetractPanel->Height;

		//scan
		ScanPanel->Left = this->Width - ApproachPanel->Width ;
		ScanPanel->Top = 0;
		ScanPanel->Width = width - ApproachPanel->Width;
		ScanPanel->Height = ApproachPanel->Height;

		//sub approach
		PanelSubApproach->Left = ApproachPanel->Width/20;
		PanelSubApproach->Width = ApproachPanel->Width/1.1;
		PanelSubApproach->Height = PanelSubApproach->Width/1.4;
		PanelSubApproach->Top = ApproachPanel->Height/2 - PanelSubApproach->Height/2;

		//sub scan
		PanelSubScan->Left = PanelSubApproach->Left;
		PanelSubScan->Width = PanelSubApproach->Width;
		PanelSubScan->Top = PanelSubApproach->Top;
		PanelSubScan->Height = PanelSubApproach->Height;

		//sub retract
		PanelSubRetract->Left = PanelSubApproach->Left;
		PanelSubRetract->Top = 0;
		PanelSubRetract->Width = RetractPanel->Width - 2 * PanelSubRetract->Left;
		PanelSubRetract->Height = PanelSubApproach->Height;

		//sub retract
		int RetractHeight = PanelSubRetract->Height - PanelLabelRetract->Height;
		int RetractTop = PanelLabelRetract->Height;
		int RetractMid = RetractTop + RetractHeight/2;

		DBAdvGlowButtonRetract->Top = RetractMid -  DBAdvGlowButtonRetract->Height/2;
		DBAdvGlowButtonRetract->Left = (PanelSubRetract->Width/3)/2 - DBAdvGlowButtonRetract->Width/2;
		DBAdvGlowButtonRetract->BringToFront();

		PanelSlider->Width =  (PanelSubRetract->Width/(double)5) * 2;
		PanelSlider->Top =  RetractMid - PanelSlider->Height/2;
		PanelSlider->Left =  DBAdvGlowButtonRetract->Left + 2*DBAdvGlowButtonRetract->Width;

		LabelTen->Left = 15;
		LabelHundred->Left =  PanelSlider->Width/2 - LabelHundred->Width/2;
		LabelThousand->Left = PanelSlider->Width - LabelThousand->Width/2 - 20;
		PanelSlider->BringToFront();

		PanelOneStep->Width = DBAdvGlowButtonRetract->Width*3/(double)2;
		PanelOneStep->Left = PanelSlider->Left + PanelSlider->Width + DBAdvGlowButtonRetract->Width/2;
		PanelOneStep->Height = (DBAdvGlowButtonRetract->Height*3)/(double)2;
		PanelOneStep->Top =  RetractMid - PanelOneStep->Height/(double)2;

		DBAdvGlowButtonDownOneStep->Left = PanelOneStep->Width/(double)2 - DBAdvGlowButtonDownOneStep->Width/(double)2;
		DBAdvGlowButtonDownOneStep->Top = PanelOneStep->Height - DBAdvGlowButtonDownOneStep->Height - 5;

		DBAdvGlowButtonUpOneStep->Left = DBAdvGlowButtonDownOneStep->Left;
		DBAdvGlowButtonUpOneStep->Top = DBAdvGlowButtonDownOneStep->Top - DBAdvGlowButtonUpOneStep->Height - 3;
		PanelOneStep->BringToFront();

		//sub approach
		int ApproachHeight = PanelSubApproach->Height - PanelLabelApproach->Height;
		int ApproachTop = PanelLabelApproach->Height;
//		int ApproachMid = ApproachTop + Height/2;

		ShapeLineApproach->Left = PanelSubApproach->Width/2 - ShapeLineApproach->Width/2;
		ShapeLineApproach->Top = ApproachTop + 10;
		ShapeLineApproach->Height = ApproachHeight - 10;

//		int approch_width = PanelSubApproach->Width - ShapeLineApproach->Left;
		int approch_mid_x_1 = (PanelSubApproach->Width/(double)2)/(double)2;
		int approch_mid_x_2 = PanelSubApproach->Width/(double)2 + approch_mid_x_1;
		int approch_mid_y = ApproachTop + ApproachHeight/2;

		DBAdvGlowButtonApproach->Width = 80;
		DBAdvGlowButtonApproach->Height = 80;
		DBAdvGlowButtonApproach->Left = approch_mid_x_1 - DBAdvGlowButtonApproach->Width/2;
		DBAdvGlowButtonApproach->Top = approch_mid_y - DBAdvGlowButtonApproach->Height/2;
		DBAdvGlowButtonApproach->BringToFront();

		RadioButtonNormal->Left = approch_mid_x_2 - RadioButtonNormal->Width/2;
		RadioButtonFast->Left = RadioButtonNormal->Left;
		RadioButtonPrecise->Left = RadioButtonNormal->Left;

		int h = ApproachHeight/2;

		RadioButtonNormal->Top = ApproachTop + h/2 - RadioButtonNormal->Height/2;
		RadioButtonFast->Top = RadioButtonNormal->Top + h;
		RadioButtonPrecise->Top = RadioButtonFast->Top + h;

		RadioButtonNormal->BringToFront();
		RadioButtonFast->BringToFront();
		RadioButtonPrecise->BringToFront();

		//sub scan
//		int ScanHeight = PanelSubScan->Height - PanelLabelScan->Height;
		int ScanTop = PanelLabelScan->Height;
//		int ScanMid = ScanTop + Height/2;

		DBAdvGlowButtonScan->Width = DBAdvGlowButtonApproach->Width;
		DBAdvGlowButtonScan->Height = DBAdvGlowButtonApproach->Height;
		DBAdvGlowButtonScan->Left = DBAdvGlowButtonApproach->Left;
		DBAdvGlowButtonScan->Top = DBAdvGlowButtonApproach->Top;
		DBAdvGlowButtonScan->BringToFront();

		ShapeLineScan->Left = ShapeLineApproach->Left;
		ShapeLineScan->Top = ShapeLineApproach->Top;
		ShapeLineScan->Height = ShapeLineApproach->Height;

		DBAdvGlowButtonContinuous->Width = DBAdvGlowButtonScan->Width;
		DBAdvGlowButtonContinuous->Height = DBAdvGlowButtonScan->Height;
		DBAdvGlowButtonContinuous->Left = PanelLabelScan->Width/2 + DBAdvGlowButtonApproach->Left;
		DBAdvGlowButtonContinuous->Top = DBAdvGlowButtonScan->Top;
		DBAdvGlowButtonContinuous->BringToFront();

		DBAdvGlowButtonScan->Picture = ScanPic;
		DBAdvGlowButtonContinuous->Picture = ContinuousPic;
		DBAdvGlowButtonApproach->Picture = ApproachPic;

//        mainForm->myApproachPanelForm->SettApproach();
		sstart = true;
	}
}
//---------------------------------------------------------------------------

void __fastcall TControlPanelForm::AdvBadgeButtonStartApproachClick(TObject *Sender)
{
	mainForm->LogToFile("TControlPanelForm::AdvBadgeButtonStartApproachClick");
	StatusFarNear = 0;
	FarNear = false;
	CountFarNear = 0;
	start = true;
	set = false;
	if(mainForm->myApproachPanelForm->fast_checkbox->Checked)
		mode = 0;
	else
		mode = 1;

	if((mainForm->AppMode == 1 || mainForm->AppMode == 5 || mainForm->AppMode == 7) && fast){
		EnableApproachPanel(2);
		FastDncCurve();
		if(!approach_selcet){
			return;
		}
	}
	TThread::Synchronize(mainForm->myCommandCreatorThread,StartStopApproch);
	EnableApproachPanel(2);
}
//---------------------------------------------------------------------------

void __fastcall TControlPanelForm::AdvBadgeButtonStopApprocheClick(TObject *Sender)
{
//	mainForm->LogToFile("stop approach btn");
	mainForm->LogToFile("TControlPanelForm::AdvBadgeButtonStopApprocheClick");
	StatusFarNear = 0;
	FarNear = false;
	CountFarNear = 0;
	start = false;
	set = true;
	if(mainForm->myApproachPanelForm->fast_checkbox->Checked)
		mode = 0;
	else
		mode = 1;

	TThread::Synchronize(mainForm->myCommandCreatorThread,StartStopApproch);

}
//---------------------------------------------------------------------------

void __fastcall TControlPanelForm::StartStopApproch()
{
	mainForm->LogToFile("TControlPanelForm::StartStopApproch");
	mainForm->myCommandCreatorThread->StartApprochClick(mode,start,set,StatusFarNear,FarNear,CountFarNear);
}
//---------------------------------------------------------------------------

void __fastcall TControlPanelForm::AdvBadgeButtonStartScanClick(TObject *Sender)
{
	mainForm->LogToFile("TControlPanelForm::AdvBadgeButtonStartScanClick");
    if(AgainScan){
		mainForm->myCommandCreatorThread->myScan->Continues = true;
//		mainForm->LogToFile("TControlPanelForm::AdvBadgeButtonStartScanClick : AgainScan = true ________________________________________ Continues =  " + BoolToStr(mainForm->myCommandCreatorThread->myScan->Continues,true));
	}
	else{
		mainForm->myCommandCreatorThread->myScan->Continues = false;
//		mainForm->LogToFile("TControlPanelForm::AdvBadgeButtonStartScanClick : AgainScan = false ________________________________________ Continues =  " + BoolToStr(mainForm->myCommandCreatorThread->myScan->Continues,true));
	}
	EnableScanPanel(4);
	Application->ProcessMessages();
	if(!FolderCreated){
		GetFolder();
	}
	SetFolderNames();

//	mainForm->myScanPanelForm->SaveToIni();
//	mainForm->myScanPanelForm->AllEditWhite();
	TThread::Synchronize(mainForm->myCommandCreatorThread,StartScan);
}
//---------------------------------------------------------------------------

void __fastcall TControlPanelForm::AdvBadgeButtonStopScanClick(TObject *Sender)
{
	mainForm->LogToFile("TControlPanelForm::AdvBadgeButtonStopScanClick");
	EnableScanPanel(1);
//    continuos_select = false;
//	DBAdvGlowButtonContinuous->Picture = ContinuousPic;
//	DBAdvGlowButtonContinuous->Font->Color = clWhite;
	DBAdvGlowButtonContinuousClick(NULL);
	TThread::Synchronize(mainForm->myCommandCreatorThread,StopScan);
}
//---------------------------------------------------------------------------

void __fastcall TControlPanelForm::StartScan()
{
	mainForm->LogToFile("TControlPanelForm::StartScan");
	ScanCommand.start = true;
	ScanCommand.set = false;
	ScanCommand.Changer = mainForm->myScanPanelForm->LastScanChanger;
	mainForm->myCommandCreatorThread->scan_command = true;
//	mainForm->myCommandCreatorThread->StartScanClick(true,false,mainForm->myScanPanelForm->LastScanChanger);
}
//---------------------------------------------------------------------------

void __fastcall TControlPanelForm::StopScan()
{
	mainForm->LogToFile("TControlPanelForm::StopScan");
//    mainForm->myScanPanelForm->AllEditWhite();
	ScanCommand.start = false;
	ScanCommand.set = false;
	ScanCommand.Changer = mainForm->myScanPanelForm->LastScanChanger;
	mainForm->myCommandCreatorThread->scan_command = true;
//	mainForm->myCommandCreatorThread->StartScanClick(false,false,mainForm->myScanPanelForm->LastScanChanger);
}
//---------------------------------------------------------------------------

void TControlPanelForm::EnableScanPanel(int enabled)
{
	mainForm->LogToFile("TControlPanelForm::EnableScanPanel , enabled = " + IntToStr(enabled));
	switch(enabled){
		case 0:{
			DBAdvGlowButtonScan->Enabled = true;
			DBAdvGlowButtonScan->Picture = ScanPic;
			DBAdvGlowButtonScan->Font->Color = clWhite;
			DBAdvGlowButtonContinuous->Enabled = true;
			mainForm->myImageFrom->ChartButton->Hide();
			if(mainForm->myScanPanelForm){
//				mainForm->myScanPanelForm->ScanStatusLabel->Hide();
				mainForm->myScanPanelForm->Enabled = true;
			}
			mainForm->myDynamicCurvePanelForm->Enabled = true;
			mainForm->myVideoForm->Enabled = true;
			break;
		}
		case 1:{
			DBAdvGlowButtonScan->Enabled = true;
			DBAdvGlowButtonContinuous->Enabled = false;

			DBAdvGlowButtonScan->Picture = ScanPicHover;
			DBAdvGlowButtonScan->Font->Color = TColor(0x00F0D27D);
			mainForm->myImageFrom->ChartButton->Hide();
			if(mainForm->myScanPanelForm){
//				mainForm->myScanPanelForm->ScanStatusLabel->Show();
				mainForm->myScanPanelForm->Enabled = false;
			}
			mainForm->myDynamicCurvePanelForm->Enabled = false;
			mainForm->myVideoForm->Enabled = false;
			break;
		}
		case 2:{
			DBAdvGlowButtonScan->Enabled = true;
			DBAdvGlowButtonContinuous->Enabled = true;
			DBAdvGlowButtonScan->Picture = ScanPicHover;

			DBAdvGlowButtonScan->Font->Color = TColor(0x00F0D27D);
			mainForm->myImageFrom->ChartButton->Show();
				if(mainForm->myScanPanelForm){
//				mainForm->myScanPanelForm->ScanStatusLabel->Show();
				mainForm->myScanPanelForm->Enabled = false;
			}
            mainForm->myDynamicCurvePanelForm->Enabled = false;
			mainForm->myVideoForm->Enabled = false;
			break;
		}
		case 4:{
			DBAdvGlowButtonScan->Enabled = false;
			DBAdvGlowButtonContinuous->Enabled = false;

			DBAdvGlowButtonScan->Picture = ScanPicHover;
			DBAdvGlowButtonScan->Font->Color = TColor(0x00F0D27D);
			mainForm->myImageFrom->ChartButton->Hide();
			if(mainForm->myScanPanelForm){
//				mainForm->myScanPanelForm->ScanStatusLabel->Show();
				mainForm->myScanPanelForm->Enabled = false;
			}
			mainForm->myDynamicCurvePanelForm->Enabled = false;
			mainForm->myVideoForm->Enabled = false;
			break;
		}
		default:{
			break;
		}
	}
}
//---------------------------------------------------------------------------

void TControlPanelForm::EnableApproachPanel(int enabled)
{
	mainForm->LogToFile("TControlPanelForm::EnableApproachPanel , enabled = " + IntToStr(enabled));
	switch(enabled){
		case 1:{
			if(mainForm->myApproachPanelForm){
				mainForm->myApproachPanelForm->EditApproachStat->Text = "Not Approached";
//				mainForm->myApproachPanelForm->ApproachStatusLabel->Show();
				DBAdvGlowButtonApproach->Enabled = true;
				DBAdvGlowButtonApproach->Picture = ApproachPic;
				DBAdvGlowButtonApproach->Font->Color = clWhite;
				RadioButtonNormal->Enabled = true;
				RadioButtonFast->Enabled = true;
				mainForm->myApproachPanelForm->KiAdvEdit->Enabled = true;
				mainForm->myApproachPanelForm->BiasAdvEdit->Enabled = true;
				mainForm->myApproachPanelForm->StpAdvEdit->Enabled = true;
				mainForm->myApproachPanelForm->RefAdvEdit->Enabled = true;
				mainForm->myApproachPanelForm->KdAdvEdit->Enabled = true;
				mainForm->myApproachPanelForm->KpAdvEdit->Enabled = true;
				mainForm->myApproachPanelForm->KiFeedbackAdvEdit->Enabled = true;
				mainForm->myApproachPanelForm->fast_checkbox->Enabled = true;
			}
			break;
		}
		case 2:{
			if(mainForm->myApproachPanelForm){
				mainForm->myApproachPanelForm->EditApproachStat->Text = "Approaching";
//				mainForm->myApproachPanelForm->ApproachStatusLabel->Show();
				DBAdvGlowButtonApproach->Enabled = true;
				DBAdvGlowButtonApproach->Picture = ApproachPicHover;
				RadioButtonNormal->Enabled = false;
				RadioButtonFast->Enabled = false;
				DBAdvGlowButtonApproach->Font->Color = TColor(0x00F0D27D);
				mainForm->myApproachPanelForm->KiAdvEdit->Enabled = false;
				mainForm->myApproachPanelForm->BiasAdvEdit->Enabled = false;
				mainForm->myApproachPanelForm->StpAdvEdit->Enabled = false;
				mainForm->myApproachPanelForm->RefAdvEdit->Enabled = false;
				mainForm->myApproachPanelForm->KdAdvEdit->Enabled = false;
				mainForm->myApproachPanelForm->KpAdvEdit->Enabled = false;
				mainForm->myApproachPanelForm->KiFeedbackAdvEdit->Enabled = false;
				mainForm->myApproachPanelForm->fast_checkbox->Enabled = false;
			}
			break;
		}
		case 3:{
			if(mainForm->myApproachPanelForm){
				mainForm->myApproachPanelForm->EditApproachStat->Text = "Approached";

				DBAdvGlowButtonApproach->Enabled = true;
				DBAdvGlowButtonApproach->Picture = ApproachPicHover;
				DBAdvGlowButtonApproach->Font->Color = TColor(0x00F0D27D);
				RadioButtonNormal->Enabled = false;
				RadioButtonFast->Enabled = false;
				mainForm->myApproachPanelForm->KiAdvEdit->Enabled = false;
				mainForm->myApproachPanelForm->BiasAdvEdit->Enabled = false;
				mainForm->myApproachPanelForm->StpAdvEdit->Enabled = false;
				mainForm->myApproachPanelForm->RefAdvEdit->Enabled = false;
				mainForm->myApproachPanelForm->KdAdvEdit->Enabled = false;
				mainForm->myApproachPanelForm->KpAdvEdit->Enabled = false;
				mainForm->myApproachPanelForm->KiFeedbackAdvEdit->Enabled = true;
				mainForm->myApproachPanelForm->fast_checkbox->Enabled = false;
			}
			break;
		}
		case 4:{
			if(mainForm->myApproachPanelForm){
				mainForm->myApproachPanelForm->EditApproachStat->Text = "Approaching";
				DBAdvGlowButtonApproach->Enabled = true;
				DBAdvGlowButtonApproach->Picture = ApproachPicHover;
				DBAdvGlowButtonApproach->Font->Color = clAppWorkSpace;
				RadioButtonNormal->Enabled = false;
				RadioButtonFast->Enabled = false;
				mainForm->myApproachPanelForm->KiAdvEdit->Enabled = false;
				mainForm->myApproachPanelForm->BiasAdvEdit->Enabled = false;
				mainForm->myApproachPanelForm->StpAdvEdit->Enabled = false;
				mainForm->myApproachPanelForm->RefAdvEdit->Enabled = false;
				mainForm->myApproachPanelForm->KdAdvEdit->Enabled = false;
				mainForm->myApproachPanelForm->KpAdvEdit->Enabled = false;
				mainForm->myApproachPanelForm->KiFeedbackAdvEdit->Enabled = false;
				mainForm->myApproachPanelForm->fast_checkbox->Enabled = false;
			}
			break;
		}
		default:{
			break;
		}
	}
}
//---------------------------------------------------------------------------

void __fastcall TControlPanelForm::UpButtonClick(TObject *Sender)
{
//	mainForm->LogToFile("retract up one step");
	//retracet up one step
	mainForm->LogToFile("TControlPanelForm::UpButtonClick");
	Num = 1;
	Status = 1;
	DownUp = false;
	TThread::Synchronize(mainForm->myCommandCreatorThread,RetDownUp);
}
//---------------------------------------------------------------------------

void __fastcall TControlPanelForm::DownButtonClick(TObject *Sender)
{
	//retracet down one step
//	mainForm->LogToFile("retract down one step");
	mainForm->LogToFile("TControlPanelForm::DownButtonClick");
	Num = 1;
	Status = 0;
	DownUp = false;
	TThread::Synchronize(mainForm->myCommandCreatorThread,RetDownUp);
}
//---------------------------------------------------------------------------

void __fastcall TControlPanelForm::RetDownUp()
{
	mainForm->LogToFile("TControlPanelForm::RetDownUp");
	mainForm->myCommandCreatorThread->StartRetDownUpClick(Num,Status,DownUp);
}
//---------------------------------------------------------------------------

void __fastcall TControlPanelForm::TenButtonClick(TObject *Sender)
{
	//retract
//	mainForm->LogToFile("retrcat 10 step");
//	AdvBadgeButtonStopApprocheClick(NULL);  //stop approach
	mainForm->LogToFile("TControlPanelForm::TenButtonClick");
	Num = 10;
	Status = 1;
	DownUp = true;

	TThread::Synchronize(mainForm->myCommandCreatorThread,RetDownUp);

//	Memo3->Lines->Add("retract");
}
//---------------------------------------------------------------------------

void __fastcall TControlPanelForm::HundredButtonClick(TObject *Sender)
{
	//retracet
//	mainForm->LogToFile("retract 100 step");
//	AdvBadgeButtonStopApprocheClick(NULL);  //stop approach
	mainForm->LogToFile("TControlPanelForm::HundredButtonClick");
	Num = 100;
	Status = 1;
	DownUp = true;

	TThread::Synchronize(mainForm->myCommandCreatorThread,RetDownUp);
}
//---------------------------------------------------------------------------

void __fastcall TControlPanelForm::ThousandButtonClick(TObject *Sender)
{
	//retracet
//	mainForm->LogToFile("retract 1000 step");
//	Memo3->Lines->Add("ThousandButtonClick");
//	AdvBadgeButtonStopApprocheClick(NULL);  //stop approach
//	Memo3->Lines->Add("StopApproche");
	mainForm->LogToFile("TControlPanelForm::ThousandButtonClick");
	Num = 1000;
	Status = 1;
	DownUp = true;

	TThread::Synchronize(mainForm->myCommandCreatorThread,RetDownUp);
}
//---------------------------------------------------------------------------

void TControlPanelForm::GetFolder()
{
	mainForm->LogToFile("TControlPanelForm::GetFolder");
	ImageFolderUser = InputBox("Directory Name","Please Enter Your Directory Name","");
//	mainForm->LogToFile("user folder = " + ImageFolderUser);
	FolderCreated = true;
}
//---------------------------------------------------------------------------

void TControlPanelForm::SetFolderNames()
{
	mainForm->LogToFile("TControlPanelForm::SetFolderNames");
	TDateTime dateTime;
	UnicodeString time = dateTime.CurrentDateTime().FormatString("hhMMss");
	UnicodeString date = dateTime.CurrentDateTime().FormatString("yyyymmdd");

	PicFolder = "scan";
	DateFolder = date;
	TimeFolder = time;
}
//---------------------------------------------------------------------------

void TControlPanelForm::EnableOneStep(bool enabled)
{
	mainForm->LogToFile("TControlPanelForm::EnableOneStep , enabled = " + BoolToStr(enabled,true));
	if(enabled)
		PanelOneStep->Enabled = true;
	else
		PanelOneStep->Enabled = false;
}
//--------------------------------------------------------------------------

void __fastcall TControlPanelForm::DBAdvGlowButtonScanClick(TObject *Sender)
{

//	mainForm->LogToFile("TControlPanelForm::DBAdvGlowButtonScanClick : scan_selcet  = " + BoolToStr(scan_selcet , true));
	if(!scan_selcet){
//		mainForm->myScanPanelForm->AllEditWhite();
		if((!HaveLicense || (HaveLicense && (LicTable.RemainedTime > 60))) && (hid == mainForm->myUniKey->FindDongle())){
            ScanPanel->Enabled = false;
			mainForm->myImageFrom->SaveButton->Visible = false;

//			mainForm->LogToFile("SaveImages = " + BoolToStr(SaveImages , true));
//			mainForm->LogToFile("LastImagesFolderPath = " + LastImagesFolderPath);
//			mainForm->LogToFile("DirectoryExists(LastImagesFolderPath,true) = " + BoolToStr(DirectoryExists(LastImagesFolderPath,true) , true));


			if(!SaveImages){
				if(DirectoryExists(LastImagesFolderPath,true)){
//					RemoveDir(LastImagesFolderPath);
					TDirectory::Delete(LastImagesFolderPath,true);
//					mainForm->LogToFile("***********DirectoryExists(LastImagesFolderPath,true) = " + BoolToStr(DirectoryExists(LastImagesFolderPath,true) , true));
				}
			}

			SaveImages = false;
			scan_selcet = true;
			mainForm->LogToFile("TControlPanelForm::DBAdvGlowButtonScanClick : start scan");
			mainForm->myMainControlPanelForm->StatusAdvEdit->Caption = "Scanning";
			mainForm->myMainControlPanelForm->StatusAdvEdit->Font->Color = clGreen;
			mainForm->myKpfmFrm->Enabled = false;
			AdvBadgeButtonStartScanClick(NULL);
			mainForm->myMainControlPanelForm->Timer1->Enabled = true;
			if(HaveLicense){
				StWatchStarted = true;
				stopwatch = StWatch->StartNew();
			}
		}
	}
	else{
        ScanPanel->Enabled = false;
		mainForm->myImageFrom->SaveButton->Visible = true;
		mainForm->myImageFrom->SaveButton->Caption = "Save Images";
		mainForm->myImageFrom->SaveButton->Enabled = true;

		scan_selcet = false;
		AgainScan = false;
		mainForm->LogToFile("TControlPanelForm::DBAdvGlowButtonScanClick : stop scan");
		AdvBadgeButtonStopScanClick(NULL);
		mainForm->myMainControlPanelForm->Timer1->Enabled = false;
		if(mainForm->Approached){
			mainForm->myMainControlPanelForm->StatusAdvEdit->Caption = "Approached";
			mainForm->myMainControlPanelForm->StatusAdvEdit->Font->Color = clAqua;
		}
		else{
			mainForm->myMainControlPanelForm->StatusAdvEdit->Caption = "Ready to Approach";
			mainForm->myMainControlPanelForm->StatusAdvEdit->Font->Color = clHighlight;
		}
		mainForm->myKpfmFrm->Enabled = true;
	}
}
//---------------------------------------------------------------------------

void __fastcall TControlPanelForm::DBAdvGlowButtonContinuousClick(TObject *Sender)
{
	if(!continuos_select){
		mainForm->LogToFile("TControlPanelForm::DBAdvGlowButtonContinuousClick : !continuos_select");
		continuos_select = true;
		DBAdvGlowButtonContinuous->Picture = ContinuousPicHover;
		DBAdvGlowButtonContinuous->Font->Color = TColor(0x00F0D27D);
        mainForm->myScanPanelForm->ContinuousCheckBox->Checked = true;
	}
	else{
		mainForm->LogToFile("TControlPanelForm::DBAdvGlowButtonContinuousClick : continuos_select");
		continuos_select = false;
		DBAdvGlowButtonContinuous->Picture = ContinuousPic;
		DBAdvGlowButtonContinuous->Font->Color = clWhite;
		mainForm->myScanPanelForm->ContinuousCheckBox->Checked = false;
	}
}

//---------------------------------------------------------------------------


void __fastcall TControlPanelForm::DBAdvGlowButtonApproachClick(TObject *Sender)
{
	if(!approach_selcet){
		if(hid == mainForm->myUniKey->FindDongle()){
	//    	mainForm->myApproachPanelForm->AllEditWhite();
			approach_selcet = true;
			mainForm->LogToFile("TControlPanelForm::DBAdvGlowButtonApproachClick : start approach");
	//		DBAdvGlowButtonApproach->Picture = ApproachPicHover;
			AdvBadgeButtonStartApproachClick(NULL);
			mainForm->myApproachPanelForm->EditApproachStat->Text = "Approaching";
			mainForm->myMainControlPanelForm->StatusAdvEdit->Font->Color = clAqua;
			mainForm->myMainControlPanelForm->Timer1->Enabled = true;
		}
	}
	else{
		approach_selcet = false;
		mainForm->LogToFile("TControlPanelForm::DBAdvGlowButtonApproachClick : stop approach");
//		DBAdvGlowButtonApproach->Picture = ApproachPic;
		AdvBadgeButtonStopApprocheClick(NULL);
		mainForm->myMainControlPanelForm->Timer1->Enabled = false;
		mainForm->myMainControlPanelForm->StatusAdvEdit->Caption = "Ready to Approach";
		mainForm->myMainControlPanelForm->StatusAdvEdit->Font->Color = clHighlight;
		if(fast){
			StopFastTimer->Enabled = true;
		}
	}
}
//---------------------------------------------------------------------------

void __fastcall TControlPanelForm::DBAdvGlowButtonRetractClick(TObject *Sender)
{
	mainForm->LogToFile("TControlPanelForm::DBAdvGlowButtonRetractClick , RetractStep = " + IntToStr(RetractStep));
	switch (RetractStep) {
		case 1:
			TenButtonClick(NULL);
			break;
		case 2:
			HundredButtonClick(NULL);
			break;
		case 3:
			ThousandButtonClick(NULL);
			break;
		default:
			break;
	}
}
//---------------------------------------------------------------------------

void __fastcall TControlPanelForm::AdvTrackBarRetractChange(TObject *Sender)
{

	RetractStep = AdvTrackBarRetract->Position;
}
//---------------------------------------------------------------------------

void __fastcall TControlPanelForm::RadioButtonNormalClick(TObject *Sender)
{
	mainForm->LogToFile("TControlPanelForm::RadioButtonNormalClick");
	StopFastTimer->Enabled = true;
}
//---------------------------------------------------------------------------

void __fastcall TControlPanelForm::RadioButtonFastClick(TObject *Sender)
{
	mainForm->LogToFile("TControlPanelForm::RadioButtonFastClick");
	fast = true;
	mainForm->myApproachPanelForm->fast_checkbox->Checked = true;
	mainForm->myUdpThread->SendSettingPacket(mainForm->AppMode,1,1);


	Fast_Dnc_From = FastApproachTable.Dnc_FrequencyFrom_Val;
	Fast_Dnc_To = FastApproachTable.Dnc_FrequencyTo_Val;
	AmpIndex = OscTable[6].index;
	AmpOffset = OscTable[6].offset;
	Min_Amp = FastApproachTable.Min_Amp;
	Max_Amp = FastApproachTable.Max_Amp;
	Start_Drive = FastApproachTable.Drive_Start;
	DriveIndex = DncTable.Dnc_DriveIndex_Val;     // mv to number
	DriveOffset = DncTable.Dnc_DriveOffset_Val;


	MainDriveVal = ((double)Start_Drive * DriveIndex) + DriveOffset;
//	mainForm->LogToFile("MainDriveVal 1 = " + IntToStr(MainDriveVal));
	if((mainForm->AppMode == 1 || mainForm->AppMode == 5 || mainForm->AppMode == 7)){
		RetractTimer->Enabled = true;
	}


}
//---------------------------------------------------------------------------

void __fastcall TControlPanelForm::RetractTimerTimer(TObject *Sender)
{
	RetractTimer->Enabled = false;
	HundredButtonClick(NULL);
}
//---------------------------------------------------------------------------
void __fastcall TControlPanelForm::RadioButtonPreciseClick(TObject *Sender)
{
	mainForm->LogToFile("TControlPanelForm::RadioButtonPreciseClick");
	RadioButtonNormal->Checked = true;
}
//---------------------------------------------------------------------------

void TControlPanelForm::FastDncCurve()
{
	mainForm->LogToFile("TControlPanelForm::FastDncCurve");
	double AmpMax;

	mainForm->myDynamicCurvePanelForm->To_Val = Fast_Dnc_To;
	mainForm->myDynamicCurvePanelForm->From_Val = Fast_Dnc_From;
	mainForm->myDynamicCurvePanelForm->MainDriveVal = MainDriveVal;
	mainForm->myDynamicCurvePanelForm->start = true;
	mainForm->myDynamicCurvePanelForm->RunAdvGlassButtonClick(NULL);

	dnc = false;
	fastfast = true;
	while(!dnc){
		Application->ProcessMessages();
	}
	dnc = false;
	fastfast = false;



	Pic_Freq = Fast_Dnc_From + (mainForm->myTcpThread->Pic_Freq_Index * mainForm->myCommandCreatorThread->myDnc->Step);
//	mainForm->LogToFile("Pic_Freq 1 = " + IntToStr(Pic_Freq));
//	AmpMax = mainForm->myTcpThread->AmpMax * 1000;
//	mainForm->LogToFile("AmpMax 1 = " + FloatToStr(AmpMax));

	int New_Fast_From = Pic_Freq - 1200;
	int New_Fast_To = Pic_Freq + 1000;
	mainForm->myDynamicCurvePanelForm->To_Val = New_Fast_To;
	mainForm->myDynamicCurvePanelForm->From_Val = New_Fast_From;
	mainForm->myDynamicCurvePanelForm->MainDriveVal = MainDriveVal;
	mainForm->myDynamicCurvePanelForm->start = true;
	mainForm->myDynamicCurvePanelForm->RunAdvGlassButtonClick(NULL);

	dnc = false;
	fastfast = true;
	while(!dnc){
		Application->ProcessMessages();
	}
	dnc = false;
	fastfast = false;

	Pic_Freq = New_Fast_From + (mainForm->myTcpThread->Pic_Freq_Index * mainForm->myCommandCreatorThread->myDnc->Step);
//	mainForm->LogToFile("Pic_Freq 2 = " + IntToStr(Pic_Freq));
//	AmpMax = mainForm->myTcpThread->AmpMax * 1000;
//	mainForm->LogToFile("AmpMax 2 = " + FloatToStr(AmpMax));

	while(mainForm->myApproachPanelForm->fast_checkbox->Checked){
		Application->ProcessMessages();
		int diff;
		if((mainForm->myUdpThread->FastAmp * 1000) > Max_Amp){
		   diff = (mainForm->myUdpThread->FastAmp * 1000) - Max_Amp;
		   if(diff > 10){
				Start_Drive = Start_Drive - ((int)(diff / 10) * 10);
		   }
		   else{
				if(diff % 10 == 0) Start_Drive = Start_Drive - 1;
				else Start_Drive = Start_Drive - (diff % 10);
		   }

		}
		else if((mainForm->myUdpThread->FastAmp * 1000) < Min_Amp){
		   diff = Min_Amp - (mainForm->myUdpThread->FastAmp * 1000);
		   if(diff > 10){
				Start_Drive = Start_Drive + ((int)(diff / 10) * 10);
		   }
		   else{
				if(diff % 10 == 0) Start_Drive = Start_Drive + 1;
				else Start_Drive = Start_Drive + (diff % 10);
		   }
		}
		else{
//			mainForm->LogToFile("Final Pic_Freq = " + IntToStr(Pic_Freq));
//			AmpMax = mainForm->myUdpThread->FastAmp * 1000;
//			mainForm->LogToFile("Final AmpMax = " + FloatToStr(AmpMax));
			FastTimer->Enabled = false;
			break;
		}

		MainDriveVal = ((double)Start_Drive * DriveIndex) + DriveOffset;



		mainForm->myDynamicCurvePanelForm->To_Val = New_Fast_To;
		mainForm->myDynamicCurvePanelForm->From_Val = New_Fast_From;
		mainForm->myDynamicCurvePanelForm->MainDriveVal = MainDriveVal;
		mainForm->myDynamicCurvePanelForm->Use_Val = Pic_Freq;
		mainForm->myDynamicCurvePanelForm->SetPoint_Val = 100;
		mainForm->myDynamicCurvePanelForm->start = false;
		mainForm->myDynamicCurvePanelForm->RunAdvGlassButtonClick(NULL);

		dncCheck = false;
		FastTimer->Enabled = true;

		while(!dncCheck){
			Application->ProcessMessages();
		}

//		mainForm->LogToFile("Pic_Freq 3 = " + IntToStr(Pic_Freq));
//		AmpMax = mainForm->myUdpThread->FastAmp * 1000;
//		mainForm->LogToFile("AmpMax 3 = " + FloatToStr(AmpMax));
	}



}
//---------------------------------------------------------------------------

void __fastcall TControlPanelForm::FastTimerTimer(TObject *Sender)
{
	mainForm->LogToFile("TControlPanelForm::FastTimerTimer");
	FastTimer->Enabled = false;
	dncCheck = true;
}
//---------------------------------------------------------------------------

void __fastcall TControlPanelForm::StopFastTimerTimer(TObject *Sender)
{
	mainForm->LogToFile("TControlPanelForm::StopFastTimerTimer , StopFastState = " + IntToStr(StopFastState));
	if(StopFastState == 0){

		fast = false;
		mainForm->myApproachPanelForm->fast_checkbox->Checked = false;
		RadioButtonNormal->Checked = true;
		if(mainForm->AppMode == 1 || mainForm->AppMode == 5 || mainForm->AppMode == 7){
			mainForm->LogToFile("stop dnc approach");
			mainForm->myDynamicCurvePanelForm->Drive_Val = 0;
			mainForm->myDynamicCurvePanelForm->start = false;
			mainForm->myDynamicCurvePanelForm->RunAdvGlassButtonClick(NULL);
		}
		StopFastState++;
	}
	else if(StopFastState == 1){
		mainForm->myUdpThread->SendSettingPacket(mainForm->AppMode,0,1);
		StopFastState++;
	}
	else{
		StopFastTimer->Enabled = false;
		StopFastState = 0;
	}

}
//---------------------------------------------------------------------------



