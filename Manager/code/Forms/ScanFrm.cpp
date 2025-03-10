//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "ScanFrm.h"
#include "mainUnit.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "AdvCombo"
#pragma link "AdvEdit"
#pragma link "AdvGlowButton"
#pragma link "CalcEdit"
#pragma link "CurvyControls"
#pragma link "AdvGlassButton"
#pragma link "AdvPanel"
#pragma resource "*.dfm"
TScanPanelForm *ScanPanelForm;
//---------------------------------------------------------------------------
__fastcall TScanPanelForm::TScanPanelForm(TComponent* Owner)
	: TForm(Owner)
{
	AdvComboBoxResolution->ItemIndex = 0;

	One_D = false;
	Two_D = false;

	for(int i=1; i<10; i++){
		X_Center[i] = -1;
		Y_Center[i] = -1;
		XY_Range[i] = -1;
	}

	HistoryIndex = -1;
	HistoryCount = 0;

    CurrentZ = -1;

}
//---------------------------------------------------------------------------

void TScanPanelForm::AddToHistory()
{
	mainForm->LogToFile("TScanPanelForm::AddToHistory");
//	mainForm->LogToFile("can add to history : history count = " + IntToStr(HistoryCount));
//	mainForm->LogToFile("can add to history : history index = " + IntToStr(HistoryIndex));
	double x = Center_X_um;
	double y = Center_Y_um;
	double r = Range;
	bool NewHistory = true;

	for(int i=0; i<HistoryCount; i++){
		if( (x == X_Center[i]) && (y == Y_Center[i]) && (r == XY_Range[i]) ){
			NewHistory = false;
//			mainForm->LogToFile("can not add to history");
		}
	}

	if(NewHistory){
		AdvComboBoxSelect->Items->Clear();
		if(HistoryCount < 10){
			HistoryCount++;
			HistoryIndex++;

			X_Center[HistoryIndex] = x;
			Y_Center[HistoryIndex] = y;
			XY_Range[HistoryIndex] = r;

			for(int i=0; i<HistoryCount; i++){
				AdvComboBoxSelect->Items->Add(FloatToStr(X_Center[i]) + " , " + FloatToStr(Y_Center[i]) + " : " + FloatToStr(XY_Range[i]));
			}
		}
		else if(HistoryCount == 10){
//			mainForm->LogToFile("can add to history after 10");
			if(HistoryIndex == 9)
				HistoryIndex = 0;

			X_Center[HistoryIndex] = x;
			Y_Center[HistoryIndex] = y;
			XY_Range[HistoryIndex] = r;

			HistoryIndex++;

			for(int i=0; i<HistoryCount; i++){
				AdvComboBoxSelect->Items->Add(FloatToStr(X_Center[i]) + " , " + FloatToStr(Y_Center[i]) + " : " + FloatToStr(XY_Range[i]));
			}
		}
		else{
		}
	}
	AdvComboBoxSelect->ItemIndex = -1;
//	mainForm->LogToFile("can add to history : history count = " + IntToStr(HistoryCount));
//	mainForm->LogToFile("can add to history : history index = " + IntToStr(HistoryIndex));
}
//---------------------------------------------------------------------------

void __fastcall TScanPanelForm::FormCreate(TObject *Sender)
{

	this->Hide();

	LastScanChanger = -1;

	One_D = false;
	OneD_CheckBox->Checked = One_D;

	Two_D = false;
	TwoD_CheckBox->Checked = Two_D;

	start = false;


//	ScanStatusLabel->Hide();
	GetIniToUi();
}
//---------------------------------------------------------------------------

void TScanPanelForm::GetIniToUi()
{

	Resolution = ScanTable.Scan_Resolution_Val;
	Angle = ScanTable.Scan_Angle_Val;
	Range = ScanTable.Scan_Range_Val;
	OverScan = ScanTable.Scan_OverScan_Val;
	Speed = ScanTable.Scan_Speed_Val;
	CenterX = ScanTable.Scan_X_Center_Val;
	CenterY = ScanTable.Scan_Y_Center_Val;
	FlyOffset = ScanTable.Scan_Offset_val;
	Max_Range = HardwareTable.Max_Range;
	KdApp = ApproachTable.Apr_Kd_Val;
	KpApp = ApproachTable.Apr_Kp_Val;
	KiFeedback_Contact = ApproachTable.Apr_KiFeedbak_Val_Contact;
	KiFeedback_NonContact = ApproachTable.Apr_KiFeedbak_Val_NonContact;
	FlyOffset_index = OscTable[3].index;
	FlyOffset_Scale = OscTable[3].scale;
	BiasApp = ApproachTable.Apr_Bias_Val;

	if(CenterX > Max_Range/2) CenterX = Max_Range/2;
	if(CenterX < -Max_Range/2) CenterX = -Max_Range/2;

	if(CenterY > Max_Range/2) CenterY = Max_Range/2;
	if(CenterY < -Max_Range/2) CenterY = -Max_Range/2;

	if(Range > Max_Range) Range = Max_Range;
	if(Range < 0) Range = 0;

	int overscan_tmp = floor( (OverScan * Resolution) + 0.5 );

	if(overscan_tmp == 0){
		OverScan = 1;
		ScanTable.Scan_OverScan_Val = OverScan;

	}



	One_D = ScanTable.Scan_1D_Leveling;
	OneD_CheckBox->Checked = One_D;
	Two_D = ScanTable.Scan_2D_Leveling;
	TwoD_CheckBox->Checked = Two_D;




	if(One_D && Two_D){
		One_D = false;
		Two_D = false;
		OneD_CheckBox->Checked = One_D;
		TwoD_CheckBox->Checked = Two_D;

		ScanTable.Scan_1D_Leveling = One_D;
		ScanTable.Scan_2D_Leveling = Two_D;

	}

	if(One_D){
		OneDButton->Appearance->BorderColor = TColor(0x00F0D27D);
		OneDButton->Font->Color = TColor(0x00F0D27D);
		TwoDButton->Appearance->BorderColor = TColor(0x008B6757);
		TwoDButton->Font->Color = clWhite;
	}

	if(Two_D){
		OneDButton->Appearance->BorderColor = TColor(0x008B6757);
		OneDButton->Font->Color = clWhite;
		TwoDButton->Appearance->BorderColor = TColor(0x00F0D27D);
		TwoDButton->Font->Color = TColor(0x00F0D27D);
	}

	switch (Resolution){
		case 64:{
			AdvComboBoxResolution->ItemIndex = 0;
			break;
		}
		case 128:{
			AdvComboBoxResolution->ItemIndex = 1;
			break;
		}
		case 256: {
			AdvComboBoxResolution->ItemIndex = 2;
			break;
		}
		case 512:{
			AdvComboBoxResolution->ItemIndex = 3;
			break;
		}
		case 1024:{
			AdvComboBoxResolution->ItemIndex = 4;
			break;
		}
		case 2048:{
			AdvComboBoxResolution->ItemIndex = 5;
			break;
		}
		default:{
			AdvComboBoxResolution->ItemIndex = 0;
			ScanTable.Scan_Resolution_Val = 64;
			break;
		}
	}


	mainForm->myDataBase->Execute(mainForm->myDataBase->myQuery->Update("SCAN_CONFIG"));

	AdvEditAngle->Text = IntToStr(Angle);
	AdvEditOverScan->Text = FloatToStr(OverScan);
	AdvEditRange->Text = FloatToStr(Range);
	AdvEditSpeed->Text = FloatToStr(Speed);
	AdvEditCenterX->Text = FloatToStr(CenterX);
	AdvEditCenterY->Text = FloatToStr(CenterY);
	KdAdvEdit->Text =  IntToStr(KdApp);
	KpAdvEdit->Text =  IntToStr(KpApp);
    BiasAdvEdit->Text = IntToStr(BiasApp);
	AdvEditOffset->Text = FloatToStr(FlyOffset);

    switch(mainForm->AppMode){
		case 1:{
			KiFeedbackAdvEdit->Text = IntToStr(KiFeedback_Contact);
			break;
		}
		case 2:{
			KiFeedbackAdvEdit->Text = IntToStr(KiFeedback_NonContact);
			break;
		}
		case 3:{
			KiFeedbackAdvEdit->Text = IntToStr(KiFeedback_NonContact);
			break;
		}
		case 4:{
			KiFeedbackAdvEdit->Text = IntToStr(KiFeedback_NonContact);
			break;
		}
		case 5:{
			KiFeedbackAdvEdit->Text = IntToStr(KiFeedback_Contact);
			break;
		}
		case 6:{
			KiFeedbackAdvEdit->Text = IntToStr(KiFeedback_NonContact);
			break;
		}
		case 7:{
			KiFeedbackAdvEdit->Text = IntToStr(KiFeedback_Contact);
			break;
		}
		default:{
			break;
		}


	}

	X_Calibration();
	Y_Calibration();
	Range_Calibration();
	FlyOffset = (int)(FlyOffset / (1000 * FlyOffset_index * pow10l(FlyOffset_Scale*3)));

	if(!AllScale){
		AdvEditCenterXLbl->Caption = "X-Center (%)";
		AdvEditCenterYLbl->Caption = "Y-Center (%)";
		AdvEditRangeLbl->Caption = "Range (%)";
		AdvEditOffsetLbl->Caption = "Offset";
		AdvEditRange->Text = FloatToStr(Range);
		AdvEditCenterX->Text = FloatToStr(CenterX);
		AdvEditCenterY->Text = FloatToStr(CenterY);
		AdvEditOffset->Text = FloatToStr(FlyOffset);
	}
	else{
		AdvEditCenterXLbl->Caption = "X-Center (�m)";
		AdvEditCenterYLbl->Caption = "Y-Center (�m)";
		AdvEditRangeLbl->Caption = "Range (�m)";
        AdvEditOffsetLbl->Caption = "Offset (nm)";
    }
	FlyOffset = -FlyOffset;
    AllEditWhite();


}
//---------------------------------------------------------------------------

