//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "DncFrm.h"
#include "mainUnit.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "AdvEdit"
#pragma link "AdvCombo"
#pragma link "AdvGlassButton"
#pragma link "VCLTee.TeeTools"
#pragma link "VCLTee.TeeComma"
#pragma link "AdvWiiProgressBar"
#pragma link "AdvMenus"
#pragma link "CalcEdit"
#pragma link "AdvGlowButton"
#pragma link "CurvyControls"
#pragma link "AdvPanel"
#pragma resource "*.dfm"
TDynamicCurveForm *DynamicCurveForm;
//---------------------------------------------------------------------------
__fastcall TDynamicCurveForm::TDynamicCurveForm(TComponent* Owner)
	: TForm(Owner)
{
	contact = false;
	myfirst = false;
	MaxPointofUse = 0;
}
//---------------------------------------------------------------------------
void __fastcall TDynamicCurveForm::FormCreate(TObject *Sender)
{
	this->Hide();


    mainForm->myDynamicCurvePanelForm->Caption = "";
	FromAdvEdit->Text = "";
	ToAdvEdit->Text = "";
	UseAdvEdit->Text = "";
	DriveAdvEdit->Text = "";
	SetPointAdvEdit->Text = "";
	TimeCntAdvComboBox->ItemIndex = 0;
	PointsAdvComboBox->ItemIndex = 0;
//	StatusLabel->Caption = "in Dnc process";
	in_dnc = false;
	AmpDraging = false;
	AmpPanel->Caption = "";
	FromToComboBox->Items->Clear();



	Config();



	Gain1 = false;
	Gain10 = false;
	Gain100 = false;


	counterBand = 1;
	band1From = -1;
	band1To = -1;

	band2From = -1;
	band2To = -1;

	band3From = -1;
	band3To = -1;

	band4From = -1;
	band4To = -1;

	AmpChart->ScrollMouseButton = mbRight;
	AmpChart->ClipPoints = false;
//	AmpChart->Title->Visible = false;
	AmpChart ->Legend->Visible = false;
	AmpChart->LeftAxis->Automatic = true;
	AmpChart->LeftAxis->Axis->Width = 1;
	AmpChart->BottomAxis->Axis->Width = 1;
	AmpChart->BottomAxis->RoundFirstLabel = false;
	AmpChart->BottomAxis->Automatic = false;
	AmpChart->View3D = false;
	AmpChart->Axes->FastCalc = true;
//	AmpDncSeries->AutoRepaint = false;
	AmpChart->Canvas->ReferenceCanvas->Pen->OwnerCriticalSection = NULL;
	AmpDncSeries->LinePen->OwnerCriticalSection = NULL;
	AmpChart->Hover->Visible = false;

	AmpPanel->Enabled = false;

//	AmpMaxMinChartTool->Text = "Max = 0";

	AmpChart->Title->Caption = "Dynamic Curve";



//	AmpAdvWiiProgressBar->Top = AmpPanel->Height/2 - AmpAdvWiiProgressBar->Height/2;
//	AmpAdvWiiProgressBar->Left = AmpPanel->Width/2 - AmpAdvWiiProgressBar->Width/2;
	AmpAdvWiiProgressBar->Top = AmpPanel->Height/2 - AmpAdvWiiProgressBar->Height/2;
	AmpAdvWiiProgressBar->Left = AmpPanel->Width/2 - AmpAdvWiiProgressBar->Width/2;

//	AmpMaxMinChartTool->Active = true;
//	AmpMaxMinChartTool->Active = false;
	GetData();
//	ValidateValues();
	EnableObjects(true);
}
//---------------------------------------------------------------------------

void TDynamicCurveForm::Config(){

    FromMin_Val = DncTable.Dnc_FrequencyFromMin_Val;
	From_Val = DncTable.Dnc_FrequencyFrom_Val;
	To_Val = DncTable.Dnc_FrequencyTo_Val;
	ToMax_Val = DncTable.Dnc_FrequencyToMax_Val;
	Use_Val = DncTable.Dnc_FrequencyUse_Val;
	Drive_Val = DncTable.Dnc_DriveVoltage_Val;
	PointsCount_Val = DncTable.Dnc_PointsCount_Val;
	SetPoint_Val = DncTable.Dnc_SetPointPercentage_Val;
	TimeCntIndex_Val = DncTable.Dnc_TimeCnt_Val;
	Rolloff = DncTable.Dnc_RollOff_Val;
	DriveIndex = DncTable.Dnc_DriveIndex_Val;
	DriveOffset = DncTable.Dnc_DriveOffset_Val;
	MaxPointofUse = DncTable.Dnc_Refrence_Val;
}
//---------------------------------------------------------------------------

void TDynamicCurveForm::EnableObjects(bool enabled)
{
	mainForm->LogToFile("TDynamicCurveForm::EnableObjects , enabled = " + BoolToStr(enabled,true));
	if(enabled){
		if(mainForm->myDynamicCurvePanelForm)
			mainForm->myDynamicCurvePanelForm->Enabled = true;
//		StatusLabel->Hide();
		AmpChart->AutoRepaint = true;
		AmpChart->Refresh();
	}
	else{
		if(mainForm->myDynamicCurvePanelForm)
			mainForm->myDynamicCurvePanelForm->Enabled = false;
		AmpChart->AutoRepaint = false;
//		StatusLabel->Show();
	}
}
//---------------------------------------------------------------------------

