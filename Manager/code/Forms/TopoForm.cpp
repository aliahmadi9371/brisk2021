//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "TopoForm.h"
#include "mainUnit.cpp"
//---------------------------------------------------------------------------
#pragma resource "*.dfm"
TTopoFrm *TopoFrm;
//---------------------------------------------------------------------------
__fastcall TTopoFrm::TTopoFrm(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TTopoFrm::FormCreate(TObject *Sender)
{
	this->Hide();
	TopoChart->ScrollMouseButton = mbRight;
	TopoChart->ClipPoints = false;
	TopoChart->Title->Visible = false;
	TopoChart ->Legend->Visible = false;
	TopoChart->LeftAxis->Automatic = true;
	TopoChart->LeftAxis->Axis->Width = 1;
	TopoChart->BottomAxis->Axis->Width = 1;
	TopoChart->BottomAxis->RoundFirstLabel = false;
	TopoChart->BottomAxis->Automatic = false;
	TopoChart->View3D = false;
	TopoChart->Axes->FastCalc = true;
	TopoChart->AutoRepaint = false;
	TopoChart->Canvas->ReferenceCanvas->Pen->OwnerCriticalSection = NULL;

	TopoChart->Hover->Visible = false;

	TopoFWSeries->LinePen->OwnerCriticalSection = NULL;
	TopoBWSeries->LinePen->OwnerCriticalSection = NULL;
}
//---------------------------------------------------------------------------
void __fastcall TTopoFrm::ImagesButtonClick(TObject *Sender)
{
	this->Hide();
    mainForm->myImageFrom->Show();
}
//---------------------------------------------------------------------------