void __fastcall TScanPanelForm::SetScan()
{
	mainForm->LogToFile("TScanPanelForm::SetScan");
    mainForm->myDataBase->Execute(mainForm->myDataBase->myQuery->Update("SCAN_CONFIG"));
//	AllEditWhite();
	ScanCommand.start = false;
	ScanCommand.set = true;
	ScanCommand.Changer = LastScanChanger;
	mainForm->myCommandCreatorThread->scan_command = true;
//	mainForm->myCommandCreatorThread->StartScanClick(false,true,LastScanChanger);
}
//---------------------------------------------------------------------------

void __fastcall TScanPanelForm::AdvEditOverScanKeyPress(TObject *Sender, System::WideChar &Key)

{
	if(Key == VK_RETURN){
        Key = 0;
		mainForm->LogToFile("TScanPanelForm::AdvEditOverScanKeyPress");
		AdvEditOverScan->Color = clWhite;
		OverScan = AdvEditOverScan->Text.ToDouble();
		LastScanChanger = 3;
		if(OverScan < 0) OverScan = 0;
		if(OverScan > 100) OverScan = 100;
		AdvEditOverScan->Text = FloatToStr(OverScan);
		ScanTable.Scan_OverScan_Val = OverScan;

		mainForm->Scaning = false;
		mainForm->myControlPanelForm->EnableScanPanel(0);
		TThread::Synchronize(mainForm->myCommandCreatorThread,SetScan);

		if(mainForm->AppMode == 7){
			mainForm->myLithoFrm->LithoConfigFrm->AdvEditOverScan->Text = AdvEditOverScan->Text;
			System::WideChar KKey = VK_RETURN;
			mainForm->myLithoFrm->LithoConfigFrm->AdvEditOverScanKeyPress(NULL, KKey);
		}
	}
}
//---------------------------------------------------------------------------

void __fastcall TScanPanelForm::AdvEditSpeedKeyPress(TObject *Sender, System::WideChar &Key)

{
	if(Key == VK_RETURN){
        Key = 0;
		mainForm->LogToFile("TScanPanelForm::AdvEditSpeedKeyPress");
		AdvEditSpeed->Color = clWhite;
//		LastScanChanger = 4;
		Speed = AdvEditSpeed->Text.ToDouble();
		if(Speed < 0.1) Speed = 0.1;
		if(Speed > 5) Speed = 5;
		AdvEditSpeed->Text = FloatToStr(Speed);
		ScanTable.Scan_Speed_Val = Speed;
		mainForm->Scaning = false;
		mainForm->myControlPanelForm->EnableScanPanel(0);
		TThread::Synchronize(mainForm->myCommandCreatorThread,SetScan);
	}
}
//---------------------------------------------------------------------------

void __fastcall TScanPanelForm::AdvEditAngleKeyPress(TObject *Sender, System::WideChar &Key)

{
	if(Key == VK_RETURN){
        Key = 0;
		mainForm->LogToFile("TScanPanelForm::AdvEditAngleKeyPress");
		AdvEditAngle->Color = clWhite;
		LastScanChanger = 1;
		Angle = AdvEditAngle->Text.ToInt();
		if(Angle < 0) Angle = 0;
		if(Angle > 90) Angle = 90;
		AdvEditAngle->Text = IntToStr(Angle);
		ScanTable.Scan_Angle_Val = Angle;
		mainForm->Scaning = false;
		mainForm->myControlPanelForm->EnableScanPanel(0);
		TThread::Synchronize(mainForm->myCommandCreatorThread,SetScan);
	}
}
//---------------------------------------------------------------------------

void __fastcall TScanPanelForm::AdvEditRangeKeyPress(TObject *Sender, System::WideChar &Key)

