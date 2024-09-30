//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "QuestionForm.h"
#include "mainUnit.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "AdvGlowButton"
#pragma link "CurvyControls"
#pragma resource "*.dfm"
TQFrm *QFrm;
//---------------------------------------------------------------------------
__fastcall TQFrm::TQFrm(TComponent* Owner)
	: TForm(Owner)
{

}
//---------------------------------------------------------------------------
void __fastcall TQFrm::Button1Click(TObject *Sender)
{
	this->Hide();
	mainForm->Enabled = false;
	mainForm->myOscForm->pOffButClick(NULL);
}
//---------------------------------------------------------------------------
void __fastcall TQFrm::FormCreate(TObject *Sender)
{
	this->Hide();
}
//---------------------------------------------------------------------------
void __fastcall TQFrm::Button2Click(TObject *Sender)
{
	this->Hide();
	mainForm->Enabled = true;
}
//---------------------------------------------------------------------------
void __fastcall TQFrm::FormShow(TObject *Sender)
{
	mainForm->Enabled = false;
}
//---------------------------------------------------------------------------
void __fastcall TQFrm::FormClose(TObject *Sender, TCloseAction &Action)
{
	this->Hide();
	mainForm->Enabled = true;
}
//---------------------------------------------------------------------------
