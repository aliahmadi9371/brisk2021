//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "ImgClass.h"
#include "mainUnit.h"
#include "globals.h"
//---------------------------------------------------------------------------
#pragma link "AdvLabel"
#pragma link "VCLTee.TeeTools"
#pragma link "VCLTee.TeeSeriesBandTool"
#pragma link "FolderDialog"
#pragma link "AdvGlowButton"
#pragma resource "*.dfm"
TImgForm *ImgForm;
//---------------------------------------------------------------------------
__fastcall TImgForm::TImgForm(TComponent* Owner)
	: TForm(Owner)
{

}
//---------------------------------------------------------------------------

void TImgForm::ShowImageNumber()
{
//	mainForm->LogToFile("change image");
	//bvRaised
	//bsSingle
	Panel1->BevelOuter = bvNone;
	Panel2->BevelOuter = bvNone;
	Panel3->BevelOuter = bvNone;
	Panel4->BevelOuter = bvNone;
	Panel5->BevelOuter = bvNone;
	Panel6->BevelOuter = bvNone;
	Panel7->BevelOuter = bvNone;
	Panel8->BevelOuter = bvNone;
	Panel9->BevelOuter = bvNone;
	Panel10->BevelOuter = bvNone;
	Panel11->BevelOuter = bvNone;
	Panel12->BevelOuter = bvNone;
	Panel13->BevelOuter = bvNone;
	Panel14->BevelOuter = bvNone;
	Panel15->BevelOuter = bvNone;
	Panel16->BevelOuter = bvNone;
	Panel17->BevelOuter = bvNone;
	Panel18->BevelOuter = bvNone;
	Panel19->BevelOuter = bvNone;
	Panel20->BevelOuter = bvNone;
	Panel21->BevelOuter = bvNone;
	Panel22->BevelOuter = bvNone;
	Panel23->BevelOuter = bvNone;
	Panel24->BevelOuter = bvNone;
	Panel25->BevelOuter = bvNone;
	Panel26->BevelOuter = bvNone;
	Panel27->BevelOuter = bvNone;
	Panel28->BevelOuter = bvNone;
	Panel29->BevelOuter = bvNone;
	Panel30->BevelOuter = bvNone;
	Panel31->BevelOuter = bvNone;
	Panel32->BevelOuter = bvNone;
	Panel33->BevelOuter = bvNone;
	Panel34->BevelOuter = bvNone;
//
//	Panel1->BorderStyle = Advshape::bsNone;
//	Panel2->BorderStyle = Advshape::bsNone;
//	Panel3->BorderStyle = Advshape::bsNone;
//	Panel4->BorderStyle = Advshape::bsNone;
//	Panel5->BorderStyle = Advshape::bsNone;
//	Panel6->BorderStyle = Advshape::bsNone;
//	Panel7->BorderStyle = Advshape::bsNone;
//	Panel8->BorderStyle = Advshape::bsNone;
//	Panel9->BorderStyle = Advshape::bsNone;
//	Panel10->BorderStyle = Advshape::bsNone;
//	Panel11->BorderStyle = Advshape::bsNone;
//	Panel12->BorderStyle = Advshape::bsNone;
//	Panel13->BorderStyle = Advshape::bsNone;
//	Panel14->BorderStyle = Advshape::bsNone;
//	Panel15->BorderStyle = Advshape::bsNone;
//	Panel16->BorderStyle = Advshape::bsNone;
//	Panel17->BorderStyle = Advshape::bsNone;
//	Panel18->BorderStyle = Advshape::bsNone;
//	Panel19->BorderStyle = Advshape::bsNone;
//	Panel20->BorderStyle = Advshape::bsNone;
//	Panel21->BorderStyle = Advshape::bsNone;
//	Panel22->BorderStyle = Advshape::bsNone;
//	Panel23->BorderStyle = Advshape::bsNone;
//	Panel24->BorderStyle = Advshape::bsNone;
//	Panel25->BorderStyle = Advshape::bsNone;
//	Panel26->BorderStyle = Advshape::bsNone;
//	Panel27->BorderStyle = Advshape::bsNone;
//	Panel28->BorderStyle = Advshape::bsNone;
//	Panel29->BorderStyle = Advshape::bsNone;
//	Panel30->BorderStyle = Advshape::bsNone;
//	Panel31->BorderStyle = Advshape::bsNone;
//	Panel32->BorderStyle = Advshape::bsNone;
//	Panel33->BorderStyle = Advshape::bsNone;
//	Panel34->BorderStyle = Advshape::bsNone;


	switch(IamgeIndex){
		case 1:{
			Panel1->BevelOuter = bvRaised;
//			Panel1->BorderStyle = Vcl::Forms::bsSingle;
			MainImage->Picture = Image1->Picture;
			break;
		}
		case 2:{
			Panel2->BevelOuter = bvRaised;
//			Panel2->BorderStyle = Vcl::Forms::bsSingle;
			MainImage->Picture = Image2->Picture;
			break;
		}
		case 3:{
			Panel3->BevelOuter = bvRaised;
//			Panel3->BorderStyle = Vcl::Forms::bsSingle;
			MainImage->Picture = Image3->Picture;
			break;
		}
		case 4:{
			Panel4->BevelOuter = bvRaised;
//			Panel4->BorderStyle = Vcl::Forms::bsSingle;
			MainImage->Picture = Image4->Picture;
			break;
		}
		case 5:{
			Panel5->BevelOuter = bvRaised;
//			Panel5->BorderStyle = Vcl::Forms::bsSingle;
			MainImage->Picture = Image5->Picture;
			break;
		}
		case 6:{
			Panel6->BevelOuter = bvRaised;
//			Panel6->BorderStyle = Vcl::Forms::bsSingle;
			MainImage->Picture = Image6->Picture;
			break;
		}
		case 7:{
			Panel7->BevelOuter = bvRaised;
//			Panel7->BorderStyle = Vcl::Forms::bsSingle;
			MainImage->Picture = Image7->Picture;
			break;
		}
		case 8:{
			Panel8->BevelOuter = bvRaised;
//			Panel8->BorderStyle = Vcl::Forms::bsSingle;
			MainImage->Picture = Image8->Picture;
			break;
		}
		case 9:{
			Panel9->BevelOuter = bvRaised;
//			Panel9->BorderStyle = Vcl::Forms::bsSingle;
			MainImage->Picture = Image9->Picture;
			break;
		}
		case 10:{
			Panel10->BevelOuter = bvRaised;
//			Panel10->BorderStyle = Vcl::Forms::bsSingle;
			MainImage->Picture = Image10->Picture;
			break;
		}
		case 11:{
			Panel11->BevelOuter = bvRaised;
//			Panel11->BorderStyle = Vcl::Forms::bsSingle;
			MainImage->Picture = Image11->Picture;
			break;
		}
		case 12:{
			Panel12->BevelOuter = bvRaised;
//			Panel12->BorderStyle = Vcl::Forms::bsSingle;
			MainImage->Picture = Image12->Picture;
			break;
		}
		case 13:{
			Panel13->BevelOuter = bvRaised;
//			Panel13->BorderStyle = Vcl::Forms::bsSingle;
			MainImage->Picture = Image13->Picture;
			break;
		}
		case 14:{
			Panel14->BevelOuter = bvRaised;
//			Panel14->BorderStyle = Vcl::Forms::bsSingle;
			MainImage->Picture = Image14->Picture;
			break;
		}
		case 15:{
			Panel15->BevelOuter = bvRaised;
//			Panel15->BorderStyle = Vcl::Forms::bsSingle;
			MainImage->Picture = Image15->Picture;
			break;
		}
		case 16:{
			Panel16->BevelOuter = bvRaised;
//			Panel16->BorderStyle = Vcl::Forms::bsSingle;
			MainImage->Picture = Image16->Picture;
			break;
		}
		case 17:{
			Panel17->BevelOuter = bvRaised;
//			Panel17->BorderStyle = Vcl::Forms::bsSingle;
			MainImage->Picture = Image17->Picture;
			break;
		}
		case 18:{
			Panel18->BevelOuter = bvRaised;
//			Panel18->BorderStyle = Vcl::Forms::bsSingle;
			MainImage->Picture = Image18->Picture;
			break;
		case 19:
			Panel19->BevelOuter = bvRaised;
//			Panel19->BorderStyle = Vcl::Forms::bsSingle;
			MainImage->Picture = Image19->Picture;
			break;
		}
		case 20:{
			Panel20->BevelOuter = bvRaised;
//			Panel20->BorderStyle = Vcl::Forms::bsSingle;
			MainImage->Picture = Image20->Picture;
			break;
		}
		case 21:{
			Panel21->BevelOuter = bvRaised;
//			Panel21->BorderStyle = Vcl::Forms::bsSingle;
			MainImage->Picture = Image21->Picture;
			break;
		}
		case 22:{
			Panel22->BevelOuter = bvRaised;
//			Panel22->BorderStyle = Vcl::Forms::bsSingle;
			MainImage->Picture = Image22->Picture;
			break;
		}
		case 23:{
			Panel23->BevelOuter = bvRaised;
//			Panel23->BorderStyle = Vcl::Forms::bsSingle;
			MainImage->Picture = Image23->Picture;
			break;
		}
		case 24:{
			Panel24->BevelOuter = bvRaised;
//			Panel24->BorderStyle = Vcl::Forms::bsSingle;
			MainImage->Picture = Image24->Picture;
			break;
		}
		case 25:{
			Panel25->BevelOuter = bvRaised;
//			Panel25->BorderStyle = Vcl::Forms::bsSingle;
			MainImage->Picture = Image25->Picture;
			break;
		case 26:
			Panel26->BevelOuter = bvRaised;
//			Panel26->BorderStyle = Vcl::Forms::bsSingle;
			MainImage->Picture = Image26->Picture;
			break;
		}
		case 27:{
			Panel27->BevelOuter = bvRaised;
//			Panel27->BorderStyle = Vcl::Forms::bsSingle;
			MainImage->Picture = Image27->Picture;
			break;
		}
		case 28:{
			Panel28->BevelOuter = bvRaised;
//			Panel28->BorderStyle = Vcl::Forms::bsSingle;
			MainImage->Picture = Image28->Picture;
			break;
		}
		case 29:{
			Panel29->BevelOuter = bvRaised;
//			Panel29->BorderStyle = Vcl::Forms::bsSingle;
			MainImage->Picture = Image29->Picture;
			break;
		}
		case 30:{
			Panel30->BevelOuter = bvRaised;
//			Panel30->BorderStyle = Vcl::Forms::bsSingle;
			MainImage->Picture = Image30->Picture;
			break;
		}
		case 31:{
			Panel31->BevelOuter = bvRaised;
//			Panel31->BorderStyle = Vcl::Forms::bsSingle;
			MainImage->Picture = Image31->Picture;
			break;
		}
		case 32:{
			Panel32->BevelOuter = bvRaised;
//			Panel32->BorderStyle = Vcl::Forms::bsSingle;
			MainImage->Picture = Image32->Picture;
			break;
		}
		case 33:{
			Panel33->BevelOuter = bvRaised;
//			Panel33->BorderStyle = Vcl::Forms::bsSingle;
			MainImage->Picture = Image33->Picture;
			break;
		}
		case 34:{
			Panel34->BevelOuter = bvRaised;
//			Panel34->BorderStyle = Vcl::Forms::bsSingle;
			MainImage->Picture = Image34->Picture;
			break;
		}
		default:{
			break;
		}
	}
}
//---------------------------------------------------------------------------