{
	if(Key == VK_RETURN){
        Key = 0;
		mainForm->LogToFile("TScanPanelForm::AdvEditRangeKeyPress");
		AdvEditRange->Color = clWhite;
		LastScanChanger = 2;
		Range = AdvEditRange->Text.ToDouble();
		if(AllScale){
			if(Range > Max_Range) Range = Max_Range;
			if(Range < 0) Range = 0;
			if(Range<10){
				int R = Range*1000;
				Range = (double)R/1000;
			}
			AdvEditRange->Text = FloatToStr(Range);

			Range_Calibration();

			ScanTable.Scan_Range_Val = Range;

		}
		else{
			if(Range > 100) Range = 100;
			if(Range < 0) Range = 0;
            if(Range<10){
				int R = Range*1000;
				Range = (double)R/1000;
			}
			AdvEditRange->Text = FloatToStr(Range);
			X_Range = Range;
			Y_Range = Range;

			ScanTable.Scan_Range_Val = Reverse_Range_Calibration();
		}

		AdvEditRange->Color = clWhite;


		mainForm->Scaning = false;
		mainForm->myControlPanelForm->EnableScanPanel(0);
		TThread::Synchronize(mainForm->myCommandCreatorThread,SetScan);
//
		if(mainForm->AppMode == 7){
			mainForm->myLithoFrm->LithoConfigFrm->AdvEditRange->Text = AdvEditRange->Text;
			System::WideChar KKey = VK_RETURN;
			mainForm->myLithoFrm->LithoConfigFrm->AdvEditRangeKeyPress(NULL, KKey);
		}
	}
}
//---------------------------------------------------------------------------

void __fastcall TScanPanelForm::AdvEditCenterXKeyPress(TObject *Sender, System::WideChar &Key)

{
	if(Key == VK_RETURN){
        Key = 0;
		mainForm->LogToFile("TScanPanelForm::AdvEditCenterXKeyPress");
		AdvEditCenterX->Color = clWhite;
		LastScanChanger = 5;
		CenterX = AdvEditCenterX->Text.ToDouble();
		if(AllScale){
			if(CenterX>Max_Range/2) CenterX = Max_Range/2;
			if(CenterX<-Max_Range/2) CenterX = -Max_Range/2;

			if(CenterX<10 && CenterX>-10){
				int X = CenterX*1000;
				CenterX = (double)X/1000;
			}

			AdvEditCenterX->Text = FloatToStr(CenterX);

			ScanTable.Scan_X_Center_Val = CenterX;

			X_Calibration();
		}
		else{
			if(CenterX>100) CenterX = 100;
			if(CenterX<0) CenterX = 0;

            if(CenterX<10 && CenterX>-10){
				int X = CenterX*1000;
				CenterX = (double)X/1000;
			}

			AdvEditCenterX->Text = FloatToStr(CenterX);
            AdvEditCenterX->Color = clWhite;

			ScanTable.Scan_X_Center_Val = Reverse_X_Calibration();

		}

		mainForm->Scaning = false;
		mainForm->myControlPanelForm->EnableScanPanel(0);
		TThread::Synchronize(mainForm->myCommandCreatorThread,SetScan);

		if(mainForm->AppMode == 7){
			mainForm->myLithoFrm->LithoConfigFrm->AdvEditCenterX->Text = AdvEditCenterX->Text;
			System::WideChar KKey = VK_RETURN;
			mainForm->myLithoFrm->LithoConfigFrm->AdvEditCenterXKeyPress(NULL, KKey);
		}
	}
}
//---------------------------------------------------------------------------

void __fastcall TScanPanelForm::AdvEditCenterYKeyPress(TObject *Sender, System::WideChar &Key)

{
	if(Key == VK_RETURN){
        Key = 0;
		mainForm->LogToFile("TScanPanelForm::AdvEditCenterYKeyPress");
		AdvEditCenterY->Color = clWhite;
		LastScanChanger = 6;
		CenterY = AdvEditCenterY->Text.ToDouble();
		if(AllScale){
			if(CenterY>Max_Range/2) CenterY = Max_Range/2;
			if(CenterY<-Max_Range/2) CenterY = -Max_Range/2;
			if(CenterY<10 && CenterY>-10){
				int Y = CenterY*1000;
				CenterY = (double)Y/1000;
			}

			AdvEditCenterY->Text = FloatToStr(CenterY);
			ScanTable.Scan_Y_Center_Val = CenterY;

			Y_Calibration();
		}
		else{
			if(CenterY>100) CenterY = 100;
			if(CenterY<0) CenterY = 0;
			if(CenterY<10 && CenterY>-10){
				int Y = CenterY*1000;
				CenterY = (double)Y/1000;
			}

			AdvEditCenterY->Text = FloatToStr(CenterY);
			ScanTable.Scan_Y_Center_Val = Reverse_Y_Calibration();
		}

		mainForm->Scaning = false;
		mainForm->myControlPanelForm->EnableScanPanel(0);
		TThread::Synchronize(mainForm->myCommandCreatorThread,SetScan);

		if(mainForm->AppMode == 7){
			mainForm->myLithoFrm->LithoConfigFrm->AdvEditCenterY->Text = AdvEditCenterY->Text;
			System::WideChar KKey = VK_RETURN;
			mainForm->myLithoFrm->LithoConfigFrm->AdvEditCenterYKeyPress(NULL, KKey);
		}

	}
}
//---------------------------------------------------------------------------

void __fastcall TScanPanelForm::AdvEditOffsetKeyPress(TObject *Sender, System::WideChar &Key)

{
	if(Key == VK_RETURN){
        Key = 0;
		mainForm->LogToFile("TScanPanelForm::AdvEditOffsetKeyPress");
		AdvEditOffset->Color = clWhite;
		LastScanChanger = 10;
		FlyOffset = AdvEditOffset->Text.ToDouble();
		FlyOffset = (int)FlyOffset;
		AdvEditOffset->Text = IntToStr((int)FlyOffset);
		AdvEditOffset->Color = clWhite;
//		if(FlyOffset > 8388607) FlyOffset = 8388607;
//		if(FlyOffset < -8388607) FlyOffset = -8388607;

		if(FlyOffset < 0){
			AdvEditOffset->Color = clYellow;
		}
		if(AllScale){
			ScanTable.Scan_Offset_val = FlyOffset;

			FlyOffset = -(int)(FlyOffset / (1000 * FlyOffset_index * pow10l(FlyOffset_Scale*3)));
		}
		else{
			double FlyOffset_um = floor(FlyOffset * FlyOffset_index * pow10l(FlyOffset_Scale*3) * 1000 + 0.5) ;
			ScanTable.Scan_Offset_val = FlyOffset_um;
			FlyOffset = - FlyOffset;
		}

		mainForm->Scaning = false;
		if(checkPermission()){
			mainForm->myControlPanelForm->EnableScanPanel(0);
			TThread::Synchronize(mainForm->myCommandCreatorThread,SetScan);
		}
	}
}
//---------------------------------------------------------------------------