//void TDynamicCurveForm::ValidateValues()
//{
////	if(From_Val < FromMin_Val)
////		From_Val = FromMin_Val;
////	FromAdvEdit->Text = IntToStr(From_Val);
////
////	if(To_Val > ToMax_Val)
////		To_Val = ToMax_Val;
////	ToAdvEdit->Text = IntToStr(To_Val);
////
////	if(Use_Val > ToMax_Val)
////		Use_Val = ToMax_Val;
////	UseAdvEdit->Text = IntToStr(Use_Val);
////
////	switch(PointsCount_Val){
////		case 64:{
////			PointsAdvComboBox->ItemIndex = 0;
////			break;
////		}
////		case 128:{
////			PointsAdvComboBox->ItemIndex = 1;
////			break;
////		}
////		case 256:{
////			PointsAdvComboBox->ItemIndex = 2;
////			break;
////		}
////		case 512:{
////			PointsAdvComboBox->ItemIndex = 3;
////			break;
////		}
////		case 1024:{
////			PointsAdvComboBox->ItemIndex = 4;
////			break;
////		}
////		case 2048:{
////			PointsAdvComboBox->ItemIndex = 5;
////			break;
////		}
////		default:{
////			PointsCount_Val = 64;
////			PointsAdvComboBox->ItemIndex = 0;
////			break;
////		}
////	}
//
////	FreqStep =  ((double)((double)To_Val - (double)From_Val))/(double)PointsCount_Val;
////
////	switch(TimeCntIndex_Val){
////		case 0:{
////			TimeCntAdvComboBox->ItemIndex = 0;
////			TimeCnt_Val = 0.2;
////			break;
////		}
////		case 1:{
////			TimeCntAdvComboBox->ItemIndex = 1;
////			TimeCnt_Val = 0.5;
////			break;
////		}
////		case 2:{
////			TimeCntAdvComboBox->ItemIndex = 2;
////			TimeCnt_Val = 1;
////			break;
////		}
////		case 3:{
////			TimeCntAdvComboBox->ItemIndex = 3;
////			TimeCnt_Val = 2;
////			break;
////		}
////		case 4:{
////			TimeCntAdvComboBox->ItemIndex = 4;
////			TimeCnt_Val = 5;
////			break;
////		}
////		case 5: {
////			TimeCntAdvComboBox->ItemIndex = 5;
////			TimeCnt_Val = 10;
////			break;
////		}
////		case 6:{
////			TimeCntAdvComboBox->ItemIndex = 6;
////			TimeCnt_Val = 20;
////			break;
////		}
////		case 7:{
////			TimeCntAdvComboBox->ItemIndex = 7;
////			TimeCnt_Val = 50;
////			break;
////		}
////		case 8:{
////			TimeCntAdvComboBox->ItemIndex = 8;
////			TimeCnt_Val = 100;
////			break;
////		}
////		case 9:{
////			TimeCntAdvComboBox->ItemIndex = 9;
////			TimeCnt_Val = 200;
////			break;
////		}
////		case 10:{
////			TimeCntAdvComboBox->ItemIndex = 10;
////			TimeCnt_Val = 500;
////			break;
////		}
////		case 11:{
////			TimeCntAdvComboBox->ItemIndex = 11;
////			TimeCnt_Val = 1000;
////			break;
////		}
////		case 12:{
////			TimeCntAdvComboBox->ItemIndex = 12;
////			TimeCnt_Val = 2000;
////			break;
////		}
////		case 13:{
////			TimeCntAdvComboBox->ItemIndex = 13;
////			TimeCnt_Val = 5000;
////			break;
////		}
////		default:{
////			TimeCntAdvComboBox->ItemIndex = 0;
////			TimeCnt_Val = 0.2;
////			TimeCntIndex_Val = 0;
////			break;
////		}
////	}
//////
////	if(SetPoint_Val < 0)
////		SetPoint_Val = 0;
////	if(SetPoint_Val > 100)
////		SetPoint_Val = 100;
////	SetPointAdvEdit->Text = IntToStr(SetPoint_Val);
//
////	switch(PointsAdvComboBox->ItemIndex){
////		case 0:{
////		 //64
////			PointsCount = 64;
////			break;
////		}
////		case 1:{
////		//128
////			PointsCount = 128;
////			break;
////		}
////		case 2:{
////		//256
////			PointsCount = 256;
////			break;
////		}
////		case 3:{
////		 //512
////			PointsCount = 512;
////			break;
////		}
////		case 4:{
////		//1024
////			PointsCount = 1024;
////			break;
////		}
////		case 5:{
////		//2048
////			PointsCount = 2048;
////			break;
////		}
////		default:{
////			PointsCount = 64;
////			break;
////		}
////	}
//
////	if(Gain1)
////		Gain_Val = 1;
////	else if(Gain10)
////		Gain_Val = 10;
////	else if(Gain100)
////		Gain_Val = 100;
////	else
////		Gain_Val = 1;
//
////	DriveAdvEdit->Text = IntToStr(Drive_Val);
//
////    TIniFile *iniFile = new TIniFile(MainPath + "/config.ini");
////	iniFile->WriteFloat("DNC_CONFIG", "Dnc_DriveVoltage_Val",Drive_Val);
////	DriveIndex = iniFile->ReadFloat("DNC_CONFIG", "Dnc_DriveIndex_Val", 1);
////	DriveOffset = iniFile->ReadFloat("DNC_CONFIG", "Dnc_DriveOffset_Val", 0);
////	delete iniFile;
//
////	mainForm->LogToFile("Dnc_DriveIndex_Val : " + FloatToStr(DriveIndex));
////	mainForm->LogToFile("Dnc_DriveOffset_Val : " + FloatToStr(DriveOffset));
//
////	MainDriveVal = ((double)Drive_Val * DriveIndex) + DriveOffset;
//}
//---------------------------------------------------------------------------

void TDynamicCurveForm::GetData()
{
	mainForm->LogToFile("TDynamicCurveForm::GetData");
	switch(PointsCount_Val){
		case 64:{
			PointsAdvComboBox->ItemIndex = 0;
			break;
		}
		case 128:{
			PointsAdvComboBox->ItemIndex = 1;
			break;
		}
		case 256:{
			PointsAdvComboBox->ItemIndex = 2;
			break;
		}
		case 512:{
			PointsAdvComboBox->ItemIndex = 3;
			break;
		}
		case 1024:{
			PointsAdvComboBox->ItemIndex = 4;
			break;
		}
		case 2048:{
			PointsAdvComboBox->ItemIndex = 5;
			break;
		}
		default:{
			PointsCount_Val = 64;
			PointsAdvComboBox->ItemIndex = 0;
			break;
		}
	}
	FreqStep =  ((double)((double)To_Val - (double)From_Val))/(double)PointsCount_Val;

	if(Gain1)
		Gain_Val = 1;
	else if(Gain10)
		Gain_Val = 10;
	else if(Gain100)
		Gain_Val = 100;
	else
		Gain_Val = 1;

}
//---------------------------------------------------------------------------

void __fastcall TDynamicCurveForm::SetDncAdvGlassButtonClick(TObject *Sender)
{
	mainForm->LogToFile("TDynamicCurveForm::SetDncAdvGlassButtonClick");
//	mainForm->LogToFile("set dnc button");
	GetData();
//	ValidateValues();
	start = false;
	TThread::Synchronize(mainForm->myCommandCreatorThread,StartDnc);
}
//---------------------------------------------------------------------------

void __fastcall TDynamicCurveForm::RunAdvGlassButtonClick(TObject *Sender)
{
	mainForm->LogToFile("TDynamicCurveForm::RunAdvGlassButtonClick");
	if(hid == mainForm->myUniKey->FindDongle()){
	//    AllEditWhite();
		if(!mainForm->Approached){
			mainForm->myMainControlPanelForm->StatusAdvEdit->Caption = "Ready to Approach";
			mainForm->myMainControlPanelForm->StatusAdvEdit->Font->Color = clHighlight;
		}
		if(contact){
			TThread::Synchronize(mainForm->myCommandCreatorThread,StartDnc);
		}
		else{
			ColorBandChartTool->Active = false;
			AmpChartToolX->Active = false;
			AmpChartToolY->Active = false;

			int diff = To_Val - From_Val;
	//		mainForm->LogToFile("From_Val = " + IntToStr(From_Val) + " To_Val = " + IntToStr(To_Val) + " diff = " + IntToStr(diff));
	//		mainForm->LogToFile("PointsCount_Val = " + IntToStr(PointsCount_Val));
	//		diff = abs(diff);

			if(diff >= PointsCount_Val){
				if(FromAdvEdit->Color == clRed)
					FromAdvEdit->Color = clWhite;
				if(ToAdvEdit->Color == clRed)
					ToAdvEdit->Color = clWhite;
				if(PointsAdvComboBox->Color == clRed)
					PointsAdvComboBox->Color = clWhite;
				PointsAdvComboBox->Refresh();

				AmpPanel->Enabled = true;
				GetData();
	//			ValidateValues();
				SaveData();

                DncTable.Dnc_FrequencyFrom_Val = From_Val;
				DncTable.Dnc_FrequencyTo_Val = To_Val;
				mainForm->myDataBase->Execute(mainForm->myDataBase->myQuery->Update("DNC_CONFIG"));


				UpDownBorder(RunAdvGlassButton->Appearance,false);

				EnableObjects(false);
				start = true;
				TThread::Synchronize(mainForm->myCommandCreatorThread,StartDnc);
			}
			else{
				FromAdvEdit->Color = clRed;

				ToAdvEdit->Color = clRed;

				PointsAdvComboBox->Color = clRed;
			}
        }
	}
}
//---------------------------------------------------------------------------