void __fastcall TImgForm::FormCreate(TObject *Sender)
{
	this->Hide();

	fisrt = false;

    IamgeIndex = 1;
	LastIamgeIndex = 0;
	ChartImage = true;

	ImgPanel->Caption = "";
	CenterPanel->Caption = "";

	set_selcet = false;
	set_force = false;
	select_litho = false;


	ImageNameAdvLabel->Caption = PIC0_FF;

	Timer1->Enabled = false;
	ChartTool2->Active = false;
	ChartTool1->Active = false;

	ScrollBox2->Width = mainForm->ptz_sub_pnl->Width;
	ScrollBox1->Width = ScrollBox2->Width;

	ImageCanvasDraw = false;
	PaintBox1->Canvas->Pen->Width = 2;
	PaintBox1->Canvas->Pen->Color = clWhite;
	PaintBox1->Canvas->Pen->Style = psSolid;


	TopoChart->ScrollMouseButton = mbRight;
	TopoChart->ClipPoints = false;
	TopoChart->Title->Visible = false;
	TopoChart->Legend->Visible = true;
	TopoChart->LeftAxis->Automatic = true;
	TopoChart->LeftAxis->Axis->Width = 1;
	TopoChart->BottomAxis->Axis->Width = 1;
	TopoChart->BottomAxis->RoundFirstLabel = false;
	TopoChart->BottomAxis->Automatic = false;
	TopoChart->View3D = false;
	TopoChart->Axes->FastCalc = true;
	TopoChart->AutoRepaint = true;
	TopoChart->Canvas->ReferenceCanvas->Pen->OwnerCriticalSection = NULL;
	TopoChart->Hover->Visible = false;
	TopoFWSeries->LinePen->OwnerCriticalSection = NULL;
	TopoBWSeries->LinePen->OwnerCriticalSection = NULL;


	for(int i=1; i<35; i++){
		((TImage*)FindComponent("Image"+IntToStr(i)))->Stretch = true;
		((TLabel*)FindComponent("Label"+IntToStr(i)))->Transparent = false;
	}

	TopoChart->Hide();

}
//---------------------------------------------------------------------------