void TScanPanelForm::HighLightChanger(int Changer, bool highlight)
{
	if(highlight){
		mainForm->LogToFile("TScanPanelForm::HighLightChanger , changer = " + IntToStr(Changer) + " , highlight = " + BoolToStr(highlight,true));
		switch(Changer){
			case 0:{
//				mainForm->LogToFile("highlight res");
				AdvComboBoxResolution->Color = clRed;
				AdvEditAngle->Color = clWhite;
				AdvEditOverScan->Color = clWhite;
				AdvEditRange->Color = clWhite;
				AdvEditSpeed->Color = clWhite;
				AdvEditCenterX->Color = clWhite;
				AdvEditCenterY->Color = clWhite;
				break;
			}
			case 1:{
//				mainForm->LogToFile("highlight res");
				AdvComboBoxResolution->Color = clWhite;
				AdvEditAngle->Color = clRed;
				AdvEditOverScan->Color = clWhite;
				AdvEditRange->Color = clWhite;
				AdvEditSpeed->Color = clWhite;
				AdvEditCenterX->Color = clWhite;
				AdvEditCenterY->Color = clWhite;
				break;
			}
			case 2:{
//				mainForm->LogToFile("highlight range");
				AdvComboBoxResolution->Color = clWhite;
				AdvEditAngle->Color = clWhite;
				AdvEditOverScan->Color = clWhite;
				AdvEditRange->Color = clRed;
				AdvEditSpeed->Color = clWhite;
				AdvEditCenterX->Color = clWhite;
				AdvEditCenterY->Color = clWhite;
				break;
			}
			case 3:{
//				mainForm->LogToFile("highlight over scan");
				AdvComboBoxResolution->Color = clWhite;
				AdvEditAngle->Color = clWhite;
				AdvEditOverScan->Color = clRed;
				AdvEditRange->Color = clWhite;
				AdvEditSpeed->Color = clWhite;
				AdvEditCenterX->Color = clWhite;
				AdvEditCenterY->Color = clWhite;
				break;
			}
			case 4:{
//				mainForm->LogToFile("highlight speed");
				AdvComboBoxResolution->Color = clWhite;
				AdvEditAngle->Color = clWhite;
				AdvEditOverScan->Color = clWhite;
				AdvEditRange->Color = clWhite;
				AdvEditSpeed->Color = clRed;
				AdvEditCenterX->Color = clWhite;
				AdvEditCenterY->Color = clWhite;
				break;
			}
			case 5:{
//				mainForm->LogToFile("highlight center y");
				AdvComboBoxResolution->Color = clWhite;
				AdvEditAngle->Color = clWhite;
				AdvEditOverScan->Color = clWhite;
				AdvEditRange->Color = clWhite;
				AdvEditSpeed->Color = clWhite;
				AdvEditCenterX->Color = clRed;
				AdvEditCenterY->Color = clWhite;
				break;
			}
			case 6:{
//				mainForm->LogToFile("highlight center y");
				AdvComboBoxResolution->Color = clWhite;
				AdvEditAngle->Color = clWhite;
				AdvEditOverScan->Color = clWhite;
				AdvEditRange->Color = clWhite;
				AdvEditSpeed->Color = clWhite;
				AdvEditCenterX->Color = clWhite;
				AdvEditCenterY->Color = clRed;
				break;
			}
			case 7:{
//				mainForm->LogToFile("highlight center y");
				AdvComboBoxResolution->Color = clWhite;
				AdvEditAngle->Color = clWhite;
				AdvEditOverScan->Color = clRed;
				AdvEditRange->Color = clRed;
				AdvEditSpeed->Color = clWhite;
				AdvEditCenterX->Color = clRed;
				AdvEditCenterY->Color = clRed;
				break;
			}

			default:{
				break;
			}
		}
	}
	else{
//		mainForm->LogToFile("highlight none");
//		AdvComboBoxResolution->Color = clWhite;
		if(AdvEditAngle->Color == clRed)
			AdvEditAngle->Color = clWhite;
		if(AdvEditOverScan->Color == clRed)
			AdvEditOverScan->Color = clWhite;
		if(AdvEditRange->Color == clRed)
			AdvEditRange->Color = clWhite;
		if(AdvEditSpeed->Color == clRed)
			AdvEditSpeed->Color = clWhite;
		if(AdvEditCenterX->Color == clRed)
			AdvEditCenterX->Color = clWhite;
		if(AdvEditCenterY->Color == clRed)
			AdvEditCenterY->Color = clWhite;
	}
}
//---------------------------------------------------------------------------

void __fastcall TScanPanelForm::OneD_CheckBoxClick(TObject *Sender)
{
	mainForm->LogToFile("TScanPanelForm::OneD_CheckBoxClick");
	if(OneD_CheckBox->Checked){
		TwoD_CheckBox->Checked = false;
		Two_D = false;
	}
	One_D = OneD_CheckBox->Checked;

	ScanTable.Scan_1D_Leveling = One_D;
	ScanTable.Scan_2D_Leveling = Two_D;
	mainForm->myDataBase->Execute(mainForm->myDataBase->myQuery->Update("SCAN_CONFIG"));

}
//---------------------------------------------------------------------------

void __fastcall TScanPanelForm::TwoD_CheckBoxClick(TObject *Sender)
{
	mainForm->LogToFile("TScanPanelForm::TwoD_CheckBoxClick");
	if(TwoD_CheckBox->Checked){
		OneD_CheckBox->Checked = false;
		One_D = false;
	}
	Two_D = TwoD_CheckBox->Checked;

	ScanTable.Scan_1D_Leveling = One_D;
	ScanTable.Scan_2D_Leveling = Two_D;
	mainForm->myDataBase->Execute(mainForm->myDataBase->myQuery->Update("SCAN_CONFIG"));
}
//---------------------------------------------------------------------------


void __fastcall TScanPanelForm::OneDButtonClick(TObject *Sender)
{
	mainForm->LogToFile("TScanPanelForm::OneDButtonClick");
	if(OneD_CheckBox->Checked){
		OneD_CheckBox->Checked = false;
		One_D = false;
		OneDButton->Appearance->BorderColor = TColor(0x008B6757);
		OneDButton->Font->Color = clWhite;
	}
	else{
		OneD_CheckBox->Checked = true;
		One_D = true;
		OneDButton->Appearance->BorderColor = TColor(0x00F0D27D);
		OneDButton->Font->Color = TColor(0x00F0D27D);
	}
	TwoD_CheckBox->Checked = false;
	Two_D = false;
	TwoDButton->Appearance->BorderColor = TColor(0x008B6757);
	TwoDButton->Font->Color = clWhite;

	ScanTable.Scan_1D_Leveling = One_D;
	ScanTable.Scan_2D_Leveling = Two_D;
	mainForm->myDataBase->Execute(mainForm->myDataBase->myQuery->Update("SCAN_CONFIG"));
}
//---------------------------------------------------------------------------