void TDynamicCurveForm::UpDownBorder(TGlowButtonAppearance* appearance, bool UpDown)
{

	if(UpDown){
		appearance->BorderColor = TColor(0x00614438);
		appearance->BorderColorHot = TColor(0x00614438);
		appearance->BorderColorChecked = TColor(0x00614438);
		appearance->BorderColorCheckedHot = TColor(0x00614438);
		appearance->BorderColorDisabled = TColor(0x006144380);
		appearance->BorderColorFocused = TColor(0x00614438);
		appearance->BorderColorDown = TColor(0x00614438);
	}
	else{
		appearance->BorderColor = TColor(0x00F0D27D);
		appearance->BorderColorHot = TColor(0x00F0D27D);
		appearance->BorderColorChecked = TColor(0x00F0D27D);
		appearance->BorderColorCheckedHot = TColor(0x00F0D27D);
		appearance->BorderColorDisabled = TColor(0x00F0D27D);
		appearance->BorderColorFocused = TColor(0x00F0D27D);
		appearance->BorderColorDown = TColor(0x00F0D27D);
	}
}
//---------------------------------------------------------------------------

void TDynamicCurveForm::SaveData()
{
	mainForm->LogToFile("TDynamicCurveForm::SaveData");
//	mainForm->LogToFile("counterBand = " + IntToStr(counterBand));
	if(counterBand < 5){
		if(counterBand == 1){
			band1From = FromMin_Val;
			band1To = ToMax_Val;

			if( ((band1To != band3To) && (band1From != band3From)) &&  ((band1To != band2To) && (band1From != band2From)) && ((band1To != band4To) && (band1From != band4From)) ){
//				mainForm->LogToFile(IntToStr(band1From) + " _ " + IntToStr(band1To));
				FromToComboBox->Items->Add(IntToStr(band1From) + " _ " + IntToStr(band1To));
				FromToComboBox->ItemIndex = 0;
				counterBand++;
			}
		}
		else if(counterBand == 2){
			band2From = From_Val;
			band2To = To_Val;

			if( ((band2To != band1To) && (band2From != band1From)) &&  ((band2To != band3To) && (band2From != band3From)) && ((band2To != band4To) && (band2From != band4From)) ){
//				mainForm->LogToFile(IntToStr(band2From) + " _ " + IntToStr(band2To));
				FromToComboBox->Items->Add(IntToStr(band2From) + " _ " + IntToStr(band2To));
				FromToComboBox->ItemIndex = 1;
				counterBand++;
			}
		}
		else if(counterBand == 3){
			band3From = From_Val;
			band3To = To_Val;
			if( ((band3To != band1To) && (band3From != band1From)) &&  ((band3To != band2To) && (band3From != band2From)) && ((band3To != band4To) && (band3From != band4From)) ){
//				mainForm->LogToFile(IntToStr(band3From) + " _ " + IntToStr(band3To));
				FromToComboBox->Items->Add(IntToStr(band3From) + " _ " + IntToStr(band3To));
				FromToComboBox->ItemIndex = 2;
				counterBand++;
			}
		}
		else if(counterBand == 4){
			band4From = From_Val;
			band4To = To_Val;
			if( ((band4To != band1To) && (band4From != band1From)) &&  ((band4To != band2To) && (band4From != band2From)) && ((band4To != band3To) && (band4From != band3From)) ){
//				mainForm->LogToFile(IntToStr(band4From) + " _ " + IntToStr(band4To));
				FromToComboBox->Items->Add(IntToStr(band4From) + " _ " + IntToStr(band4To));
				FromToComboBox->ItemIndex = 3;
				counterBand++;
			}
		}
	}
	else{
		int index = -1;

		if(counterBand % 4 == 0){
			band1From = FromMin_Val;
			band1To = ToMax_Val;
			if( ((band1To != band3To) && (band1From != band3From)) &&  ((band1To != band2To) && (band1From != band2From)) && ((band1To != band4To) && (band1From != band4From)) ){
				index = 0;
				counterBand++;
			}
		}
		else if(counterBand % 4 == 1){
			if( ((To_Val != band1To) && (From_Val != band1From)) && ((To_Val != band2To) && (From_Val != band2From)) &&  ((To_Val != band3To) && (From_Val != band3From)) && ((To_Val != band4To) && (From_Val != band4From)) ){
				band2From = From_Val;
				band2To = To_Val;
				index = 1;
				counterBand++;
			}
		}
		else if(counterBand % 4 == 2){
			if( ((To_Val != band1To) && (From_Val != band1From)) && ((To_Val != band2To) && (From_Val != band2From)) &&  ((To_Val != band3To) && (From_Val != band3From)) && ((To_Val != band4To) && (From_Val != band4From)) ){
                band3From = From_Val;
				band3To = To_Val;
				index = 2;
				counterBand++;
			}
		}
		else if(counterBand % 4 == 3){
			if( ((To_Val != band1To) && (From_Val != band1From)) && ((To_Val != band2To) && (From_Val != band2From)) &&  ((To_Val != band3To) && (From_Val != band3From)) && ((To_Val != band4To) && (From_Val != band4From)) ){
                band4From = From_Val;
				band4To = To_Val;
				index = 3;
				counterBand = counterBand + 2;
			}
		}

		FromToComboBox->Items->Clear();
		FromToComboBox->Items->Add(IntToStr(band1From) + " _ " + IntToStr(band1To));
		FromToComboBox->Items->Add(IntToStr(band2From) + " _ " + IntToStr(band2To));
		FromToComboBox->Items->Add(IntToStr(band3From) + " _ " + IntToStr(band3To));
		FromToComboBox->Items->Add(IntToStr(band4From) + " _ " + IntToStr(band4To));
		FromToComboBox->ItemIndex = index;
	}
}
//---------------------------------------------------------------------------

void __fastcall TDynamicCurveForm::StartDnc()
{
//    AllEditWhite();
	mainForm->LogToFile("TDynamicCurveForm::StartDnc");
	mainForm->myCommandCreatorThread->StartDncClick(start);
}
//---------------------------------------------------------------------------