void __fastcall TImgForm::FormShow(TObject *Sender)
{
	if(!fisrt){


		fisrt = true;

		SetAdvGlassButton->Top = ImageNameAdvLabel->Height/2 - SetAdvGlassButton->Height/2;
		SetAdvGlassButton->Left = 5;

		SetFAdvGlassButton->Top = SetAdvGlassButton->Top;
		SetFAdvGlassButton->Left = SetAdvGlassButton->Left + SetAdvGlassButton->Width + 5;

		SaveButton->Top = SetAdvGlassButton->Top;
		SaveButton->Left = CenterPanel->Left + CenterPanel->Width - SaveButton->Width/2;

		SetAdvGlassButton->Enabled = false;
		SetFAdvGlassButton->Enabled = false;

		if(ImgPanel->Width > ImgPanel->Height){
		CenterPanel->Width = ImgPanel->Height - 20;
		CenterPanel->Height = CenterPanel->Width;
		CenterPanel->Top = ImgPanel->Height/2 - CenterPanel->Height/2 + 20;
		CenterPanel->Left = ImgPanel->Width/2 - CenterPanel->Width/2;
		}
		else{
			CenterPanel->Width = ImgPanel->Width - 20 ;
			CenterPanel->Height = CenterPanel->Width;
			CenterPanel->Top = ImgPanel->Height/2 - CenterPanel->Height/2 + 20 - 5;
			CenterPanel->Left = ImgPanel->Width/2 - CenterPanel->Width/2;
		}


		ImageNameAdvLabel->Top = 5;
		ImageNameAdvLabel->Left = 0;
		ImageNameAdvLabel->Height = CenterPanel->Top;
		ImageNameAdvLabel->Width = ImgPanel->Width;

		PanelImageNames->Height = Panel36->Height;

		ChartButton->Height = 30;
		ChartButton->Width = 30;
		ChartButton->Left = 5;
		ChartButton->Top = ImgPanel->Height - 5 - ChartButton->Height;

		switch(mainForm->AppMode)
		{
			case 1:{
//				Panel1->Visible = false;
//				Panel2->Visible = false;
//				Panel3->Visible = false;
//				Panel4->Visible = false;
//				Panel5->Visible = false;
//				Panel6->Visible = false;
				Panel7->Visible = false;
				Panel8->Visible = false;
				Panel9->Visible = false;
				Panel10->Visible = false;
				Panel11->Visible = false;
				Panel12->Visible = false;
				Panel13->Visible = false;
				Panel14->Visible = false;
				Panel15->Visible = false;
				Panel16->Visible = false;
				Panel17->Visible = false;
				Panel18->Visible = false;
				Panel19->Visible = false;
				Panel20->Visible = false;
				Panel21->Visible = false;
				Panel22->Visible = false;
				Panel23->Visible = false;
				Panel24->Visible = false;
				Panel25->Visible = false;
				Panel26->Visible = false;
				Panel27->Visible = false;
				Panel28->Visible = false;
				Panel29->Visible = false;
				Panel30->Visible = false;
				Panel31->Visible = false;
				Panel32->Visible = false;
				Panel33->Visible = false;
				Panel34->Visible = false;

				Panel1->Top = 0;
				Panel2->Top = Panel1->Top + Panel1->Height;
				Panel3->Top = Panel2->Top + Panel2->Height;
				Panel4->Top = Panel7->Top + Panel7->Height;
				Panel5->Top = Panel8->Top + Panel8->Height;
				Panel6->Top = Panel9->Top + Panel9->Height;

				Label1->Caption = PIC0_FF;
				Label2->Caption = PIC0_BB;
				Label3->Caption = PIC1_FF;
				Label4->Caption = PIC1_BB;
				Label5->Caption = PIC2_FF;
				Label6->Caption = PIC2_BB;

				Label1->Left = Panel1->Width/2 - Label1->Width/2;
				Label2->Left = Panel2->Width/2 - Label2->Width/2;
				Label3->Left = Panel3->Width/2 - Label3->Width/2;
				Label4->Left = Panel4->Width/2 - Label4->Width/2;
				Label5->Left = Panel5->Width/2 - Label5->Width/2;
				Label6->Left = Panel6->Width/2 - Label6->Width/2;

				Label1->Top = 0;
				Label2->Top = 0;
				Label3->Top = 0;
				Label4->Top = 0;
				Label5->Top = 0;
				Label6->Top = 0;

				SetFAdvGlassButton->Hide();

//				mainForm->LogToFile("contact image");
				break;
			}

			case 2:{
//				Panel1->Visible = false;
//				Panel2->Visible = false;
				Panel3->Visible = false;
				Panel4->Visible = false;
				Panel5->Visible = false;
				Panel6->Visible = false;
//              Panel7->Visible = false;
//				Panel8->Visible = false;
//				Panel9->Visible = false;
//				Panel10->Visible = false;
				Panel11->Visible = false;
				Panel12->Visible = false;
				Panel13->Visible = false;
				Panel14->Visible = false;
				Panel15->Visible = false;
				Panel16->Visible = false;
				Panel17->Visible = false;
				Panel18->Visible = false;
				Panel19->Visible = false;
				Panel20->Visible = false;
				Panel21->Visible = false;
				Panel22->Visible = false;
				Panel23->Visible = false;
				Panel24->Visible = false;
				Panel25->Visible = false;
				Panel26->Visible = false;
				Panel27->Visible = false;
				Panel28->Visible = false;
				Panel29->Visible = false;
				Panel30->Visible = false;
				Panel31->Visible = false;
				Panel32->Visible = false;
				Panel33->Visible = false;
				Panel34->Visible = false;

				Panel1->Top = 0;
				Panel2->Top = Panel1->Top + Panel1->Height;
				Panel7->Top = Panel2->Top + Panel2->Height;
				Panel8->Top = Panel7->Top + Panel7->Height;
				Panel9->Top = Panel8->Top + Panel8->Height;
				Panel10->Top = Panel9->Top + Panel9->Height;

				Label1->Caption = PIC0_FF;
				Label2->Caption = PIC0_BB;
				Label7->Caption = PIC3_FF;
				Label8->Caption = PIC3_BB;
				Label9->Caption = PIC4_FF;
				Label10->Caption = PIC4_BB;

				Label1->Left = Panel1->Width/2 - Label1->Width/2;
				Label2->Left = Panel2->Width/2 - Label2->Width/2;
				Label7->Left = Panel7->Width/2 - Label7->Width/2;
				Label8->Left = Panel8->Width/2 - Label8->Width/2;
				Label9->Left = Panel9->Width/2 - Label9->Width/2;
				Label10->Left = Panel10->Width/2 - Label10->Width/2;

				Label1->Top = 0;
				Label2->Top = 0;
				Label7->Top = 0;
				Label8->Top = 0;
				Label9->Top = 0;
				Label10->Top = 0;

				SetFAdvGlassButton->Hide();

//				mainForm->LogToFile("non contact image");

				break;
			}

			case 3:{
//				Panel1->Visible = false;
//				Panel2->Visible = false;
				Panel3->Visible = false;
				Panel4->Visible = false;
				Panel5->Visible = false;
				Panel6->Visible = false;
//				Panel7->Visible = false;
//				Panel8->Visible = false;
//				Panel9->Visible = false;
//				Panel10->Visible = false;
				Panel11->Visible = false;
				Panel12->Visible = false;
				Panel13->Visible = false;
				Panel14->Visible = false;
				Panel15->Visible = false;
				Panel16->Visible = false;
				Panel17->Visible = false;
				Panel18->Visible = false;
				Panel19->Visible = false;
				Panel20->Visible = false;
				Panel21->Visible = false;
				Panel22->Visible = false;
				Panel23->Visible = false;
				Panel24->Visible = false;
				Panel25->Visible = false;
				Panel26->Visible = false;
				Panel27->Visible = false;
				Panel28->Visible = false;
				Panel29->Visible = false;
				Panel30->Visible = false;
//				Panel31->Visible = false;
//				Panel32->Visible = false;
//				Panel33->Visible = false;
//				Panel34->Visible = false;

				Panel1->Top = 0;
				Panel2->Top = Panel1->Top + Panel1->Height;
				Panel7->Top = Panel2->Top + Panel2->Height;
				Panel8->Top = Panel7->Top + Panel7->Height;
				Panel9->Top = Panel8->Top + Panel8->Height;
				Panel10->Top = Panel9->Top + Panel9->Height;
				Panel31->Top = Panel10->Top + Panel10->Height;
				Panel32->Top = Panel31->Top + Panel31->Height;
				Panel33->Top = Panel32->Top + Panel32->Height;
				Panel34->Top = Panel33->Top + Panel33->Height;

				Label1->Caption = PIC0_FF;
				Label2->Caption = PIC0_BB;
				Label7->Caption = PIC3_FF;
				Label8->Caption = PIC3_BB;
				Label9->Caption = PIC4_FF;
				Label10->Caption = PIC4_BB;
				Label31->Caption = PIC15_FF;
				Label32->Caption = PIC15_BB;
				Label33->Caption = PIC16_FF;
				Label34->Caption = PIC16_BB;

				Label1->Left = Panel1->Width/2 - Label1->Width/2;
				Label2->Left = Panel2->Width/2 - Label2->Width/2;
				Label7->Left = Panel7->Width/2 - Label7->Width/2;
				Label8->Left = Panel8->Width/2 - Label8->Width/2;
				Label9->Left = Panel9->Width/2 - Label9->Width/2;
				Label10->Left = Panel10->Width/2 - Label10->Width/2;
				Label31->Left = Panel31->Width/2 - Label31->Width/2;
				Label32->Left = Panel32->Width/2 - Label32->Width/2;
				Label33->Left = Panel33->Width/2 - Label33->Width/2;
				Label34->Left = Panel34->Width/2 - Label34->Width/2;

				Label1->Top = 0;
				Label2->Top = 0;
				Label7->Top = 0;
				Label8->Top = 0;
				Label9->Top = 0;
				Label10->Top = 0;
				Label31->Top = 0;
				Label32->Top = 0;
				Label33->Top = 0;
				Label34->Top = 0;

				SetFAdvGlassButton->Hide();

//				mainForm->LogToFile("MFM image");
				break;
			}

			case 4:{
//				Panel1->Visible = false;
//				Panel2->Visible = false;
				Panel3->Visible = false;
				Panel4->Visible = false;
				Panel5->Visible = false;
				Panel6->Visible = false;
//				Panel7->Visible = false;
//				Panel8->Visible = false;
//				Panel9->Visible = false;
//				Panel10->Visible = false;
				Panel11->Visible = false;
				Panel12->Visible = false;
				Panel13->Visible = false;
				Panel14->Visible = false;
				Panel15->Visible = false;
				Panel16->Visible = false;
				Panel17->Visible = false;
				Panel18->Visible = false;
				Panel19->Visible = false;
				Panel20->Visible = false;
				Panel21->Visible = false;
				Panel22->Visible = false;
				Panel23->Visible = false;
				Panel24->Visible = false;
				Panel25->Visible = false;
				Panel26->Visible = false;
				Panel27->Visible = false;
				Panel28->Visible = false;
				Panel29->Visible = false;
				Panel30->Visible = false;
//				Panel31->Visible = false;
//				Panel32->Visible = false;
//				Panel33->Visible = false;
//				Panel34->Visible = false;

				Panel1->Top = 0;
				Panel2->Top = Panel1->Top + Panel1->Height;
				Panel7->Top = Panel2->Top + Panel2->Height;
				Panel8->Top = Panel7->Top + Panel7->Height;
				Panel9->Top = Panel8->Top + Panel8->Height;
				Panel10->Top = Panel9->Top + Panel9->Height;
				Panel31->Top = Panel10->Top + Panel10->Height;
				Panel32->Top = Panel31->Top + Panel31->Height;
				Panel33->Top = Panel32->Top + Panel32->Height;
				Panel34->Top = Panel33->Top + Panel33->Height;

				Label1->Caption = PIC0_FF;
				Label2->Caption = PIC0_BB;
				Label7->Caption = PIC3_FF;
				Label8->Caption = PIC3_BB;
				Label9->Caption = PIC4_FF;
				Label10->Caption = PIC4_BB;
				Label31->Caption = PIC15_FF;
				Label32->Caption = PIC15_BB;
				Label33->Caption = PIC16_FF;
				Label34->Caption = PIC16_BB;

				Label1->Left = Panel1->Width/2 - Label1->Width/2;
				Label2->Left = Panel2->Width/2 - Label2->Width/2;
				Label7->Left = Panel7->Width/2 - Label7->Width/2;
				Label8->Left = Panel8->Width/2 - Label8->Width/2;
				Label9->Left = Panel9->Width/2 - Label9->Width/2;
				Label10->Left = Panel10->Width/2 - Label10->Width/2;
				Label31->Left = Panel31->Width/2 - Label31->Width/2;
				Label32->Left = Panel32->Width/2 - Label32->Width/2;
				Label33->Left = Panel33->Width/2 - Label33->Width/2;
				Label34->Left = Panel34->Width/2 - Label34->Width/2;

				Label1->Top = 0;
				Label2->Top = 0;
				Label7->Top = 0;
				Label8->Top = 0;
				Label9->Top = 0;
				Label10->Top = 0;
				Label31->Top = 0;
				Label32->Top = 0;
				Label33->Top = 0;
				Label34->Top = 0;

				SetFAdvGlassButton->Hide();

//				mainForm->LogToFile("EFM image");
				break;
			}

			case 5:{
//				Panel1->Visible = false;
//				Panel2->Visible = false;
//				Panel3->Visible = false;
//				Panel4->Visible = false;
//				Panel5->Visible = false;
//				Panel6->Visible = false;
				Panel7->Visible = false;
				Panel8->Visible = false;
				Panel9->Visible = false;
				Panel10->Visible = false;
				Panel11->Visible = false;
				Panel12->Visible = false;
				Panel13->Visible = false;
				Panel14->Visible = false;
				Panel15->Visible = false;
				Panel16->Visible = false;
				Panel17->Visible = false;
				Panel18->Visible = false;
				Panel19->Visible = false;
				Panel20->Visible = false;
				Panel21->Visible = false;
				Panel22->Visible = false;
				Panel23->Visible = false;
				Panel24->Visible = false;
				Panel25->Visible = false;
				Panel26->Visible = false;
				Panel27->Visible = false;
				Panel28->Visible = false;
				Panel29->Visible = false;
				Panel30->Visible = false;
				Panel31->Visible = false;
				Panel32->Visible = false;
				Panel33->Visible = false;
				Panel34->Visible = false;

				Panel1->Top = 0;
				Panel2->Top = Panel1->Top + Panel1->Height;
				Panel3->Top = Panel2->Top + Panel2->Height;
				Panel4->Top = Panel7->Top + Panel7->Height;
				Panel5->Top = Panel8->Top + Panel8->Height;
				Panel6->Top = Panel9->Top + Panel9->Height;

				Label1->Caption = PIC0_FF;
				Label2->Caption = PIC0_BB;
				Label3->Caption = PIC1_FF;
				Label4->Caption = PIC1_BB;
				Label5->Caption = PIC2_FF;
				Label6->Caption = PIC2_BB;

				Label1->Left = Panel1->Width/2 - Label1->Width/2;
				Label2->Left = Panel2->Width/2 - Label2->Width/2;
				Label3->Left = Panel3->Width/2 - Label3->Width/2;
				Label4->Left = Panel4->Width/2 - Label4->Width/2;
				Label5->Left = Panel5->Width/2 - Label5->Width/2;
				Label6->Left = Panel6->Width/2 - Label6->Width/2;

				Label1->Top = 0;
				Label2->Top = 0;
				Label3->Top = 0;
				Label4->Top = 0;
				Label5->Top = 0;
				Label6->Top = 0;

				SetFAdvGlassButton->Hide();
//				SetFAdvGlassButton->Visible = true;

				break;
			}
			case 6:{
//				Panel1->Visible = false;
//				Panel2->Visible = false;
//				Panel3->Visible = false;
//				Panel4->Visible = false;
//				Panel5->Visible = false;
//				Panel6->Visible = false;
//				Panel7->Visible = false;
//				Panel8->Visible = false;
//				Panel9->Visible = false;
//				Panel10->Visible = false;
//				Panel11->Visible = false;
//				Panel12->Visible = false;
//				Panel13->Visible = false;
//				Panel14->Visible = false;
//				Panel15->Visible = false;
//				Panel16->Visible = false;
				Panel17->Visible = false;
				Panel18->Visible = false;
				Panel19->Visible = false;
				Panel20->Visible = false;
				Panel21->Visible = false;
				Panel22->Visible = false;
				Panel23->Visible = false;
				Panel24->Visible = false;
				Panel25->Visible = false;
				Panel26->Visible = false;
				Panel27->Visible = false;
				Panel28->Visible = false;
				Panel29->Visible = false;
				Panel30->Visible = false;
				Panel31->Visible = false;
				Panel32->Visible = false;
				Panel33->Visible = false;
				Panel34->Visible = false;

				Panel1->Top = 0;
				Panel2->Top = Panel1->Top + Panel1->Height;
				Panel3->Top = Panel2->Top + Panel2->Height;
				Panel4->Top = Panel3->Top + Panel3->Height;
				Panel5->Top = Panel4->Top + Panel4->Height;
				Panel6->Top = Panel5->Top + Panel5->Height;
				Panel7->Top = Panel6->Top + Panel6->Height;
				Panel8->Top = Panel7->Top + Panel7->Height;
				Panel9->Top = Panel8->Top + Panel8->Height;
				Panel10->Top = Panel9->Top + Panel9->Height;
				Panel11->Top = Panel10->Top + Panel10->Height;
				Panel12->Top = Panel11->Top + Panel11->Height;
				Panel13->Top = Panel12->Top + Panel12->Height;
				Panel14->Top = Panel13->Top + Panel13->Height;
				Panel15->Top = Panel14->Top + Panel14->Height;
				Panel16->Top = Panel15->Top + Panel15->Height;

				Label1->Caption = PIC0_FF;
				Label2->Caption = PIC0_BB;
				Label3->Caption = PIC7_FF;
				Label4->Caption = PIC7_BB;
				Label5->Caption = PIC8_FF;
				Label6->Caption = PIC8_BB;
				Label7->Caption = PIC3_FF;
				Label8->Caption = PIC3_BB;
				Label9->Caption = PIC4_FF;
				Label10->Caption = PIC4_BB;
				Label11->Caption = PIC5_FF;
				Label12->Caption = PIC5_BB;
				Label13->Caption = PIC9_FF;
				Label14->Caption = PIC9_BB;
				Label15->Caption = PIC10_FF;
				Label16->Caption = PIC10_BB;

				Label1->Left = Panel1->Width/2 - Label1->Width/2;
				Label2->Left = Panel2->Width/2 - Label2->Width/2;
				Label3->Left = Panel3->Width/2 - Label3->Width/2;
				Label4->Left = Panel4->Width/2 - Label4->Width/2;
				Label5->Left = Panel5->Width/2 - Label5->Width/2;
				Label6->Left = Panel6->Width/2 - Label6->Width/2;
				Label7->Left = Panel7->Width/2 - Label7->Width/2;
				Label8->Left = Panel8->Width/2 - Label8->Width/2;
				Label9->Left = Panel9->Width/2 - Label9->Width/2;
				Label10->Left = Panel10->Width/2 - Label10->Width/2;
				Label11->Left = Panel11->Width/2 - Label11->Width/2;
				Label12->Left = Panel12->Width/2 - Label12->Width/2;
				Label13->Left = Panel13->Width/2 - Label13->Width/2;
				Label14->Left = Panel14->Width/2 - Label14->Width/2;
				Label15->Left = Panel15->Width/2 - Label15->Width/2;
				Label16->Left = Panel16->Width/2 - Label16->Width/2;


				Label1->Top = 0;
				Label2->Top = 0;
				Label3->Top = 0;
				Label4->Top = 0;
				Label5->Top = 0;
				Label6->Top = 0;
				Label7->Top = 0;
				Label8->Top = 0;
				Label9->Top = 0;
				Label10->Top = 0;
				Label11->Top = 0;
				Label12->Top = 0;
				Label13->Top = 0;
				Label14->Top = 0;
				Label15->Top = 0;
				Label16->Top = 0;
				SetFAdvGlassButton->Hide();

//				mainForm->LogToFile("KPFM image");
				break;
			}

			case 7:{
//				Panel1->Visible = false;
//				Panel2->Visible = false;
//				Panel3->Visible = false;
//				Panel4->Visible = false;
//				Panel5->Visible = false;
//				Panel6->Visible = false;
				Panel7->Visible = false;
				Panel8->Visible = false;
				Panel9->Visible = false;
				Panel10->Visible = false;
				Panel11->Visible = false;
				Panel12->Visible = false;
				Panel13->Visible = false;
				Panel14->Visible = false;
				Panel15->Visible = false;
				Panel16->Visible = false;
				Panel17->Visible = false;
				Panel18->Visible = false;
				Panel19->Visible = false;
				Panel20->Visible = false;
				Panel21->Visible = false;
				Panel22->Visible = false;
				Panel23->Visible = false;
				Panel24->Visible = false;
				Panel25->Visible = false;
				Panel26->Visible = false;
				Panel27->Visible = false;
				Panel28->Visible = false;
				Panel29->Visible = false;
				Panel30->Visible = false;
				Panel31->Visible = false;
				Panel32->Visible = false;
				Panel33->Visible = false;
				Panel34->Visible = false;

				Panel1->Top = 0;
				Panel2->Top = Panel1->Top + Panel1->Height;
				Panel3->Top = Panel2->Top + Panel2->Height;
				Panel4->Top = Panel7->Top + Panel7->Height;
				Panel5->Top = Panel8->Top + Panel8->Height;
				Panel6->Top = Panel9->Top + Panel9->Height;

				Label1->Caption = PIC0_FF;
				Label2->Caption = PIC0_BB;
				Label3->Caption = PIC1_FF;
				Label4->Caption = PIC1_BB;
				Label5->Caption = PIC2_FF;
				Label6->Caption = PIC2_BB;

				Label1->Left = Panel1->Width/2 - Label1->Width/2;
				Label2->Left = Panel2->Width/2 - Label2->Width/2;
				Label3->Left = Panel3->Width/2 - Label3->Width/2;
				Label4->Left = Panel4->Width/2 - Label4->Width/2;
				Label5->Left = Panel5->Width/2 - Label5->Width/2;
				Label6->Left = Panel6->Width/2 - Label6->Width/2;

				Label1->Top = 0;
				Label2->Top = 0;
				Label3->Top = 0;
				Label4->Top = 0;
				Label5->Top = 0;
				Label6->Top = 0;

//				mainForm->LogToFile("Force image");
				SetFAdvGlassButton->Caption = "Litho-Select";
				SetFAdvGlassButton->Show();
				SetFAdvGlassButton->Visible = true;
				break;
			}
			default:{
				break;
			}
		}

		for(int i=1; i<35; i++){
			((TPanel*)FindComponent("Panel"+IntToStr(i)))->Height = Panel1->Width;
			((TLabel*)FindComponent("Label"+IntToStr(i)))->Font = Label1->Font;
		}
	}

	PanelImageNames->Top = 0;

	MainImage->SendToBack();
	PaintBox1->BringToFront();

}
//---------------------------------------------------------------------------

