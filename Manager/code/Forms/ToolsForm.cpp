//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "ToolsForm.h"
#include "PntForm.h"
#include "mainUnit.h"
#include "defines.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "AdvGlowButton"
#pragma link "AdvSelectors"
#pragma link "AdvGlassButton"
#pragma link "CurvyControls"
#pragma resource "*.dfm"
TToolsFrm *ToolsFrm;
//---------------------------------------------------------------------------
__fastcall TToolsFrm::TToolsFrm(TComponent* Owner)
	: TForm(Owner)
{
	first = false;
}
//---------------------------------------------------------------------------
void __fastcall TToolsFrm::FormCreate(TObject *Sender)
{
	this->Hide();
	this->FormStyle = fsStayOnTop;
    AdvComboBoxTools->ItemIndex = AdvComboBoxTools->Items->Count - 1 ;
}
//---------------------------------------------------------------------------
void __fastcall TToolsFrm::CloseButtonClick(TObject *Sender)
{
	this->Hide();
	PaintForm->Enabled = true;
}
//---------------------------------------------------------------------------
void __fastcall TToolsFrm::FormClose(TObject *Sender, TCloseAction &Action)
{
	Action = Vcl::Forms::caNone;
}
//---------------------------------------------------------------------------
void __fastcall TToolsFrm::FormCloseQuery(TObject *Sender, bool &CanClose)
{
	CanClose = false;
}
//---------------------------------------------------------------------------
void __fastcall TToolsFrm::FormShow(TObject *Sender)
{
	if(!first){
//		mainForm->LogToFile("this->Width = " + IntToStr(this->Width));
//		mainForm->LogToFile("this->Height = " + IntToStr(this->Height));

		CloseButton->Left = 10;
		CloseButton->Top = this->Height - CloseButton->Height - 10;

		int top = 10;
		int left = 10;

		PanelTools->Top = top;
		PanelTools->Left = left;

		PanelColor->Left = left;
		PanelColor->Top = PanelTools->Top + PanelTools->Height + 10;

		PanelWidth->Left = left;
		PanelWidth->Top = PanelColor->Top + PanelColor->Height + 10;

		first = true;
	}
}
//---------------------------------------------------------------------------
void __fastcall TToolsFrm::AdvEditColorChange(TObject *Sender)
{
	if(AdvEditColor->Text.ToInt() < 0)
		AdvEditColor->Text = "0";
	if(AdvEditColor->Text.ToInt() > 255)
		AdvEditColor->Text = "255";
}
//---------------------------------------------------------------------------

void __fastcall TToolsFrm::AdvComboBoxToolsChange(TObject *Sender)
{
	if(AdvComboBoxTools->ItemIndex == 0){   //pen
		PaintForm->Image->Cursor = crMyPenCur;
	}
	else if(AdvComboBoxTools->ItemIndex == 1){	//rect
		PaintForm->Image->Cursor = crMyRectCur;
	}
	else if(AdvComboBoxTools->ItemIndex == 2){	//circle
		PaintForm->Image->Cursor = crMyCircCur;
	}
	else if(AdvComboBoxTools->ItemIndex == 3){	//line
		PaintForm->Image->Cursor = crMyLineCur;
	}
	else if(AdvComboBoxTools->ItemIndex == 4){	//brush
		PaintForm->Image->Cursor = crMyBrushCur;
	}
	else if(AdvComboBoxTools->ItemIndex == 5){	//eraser
		PaintForm->Image->Cursor = crMyEraseCur;
	}
	else if(AdvComboBoxTools->ItemIndex == 6){	//None
		PaintForm->Image->Cursor = crDefault;
	}
}
//---------------------------------------------------------------------------

