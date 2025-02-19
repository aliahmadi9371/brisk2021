//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "MovingForm.h"
#include "mainUnit.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "AdvShapeButton"
#pragma link "AdvGlowButton"
#pragma link "htmlbtns"
#pragma link "AdvOfficeButtons"
#pragma link "AdvTrackBar"
#pragma link "AdvPanel"
#pragma link "CurvyControls"
#pragma link "AdvGlassButton"
#pragma resource "*.dfm"
TMvFrm *MvFrm;
//---------------------------------------------------------------------------
__fastcall TMvFrm::TMvFrm(TComponent* Owner)
	: TForm(Owner)
{

}
//---------------------------------------------------------------------------
void __fastcall TMvFrm::FormCreate(TObject *Sender)
{
	this->Hide();

	first = false;


	FastStage = false;
	FastCoarse = false;
}
//---------------------------------------------------------------------------

void TMvFrm::CheckUnCkeck(bool A, bool B, bool C, bool all, bool fast)
{

}
//---------------------------------------------------------------------------


void __fastcall TMvFrm::StepperRetract()
{
	mainForm->LogToFile("TMvFrm::StepperRetract");
	mainForm->myCommandCreatorThread->StartRetractClick(Mode,StateM,SShift);
}
//---------------------------------------------------------------------------

void __fastcall TMvFrm::UpButtonMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift,
		  int X, int Y)
{
	mainForm->LogToFile("TMvFrm::UpButtonMouseDown");
    mainForm->StageMoving = true;
	mainForm->GetSecure();
	UpCoarseButton->Picture = UpCoarseHover;
	UpDownBorder(UpCoarseButton->Appearance,false);
	if (AllStepper){
		if( (Button == mbLeft) && (Shift.ToInt() == ssShift || FastCoarse) ){
			Mode = 0;
			StateM = 1;
			SShift = true;
			TThread::Synchronize(mainForm->myCommandCreatorThread,StepperRetract);
		}
		else{
			Mode = 0;
			StateM = 1;
			SShift = false;

			TThread::Synchronize(mainForm->myCommandCreatorThread,StepperRetract);
		}
	}
	else
	{
		if (AStepper)
		{
			if ((Button == mbLeft) && (Shift.ToInt() == ssShift || FastCoarse)){
				Mode = 2;
				StateM = 1;
				SShift = true;

				TThread::Synchronize(mainForm->myCommandCreatorThread,StepperRetract);
			}
			else{
				Mode = 2;
				StateM = 1;
				SShift = false;

				TThread::Synchronize(mainForm->myCommandCreatorThread,StepperRetract);
			}
		}
		if (BStepper)
		{
			if ((Button == mbLeft) && (Shift.ToInt() == ssShift || FastCoarse)){
				Mode = 3;
				StateM = 1;
				SShift = true;

				TThread::Synchronize(mainForm->myCommandCreatorThread,StepperRetract);
			}
			else {
				Mode = 3;
				StateM = 1;
				SShift = false;

				TThread::Synchronize(mainForm->myCommandCreatorThread,StepperRetract);
			}
		}
		if (CStepper)
		{
			if ((Button == mbLeft) && (Shift.ToInt() == ssShift || FastCoarse)){
				Mode = 4;
				StateM = 1;
				SShift = true;

				TThread::Synchronize(mainForm->myCommandCreatorThread,StepperRetract);
			}
			else{
				Mode = 4;
				StateM = 1;
				SShift = false;

				TThread::Synchronize(mainForm->myCommandCreatorThread,StepperRetract);
			}
		}
	}
}
//---------------------------------------------------------------------------

