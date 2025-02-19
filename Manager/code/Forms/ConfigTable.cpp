//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "ConfigTable.h"
#include "mainUnit.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "AdvGlassButton"
#pragma resource "*.dfm"
TConfTable *ConfTable;
//---------------------------------------------------------------------------

__fastcall TConfTable::TConfTable(TComponent* Owner)
	: TForm(Owner)
{
	first = false;
	Showing = false;
}
//---------------------------------------------------------------------------

void __fastcall TConfTable::FormShow(TObject *Sender)
{
	mainForm->LogToFile("TConfTable::FormShow");
	if(!first){
		InitValues();
		CreatObjects();
		first = true;
	}

	if(!Showing){
		for(int i = 0; i<mainForm->mySettingForm->myConfigForm->ColumnNumber; i++){

			switch(mainForm->mySettingForm->myConfigForm->TableNumber){
				case 0:{
					HeaderPanel->Visible = false;
					HeaderPanel2->Visible = false;
					if(i == 0){
						myRows[i]->TAdvGlowButton1->Caption = "Total Time (s)";
						myRows[i]->CurvyEdit1->Text = FloatToStr(LicTable.TotalTime);
					}
					else if(i == 1){
						myRows[i]->TAdvGlowButton1->Caption = "Worked Time (s)";
						myRows[i]->CurvyEdit1->Text = FloatToStr(LicTable.WorkedTime);
					}
					else{
						myRows[i]->TAdvGlowButton1->Caption = "Remained Time (s)";
						myRows[i]->CurvyEdit1->Text = FloatToStr(LicTable.RemainedTime);
					}
					myRows[i]->CurvyEdit1->Color = clWhite;
					myRows[i]->Show();
					break;
				}
				case 1:{
					HeaderPanel->Visible = false;
					HeaderPanel2->Visible = false;
					if(i == 0){
						myRows[i]->TAdvGlowButton1->Caption = "url";
						myRows[i]->CurvyEdit1->Text = InfoTable.url;
					}
					else{
						myRows[i]->TAdvGlowButton1->Caption = "tel";
						myRows[i]->CurvyEdit1->Text = InfoTable.tel;
					}
					myRows[i]->CurvyEdit1->Color = clWhite;
					myRows[i]->Show();
					break;
				}
				case 2:{
					HeaderPanel->Visible = false;
					HeaderPanel2->Visible = false;
					myRows[i]->TAdvGlowButton1->Caption = "all scale";
					UnicodeString tmp;
					if(OscChartTable.all_scale == true)
						tmp = "1";
					else
						tmp = "0";

					myRows[i]->CurvyEdit1->Text = tmp;
					myRows[i]->CurvyEdit1->Color = clWhite;
					myRows[i]->Show();
					break;
				}
				case 3:{
					HeaderPanel->Visible = false;
					HeaderPanel2->Visible = false;
					if(i == 0){
						myRows[i]->TAdvGlowButton1->Caption = "Coarse Stepper Speed Slow";
						myRows[i]->CurvyEdit1->Text = IntToStr(MoveTable.Coarse_StepperSpeed_Val_Slow);
					}
					else if(i == 1){
						myRows[i]->TAdvGlowButton1->Caption = "Coarse Stepper Speed Fast";
						myRows[i]->CurvyEdit1->Text = IntToStr(MoveTable.Coarse_StepperSpeed_Val_Fast);
					}
					else{
						myRows[i]->TAdvGlowButton1->Caption = "Coarse Stepper Step Micro";
						myRows[i]->CurvyEdit1->Text = IntToStr(MoveTable.Coarse_StepperStepMicro_Val);
					}
					myRows[i]->CurvyEdit1->Color = clWhite;
					myRows[i]->Show();
					break;
				}
				case 4:{
					HeaderPanel->Visible = false;
					HeaderPanel2->Visible = false;
					if(i == 0){
						myRows[i]->TAdvGlowButton1->Caption = "Stage Stepper Speed Slow";
						myRows[i]->CurvyEdit1->Text = IntToStr(StageTable.Stage_StepperSpeed_Val_Slow);
					}
					else if(i == 1){
						myRows[i]->TAdvGlowButton1->Caption = "Stage Stepper Speed Fast";
						myRows[i]->CurvyEdit1->Text = IntToStr(StageTable.Stage_StepperSpeed_Val_Fast);
					}
					else{
						myRows[i]->TAdvGlowButton1->Caption = "Stage Stepper Step Micro ";
						myRows[i]->CurvyEdit1->Text = IntToStr(StageTable.Stage_StepperStepMicro_Val);
					}
					myRows[i]->CurvyEdit1->Color = clWhite;
					myRows[i]->Show();
					break;
				}
				case 5:{
					HeaderPanel->Visible = false;
					HeaderPanel2->Visible = false;
					if(i == 0){
						myRows[i]->TAdvGlowButton1->Caption = "Retract One Step";
						myRows[i]->CurvyEdit1->Text = IntToStr(RetractTable.Ret_OneStep_Val);
					}
					else if(i == 1){
						myRows[i]->TAdvGlowButton1->Caption = "Retract Stepper Speed";
						myRows[i]->CurvyEdit1->Text = IntToStr(RetractTable.Ret_StepperSpeed_Val);
					}
					else{
						myRows[i]->TAdvGlowButton1->Caption = "Retract Stepper Step Micro";
						myRows[i]->CurvyEdit1->Text = IntToStr(RetractTable.Ret_StepperStepMicro_Val);
					}
					myRows[i]->CurvyEdit1->Color = clWhite;
					myRows[i]->Show();
					break;
				}
				case 6:{
					HeaderPanel->Visible = false;
					HeaderPanel2->Visible = false;
					if(i == 0){
						myRows[i]->TAdvGlowButton1->Caption = "Steper Speed Precise";
						myRows[i]->CurvyEdit1->Text = IntToStr(ApproachTable.Apr_SteperSpeed_Val_Precise);
					}
					else if(i == 1){
						myRows[i]->TAdvGlowButton1->Caption = "Stepper Step Micro Precise";
						myRows[i]->CurvyEdit1->Text = IntToStr(ApproachTable.Apr_SteperStepMicro_Val_Precise);
					}
					else if(i == 2){
						myRows[i]->TAdvGlowButton1->Caption = "Stepper Speed Fast";
						myRows[i]->CurvyEdit1->Text = IntToStr(ApproachTable.Apr_StepperSpeed_Val_Fast);
					}
					else if(i == 3){
						myRows[i]->TAdvGlowButton1->Caption = "Stepper Step Micro Fast";
						myRows[i]->CurvyEdit1->Text = IntToStr(ApproachTable.Apr_StepperStepMicro_Val_Fast);
					}
					else if(i == 4){
						myRows[i]->TAdvGlowButton1->Caption = "Stepper Step";
						myRows[i]->CurvyEdit1->Text = IntToStr(ApproachTable.Apr_StepperStep_Val);
					}
					else if(i == 5){
						myRows[i]->TAdvGlowButton1->Caption = "Bias Index";
						myRows[i]->CurvyEdit1->Text = IntToStr(ApproachTable.Apr_BiasIndex_Val);
					}
					else{
						myRows[i]->TAdvGlowButton1->Caption = "Bias Offset";
						myRows[i]->CurvyEdit1->Text = IntToStr(ApproachTable.Apr_BiasOffset_Val);
					}
					myRows[i]->CurvyEdit1->Color = clWhite;
					myRows[i]->Show();
					break;
				}
				case 7:{
					HeaderPanel->Visible = false;
					HeaderPanel2->Visible = false;
					if(i == 0){
						myRows[i]->TAdvGlowButton1->Caption = "Start Frequency";
						myRows[i]->CurvyEdit1->Text = IntToStr(FastApproachTable.Dnc_FrequencyFrom_Val);
					}
					else if(i == 1){
						myRows[i]->TAdvGlowButton1->Caption = "Final Frequency";
						myRows[i]->CurvyEdit1->Text = IntToStr(FastApproachTable.Dnc_FrequencyTo_Val);
					}
					else if(i == 2){
						myRows[i]->TAdvGlowButton1->Caption = "Threshold Contact";
						myRows[i]->CurvyEdit1->Text = IntToStr(FastApproachTable.Threshold_Contact);
					}
					else if(i == 3){
						myRows[i]->TAdvGlowButton1->Caption = "Threshold NonContact";
						myRows[i]->CurvyEdit1->Text = IntToStr(FastApproachTable.Threshold_NonContact);
					}
					else if(i == 4){
						myRows[i]->TAdvGlowButton1->Caption = "Min Amp";
						myRows[i]->CurvyEdit1->Text = IntToStr(FastApproachTable.Min_Amp);
					}
					else if(i == 5){
						myRows[i]->TAdvGlowButton1->Caption = "Max Amp";
						myRows[i]->CurvyEdit1->Text = IntToStr(FastApproachTable.Max_Amp);
					}
					else{
						myRows[i]->TAdvGlowButton1->Caption = "Drive Start";
						myRows[i]->CurvyEdit1->Text = IntToStr(FastApproachTable.Drive_Start);
					}
					myRows[i]->CurvyEdit1->Color = clWhite;
					myRows[i]->Show();
					break;
				}
				case 8:{
					HeaderPanel->Visible = false;
					HeaderPanel2->Visible = false;
					myRows[i]->TAdvGlowButton1->Caption = "OverScan";
					myRows[i]->CurvyEdit1->Text = FloatToStr(ScanTable.Scan_OverScan_Val);
					myRows[i]->CurvyEdit1->Color = clWhite;
					myRows[i]->Show();
					break;
				}
				case 9:{
					HeaderPanel->Visible = false;
					HeaderPanel2->Visible = false;
					if(i == 0){
						myRows[i]->TAdvGlowButton1->Caption = "Scanner Type";
						myRows[i]->CurvyEdit1->Text = IntToStr(HardwareTable.HardWare_Scanner_Type);
					}
					else if(i == 1){
						myRows[i]->TAdvGlowButton1->Caption = "Max Range (um)";
						myRows[i]->CurvyEdit1->Text = FloatToStr(HardwareTable.Max_Range);
					}
					else{
						myRows[i]->TAdvGlowButton1->Caption = "Log To File";
						UnicodeString tmp;
						if(HardwareTable.LogToFile == true)
							tmp = "1";
						else
							tmp = "0";

						myRows[i]->CurvyEdit1->Text = tmp;
					}
					myRows[i]->CurvyEdit1->Color = clWhite;
					myRows[i]->Show();
					break;
				}
				case 10:{
					HeaderPanel->Visible = false;
					HeaderPanel2->Visible = false;
					if(i == 0){
						myRows[i]->TAdvGlowButton1->Caption = "Min Frequency";
						myRows[i]->CurvyEdit1->Text = IntToStr(DncTable.Dnc_FrequencyFromMin_Val);
					}
					else if(i == 1){
						myRows[i]->TAdvGlowButton1->Caption = "Max Frequency";
						myRows[i]->CurvyEdit1->Text = IntToStr(DncTable.Dnc_FrequencyToMax_Val);
					}
					else if(i == 2){
						myRows[i]->TAdvGlowButton1->Caption = "Drive Index";
						myRows[i]->CurvyEdit1->Text = FloatToStr(DncTable.Dnc_DriveIndex_Val);
					}
					else{
						myRows[i]->TAdvGlowButton1->Caption = "Drive Offset";
						myRows[i]->CurvyEdit1->Text = FloatToStr(DncTable.Dnc_DriveOffset_Val);
					}
					myRows[i]->CurvyEdit1->Color = clWhite;
					myRows[i]->Show();
					break;
				}
				case 11:{
					HeaderPanel->Visible = true;
					HeaderPanel2->Visible = false;
					myOscConfigFrm[i]->TAdvGlowButton1->Caption = "Osc " + IntToStr(i);
					myOscConfigFrm[i]->CurvyEdit1->Text = OscTable[i].name;
					myOscConfigFrm[i]->CurvyEdit2->Text = FloatToStr(OscTable[i].index);
					myOscConfigFrm[i]->CurvyEdit3->Text = FloatToStr(OscTable[i].offset);
					myOscConfigFrm[i]->CurvyEdit4->Text = OscTable[i].unit;
					myOscConfigFrm[i]->CurvyEdit5->Text = IntToStr(OscTable[i].scale);
					myOscConfigFrm[i]->CurvyEdit1->Color = clWhite;
					myOscConfigFrm[i]->CurvyEdit2->Color = clWhite;
					myOscConfigFrm[i]->CurvyEdit3->Color = clWhite;
					myOscConfigFrm[i]->CurvyEdit4->Color = clWhite;
					myOscConfigFrm[i]->CurvyEdit5->Color = clWhite;
					myOscConfigFrm[i]->Show();
					break;
				}
				case 12:{
					HeaderPanel->Visible = false;
					HeaderPanel2->Visible = true;
					myColibration[i]->TAdvGlowButton1->Caption = IntToStr(ColibrationTable[i].Range_um) + " um";
					myColibration[i]->CurvyEdit1->Text = FloatToStr(ColibrationTable[i].X_Range);
					myColibration[i]->CurvyEdit2->Text = FloatToStr(ColibrationTable[i].Y_Range);
					myColibration[i]->CurvyEdit1->Color = clWhite;
					myColibration[i]->CurvyEdit2->Color = clWhite;
					myColibration[i]->Show();
				}
				default :{
				}


			}

		}
		Showing = true;
	}

}
//---------------------------------------------------------------------------