void TImgForm::Togle1_2(bool lia)
{
	mainForm->LogToFile("TImgForm::Togle1_2 , lia = " + BoolToStr(lia,true));
	if(lia){    //lia2
    	Label1->Caption = PIC0_FF;
		Label2->Caption = PIC0_BB;
		Label3->Caption = PIC11_FF;
		Label4->Caption = PIC11_BB;
		Label5->Caption = PIC12_FF;
		Label6->Caption = PIC12_BB;
		Label7->Caption = PIC3_FF;
		Label8->Caption = PIC3_BB;
		Label9->Caption = PIC4_FF;
		Label10->Caption = PIC4_BB;
		Label11->Caption = PIC5_FF;
		Label12->Caption = PIC5_BB;
		Label13->Caption = PIC13_FF;
		Label14->Caption = PIC13_BB;
		Label15->Caption = PIC14_FF;
		Label16->Caption = PIC14_BB;
	}
	else{       //lia1
		Label1->Caption = PIC0_FF;
		Label2->Caption = PIC0_BB;
		Label3->Caption = PIC7_FF;
		Label4->Caption = PIC7_BB;
		Label5->Caption = PIC8_FF;
		Label6->Caption = PIC8_BB;
		Label7->Caption = PIC3_FF;
		Label8->Caption = PIC3_BB;
		Label9->Caption = PIC4_FF;
		Label10->Caption = PIC4_BB;
		Label11->Caption = PIC5_FF;
		Label12->Caption = PIC5_BB;
		Label13->Caption = PIC9_FF;
		Label14->Caption = PIC9_BB;
		Label15->Caption = PIC10_FF;
		Label16->Caption = PIC10_BB;
	}

    Label1->Left = Panel1->Width/2 - Label1->Width/2;
	Label2->Left = Panel2->Width/2 - Label2->Width/2;
	Label3->Left = Panel3->Width/2 - Label3->Width/2;
	Label4->Left = Panel4->Width/2 - Label4->Width/2;
	Label5->Left = Panel5->Width/2 - Label5->Width/2;
	Label6->Left = Panel6->Width/2 - Label6->Width/2;
	Label7->Left = Panel7->Width/2 - Label7->Width/2;
	Label8->Left = Panel8->Width/2 - Label8->Width/2;
	Label9->Left = Panel9->Width/2 - Label9->Width/2;
	Label10->Left = Panel10->Width/2 - Label10->Width/2;
	Label11->Left = Panel11->Width/2 - Label11->Width/2;
	Label12->Left = Panel12->Width/2 - Label12->Width/2;
	Label13->Left = Panel13->Width/2 - Label13->Width/2;
	Label14->Left = Panel14->Width/2 - Label14->Width/2;
	Label15->Left = Panel15->Width/2 - Label15->Width/2;
	Label16->Left = Panel16->Width/2 - Label16->Width/2;
}
//---------------------------------------------------------------------------

void __fastcall TImgForm::Image1DblClick(TObject *Sender)
{
	mainForm->LogToFile("TImgForm::Image1DblClick");
	IamgeIndex = 1;
	ImageNameAdvLabel->Caption = Label1->Caption;
	ShowImageNumber();
}
//---------------------------------------------------------------------------

void __fastcall TImgForm::Image2DblClick(TObject *Sender)
{
	mainForm->LogToFile("TImgForm::Image2DblClick");
	IamgeIndex = 2;
	ImageNameAdvLabel->Caption = Label2->Caption;
	ShowImageNumber();
}
//---------------------------------------------------------------------------