void __fastcall TMvFrm::UpButtonMouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift,
		  int X, int Y)
{
	mainForm->LogToFile("TMvFrm::UpButtonMouseUp");
    mainForm->StageMoving = false;
	mainForm->GetSecure();
//	mainForm->LogToFile("up button stop");
	UpCoarseButton->Picture = UpCoarsePic;
	UpDownBorder(UpCoarseButton->Appearance,true);
	Mode = 1;
	StateM = 0;
	SShift = false;

	TThread::Synchronize(mainForm->myCommandCreatorThread,StepperRetract);
}
//---------------------------------------------------------------------------

void __fastcall TMvFrm::DownButtonMouseDown(TObject *Sender, TMouseButton Button,
		  TShiftState Shift, int X, int Y)
{
	mainForm->LogToFile("TMvFrm::DownButtonMouseDown");
//	mainForm->LogToFile("down button start");
	mainForm->StageMoving = true;
	mainForm->GetSecure();
	DownCoarseButton->Picture = DownCoarsePicHover;
	UpDownBorder(DownCoarseButton->Appearance,false);
	if (AllStepper){
		if( (Button == mbLeft) && (Shift.ToInt() == ssShift || FastCoarse) ){
			Mode = 0;
			StateM = 0;
			SShift = true;

			TThread::Synchronize(mainForm->myCommandCreatorThread,StepperRetract);
		}
		else{
			Mode = 0;
			StateM = 0;
			SShift = false;

			TThread::Synchronize(mainForm->myCommandCreatorThread,StepperRetract);
		}
	}
	else
	{
		if (AStepper)
		{
			if ((Button == mbLeft) && (Shift.ToInt() == ssShift || FastCoarse)){
				Mode = 2;
				StateM = 0;
				SShift = true;

				TThread::Synchronize(mainForm->myCommandCreatorThread,StepperRetract);
			}
			else{
				Mode = 2;
				StateM = 0;
				SShift = false;

				TThread::Synchronize(mainForm->myCommandCreatorThread,StepperRetract);
			}
		}
		if (BStepper)
		{
			if ((Button == mbLeft) && (Shift.ToInt() == ssShift || FastCoarse)){
				Mode = 3;
				StateM = 0;
				SShift = true;

				TThread::Synchronize(mainForm->myCommandCreatorThread,StepperRetract);
			}
			else {
				Mode = 3;
				StateM = 0;
				SShift = false;

				TThread::Synchronize(mainForm->myCommandCreatorThread,StepperRetract);
			}
		}
		if (CStepper)
		{
			if ((Button == mbLeft) && (Shift.ToInt() == ssShift || FastCoarse)){
				Mode = 4;
				StateM = 0;
				SShift = true;

				TThread::Synchronize(mainForm->myCommandCreatorThread,StepperRetract);
			}
			else{
				Mode = 4;
				StateM = 0;
				SShift = false;

				TThread::Synchronize(mainForm->myCommandCreatorThread,StepperRetract);
			}
		}
	}
}
//---------------------------------------------------------------------------

void __fastcall TMvFrm::DownButtonMouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift,
		  int X, int Y)
{
	mainForm->LogToFile("TMvFrm::DownButtonMouseUp");
//	mainForm->LogToFile("down button stop");
    mainForm->StageMoving = false;
	mainForm->GetSecure();
	DownCoarseButton->Picture = DownCoarsePic;
	UpDownBorder(DownCoarseButton->Appearance,true);
	Mode = 1;
	StateM = 0;
	SShift = false;

	TThread::Synchronize(mainForm->myCommandCreatorThread,StepperRetract);
}
//---------------------------------------------------------------------------



void TMvFrm::EnabledMoving(bool enabled)
{
	mainForm->LogToFile("TMvFrm::EnabledMoving , enabled = " +BoolToStr(enabled,true));
	if(enabled)
		CoarsePanel->Enabled = true;
	else
		CoarsePanel->Enabled = false;
}
//---------------------------------------------------------------------------