void __fastcall TDynamicCurveForm::AmpChartMouseDown(TObject *Sender, TMouseButton Button,
		  TShiftState Shift, int X, int Y)
{
	if(Button == mbRight){
		mainForm->LogToFile("TDynamicCurveForm::AmpChartMouseDown");
		AmpChartToolX->Active = false;
		AmpChartToolY->Active = false;

//		FromToComboBox->Visible = true;
		ColorBandChartTool->Active = true;
		ColorBandChartTool->StartValue = AmpChart->BottomAxis->CalcPosPoint(X);
		ColorBandChartTool->EndValue = ColorBandChartTool->StartValue;

//		if( abs( (int)(ColorBandChartTool->StartValue) - (int)ColorBandChartTool->EndValue) ) >= 64){
//			FromAdvEdit->Text = IntToStr( (int)(ColorBandChartTool->StartValue) );
//			ToAdvEdit->Text = IntToStr( (int)(ColorBandChartTool->EndValue) );
//		}



//		mainForm->LogToFile("start start = " + FloatToStr(ColorBandChartTool->StartValue));
//		mainForm->LogToFile("start end = " + FloatToStr(ColorBandChartTool->EndValue));
//		ColorBandChartTool->EndValue = AmpChart->BottomAxis->CalcPosPoint(X);


		AmpDraging = true;
		AmpXStart = X;
		AmpYStart = Y;

		TopLeftX = X;
		TopLeftY = Y;
	}
}
//---------------------------------------------------------------------------

void __fastcall TDynamicCurveForm::AmpChartMouseUp(TObject *Sender, TMouseButton Button,
		  TShiftState Shift, int X, int Y)
{
	if(Button == mbRight && AmpDraging){
		mainForm->LogToFile("TDynamicCurveForm::AmpChartMouseUp");
		AmpDraging = false;
		AmpXStop = X;
		AmpYStop = Y;

		BotRighX = X;
		BotRightY = Y;

		rect.Location.X = TopLeftX;
		rect.Location.Y = TopLeftY;

		rect.init(0,0,BotRighX-TopLeftX,BotRightY - TopLeftY);
	}
}
//---------------------------------------------------------------------------

void __fastcall TDynamicCurveForm::AmpChartClickSeries(TCustomChart *Sender, TChartSeries *Series,
		  int ValueIndex, TMouseButton Button, TShiftState Shift, int X,
		  int Y)
{
	if(Button == mbLeft){
		mainForm->LogToFile("TDynamicCurveForm::AmpChartClickSeries");
		AmpChartToolX->Active = true;
		AmpChartToolY->Active = true;

		double xvalue;
		double yvalue;
		double intecept;
		MoveColorLineAmp(X,Y,&xvalue,&yvalue,&intecept);

		int use = floor(xvalue+0.5);
		int percent = 100;
		MaxPointofUse = AmpDncSeries->YValues->operator [](ValueIndex);

		MaxAdvEdit->Text = FormatFloat("#0.0##",MaxPointofUse);
		SetPAdvEdit->Text = FormatFloat("#0.0##",MaxPointofUse);

		SetPointAdvEdit->Text = FloatToStr(percent);
		SetPoint_Val = SetPointAdvEdit->Text.ToDouble();
		SetPointAdvEdit->Color = clWhite;

		UseAdvEdit->Text = FloatToStr(use);
		Use_Val = UseAdvEdit->Text.ToDouble();
		UseAdvEdit->Color = clWhite;
		DncTable.Dnc_FrequencyUse_Val = use;

//		AmpMaxMinChartTool->Text = "Max = " + FloatToStr(floor((MaxPointofUse*1000 + 0.5))/1000);


		GetData();
//		ValidateValues();
//		mainForm->LogToFile("send drive");

		DncTable.Dnc_DriveVoltage_Val = Drive_Val;
		mainForm->myDataBase->Execute(mainForm->myDataBase->myQuery->Update("DNC_CONFIG"));

		DriveIndex = DncTable.Dnc_DriveIndex_Val;     // mv to number
		DriveOffset = DncTable.Dnc_DriveOffset_Val;


//        mainForm->LogToFile("Dnc_DriveIndex_Val : " + FloatToStr(DriveIndex));
//		mainForm->LogToFile("Dnc_DriveOffset_Val : " + FloatToStr(DriveOffset));

		MainDriveVal = ((double)Drive_Val * DriveIndex) + DriveOffset;
		start = false;
		TThread::Synchronize(mainForm->myCommandCreatorThread,StartDnc);

		mainForm->myApproachPanelForm->SettApproach();

	}

}
//---------------------------------------------------------------------------

void __fastcall TDynamicCurveForm::AmpChartClickBackground(TCustomChart *Sender,
		  TMouseButton Button, TShiftState Shift, int X, int Y)
{
	if(Button == mbLeft){
		mainForm->LogToFile("TDynamicCurveForm::AmpChartClickBackground");
		AmpChartToolX->Active = true;
		AmpChartToolY->Active = true;
		double xvalue;
		double yvalue;
		double intecept;
		MoveColorLineAmp(X,Y,&xvalue,&yvalue,&intecept);


		double x,y,ym;
		x = xvalue;
		y = yvalue;
		ym = intecept;

		MaxPointofUse = intecept;

//		mainForm->LogToFile("xvalue = " + FloatToStr(xvalue));
//		mainForm->LogToFile("yvalue = " + FloatToStr(yvalue));
//		mainForm->LogToFile("intecept = " + FloatToStr(intecept));


		int percent;
		if (y > ym)	y = ym;

		MaxAdvEdit->Text = FormatFloat("#0.0##",ym);
		SetPAdvEdit->Text = FormatFloat("#0.0##",y);

//		double min = 0;
		double difChart = ym - 0;
		double difData =  ym - y;
//		mainForm->LogToFile("difChart  = " + FloatToStr(floor(difChart+0.5)));
//		mainForm->LogToFile("difData  = " + FloatToStr(floor(difData+0.5)));
		if(difChart == 0 || difData == 0){
			percent = 100;
		}
		else{
			percent = floor( ( ( (difChart - difData) / difChart ) * 100 ) + 0.5 );
		}

		if(percent < 0) percent = 0;

		int use = floor(x+0.5);
		if(use < AmpChart->BottomAxis->Minimum) use = floor(AmpChart->BottomAxis->Minimum + 0.5);
		if(use > AmpChart->BottomAxis->Maximum) use = floor(AmpChart->BottomAxis->Maximum + 0.5);

//		mainForm->LogToFile("use  = " + IntToStr(use));
//		mainForm->LogToFile("set  = " + FloatToStr(floor(y+0.5)));
//		mainForm->LogToFile("main  = " + FloatToStr(floor(ym+0.5)));
//		mainForm->LogToFile("set point  = " + IntToStr(percent));
		SetPointAdvEdit->Text = IntToStr(percent);
		SetPoint_Val = SetPointAdvEdit->Text.ToDouble();
		SetPointAdvEdit->Color = clWhite;

		UseAdvEdit->Text = IntToStr(use);
		Use_Val = UseAdvEdit->Text.ToDouble();
		UseAdvEdit->Color = clWhite;
        DncTable.Dnc_FrequencyUse_Val = use;
//		AmpMaxMinChartTool->Text = "Max = " + FloatToStr(floor((MaxPointofUse*1000 + 0.5))/1000);

		GetData();
//		ValidateValues();
//		mainForm->LogToFile("send drive");

		DncTable.Dnc_DriveVoltage_Val = Drive_Val;
		DncTable.Dnc_Refrence_Val = MaxPointofUse;
		mainForm->myDataBase->Execute(mainForm->myDataBase->myQuery->Update("DNC_CONFIG"));

		DriveIndex = DncTable.Dnc_DriveIndex_Val;
		DriveOffset = DncTable.Dnc_DriveOffset_Val;


//		mainForm->LogToFile("Dnc_DriveIndex_Val : " + FloatToStr(DriveIndex));
//		mainForm->LogToFile("Dnc_DriveOffset_Val : " + FloatToStr(DriveOffset));

		MainDriveVal = ((double)Drive_Val * DriveIndex) + DriveOffset;
		start = false;
		TThread::Synchronize(mainForm->myCommandCreatorThread,StartDnc);

		mainForm->myApproachPanelForm->SettApproach();
	}
}
//---------------------------------------------------------------------------