void __fastcall TImgForm::Image3DblClick(TObject *Sender)
{
	mainForm->LogToFile("TImgForm::Image3DblClick");
	IamgeIndex = 3;
	ImageNameAdvLabel->Caption = Label3->Caption;
	ShowImageNumber();
}
//---------------------------------------------------------------------------

void __fastcall TImgForm::Image4DblClick(TObject *Sender)
{
	mainForm->LogToFile("TImgForm::Image4DblClick");
	IamgeIndex = 4;
	ImageNameAdvLabel->Caption = Label4->Caption;
	ShowImageNumber();
}
//---------------------------------------------------------------------------

void __fastcall TImgForm::Image5DblClick(TObject *Sender)
{
	mainForm->LogToFile("TImgForm::Image5DblClick");
	IamgeIndex = 5;
	ImageNameAdvLabel->Caption = Label5->Caption;
	ShowImageNumber();
}
//---------------------------------------------------------------------------

void __fastcall TImgForm::Image6DblClick(TObject *Sender)
{
	mainForm->LogToFile("TImgForm::Image6DblClick");
	IamgeIndex = 6;
	ImageNameAdvLabel->Caption = Label6->Caption;
	ShowImageNumber();
}
//---------------------------------------------------------------------------

void __fastcall TImgForm::Image7DblClick(TObject *Sender)
{
	mainForm->LogToFile("TImgForm::Image7DblClick");
	IamgeIndex = 7;
	ImageNameAdvLabel->Caption = Label7->Caption;
	ShowImageNumber();
}
//---------------------------------------------------------------------------

void __fastcall TImgForm::Image8DblClick(TObject *Sender)
{
	mainForm->LogToFile("TImgForm::Image8DblClick");
	IamgeIndex = 8;
	ImageNameAdvLabel->Caption = Label8->Caption;
	ShowImageNumber();
}
//---------------------------------------------------------------------------


void __fastcall TImgForm::Image9DblClick(TObject *Sender)
{
	mainForm->LogToFile("TImgForm::Image9DblClick");
	IamgeIndex = 9;
	ImageNameAdvLabel->Caption = Label9->Caption;
	ShowImageNumber();
}
//---------------------------------------------------------------------------

void __fastcall TImgForm::Image10DblClick(TObject *Sender)
{
	mainForm->LogToFile("TImgForm::Image10DblClick");
	IamgeIndex = 10;
	ImageNameAdvLabel->Caption = Label10->Caption;
	ShowImageNumber();
}
//---------------------------------------------------------------------------

void __fastcall TImgForm::Image11DblClick(TObject *Sender)
{
	mainForm->LogToFile("TImgForm::Image11DblClick");
	IamgeIndex = 11;
	ImageNameAdvLabel->Caption = Label11->Caption;
	ShowImageNumber();
}
//---------------------------------------------------------------------------

void __fastcall TImgForm::Image12DblClick(TObject *Sender)
{
	mainForm->LogToFile("TImgForm::Image12DblClick");
	IamgeIndex = 12;
	ImageNameAdvLabel->Caption = Label12->Caption;
	ShowImageNumber();
}
//---------------------------------------------------------------------------

void __fastcall TImgForm::Image13DblClick(TObject *Sender)
{
	mainForm->LogToFile("TImgForm::Image13DblClick");
	IamgeIndex = 13;
	ImageNameAdvLabel->Caption = Label13->Caption;
	ShowImageNumber();
}
//---------------------------------------------------------------------------

void __fastcall TImgForm::Image14DblClick(TObject *Sender)
{
	mainForm->LogToFile("TImgForm::Image14DblClick");
	IamgeIndex = 14;
	ImageNameAdvLabel->Caption = Label14->Caption;
	ShowImageNumber();
}
//---------------------------------------------------------------------------

void __fastcall TImgForm::Image15DblClick(TObject *Sender)
{
	mainForm->LogToFile("TImgForm::Image15DblClick");
	IamgeIndex = 15;
	ImageNameAdvLabel->Caption = Label15->Caption;
	ShowImageNumber();
}
//---------------------------------------------------------------------------

void __fastcall TImgForm::Image16DblClick(TObject *Sender)
{
	mainForm->LogToFile("TImgForm::Image16DblClick");
	IamgeIndex = 16;
	ImageNameAdvLabel->Caption = Label16->Caption;
	ShowImageNumber();
}
//---------------------------------------------------------------------------

void __fastcall TImgForm::Image17DblClick(TObject *Sender)
{
	mainForm->LogToFile("TImgForm::Image17DblClick");
	IamgeIndex = 17;
	ImageNameAdvLabel->Caption = Label17->Caption;
	ShowImageNumber();
}
//---------------------------------------------------------------------------

void __fastcall TImgForm::Image18DblClick(TObject *Sender)
{
	mainForm->LogToFile("TImgForm::Image18DblClick");
	IamgeIndex = 18;
	ImageNameAdvLabel->Caption = Label18->Caption;
	ShowImageNumber();
}
//---------------------------------------------------------------------------

void __fastcall TImgForm::Image19DblClick(TObject *Sender)
{
	mainForm->LogToFile("TImgForm::Image19DblClick");
	IamgeIndex = 19;
	ImageNameAdvLabel->Caption = Label1->Caption;
	ShowImageNumber();
}
//---------------------------------------------------------------------------

void __fastcall TImgForm::Image20DblClick(TObject *Sender)
{
	mainForm->LogToFile("TImgForm::Image20DblClick");
	IamgeIndex = 20;
	ImageNameAdvLabel->Caption = Label20->Caption;
	ShowImageNumber();
}
//---------------------------------------------------------------------------

void __fastcall TImgForm::Image21DblClick(TObject *Sender)
{
	mainForm->LogToFile("TImgForm::Image21DblClick");
	IamgeIndex = 21;
	ImageNameAdvLabel->Caption = Label21->Caption;
	ShowImageNumber();
}
//---------------------------------------------------------------------------

void __fastcall TImgForm::Image22DblClick(TObject *Sender)
{
	mainForm->LogToFile("TImgForm::Image22DblClick");
	IamgeIndex = 22;
	ImageNameAdvLabel->Caption = Label22->Caption;
	ShowImageNumber();
}
//---------------------------------------------------------------------------

void __fastcall TImgForm::Image23DblClick(TObject *Sender)
{
	mainForm->LogToFile("TImgForm::Image23DblClick");
	IamgeIndex = 23;
	ImageNameAdvLabel->Caption = Label23->Caption;
	ShowImageNumber();
}
//---------------------------------------------------------------------------

void __fastcall TImgForm::Image24DblClick(TObject *Sender)
{
	mainForm->LogToFile("TImgForm::Image24DblClick");
	IamgeIndex = 24;
	ImageNameAdvLabel->Caption = Label24->Caption;
	ShowImageNumber();
}
//---------------------------------------------------------------------------

void __fastcall TImgForm::Image25DblClick(TObject *Sender)
{
	mainForm->LogToFile("TImgForm::Image25DblClick");
	IamgeIndex = 25;
	ImageNameAdvLabel->Caption = Label25->Caption;
	ShowImageNumber();
}
//---------------------------------------------------------------------------

void __fastcall TImgForm::Image26DblClick(TObject *Sender)
{
	mainForm->LogToFile("TImgForm::Image26DblClick");
	IamgeIndex = 26;
	ImageNameAdvLabel->Caption = Label26->Caption;
	ShowImageNumber();
}
//---------------------------------------------------------------------------

void __fastcall TImgForm::Image27DblClick(TObject *Sender)
{
	mainForm->LogToFile("TImgForm::Image27DblClick");
	IamgeIndex = 27;
	ImageNameAdvLabel->Caption = Label27->Caption;
	ShowImageNumber();
}
//---------------------------------------------------------------------------

void __fastcall TImgForm::Image28DblClick(TObject *Sender)
{
	mainForm->LogToFile("TImgForm::Image28DblClick");
	IamgeIndex = 28;
	ImageNameAdvLabel->Caption = Label28->Caption;
	ShowImageNumber();
}
//---------------------------------------------------------------------------

void __fastcall TImgForm::Image29DblClick(TObject *Sender)
{
	mainForm->LogToFile("TImgForm::Image29DblClick");
	IamgeIndex = 29;
	ImageNameAdvLabel->Caption = Label29->Caption;
	ShowImageNumber();
}
//---------------------------------------------------------------------------

void __fastcall TImgForm::Image30DblClick(TObject *Sender)
{
	mainForm->LogToFile("TImgForm::Image30DblClick");
	IamgeIndex = 30;
	ImageNameAdvLabel->Caption = Label30->Caption;
	ShowImageNumber();
}
//---------------------------------------------------------------------------

void __fastcall TImgForm::Image31DblClick(TObject *Sender)
{
	mainForm->LogToFile("TImgForm::Image31DblClick");
	IamgeIndex = 31;
	ImageNameAdvLabel->Caption = Label31->Caption;
	ShowImageNumber();
}
//---------------------------------------------------------------------------

void __fastcall TImgForm::Image32DblClick(TObject *Sender)
{
	mainForm->LogToFile("TImgForm::Image32DblClick");
	IamgeIndex = 32;
	ImageNameAdvLabel->Caption = Label32->Caption;
	ShowImageNumber();
}
//---------------------------------------------------------------------------

void __fastcall TImgForm::Image33DblClick(TObject *Sender)
{
	mainForm->LogToFile("TImgForm::Image33DblClick");
	IamgeIndex = 33;
	ImageNameAdvLabel->Caption = Label33->Caption;
	ShowImageNumber();
}
//---------------------------------------------------------------------------

void __fastcall TImgForm::Image34DblClick(TObject *Sender)
{
	mainForm->LogToFile("TImgForm::Image34DblClick");
	LastIamgeIndex = IamgeIndex;
	IamgeIndex = 34;
	ImageNameAdvLabel->Caption = Label34->Caption;
	ShowImageNumber();
}
//---------------------------------------------------------------------------