void __fastcall TMvFrm::FormShow(TObject *Sender)
{
	if(!first){
		first = true;

		int w_this = mainForm->myMainControlPanelForm->MainPanel->Width;
		int h_this = mainForm->myMainControlPanelForm->MainPanel->Height;


		CoarsePanel->Height = ( h_this / (double)2 );


		int w_1 = w_this;
		int h_1 = CoarsePanel->Height;

		PanelSubCoarse->Left = 20;
		PanelSubCoarse->Top = 20;
		PanelSubCoarse->Width = w_1 - 40;
		PanelSubCoarse->Height = h_1 - 40;

		int L_1 = PanelSubCoarse->Width;
		int L_2 = PanelSubCoarse->Height - PanelLabelCoarse->Height;
		int top_1 = PanelLabelCoarse->Height;


		PanelShape->Left = 10;
		PanelShape->Top = top_1 + 10;
		PanelShape->Width = L_1/3 - 20;
		PanelShape->Height = L_2 - 20;

		int h = PanelShape->Height;
		int w = PanelShape->Width;
		CreateStepperPanel(h,w);

		PanelUpDown->Width = L_1/3 - 20;
		PanelUpDown->Height = L_2 - 20;
		PanelUpDown->Left =  L_1/3 + 10;
		PanelUpDown->Top = top_1 + 10;

		FastCoarseButton->Left = PanelUpDown->Width/2 - FastCoarseButton->Height/2;
		FastCoarseButton->Top = PanelUpDown->Height/2 - FastCoarseButton->Height;
		UpCoarseButton->Left = FastCoarseButton->Left;
		UpCoarseButton->Top = PanelUpDown->Width/2;
		DownCoarseButton->Left =  FastCoarseButton->Left + FastCoarseButton->Width - DownCoarseButton->Width;
		DownCoarseButton->Top = UpCoarseButton->Top;

		PanelUp->Left = L_1 - 20 - PanelUp->Width;
		PanelUp->Top = top_1 + L_2/2 - PanelUp->Height/2;


		PanelSubStage->Width = PanelSubCoarse->Width/2;
		PanelSubStage->Height = PanelSubCoarse->Height;
		PanelSubStage->Left = w_1/2 - PanelSubStage->Width/2;
		PanelSubStage->Top = PanelSubCoarse->Top;

		FastStageButton->Left = PanelSubStage->Width - 10 - FastStageButton->Width;
		FastStageButton->Top = PanelSubStage->Height - 10 - FastStageButton->Height;

		LeftNumber->Left = 10;
		LeftNumber->Top = top_1 + L_2/2 - LeftNumber->Height/2;
		LeftButton->Left = LeftNumber->Left + LeftNumber->Width + 3;
		LeftButton->Top = top_1 + L_2/2 - LeftButton->Height/2;

		RightNumber->Left = PanelSubStage->Width - 10 - RightNumber->Width;
		RightNumber->Top = LeftNumber->Top;
		RightButton->Left = RightNumber->Left - RightButton->Width - 3;
		RightButton->Top = LeftButton->Top;

		FrontNumber->Left = PanelSubStage->Width/2 - FrontNumber->Width/2;
		FrontNumber->Top = top_1 + 10;
		FrontButton->Left = PanelSubStage->Width/2 - FrontButton->Width/2;
		FrontButton->Top = FrontNumber->Top + FrontNumber->Height + 3;

		BackNumber->Left = FrontNumber->Left;
		BackNumber->Top = top_1 + L_2 - 10 - BackNumber->Height;
		BackButton->Left = FrontButton->Left;
		BackButton->Top = BackNumber->Top - BackButton->Height  - 3;

		LoadPictures();
	}
}
//---------------------------------------------------------------------------

