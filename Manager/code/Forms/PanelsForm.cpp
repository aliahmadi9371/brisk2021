//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "PanelsForm.h"
#include "mainUnit.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "AdvScrollBox"
#pragma link "AdvGlowButton"
#pragma link "AdvPanel"
#pragma link "AdvGlassButton"
#pragma resource "*.dfm"
TCtrlForm *CtrlForm;
//---------------------------------------------------------------------------
__fastcall TCtrlForm::TCtrlForm(TComponent* Owner)
	: TForm(Owner)
{
	PanelPickIndex = 1;
	MainPanel->Caption = "";
	first = false;
}
//---------------------------------------------------------------------------

void __fastcall TCtrlForm::CtrlButtonClick(TObject *Sender)
{
	mainForm->LogToFile("TCtrlForm::CtrlButtonClick");
	if(PanelPickIndex != 1){
		PanelPickIndex = 1;
		PickPanel(PanelPickIndex);
	}
}
//---------------------------------------------------------------------------

void __fastcall TCtrlForm::DncButtonClick(TObject *Sender)
{
	mainForm->LogToFile("TCtrlForm::DncButtonClick");
	if(PanelPickIndex != 2){
		PanelPickIndex = 2;
		PickPanel(PanelPickIndex);
	}
}
//---------------------------------------------------------------------------

void __fastcall TCtrlForm::ApchButtonClick(TObject *Sender)
{
	mainForm->LogToFile("TCtrlForm::ApchButtonClick");
	if(PanelPickIndex != 3){
		PanelPickIndex = 3;
		PickPanel(PanelPickIndex);
	}
}
//---------------------------------------------------------------------------

void __fastcall TCtrlForm::ScanButtonClick(TObject *Sender)
{
	mainForm->LogToFile("TCtrlForm::ScanButtonClick");
	if(PanelPickIndex != 4){
		PanelPickIndex = 4;
		PickPanel(PanelPickIndex);
	}
}
//---------------------------------------------------------------------------

void __fastcall TCtrlForm::MovingButtonClick(TObject *Sender)
{
	mainForm->LogToFile("TCtrlForm::MovingButtonClick");
	if(PanelPickIndex != 5){
		PanelPickIndex = 5;
		PickPanel(PanelPickIndex);
	}
}
//---------------------------------------------------------------------------

void __fastcall TCtrlForm::ForceSpecButtonClick(TObject *Sender)
{
	mainForm->LogToFile("TCtrlForm::ForceSpecButtonClick");
	if(PanelPickIndex != 6){
		PanelPickIndex = 6;
		PickPanel(PanelPickIndex);
	}
}
//--------------------------------------------------------------------------

void __fastcall TCtrlForm::SettingButtonClick(TObject *Sender)
{
	mainForm->LogToFile("TCtrlForm::SettingButtonClick");
	if(PanelPickIndex != 7){
		PanelPickIndex = 7;
		PickPanel(PanelPickIndex);
	}
}
//---------------------------------------------------------------------------

void __fastcall TCtrlForm::LithoButtonClick(TObject *Sender)
{
	mainForm->LogToFile("TCtrlForm::LithoButtonClick");
	if(PanelPickIndex != 8){
		PanelPickIndex = 8;
		PickPanel(PanelPickIndex);
	}
}
//---------------------------------------------------------------------------

void __fastcall TCtrlForm::GalleryButtonClick(TObject *Sender)
{
	mainForm->LogToFile("TCtrlForm::GalleryButtonClick");
	if(PanelPickIndex != 9){
		PanelPickIndex = 9;
		PickPanel(PanelPickIndex);
	}
}
//---------------------------------------------------------------------------

void __fastcall TCtrlForm::KpfmButtonClick(TObject *Sender)
{
	mainForm->LogToFile("TCtrlForm::KpfmButtonClick");
	if(PanelPickIndex != 10){
		PanelPickIndex = 10;
		PickPanel(PanelPickIndex);
	}
}
//---------------------------------------------------------------------------

void __fastcall TCtrlForm::FormCreate(TObject *Sender)
{

	this->Hide();
	ApproachingTogle = false;
	ScaningTogle = false;
	MainPanel->Height = this->Height - PanelAdvScrollBox->Height;
	LoadPictures();
}
//---------------------------------------------------------------------------