void __fastcall TImgForm::ChartButtonClick(TObject *Sender)
{
	mainForm->LogToFile("TImgForm::ChartButtonClick");
	mainForm->LogToFile("TImgForm::ChartButtonClick : ChartImage = " + BoolToStr(ChartImage,true));
	mainForm->LogToFile("TImgForm::ChartButtonClick : mainForm->Scaning = " + BoolToStr(mainForm->Scaning,true));
	if(ChartImage && mainForm->Scaning){

		ShowChart();
	}
	else{
		ShowImages();
	}
}
//---------------------------------------------------------------------------

void __fastcall TImgForm::ShowChart()
{
	mainForm->LogToFile("TImgForm::ShowChart");
	ChartImage = false;
	ScrollBox2->Hide();
	TopoChart->Axes->Bottom->Items->Clear();
	ImgPanel->Hide();
	if(AllScale){
		for(int i=0; i<11; i++){
			TopoChart->Axes->Bottom->Items->Add( i * (mainForm->myScanPanelForm->Resolution / 10) , FloatToStr(i * mainForm->myScanPanelForm->Range / 10));
//			mainForm->LogToFile(FloatToStr(i * mainForm->myScanPanelForm->Range / 10));
		}
    }
	TopoChart->Show();
	ChartButton->SetParentComponent(TopoChart);
	ChartButton->BringToFront();
}
//---------------------------------------------------------------------------

void __fastcall TImgForm::ShowImages()
{
	mainForm->LogToFile("TImgForm::ShowImages");
	ChartImage = true;
	TopoChart->Hide();
	ImgPanel->Show();
	ScrollBox2->Show();
	ChartButton->SetParentComponent(ImgPanel);
	ChartButton->BringToFront();
}
//---------------------------------------------------------------------------

void __fastcall TImgForm::TopoChartClickBackground(TCustomChart *Sender, TMouseButton Button,
		  TShiftState Shift, int X, int Y)
{
		mainForm->LogToFile("TImgForm::TopoChartClickBackground");
//    mainForm->LogToFile("click back");
//	if(TopoChart->AutoRepaint){
		int ValueX = TopoChart->BottomAxis->CalcPosPoint(X);
		double ValueInterceptFw = InterpolateTopoSeries(ValueX,true);
		double ValueInterceptBw = InterpolateTopoSeries(ValueX,false);
//		mainForm->LogToFile(FloatToStr(ValueInterceptFw - ValueInterceptBw));

		ChartTool2->Value = TopoChart->BottomAxis->CalcPosPoint(X);
		ChartTool1->Text = FloatToStr(ValueInterceptFw - ValueInterceptBw);

		ChartTool2->Active = true;
		ChartTool1->Active = true;

		Timer1->Enabled = true;
//	}
}
//---------------------------------------------------------------------------

double TImgForm::InterpolateTopoSeries(double XValue, bool fb)
{
	mainForm->LogToFile("TImgForm::InterpolateTopoSeries , fb = " + BoolToStr(fb,true));
	int index;
	double dx,dy;
	double result;

	if(fb){
		for(index = 1; index < TopoFWSeries->Count(); index++){
			if(XValue < TopoFWSeries->XValue[index])
				break;
			dx=TopoFWSeries->XValue[index] - TopoFWSeries->XValue[index-1];
			dy=TopoFWSeries->YValue[index] - TopoFWSeries->YValue[index-1];
			if(dx != 0){
				result = dy*(XValue - TopoFWSeries->XValue[index-1])/dx + TopoFWSeries->YValue[index-1];
			}
			else
				result = 0;
		}
	}
	else{
		for(index = 1; index < TopoBWSeries->Count(); index++){
			if(XValue < TopoBWSeries->XValue[index])
				break;
			dx=TopoBWSeries->XValue[index] - TopoBWSeries->XValue[index-1];
			dy=TopoBWSeries->YValue[index] - TopoBWSeries->YValue[index-1];
			if(dx != 0){
				result = dy*(XValue - TopoBWSeries->XValue[index-1])/dx + TopoBWSeries->YValue[index-1];
			}
			else
				result = 0;
		}
	}

	return result;
}
//---------------------------------------------------------------------------


void __fastcall TImgForm::TopoChartClickSeries(TCustomChart *Sender, TChartSeries *Series,
          int ValueIndex, TMouseButton Button, TShiftState Shift, int X,
          int Y)
{
//	mainForm->LogToFile("click series");
//	if(TopoChart->AutoRepaint){
		mainForm->LogToFile("TImgForm::TopoChartClickSeries");
		int ValueX = TopoChart->BottomAxis->CalcPosPoint(X);
		double ValueInterceptFw = InterpolateTopoSeries(ValueX,true);
		double ValueInterceptBw = InterpolateTopoSeries(ValueX,false);
//		mainForm->LogToFile(FloatToStr(ValueInterceptFw - ValueInterceptBw));

		ChartTool2->Value = TopoChart->BottomAxis->CalcPosPoint(X);
		ChartTool1->Text = FloatToStr(ValueInterceptFw - ValueInterceptBw);

		ChartTool2->Active = true;
		ChartTool1->Active = true;
		Timer1->Enabled = true;
//	}
}
//---------------------------------------------------------------------------

void __fastcall TImgForm::Timer1Timer(TObject *Sender)
{
	mainForm->LogToFile("TImgForm::Timer1Timer");
	Timer1->Enabled = false;
	ChartTool2->Active = false;
	ChartTool1->Active = false;
}
//---------------------------------------------------------------------------

//void __fastcall TImgForm::SaveButtonClick(TObject *Sender)
//{
//	SaveButton->Enabled = false;
//	TThread::Synchronize(mainForm->myImagerThread,SaveFiles);
//}
////---------------------------------------------------------------------------
//
//void __fastcall TImgForm::SaveFiles()
//{
//	mainForm->myImagerThread->SaveAll(false);
//}
////---------------------------------------------------------------------------

void __fastcall TImgForm::PaintBox1MouseDown(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y)
{
	mainForm->LogToFile("TImgForm::PaintBox1MouseDown");
	if(!ImageCanvasDraw && (mainForm->GetSecure() == 0 || mainForm->GetSecure() == 8)  && Button == mbRight){
		ImageCanvasDraw = true;
		PaintBox1->Canvas->Pen->Style = psDashDot;
		XStart = X;
		YStart = Y;
	}

}
//---------------------------------------------------------------------------

void __fastcall TImgForm::PaintBox1MouseMove(TObject *Sender, TShiftState Shift, int X,
		  int Y)
{
	if(ImageCanvasDraw){
		int w = abs(X - XStart);
		int h = abs(Y - YStart);
		bool x = false;
		bool y = false;
		if(X > XStart) x = true;
		if(Y > YStart) y = true;
		TPoint p[5];
		if(w > h){
			if(y){
				p[0] = TPoint(XStart, YStart);
				p[1] = TPoint(XStart, YStart + w);
				p[2] = TPoint(X, YStart + w);
				p[3] = TPoint(X, YStart);
				p[4] = p[0];
			}
			else{
				p[0] = TPoint(XStart, YStart);
				p[1] = TPoint(XStart, YStart - w);
				p[2] = TPoint(X, YStart - w);
				p[3] = TPoint(X, YStart);
				p[4] = p[0];
			}
		}
		else{
			if(x){
				p[0] = TPoint(XStart, YStart);
				p[1] = TPoint(XStart, Y);
				p[2] = TPoint(XStart + h, Y);
				p[3] = TPoint(XStart + h, YStart);
				p[4] = p[0];
			}
			else{
				p[0] = TPoint(XStart, YStart);
				p[1] = TPoint(XStart, Y);
				p[2] = TPoint(XStart - h, Y);
				p[3] = TPoint(XStart - h, YStart);
				p[4] = p[0];
			}
		}
		PaintBox1->Canvas->Polyline(p, 4);

		PaintBox1->Invalidate();
	}
}
//---------------------------------------------------------------------------