void TMvFrm::CreateStepperPanel(int h, int w)
{
//	mainForm->LogToFile("**********************************************************h = " + IntToStr(h)+" , w = " + IntToStr(w));
	ImageTriangle->Canvas->Brush->Color = TColor(0x00614438);
	ImageTriangle->Canvas->Pen->Color = TColor(0x00614438);
	ImageTriangle->Canvas->Rectangle(0,0,w,h);

	ImageTriangle->Canvas->Brush->Color = TColor(0x00614438);
	ImageTriangle->Canvas->Pen->Color = clWhite;
	ImageTriangle->Canvas->Pen->Width = 1;

	TPoint points[3];
	points[0] = TPoint(15,h-15);
	points[1] = TPoint(15,15);
	points[2] = TPoint(w-15,h/2);

	ImageTriangle->Canvas->Pen->Width = 1;
	ImageTriangle->Canvas->Polygon(points,3);

	DBAdvGlowButtonB->Top = 0;
	DBAdvGlowButtonB->Left = 0;

	DBAdvGlowButtonC->Top = h-30;
	DBAdvGlowButtonC->Left = 0;

	DBAdvGlowButtonA->Top = h/2-15;
	DBAdvGlowButtonA->Left = w - 30;

	DBAdvGlowButtonAll->Top = h/2-15;
	DBAdvGlowButtonAll->Left = w/2-30;

	PanelShape->BringToFront();
}
//---------------------------------------------------------------------------

void TMvFrm::LoadPictures()
{
	StepperPic = new TGDIPPicture;
	StepperPic->LoadFromFile("./Resources/Images/MOV_Form/circle.png");

	StepperPicHover = new TGDIPPicture;
	StepperPicHover->LoadFromFile(MainPath + "/Resources/Images/MOV_Form/circle_hover.png");

	CenterPic = new TGDIPPicture;
	CenterPic->LoadFromFile(MainPath + "/Resources/Images/MOV_Form/center.png");

	CenterPicHover = new TGDIPPicture;
	CenterPicHover->LoadFromFile(MainPath + "/Resources/Images/MOV_Form/center_hover.png");

	UpPic = new TGDIPPicture;
	UpPic->LoadFromFile(MainPath + "/Resources/Images/MOV_Form/uparrow.png");

	UpPicHover = new TGDIPPicture;
	UpPicHover->LoadFromFile(MainPath + "/Resources/Images/MOV_Form/uparrow_hover.png");

	DownPic = new TGDIPPicture;
	DownPic->LoadFromFile(MainPath + "/Resources/Images/MOV_Form/downarrow.png");

	DownPicHover = new TGDIPPicture;
	DownPicHover->LoadFromFile(MainPath + "/Resources/Images/MOV_Form/downarrow_hover.png");

	LeftPic = new TGDIPPicture;
	LeftPic->LoadFromFile(MainPath + "/Resources/Images/MOV_Form/leftarrow.png");

	LeftPicHover = new TGDIPPicture;
	LeftPicHover->LoadFromFile(MainPath + "/Resources/Images/MOV_Form/leftarrow_hover.png");

	RightPic = new TGDIPPicture;
	RightPic->LoadFromFile(MainPath + "/Resources/Images/MOV_Form/rightarrow.png");

	RightPicHover = new TGDIPPicture;
	RightPicHover->LoadFromFile(MainPath + "/Resources/Images/MOV_Form/rightarrow_hover.png");


	UpCoarsePic = new TGDIPPicture;
	UpCoarsePic->LoadFromFile(MainPath + "/Resources/Images/MOV_Form/coarse_up.png");

	UpCoarseHover = new TGDIPPicture;
	UpCoarseHover->LoadFromFile(MainPath + "/Resources/Images/MOV_Form/coarse_up_hover.png");

	DownCoarsePic = new TGDIPPicture;
	DownCoarsePic->LoadFromFile(MainPath + "/Resources/Images/MOV_Form/coarse_down.png");

	DownCoarsePicHover = new TGDIPPicture;
	DownCoarsePicHover->LoadFromFile(MainPath + "/Resources/Images/MOV_Form/coarse_down_hover.png");

	AStepper = false;
	BStepper = false;
	CStepper = false;
	AllStepper = false;
}
//---------------------------------------------------------------------------