void TCtrlForm::LoadPictures()
{
	CtrlPanelPic = new TGDIPPicture;
	CtrlPanelPic->LoadFromFile(MainPath + "/Resources/Images/PNL_Form/control.png");

	CtrlPanelPicHover = new TGDIPPicture;
	CtrlPanelPicHover->LoadFromFile(MainPath + "/Resources/Images/PNL_Form/control_hover.png");

	DncPanelPic = new TGDIPPicture;
	DncPanelPic->LoadFromFile(MainPath + "/Resources/Images/PNL_Form/dnc.png");

	DncPanelPicHover = new TGDIPPicture;
	DncPanelPicHover->LoadFromFile(MainPath + "/Resources/Images/PNL_Form/dnc_hover.png");

	ApchPanelPic = new TGDIPPicture;
	ApchPanelPic->LoadFromFile(MainPath + "/Resources/Images/PNL_Form/approach.png");

	ApchPanelPicHover = new TGDIPPicture;
	ApchPanelPicHover->LoadFromFile(MainPath + "/Resources/Images/PNL_Form/approach_hover.png");

	ScanPanelPic = new TGDIPPicture;
	ScanPanelPic->LoadFromFile(MainPath + "/Resources/Images/PNL_Form/scan.png");

	ScanPanelPicHover = new TGDIPPicture;
	ScanPanelPicHover->LoadFromFile(MainPath + "/Resources/Images/PNL_Form/scan_hover.png");

	MovePanelPic = new TGDIPPicture;
	MovePanelPic->LoadFromFile(MainPath + "/Resources/Images/PNL_Form/moving.png");

	MovePanelPicHover = new TGDIPPicture;
	MovePanelPicHover->LoadFromFile(MainPath + "/Resources/Images/PNL_Form/moving_hover.png");

	SettingPanelPic = new TGDIPPicture;
	SettingPanelPic->LoadFromFile(MainPath + "/Resources/Images/PNL_Form/wrench.png");

	SettingPanelPicHover = new TGDIPPicture;
	SettingPanelPicHover->LoadFromFile(MainPath + "/Resources/Images/PNL_Form/wrench_hover.png");

	ForcePanelPic = new TGDIPPicture;
	ForcePanelPic->LoadFromFile(MainPath + "/Resources/Images/PNL_Form/force.png");

	ForcePanelPicHover = new TGDIPPicture;
	ForcePanelPicHover->LoadFromFile(MainPath + "/Resources/Images/PNL_Form/force_hover.png");

	LithoPanelPic = new TGDIPPicture;
	LithoPanelPic->LoadFromFile(MainPath + "/Resources/Images/PNL_Form/litho.png");

	LithoPanelPicHover = new TGDIPPicture;
	LithoPanelPicHover->LoadFromFile(MainPath + "/Resources/Images/PNL_Form/litho_hover.png");

	GalPanelPic = new TGDIPPicture;
	GalPanelPic->LoadFromFile(MainPath + "/Resources/Images/PNL_Form/gallery.png");

	GalPanelPicHover = new TGDIPPicture;
	GalPanelPicHover->LoadFromFile(MainPath + "/Resources/Images/PNL_Form/gallery_hover.png");

	KpfmPanelPic = new TGDIPPicture;
	KpfmPanelPic->LoadFromFile(MainPath + "/Resources/Images/PNL_Form/kpfm.png");

	KpfmPanelPicHover = new TGDIPPicture;
	KpfmPanelPicHover->LoadFromFile(MainPath + "/Resources/Images/PNL_Form/kpfm_hover.png");

    if(!mutex){
		mutex = new TMutex(false);

	}

	mutex = NULL;

    if(!myUdpDataSendClass){
		myUdpDataSendClass = new UdpDataSendClass(NULL);
	}
	myUdpDataSendClass = NULL;

}
//---------------------------------------------------------------------------