void __fastcall TImgForm::PaintBox1MouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift,
		  int X, int Y)
{
	mainForm->LogToFile("TImgForm::PaintBox1MouseUp");
	if(ImageCanvasDraw){
		ImageCanvasDraw = false;

		int w = abs(X - XStart);
		int h = abs(Y - YStart);
		int X_Center;
		int Y_Center;
		bool x = false;
		bool y = false;


		if(X > XStart) x = true;
		if(Y > YStart) y = true;

//		mainForm->LogToFile("TImgForm::PaintBox1MouseUp : w = " + FloatToStr(w));
//		mainForm->LogToFile("TImgForm::PaintBox1MouseUp : h = " + FloatToStr(h));

		TPoint p[5];

		int t;
		if(w > h){
			t = w;
			if(y){
				p[0] = TPoint(XStart, YStart);
				p[1] = TPoint(XStart, YStart + w);
				p[2] = TPoint(X, YStart + w);
				p[3] = TPoint(X, YStart);
				p[4] = p[0];

				if(x){
					X_Center = XStart + w/2;
					Y_Center = YStart + w/2;
				}
				else{
					X_Center = XStart - w/2;
					Y_Center = YStart + w/2;
				}
			}
			else{
				p[0] = TPoint(XStart, YStart);
				p[1] = TPoint(XStart, YStart - w);
				p[2] = TPoint(X, YStart - w);
				p[3] = TPoint(X, YStart);
				p[4] = p[0];

                if(x){
					X_Center = XStart + w/2;
					Y_Center = YStart - w/2;
				}
				else{
					X_Center = XStart - w/2;
					Y_Center = YStart - w/2;
				}
			}
		}
		else{
			t = h;
			if(x){
				p[0] = TPoint(XStart, YStart);
				p[1] = TPoint(XStart, Y);
				p[2] = TPoint(XStart + h, Y);
				p[3] = TPoint(XStart + h, YStart);
				p[4] = p[0];

				if(y){
					X_Center = XStart + h/2;
					Y_Center = YStart + h/2;
				}
				else{
					X_Center = XStart + h/2;
					Y_Center = YStart - h/2;
				}
			}
			else{
				p[0] = TPoint(XStart, YStart);
				p[1] = TPoint(XStart, Y);
				p[2] = TPoint(XStart - h, Y);
				p[3] = TPoint(XStart - h, YStart);
				p[4] = p[0];

                if(y){
					X_Center = XStart - h/2;
					Y_Center = YStart + h/2;
				}
				else{
					X_Center = XStart - h/2;
					Y_Center = YStart - h/2;
				}
			}
		}
		PaintBox1->Canvas->Polyline(p, 4);

//		mainForm->LogToFile("TImgForm::PaintBox1MouseUp : XStart = " + FloatToStr(XStart));
//		mainForm->LogToFile("TImgForm::PaintBox1MouseUp : YStart = " + FloatToStr(YStart));

//		mainForm->LogToFile("TImgForm::PaintBox1MouseUp : X_Center = " + FloatToStr(X_Center));
//		mainForm->LogToFile("TImgForm::PaintBox1MouseUp : Y_Center = " + FloatToStr(Y_Center));

		int L = PaintBox1->Width;

		double mainXRange = mainForm->myScanPanelForm->X_Range;
		double mainYRange = mainForm->myScanPanelForm->Y_Range;


		int mainAngle = mainForm->myScanPanelForm->Angle;

		new_range = (double)t/(double)L * 100;

		float Theta = atan((float)Y_Center / (float)X_Center);
//		mainForm->LogToFile("Theta = " + FloatToStr(Theta));
//		mainForm->LogToFile("mainAngle*M_PI/180 = " + FloatToStr(mainAngle*M_PI/180));

		new_center_x = ( (double) X_Center /(double)L ) * 100;
		new_center_y = ( (double) Y_Center /(double)L ) * 100;


//		mainForm->LogToFile("TImgForm::PaintBox1MouseUp : new_center_x  = " + FloatToStr(new_center_x));
//		mainForm->LogToFile("TImgForm::PaintBox1MouseUp : new_center_y  = " + FloatToStr(new_center_y));

		float TAN;
		if(mainAngle == 90)
			TAN = tan((88*M_PI/180));
		else
			TAN = tan((mainAngle*M_PI/180));

		mainForm->LogToFile("if = " + BoolToStr(Y_Center <= TAN * X_Center , true));
//		mainForm->LogToFile("Y_Center = " + FloatToStr((double)Y_Center));
//		mainForm->LogToFile("TAN* (double)X_Center = " + FloatToStr(TAN* (double)X_Center));
//		mainForm->LogToFile("mainXRange = " + FloatToStr(mainXRange));
//		mainForm->LogToFile("mainYRange = " + FloatToStr(mainYRange));
		double length = sqrt(pow((float)new_center_x,2) + pow((float)new_center_y,2));
		if((double)Y_Center <= TAN * (double)X_Center)
		{
//            mainForm->LogToFile("sqrt(pow((float)new_center_x,2) + pow((float)new_center_y,2)) = " + FloatToStr(sqrt(pow((float)new_center_x,2) + pow((float)new_center_y,2))));
//			mainForm->LogToFile("sin((mainAngle*M_PI/180) - Theta) = " + FloatToStr(sin((mainAngle*M_PI/180) - Theta)));

			new_center_x = length * cos((mainAngle*M_PI/180) - Theta);
			new_center_y = length * sin((mainAngle*M_PI/180) - Theta);

//			mainForm->LogToFile("new_center_x , new_center_y = " + FloatToStr(new_center_x) + " , " + FloatToStr(new_center_y));



			new_center_x = mainXRange * new_center_x / (double)100;
			new_center_y = -1 * (mainYRange * new_center_y / (double)100);
//			mainForm->LogToFile("new_center_x , new_center_y = " + FloatToStr(new_center_x) + " , " + FloatToStr(new_center_y));
			new_center_x = mainForm->myCommandCreatorThread->myScan->myCoordinateClass->TL2[0] + new_center_x;
			new_center_y = mainForm->myCommandCreatorThread->myScan->myCoordinateClass->TL2[1] - new_center_y;
//            mainForm->LogToFile("new_center_x , new_center_y = " + FloatToStr(new_center_x) + " , " + FloatToStr(new_center_y));
		}
		else
		{
			new_center_x = length * cos(Theta - (mainAngle*M_PI/180));
			new_center_y = length * sin(Theta - (mainAngle*M_PI/180));


			new_center_x = mainXRange * new_center_x / (double)100;
			new_center_y = -1 * (mainYRange * new_center_y / (double)100);


			new_center_x = mainForm->myCommandCreatorThread->myScan->myCoordinateClass->TL2[0] + new_center_x;
			new_center_y = mainForm->myCommandCreatorThread->myScan->myCoordinateClass->TL2[1] + new_center_y;


		}

//		mainForm->LogToFile("TImgForm::PaintBox1MouseUp : new_center_x (%) = " + FloatToStr(new_center_x));
//		mainForm->LogToFile("TImgForm::PaintBox1MouseUp : new_center_y (%) = " + FloatToStr(new_center_y));


		double new_X_range = mainXRange * new_range / (double)100;
		double new_Y_range = mainYRange * new_range / (double)100;

		if(AllScale){
			double new_center_xx;
			bool Xplus = false;
			if(new_center_x > 50){
				new_center_xx = new_center_x - 50;
				Xplus = true;
			}
			else new_center_xx = 50 - new_center_x;

			double new_center_yy;
			bool Yplus = false;
			if(new_center_y > 50) {
				new_center_yy = new_center_y - 50;
				Yplus = true;
			}
			else new_center_yy = 50 - new_center_y;

			float min_CenterX = 100;
			float min_CenterY = 100;
			float min_XRange = 100;
			float min_YRange = 100;

			int new_XCenter;
			int new_YCenter;
			int new_XRange;;
			int new_YRange;


			for (int i = 0; i < mainForm->Max_Range; i++) {
				if (min_CenterX > abs(new_center_xx-mainForm->X_Range[i])){
					min_CenterX = abs(new_center_xx-mainForm->X_Range[i]);
					new_XCenter = i;
				}
				if (min_CenterY > abs(new_center_yy-mainForm->Y_Range[i])){
					min_CenterY = abs(new_center_yy-mainForm->Y_Range[i]);
					new_YCenter = i;
				}
				if (min_XRange > abs(new_X_range-mainForm->X_Range[i])){
					min_XRange = abs(new_X_range-mainForm->X_Range[i]);
					new_XRange = i;
				}
				if (min_YRange > abs(new_Y_range-mainForm->Y_Range[i])){
					min_YRange = abs(new_Y_range-mainForm->Y_Range[i]);
					new_YRange = i;
				}

			}

			if(new_center_xx-mainForm->X_Range[new_XCenter] >= 0)
				new_center_xx = new_XCenter + (new_center_xx - mainForm->X_Range[new_XCenter]) / (mainForm->X_Range[new_XCenter+1] - mainForm->X_Range[new_XCenter]);
			else
				new_center_xx = new_XCenter + (new_center_xx - mainForm->X_Range[new_XCenter]) / (mainForm->X_Range[new_XCenter] - mainForm->X_Range[new_XCenter-1]);


			if(new_center_yy-mainForm->Y_Range[new_YCenter] >= 0)
				new_center_yy = new_YCenter + (new_center_yy - mainForm->Y_Range[new_YCenter]) / (mainForm->Y_Range[new_YCenter+1] - mainForm->Y_Range[new_YCenter]);
			else
				new_center_yy = new_YCenter + (new_center_yy - mainForm->Y_Range[new_YCenter]) / (mainForm->Y_Range[new_YCenter] - mainForm->Y_Range[new_YCenter-1]);


			if(new_X_range-mainForm->X_Range[new_XRange] >= 0)
				new_X_range = new_XRange + (new_X_range - mainForm->X_Range[new_XRange]) / (mainForm->X_Range[new_XRange+1] - mainForm->X_Range[new_XRange]);
			else
				new_X_range = new_XRange + (new_X_range - mainForm->X_Range[new_XRange]) / (mainForm->X_Range[new_XRange] - mainForm->X_Range[new_XRange-1]);


			if(new_Y_range-mainForm->Y_Range[new_YRange] >= 0)
				new_Y_range = new_YRange + (new_Y_range - mainForm->Y_Range[new_YRange]) / (mainForm->Y_Range[new_YRange+1] - mainForm->Y_Range[new_YRange]);
			else
				new_Y_range = new_YRange + (new_Y_range - mainForm->Y_Range[new_YRange]) / (mainForm->Y_Range[new_YRange] - mainForm->Y_Range[new_YRange-1]);


//			new_range = (new_X_range + new_Y_range) / 2;

	//		mainForm->LogToFile("new_X_range = " + FloatToStr(new_X_range));
	//		mainForm->LogToFile("new_Y_range = " + FloatToStr(new_Y_range));
	//		mainForm->LogToFile("new_center_xx = " + FloatToStr(new_center_xx));
	//		mainForm->LogToFile("new_center_yy = " + FloatToStr(new_center_yy));

			if(!Xplus) new_center_x = -new_center_xx;
			else new_center_x = new_center_xx;
			if(!Yplus) new_center_y = -new_center_yy;
			else new_center_y = new_center_yy;
		}

		new_range = (new_X_range + new_Y_range) / 2;
		int F_new;

		F_new = new_center_x * 1000;
		new_center_x = (double)F_new/1000;

		F_new = new_center_y * 1000;
		new_center_y = (double)F_new/1000;

		F_new = new_range * 1000;
		new_range = (double)F_new/1000;


//		mainForm->LogToFile("TImgForm::PaintBox1MouseUp : new_center_x = " + FloatToStr(new_center_x));
//		mainForm->LogToFile("TImgForm::PaintBox1MouseUp : new_center_y = " + FloatToStr(new_center_y));
//		mainForm->LogToFile("TImgForm::PaintBox1MouseUp : new_range = " + FloatToStr(new_range));

		set_selcet = true;
		SetAdvGlassButton->Enabled = true;

		if(mainForm->AppMode == 7){
			select_litho = true;
			SetFAdvGlassButton->Enabled = true;
		}

	}

}
//---------------------------------------------------------------------------