void __fastcall TMvFrm::DBAdvGlowButtonAClick(TObject *Sender)
{
	mainForm->LogToFile("TMvFrm::DBAdvGlowButtonAClick , AStepper = " +BoolToStr(AStepper,true));
	if(AStepper){
		if(!AllStepper){
			AStepper = false;
			DBAdvGlowButtonA->Picture = StepperPic;
			AllStepper = false;
			DBAdvGlowButtonAll->Picture = CenterPic;
        }

	}
	else{
		AStepper = true;
		DBAdvGlowButtonA->Picture = StepperPicHover;
		if(AStepper && BStepper && CStepper){
			AllStepper = true;
			DBAdvGlowButtonAll->Picture = CenterPic;
		}
		else{
			BStepper = false;
			CStepper = false;
			DBAdvGlowButtonC->Picture = StepperPic;
			DBAdvGlowButtonB->Picture = StepperPic;
		}
	}
}
//---------------------------------------------------------------------------



void __fastcall TMvFrm::DBAdvGlowButtonCClick(TObject *Sender)
{
	mainForm->LogToFile("TMvFrm::DBAdvGlowButtonCClick , CStepper = " +BoolToStr(CStepper,true));
	if(CStepper){
		if(!AllStepper){
			CStepper = false;
			DBAdvGlowButtonC->Picture = StepperPic;
			AllStepper = false;
			DBAdvGlowButtonAll->Picture = CenterPic;
		}
	}
	else{
		CStepper = true;
		DBAdvGlowButtonC->Picture = StepperPicHover;
		if(AStepper && BStepper && CStepper){
			AllStepper = true;
			DBAdvGlowButtonAll->Picture = CenterPicHover;
		}
		else{
			BStepper = false;
			AStepper = false;
			DBAdvGlowButtonA->Picture = StepperPic;
			DBAdvGlowButtonB->Picture = StepperPic;
		}
	}
}
//---------------------------------------------------------------------------

void __fastcall TMvFrm::DBAdvGlowButtonBClick(TObject *Sender)
{
	mainForm->LogToFile("TMvFrm::DBAdvGlowButtonBClick , BStepper = " +BoolToStr(BStepper,true));
	if(BStepper){
		if(!AllStepper){
			BStepper = false;
			DBAdvGlowButtonB->Picture = StepperPic;
			AllStepper = false;
			DBAdvGlowButtonAll->Picture = CenterPic;
		}

	}
	else{
		BStepper = true;
		DBAdvGlowButtonB->Picture = StepperPicHover;
		if(AStepper && BStepper && CStepper){
			AllStepper = true;
			DBAdvGlowButtonAll->Picture = CenterPicHover;
		}
		else{
			AStepper = false;
			CStepper = false;
			DBAdvGlowButtonC->Picture = StepperPic;
			DBAdvGlowButtonA->Picture = StepperPic;
		}
	}
}
//---------------------------------------------------------------------------

void __fastcall TMvFrm::DBAdvGlowButtonAllClick(TObject *Sender)
{
	mainForm->LogToFile("TMvFrm::DBAdvGlowButtonAllClick , AllStepper = " +BoolToStr(AllStepper,true));
	if(AllStepper){
		AllStepper = false;
		DBAdvGlowButtonAll->Picture = CenterPic;

		DBAdvGlowButtonA->Picture = StepperPic;
		AStepper = false;

		DBAdvGlowButtonB->Picture = StepperPic;
		BStepper = false;

		DBAdvGlowButtonC->Picture = StepperPic;
		CStepper = false;
	}
	else{
		AllStepper = true;
		DBAdvGlowButtonAll->Picture = CenterPicHover;

		DBAdvGlowButtonA->Picture = StepperPicHover;
		AStepper = true;

		DBAdvGlowButtonB->Picture = StepperPicHover;
		BStepper = true;

		DBAdvGlowButtonC->Picture = StepperPicHover;
		CStepper = true;
	}
}
//---------------------------------------------------------------------------