void TCtrlForm::PickPanel(unsigned int pnl_index)
{
	mainForm->LogToFile("TCtrlForm::PickPanel");
	switch(pnl_index){
		case 1:{
			ShowButtonsPanel(1);
			SetPanelColorPic(CtrlPanelPicHover, CtrlButton);
			break;
		}
		case 2:{
			ShowButtonsPanel(2);
			SetPanelColorPic(DncPanelPicHover, DncButton);
			break;
		}
		case 3:{
			ShowButtonsPanel(3);
			SetPanelColorPic(ApchPanelPicHover, ApchButton);
			break;
		}
		case 4:{
			ShowButtonsPanel(4);
			SetPanelColorPic(ScanPanelPicHover, ScanButton);
			break;
		}
		case 5:{
			ShowButtonsPanel(5);
			SetPanelColorPic(MovePanelPicHover, MovingButton);
			break;
		}
		case 6:{
			ShowButtonsPanel(6);
			SetPanelColorPic(ForcePanelPicHover, ForceSpecButton);
			break;
		}
		case 7:{

			ShowButtonsPanel(7);
			SetPanelColorPic(SettingPanelPicHover, SettingButton);
			break;
		}
		case 8:{
			ShowButtonsPanel(8);
			SetPanelColorPic(LithoPanelPicHover, LithoButton);
			break;
		}
		case 9:{
			ShowButtonsPanel(9);
			SetPanelColorPic(GalPanelPicHover, GalleryButton);
			break;
		}
		case 10:{
			ShowButtonsPanel(10);
			SetPanelColorPic(KpfmPanelPicHover, KpfmButton);
			break;
		}
	}
}
//---------------------------------------------------------------------------

void TCtrlForm::ShowButtonsPanel(int panel)
{

	mainForm->myControlPanelForm->Hide();
	mainForm->myDynamicCurvePanelForm->Hide();
	mainForm->myApproachPanelForm->Hide();
	mainForm->myScanPanelForm->Hide();
	mainForm->myMovingPanelForm->Hide();
	mainForm->myForceForm->Hide();
	mainForm->mySettingForm->Hide();
	mainForm->myLithoFrm->Hide();
	mainForm->GalFrm->Hide();
	mainForm->myKpfmFrm->Hide();
	switch(panel){
		case 1:
			mainForm->myControlPanelForm->Show();
			break;
		case 2:
			mainForm->myDynamicCurvePanelForm->Show();
			break;
		case 3:
			mainForm->myApproachPanelForm->Show();
			break;
		case 4:
			mainForm->myScanPanelForm->Show();
			break;
		case 5:
			mainForm->myMovingPanelForm->Show();
			break;
		case 6:
			mainForm->myForceForm->Show();
			break;
		case 7:
			mainForm->mySettingForm->Show();
			break;
		case 8:
			mainForm->myLithoFrm->Show();
			break;
		case 9:
			mainForm->GalFrm->Show();
			break;
		case 10:
			mainForm->myKpfmFrm->Show();
			break;
	}
}
//---------------------------------------------------------------------------