void __fastcall TScanPanelForm::TwoDButtonClick(TObject *Sender)
{
	mainForm->LogToFile("TScanPanelForm::TwoDButtonClick");
	if(TwoD_CheckBox->Checked){
		TwoD_CheckBox->Checked = false;
		Two_D = false;
		TwoDButton->Appearance->BorderColor = TColor(0x008B6757);
		TwoDButton->Font->Color = clWhite;
	}
	else{
		TwoD_CheckBox->Checked = true;
		Two_D = true;
		TwoDButton->Appearance->BorderColor = TColor(0x00F0D27D);
		TwoDButton->Font->Color = TColor(0x00F0D27D);
	}
	OneD_CheckBox->Checked = false;
	One_D = false;
	OneDButton->Appearance->BorderColor = TColor(0x008B6757);
	OneDButton->Font->Color = clWhite;

	ScanTable.Scan_1D_Leveling = One_D;
	ScanTable.Scan_2D_Leveling = Two_D;
	mainForm->myDataBase->Execute(mainForm->myDataBase->myQuery->Update("SCAN_CONFIG"));
}
//---------------------------------------------------------------------------

void __fastcall TScanPanelForm::FormShow(TObject *Sender)
{
	if(!start){
		start = true;

		int w_this = mainForm->myMainControlPanelForm->MainPanel->Width;
		int h_this = mainForm->myMainControlPanelForm->MainPanel->Height;

		PanelSubScan->Width = w_this - 40;
		PanelSubScan->Height = h_this - 40;
		PanelSubScan->Left = 20;
		PanelSubScan->Top = 20;

		int w = PanelSubScan->Width;
		int h = PanelSubScan->Height -  PanelLabelScan->Height;

		int l = 260;
		int p = 30;

		int left1 =  10;
		int left2 = w - 10 - 260;

//		KiAdvEdit->SetParentComponent(RoundApproachSetting);
		//Hide
		Panel1->Left = left1;
		Panel1->Top = PanelLabelScan->Height + 10;
		Panel1->Width = l;
		Panel1->Height = p;
		Panel1->BringToFront();

		Panel6->Left = Panel1->Left;
		Panel6->Top = Panel1->Top;
		Panel6->Width = l;
		Panel6->Height = p;
		Panel6->BringToFront();
//
//		KdAdvEdit->SetParentComponent(RoundApproachSetting);
		Panel3->Left = left1;
		Panel3->Top = Panel6->Top + 40;
		Panel3->Width = l;
		Panel3->Height = p;
		Panel3->BringToFront();
//
//		StpAdvEdit->SetParentComponent(RoundApproachSetting);
		Panel4->Left = left1;
		Panel4->Top = Panel3->Top + 40;
		Panel4->Width = l;
		Panel4->Height = p;
		Panel4->BringToFront();
//
//		KiFeebackAdvEdit->SetParentComponent(RoundApproachSetting);
		Panel2->Left = left1;
		Panel2->Top = Panel4->Top + 40;
		Panel2->Width = l;
		Panel2->Height = p;
		Panel2->BringToFront();
//
//		KpAdvEdit->SetParentComponent(RoundApproachSetting);
		Panel5->Left = left1;
		Panel5->Top = Panel2->Top + 40;
		Panel5->Width = l;
		Panel5->Height = p;
		Panel5->BringToFront();
//
		Panel7->Left = left1;
		Panel7->Top = Panel5->Top + 40;
		Panel7->Width = l;
		Panel7->Height = p;
		Panel7->BringToFront();

		Panel8->Left = left1;
		Panel8->Top = Panel7->Top + 40;
		Panel8->Width = l;
		Panel8->Height = p;
		Panel8->BringToFront();

		if( !(mainForm->AppMode == 3 || mainForm->AppMode == 4) ){
			Panel8->Hide();

			Panel9->Left = Panel8->Left;
			Panel9->Top = Panel8->Top;
			Panel9->Width = l;
			Panel9->Height = p;
			Panel9->BringToFront();
		}
		else{
			Panel9->Left = left1;
			Panel9->Top = Panel8->Top + 40;
			Panel9->Width = l;
			Panel9->Height = p;
			Panel9->BringToFront();
		}

		int mid = Panel4->Top + Panel4->Height/2;
//
		OneDButton->Width = l/2 - 10;
		OneDButton->Height = 60;
		OneDButton->Left = left2;
		OneDButton->Top = Panel1->Top;
		OneDButton->BringToFront();
//
		TwoDButton->Width = l/2 - 10;
		TwoDButton->Height = 60;
		TwoDButton->Left = left2 + OneDButton->Width + 10;
		TwoDButton->Top = OneDButton->Top;
		TwoDButton->BringToFront();

		Panel10->Left = left2;
		Panel10->Top = OneDButton->Top + 80;
		Panel10->Width = l;
		Panel10->Height = 5 * p;
		Panel10->BringToFront();


		if(AllScale)
            AdvEditOffset->MaxLength = 5;

		AllEditWhite();

	}
}
//---------------------------------------------------------------------------

void TScanPanelForm::AdvEditChange(double x_center, double y_center, double range)
{
	mainForm->LogToFile("TScanPanelForm::AdvEditChange");

	//x center
	if(AllScale){
		CenterX = x_center;
		if(CenterX>Max_Range/2) CenterX = Max_Range/2;
		if(CenterX<-Max_Range/2) CenterX = -Max_Range/2;

		if(CenterX<10 && CenterX>-10){
			int X = CenterX*1000;
			CenterX = (double)X/1000;
		}
		AdvEditCenterX->Text = FloatToStr(CenterX);
		AdvEditCenterX->Color = clWhite;
		ScanTable.Scan_X_Center_Val = CenterX;

		X_Calibration();

		// y center
		CenterY = y_center;
		if(CenterY>Max_Range/2) CenterY = Max_Range/2;
		if(CenterY<-Max_Range/2) CenterY = -Max_Range/2;

		if(CenterY<10 && CenterY>-10){
			int X = CenterY*1000;
			CenterY = (double)X/1000;
		}

		AdvEditCenterY->Text = FloatToStr(CenterY);
		AdvEditCenterY->Color = clWhite;
		ScanTable.Scan_Y_Center_Val = CenterY;

		Y_Calibration();

		//range
		Range = range;
		if(Range > Max_Range) Range = Max_Range;
		if(Range < 0) Range = 0;
		if(Range<10){
			int R = Range*1000;
			Range = (double)R/1000;
		}

		AdvEditRange->Text = FloatToStr(Range);
		AdvEditRange->Color = clWhite;
		ScanTable.Scan_Range_Val = Range;


		Range_Calibration();
        LastScanChanger = 7;
	}
	else{
        CenterX = x_center;
		if(CenterX>100) CenterX = 100;
		if(CenterX<0) CenterX = 0;

		if(CenterX<10 && CenterX>-10){
			int X = CenterX*1000;
			CenterX = (double)X/1000;
		}
		AdvEditCenterX->Text = FloatToStr(CenterX);
		AdvEditCenterX->Color = clWhite;
		ScanTable.Scan_X_Center_Val = Reverse_X_Calibration();

		// y center
		CenterY = y_center;
		if(CenterY>100) CenterY = 100;
		if(CenterY<0) CenterY = 0;

		if(CenterY<10 && CenterY>-10){
			int X = CenterY*1000;
			CenterY = (double)X/1000;
		}

		AdvEditCenterY->Text = FloatToStr(CenterY);
		AdvEditCenterY->Color = clWhite;
		ScanTable.Scan_Y_Center_Val = Reverse_Y_Calibration();

		//range
		Range = range;
		if(Range > 100) Range = 100;
		if(Range < 0) Range = 0;
		if(Range<10){
			int R = Range*1000;
			Range = (double)R/1000;
		}

		AdvEditRange->Text = FloatToStr(Range);
		AdvEditRange->Color = clWhite;
		ScanTable.Scan_Range_Val = Reverse_Range_Calibration();
		LastScanChanger = 7;

	}


	mainForm->Scaning = false;
	TThread::Synchronize(mainForm->myCommandCreatorThread,SetScan);
}
//---------------------------------------------------------------------------

