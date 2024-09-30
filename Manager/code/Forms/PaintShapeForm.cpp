//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "PaintShapeForm.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TShapeForm *ShapeForm;
//---------------------------------------------------------------------------
__fastcall TShapeForm::TShapeForm(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TShapeForm::FormCreate(TObject *Sender)
{
    this->Hide();
}
//---------------------------------------------------------------------------