void TCtrlForm::SetPanelColorPic(TGDIPPicture* picture, TDBAdvGlowButton* button)
{
	CtrlButton->Picture = CtrlPanelPic;
	CtrlButton->Appearance->Color = TColor(0x00553629);
	CtrlButton->Appearance->ColorTo = TColor(0x00553629);
	CtrlButton->Appearance->ColorMirror = TColor(0x00553629);
	CtrlButton->Appearance->ColorMirrorTo = TColor(0x00553629);
	CtrlButton->Font->Color = clWhite;

	DncButton->Picture = DncPanelPic;
	DncButton->Appearance->Color = TColor(0x00553629);
	DncButton->Appearance->ColorTo = TColor(0x00553629);
	DncButton->Appearance->ColorMirror = TColor(0x00553629);
	DncButton->Appearance->ColorMirrorTo = TColor(0x00553629);
	DncButton->Font->Color = clWhite;

	ApchButton->Picture = ApchPanelPic;
	ApchButton->Appearance->Color = TColor(0x00553629);
	ApchButton->Appearance->ColorTo = TColor(0x00553629);
	ApchButton->Appearance->ColorMirror = TColor(0x00553629);
	ApchButton->Appearance->ColorMirrorTo = TColor(0x00553629);
	ApchButton->Font->Color = clWhite;

	ScanButton->Picture = ScanPanelPic;
	ScanButton->Appearance->Color = TColor(0x00553629);
	ScanButton->Appearance->ColorTo = TColor(0x00553629);
	ScanButton->Appearance->ColorMirror = TColor(0x00553629);
	ScanButton->Appearance->ColorMirrorTo = TColor(0x00553629);
	ScanButton->Font->Color = clWhite;

	MovingButton->Picture = MovePanelPic;
	MovingButton->Appearance->Color = TColor(0x00553629);
	MovingButton->Appearance->ColorTo = TColor(0x00553629);
	MovingButton->Appearance->ColorMirror = TColor(0x00553629);
	MovingButton->Appearance->ColorMirrorTo = TColor(0x00553629);
	MovingButton->Font->Color = clWhite;

	ForceSpecButton->Picture = ForcePanelPic;
	ForceSpecButton->Appearance->Color = TColor(0x00553629);
	ForceSpecButton->Appearance->ColorTo = TColor(0x00553629);
	ForceSpecButton->Appearance->ColorMirror = TColor(0x00553629);
	ForceSpecButton->Appearance->ColorMirrorTo = TColor(0x00553629);
	ForceSpecButton->Font->Color = clWhite;

	SettingButton->Picture = SettingPanelPic;
	SettingButton->Appearance->Color = TColor(0x00553629);
	SettingButton->Appearance->ColorTo = TColor(0x00553629);
	SettingButton->Appearance->ColorMirror = TColor(0x00553629);
	SettingButton->Appearance->ColorMirrorTo = TColor(0x00553629);
	SettingButton->Font->Color = clWhite;

	LithoButton->Picture = LithoPanelPic;
	LithoButton->Appearance->Color = TColor(0x00553629);
	LithoButton->Appearance->ColorTo = TColor(0x00553629);
	LithoButton->Appearance->ColorMirror = TColor(0x00553629);
	LithoButton->Appearance->ColorMirrorTo = TColor(0x00553629);
	LithoButton->Font->Color = clWhite;

	GalleryButton->Picture = GalPanelPic;
	GalleryButton->Appearance->Color = TColor(0x00553629);
	GalleryButton->Appearance->ColorTo = TColor(0x00553629);
	GalleryButton->Appearance->ColorMirror = TColor(0x00553629);
	GalleryButton->Appearance->ColorMirrorTo = TColor(0x00553629);
	GalleryButton->Font->Color = clWhite;

	KpfmButton->Picture = KpfmPanelPic;
	KpfmButton->Appearance->Color = TColor(0x00553629);
	KpfmButton->Appearance->ColorTo = TColor(0x00553629);
	KpfmButton->Appearance->ColorMirror = TColor(0x00553629);
	KpfmButton->Appearance->ColorMirrorTo = TColor(0x00553629);
	KpfmButton->Font->Color = clWhite;

	CtrlButton->Width = 79;
	DncButton->Width = 79;
	ApchButton->Width = 79;
	ScanButton->Width = 79;
	MovingButton->Width = 79;
	SettingButton->Width = 79;
	ForceSpecButton->Width = 79;
	LithoButton->Width = 79;
	GalleryButton->Width = 79;
	KpfmButton->Width = 79;

	button->Picture = picture;
	button->Appearance->Color = TColor(0x00614438);
	button->Appearance->ColorTo = TColor(0x00614438);
	button->Appearance->ColorMirror = TColor(0x00614438);
	button->Appearance->ColorMirrorTo = TColor(0x00614438);
	button->Font->Color = TColor(0x00F0D27D);
}
//---------------------------------------------------------------------------