void TScanPanelForm::AllEditWhite()
{
	mainForm->LogToFile("TScanPanelForm::AllEditWhite");
	AdvEditOverScan->Color = clWhite;
	AdvEditSpeed->Color = clWhite;
	AdvEditCenterX->Color = clWhite;
	AdvEditCenterY->Color = clWhite;
	AdvEditAngle->Color = clWhite;
	AdvEditRange->Color = clWhite;
	AdvComboBoxResolution->Color = clWhite;
	AdvEditOffset->Color = clWhite;
	AdvComboBoxSelect->Color = clWhite;
	KiFeedbackAdvEdit->Color = clWhite;
	KdAdvEdit->Color = clWhite;
	KpAdvEdit->Color = clWhite;
	BiasAdvEdit->Color = clWhite;
}
//---------------------------------------------------------------------------


void __fastcall TScanPanelForm::AdvEditOverScanChange(TObject *Sender)
{
	AdvEditOverScan->Color = clSilver;
}
//---------------------------------------------------------------------------

void __fastcall TScanPanelForm::AdvEditSpeedChange(TObject *Sender)
{
	AdvEditSpeed->Color = clSilver;
}
//---------------------------------------------------------------------------

void __fastcall TScanPanelForm::AdvEditCenterXChange(TObject *Sender)
{
	AdvEditCenterX->Color = clSilver;
}
//---------------------------------------------------------------------------

void __fastcall TScanPanelForm::AdvEditCenterYChange(TObject *Sender)
{
	AdvEditCenterY->Color = clSilver;
}
//---------------------------------------------------------------------------

void __fastcall TScanPanelForm::AdvEditAngleChange(TObject *Sender)
{
	AdvEditAngle->Color = clSilver;
}
//---------------------------------------------------------------------------

void __fastcall TScanPanelForm::AdvEditRangeChange(TObject *Sender)
{
	AdvEditRange->Color = clSilver;
}
//---------------------------------------------------------------------------

void __fastcall TScanPanelForm::AdvComboBoxResolutionChange(TObject *Sender)
{
	mainForm->LogToFile("TScanPanelForm::AdvComboBoxResolutionChange");
	Resolution = pow((double)2,6+AdvComboBoxResolution->ItemIndex);
//	LastScanChanger = 0;
	ScanTable.Scan_Resolution_Val = Resolution;
	mainForm->Scaning = false;
	mainForm->myControlPanelForm->EnableScanPanel(0);

	if(mainForm->AppMode == 7){
		//change resolution of litho
		mainForm->myLithoFrm->LithoConfigFrm->GetResolution();
	}

	TThread::Synchronize(mainForm->myCommandCreatorThread,SetScan);
}
//---------------------------------------------------------------------------

void __fastcall TScanPanelForm::AdvEditOffsetChange(TObject *Sender)
{
	AdvEditOffset->Color = clSilver;
}
//---------------------------------------------------------------------------

void __fastcall TScanPanelForm::AdvComboBoxSelectChange(TObject *Sender)
{
	mainForm->LogToFile("TScanPanelForm::AdvComboBoxSelectChange");
	int index = AdvComboBoxSelect->ItemIndex;
	if(index != -1){
		CenterX = X_Center[index];
		CenterY = Y_Center[index];
		Range = XY_Range[index];

		AdvEditChange(CenterX,CenterY,Range);

//		ScanTable.Scan_X_Center_Val = CenterX;
//		ScanTable.Scan_Y_Center_Val = CenterY;
//		ScanTable.Scan_Range_Val = Range;
		mainForm->myDataBase->Execute(mainForm->myDataBase->myQuery->Update("SCAN_CONFIG"));


	}

}
//---------------------------------------------------------------------------



void __fastcall TScanPanelForm::AdvComboBoxSelectKeyPress(TObject *Sender, System::WideChar &Key)

{

	if(Key == VK_BACK){
		mainForm->LogToFile("TScanPanelForm::AdvComboBoxSelectKeyPress");
	   AdvComboBoxSelect->Items->Clear();
	   AdvComboBoxSelect->Items->Add(FloatToStr(X_Center[0]) + " , " + FloatToStr(Y_Center[0]) + " : " + FloatToStr(XY_Range[0]));
	   for (int i = 1 ; i < 10 ; i++){
		  X_Center[i] = -1;
		  Y_Center[i] = -1;
		  XY_Range[i] = -1;
	   }
       HistoryIndex = 0;
	   HistoryCount = 1;

	}
}
//---------------------------------------------------------------------------

double TScanPanelForm::Regression(double First , double Second , double diff)
{
	mainForm->LogToFile("TScanPanelForm::Regression");
	double Final = First + (Second - First) * diff ;
	return Final;
}
//---------------------------------------------------------------------------

void TScanPanelForm::X_Calibration()
{
	mainForm->LogToFile("TScanPanelForm::X_Calibration");
	Center_X_um = CenterX;
	double CenterXX = abs(CenterX);
	double X1_Center = mainForm->X_Range[(int)CenterXX];
	double X2_Center = mainForm->X_Range[(int)CenterXX+1];

	if((int)CenterXX < CenterXX){
	   double diff = CenterXX - (int)CenterXX;
	   CenterXX = Regression(X1_Center,X2_Center,diff);
	}
	else{
		CenterXX = X1_Center;
	}

	if(CenterX>0) CenterX = 50 + CenterXX;
	else CenterX = 50 - CenterXX;


}
//---------------------------------------------------------------------------