void TDynamicCurveForm::MoveColorLineAmp(int x, int y,double* ValueX,double* ValueY,double *ValueIntercept)
{
	mainForm->LogToFile("TDynamicCurveForm::MoveColorLineAmp");
	if(AmpDncSeries->Count() > 1){
		*ValueX = AmpChart->BottomAxis->CalcPosPoint(x);
		*ValueY = AmpChart->LeftAxis->CalcPosPoint(y);
		*ValueIntercept = InterpolateAmpDncSeries(*ValueX);


		AmpChartToolX->Value = *ValueX;
		AmpChartToolY->Value = *ValueY;


//		mainForm->LogToFile("Value X = " + FloatToStr(*ValueX));
//		mainForm->LogToFile("Y ValueY= " + FloatToStr(*ValueY));
//		mainForm->LogToFile("Y intercept = " + FloatToStr(*ValueIntercept));
	}
}
//---------------------------------------------------------------------------

double TDynamicCurveForm::InterpolateAmpDncSeries(double XValue)
{
	mainForm->LogToFile("TDynamicCurveForm::InterpolateAmpDncSeries");
	int index;
	double dx,dy;
	double result;
	for(index = 1; index < AmpDncSeries->Count(); index++){
		if(XValue < AmpDncSeries->XValue[index])
			break;
		dx=AmpDncSeries->XValue[index] - AmpDncSeries->XValue[index-1];
		dy=AmpDncSeries->YValue[index] - AmpDncSeries->YValue[index-1];
		if(dx != 0){
			result = dy*(XValue - AmpDncSeries->XValue[index-1])/dx + AmpDncSeries->YValue[index-1];
		}
		else
			result = 0;
	}
	return result;
}
//---------------------------------------------------------------------------

void __fastcall TDynamicCurveForm::FormShow(TObject *Sender)
{

	if(!myfirst){
		myfirst = true;

		TimeCntAdvComboBox->ItemIndex = TimeCntIndex_Val;
		DriveAdvEdit->Text = Drive_Val;
		SetPointAdvEdit->Text = SetPoint_Val;
		UseAdvEdit->Text = Use_Val;
		FromAdvEdit->Text = From_Val;
		ToAdvEdit->Text = To_Val;
		PointsAdvComboBox->Text = PointsCount_Val;


		GetData();
//		ValidateValues();


		DncTable.Dnc_DriveVoltage_Val = Drive_Val;
		mainForm->myDataBase->Execute(mainForm->myDataBase->myQuery->Update("DNC_CONFIG"));

		DriveIndex = DncTable.Dnc_DriveIndex_Val;
		DriveOffset = DncTable.Dnc_DriveOffset_Val;


//      mainForm->LogToFile("Dnc_DriveIndex_Val : " + FloatToStr(DriveIndex));
//		mainForm->LogToFile("Dnc_DriveOffset_Val : " + FloatToStr(DriveOffset));

		MainDriveVal = ((double)Drive_Val * DriveIndex) + DriveOffset;
		if(mainForm->GetSecure() == 0){
			start = false;
			TThread::Synchronize(mainForm->myCommandCreatorThread,StartDnc);
			mainForm->myApproachPanelForm->SettApproach();
			RunAdvGlassButtonClick(NULL);
        }
//        AmpChart->BottomAxis->Automatic = true;
		int w_this = mainForm->myMainControlPanelForm->MainPanel->Width;
		int h_this = mainForm->myMainControlPanelForm->MainPanel->Height;


		PanelSubDnc->Height = h_this - 40;
		PanelSubDnc->Width = w_this - 40;
		PanelSubDnc->Left = 20;
		PanelSubDnc->Top = 20;

		int Height = PanelSubDnc->Height - PanelLabelDnc->Height;

		AmpPanel->Height = (Height * 5)/(double)12;

		int w = PanelSubDnc->Width;
//		int h = PanelSubDnc->Height - PanelLabelDnc->Height - AmpPanel->Height;

		int Top = PanelLabelDnc->Height + AmpPanel->Height + 10;

		int l = 260;
		int p = 30;

		int left1 =  10;
		int left2 = w - 10 - 260;

//		KiAdvEdit->SetParentComponent(RoundApproachSetting);
		Panel1->Left = left1;
		Panel1->Top = Top + 10;
		Panel1->Width = l;
		Panel1->Height = p;
		Panel1->BringToFront();

		Panel2->Left = left1;
		Panel2->Top = Panel1->Top + 40;
		Panel2->Width = l;
		Panel2->Height = p;
		Panel2->BringToFront();

//
//		KdAdvEdit->SetParentComponent(RoundApproachSetting);
		Panel3->Left = left1;
		Panel3->Top = Panel2->Top + 40;
		Panel3->Width = l;
		Panel3->Height = p;
		Panel3->BringToFront();
//
//		StpAdvEdit->SetParentComponent(RoundApproachSetting);
		Panel6->Left = left1;
		Panel6->Top = Panel3->Top + 40;
		Panel6->Width = l;
		Panel6->Height = p;
		Panel6->BringToFront();
//
//		KiFeebackAdvEdit->SetParentComponent(RoundApproachSetting);
		Panel7->Left = left1;
		Panel7->Top = Panel6->Top + 40;
		Panel7->Width = l;
		Panel7->Height = p;
		Panel7->BringToFront();

		PanelRun->Left = left1;
		PanelRun->Top = Panel6->Top + 40;
		PanelRun->Width = l + ContinuousButton->Margins->Right;
		PanelRun->Height = p * 1.5;
		PanelRun->BringToFront();
		RunAdvGlassButton->Width = (PanelRun->Width/3) * 2;
		ContinuousButton->Width = PanelRun->Width/3;


		Panel4->Left = left2;
		Panel4->Top = Panel1->Top;
		Panel4->Width = l;
		Panel4->Height = p;
		Panel4->BringToFront();

		Panel5->Left = left2;
		Panel5->Top = Panel2->Top;
		Panel5->Width = l;
		Panel5->Height = p;
		Panel5->BringToFront();

		Panel8->Left = left2;
		Panel8->Top = Panel3->Top;
		Panel8->Width = l;
		Panel8->Height = p;
		Panel8->BringToFront();

		Panel10->Left = left2;
		Panel10->Top = Panel6->Top;
		Panel10->Width = l;
		Panel10->Height = p;
		Panel10->BringToFront();

		Panel11->Left = left2;
		Panel11->Top = Panel7->Top;
		Panel11->Width = l;
		Panel11->Height = p;
		Panel11->BringToFront();

		Panel9->Width = 150;
		Panel9->Height = 25;
		Panel9->Left = 2;
		Panel9->Top = AmpPanel->Height - Panel9->Height - 2;
		Panel9->BringToFront();
//		MaxAllAdvEditLbl->Top = MaxAllAdvEdit->Top;

		PanelGain->Left = left2;
		PanelGain->Top = PanelRun->Top;
		PanelGain->Width = l;
		PanelGain->Height = PanelRun->Height;
		PanelGain->BringToFront();
		AdvGlowButton1->Width = PanelGain->Width/3 - 2* ContinuousButton->Margins->Right;
		AdvGlowButton10->Width = AdvGlowButton1->Width ;
		AdvGlowButton100->Width = AdvGlowButton1->Width;


        Gain1 = false;
		Gain10 = false;
		Gain100 = false;
		TDynamicCurveForm::AdvGlowButton1Click(NULL);

		AllEditWhite();
	}

}
//---------------------------------------------------------------------------