void __fastcall TCtrlForm::FormShow(TObject *Sender)
{
	if(!first){

		myQfrm = new TQFrm(this);
//		Application->CreateForm(__classid(TQFrm), &QFrm);
//		myQfrm->Parent = this;
//		myQfrm->SetParentComponent(this);

		myQfrm->Top = 0;
		myQfrm->Left = 0;

		switch(mainForm->AppMode){
			case 1:{
				//hide some panels
				DncButton->Visible = false;
				ForceSpecButton->Visible = false;
				LithoButton->Visible = false;
				KpfmButton->Visible = false;

				//contact mode first dnc
				mainForm->myDynamicCurvePanelForm->Visible = false;
				mainForm->myDynamicCurvePanelForm->contact = true;
				if(!mainForm->myUdpThread->ConnectionState){
					mainForm->myDynamicCurvePanelForm->RunAdvGlassButtonClick(NULL);
				}

				PanelAdvScrollBox->Height = this->Height/7;
				StatusAdvEdit->Caption = "Ready to Approach";
				StatusAdvEdit->Font->Color = clHighlight;
				break;
			}
			case 2:{
				//hide some panels
				ForceSpecButton->Visible = false;
				LithoButton->Visible = false;
				KpfmButton->Visible = false;

				PanelAdvScrollBox->Height = this->Height/7;
				StatusAdvEdit->Caption = "Not Ready to Approach";
				StatusAdvEdit->Font->Color = clWhite;
				break;
			}

			case 3:{
				//hide some panels

				ForceSpecButton->Visible = false;
				LithoButton->Visible = false;
				KpfmButton->Visible = false;

				PanelAdvScrollBox->Height = this->Height/7;
				StatusAdvEdit->Caption = "Not Ready to Approach";
				StatusAdvEdit->Font->Color = clWhite;
				break;
			}

			case 4:{
				//hide some panels
				ForceSpecButton->Visible = false;
				LithoButton->Visible = false;
				KpfmButton->Visible = false;

				PanelAdvScrollBox->Height = this->Height/7;
				StatusAdvEdit->Caption = "Not Ready to Approach";
				StatusAdvEdit->Font->Color = clWhite;
				break;
			}

			case 5:{
				//hide some panels
				DncButton->Visible = false;
				LithoButton->Visible = false;
				KpfmButton->Visible = false;

				//contact mode first dnc
				mainForm->myDynamicCurvePanelForm->Visible = false;
				mainForm->myDynamicCurvePanelForm->contact = true;
				if(!mainForm->myUdpThread->ConnectionState){
					mainForm->myDynamicCurvePanelForm->RunAdvGlassButtonClick(NULL);
				}


				PanelAdvScrollBox->Height = this->Height/7;
				StatusAdvEdit->Caption = "Ready to Approach";
				StatusAdvEdit->Font->Color = clHighlight;
				break;
			}
			case 6:{
                //hide some panels
				ForceSpecButton->Visible = false;
				LithoButton->Visible = false;

				PanelAdvScrollBox->Height = this->Height/7;
				StatusAdvEdit->Caption = "Not Ready to Approach";
				StatusAdvEdit->Font->Color = clWhite;
				break;
			}
			case 7:{
				//hide some panels
				DncButton->Visible = false;
				ForceSpecButton->Visible = false;
				KpfmButton->Visible = false;

				//contact mode first dnc
				mainForm->myDynamicCurvePanelForm->Visible = false;
				mainForm->myDynamicCurvePanelForm->contact = true;
				if(!mainForm->myUdpThread->ConnectionState){
					mainForm->myDynamicCurvePanelForm->RunAdvGlassButtonClick(NULL);
				}


				PanelAdvScrollBox->Height = this->Height/7;
				StatusAdvEdit->Caption = "Ready to Approach";
				StatusAdvEdit->Font->Color = clHighlight;
				break;
			}
			default:{
				break;
			}
		}


		PanelAdvScrollBox->Height = 60;
		PanelTop->Height = 60;


		ImageLogo->Left = this->Width - ImageLogo->Width - 10;
		ImageLogo->Top = 5;

		DateTimeEdit->Top =  ImageLogo->Top;
		DateTimeEdit->Left =  ImageLogo->Left - DateTimeEdit->Width - 20;

		StatusAdvEdit->Top = DateTimeEdit->Top;
		StatusAdvEdit->Left = DateTimeEdit->Left - StatusAdvEdit->Width - 20;

		pOffBut->Left = 15;
		pOffBut->Top = 5;

		PickPanel(1);
		first = true;

		if(!mainForm->myUdpThread->ConnectionState){
			 mainForm->myControlPanelForm->AdvBadgeButtonStopApprocheClick(NULL);
             mainForm->ext_pnl->Caption = "please wait for initializing";
			 mainForm->ext_pnl->ShowCaption = true;
			 mainForm->ext_pnl->BringToFront();
			 mainForm->ext_pnl->Show();
			 mainForm->Enabled = false;
			 Timer2->Enabled = true;
		}

		if(mainForm->myUdpThread->approched && mainForm->myUdpThread->ConnectionState ){
			mainForm->myControlPanelForm->approach_selcet = true;
			mainForm->myControlPanelForm->EnableApproachPanel(3);

		}
		mainForm->GetSecure();
	}
}
//---------------------------------------------------------------------------