void TScanPanelForm::Y_Calibration()
{
	mainForm->LogToFile("TScanPanelForm::Y_Calibration");
	Center_Y_um = CenterY;
	double CenterYY = abs(CenterY);
	double Y1_Center = mainForm->Y_Range[(int)CenterYY];
	double Y2_Center = mainForm->Y_Range[(int)CenterYY+1];


	if((int)CenterYY < CenterYY){
	   double diff = CenterYY - (int)CenterYY;
	   CenterYY = Regression(Y1_Center,Y2_Center,diff);
	}
	else{
		CenterYY = Y1_Center;
	}

	if(CenterY>0) CenterY = 50 + CenterYY;
	else CenterY = 50 - CenterYY;
}
//---------------------------------------------------------------------------

void TScanPanelForm::Range_Calibration()
{
	mainForm->LogToFile("TScanPanelForm::Range_Calibration");
	double X1_Range = mainForm->X_Range[(int)Range];
	double X2_Range = mainForm->X_Range[(int)Range+1];
	double Y1_Range = mainForm->Y_Range[(int)Range];
	double Y2_Range = mainForm->Y_Range[(int)Range+1];


	if((int)Range < Range){
	   double diff = Range - (int)Range;
	   X_Range = Regression(X1_Range,X2_Range,diff);
	   Y_Range = Regression(Y1_Range,Y2_Range,diff);
	}
	else{
		X_Range = X1_Range;
		Y_Range = Y1_Range;
	}
	if(!AllScale){
		if(X_Range < Y_Range){
			Y_Range = X_Range;
			Range = Y_Range;
		}
		else{
			X_Range = Y_Range;
			Range = X_Range;
		}
	}
}

//---------------------------------------------------------------------------
void __fastcall TScanPanelForm::KiFeedbackAdvEditKeyPress(TObject *Sender, System::WideChar &Key)
{
	if(Key == VK_RETURN){
		mainForm->LogToFile("TScanPanelForm::KiFeedbackAdvEditKeyPress");
        Key = 0;
		KiFeedbackAdvEdit->Color = clWhite;
		switch(mainForm->AppMode){
			case 1:{

				mainForm->myApproachPanelForm->KiFeedback_Contact = KiFeedbackAdvEdit->Text.ToInt();
				ApproachTable.Apr_KiFeedbak_Val_Contact = mainForm->myApproachPanelForm->KiFeedback_Contact;
				break;
			}
			case 2:{
				mainForm->myApproachPanelForm->KiFeedback_NonContact = KiFeedbackAdvEdit->Text.ToInt();
				ApproachTable.Apr_KiFeedbak_Val_NonContact = mainForm->myApproachPanelForm->KiFeedback_NonContact;
				break;
			}
			case 3:{
				mainForm->myApproachPanelForm->KiFeedback_NonContact = KiFeedbackAdvEdit->Text.ToInt();
				ApproachTable.Apr_KiFeedbak_Val_NonContact = mainForm->myApproachPanelForm->KiFeedback_NonContact;
				break;
			}
			case 4:{
				mainForm->myApproachPanelForm->KiFeedback_NonContact = KiFeedbackAdvEdit->Text.ToInt();
				ApproachTable.Apr_KiFeedbak_Val_NonContact = mainForm->myApproachPanelForm->KiFeedback_NonContact;
				break;
			}
			case 5:{
				mainForm->myApproachPanelForm->KiFeedback_Contact = KiFeedbackAdvEdit->Text.ToInt();
				ApproachTable.Apr_KiFeedbak_Val_Contact = mainForm->myApproachPanelForm->KiFeedback_Contact;
				break;
			}
			case 6:{
				mainForm->myApproachPanelForm->KiFeedback_NonContact = KiFeedbackAdvEdit->Text.ToInt();
				ApproachTable.Apr_KiFeedbak_Val_NonContact = mainForm->myApproachPanelForm->KiFeedback_NonContact;
				break;
			}
			case 7:{
				mainForm->myApproachPanelForm->KiFeedback_Contact = KiFeedbackAdvEdit->Text.ToInt();
				ApproachTable.Apr_KiFeedbak_Val_Contact = mainForm->myApproachPanelForm->KiFeedback_Contact;
				break;
			}
			default:{
				break;
			}
		}
		mainForm->myApproachPanelForm->KiFeedBack = KiFeedbackAdvEdit->Text.ToInt();

		if(mainForm->Approached){
//			mainForm->LogToFile("approched feed back enter");
			mainForm->myControlPanelForm->EnableApproachPanel(3);
			TThread::Synchronize(mainForm->myCommandCreatorThread,mainForm->myApproachPanelForm->SetApproach);
		}
		else{
//			mainForm->LogToFile("not approached feed back enter");
			mainForm->myApproachPanelForm->SettApproach();
		}
	}
}
//---------------------------------------------------------------------------

void __fastcall TScanPanelForm::KdAdvEditKeyPress(TObject *Sender, System::WideChar &Key)

{
	if(Key == VK_RETURN){
		mainForm->LogToFile("TScanPanelForm::KdAdvEditKeyPress");
        Key = 0;
		KdAdvEdit->Color = clWhite;
		mainForm->myApproachPanelForm->KdApp = KdAdvEdit->Text.ToInt();
		ApproachTable.Apr_Kd_Val = mainForm->myApproachPanelForm->KdApp;


		if(mainForm->Approached){
			mainForm->myControlPanelForm->EnableApproachPanel(3);
			TThread::Synchronize(mainForm->myCommandCreatorThread,mainForm->myApproachPanelForm->SetApproach);
		}
		else{
			mainForm->myApproachPanelForm->SettApproach();
		}
	}
}
//---------------------------------------------------------------------------

void __fastcall TScanPanelForm::KpAdvEditKeyPress(TObject *Sender, System::WideChar &Key)

{
	if(Key == VK_RETURN){
		mainForm->LogToFile("TScanPanelForm::KpAdvEditKeyPress");
        Key = 0;
		KpAdvEdit->Color = clWhite;
		mainForm->myApproachPanelForm->KpApp = KpAdvEdit->Text.ToInt();
		ApproachTable.Apr_Kp_Val = mainForm->myApproachPanelForm->KpApp;

		if(mainForm->Approached){
			mainForm->myControlPanelForm->EnableApproachPanel(3);
			TThread::Synchronize(mainForm->myCommandCreatorThread,mainForm->myApproachPanelForm->SetApproach);
		}
		else{
			mainForm->myApproachPanelForm->SettApproach();
		}
	}
}
//---------------------------------------------------------------------------

void __fastcall TScanPanelForm::KpAdvEditChange(TObject *Sender)
{
	KpAdvEdit->Color = clSilver;
}
//---------------------------------------------------------------------------

void __fastcall TScanPanelForm::KdAdvEditChange(TObject *Sender)
{
	KdAdvEdit->Color = clSilver;
}
//---------------------------------------------------------------------------

void __fastcall TScanPanelForm::KiFeedbackAdvEditChange(TObject *Sender)
{
	KiFeedbackAdvEdit->Color = clSilver;
}
//---------------------------------------------------------------------------