void __fastcall TMvFrm::LeftButtonMouseDown(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y)
{
	mainForm->LogToFile("TMvFrm::LeftButtonMouseDown");
	mainForm->CameraMoving = true;
	mainForm->GetSecure();
	LeftButton->Picture = LeftPicHover;
	UpDownBorder(LeftButton->Appearance,false);
	if ( (Button == mbLeft) && (Shift.ToInt() == ssShift || FastStage) )
		mainForm->myVideoForm->SShift = true;
	else
		mainForm->myVideoForm->SShift = false;
	mainForm->myVideoForm->Left_start();
}
//---------------------------------------------------------------------------

void __fastcall TMvFrm::LeftButtonMouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift,
		  int X, int Y)
{
	mainForm->LogToFile("TMvFrm::LeftButtonMouseUp");
	mainForm->CameraMoving = false;
	mainForm->GetSecure();
	LeftButton->Picture = LeftPic;
	UpDownBorder(LeftButton->Appearance,true);
	mainForm->myVideoForm->Left_stop();
}
//---------------------------------------------------------------------------

void __fastcall TMvFrm::RightButtonMouseDown(TObject *Sender, TMouseButton Button,
		  TShiftState Shift, int X, int Y)
{
	mainForm->LogToFile("TMvFrm::RightButtonMouseDown");
	mainForm->CameraMoving = true;
	mainForm->GetSecure();
	RightButton->Picture = RightPicHover;
	UpDownBorder(RightButton->Appearance,false);
	if ( (Button == mbLeft) && (Shift.ToInt() == ssShift || FastStage) )
		mainForm->myVideoForm->SShift = true;
	else
		mainForm->myVideoForm->SShift = false;
	mainForm->myVideoForm->Right_start();
}
//---------------------------------------------------------------------------

void __fastcall TMvFrm::RightButtonMouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y)
{
	mainForm->LogToFile("TMvFrm::RightButtonMouseUp");
	mainForm->CameraMoving = false;
	mainForm->GetSecure();
	RightButton->Picture = RightPic;
	UpDownBorder(RightButton->Appearance,true);
	mainForm->myVideoForm->Right_stop();
}
//---------------------------------------------------------------------------

void __fastcall TMvFrm::FrontButtonMouseDown(TObject *Sender, TMouseButton Button,
		  TShiftState Shift, int X, int Y)
{
	mainForm->LogToFile("TMvFrm::FrontButtonMouseDown");
	mainForm->CameraMoving = true;
	mainForm->GetSecure();
	FrontButton->Picture = UpPicHover;
	UpDownBorder(FrontButton->Appearance,false);
	if ( (Button == mbLeft) && (Shift.ToInt() == ssShift || FastStage) )
		mainForm->myVideoForm->SShift = true;
	else
		mainForm->myVideoForm->SShift = false;
	mainForm->myVideoForm->Front_start();
}
//---------------------------------------------------------------------------

void __fastcall TMvFrm::FrontButtonMouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y)
{
	mainForm->LogToFile("TMvFrm::FrontButtonMouseUp");
	mainForm->CameraMoving = false;
	mainForm->GetSecure();
	FrontButton->Picture = UpPic;
	UpDownBorder(FrontButton->Appearance,true);
	mainForm->myVideoForm->Front_stop();
}
//---------------------------------------------------------------------------

void __fastcall TMvFrm::BackButtonMouseDown(TObject *Sender, TMouseButton Button,
		  TShiftState Shift, int X, int Y)
{
	mainForm->LogToFile("TMvFrm::BackButtonMouseDown");
	mainForm->CameraMoving = true;
	mainForm->GetSecure();
	BackButton->Picture = DownPicHover;
	UpDownBorder(BackButton->Appearance,false);
	if ( (Button == mbLeft) && (Shift.ToInt() == ssShift || FastStage) )
		mainForm->myVideoForm->SShift = true;
	else
		mainForm->myVideoForm->SShift = false;
	mainForm->myVideoForm->Back_start();
}
//---------------------------------------------------------------------------