void __fastcall TDynamicCurveForm::AmpChartMouseMove(TObject *Sender, TShiftState Shift,
		  int X, int Y)
{
	if(AmpDraging){
		ColorBandChartTool->StartValue = AmpChart->BottomAxis->CalcPosPoint(X);
		ColorBandChartTool->EndValue = AmpChart->BottomAxis->CalcPosPoint(X);
	}
}
//---------------------------------------------------------------------------

void __fastcall TDynamicCurveForm::ColorBandChartToolDragging(TObject *Sender)
{
//	ColorBandChartTool->StartValue = AmpChart->BottomAxis->CalcPosPoint(X);
//	ColorBandChartTool->EndValue = AmpChart->BottomAxis->CalcPosPoint(X);
	ColorBandChartToolResized(NULL);
}
//---------------------------------------------------------------------------

void __fastcall TDynamicCurveForm::ColorBandChartToolResized(TObject *Sender)
{

	if(ColorBandChartTool->StartValue < ColorBandChartTool->EndValue){
		FromAdvEdit->Text = IntToStr( (int)(ColorBandChartTool->StartValue) );
		ToAdvEdit->Text = IntToStr( (int)(ColorBandChartTool->EndValue) );
	}
	else{
		FromAdvEdit->Text = IntToStr( (int)(ColorBandChartTool->EndValue) );
		ToAdvEdit->Text = IntToStr( (int)(ColorBandChartTool->StartValue) );
	}

	if( ToAdvEdit->Text.ToInt() - FromAdvEdit->Text.ToInt() >= PointsCount_Val){
		From_Val = FromAdvEdit->Text.ToInt();
		To_Val = ToAdvEdit->Text.ToInt();
		FromAdvEdit->Color = clWhite;
		ToAdvEdit->Color = clWhite;
	}
	else{
        FromAdvEdit->Color = clRed;
		ToAdvEdit->Color = clRed;
		PointsAdvComboBox->Color = clRed;
		PointsAdvComboBox->Refresh();
	}

}
//---------------------------------------------------------------------------

void __fastcall TDynamicCurveForm::FromAdvEditKeyPress(TObject *Sender, System::WideChar &Key)

{
	if(Key == VK_RETURN){
		mainForm->LogToFile("TDynamicCurveForm::FromAdvEditKeyPress");
        Key = 0;
		From_Val = FromAdvEdit->Text.ToInt();

//        if(From_Val < FromMin_Val)
//			From_Val = FromMin_Val;
//		FromAdvEdit->Text = IntToStr(From_Val);

		FromAdvEdit->Color = clWhite;
		GetData();
//		ValidateValues();

		DncTable.Dnc_FrequencyFrom_Val = From_Val;
		mainForm->myDataBase->Execute(mainForm->myDataBase->myQuery->Update("DNC_CONFIG"));



		int diff = To_Val - From_Val;
//		mainForm->LogToFile("From_Val = " + IntToStr(From_Val) + " To_Val = " + IntToStr(To_Val) + " diff = " + IntToStr(diff));
//		mainForm->LogToFile("PointsCount_Val = " + IntToStr(PointsCount_Val));
//		diff = abs(diff);

		if(diff >= PointsCount_Val){
			if(FromAdvEdit->Color == clRed)
				FromAdvEdit->Color = clWhite;
			if(ToAdvEdit->Color == clRed)
				ToAdvEdit->Color = clWhite;
			if(PointsAdvComboBox->Color == clRed)
				PointsAdvComboBox->Color = clWhite;
			PointsAdvComboBox->Refresh();



			start = false;
			TThread::Synchronize(mainForm->myCommandCreatorThread,StartDnc);
		}
		else{
			FromAdvEdit->Color = clRed;
			ToAdvEdit->Color = clRed;
			PointsAdvComboBox->Color = clRed;
			PointsAdvComboBox->Refresh();
		}
	}
}
//---------------------------------------------------------------------------

void __fastcall TDynamicCurveForm::ToAdvEditKeyPress(TObject *Sender, System::WideChar &Key)

{
	if(Key == VK_RETURN){
		mainForm->LogToFile("TDynamicCurveForm::ToAdvEditKeyPress");
        Key = 0;
		ToAdvEdit->Color = clWhite;
		To_Val = ToAdvEdit->Text.ToInt();

//		if(To_Val > ToMax_Val)
//			To_Val = ToMax_Val;
//		ToAdvEdit->Text = IntToStr(To_Val);

		GetData();
//		ValidateValues();

		DncTable.Dnc_FrequencyTo_Val = To_Val;
		mainForm->myDataBase->Execute(mainForm->myDataBase->myQuery->Update("DNC_CONFIG"));



		int diff = To_Val - From_Val;
//		mainForm->LogToFile("From_Val = " + IntToStr(From_Val) + " To_Val = " + IntToStr(To_Val) + " diff = " + IntToStr(diff));
//		mainForm->LogToFile("PointsCount_Val = " + IntToStr(PointsCount_Val));
//		diff = abs(diff);

		if(diff >= PointsCount_Val){
			if(FromAdvEdit->Color == clRed)
				FromAdvEdit->Color = clWhite;
			if(ToAdvEdit->Color == clRed)
				ToAdvEdit->Color = clWhite;
			if(PointsAdvComboBox->Color == clRed)
				PointsAdvComboBox->Color = clWhite;
			PointsAdvComboBox->Refresh();



			start = false;
			TThread::Synchronize(mainForm->myCommandCreatorThread,StartDnc);
		}
		else{
			FromAdvEdit->Color = clRed;
			ToAdvEdit->Color = clRed;
			PointsAdvComboBox->Color = clRed;
			PointsAdvComboBox->Refresh();
		}
	}
}
//---------------------------------------------------------------------------

void __fastcall TDynamicCurveForm::UseAdvEditKeyPress(TObject *Sender, System::WideChar &Key)

{
	if(Key == VK_RETURN){
		mainForm->LogToFile("TDynamicCurveForm::UseAdvEditKeyPress");
		Key = 0;
		Use_Val = UseAdvEdit->Text.ToInt();
		if(Use_Val > ToMax_Val)
			Use_Val = ToMax_Val;
		UseAdvEdit->Text = IntToStr(Use_Val);
		UseAdvEdit->Color = clWhite;

		AmpChartToolX->Value = Use_Val;

		MaxPointofUse = InterpolateAmpDncSeries(Use_Val);

		MaxAdvEdit->Text = FormatFloat("#0.0##",MaxPointofUse);
		SetPAdvEdit->Text = FloatToStr(SetPoint_Val * MaxAdvEdit->Text.ToDouble() / 100 );
		AmpChartToolY->Value = MaxPointofUse * (SetPointAdvEdit->Text.ToInt()/(double)100);


		GetData();
//		ValidateValues();

		DncTable.Dnc_FrequencyUse_Val = Use_Val;
		mainForm->myDataBase->Execute(mainForm->myDataBase->myQuery->Update("DNC_CONFIG"));


		start = false;
		TThread::Synchronize(mainForm->myCommandCreatorThread,StartDnc);
	}
}
//---------------------------------------------------------------------------