void TConfTable::InitValues()
{
	mainForm->LogToFile("TConfTable::InitValues");
	for(int i = 0; i<56; i++)
		myColibration[i] = NULL;
	for(int i = 0; i<27; i++)
		myOscConfigFrm[i] = NULL;
	for(int i = 0; i<7; i++)
		myRows[i] = NULL;

}
//---------------------------------------------------------------------------

void TConfTable::CreatObjects()
{
	mainForm->LogToFile("TConfTable::CreatObjects");
	if(mainForm->mySettingForm->myConfigForm->TableNumber == 11){
		int top = HeaderPanel->Top + HeaderPanel->Height;
		for (int i = 0; i < 27; i++){
			myOscConfigFrm[i] = new TOscConfigForm(this);
			myOscConfigFrm[i]->Parent = ScrollBox1;
			myOscConfigFrm[i]->SetParentComponent(ScrollBox1);
			if(!mainForm->mySettingForm->myConfigForm->EditBtn)
				myOscConfigFrm[i]->Enabled = false;
			myOscConfigFrm[i]->Left = 10;
			myOscConfigFrm[i]->Top = top;
			top = top + myOscConfigFrm[i]->Height;
		}
		HeaderPanel->Left = myOscConfigFrm[0]->Width - HeaderPanel->Width;


	}
	else if(mainForm->mySettingForm->myConfigForm->TableNumber == 12){
		HeaderPanel2->Top = HeaderPanel->Top;
		int top = HeaderPanel2->Top + HeaderPanel->Height;
		for (int i = 0; i < 56; i++){
			myColibration[i] = new TColibration(this);
			myColibration[i]->Parent = ScrollBox1;
			myColibration[i]->SetParentComponent(ScrollBox1);
			if(!mainForm->mySettingForm->myConfigForm->EditBtn)
				myColibration[i]->Enabled = false;
			myColibration[i]->Left = 10;
			myColibration[i]->Top = top;
			top = top + myColibration[i]->Height;
		}
		HeaderPanel2->Left = myColibration[0]->Width - HeaderPanel2->Width;

	}
	else{
		int top = 5;
		for(int i = 0; i<7; i++){
		   myRows[i] = new TRowFrm(this);
		   myRows[i]->Parent = ScrollBox1;
		   myRows[i]->SetParentComponent(ScrollBox1);
		   if(!mainForm->mySettingForm->myConfigForm->EditBtn)
				myRows[i]->Enabled = false;
		   myRows[i]->Left = 10;
		   myRows[i]->Top = top;
		   top = top + myRows[i]->Height;
		}
	}
}
//---------------------------------------------------------------------------

void __fastcall TConfTable::ScrollBox1MouseWheelDown(TObject *Sender, TShiftState Shift,
		  TPoint &MousePos, bool &Handled)
{
	ScrollBox1->VertScrollBar->Position += 10;

}
//---------------------------------------------------------------------------

void __fastcall TConfTable::ScrollBox1MouseWheelUp(TObject *Sender, TShiftState Shift,
		  TPoint &MousePos, bool &Handled)
{
	ScrollBox1->VertScrollBar->Position -= 10;
}
//---------------------------------------------------------------------------

