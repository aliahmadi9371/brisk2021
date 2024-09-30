//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "PiezoForm.h"
#include "defines.h"
#include "mainUnit.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "VCLTee.TeeLinearGauge"
#pragma link "VCLTee.TeeNumericGauge"
#pragma resource "*.dfm"
TPiezoFrm *PiezoFrm;
//---------------------------------------------------------------------------
__fastcall TPiezoFrm::TPiezoFrm(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TPiezoFrm::FormCreate(TObject *Sender)
{
	this->Hide();
	first = false;
	PizoState = -1;
	Tmp = 0;
	LastTmp = -1;
//	PiezoChart->ClipPoints = false;
//	PiezoChart->Title->Caption = "Piezo";
//	PiezoChart->Title->Visible = true;
//	PiezoChart->Legend->Visible = false;
//	PiezoChart->LeftAxis->Automatic = false;
//	PiezoChart->LeftAxis->SetMinMax(0,100);
//	PiezoChart->LeftAxis->Axis->Width = 1;
//	PiezoChart->BottomAxis->Axis->Width = 1;
//	PiezoChart->BottomAxis->RoundFirstLabel = false;
//	PiezoChart->BottomAxis->Automatic = false;
//	PiezoChart->View3D = false;
//	PiezoChart->Axes->FastCalc = true;
//	PiezoChart->AutoRepaint = true;
//	PiezoChart->Canvas->ReferenceCanvas->Pen->OwnerCriticalSection = NULL;
//	PiezoChart->Hover->Visible = false;
//
//	PiezoSeries->AddXY(0,0);
	LabelPiezoValue->Caption = 0;

	LoadPicture();
}
//---------------------------------------------------------------------------

void TPiezoFrm::ModifyPiezo(int value)
{
	LastTmp = Tmp;
	Tmp = floor(((double)100 * (double)((double)(MAX_VALUE) - (double)value ) / (double)(MAX_MAX))+0.5)  ;
	int L =  Tmp/(double)100 * L2;


//	Image1->Top = zero - L/2 - Image1->Height;

	Image2->Top = Image1->Top + Image1->Height + L;


	if(LastTmp != Tmp){

		LabelPiezoValue->Caption = "% " + IntToStr(100 - Tmp);

//		if((Tmp >= 90 || Tmp <= 10) && mainForm->Scaning && (mainForm->AppMode == 3 || mainForm->AppMode == 4)){
//            mainForm->myControlPanelForm->DBAdvGlowButtonScanClick(NULL);
//		}

		if(Tmp >= 0 && Tmp <= 10 && PizoState != 0){
			PizoState = 0;
//			mainForm->LogToFile("PizoState = " + IntToStr(PizoState));
			Image1->Picture = YellowPicPeizo;
			Image2->Picture = YellowPicGround;
			Shape2->Pen->Color = TColor(0x001AC2DD);
			Shape1->Pen->Color = TColor(0x001AC2DD);
		}
		else if(Tmp > 10 && Tmp < 90 && PizoState != 1){
			PizoState = 1;
//			mainForm->LogToFile("PizoState = " + IntToStr(PizoState));
			Image1->Picture = GreenPicPeizo;
			Image2->Picture = GreenPicGround;
			Shape2->Pen->Color = TColor(0x004EDD1A);
			Shape1->Pen->Color = TColor(0x004EDD1A);
		}
		else if(Tmp >= 90 && PizoState != 2){
			PizoState = 2;
//            mainForm->LogToFile("PizoState = " + IntToStr(PizoState));
			Image1->Picture = RedPicPeizo;
			Image2->Picture = RedPicGround;
			Shape2->Pen->Color = TColor(0x003F3FE4);
			Shape1->Pen->Color = TColor(0x003F3FE4);
		}

////		mainForm->LogToFile("Tmp = " + IntToStr(Tmp));
//		if( (mainForm->AppMode == 1 || mainForm->AppMode == 5 || mainForm->AppMode == 7) && mainForm->Approaching && Tmp >= 98){
//			mainForm->LogToFile("Update Tb..........................");
//			mainForm->myCommandCreatorThread->UpdateTB = true;
//			mainForm->myCommandCreatorThread->StartApprochClick(1,1,0,0,0,0);
//			mainForm->myCommandCreatorThread->UpdateTB = false;
//		}
	}

//	Shape2->Left = Image2->Width/2 - Shape2->Width/2;
	Shape2->Top = Image2->Top + Image2->Height - 5;
}
//---------------------------------------------------------------------------

void __fastcall TPiezoFrm::FormShow(TObject *Sender)
{
	if(!first){
		first = true;

		width = mainForm->ptz_sub_pnl->Width;
		height = mainForm->ptz_sub_pnl->Height;

		PenWidth = Shape1->Pen->Width;

		L1 = width - PenWidth * 2;
		LabelPiezoValue->Width = L1 - PenWidth * 2;
		LabelPiezoValue->Top = 0 + PenWidth * 2;
		LabelPiezoValue->Left = 0 + PenWidth * 2;

		Image1->Left = 0;
		Image1->Top = LabelPiezoValue->Top + LabelPiezoValue->Height + PenWidth * 2;

		Image1->Width = width;

		Image2->Width = width;

		Image2->Left = 0;
		Image2->Top =  height - PenWidth * 3 - Image2->Height;

		buttom = height;

		L2 = Image2->Top - (Image1->Top + Image1->Height);
		zero = Image2->Top - L2/2;


		Shape2->Left = Image2->Width/2 - Shape2->Width/2;
		Shape2->Top = Image2->Top + Image2->Height - 5;
		Shape2->Height = buttom;
//		Shape2->Height = zero +

//		mainForm->LogToFile("width = " + IntToStr(width));
//		mainForm->LogToFile("height = " + IntToStr(height));
//		mainForm->LogToFile("PenWidth = " + IntToStr(PenWidth));
//		mainForm->LogToFile("L1 = " + IntToStr(L1));
//		mainForm->LogToFile("L2 = " + IntToStr(L2));


		all_scale = OscChartTable.all_scale;

	}
}
//---------------------------------------------------------------------------

void TPiezoFrm::LoadPicture()
{
	GreenPicGround = new TPicture;
	GreenPicGround->LoadFromFile(MainPath + "/Resources/Images/PIEZ_Form/ground_green.png");

	OrangePicGround = new TPicture;
	OrangePicGround->LoadFromFile(MainPath + "/Resources/Images/PIEZ_Form/ground_orange.png");

	YellowPicGround = new TPicture;
	YellowPicGround->LoadFromFile(MainPath + "/Resources/Images/PIEZ_Form/ground_yellow.png");

	RedPicGround = new TPicture;
	RedPicGround->LoadFromFile(MainPath + "/Resources/Images/PIEZ_Form/ground_red.png");

	GreenPicPeizo = new TPicture;
	GreenPicPeizo->LoadFromFile(MainPath + "/Resources/Images/PIEZ_Form/opizo_green.png");

	OrangePicPeizo = new TPicture;
	OrangePicPeizo->LoadFromFile(MainPath + "/Resources/Images/PIEZ_Form/opizo_orange.png");

	YellowPicPeizo = new TPicture;
	YellowPicPeizo->LoadFromFile(MainPath + "/Resources/Images/PIEZ_Form/opizo_yellow.png");

	RedPicPeizo = new TPicture;
	RedPicPeizo->LoadFromFile(MainPath + "/Resources/Images/PIEZ_Form/opizo_red.png");

}
//---------------------------------------------------------------------------

//#1ADD4E
//green code
//0x004EDD1A

//#E43F3F
//red code
//0x003F3FE4

//#DC7E2D
//orange code
//0x002D7EDC

//#DDC21A
//yellow code
//0x001AC2DD



