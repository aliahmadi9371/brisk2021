//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "VidClass.h"
#include "mainUnit.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "VidGrab"
#pragma link "AdvGroupBox"
#pragma link "PickDlg"
#pragma link "AdvGlowButton"
#pragma link "AdvShapeButton"
#pragma resource "*.dfm"
TVidForm *VidForm;
//---------------------------------------------------------------------------
__fastcall TVidForm::TVidForm(TComponent* Owner)
	: TForm(Owner)
{

}
//---------------------------------------------------------------------------

void __fastcall TVidForm::FormCreate(TObject *Sender)
{
	this->Hide();

	Camera_Index = -1;
	first = false;
	record = false;

	FrontButton->Hide();
	BackButton->Hide();
	LeftButton->Hide();
	RightButton->Hide();
//
	SetButton->Hide();
//	ShotButton->Hide();

	myVidSettingForm = new TVidSettingFrm(this);
	myVidSettingForm->Height = 400;
	myVidSettingForm->Width = 520;
	myVidSettingForm->Top = mainForm->Height/2 - myVidSettingForm->Height/2;
	myVidSettingForm->Left = mainForm->Width/2 - myVidSettingForm->Width/2;

	myVidSettingForm->PanelLogo->Height = 70;
	myVidSettingForm->ImageLogo->Height = 50;
	myVidSettingForm->ImageLogo->Width = 60;
	myVidSettingForm->ImageLogo->Top = 10;
	myVidSettingForm->ImageLogo->Left = 10;

	myVidSettingForm->PanelCameraName->Height = 90;
	myVidSettingForm->DeviceNameEditLbl->Height = 28;
	myVidSettingForm->DeviceNameEdit->Height = 30;
	myVidSettingForm->DeviceNameEdit->Width = myVidSettingForm->PanelCameraName->Width - myVidSettingForm->DeviceNameEditLbl->Left * 2;
	myVidSettingForm->DeviceNameEdit->Left =  myVidSettingForm->DeviceNameEditLbl->Left;

	myVidSettingForm->PanelResolution->Height = 90;
	myVidSettingForm->ResoulitionAdvComboBoxLbl->Height = 28;
	myVidSettingForm->ResoulitionAdvComboBox->Height = 33;
	myVidSettingForm->ResoulitionAdvComboBox->Left = 5;
	myVidSettingForm->ResoulitionAdvComboBox->Width = 250;

	myVidSettingForm->PanelCamera->Height = 90;
	myVidSettingForm->CameraAdvComboBoxLbl->Height = 28;
	myVidSettingForm->CameraAdvComboBox->Height = 33;
	myVidSettingForm->CameraAdvComboBox->Left = 5;
	myVidSettingForm->CameraAdvComboBox->Width = 250;


	VideoGrabber1->AudioRecording = false;
}
//---------------------------------------------------------------------------

