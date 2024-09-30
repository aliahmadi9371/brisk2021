//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "OscConfigFrm.h"
#include "mainUnit.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "AdvGlassButton"
#pragma link "CurvyControls"
#pragma resource "*.dfm"

TOscConfigForm *OscConfigForm;
//---------------------------------------------------------------------------
__fastcall TOscConfigForm::TOscConfigForm(TComponent* Owner)
	: TForm(Owner)
{
	first = false;
}
//---------------------------------------------------------------------------

void __fastcall TOscConfigForm::CurvyEdit1Change(TObject *Sender)
{
	CurvyEdit1->Color = clSilver;
}
//---------------------------------------------------------------------------

void __fastcall TOscConfigForm::CurvyEdit2Change(TObject *Sender)
{
	CurvyEdit2->Color = clSilver;
}
//---------------------------------------------------------------------------

void __fastcall TOscConfigForm::CurvyEdit3Change(TObject *Sender)
{
	CurvyEdit3->Color = clSilver;
}
//---------------------------------------------------------------------------

void __fastcall TOscConfigForm::CurvyEdit4Change(TObject *Sender)
{
	CurvyEdit4->Color = clSilver;
}
//---------------------------------------------------------------------------

void __fastcall TOscConfigForm::CurvyEdit5Change(TObject *Sender)
{
	CurvyEdit5->Color = clSilver;
}
//---------------------------------------------------------------------------