void __fastcall TDynamicCurveForm::DriveAdvEditKeyPress(TObject *Sender, System::WideChar &Key)

{
	if(Key == VK_RETURN){
		mainForm->LogToFile("TDynamicCurveForm::DriveAdvEditKeyPress");
        Key = 0;
		DriveAdvEdit->Color = clWhite;
		Drive_Val = DriveAdvEdit->Text.ToInt();
		GetData();
//		ValidateValues();
//		mainForm->LogToFile("send drive");

		DncTable.Dnc_DriveVoltage_Val = Drive_Val;
		mainForm->myDataBase->Execute(mainForm->myDataBase->myQuery->Update("DNC_CONFIG"));

		DriveIndex = DncTable.Dnc_DriveIndex_Val;
		DriveOffset = DncTable.Dnc_DriveOffset_Val;


		mainForm->LogToFile("Dnc_DriveIndex_Val : " + FloatToStr(DriveIndex));
		mainForm->LogToFile("Dnc_DriveOffset_Val : " + FloatToStr(DriveOffset));

		MainDriveVal = ((double)Drive_Val * DriveIndex) + DriveOffset;
		start = false;
		TThread::Synchronize(mainForm->myCommandCreatorThread,StartDnc);
	}
}
//---------------------------------------------------------------------------

void __fastcall TDynamicCurveForm::SetPointAdvEditKeyPress(TObject *Sender, System::WideChar &Key)

{
	if(Key == VK_RETURN){
		mainForm->LogToFile("TDynamicCurveForm::SetPointAdvEditKeyPress");
		Key = 0;

		if(SetPointAdvEdit->Text.ToInt() > 100){
		   SetPointAdvEdit->Text = "100";
		}
		else if(SetPointAdvEdit->Text.ToInt() < 0){
			SetPointAdvEdit->Text = "0";
		}

        SetPointAdvEdit->Color = clWhite;
		SetPoint_Val = SetPointAdvEdit->Text.ToInt();

		GetData();
//		ValidateValues();

		DncTable.Dnc_SetPointPercentage_Val = SetPoint_Val;
		mainForm->myDataBase->Execute(mainForm->myDataBase->myQuery->Update("DNC_CONFIG"));

		SetPAdvEdit->Text = FloatToStr(SetPoint_Val * MaxAdvEdit->Text.ToDouble() / 100 );


		AmpChartToolY->Value = MaxPointofUse * (SetPointAdvEdit->Text.ToInt()/(double)100);

		start = false;
		TThread::Synchronize(mainForm->myCommandCreatorThread,StartDnc);

		mainForm->myApproachPanelForm->SettApproach();
	}
}
//---------------------------------------------------------------------------
void __fastcall TDynamicCurveForm::AmpChartClickAxis(TCustomChart *Sender, TChartAxis *Axis,
		  TMouseButton Button, TShiftState Shift, int X, int Y)
{
	if(Button == mbRight && Axis == AmpChart->BottomAxis){

	}
}
//---------------------------------------------------------------------------

void __fastcall TDynamicCurveForm::FromToComboBoxChange(TObject *Sender)
{
	mainForm->LogToFile("TDynamicCurveForm::FromToComboBoxChange");
	if(FromToComboBox->ItemIndex == 0){
		From_Val = band1From;
		FromAdvEdit->Text = IntToStr(From_Val);
		FromAdvEdit->Color = clWhite;

		To_Val = band1To;
		ToAdvEdit->Text = IntToStr(To_Val);
		ToAdvEdit->Color = clWhite;
	}
	else if(FromToComboBox->ItemIndex == 1){
		From_Val = band2From;
		FromAdvEdit->Text = IntToStr(From_Val);
		FromAdvEdit->Color = clWhite;

		To_Val = band2To;
		ToAdvEdit->Text = IntToStr(To_Val);
		ToAdvEdit->Color = clWhite;
	}
	else if(FromToComboBox->ItemIndex == 2){
		From_Val = band3From;
		FromAdvEdit->Text = IntToStr(From_Val);
		FromAdvEdit->Color = clWhite;

		To_Val = band3To;
		ToAdvEdit->Text = IntToStr(To_Val);
		ToAdvEdit->Color = clWhite;
	}
	else if(FromToComboBox->ItemIndex == 3){
		From_Val = band4From;
		FromAdvEdit->Text = IntToStr(From_Val);
		FromAdvEdit->Color = clWhite;

		To_Val = band4To;
		ToAdvEdit->Text = IntToStr(To_Val);
		ToAdvEdit->Color = clWhite;
	}
//	FromToComboBox->Visible = false;


	GetData();
//		ValidateValues();

	DncTable.Dnc_PointsCount_Val = PointsCount_Val;
	mainForm->myDataBase->Execute(mainForm->myDataBase->myQuery->Update("DNC_CONFIG"));



	int diff = To_Val - From_Val;
//		mainForm->LogToFile("From_Val = " + IntToStr(From_Val) + " To_Val = " + IntToStr(To_Val) + " diff = " + IntToStr(diff));
//		mainForm->LogToFile("PointsCount_Val = " + IntToStr(PointsCount_Val));
//		diff = abs(diff);

	if(diff >= PointsCount_Val){
		if(FromAdvEdit->Color == clRed)
			FromAdvEdit->Color = clWhite;
		if(ToAdvEdit->Color == clRed)
			ToAdvEdit->Color = clWhite;
		if(PointsAdvComboBox->Color == clRed)
			PointsAdvComboBox->Color = clWhite;
		PointsAdvComboBox->Refresh();


//		start = false;
//		TThread::Synchronize(mainForm->myCommandCreatorThread,StartDnc);
	}
	else{
		FromAdvEdit->Color = clRed;
		ToAdvEdit->Color = clRed;
		PointsAdvComboBox->Color = clRed;
		PointsAdvComboBox->Refresh();
	}

	start = false;
	TThread::Synchronize(mainForm->myCommandCreatorThread,StartDnc);

}
//---------------------------------------------------------------------------


void __fastcall TDynamicCurveForm::AdvGlowButton1Click(TObject *Sender)
{
	mainForm->LogToFile("TDynamicCurveForm::AdvGlowButton1Click");
	if(Gain1){
//		Gain100 = false;
//		UpDownBorder(AdvGlowButton100->Appearance,true);
	}
	else{
		Gain1 = true;
		UpDownBorder(AdvGlowButton1->Appearance,false);

		Gain10 = false;
		UpDownBorder(AdvGlowButton10->Appearance,true);

		Gain100 = false;
		UpDownBorder(AdvGlowButton100->Appearance,true);
	}
}
//---------------------------------------------------------------------------