void __fastcall TVidForm::FormShow(TObject *Sender)
{
	if(!first){
		first = true;
		myVidSettingForm->CameraAdvComboBox->Items->Clear();
		myVidSettingForm->ResoulitionAdvComboBox->Items->Clear();
		mainForm->LogToFile("TVidForm: FormShow: VideoDevicesCount: " + IntToStr(VideoGrabber1->VideoDevicesCount));
		usb_camera = false;
		Camera_Index = -1;
		if(VideoGrabber1->VideoDevicesCount > 0){
			Camera_Index = 0;
			for(int i=0; i<VideoGrabber1->VideoDevicesCount; i++){
				VideoGrabber1->VideoDevice = i;
                if(VideoGrabber1->VideoDeviceName.LowerCase() == "usb camera"){
					Camera_Index = i;
					usb_camera = true;
				}
			}

			if(usb_camera){
                VideoGrabber1->VideoDevice = Camera_Index;

				mainForm->LogToFile("TVidForm: FormShow: Camera_Index: " + IntToStr(Camera_Index));
				mainForm->LogToFile("TVidForm: FormShow: Devce Id: " + VideoGrabber1->VideoDevicesId.LowerCase());
				mainForm->LogToFile("TVidForm: FormShow: Device Name: " + VideoGrabber1->VideoDeviceName.LowerCase());

				myVidSettingForm->CameraAdvComboBox->DropDownCount = VideoGrabber1->VideoDevicesCount;
				myVidSettingForm->CameraAdvComboBox->Items->Text = VideoGrabber1->VideoDevices;
				myVidSettingForm->ResoulitionAdvComboBox->DropDownCount = VideoGrabber1->VideoSizesCount;
				myVidSettingForm->ResoulitionAdvComboBox->Items->Text = VideoGrabber1->VideoSizes;
				myVidSettingForm->DeviceNameEdit->Caption = VideoGrabber1->VideoDeviceName;

				myVidSettingForm->CameraAdvComboBox->Hide();
				myVidSettingForm->CameraAdvComboBoxLbl->Hide();


				VideoGrabber1->VideoDevice = Camera_Index;
				VideoGrabber1->AutoRefreshPreview = true;

				if(VideoGrabber1->VideoSizesCount > 1){
					VideoGrabber1->VideoSize = 1;
				}
				else{
					VideoGrabber1->VideoSize = 0;
				}

				VideoGrabber1->FrameGrabber = fg_PreviewStream;
				VideoGrabber1->Display_AspectRatio = ar_Stretch;
				VideoGrabber1->Display_Embedded_FitParent = true;
				int preview = VideoGrabber1->StartPreview();
				mainForm->LogToFile("TVidForm: FormShow: StartPreview: " + IntToStr(preview));

				myVidSettingForm->CameraAdvComboBox->ItemIndex = Camera_Index;
				myVidSettingForm->ResoulitionAdvComboBox->ItemIndex = 1;

			}
			else{
				mainForm->LogToFile("TVidForm: FormShow: Camera not found");
//				VideoGrabber1->Color = clWhite;
				mainForm->Label4->Visible = true;;
				mainForm->Label4->Show();
				LeftButton->Hide();
				RightButton->Hide();
				BackButton->Hide();
				FrontButton->Hide();
				SetButton->Hide();

				LeftButton->SendToBack();
				RightButton->SendToBack();
				BackButton->SendToBack();
				FrontButton->SendToBack();
				SetButton->SendToBack();
			}
		}
	}


	LeftButton->Top =  this->Height/2 - LeftButton->Height/2;
	LeftButton->Left = 20;

	RightButton->Top =  this->Height/2 - RightButton->Height/2;
	RightButton->Left = this->Width - RightButton->Width - 20;

	FrontButton->Top =  20;
	FrontButton->Left = this->Width/2 - FrontButton->Width/2;

	BackButton->Top =  this->Height - BackButton->Height - 20;
	BackButton->Left = this->Width/2 - BackButton->Width/2;

	SetButton->Top = 20;
	SetButton->Left = this->Width - SetButton->Width - 20;
}
//---------------------------------------------------------------------------

void __fastcall TVidForm::StepperStage()
{
	mainForm->myCommandCreatorThread->StartStageClick(StateM,StatusMove,Stop,SShift);
}
//---------------------------------------------------------------------------

void __fastcall TVidForm::LeftButton1MouseDown(TObject *Sender, TMouseButton Button,
		  TShiftState Shift, int X, int Y)
{
	mainForm->CameraMoving = true;
	mainForm->GetSecure();
	if ( (Button == mbLeft) && (Shift.ToInt() == ssShift || mainForm->myMovingPanelForm->FastStage) )
		SShift = true;
	else
		SShift = false;

	Left_start();
}
//---------------------------------------------------------------------------

void TVidForm::Left_start()
{
//	mainForm->LogToFile("left button start");
	StateM = 0;
	StatusMove = 1;
	Stop = 0;

	TThread::Synchronize(mainForm->myCommandCreatorThread,StepperStage);
}
//---------------------------------------------------------------------------

void __fastcall TVidForm::LeftButton1MouseUp(TObject *Sender, TMouseButton Button,
		  TShiftState Shift, int X, int Y)
{
	mainForm->CameraMoving = false;
	mainForm->GetSecure();
	Left_stop();
}
//---------------------------------------------------------------------------

void TVidForm::Left_stop()
{
//	mainForm->LogToFile("left button stop");
	StateM = 1;
	StatusMove = 1;
	Stop = 1;
	SShift = false;

	TThread::Synchronize(mainForm->myCommandCreatorThread,StepperStage);
}
//---------------------------------------------------------------------------