double TScanPanelForm::Reverse_X_Calibration()
{
	mainForm->LogToFile("TScanPanelForm::Reverse_X_Calibration");
	double min_CenterX = 100;
	int new_XCenter;

	for (int i = 0; i < mainForm->Max_Range; i++) {
		if (min_CenterX > abs(abs(50 - CenterX)-mainForm->X_Range[i])){
			min_CenterX = abs(abs(50 - CenterX)-mainForm->X_Range[i]);
			new_XCenter = i;
		}
	}

	if(abs(50 - CenterX)-mainForm->X_Range[new_XCenter] >= 0)
		min_CenterX = new_XCenter + (abs(50 - CenterX) - mainForm->X_Range[new_XCenter]) / (mainForm->X_Range[new_XCenter+1] - mainForm->X_Range[new_XCenter]);
	else
		min_CenterX = new_XCenter + (abs(50 - CenterX) - mainForm->X_Range[new_XCenter]) / (mainForm->X_Range[new_XCenter] - mainForm->X_Range[new_XCenter-1]);

	if(CenterX < 50) min_CenterX = -min_CenterX;

	int F_new;

	F_new = min_CenterX * 1000;
	min_CenterX = (double)F_new/1000;

	return min_CenterX;
}
//---------------------------------------------------------------------------

double TScanPanelForm::Reverse_Y_Calibration()
{
	mainForm->LogToFile("TScanPanelForm::Reverse_Y_Calibration");
	double min_CenterY = 100;
	int new_YCenter;


	for (int i = 0; i < mainForm->Max_Range; i++) {
		if (min_CenterY > abs(abs(50 - CenterY)-mainForm->Y_Range[i])){
			min_CenterY = abs(abs(50 - CenterY)-mainForm->Y_Range[i]);
			new_YCenter = i;
		}
	}

	if(abs(50 - CenterY)-mainForm->Y_Range[new_YCenter] >= 0)
		min_CenterY = new_YCenter + (abs(50 - CenterY) - mainForm->Y_Range[new_YCenter]) / (mainForm->Y_Range[new_YCenter+1] - mainForm->Y_Range[new_YCenter]);
	else
		min_CenterY = new_YCenter + (abs(50 - CenterY) - mainForm->Y_Range[new_YCenter]) / (mainForm->Y_Range[new_YCenter] - mainForm->Y_Range[new_YCenter-1]);


	if(CenterY < 50) min_CenterY = -min_CenterY;



	int F_new;

	F_new = min_CenterY * 1000;
	min_CenterY = (double)F_new/1000;

	return min_CenterY;
}
//---------------------------------------------------------------------------

double TScanPanelForm::Reverse_Range_Calibration()
{
	mainForm->LogToFile("TScanPanelForm::Reverse_Range_Calibration");
	float min_XRange = 100;
	float min_YRange = 100;

	int new_XRange;;
	int new_YRange;

	for (int i = 0; i < mainForm->Max_Range; i++) {
		if (min_XRange > abs(Range-mainForm->X_Range[i])){
			min_XRange = abs(Range-mainForm->X_Range[i]);
			new_XRange = i;
		}
		if (min_YRange > abs(Range-mainForm->Y_Range[i])){
			min_YRange = abs(Range-mainForm->Y_Range[i]);
			new_YRange = i;
		}
	}

	if(Range-mainForm->X_Range[new_XRange] >= 0)
		min_XRange = new_XRange + (Range - mainForm->X_Range[new_XRange]) / (mainForm->X_Range[new_XRange+1] - mainForm->X_Range[new_XRange]);
	else
		min_XRange = new_XRange + (Range - mainForm->X_Range[new_XRange]) / (mainForm->X_Range[new_XRange] - mainForm->X_Range[new_XRange-1]);


	if(Range-mainForm->Y_Range[new_YRange] >= 0)
		min_YRange = new_YRange + (Range - mainForm->Y_Range[new_YRange]) / (mainForm->Y_Range[new_YRange+1] - mainForm->Y_Range[new_YRange]);
	else
		min_YRange = new_YRange + (Range - mainForm->Y_Range[new_YRange]) / (mainForm->Y_Range[new_YRange] - mainForm->Y_Range[new_YRange-1]);

	double new_range;
	new_range = (min_XRange + min_YRange) / 2;

	int F_new;

    F_new = new_range * 1000;
	new_range = (double)F_new/1000;

	return new_range;

}
//---------------------------------------------------------------------------

bool TScanPanelForm::checkPermission()
{
	mainForm->LogToFile("TScanPanelForm::checkPermission");
    bool done = true;
	mainForm->LogToFile("CurrentZ = " + IntToStr(CurrentZ));
	mainForm->LogToFile("FlyOffset = " + FloatToStr(FlyOffset));
	mainForm->LogToFile("CurrentZ + FlyOffset = " + FloatToStr(CurrentZ + FlyOffset));


	if( (CurrentZ + FlyOffset) < -8388608 || (CurrentZ + FlyOffset) > 8388608 )
		done = false;

	int ErrorPercent = mainForm->myOscForm->ErrorPercent;
	int Err = MAX_MAX * ErrorPercent / 100;

	if((CurrentZ < -8388608 + Err) || (CurrentZ > 8388608 - Err) ){
		if(mainForm->Scaning){
			done = false;
			mainForm->myOscForm->FlyError = true;
        }
	}


	if(done){
		if(AdvEditOffset->Color == clRed)
			AdvEditOffset->Color = clWhite;
	}
	else{
		AdvEditOffset->Color = clRed;
	}

	return done;
}
//---------------------------------------------------------------------------

void __fastcall TScanPanelForm::BiasAdvEditChange(TObject *Sender)
{
    BiasAdvEdit->Color = clSilver;
}
//---------------------------------------------------------------------------

void __fastcall TScanPanelForm::BiasAdvEditKeyPress(TObject *Sender, System::WideChar &Key)

{
	if(Key == VK_RETURN){
		mainForm->LogToFile(" TScanPanelForm::BiasAdvEditKeyPress");
        Key = 0;
		BiasAdvEdit->Color = clWhite;
		BiasApp = BiasAdvEdit->Text.ToInt();
		ApproachTable.Apr_Bias_Val = BiasApp;
		mainForm->myApproachPanelForm->BiasAdvEdit->Text = IntToStr(BiasApp);
		mainForm->myApproachPanelForm->BiasAdvEdit->Color = clWhite;
		if(mainForm->Approached){
//			mainForm->LogToFile("bias back enter");
			mainForm->myControlPanelForm->EnableApproachPanel(3);
			TThread::Synchronize(mainForm->myCommandCreatorThread,mainForm->myApproachPanelForm->SetApproach);
		}
		else{
//			mainForm->LogToFile("not approached bias enter");
			mainForm->myApproachPanelForm->SettApproach();
		}
	}
}
//---------------------------------------------------------------------------

