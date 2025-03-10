//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "LithoDesignPage.h"
#include "mainUnit.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "AdvGlowButton"
#pragma link "hyiedefs"
#pragma link "hyieutils"
#pragma link "iesettings"
#pragma link "ieview"
#pragma link "iexBitmaps"
#pragma link "iexLayers"
#pragma link "iexRulers"
#pragma link "imageenview"
#pragma link "iexBitmaps"
#pragma resource "*.dfm"
TFormLithoDesign *FormLithoDesign;
//---------------------------------------------------------------------------
__fastcall TFormLithoDesign::TFormLithoDesign(TComponent* Owner)
	: TForm(Owner)
{
	mainForm->LogToFile("TFormLithoDesign::TFormLithoDesign");
	first = false;
}
//---------------------------------------------------------------------------

void __fastcall TFormLithoDesign::FormCreate(TObject *Sender)
{
	mainForm->LogToFile("TFormLithoDesign::FormCreate");
	this->Hide();

	CreateObjects();
	InitValues();
	ConfigClass();
}
//---------------------------------------------------------------------------

void TFormLithoDesign::InitValues()
{

}
//---------------------------------------------------------------------------

void TFormLithoDesign::CreateObjects()
{
	mainForm->LogToFile("TFormLithoDesign::CreateObjects");
	myPaintForm = new TPaintForm(this);
	map = new TBitmap;

}
//---------------------------------------------------------------------------

void TFormLithoDesign::ConfigClass()
{

}
//---------------------------------------------------------------------------
void __fastcall TFormLithoDesign::FormShow(TObject *Sender)
{
	mainForm->LogToFile("TFormLithoDesign::FormShow");
	if(!first){

		int w_this = mainForm->myMainControlPanelForm->MainPanel->Width;
		int h_this = mainForm->myMainControlPanelForm->MainPanel->Height - mainForm->myLithoFrm->PanelLithoLabel->Height - mainForm->myLithoFrm->PanelLithoPages->Height;

		this->Width = w_this;
		this->Height = h_this;

//		mainForm->LogToFile("litho w = " + IntToStr(mainForm->myMainControlPanelForm->MainPanel->Width));
//		mainForm->LogToFile("litho h = " + IntToStr(mainForm->myMainControlPanelForm->MainPanel->Height));
//
//		mainForm->LogToFile("litho this->w = " + IntToStr(this->Width));
//		mainForm->LogToFile("litho this->h = " + IntToStr(this->Height));
//
//		mainForm->LogToFile("litho w_this = " + IntToStr(w_this));
//		mainForm->LogToFile("litho h_this = " + IntToStr(h_this));

		int width = w_this - 80;
		int height = h_this - 80;

//		mainForm->LogToFile("litho width = " + IntToStr(width));
//		mainForm->LogToFile("litho height = " + IntToStr(height));


		myPaintForm->Height = mainForm->Height - 20;
		myPaintForm->Width = mainForm->Height - 20;
		myPaintForm->Top = mainForm->Height/2 - myPaintForm->Height/2;
		myPaintForm->Left = mainForm->Width/2 - myPaintForm->Width/2;


		int l;
		int ll;

		if(width > height)
			l = height;
		else
			l = width;

		ll = l/2;

//		mainForm->LogToFile("litho l = " + IntToStr(l));

		PanelPaint->Width = l;
		PanelPaint->Height = l;
		PanelPaint->Left = this->Width/2 - l/2;
		PanelPaint->Top = 5;

		ViewButton->Left = 5;
		ViewButton->Top = 5;
//
        InitPaint(false);
		first = true;
	}

}
//---------------------------------------------------------------------------

void TFormLithoDesign::InitPaint(bool state)
{
	mainForm->LogToFile("TFormLithoDesign::InitPaint , state = " + BoolToStr(state,true));
	if(state){
		Image->Align = alNone;
		Image->Stretch = false;
		Image->Width = Image->Picture->Bitmap->Width;
		Image->Height = Image->Picture->Bitmap->Height;
		Image->Left = ScrollBox->Width/2 - Image->Width/2;
		Image->Top = ScrollBox->Height/2 - Image->Height/2;
	}
	else{
        Image->Align = alNone;
		Image->Stretch = false;
		Image->Width = mainForm->myLithoFrm->LithoConfigFrm->scan_resolution;
		Image->Height = mainForm->myLithoFrm->LithoConfigFrm->scan_resolution;
		Image->Left = ScrollBox->Width/2 - Image->Width/2;
		Image->Top = ScrollBox->Height/2 - Image->Height/2;
	}
	myPaintForm->AdvEditResolution->Text = IntToStr(mainForm->myLithoFrm->LithoConfigFrm->scan_resolution);

}
//---------------------------------------------------------------------------

void __fastcall TFormLithoDesign::ViewButtonClick(TObject *Sender)
{
	mainForm->LogToFile("TFormLithoDesign::ViewButtonClick");
//	mainForm->myOscForm->p1PauseClick(NULL);
	Osc_PreviousState = false;
	for(int i=0; i<4; i++){
		if(mainForm->myOscForm->my_plot_set[i].bool_PlotPlay){
			Osc_PreviousState = true;
			mainForm->myOscForm->p1PauseClick(NULL);
		}
	}
	mainForm->myVideoForm->VideoGrabber1->StopPreview();
	myPaintForm->Show();
}
//---------------------------------------------------------------------------

void __fastcall TFormLithoDesign::ImageDblClick(TObject *Sender)
{
	mainForm->LogToFile("TFormLithoDesign::ImageDblClick");
	mainForm->myOscForm->p1PauseClick(NULL);
	mainForm->myVideoForm->VideoGrabber1->StopPreview();
	myPaintForm->Show();
}
//---------------------------------------------------------------------------