void __fastcall TCtrlForm::pOffButClick(TObject *Sender)
{
	mainForm->LogToFile("TCtrlForm::pOffButClick");

	if(mainForm->Scaning || mainForm->Lithoing || mainForm->Forcing || mainForm->Approached || mainForm->Approaching){
		myQfrm->Show();
	}
	else{
		if(mainForm->myOscForm){
			mainForm->Enabled = false;
			mainForm->myOscForm->pOffButClick(NULL);
		}
	}
}
//---------------------------------------------------------------------------

void __fastcall TCtrlForm::TimeTimerTimer(TObject *Sender)
{
	DateTimeEdit->Caption =  TDateTime::CurrentDateTime().FormatString("yyyy/mm/dd\r\nhh:MM:ss");
}
//---------------------------------------------------------------------------

void __fastcall TCtrlForm::Timer1Timer(TObject *Sender)
{
	if(mainForm->Approaching){
		if(ApproachingTogle){
			ApproachingTogle = false;
			StatusAdvEdit->Caption = "Approaching";
			StatusAdvEdit->Font->Color = clAqua;
		}
		else{
			ApproachingTogle = true;
			StatusAdvEdit->Caption = "Approaching";
			StatusAdvEdit->Font->Color = clHighlight;
		}
	}

	if(mainForm->Approached && !mainForm->Scaning){
		StatusAdvEdit->Caption = "Approached";
		StatusAdvEdit->Font->Color = clAqua;
		Timer1->Enabled = false;
	}

	if(!mainForm->Approached && !mainForm->Scaning && !mainForm->Approaching){
		StatusAdvEdit->Caption = "Ready to Approach";
		StatusAdvEdit->Font->Color = clHighlight;
		Timer1->Enabled = false;
	}

	if(mainForm->Approached && mainForm->Scaning){

		if(ScaningTogle){
			ScaningTogle = false;
			StatusAdvEdit->Caption = "Scanning";
			StatusAdvEdit->Font->Color = clGreen;
		}
		else{
			ScaningTogle = true;
			StatusAdvEdit->Caption = "Scanning";
			StatusAdvEdit->Font->Color = clAqua;
		}
	}
	else if(!mainForm->Approached && mainForm->Scaning){
		if(ScaningTogle){
			ScaningTogle = false;
			StatusAdvEdit->Caption = "Scanning";
			StatusAdvEdit->Font->Color = clGreen;
		}
		else{
			ScaningTogle = true;
			StatusAdvEdit->Caption = "Scanning";
			StatusAdvEdit->Font->Color = clHighlight;
		}
	}
}
//---------------------------------------------------------------------------

void __fastcall TCtrlForm::Timer2Timer(TObject *Sender)
{
	mainForm->LogToFile("TCtrlForm : Timer2Timer");
	Timer2->Enabled = false;

	FsCommand.start = false;
	FsCommand.startx = 50;
	FsCommand.starty = 50;
	FsCommand.resolution = 64;
	FsCommand.delay = 0;
	FsCommand.mode = 1;
	FsCommand.GOTO = 1;
	FsCommand.dz1 = 0;
	FsCommand.dz2 = 0;
	FsCommand.u1 = 0;
	FsCommand.u2 = 0;
	FsCommand.currentZ = 0;
	FsCommand.currentU = 0;
	mainForm->myCommandCreatorThread->force_file = true;
//	mainForm->myCommandCreatorThread->StartStopFsClick(true, 50, 50, 64, 0, 1, 1, 0, 0, 0, 0, 0, 0);
	while(!mainForm->myUdpThread->fs_GoTo_set){
		Application->ProcessMessages();
	}
	mainForm->myCommandCreatorThread->myFs->OffFs();
	mainForm->ext_pnl->Hide();
	mainForm->LogToFile("oscForm : GoTo (0 ,0)");
	mainForm->Enabled = true;


}
//---------------------------------------------------------------------------


