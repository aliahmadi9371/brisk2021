//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "RowConfigFrm.h"
#include "mainUnit.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "AdvGlassButton"
#pragma link "CurvyControls"
#pragma resource "*.dfm"
TRowFrm *RowFrm;
//---------------------------------------------------------------------------
__fastcall TRowFrm::TRowFrm(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TRowFrm::CurvyEdit1Change(TObject *Sender)
{
    CurvyEdit1->Color = clSilver;
}
//---------------------------------------------------------------------------

