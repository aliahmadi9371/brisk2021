//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "ViewerForm.h"
#include "mainUnit.h"
#include "GalleryForm.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "AdvGlowButton"
#pragma resource "*.dfm"
TViewerFrm *ViewerFrm;
//---------------------------------------------------------------------------
__fastcall TViewerFrm::TViewerFrm(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TViewerFrm::FormCreate(TObject *Sender)
{
	this->Hide();

	this->FormStyle = fsStayOnTop;

	first = false;
}
//---------------------------------------------------------------------------
void __fastcall TViewerFrm::FormShow(TObject *Sender)
{
//	mainForm->LogToFile("show image viewer");
	if(!first){
		first = true;
		int w = this->Width - 2*(DBAdvGlowButtonNext->Width + 10);
		int h = w;

		mainForm->LogToFile("w = " + IntToStr(w));
		mainForm->LogToFile("h = " + IntToStr(h));

		Image->Width = w;
		Image->Height = h;
		Image->Left = this->Width/2 - Image->Width/2;
		Image->Top = this->Height/2 - Image->Height/2;

		Label->Left = Image->Left;
		Label->Top = Image->Top - Label->Height - 5;
		Label->Width = Image->Width;

		DBAdvGlowButtonNext->Left = this->Width - DBAdvGlowButtonNext->Width - 5;
		DBAdvGlowButtonPerior->Left = 5;

		DBAdvGlowButtonNext->Top = h/2 - DBAdvGlowButtonNext->Height;
		DBAdvGlowButtonPerior->Top = h/2 - DBAdvGlowButtonNext->Height;

		CloseButton->Left = 5;
		CloseButton->Top = this->Height - CloseButton->Height - 10;
	}

	DBAdvGlowButtonNext->BringToFront();
	DBAdvGlowButtonPerior->BringToFront();

	Image->Picture->Assign(GalleyForm->image_address_array[current_image_number]->Image->Picture);
	Label->Caption = GalleyForm->image_address_array[current_image_number]->LabelName->Caption;

	if(current_image_number < current_image_count-1)
		DBAdvGlowButtonNext->Enabled = true;
	else
		DBAdvGlowButtonNext->Enabled = false;

	if(current_image_number > 0)
		DBAdvGlowButtonPerior->Enabled = true;
	else
		DBAdvGlowButtonPerior->Enabled = false;
}
//---------------------------------------------------------------------------

void __fastcall TViewerFrm::FormClose(TObject *Sender, TCloseAction &Action)
{
	Action = Vcl::Forms::caNone;
}
//---------------------------------------------------------------------------

void __fastcall TViewerFrm::FormCloseQuery(TObject *Sender, bool &CanClose)
{
	CanClose = false;
}
//---------------------------------------------------------------------------
void __fastcall TViewerFrm::CloseButtonClick(TObject *Sender)
{
	mainForm->Enabled = true;
	mainForm->myVideoForm->VideoGrabber1->StartPreview();
	if(mainForm->GalFrm->Osc_PreviousState)
		mainForm->myOscForm->p1PauseClick(NULL);
	this->Hide();
	mainForm->myVideoForm->BringToFront();
}
//---------------------------------------------------------------------------
void __fastcall TViewerFrm::DBAdvGlowButtonNextClick(TObject *Sender)
{
	if(current_image_number < current_image_count-1){
		current_image_number++;
		Image->Picture->Assign(GalleyForm->image_address_array[current_image_number]->Image->Picture);
		Label->Caption = GalleyForm->image_address_array[current_image_number]->LabelName->Caption;
	}

	if(current_image_number < current_image_count-1)
		DBAdvGlowButtonNext->Enabled = true;
	else
		DBAdvGlowButtonNext->Enabled = false;

	if(current_image_number > 0)
		DBAdvGlowButtonPerior->Enabled = true;
	else
		DBAdvGlowButtonPerior->Enabled = false;
}
//---------------------------------------------------------------------------
void __fastcall TViewerFrm::DBAdvGlowButtonPeriorClick(TObject *Sender)
{
	if(current_image_number > 0){
		current_image_number--;
		Image->Picture->Assign(GalleyForm->image_address_array[current_image_number]->Image->Picture);
		Label->Caption = GalleyForm->image_address_array[current_image_number]->LabelName->Caption;
	}

	if(current_image_number < current_image_count-1)
		DBAdvGlowButtonNext->Enabled = true;
	else
		DBAdvGlowButtonNext->Enabled = false;

	if(current_image_number > 0)
		DBAdvGlowButtonPerior->Enabled = true;
	else
		DBAdvGlowButtonPerior->Enabled = false;
}
//---------------------------------------------------------------------------