void __fastcall TImgForm::SetAdvGlassButtonClick(TObject *Sender)
{
	mainForm->LogToFile("TImgForm::SetAdvGlassButtonClick");
	if(set_selcet && (mainForm->GetSecure() == 0 || mainForm->GetSecure() == 8) && mainForm->myScanPanelForm->start){
		mainForm->myScanPanelForm->AdvEditChange(new_center_x, new_center_y, new_range);
		set_selcet = false;
		SetAdvGlassButton->Enabled = false;

		if(mainForm->AppMode == 7){
            select_litho = false;
			SetFAdvGlassButton->Enabled = false;
			mainForm->myLithoFrm->LithoConfigFrm->AdvEditChange(new_center_x, new_center_y, new_range);
		}

		ShowImageNumber();
		PaintBox1->Invalidate();
	}
}
//---------------------------------------------------------------------------

void __fastcall TImgForm::PaintBox1DblClick(TObject *Sender)
{
	if((mainForm->GetSecure() == 0 || mainForm->GetSecure() == 8)   && mainForm->AppMode == 5){
		mainForm->LogToFile("TImgForm::PaintBox1DblClick");
		PaintBox1->Invalidate();
		PainBoxDblClickTimer->Enabled = true;
	}
}
//---------------------------------------------------------------------------

void __fastcall TImgForm::SetFAdvGlassButtonClick(TObject *Sender)
{
	mainForm->LogToFile("TImgForm::SetFAdvGlassButtonClick");

	if(mainForm->AppMode == 5 && mainForm->myForceForm->first){
		if(set_force && (mainForm->GetSecure() == 0 || mainForm->GetSecure() == 8)){
			set_force = false;
			SetFAdvGlassButton->Enabled = false;
			mainForm->myForceForm->AdvEditChange(new_force_x, new_force_y);
		}
	}
	else if(mainForm->AppMode == 7 && mainForm->myLithoFrm->first){
		if(select_litho && (mainForm->GetSecure() == 0 || mainForm->GetSecure() == 8)){
			select_litho = false;
			SetFAdvGlassButton->Enabled = false;
			mainForm->myLithoFrm->LithoConfigFrm->AdvEditChange(new_center_x, new_center_y, new_range);
		}
		ShowImageNumber();
        PaintBox1->Invalidate();
	}
	else{
		PaintBox1->Invalidate();
    }
}
//---------------------------------------------------------------------------


void __fastcall TImgForm::PainBoxDblClickTimerTimer(TObject *Sender)
{
	mainForm->LogToFile("TImgForm::PainBoxDblClickTimerTimer");
	PainBoxDblClickTimer->Enabled = false;
	set_force = true;
	SetFAdvGlassButton->Enabled = true;

	bool Xset = false;
	bool Yset = false;
	int L = PaintBox1->Width;
	double mainXRange = mainForm->myScanPanelForm->X_Range;
	double mainYRange = mainForm->myScanPanelForm->Y_Range;

	int mainX = mainForm->myScanPanelForm->CenterX;
	int mainY = mainForm->myScanPanelForm->CenterY;

//		mainForm->LogToFile("mainX = " + IntToStr(mainX) + " , mainY = " + IntToStr(mainY) + " , mainXRange = " + FloatToStr(mainXRange) + " , mainYRange = " + FloatToStr(mainYRange));

//		mainX = mainX * 167772.14 - 8388607;
//		mainY = mainY * 167772.14 - 8388607;

//		mainForm->LogToFile("mainX = " + IntToStr(mainX) + " , mainY = " + IntToStr(mainY));

	int xf = ((int)PaintBox1->ScreenToClient(Mouse->CursorPos).X);
	int yf = ((int)PaintBox1->ScreenToClient(Mouse->CursorPos).Y);

	TPoint p[2];
	p[0] = TPoint(xf, yf+10);
	p[1] = TPoint(xf, yf-10);
	PaintBox1->Canvas->Polyline(p, 1);
	p[0] = TPoint(xf+10, yf);
	p[1] = TPoint(xf-10, yf);
//	p[2] = TPoint(xf+3, yf-3);
//	p[3] = TPoint(xf-3, yf-3);
//	p[4] = TPoint(xf-3, yf+3);
	PaintBox1->Canvas->Polyline(p, 1);


//		mainForm->LogToFile("xf = " + IntToStr(xf) + " , yf = " + IntToStr(yf));

	int center = L/2.0;

//		mainForm->LogToFile("cx = " + IntToStr(center) + " , cy = " + IntToStr(center));

	double w = abs(xf - center);
	double h = abs(yf - center);
//		mainForm->LogToFile("w = " + FloatToStr(w) + " , h = " + FloatToStr(h));

	w = w / (double)L;
	h = h / (double)L;

//		mainForm->LogToFile("w = " + FloatToStr(w) + " , h = " + FloatToStr(h));


	w = w * mainXRange;
	h = h * mainYRange;
//		mainForm->LogToFile("w = " + FloatToStr(w) + " , h = " + FloatToStr(h));

//		w = w * 167772.14/2.0;
//		h = h * 167772.14/2.0;


	if(xf > center){
		new_force_x = mainX + w;
	}
	else{
		new_force_x = mainX - w;
	}

	if(yf < center){
		new_force_y = mainY + h;
	}
	else{
		new_force_y = mainY - h;
	}


	if(AllScale){
		double new_force_xx;
		bool Xplus = false;
		if(new_force_x > 50){
			new_force_xx = new_force_x - 50;
			Xplus = true;
		}
		else new_force_xx = 50 - new_force_x;

		double new_force_yy;
		bool Yplus = false;
		if(new_force_y > 50) {
			new_force_yy = new_force_y - 50;
			Yplus = true;
		}
		else new_force_yy = 50 - new_force_y;

        float min_XRange = 100;
		float min_YRange = 100;
		int new_force_xx_index = 0;
		int new_force_yy_index = 0;

		for (int i = 0; i < mainForm->Max_Range; i++) {
			if (min_XRange > abs(new_force_xx-mainForm->X_Range[i])){
				min_XRange = abs(new_force_xx-mainForm->X_Range[i]);
				new_force_xx_index = i;
			}
			if (min_YRange > abs(new_force_yy-mainForm->Y_Range[i])){
				min_YRange = abs(new_force_yy-mainForm->Y_Range[i]);
				new_force_yy_index = i;
			}
		}

		if(new_force_xx-mainForm->X_Range[new_force_xx_index] >= 0){
			double deltaX = 1;
			if(new_force_xx_index != mainForm->Max_Range)
				deltaX = mainForm->X_Range[new_force_xx_index+1] - mainForm->X_Range[new_force_xx_index];
			if(deltaX == 0)
				deltaX = 1;
			new_force_xx = new_force_xx_index + (new_force_xx - mainForm->X_Range[new_force_xx_index]) / deltaX ;
		}
		else {
			double deltaX = 1;
			if(new_force_xx_index != 0)
				deltaX = mainForm->X_Range[new_force_xx_index] - mainForm->X_Range[new_force_xx_index-1];
			if(deltaX == 0)
				deltaX = 1;
			new_force_xx = new_force_xx_index + (new_force_xx - mainForm->X_Range[new_force_xx_index]) / deltaX;
		}


		if(new_force_yy-mainForm->Y_Range[new_force_yy_index] >= 0){
			double deltaY = 1;
			if(new_force_yy_index != mainForm->Max_Range)
				deltaY = mainForm->Y_Range[new_force_yy_index+1] - mainForm->Y_Range[new_force_yy_index];
			if(deltaY == 0)
				deltaY = 1;
			new_force_yy = new_force_yy_index + (new_force_yy - mainForm->Y_Range[new_force_yy_index]) / deltaY;
		}
		else{
            double deltaY = 1;
			if(new_force_yy_index != 0)
				deltaY = mainForm->Y_Range[new_force_yy_index] - mainForm->Y_Range[new_force_yy_index-1];
			if(deltaY == 0)
				deltaY = 1;
			new_force_yy = new_force_yy_index + (new_force_yy - mainForm->Y_Range[new_force_yy_index]) / deltaY;
		}
//		mainForm->LogToFile("new_force_xx = " + FloatToStr(new_force_xx) + " ,new_force_yy = " + FloatToStr(new_force_yy) );
		if(!Xplus) new_force_x = -new_force_xx;
		else new_force_x = new_force_xx;
		if(!Yplus) new_force_y = -new_force_yy;
		else new_force_y = new_force_yy;

	}


    int F_new;

	F_new = new_force_x * 1000;
	new_force_x = (double)F_new/1000;

	F_new = new_force_y * 1000;
	new_force_y = (double)F_new/1000;


//	switch (Scanner_Type){
//		case 0:{
//			new_force_x =  8388607 - new_force_x * 167772.14;
//			new_force_y =  new_force_y * 167772.14 - 8388607;
//		}
//		case 1:{
//			new_force_x =  8388607 - new_force_x * 167772.14;
//			new_force_y =  8388607 - new_force_y * 167772.14;
//		}
//		case 2:{
//			new_force_x =  new_force_x * 167772.14 - 8388607;
//			new_force_y =  8388607 - new_force_y * 167772.14;
//		}
//		case 3:{
//			new_force_x =  new_force_x * 167772.14 - 8388607;
//			new_force_y =  new_force_y * 167772.14 - 8388607;
//		}
//	}

//	mainForm->LogToFile("new_force_x = " + FloatToStr(new_force_x) + " , new_force_y = " + FloatToStr(new_force_y));
    SetFAdvGlassButtonClick(NULL);

}
//---------------------------------------------------------------------------

void __fastcall TImgForm::SaveButtonClick(TObject *Sender)
{
	SaveImages = true;
	SaveButton->Caption = "Images Saved";
    SaveButton->Enabled = false;
}
//---------------------------------------------------------------------------




void __fastcall TImgForm::ScrollBox1MouseWheelDown(TObject *Sender, TShiftState Shift,
          TPoint &MousePos, bool &Handled)
{
	ScrollBox1->VertScrollBar->Position += 10;
}
//---------------------------------------------------------------------------

void __fastcall TImgForm::ScrollBox1MouseWheelUp(TObject *Sender, TShiftState Shift,
          TPoint &MousePos, bool &Handled)
{
	ScrollBox1->VertScrollBar->Position -= 10;
}
//---------------------------------------------------------------------------


