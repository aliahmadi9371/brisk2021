//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Image.h"
#include "mainUnit.h"
#include "PntForm.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "hyiedefs"
#pragma link "hyieutils"
#pragma link "iesettings"
#pragma link "ieview"
#pragma link "iexBitmaps"
#pragma link "iexLayers"
#pragma link "iexRulers"
#pragma link "imageenview"
#pragma resource "*.dfm"
TImageShapeForm *ImageShapeForm;

#include "GalleryForm.h"
//---------------------------------------------------------------------------
__fastcall TImageShapeForm::TImageShapeForm(TComponent* Owner)
	: TForm(Owner)
{

}
//---------------------------------------------------------------------------

void __fastcall TImageShapeForm::FormCreate(TObject *Sender)
{
	this->Hide();
}
//---------------------------------------------------------------------------

void __fastcall TImageShapeForm::ImageDblClick(TObject *Sender)
{
	mainForm->LogToFile("TImageShapeForm::ImageDblClick");
	GalleyForm->Osc_PreviousState = false;
	for(int i=0; i<4; i++){
		if(mainForm->myOscForm->my_plot_set[i].bool_PlotPlay){
			GalleyForm->Osc_PreviousState = true;
			mainForm->myOscForm->p1PauseClick(NULL);
		}
	}
	mainForm->myVideoForm->VideoGrabber1->StopPreview();
	GalleyForm->myViewer->current_image_count =  GalleyForm->currentimagecount;
	GalleyForm->myViewer->current_image_number = image_number;
	mainForm->Enabled = false;

	GalleyForm->myViewer->Show();
}
//---------------------------------------------------------------------------

void TImageShapeForm::CreateObject(int Resolution)
{
//	mainForm->LogToFile("TImageShapeForm::CreateObject , Resolution = " + IntToStr(Resolution));
	Main = new int[Resolution*Resolution];
}
//---------------------------------------------------------------------------

void __fastcall TImageShapeForm::FormDestroy(TObject *Sender)
{
    if(Main){
		delete[] Main;
		Main = NULL;
	}
}
//---------------------------------------------------------------------------

