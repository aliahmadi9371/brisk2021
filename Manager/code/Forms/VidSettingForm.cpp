//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "VidSettingForm.h"
#include "mainUnit.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "AdvCombo"
#pragma link "CalcEdit"
#pragma link "CurvyControls"
#pragma link "AdvGlassButton"
#pragma resource "*.dfm"
TVidSettingFrm *VidSettingFrm;
//---------------------------------------------------------------------------
__fastcall TVidSettingFrm::TVidSettingFrm(TComponent* Owner)
	: TForm(Owner)
{

}
//---------------------------------------------------------------------------
void __fastcall TVidSettingFrm::FormCreate(TObject *Sender)
{
	this->Hide();
	this->FormStyle = fsStayOnTop;

}
//---------------------------------------------------------------------------
void __fastcall TVidSettingFrm::CameraAdvComboBoxChange(TObject *Sender)
{
	mainForm->myVideoForm->VideoGrabber1->StopPreview();
	mainForm->myVideoForm->VideoGrabber1->VideoDevice = CameraAdvComboBox->ItemIndex;
	ResoulitionAdvComboBox->DropDownCount = mainForm->myVideoForm->VideoGrabber1->VideoSizesCount;
	ResoulitionAdvComboBox->Items->Text = mainForm->myVideoForm->VideoGrabber1->VideoSizes;
	ResoulitionAdvComboBox->ItemIndex = 1;
	DeviceNameEdit->Caption = mainForm->myVideoForm->VideoGrabber1->VideoDeviceName;
	mainForm->myVideoForm->VideoGrabber1->StartPreview();

	mainForm->myVideoForm->Refresh();
	mainForm->myVideoForm->VideoGrabber1->BringToFront();
	mainForm->myVideoForm->BackButton->BringToFront();
	mainForm->myVideoForm->FrontButton->BringToFront();
	mainForm->myVideoForm->LeftButton->BringToFront();
	mainForm->myVideoForm->RightButton->BringToFront();
	mainForm->myVideoForm->SetButton->BringToFront();
}
//---------------------------------------------------------------------------
void __fastcall TVidSettingFrm::ResoulitionAdvComboBoxChange(TObject *Sender)
{
	mainForm->myVideoForm->VideoGrabber1->StopPreview();
	mainForm->myVideoForm->VideoGrabber1->VideoSize = ResoulitionAdvComboBox->ItemIndex;
	mainForm->myVideoForm->VideoGrabber1->StartPreview();

	mainForm->myVideoForm->Refresh();
	mainForm->myVideoForm->VideoGrabber1->BringToFront();
	mainForm->myVideoForm->BackButton->BringToFront();
	mainForm->myVideoForm->FrontButton->BringToFront();
	mainForm->myVideoForm->LeftButton->BringToFront();
	mainForm->myVideoForm->RightButton->BringToFront();
	mainForm->myVideoForm->SetButton->BringToFront();

}
//---------------------------------------------------------------------------