void __fastcall TDynamicCurveForm::AdvGlowButton10Click(TObject *Sender)
{
	mainForm->LogToFile("TDynamicCurveForm::AdvGlowButton10Click");
	if(Gain10){
//		Gain10 = false;
//		UpDownBorder(AdvGlowButton10->Appearance,true);
	}
	else{
		Gain10 = true;
		UpDownBorder(AdvGlowButton10->Appearance,false);

		Gain1 = false;
		UpDownBorder(AdvGlowButton1->Appearance,true);

		Gain100 = false;
		UpDownBorder(AdvGlowButton100->Appearance,true);
	}
}
//---------------------------------------------------------------------------

void __fastcall TDynamicCurveForm::AdvGlowButton100Click(TObject *Sender)
{
	mainForm->LogToFile("TDynamicCurveForm::AdvGlowButton100Click");
	if(Gain1){
//		Gain1 = false;
//		UpDownBorder(AdvGlowButton1->Appearance,true);
	}
	else{
		Gain100 = true;
		UpDownBorder(AdvGlowButton100->Appearance,false);

		Gain1 = false;
		UpDownBorder(AdvGlowButton1->Appearance,true);

		Gain10 = false;
		UpDownBorder(AdvGlowButton10->Appearance,true);
	}
}
//---------------------------------------------------------------------------

void __fastcall TDynamicCurveForm::ToAdvEditChange(TObject *Sender)
{
	ToAdvEdit->Color = clSilver;
}
//---------------------------------------------------------------------------

void __fastcall TDynamicCurveForm::FromAdvEditChange(TObject *Sender)
{
	FromAdvEdit->Color = clSilver;
}
//---------------------------------------------------------------------------

void __fastcall TDynamicCurveForm::UseAdvEditChange(TObject *Sender)
{
	UseAdvEdit->Color = clSilver;
}
//---------------------------------------------------------------------------

void __fastcall TDynamicCurveForm::SetPointAdvEditChange(TObject *Sender)
{
	SetPointAdvEdit->Color = clSilver;
}
//---------------------------------------------------------------------------

void __fastcall TDynamicCurveForm::DriveAdvEditChange(TObject *Sender)
{
	DriveAdvEdit->Color = clSilver;
}
//---------------------------------------------------------------------------

void __fastcall TDynamicCurveForm::TimeCntAdvComboBoxChange(TObject *Sender)
{
	mainForm->LogToFile("TDynamicCurveForm::TimeCntAdvComboBoxChange");
	switch (TimeCntAdvComboBox->ItemIndex){
		case 0:{
			TimeCnt_Val = 0.2;
			TimeCntIndex_Val = TimeCntAdvComboBox->ItemIndex;
			break;
		}
		case 1:{
			TimeCnt_Val = 0.5;
			TimeCntIndex_Val = TimeCntAdvComboBox->ItemIndex;
			break;
		}
		case 2:{
			TimeCnt_Val = 1;
			TimeCntIndex_Val = TimeCntAdvComboBox->ItemIndex;
			break;
		}
		case 3:{
			TimeCnt_Val = 2;
			TimeCntIndex_Val = TimeCntAdvComboBox->ItemIndex;
			break;
		}
		case 4:{
			TimeCnt_Val = 5;
			TimeCntIndex_Val = TimeCntAdvComboBox->ItemIndex;
			break;
		}
		case 5:{
			TimeCnt_Val = 10;
			TimeCntIndex_Val = TimeCntAdvComboBox->ItemIndex;
			break;
		}
		case 6:{
			TimeCnt_Val = 20;
			TimeCntIndex_Val = TimeCntAdvComboBox->ItemIndex;
			break;
		}
		case 7:{
			TimeCnt_Val = 50;
			TimeCntIndex_Val = TimeCntAdvComboBox->ItemIndex;
			break;
		}
		case 8:{
			TimeCnt_Val = 100;
			TimeCntIndex_Val = TimeCntAdvComboBox->ItemIndex;
			break;
		}
		case 9:{
			TimeCnt_Val = 200;
			TimeCntIndex_Val = TimeCntAdvComboBox->ItemIndex;
			break;
		}
		case 10:{
			TimeCnt_Val = 500;
			TimeCntIndex_Val = TimeCntAdvComboBox->ItemIndex;
			break;
		}
		case 11:{
			TimeCnt_Val = 1000;
			TimeCntIndex_Val = TimeCntAdvComboBox->ItemIndex;
			break;
		}
		case 12:{
			TimeCnt_Val = 2000;
			TimeCntIndex_Val = TimeCntAdvComboBox->ItemIndex;
			break;
		}
		case 13:{
			TimeCnt_Val = 5000;
			TimeCntIndex_Val = TimeCntAdvComboBox->ItemIndex;
			break;
		}
		default:{
			TimeCnt_Val = 0.2;
			TimeCntAdvComboBox->ItemIndex = 0;
			break;
		}
	}
	GetData();
//		ValidateValues();

	DncTable.Dnc_TimeCnt_Val = TimeCntIndex_Val;
	mainForm->myDataBase->Execute(mainForm->myDataBase->myQuery->Update("DNC_CONFIG"));


	start = false;
	TThread::Synchronize(mainForm->myCommandCreatorThread,StartDnc);
}
//---------------------------------------------------------------------------

void __fastcall TDynamicCurveForm::PointsAdvComboBoxChange(TObject *Sender)
{
	mainForm->LogToFile("TDynamicCurveForm::PointsAdvComboBoxChange");
	PointsCount_Val = pow((double)2, PointsAdvComboBox->ItemIndex+ 6);

	GetData();
//		ValidateValues();

	DncTable.Dnc_PointsCount_Val = PointsCount_Val;
	mainForm->myDataBase->Execute(mainForm->myDataBase->myQuery->Update("DNC_CONFIG"));




	int diff = To_Val - From_Val;
//		mainForm->LogToFile("From_Val = " + IntToStr(From_Val) + " To_Val = " + IntToStr(To_Val) + " diff = " + IntToStr(diff));
//		mainForm->LogToFile("PointsCount_Val = " + IntToStr(PointsCount_Val));
//		diff = abs(diff);

	if(diff >= PointsCount_Val){
		if(FromAdvEdit->Color == clRed)
			FromAdvEdit->Color = clWhite;
		if(ToAdvEdit->Color == clRed)
			ToAdvEdit->Color = clWhite;
		if(PointsAdvComboBox->Color == clRed)
			PointsAdvComboBox->Color = clWhite;
		PointsAdvComboBox->Refresh();


		start = false;
		TThread::Synchronize(mainForm->myCommandCreatorThread,StartDnc);
	}
	else{
		FromAdvEdit->Color = clRed;
		ToAdvEdit->Color = clRed;
		PointsAdvComboBox->Color = clRed;
		PointsAdvComboBox->Refresh();
	}
}
//---------------------------------------------------------------------------

void TDynamicCurveForm::AllEditWhite()
{
	TimeCntAdvComboBox->Color = clWhite;
	DriveAdvEdit->Color = clWhite;
	SetPointAdvEdit->Color = clWhite;
	UseAdvEdit->Color = clWhite;
	FromAdvEdit->Color = clWhite;
	ToAdvEdit->Color = clWhite;
	PointsAdvComboBox->Color = clWhite;
	FromToComboBox->Color = clWhite;
}

//---------------------------------------------------------------------------