void __fastcall TMvFrm::BackButtonMouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y)
{
	mainForm->LogToFile("TMvFrm::BackButtonMouseUp");
	mainForm->CameraMoving = false;
	mainForm->GetSecure();
	BackButton->Picture = DownPic;
	UpDownBorder(BackButton->Appearance,true);
	mainForm->myVideoForm->Back_stop();
}
//---------------------------------------------------------------------------

void TMvFrm::UpDownBorder(TGlowButtonAppearance* appearance, bool UpDown)
{

	if(UpDown){
		appearance->BorderColor = TColor(0x00614438);
		appearance->BorderColorHot = TColor(0x00614438);
		appearance->BorderColorChecked = TColor(0x00614438);
		appearance->BorderColorCheckedHot = TColor(0x00614438);
		appearance->BorderColorDisabled = TColor(0x00614438);
		appearance->BorderColorFocused = TColor(0x00614438);
		appearance->BorderColorDown = TColor(0x00614438);
	}
	else{
		appearance->BorderColor = TColor(0x00F0D27D);
		appearance->BorderColorHot = TColor(0x00F0D27D);
		appearance->BorderColorChecked = TColor(0x00F0D27D);
		appearance->BorderColorCheckedHot = TColor(0x00F0D27D);
		appearance->BorderColorDisabled = TColor(0x00F0D27D);
		appearance->BorderColorFocused = TColor(0x00F0D27D);
		appearance->BorderColorDown = TColor(0x00F0D27D);
	}
}
//---------------------------------------------------------------------------



void __fastcall TMvFrm::DBAdvGlowButtonRetractClick(TObject *Sender)
{
	mainForm->LogToFile("TMvFrm::DBAdvGlowButtonRetractClick");
	mainForm->myControlPanelForm->DBAdvGlowButtonRetractClick(NULL);
}
//---------------------------------------------------------------------------

void __fastcall TMvFrm::FastStageButtonClick(TObject *Sender)
{
	mainForm->LogToFile("TMvFrm::FastStageButtonClick , FastStage = " + BoolToStr(FastStage,true));
	if(FastStage){
		FastStage = false;
		FastStageButton->Appearance->BorderColor = TColor(0x008B6757);
		FastStageButton->Font->Color = clWhite;
	}
	else{
		FastStage = true;
		FastStageButton->Appearance->BorderColor = TColor(0x00F0D27D);
		FastStageButton->Font->Color = TColor(0x00F0D27D);
	}
}
//---------------------------------------------------------------------------

void __fastcall TMvFrm::FastCoarseButtonClick(TObject *Sender)
{
	mainForm->LogToFile("TMvFrm::FastCoarseButtonClick , FastStage = " + BoolToStr(FastStage,true));
	if(FastCoarse){
		FastCoarse = false;
		FastCoarseButton->Appearance->BorderColor = TColor(0x008B6757);
		FastCoarseButton->Font->Color = clWhite;
	}
	else{
		FastCoarse = true;
		FastCoarseButton->Appearance->BorderColor = TColor(0x00F0D27D);
		FastCoarseButton->Font->Color = TColor(0x00F0D27D);
	}
}
//---------------------------------------------------------------------------




void __fastcall TMvFrm::AdvEditUpKeyPress(TObject *Sender, System::WideChar &Key)

{
	mainForm->myControlPanelForm->Num = AdvEditUp->Text.ToInt();
	mainForm->myControlPanelForm->Status = 1;
	mainForm->myControlPanelForm->DownUp = true;
    mainForm->myControlPanelForm->RetDownUp();
}
//---------------------------------------------------------------------------