void __fastcall TVidForm::FrontButton1MouseDown(TObject *Sender, TMouseButton Button,
		  TShiftState Shift, int X, int Y)
{
	mainForm->CameraMoving = true;
	mainForm->GetSecure();
	if ( (Button == mbLeft) && (Shift.ToInt() == ssShift || mainForm->myMovingPanelForm->FastStage) )
		SShift = true;
	else
		SShift = false;
	Front_start();
}
//---------------------------------------------------------------------------

void TVidForm::Front_start()
{
//	mainForm->LogToFile("front button start");
	StateM = 1;
	StatusMove = 0;
	Stop = 0;

	TThread::Synchronize(mainForm->myCommandCreatorThread,StepperStage);
}
//---------------------------------------------------------------------------

void __fastcall TVidForm::FrontButton1MouseUp(TObject *Sender, TMouseButton Button,
		  TShiftState Shift, int X, int Y)
{
	mainForm->CameraMoving = false;
	mainForm->GetSecure();
	Front_stop();
}
//---------------------------------------------------------------------------

void TVidForm::Front_stop()
{
//	mainForm->LogToFile("front button stop");
	StateM = 1;
	StatusMove = 0;
	Stop = 1;
	SShift = false;

	TThread::Synchronize(mainForm->myCommandCreatorThread,StepperStage);
}
//---------------------------------------------------------------------------

void __fastcall TVidForm::RightButton1MouseDown(TObject *Sender, TMouseButton Button,
		  TShiftState Shift, int X, int Y)
{
	mainForm->CameraMoving = true;
	mainForm->GetSecure();
	if ( (Button == mbLeft) && (Shift.ToInt() == ssShift || mainForm->myMovingPanelForm->FastStage) )
		SShift = true;
	else
		SShift = false;
	Right_start();
}
//---------------------------------------------------------------------------

void TVidForm::Right_start()
{
//	mainForm->LogToFile("right button start");
	StateM = 1;
	StatusMove = 1;
	Stop = 0;

	TThread::Synchronize(mainForm->myCommandCreatorThread,StepperStage);
}
//---------------------------------------------------------------------------


void __fastcall TVidForm::RightButton1MouseUp(TObject *Sender, TMouseButton Button,
		  TShiftState Shift, int X, int Y)
{
	mainForm->CameraMoving = false;
	mainForm->GetSecure();
	Right_stop();
}
//---------------------------------------------------------------------------

void TVidForm::Right_stop()
{
//	mainForm->LogToFile("right button stop");
	StateM = 0;
	StatusMove = 1;
	Stop = 1;
	SShift = false;

	TThread::Synchronize(mainForm->myCommandCreatorThread,StepperStage);
}
//---------------------------------------------------------------------------

void __fastcall TVidForm::BackButton1MouseDown(TObject *Sender, TMouseButton Button,
		  TShiftState Shift, int X, int Y)
{
	mainForm->CameraMoving = true;
	mainForm->GetSecure();
	if ( (Button == mbLeft) && (Shift.ToInt() == ssShift || mainForm->myMovingPanelForm->FastStage) )
		SShift = true;
	else
		SShift = false;
	Back_start();
}
//---------------------------------------------------------------------------

void TVidForm::Back_start()
{
//	mainForm->LogToFile("back button start");
	StateM = 0;
	StatusMove = 0;
	Stop = 0;

	TThread::Synchronize(mainForm->myCommandCreatorThread,StepperStage);
}
//---------------------------------------------------------------------------


void __fastcall TVidForm::BackButton1MouseUp(TObject *Sender, TMouseButton Button,
		  TShiftState Shift, int X, int Y)
{
	mainForm->CameraMoving = false;
	mainForm->GetSecure();
	Back_stop();
}
//---------------------------------------------------------------------------

void TVidForm::Back_stop()
{
//	mainForm->LogToFile("back button stop");
	StateM = 0;
	StatusMove = 0;
	Stop = 1;
	SShift = false;

	TThread::Synchronize(mainForm->myCommandCreatorThread,StepperStage);
}
//---------------------------------------------------------------------------

void TVidForm::EnableStage(bool enabled)
{
	if(enabled){
		LeftButton->Enabled = true;
		RightButton->Enabled = true;
		FrontButton->Enabled = true;
		BackButton->Enabled = true;
	}
	else{
		LeftButton->Enabled = false;
		RightButton->Enabled = false;
		FrontButton->Enabled = false;
		BackButton->Enabled = false;
	}
}
//---------------------------------------------------------------------------

void __fastcall TVidForm::SetButton1Click(TObject *Sender)
{
	if( !(myVidSettingForm->Visible) )
		myVidSettingForm->Show();
}
//---------------------------------------------------------------------------

void __fastcall TVidForm::ShotButtonClick(TObject *Sender)
{
	if(!record){
		record = true;
		SetRecordFile();
		VideoGrabber1->StartRecording();
	}
	else{
		record = false;
		VideoGrabber1->StopRecording();
		VideoGrabber1->StartPreview();
	}
}
//---------------------------------------------------------------------------

void TVidForm::SetRecordFile()
{
	TDateTime dateTime;
	UnicodeString source;
	UnicodeString time = dateTime.CurrentDateTime().FormatString("hhMMss");
	UnicodeString date = dateTime.CurrentDateTime().FormatString("yyyymmdd");
	UnicodeString RecordFolder = DownloadPath;

	if( !DirectoryExists(RecordFolder) ){
		AnsiString dir = RecordFolder;
		CreateDirectoryA(dir.c_str(),NULL);
	}
	switch(mainForm->AppMode){
		case 1:{
			if( !DirectoryExists(RecordFolder + "/" + "records/Contact") ){
				AnsiString dir = RecordFolder + "/" + "records/Contact";
				CreateDirectoryA(dir.c_str(),NULL);
			}
			if( !DirectoryExists(RecordFolder + "/" + "records/Contact/Vid") ){
				AnsiString dir = RecordFolder + "/" + "records/Contact/Vid";
				CreateDirectoryA(dir.c_str(),NULL);
			}
			if(!DirectoryExists(RecordFolder + "/" + "records/Contact/Vid"+ date)){
				AnsiString dir = RecordFolder + "/" + "records/Contact/Vid" + date;
				CreateDirectoryA(dir.c_str(),NULL);
			}
			source = RecordFolder + "/" + "records/Contact/Vid" + "/" + date + "/" + "time_";
			break;
		}
		case 2:{
			if( !DirectoryExists(RecordFolder + "/" + "records/NonContact") ){
				AnsiString dir = RecordFolder + "/" + "records/NonContact";
				CreateDirectoryA(dir.c_str(),NULL);
			}
			if( !DirectoryExists(RecordFolder + "/" + "records/NonContact/Vid") ){
				AnsiString dir = RecordFolder + "/" + "records/NonContact/Vid";
				CreateDirectoryA(dir.c_str(),NULL);
			}
			if(!DirectoryExists(RecordFolder + "/" + "records/NonContact/Vid"+ date)){
				AnsiString dir = RecordFolder + "/" + "records/NonContact/Vid" + date;
				CreateDirectoryA(dir.c_str(),NULL);
			}
			source = RecordFolder + "/" + "records/NonContact/Vid" + "/" + date + "/" + "time_ ";
			break;
		}

		case 3:{
			if( !DirectoryExists(RecordFolder + "/" + "records/EFM") ){
				AnsiString dir = RecordFolder + "/" + "records/EFM";
				CreateDirectoryA(dir.c_str(),NULL);
			}
			if( !DirectoryExists(RecordFolder + "/" + "records/EFM/Vid") ){
				AnsiString dir = RecordFolder + "/" + "records/EFM/Vid";
				CreateDirectoryA(dir.c_str(),NULL);
			}
			if(!DirectoryExists(RecordFolder + "/" + "records/EFM/Vid"+ date)){
				AnsiString dir = RecordFolder + "/" + "records/EFM/Vid" + date;
				CreateDirectoryA(dir.c_str(),NULL);
			}
			source = RecordFolder + "/" + "records/EFM/Vid" + "/" + date + "/" + "time_ ";
			break;
		}

		case 4:{
			if( !DirectoryExists(RecordFolder + "/" + "records/MFM") ){
				AnsiString dir = RecordFolder + "/" + "records/MFM";
				CreateDirectoryA(dir.c_str(),NULL);
			}
			if( !DirectoryExists(RecordFolder + "/" + "records/MFM/Vid") ){
				AnsiString dir = RecordFolder + "/" + "records/MFM/Vid";
				CreateDirectoryA(dir.c_str(),NULL);
			}
			if(!DirectoryExists(RecordFolder + "/" + "records/MFM/Vid"+ date)){
				AnsiString dir = RecordFolder + "/" + "records/MFM/Vid" + date;
				CreateDirectoryA(dir.c_str(),NULL);
			}
			source = RecordFolder + "/" + "records/MFM/Vid" + "/" + date + "/" + "time_ ";
			break;
		}

		case 5:{
			if( !DirectoryExists(RecordFolder + "/" + "records/ForceSpectroscopy") ){
				AnsiString dir =RecordFolder + "/" + "records/ForceSpectroscopy";
				CreateDirectoryA(dir.c_str(),NULL);
			}
			if( !DirectoryExists(RecordFolder + "/" + "records/ForceSpectroscopy/Vid") ){
				AnsiString dir = RecordFolder + "/" + "records/ForceSpectroscopy/Vid";
				CreateDirectoryA(dir.c_str(),NULL);
			}
			if(!DirectoryExists(RecordFolder + "/" + "records/ForceSpectroscopy/Vid"+ date)){
				AnsiString dir = RecordFolder + "/" + "records/ForceSpectroscopy/Vid" + date;
				CreateDirectoryA(dir.c_str(),NULL);
			}
			source = RecordFolder + "/" + "records/ForceSpectroscopy/Vid" + "/" + date + "/" + "time_ ";
			break;
		}

		case 6:{
			if( !DirectoryExists(RecordFolder + "/" + "records/KPFM") ){
				AnsiString dir =RecordFolder + "/" + "records/KPFM";
				CreateDirectoryA(dir.c_str(),NULL);
			}
			if( !DirectoryExists(RecordFolder + "/" + "records/KPFM/Vid") ){
				AnsiString dir = RecordFolder + "/" + "records/KPFM/Vid";
				CreateDirectoryA(dir.c_str(),NULL);
			}
			if(!DirectoryExists(RecordFolder + "/" + "records/KPFM/Vid"+ date)){
				AnsiString dir = RecordFolder + "/" + "records/KPFM/Vid" + date;
				CreateDirectoryA(dir.c_str(),NULL);
			}
			source = RecordFolder + "/" + "records/KPFM/Vid" + "/" + date + "/" + "time_ ";
			break;
		}

		case 7:{
			if( !DirectoryExists(RecordFolder + "/" + "records/Lithography") ){
				AnsiString dir = RecordFolder + "/" + "records/Lithography";
				CreateDirectoryA(dir.c_str(),NULL);
			}
			if( !DirectoryExists(RecordFolder + "/" + "records/Lithography/Vid") ){
				AnsiString dir = RecordFolder + "/" + "records/Lithography/Vid";
				CreateDirectoryA(dir.c_str(),NULL);
			}
			if(!DirectoryExists(RecordFolder + "/" + "records/Lithography/Vid"+ date)){
				AnsiString dir = RecordFolder + "/" + "records/Lithography/Vid" + date;
				CreateDirectoryA(dir.c_str(),NULL);
			}
			source = RecordFolder + "/" + "records/Lithography/Vid" + "/" + date + "/" + "time_ ";
			break;
		}
		default:
			break;
	}


//	By example if you customize the file name as follows:
	VideoGrabber1->AutoFileName = fn_DateTime;
	VideoGrabber1->AutoFileNameDateTimeFormat = "dd-mm-yy_hh-mm-ss";
	VideoGrabber1->AutoFilePrefix = source;
}
//---------------------------------------------------------------------------

void __fastcall TVidForm::VideoGrabber1MouseEnter(TObject *Sender, int VideoWindow)

{
//	mainForm->LogToFile("TVidForm::VideoGrabber1MouseEnter");
	if(usb_camera){
		FrontButton->Show();
		BackButton->Show();
		LeftButton->Show();
		RightButton->Show();
		SetButton->Show();
	}
}
//---------------------------------------------------------------------------

void __fastcall TVidForm::VideoGrabber1MouseLeave(TObject *Sender, int VideoWindow)

{
//	mainForm->LogToFile("TVidForm::VideoGrabber1MouseLeave");
	mainForm->crslbl_pnl_zoom->Hide();
	if(usb_camera){
		FrontButton->Hide();
		BackButton->Hide();
		LeftButton->Hide();
		RightButton->Hide();
		SetButton->Hide();
	}
}
//---------------------------------------------------------------------------

void TVidForm::BringToFront()
{
	FrontButton->BringToFront();
	BackButton->BringToFront();
	LeftButton->BringToFront();
	RightButton->BringToFront();
	SetButton->BringToFront();
}
//---------------------------------------------------------------------------


