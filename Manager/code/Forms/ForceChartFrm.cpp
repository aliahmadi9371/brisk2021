//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "ForceChartFrm.h"
#include "mainUnit.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "AdvGlowButton"
#pragma link "CurvyControls"
#pragma link "VCLTee.TeeComma"
#pragma link "VCLTee.TeeEdit"
#pragma link "VCLTee.TeeTools"
#pragma link "AdvGlassButton"
#pragma link "VCLTee.TeeSeriesRegion"
#pragma link "htmlbtns"
#pragma link "VCLTee.TeeSeriesBandTool"
#pragma resource "*.dfm"
TForceChartForm *ForceChartForm;
//---------------------------------------------------------------------------
__fastcall TForceChartForm::TForceChartForm(TComponent* Owner)
	: TForm(Owner)
{

}
//---------------------------------------------------------------------------
void __fastcall TForceChartForm::ChartPickerChange(TObject *Sender)
{
	KAdvEdit->Color = clWhite;
	PickSeries(ChartPicker->ItemIndex+1);
}
//---------------------------------------------------------------------------
void TForceChartForm::SetupChart()
{

	TeeCommander1->ButtonZoom->Hide();
	TeeCommander1->Button3D->Hide();
	TeeCommander1->ButtonDepth->Hide();
	TeeCommander1->ButtonMove->Hide();
	TeeCommander1->ButtonRotate->Hide();
	TeeCommander1->ButtonPrint->Hide();
	TeeCommander1->ButtonSave->Hide();
	int LeftSide = TeeCommander1->ButtonRotate->Left;

// 	TeeCommander1->ButtonNormal->Hint = "Left To Select , Right To Zoom";
//	TeeCommander1->LabelText->ShowHint = true;

	TeeCommander1->ButtonEdit->Left = LeftSide;
	TeeCommander1->ButtonCopy->Left = LeftSide +30;

	Panel11->Top = TeeCommander1->Top;
	Panel11->Left = LeftSide + 60;
	UnitLabel->Top = Panel11->Top;
	RadioButtonUnitZ->Top = UnitLabel->Top + 3;
	RadioButtonUnitTime->Top = RadioButtonUnitZ->Top;
	ChartPicker->Top = UnitLabel->Top + 1;

	ChartChart->Legend->Top = 20;
	ChartChart->Legend->Left = ChartChart->Width - ChartChart->Legend->Width - 100;

	PanelButtonShow(ChartPicker->ItemIndex+1);

	ChartTool4->Condition = bcLower;

}

//---------------------------------------------------------------------------

void TForceChartForm::PickSeries(int series)
{
	mainForm->LogToFile("TForceChartForm::PickSeries , series = " + IntToStr(series));
	X1AdvEdit->Text = "";
	Y1AdvEdit->Text = "";
	X2AdvEdit->Text = "";
	Y2AdvEdit->Text = "";
	dYdXAdvEdit->Text = "";

    X1AdvEdit->Color = clWhite;
	Y1AdvEdit->Color = clWhite;
	X2AdvEdit->Color = clWhite;
	Y2AdvEdit->Color = clWhite;
	dYdXAdvEdit->Color = clWhite;

    ChartChart->UndoZoom();
	Series101->Active = false;
	Series102->Active = false;


	ChartTool3->Lines->Clear();
	ChartTool1->Active = false;
	ChartTool2->Active = false;
	FirstPoint = 0;
	ChartChartSetting(series);
	PanelButtonShow(series);
	ChartChart->Legend->Visible = false;


	if(RadioButtonUnitZ->Checked){
		switch(series){
			case 1:{
                Series101->AssignValues(Series1);
				Series102->AssignValues(Series2);
				Series101->Active = true;
				Series102->Active = true;
				Series101->Title = "Topo-F";
				Series102->Title = "Topo-B";
				Series101->ShowInEditor = true;
				Series102->ShowInEditor = true;
				if(AllScale)
					ChartChart->LeftAxis->Title->Caption = "Topo (nm)";
				else
					ChartChart->LeftAxis->Title->Caption = "Topo";
				ChartTool1->Series = Series101;
				ChartTool2->Series = Series102;
				SameSeries = false;
				ChartChart->Legend->Visible = true;
				break;
			}
			case 2:{
                Series101->AssignValues(Series3);
				Series102->AssignValues(Series4);
				Series101->Active = true;
				Series102->Active = true;
				Series101->Title = "TB-F";
				Series102->Title = "TB-B";
				Series101->ShowInEditor = true;
				Series102->ShowInEditor = true;
				if (mainForm->myTcpThread->Fs_C_Factor_Set) {
					ChartChart->LeftAxis->Title->Caption = "TB (nN)";
				}
				else{
					ChartChart->LeftAxis->Title->Caption = "TB (mV)";
				}
				ChartTool1->Series = Series101;
				ChartTool2->Series = Series102;
				SameSeries = false;
				ChartChart->Legend->Visible = true;
				break;
			}
			case 3:{
                Series101->AssignValues(Series5);
				Series102->AssignValues(Series6);
				Series101->Active = true;
				Series102->Active = true;
				Series101->Title = "LR-F";
				Series102->Title = "LR-B";
				Series101->ShowInEditor = true;
				Series102->ShowInEditor = true;
				ChartChart->LeftAxis->Title->Caption = "LR (mV)";
				ChartTool1->Series = Series101;
				ChartTool2->Series = Series102;
				SameSeries = false;
				ChartChart->Legend->Visible = true;
				break;
			}
			case 4:{
                Series101->AssignValues(Series11);
				Series102->AssignValues(Series12);
				Series101->Title = "cmAFM-F";
				Series102->Title = "cmAFM-B";
				Series101->Active = true;
				Series102->Active = true;
				Series101->ShowInEditor = true;
				Series102->ShowInEditor = true;
				ChartChart->LeftAxis->Title->Caption = "CmAfm (z)";
				ChartTool1->Series = Series101;
				ChartTool2->Series = Series102;
				SameSeries = false;
				ChartChart->Legend->Visible = true;
				break;
			}
			case 5:{
                Series101->AssignValues(Series1);
				Series102->AssignValues(Series2);
				Series101->Active = true;
				Series101->Title = "Topo-F";
				Series102->Title = "Topo-B";
				Series101->ShowInEditor = true;
				Series102->ShowInEditor = true;
				if(AllScale)
					ChartChart->LeftAxis->Title->Caption = "Topo-F (nm)";
				else
					ChartChart->LeftAxis->Title->Caption = "Topo-F";
				ChartTool1->Series = Series101;
				ChartTool2->Series = Series101;
				ChartTool4->Series = Series101;

				SameSeries = true;
				break;

			}
			case 6:{
                Series101->AssignValues(Series1);
				Series102->AssignValues(Series2);
				Series102->Active = true;
				Series101->Title = "Topo-F";
				Series102->Title = "Topo-B";
				Series101->ShowInEditor = true;
				Series102->ShowInEditor = true;
				if(AllScale)
					ChartChart->LeftAxis->Title->Caption = "Topo-B (nm)";
				else
					ChartChart->LeftAxis->Title->Caption = "Topo-B";
				ChartTool1->Series = Series102;
				ChartTool2->Series = Series102;
				ChartTool4->Series = Series102;
				SameSeries = true;
				break;
			}
//			case 7:{
//				Series7->Active = true;
//				ChartChart->LeftAxis->Title->Caption = "Amp_Fw(z)";
//				ChartTool1->Series = Series7;
//				ChartTool2->Series = Series7;
//				SameSeries = true;
//				break;
//			}
//			case 8:{
//				Series8->Active = true;
//				ChartChart->LeftAxis->Title->Caption = "Amp_Bw(z)";
//				ChartTool1->Series = Series8;
//				ChartTool2->Series = Series8;
//				SameSeries = true;
//				break;
//			}
//			case 9:{
//				Series9->Active = true;
//				ChartChart->LeftAxis->Title->Caption = "Phase_Fw(z)";
//				ChartTool1->Series = Series9;
//				ChartTool2->Series = Series9;
//				SameSeries = true;
//				break;
//			}
//			case 10:{
//				Series10->Active = true;
//				ChartChart->LeftAxis->Title->Caption = "Phase_Fw(z)";
//				ChartTool1->Series = Series10;
//				ChartTool2->Series = Series10;
//				SameSeries = true;
//				break;
//			}
			case 7:{
                Series101->AssignValues(Series3);
				Series102->AssignValues(Series4);
				Series101->Active = true;
				Series101->Title = "TB-F";
				Series102->Title = "TB-B";
				Series101->ShowInEditor = true;
				Series102->ShowInEditor = true;
				if (mainForm->myTcpThread->Fs_C_Factor_Set) {
					ChartChart->LeftAxis->Title->Caption = "TB-F (nN)";
				}
				else{
					ChartChart->LeftAxis->Title->Caption = "TB-F (mV)";
				}
				ChartTool1->Series = Series101;
				ChartTool2->Series = Series101;
				ChartTool4->Series = Series101;
				SameSeries = true;
				break;
			}
			case 8:{
                Series101->AssignValues(Series3);
				Series102->AssignValues(Series4);
				Series102->Active = true;
				Series101->Title = "TB-F";
				Series102->Title = "TB-B";
				Series101->ShowInEditor = true;
				Series102->ShowInEditor = true;
				if (mainForm->myTcpThread->Fs_C_Factor_Set) {
					ChartChart->LeftAxis->Title->Caption = "TB-B (nN)";
				}
				else{
					ChartChart->LeftAxis->Title->Caption = "TB-B (mV)";
				}
				ChartTool1->Series = Series102;
				ChartTool2->Series = Series102;
				ChartTool4->Series = Series102;
				SameSeries = true;
				break;
			}
			case 9:{
                Series101->AssignValues(Series5);
				Series102->AssignValues(Series6);
				Series101->Active = true;
				Series101->Title = "LR-F";
				Series102->Title = "LR-B";
				Series101->ShowInEditor = true;
				Series102->ShowInEditor = true;
				ChartChart->LeftAxis->Title->Caption = "LR-F (mV)";
				ChartTool1->Series = Series101;
				ChartTool2->Series = Series101;
				ChartTool4->Series = Series101;
				SameSeries = true;
				break;

			}
			case 10:{
                Series101->AssignValues(Series5);
				Series102->AssignValues(Series6);
				Series102->Active = true;
				Series101->Title = "LR-F";
				Series102->Title = "LR-B";
				Series101->ShowInEditor = true;
				Series102->ShowInEditor = true;
				ChartChart->LeftAxis->Title->Caption = "LR-B (mV)";
				ChartTool1->Series = Series102;
				ChartTool2->Series = Series102;
				ChartTool4->Series = Series102;
				SameSeries = true;
				break;
			}
			case 11:{
                Series101->AssignValues(Series11);
				Series102->AssignValues(Series12);
				Series101->Active = true;
				Series101->Title = "cmAFM-F";
				Series102->Title = "cmAFM-B";
				Series101->ShowInEditor = true;
				Series102->ShowInEditor = true;
				ChartChart->LeftAxis->Title->Caption = "cmAFM-F (z)";
				ChartTool1->Series = Series101;
				ChartTool2->Series = Series101;
				ChartTool4->Series = Series101;
				SameSeries = true;
				break;
			}
//			case 16:{
//				Series8->Active = true;
//				Series7->Active = true;
//				ChartChart->LeftAxis->Title->Caption = "Amp(z)";
//				ChartTool1->Series = Series7;
//				ChartTool2->Series = Series8;
//				SameSeries = false;
//				break;
//			}
//			case 17:{
//				Series9->Active = true;
//				Series10->Active = true;
//				ChartChart->LeftAxis->Title->Caption = "Phase(z)";
//				ChartTool1->Series = Series9;
//				ChartTool2->Series = Series10;
//				SameSeries = false;
//				break;
//			}
			case 12:{
                Series101->AssignValues(Series11);
				Series102->AssignValues(Series12);
				Series102->Active = true;
				Series101->Title = "cmAFM-F";
				Series102->Title = "cmAFM-B";
				Series101->ShowInEditor = true;
				Series102->ShowInEditor = true;
				ChartChart->LeftAxis->Title->Caption = "cmAFM-B (z)";
				ChartTool1->Series = Series102;
				ChartTool2->Series = Series102;
				ChartTool4->Series = Series102;
				SameSeries = true;
				break;

			}
			default:{
				Series101->AssignValues(Series1);
				Series102->AssignValues(Series2);
				Series101->Active = true;
				Series102->Active = true;
				Series101->Title = "Topo-F";
				Series102->Title = "Topo-B";
				Series101->ShowInEditor = true;
				Series102->ShowInEditor = true;
				if(AllScale)
					ChartChart->LeftAxis->Title->Caption = "Topo (nm)";
				else
					ChartChart->LeftAxis->Title->Caption = "Topo";
				ChartTool1->Series = Series101;
				ChartTool2->Series = Series102;
				SameSeries = false;
				ChartChart->Legend->Visible = true;
				break;
			}
		}
	}
	else{
		Panel6->Visible = false;
		SlopeRadioButton->Visible = false;
		IntegralRadioButton->Visible = false;
		ChartChart->BottomAxis->Title->Caption = "Time (ms)";
		switch(series){
			case 1:{
                Series101->AssignValues(Series13);
				Series102->AssignValues(Series25);
				Series102->Active = true;
				Series101->Title = "Topo-F";
				Series102->Title = "Topo";
				Series101->ShowInEditor = false;
				Series102->ShowInEditor = true;
				if(AllScale)
					ChartChart->LeftAxis->Title->Caption = "Topo (nm)";
				else
					ChartChart->LeftAxis->Title->Caption = "Topo";
				ChartTool1->Series = Series102;
				ChartTool2->Series = Series102;
				SameSeries = false;
				break;
			}
			case 2:{
                Series101->AssignValues(Series15);
				Series102->AssignValues(Series26);
				Series102->Active = true;
				Series102->Title = "Tb";
				Series101->ShowInEditor = false;
				Series102->ShowInEditor = true;
				if (mainForm->myTcpThread->Fs_C_Factor_Set) {
					ChartChart->LeftAxis->Title->Caption = "TB (nN)";
				}
				else{
					ChartChart->LeftAxis->Title->Caption = "TB (mV)";
				}
				ChartTool1->Series = Series102;
				ChartTool2->Series = Series102;
				SameSeries = false;
				break;
			}
			case 3:{
                Series101->AssignValues(Series17);
				Series102->AssignValues(Series27);
				Series102->Active = true;
				Series102->Title = "Lr";
				Series101->ShowInEditor = false;
				Series102->ShowInEditor = true;
				ChartChart->LeftAxis->Title->Caption = "LR (mV)";
				ChartTool1->Series = Series102;
				ChartTool2->Series = Series102;
				SameSeries = false;
				break;
			}
			case 4:{
                Series101->AssignValues(Series23);
				Series102->AssignValues(Series28);
				Series102->Active = true;
				Series102->Title = "CmAfm";
				Series101->ShowInEditor = false;
				Series102->ShowInEditor = true;
				ChartChart->LeftAxis->Title->Caption = "CmAfm (t)";
				ChartTool1->Series = Series102;
				ChartTool2->Series = Series102;
				SameSeries = false;
				break;
			}
			case 5:{
                Series101->AssignValues(Series13);
				Series102->AssignValues(Series14);
				Series101->Active = true;
				Series101->Title = "Topo-F";
				Series102->Title = "Topo-B";
				Series101->ShowInEditor = true;
				Series102->ShowInEditor = true;
				if(AllScale)
					ChartChart->LeftAxis->Title->Caption = "Topo-F (nm)";
				else
					ChartChart->LeftAxis->Title->Caption = "Topo-F";
				ChartTool1->Series = Series101;
				ChartTool2->Series = Series101;
				SameSeries = true;
				break;

			}
			case 6:{
                Series101->AssignValues(Series13);
				Series102->AssignValues(Series14);
				Series102->Active = true;
				Series101->Title = "Topo-F";
				Series102->Title = "Topo-B";
				Series101->ShowInEditor = true;
				Series102->ShowInEditor = true;
				if(AllScale)
					ChartChart->LeftAxis->Title->Caption = "Topo-B (nm)";
				else
					ChartChart->LeftAxis->Title->Caption = "Topo-B";
				ChartTool1->Series = Series102;
				ChartTool2->Series = Series102;
				SameSeries = true;
				break;

			}
//			case 7:{
//				Series19->Active = true;
//				ChartChart->LeftAxis->Title->Caption = "Amp_Fw(t)";
//				ChartTool1->Series = Series19;
//				ChartTool2->Series = Series19;
//				SameSeries = true;
//				break;
//			}
//			case 8:{
//				Series20->Active = true;
//				ChartChart->LeftAxis->Title->Caption = "Amp_Bw(t)";
//				ChartTool1->Series = Series20;
//				ChartTool2->Series = Series20;
//				SameSeries = true;
//				break;
//			}
//			case 9:{
//				Series21->Active = true;
//				ChartChart->LeftAxis->Title->Caption = "Phase_Fw(t)";
//				ChartTool1->Series = Series21;
//				ChartTool2->Series = Series21;
//				SameSeries = true;
//				break;
//			}
//			case 10:{
//				Series22->Active = true;
//				ChartChart->LeftAxis->Title->Caption = "Phase_Fw(t)";
//				ChartTool1->Series = Series22;
//				ChartTool2->Series = Series22;
//				SameSeries = true;
//				break;
//			}
			case 7:{
				Series101->AssignValues(Series15);
				Series102->AssignValues(Series16);
				Series101->Active = true;
				Series101->Title = "TB-F";
				Series102->Title = "TB-B";
				Series101->ShowInEditor = true;
				Series102->ShowInEditor = true;
				if (mainForm->myTcpThread->Fs_C_Factor_Set) {
					ChartChart->LeftAxis->Title->Caption = "TB-F (nN)";
				}
				else{
					ChartChart->LeftAxis->Title->Caption = "TB-F (mV)";
				}
				ChartTool1->Series = Series101;
				ChartTool2->Series = Series101;
				SameSeries = true;
				break;
			}
			case 8:{
                Series101->AssignValues(Series15);
				Series102->AssignValues(Series16);
				Series102->Active = true;
				Series101->Title = "TB-F";
				Series102->Title = "TB-B";
				Series101->ShowInEditor = true;
				Series102->ShowInEditor = true;
				if (mainForm->myTcpThread->Fs_C_Factor_Set) {
					ChartChart->LeftAxis->Title->Caption = "TB-B (nN)";
				}
				else{
					ChartChart->LeftAxis->Title->Caption = "TB-B (mV)";
				}
				ChartTool1->Series = Series102;
				ChartTool2->Series = Series102;
				SameSeries = true;
				break;

			}
			case 9:{
                Series101->AssignValues(Series17);
				Series102->AssignValues(Series18);
				Series101->Active = true;
				Series101->Title = "LR-F";
				Series102->Title = "LR-B";
				Series101->ShowInEditor = true;
				Series102->ShowInEditor = true;
				ChartChart->LeftAxis->Title->Caption = "LR-F (mV)";
				ChartTool1->Series = Series101;
				ChartTool2->Series = Series101;
				SameSeries = true;
				break;

			}
			case 10:{
                Series101->AssignValues(Series17);
				Series102->AssignValues(Series18);
				Series102->Active = true;
				Series101->Title = "LR-F";
				Series102->Title = "LR-B";
				Series101->ShowInEditor = true;
				Series102->ShowInEditor = true;
				ChartChart->LeftAxis->Title->Caption = "LR-B (mV)";
				ChartTool1->Series = Series102;
				ChartTool2->Series = Series102;
				SameSeries = true;
				break;

			}
			case 11:{
                Series101->AssignValues(Series23);
				Series102->AssignValues(Series24);
				Series101->Active = true;
				Series101->Title = "cmAFM-F";
				Series102->Title = "cmAFM-B";
				Series101->ShowInEditor = true;
				Series102->ShowInEditor = true;
				ChartChart->LeftAxis->Title->Caption = "cmAFM-F (t)";
				ChartTool1->Series = Series101;
				ChartTool2->Series = Series101;
				SameSeries = true;
				break;

			}
//			case 16:{
//				Series8->Active = true;
//				Series7->Active = true;
//				ChartChart->LeftAxis->Title->Caption = "Amp (z)";
//				ChartTool1->Series = NULL;
//				ChartTool2->Series = NULL;
//				SameSeries = false;
//				break;
//			}
//			case 17:{
//				Series9->Active = true;
//				Series10->Active = true;
//				ChartChart->LeftAxis->Title->Caption = "Phase (z)";
//				ChartTool1->Series = NULL;
//				ChartTool2->Series = NULL;
//				SameSeries = false;
//				break;
//			}
			case 12:{
                Series101->AssignValues(Series23);
				Series102->AssignValues(Series24);
				Series102->Active = true;
				Series101->Title = "cmAFM-F";
				Series102->Title = "cmAFM-B";
				Series101->ShowInEditor = true;
				Series102->ShowInEditor = true;
				ChartChart->LeftAxis->Title->Caption = "cmAFM-B (t)";
				ChartTool1->Series = Series102;
				ChartTool2->Series = Series102;
				SameSeries = true;
				break;
			}
			default:{
				Series101->AssignValues(Series13);
				Series102->AssignValues(Series25);
				Series102->Active = true;
				Series101->Title = "Topo-F";
				Series102->Title = "Topo";
				Series101->ShowInEditor = false;
				Series102->ShowInEditor = true;
				if(AllScale)
					ChartChart->LeftAxis->Title->Caption = "Topo (nm)";
				else
					ChartChart->LeftAxis->Title->Caption = "Topo";
				ChartTool1->Series = Series102;
				ChartTool2->Series = Series102;
				SameSeries = false;
				break;
			}
		}
	}
}
//---------------------------------------------------------------------------

void TForceChartForm::ChartChartSetting(int series){

	mainForm->LogToFile("TForceChartForm::ChartChartSetting , series = " + IntToStr(series));

	if(series== 7 || series == 8){
		Panel5->Top = Panel4->Top;
		Panel8->Top = Panel3->Top;
		Panel8->Left = Panel5->Left ;
		Panel8->Visible = true;
	}
	else{
		Panel8->Visible = false;
	}

	if(mainForm->myForceForm->FinalMode == 1 || mainForm->myForceForm->FinalMode == 4 || mainForm->myForceForm->FinalMode == 5){

		if (RadioButtonUnitZ->Checked && (series == -1 || series == 5 || series == 7 || series == 9 || series == 11 || series == 1 || series == 2 || series == 3 || series == 4)) {
			ChartChart->BottomAxis->Title->Caption = "Z (nm)";
			if(!XInverted){
				if((mainForm->myForceForm->Finaldz * mainForm->myForceForm->index * pow10l(mainForm->myForceForm->scale*3)) >= 0 ){
					ChartChart->BottomAxis->Inverted = true;
				}
				else{
					ChartChart->BottomAxis->Inverted = false;
				}
			}
		}
		else if(RadioButtonUnitZ->Checked && (series == 6 || series == 8 || series == 10 || series == 12 )) {
			ChartChart->BottomAxis->Title->Caption = "Z (nm)";
			if(!XInverted){
				if((mainForm->myForceForm->Finaldz * mainForm->myForceForm->index * pow10l(mainForm->myForceForm->scale*3)) >= 0){
					ChartChart->BottomAxis->Inverted = false;
				}
				else{
					ChartChart->BottomAxis->Inverted = true;
				}
			}
		}
		else{
			if(!XInverted){
				ChartChart->BottomAxis->Inverted = false;
			}
		}
	}
	else{
		if (RadioButtonUnitZ->Checked && (series == -1 || series == 5 || series == 7 || series == 9 || series == 11 || series == 1 || series == 2 || series == 3 || series == 4)) {
			ChartChart->BottomAxis->Title->Caption = "U (mV)";
			if(!XInverted){
				if((mainForm->myForceForm->FinalU * mainForm->myForceForm->U_index * pow10l(mainForm->myForceForm->U_Scale*3)) >= 0 ){
					ChartChart->BottomAxis->Inverted = false;
				}
				else{
					ChartChart->BottomAxis->Inverted = true;
				}
			}
		}
		else if(RadioButtonUnitZ->Checked && (series == 6 || series == 8 || series == 10 || series == 12 )) {
			ChartChart->BottomAxis->Title->Caption = "U (mV)";
			if(!XInverted){
				if((mainForm->myForceForm->FinalU * mainForm->myForceForm->U_index * pow10l(mainForm->myForceForm->U_Scale*3)) >= 0){
					ChartChart->BottomAxis->Inverted = true;
				}
				else{
					ChartChart->BottomAxis->Inverted = false;
				}
			}
		}
		else{
			if(!XInverted){
				ChartChart->BottomAxis->Inverted = false;
            }
		}
	}
}
//---------------------------------------------------------------------------

void __fastcall TForceChartForm::FormCloseQuery(TObject *Sender, bool &CanClose)
{
	CanClose = false;
}
//---------------------------------------------------------------------------

void __fastcall TForceChartForm::FormClose(TObject *Sender, TCloseAction &Action)

{
	Action = Vcl::Forms::caNone;
}
//---------------------------------------------------------------------------

void __fastcall TForceChartForm::CloseButtonClic(TObject *Sender)
{
	mainForm->LogToFile("TForceChartForm::CloseButtonClic");
	mainForm->Enabled = true;
	mainForm->myVideoForm->VideoGrabber1->StartPreview();
	if(mainForm->myForceForm->Osc_PreviousState)
		mainForm->myOscForm->p1PauseClick(NULL);
	mainForm->myVideoForm->BringToFront();
	ChartPicker->ItemIndex = 0;
	ChartChart->UndoZoom();
	this->Hide();

}
//---------------------------------------------------------------------------

void __fastcall TForceChartForm::FormShow(TObject *Sender)
{
	if(!first){
		first = true;

		ChartTool1->Active = false;
		ChartTool2->Active = false;
		ChartTool1->Snap = true;
		ChartTool2->Snap = true;

        XInverted = false;

		Panel7->Height = 120;
		Panel7->Width = 640;

		Panel7->Top = ChartChart->Height / 2 - Panel7->Height /2 ;
		Panel7->Left = ChartChart->Width / 2 - Panel7->Width / 2;

		IntegralRadioButton->Left = Panelbuttons->Width - IntegralRadioButton->Width - 10;
		SlopeRadioButton->Left = IntegralRadioButton->Left;

		QuestionLabel->Left = 5;
		QuestionLabel->Top = 5;
		QuestionLabel->Width = 630;
		QuestionLabel->Height = 50;
		YesButton->Top = QuestionLabel->Height + 30;
		NoButton->Top = YesButton->Top;
		YesButton->Left = Panel7->Width / 2 - YesButton->Width -5;
		NoButton->Left = Panel7->Width / 2 + 5;
		Panel7->Hide();


		C_Factor_Set = ForceTable.C_Factor_Set;
		K_Factor = ForceTable.K_Factor;


		KAdvEdit->Text = FloatToStr(K_Factor);

		if(mainForm->myTcpThread->Fs_C_Factor_Set)
			Panel8->Enabled = false;



		FirstPoint = 0;
		SetupChart();
		ShowThemesEditor(false); // Add #include <VCLTee.TeeThemeEditor.hpp> to remove theme frome editor
	}
}
//---------------------------------------------------------------------------

void __fastcall TForceChartForm::FormCreate(TObject *Sender)
{
	this->Hide();
	first = false;
}
//---------------------------------------------------------------------------
void __fastcall TForceChartForm::ChartChartClickSeries(TCustomChart *Sender, TChartSeries *Series,
		  int ValueIndex, TMouseButton Button, TShiftState Shift, int X,
		  int Y)
{
	if(Button == mbLeft){
		mainForm->LogToFile("TForceChartForm::ChartChartClickSeries , FirstPoint = " + IntToStr(FirstPoint));
//		ColorBand->Active = true;
//		ColorBand->StartValue = floor(ChartChart->BottomAxis->CalcPosPoint(X) * 1000 + 0.5) / (double) 1000;
//		ColorBand->EndValue = ColorBand->StartValue;
//		X1AdvEdit->Text = FloatToStr(ColorBand->StartValue);

		if(SameSeries && RadioButtonUnitZ->Checked){
			if(SlopeRadioButton->Checked){
				ChartTool1->Style = 2;
				ChartTool2->Style = 2;
				if(FirstPoint == 0){
					ChartTool3->Lines->Clear();
					ChartTool2->Active = false;
					double x1 = floor(ChartChart->BottomAxis->CalcPosPoint(X) * 1000 + 0.5) / (double) 1000;
					X1AdvEdit->Text = FloatToStr(x1);
					double y1 = floor(ChartChart->LeftAxis->CalcPosPoint(Y) * 1000 + 0.5) / (double) 1000;
					ChartTool1->Active = true;
					ChartTool1->XValue = x1;
					ChartTool1->YValue = y1;
					Y1AdvEdit->Text = FloatToStr(y1);
					Y1AdvEdit->Color = clSilver;
					X2AdvEdit->Text = "";
					Y2AdvEdit->Text = "";
					dYdXAdvEdit->Text = "";
                    FirstPoint = 1;
//					ChartTool3->FromPoint = TPoint(ChartTool2->XValue, ChartTool1->YValue);

				}
				else if(FirstPoint == 1){
					double x1 = X1AdvEdit->Text.ToDouble();
					double y1 = Y1AdvEdit->Text.ToDouble();
					double x2 = floor(ChartChart->BottomAxis->CalcPosPoint(X) * 1000 + 0.5) / (double) 1000;
					double y2 = floor(ChartChart->LeftAxis->CalcPosPoint(Y) * 1000 + 0.5) / (double) 1000;
					ChartTool2->Active = true;
					ChartTool2->XValue = x2;
					ChartTool2->YValue = y2;
					X2AdvEdit->Text = FloatToStr(x2);
					Y2AdvEdit->Text = FloatToStr(y2);
					double d = floor(((y2 - y1) / (x2 - x1)) * 1000 + 0.5) / (double)1000;

					dYdXAdvEdit->Text = FloatToStr(d);

					ChartTool3->ToPoint = TPoint(ChartTool2->XValue, ChartTool1->YValue);

					ChartTool3->Lines->AddLine(x1,y1,x2,y2);
//					double d = floor(((y2 - y1) / (x2 - x1)) * 1000 + 0.5) / (double)1000;
					dYdXAdvEdit->Text = FloatToStr(d);
					if(ChartPicker->ItemIndex == 2 || ChartPicker->ItemIndex == 3){
						dYdXAdvEdit->Color = clSilver;
                    }
					FirstPoint = 3;
				}
			}
			else{
				ChartTool1->Style = 1;
				ChartTool2->Style = 1;
				if(FirstPoint == 0){
					ChartTool2->Active = false;
					ChartTool1->Active = false;
					ChartTool4->Active = false;
					ChartTool3->Lines->Clear();
					y_bound = floor(ChartChart->LeftAxis->CalcPosPoint(Y) * 1000 + 0.5) / (double) 1000;
					Y1AdvEdit->Text = FloatToStr(y_bound);
					ChartTool3->Lines->AddLine(ChartChart->BottomAxis->Minimum,y_bound,ChartChart->BottomAxis->Maximum,y_bound);
					X2AdvEdit->Text = "";
					dYdXAdvEdit->Text = "";

				}
				else if(FirstPoint == 1){
					ChartTool2->Active = false;
					ChartTool1->Active = false;
					double x1 = floor(ChartChart->BottomAxis->CalcPosPoint(X) * 1000 + 0.5) / (double) 1000;
					X1AdvEdit->Text = FloatToStr(x1);
					ChartTool1->Active = true;
					ChartTool1->XValue = x1;
					X2AdvEdit->Text = "";
					dYdXAdvEdit->Text = "";
					FirstPoint = 2;
				}
				else if(FirstPoint == 2){
					ChartTool2->Active = false;
					double Integral = 0;
					double ySeries1 = 0;
					double ySeries2 = 0;
					double xvalue;
					double yvalue;
					double intecept;
					double x1 = X1AdvEdit->Text.ToDouble();
					double x2 = floor(ChartChart->BottomAxis->CalcPosPoint(X) * 1000 + 0.5) / 1000;
					ChartTool2->Active = true;
					ChartTool2->XValue = x2;
					X2AdvEdit->Text = FloatToStr(x2);
					ChartTool3->Lines->Clear();
					ChartTool3->Lines->AddLine(x1,y_bound,x2,y_bound);
//					mainForm->LogToFile("line drowed");
					int x1_Res = (abs(x1-ChartTool1->Series->XValues->Value[0]) / abs(mainForm->myTcpThread->FsRange_z)) * mainForm->myForceForm->FinalResolution;
					int x2_Res = (abs(x2-ChartTool1->Series->XValues->Value[0]) / abs(mainForm->myTcpThread->FsRange_z)) * mainForm->myForceForm->FinalResolution;
					mainForm->LogToFile("x1_Res = " + IntToStr(x1_Res) + " ,x2_Res = " + IntToStr(x2_Res));
					//					mainForm->LogToFile("x1_Res = " + IntToStr(x1_Res));
//					mainForm->LogToFile("x2_Res = " + IntToStr(x2_Res));
//					mainForm->LogToFile("FinalResolution = " + IntToStr(mainForm->myForceForm->FinalResolution));
					if(x2_Res < x1_Res){
						int x3 = x1_Res;
						x1_Res = x2_Res;
						x2_Res = x3;
					}
//					mainForm->LogToFile("y_bound = " + FloatToStr(y_bound));
					for(int i = x1_Res; i < x2_Res; i++){
						ySeries1 = ChartTool1->Series->YValues->Value[i];
						ySeries2 = ChartTool1->Series->YValues->Value[i+1];
//						mainForm->LogToFile("ySeries1 " + IntToStr(i) + " = " + FloatToStr(ySeries1));
//						mainForm->LogToFile("ySeries2 " + IntToStr(i+1) + " = " + FloatToStr(ySeries2));
						Integral = Integral + (abs((ySeries1 - y_bound) + (ySeries2 - y_bound)))/2;
//						mainForm->LogToFile("Integral = " + FloatToStr(Integral));
					}
//                    Integral = Integral * mainForm->myTcpThread->FsRange_z * 1000 / mainForm->myForceForm->FinalResolution;
					Integral = floor(Integral * abs(mainForm->myTcpThread->FsRange_z) * 1000 / mainForm->myForceForm->FinalResolution  + 0.5)/(double)1000;
					dYdXAdvEdit->Text = FloatToStr(Integral);
					FirstPoint = 3;
				}

			}
		}
	}
}

//---------------------------------------------------------------------------

void __fastcall TForceChartForm::RadioButtonUnitZClick(TObject *Sender)
{
	mainForm->LogToFile("TForceChartForm::RadioButtonUnitZClick");
	PickSeries(ChartPicker->ItemIndex+1);
}
//---------------------------------------------------------------------------

void __fastcall TForceChartForm::RadioButtonUnitTimeClick(TObject *Sender)
{
	mainForm->LogToFile("TForceChartForm::RadioButtonUnitTimeClick");
	PickSeries(ChartPicker->ItemIndex+1);
}
//---------------------------------------------------------------------------

void __fastcall TForceChartForm::ChartChartClickBackground(TCustomChart *Sender, TMouseButton Button,
		  TShiftState Shift, int X, int Y)
{
	if(Button == mbLeft){
		mainForm->LogToFile("TForceChartForm::ChartChartClickBackground , FirstPoint = " + IntToStr(FirstPoint));
		if(SameSeries && RadioButtonUnitZ->Checked){
			if(SlopeRadioButton->Checked){
				ChartTool1->Style = 2;
				ChartTool2->Style = 2;
				if(FirstPoint == 0){
					ChartTool3->Lines->Clear();
					ChartTool2->Active = false;
					ChartTool1->Active = true;

					double xvalue;
					double yvalue;
					double intecept;
					SeriesValueLine(X,Y,&xvalue,&yvalue,&intecept,ChartTool1);
					double x1 = floor(ChartTool1->XValue * 1000 + 0.5) / 1000;
					double y1 = floor(ChartTool1->YValue * 1000 + 0.5) / 1000;

					X1AdvEdit->Text = FloatToStr(x1);
					Y1AdvEdit->Text = FloatToStr(y1);
					FirstPoint = 1;
				}
				else if(FirstPoint == 1){
					double xvalue;
					double yvalue;
					double intecept;
					double x1 = X1AdvEdit->Text.ToDouble();
					double y1 = Y1AdvEdit->Text.ToDouble();
					ChartTool2->Active = true;
					SeriesValueLine(X,Y,&xvalue,&yvalue,&intecept,ChartTool2);
					double x2 = floor(ChartTool2->XValue * 1000 + 0.5) / 1000;
					double y2 = floor(ChartTool2->YValue * 1000 + 0.5) / 1000;
					X2AdvEdit->Text = FloatToStr(x2);
					Y2AdvEdit->Text = FloatToStr(y2);

//					double d = floor(((y2 - y1) / (x2 - x1)) * 1000 + 0.5) / (double)1000;
//
//					dYdXAdvEdit->Text = FloatToStr(d);
//
//					ChartTool3->ToPoint = TPoint(ChartTool2->XValue, ChartTool1->YValue);
//
					ChartTool3->Lines->AddLine(x1,y1,x2,y2);
					double d = floor(((y2 - y1) / (x2 - x1)) * 1000 + 0.5) / (double)1000;
					dYdXAdvEdit->Text = FloatToStr(d);
					if(ChartPicker->ItemIndex == 2 || ChartPicker->ItemIndex == 3){
						dYdXAdvEdit->Color = clSilver;
                    }
					FirstPoint = 3;
				}
			}
			else{
				ChartTool1->Style = 1;
				ChartTool2->Style = 1;
				if(FirstPoint == 0){
					ChartTool2->Active = false;
					ChartTool1->Active = false;
					ChartTool4->Active = false;
					ChartTool3->Lines->Clear();
					y_bound = floor(ChartChart->LeftAxis->CalcPosPoint(Y) * 1000 + 0.5) / (double) 1000;
					Y1AdvEdit->Text = FloatToStr(y_bound);
                    Y1AdvEdit->Color = clSilver;
					ChartTool3->Lines->AddLine(ChartChart->BottomAxis->Minimum,y_bound,ChartChart->BottomAxis->Maximum,y_bound);
					X2AdvEdit->Text = "";
					dYdXAdvEdit->Text = "";

				}
				else if(FirstPoint == 1){
					ChartTool2->Active = false;
					ChartTool1->Active = false;
					double x1 = floor(ChartChart->BottomAxis->CalcPosPoint(X) * 1000 + 0.5) / (double) 1000;
					X1AdvEdit->Text = FloatToStr(x1);
					ChartTool1->Active = true;
					ChartTool1->XValue = x1;
					X2AdvEdit->Text = "";
					dYdXAdvEdit->Text = "";
					FirstPoint = 2;
				}
				else if(FirstPoint == 2){
					ChartTool2->Active = false;
					double Integral = 0;
					double ySeries1 = 0;
					double ySeries2 = 0;
					double xvalue;
					double yvalue;
					double intecept;
					double x1 = X1AdvEdit->Text.ToDouble();
					double x2 = floor(ChartChart->BottomAxis->CalcPosPoint(X) * 1000 + 0.5) / 1000;
					ChartTool2->Active = true;
					ChartTool2->XValue = x2;
					X2AdvEdit->Text = FloatToStr(x2);
					ChartTool3->Lines->Clear();
					ChartTool3->Lines->AddLine(x1,y_bound,x2,y_bound);
//					mainForm->LogToFile("Line drowed");
					int x1_Res = (abs(x1-ChartTool1->Series->XValues->Value[0]) / abs(mainForm->myTcpThread->FsRange_z)) * mainForm->myForceForm->FinalResolution;
					int x2_Res = (abs(x2-ChartTool1->Series->XValues->Value[0]) / abs(mainForm->myTcpThread->FsRange_z)) * mainForm->myForceForm->FinalResolution;
					mainForm->LogToFile("x1_Res = " + IntToStr(x1_Res));
					mainForm->LogToFile("x2_Res = " + IntToStr(x2_Res));
//					mainForm->LogToFile("FinalResolution = " + IntToStr(mainForm->myForceForm->FinalResolution));
					if(x2_Res < x1_Res){
						int x3 = x1_Res;
						x1_Res = x2_Res;
						x2_Res = x3;
					}
//					mainForm->LogToFile("y_bound = " + FloatToStr(y_bound));
					for(int i = x1_Res; i < x2_Res; i++){
						ySeries1 = ChartTool1->Series->YValues->Value[i];
						ySeries2 = ChartTool1->Series->YValues->Value[i+1];
						mainForm->LogToFile("ySeries1 " + IntToStr(i) + " = " + FloatToStr(ySeries1));
						mainForm->LogToFile("ySeries2 " + IntToStr(i+1) + " = " + FloatToStr(ySeries2));
						Integral = Integral + (abs((ySeries1 - y_bound) + (ySeries2 - y_bound)))/2;
						mainForm->LogToFile("Integral = " + FloatToStr(Integral));
					}
//                    Integral = Integral * mainForm->myTcpThread->FsRange_z * 1000 / mainForm->myForceForm->FinalResolution;
					Integral = floor(Integral * abs(mainForm->myTcpThread->FsRange_z) * 1000 / mainForm->myForceForm->FinalResolution  + 0.5)/(double)1000;
					dYdXAdvEdit->Text = FloatToStr(Integral);
					FirstPoint = 3;
				}
			}
		}
	}

	else if(Button == mbRight){
		ChartChart->Zoom->X0 = X;
		ChartChart->Zoom->Y0 = Y;
		ChartChart->Zoom->X1 = X;
		ChartChart->Zoom->Y1 = Y;
		ChartChart->Zoom->Active = true;
//		ChartChart->Zoom->Allow = true;

	}

}
//---------------------------------------------------------------------------

void TForceChartForm::SeriesValueLine(int x, int y,double* ValueX,double* ValueY,double *ValueIntercept,TCursorTool *charttools)
{
	mainForm->LogToFile("TForceChartForm::SeriesValueLine");
	*ValueX = ChartChart->BottomAxis->CalcPosPoint(x);
	*ValueY = ChartChart->LeftAxis->CalcPosPoint(y);
	*ValueIntercept = InterpolateSeries(*ValueX);

	charttools->XValue = *ValueX;
	charttools->YValue = *ValueIntercept;

}
//---------------------------------------------------------------------------

double TForceChartForm::InterpolateSeries(double XValue)
{
	mainForm->LogToFile("TForceChartForm::InterpolateSeries");
	int index;
	double dx,dy;
	double result;
	if(FirstPoint == 0){
		for(index = 1; index < ChartTool1->Series->Count(); index++){
			if(XValue < ChartTool1->Series->XValue[index])
				break;
			dx=ChartTool1->Series->XValue[index] - ChartTool1->Series->XValue[index-1];
			dy=ChartTool1->Series->YValue[index] - ChartTool1->Series->YValue[index-1];
			if(dx != 0){
				result = dy*(XValue - ChartTool1->Series->XValue[index-1])/dx + ChartTool1->Series->YValue[index-1];
			}
			else
				result = 0;
		}
	}
	else if(FirstPoint == 1) {
		for(index = 1; index < ChartTool2->Series->Count(); index++){
			if(XValue < ChartTool2->Series->XValue[index])
				break;
			dx=ChartTool2->Series->XValue[index] - ChartTool2->Series->XValue[index-1];
			dy=ChartTool2->Series->YValue[index] - ChartTool2->Series->YValue[index-1];
			if(dx != 0){
				result = dy*(XValue - ChartTool2->Series->XValue[index-1])/dx + ChartTool2->Series->YValue[index-1];
			}
			else
				result = 0;
		}
	}
	return result;
}

//---------------------------------------------------------------------------


void __fastcall TForceChartForm::ChartTool1SnapChange(TCursorTool *Sender, int x,
          int y, const double XValue, const double YValue, TChartSeries *Series, int ValueIndex)

{
//	mainForm->LogToFile("TForceChartForm::ChartTool1SnapChange");
	double xvalue;
	double yvalue;
	double intecept;
//	SeriesValueLine(X,Y,&xvalue,&yvalue,&intecept,ChartTool1);

	xvalue = floor(ChartTool1->XValue * 1000 + 0.5) / (double)1000;
	yvalue = floor(ChartTool1->YValue * 1000 + 0.5) / (double)1000;
	X1AdvEdit->Text = FloatToStr(xvalue);
	if(SlopeRadioButton->Checked){
		Y1AdvEdit->Text = FloatToStr(yvalue);
    }

	if(FirstPoint == 3 ){
		ChartTool3->Lines->Clear();
		if(SlopeRadioButton->Checked){
			double x1 = X1AdvEdit->Text.ToDouble();
			double y1 = Y1AdvEdit->Text.ToDouble();
			double x2 = X2AdvEdit->Text.ToDouble();
			double y2 = Y2AdvEdit->Text.ToDouble();
			ChartTool3->Lines->AddLine(x1,y1,x2,y2);
			double d = floor(((y2 - y1) / (x2 - x1)) * 1000 + 0.5) / (double)1000;
			dYdXAdvEdit->Text = FloatToStr(d);
			if(ChartPicker->ItemIndex == 2 || ChartPicker->ItemIndex == 3){
				dYdXAdvEdit->Color = clSilver;
			}
		}
		else{
			double Integral = 0;
			double ySeries1 = 0;
			double ySeries2 = 0;
			double x1 = X1AdvEdit->Text.ToDouble();
			double x2 = X2AdvEdit->Text.ToDouble();
			ChartTool3->Lines->AddLine(x1,y_bound,x2,y_bound);
//			ChartTool3->Lines->AddLine(x1,y_bound,x2,y_bound);
			int x1_Res = (abs(x1-ChartTool1->Series->XValues->Value[0]) / abs(mainForm->myTcpThread->FsRange_z)) * mainForm->myForceForm->FinalResolution;
			int x2_Res = (abs(x2-ChartTool1->Series->XValues->Value[0]) / abs(mainForm->myTcpThread->FsRange_z)) * mainForm->myForceForm->FinalResolution;
			if(x2_Res < x1_Res){
				int x3 = x1_Res;
				x1_Res = x2_Res;
				x2_Res = x3;
			}
			for(int i = x1_Res; i < x2_Res; i++){
				ySeries1 = ChartTool1->Series->YValues->Value[i];
				ySeries2 = ChartTool1->Series->YValues->Value[i+1];
				Integral = Integral + (abs((ySeries1 - y_bound) + (ySeries2 - y_bound)))/2;

			}

			Integral = floor(Integral * abs(mainForm->myTcpThread->FsRange_z) * 1000 / mainForm->myForceForm->FinalResolution  + 0.5)/(double)1000;
			dYdXAdvEdit->Text = FloatToStr(Integral);
		}


	}
}
//---------------------------------------------------------------------------

void __fastcall TForceChartForm::ChartTool2SnapChange(TCursorTool *Sender, int x,
          int y, const double XValue, const double YValue, TChartSeries *Series, int ValueIndex)

{
//    mainForm->LogToFile("TForceChartForm::ChartTool1SnapChange");
	double xvalue;
	double yvalue;
	double intecept;

	xvalue = floor(ChartTool2->XValue * 1000 + 0.5) / (double)1000;
	yvalue = floor(ChartTool2->YValue * 1000 + 0.5) / (double)1000;
	X2AdvEdit->Text = FloatToStr(xvalue);
	if(SlopeRadioButton->Checked){
		Y2AdvEdit->Text = FloatToStr(yvalue);
    }

	if(FirstPoint == 3 ){
		ChartTool3->Lines->Clear();
		if(SlopeRadioButton->Checked){
			double x1 = X1AdvEdit->Text.ToDouble();
			double y1 = Y1AdvEdit->Text.ToDouble();
			double x2 = X2AdvEdit->Text.ToDouble();
			double y2 = Y2AdvEdit->Text.ToDouble();
			ChartTool3->Lines->AddLine(x1,y1,x2,y2);
			double d = floor(((y2 - y1) / (x2 - x1)) * 1000 + 0.5) / (double)1000;
			dYdXAdvEdit->Text = FloatToStr(d);
			if(ChartPicker->ItemIndex == 2 || ChartPicker->ItemIndex == 3){
				dYdXAdvEdit->Color = clSilver;
			}
		}
		else{
			double Integral = 0;
			double ySeries1 = 0;
			double ySeries2 = 0;
			double x1 = X1AdvEdit->Text.ToDouble();
			double x2 = X2AdvEdit->Text.ToDouble();
            ChartTool3->Lines->AddLine(x1,y_bound,x2,y_bound);
			int x1_Res = (abs(x1-ChartTool1->Series->XValues->Value[0]) / abs(mainForm->myTcpThread->FsRange_z)) * mainForm->myForceForm->FinalResolution;
			int x2_Res = (abs(x2-ChartTool1->Series->XValues->Value[0]) / abs(mainForm->myTcpThread->FsRange_z)) * mainForm->myForceForm->FinalResolution;
			if(x2_Res < x1_Res){
				int x3 = x1_Res;
				x1_Res = x2_Res;
				x2_Res = x3;
			}
			for(int i = x1_Res; i < x2_Res; i++){
				ySeries1 = ChartTool1->Series->YValues->Value[i];
				ySeries2 = ChartTool1->Series->YValues->Value[i+1];
				Integral = Integral + (abs((ySeries1 - y_bound) + (ySeries2 - y_bound)))/2;

			}

			Integral = floor(Integral * abs(mainForm->myTcpThread->FsRange_z) * 1000 / mainForm->myForceForm->FinalResolution  + 0.5)/(double)1000;
			dYdXAdvEdit->Text = FloatToStr(Integral);
		}


	}
}
//---------------------------------------------------------------------------

void __fastcall TForceChartForm::dYdXAdvEditKeyPress(TObject *Sender, System::WideChar &Key)

{
	if(Key == VK_BACK){
		mainForm->LogToFile("TForceChartForm::dYdXAdvEditKeyPress : Key = VK_BACK");
		Key = 0;
		ChartTool3->Lines->Clear();
		ChartTool2->Active = false;
		ChartTool1->Active = false;
		FirstPoint = 0;

		X1AdvEdit->Text = "";
		Y1AdvEdit->Text = "";

		X2AdvEdit->Text = "";
		Y2AdvEdit->Text = "";

		dYdXAdvEdit->Text = "";
		if((ChartPicker->ItemIndex == 6 || ChartPicker->ItemIndex == 7) && C_Factor_Set){
			SetReset = false;
			CloseButton->Enabled = false;
			QuestionLabel->Text = "Reset conversion factor?";
			Panel7->Show();
		}
		else{
			FirstPoint = 0;
        }
	}
	else if(Key == VK_RETURN && FirstPoint == 3 ){
		mainForm->LogToFile("TForceChartForm::dYdXAdvEditKeyPress : Key = VK_RETURN");
        Key = 0;
		if(SameSeries && SlopeRadioButton->Checked){
//			double x1 = X1AdvEdit->Text.ToDouble();
//			double y1 = Y1AdvEdit->Text.ToDouble();
//			double x2 = X2AdvEdit->Text.ToDouble();
//			double y2 = Y2AdvEdit->Text.ToDouble();
//			double d = floor(((y2 - y1) / (x2 - x1)) * 1000 + 0.5) / (double)1000;
//			dYdXAdvEdit->Text = FloatToStr(d);
			Slope = dYdXAdvEdit->Text.ToDouble();

			ChartTool3->Lines->Clear();
			ChartTool2->Active = false;
			ChartTool1->Active = false;
			if(ChartPicker->ItemIndex == 6 || ChartPicker->ItemIndex == 7){
				SetReset = true;
				CloseButton->Enabled = false;
				QuestionLabel->Text = "Save new TB conversion factor ?";
				Panel7->Show();
			}
			else{
				FirstPoint = 0;
            }



		}
		else if(SameSeries && !SlopeRadioButton->Checked){

//			double Integral = 0;
//			double ySeries1 = 0;
//			double ySeries2 = 0;
//			double x1 = X1AdvEdit->Text.ToDouble();
//			double x2 = X2AdvEdit->Text.ToDouble();
//			int x1_Res = (x1 / mainForm->myTcpThread->FsRange_z) * mainForm->myForceForm->Resolution;
//			int x2_Res = (x2 / mainForm->myTcpThread->FsRange_z) * mainForm->myForceForm->Resolution;
//
//			if(x2_Res < x1_Res){
//				int x3 = x1_Res;
//				x1_Res = x2_Res;
//				x2_Res = x3;
//			}
//
//			for(int i = x1_Res; i < x2_Res; i++){
//				ySeries1 = ChartTool1->Series->YValues->Value[i];
//				ySeries2 = ChartTool2->Series->YValues->Value[i];
//				Integral = Integral + abs(ySeries1 - ySeries2);
//			}
//
//			Integral = floor(Integral * mainForm->myTcpThread->FsRange_z * 1000 / mainForm->myForceForm->Resolution  + 0.5)/(double)1000;
//			dYdXAdvEdit->Text = FloatToStr(Integral);
			ChartTool3->Lines->Clear();
            ChartTool2->Active = false;
			ChartTool1->Active = false;
			dYdXAdvEdit->Color = clWhite;
			FirstPoint = 0;

		}
		else{
        }
	}
}
//---------------------------------------------------------------------------

void __fastcall TForceChartForm::YesButtonClick(TObject *Sender)
{
	mainForm->LogToFile("TForceChartForm::YesButtonClick , SetReset = " + BoolToStr(SetReset,true));
	if(SetReset){
		double TB_C_Factor = K_Factor / Slope;
		mainForm->myForceForm->CFactorEdit->Text = FloatToStr(TB_C_Factor);
		mainForm->myForceForm->Fs_C_Factor = TB_C_Factor;
		dYdXAdvEdit->Color = clWhite;

		ForceTable.TB_C_Factor = TB_C_Factor;
		ForceTable.C_Factor_Set = true;
		mainForm->myDataBase->Execute(mainForm->myDataBase->myQuery->Update("FORCE_CONFIG"));

		C_Factor_Set = true;
		Panel8->Enabled = false;
		Panel7->Hide();
		CloseButton->Enabled = true;
		FirstPoint = 0;
	}
	else{
		dYdXAdvEdit->Color = clSilver;
        mainForm->myForceForm->CFactorEdit->Text = FloatToStr(1);

		ForceTable.TB_C_Factor = 1;
		ForceTable.C_Factor_Set = false;
		mainForm->myDataBase->Execute(mainForm->myDataBase->myQuery->Update("FORCE_CONFIG"));

		C_Factor_Set = false;
		Panel8->Enabled = true;
		Panel7->Hide();
		CloseButton->Enabled = true;
    }

}
//---------------------------------------------------------------------------

void __fastcall TForceChartForm::NoButtonClick(TObject *Sender)
{
	mainForm->LogToFile("TForceChartForm::NoButtonClick");
    Panel7->Hide();
	CloseButton->Enabled = true;
	if(SetReset)
		FirstPoint = 0;
}
//---------------------------------------------------------------------------

void __fastcall TForceChartForm::KAdvEditChange(TObject *Sender)
{
	KAdvEdit->Color = clSilver;
}
//---------------------------------------------------------------------------

void __fastcall TForceChartForm::KAdvEditKeyPress(TObject *Sender, System::WideChar &Key)

{
	if(Key == VK_RETURN){
		mainForm->LogToFile("TForceChartForm::KAdvEditKeyPress");
		K_Factor = KAdvEdit->Text.ToDouble();
		ForceTable.K_Factor = K_Factor;
		mainForm->myDataBase->Execute(mainForm->myDataBase->myQuery->Update("FORCE_CONFIG"));
		KAdvEdit->Color = clWhite;
	}

}
//---------------------------------------------------------------------------

 void TForceChartForm::PanelButtonShow(int series)
 {

	ChartTool2->Active = false;
	ChartTool1->Active = false;
	ChartTool4->Active = false;
    ChartTool3->Lines->Clear();


	X1AdvEdit->Text = "";
	Y1AdvEdit->Text = "";
	X2AdvEdit->Text = "";
	Y2AdvEdit->Text = "";
	dYdXAdvEdit->Text = "";

	X1AdvEdit->Color = clWhite;
	Y1AdvEdit->Color = clWhite;
	X2AdvEdit->Color = clWhite;
	Y2AdvEdit->Color = clWhite;
	dYdXAdvEdit->Color = clWhite;

	FirstPoint = 0;
	if((series == 1) || (series == 2) || (series == 3) || (series == 4)){
		Panel6->Visible = false;
        SlopeRadioButton->Visible = false;
		IntegralRadioButton->Visible = false;
	}
	else{
		Panel6->Visible = true;
		SlopeRadioButton->Visible = true;
		IntegralRadioButton->Visible = true;
		if(SlopeRadioButton->Checked){
            ChartTool3->Lines->Clear();
			Y1AdvEditLbl->Caption = "Y1";
			Panel1->Left = 0;
			Panel1->Top = 60;
			Panel2->Top = Panel1->Top + Panel1->Height + 10;
			Panel2->Left = Panel1->Left;
			Panel3->Top = Panel2->Top;
			Panel3->Left = Panel4->Left;
			Panel4->Top = Panel1->Top;
			dYdXAdvEditLbl->Caption = "Line Slope";
			Panel2->Visible = true;
			Panel3->Visible = true;
			if(series == 7 || series == 8){
				Panel5->Top = Panel4->Top;
				Panel8->Top = Panel3->Top;
				Panel8->Left = Panel5->Left ;
				Panel8->Visible = true;
			}
			else{
				Panel8->Visible = false;
				Panel5->Top = Panel2->Top - Panel5->Height/2;
			}


		}
		else{

			Panel2->Visible = true;
			Panel3->Visible = false;
			Panel8->Visible = false;
			Panel1->Left = Panel4->Left;
			Panel1->Top = 20;
			Panel4->Top = Panel1->Top + 40;
			Panel5->Top = Panel4->Top;
			Panel2->Top = Panel4->Top + 40;
			Panel2->Left = Panel1->Left;
			Y1AdvEditLbl->Caption = "Y";


			dYdXAdvEditLbl->Caption = "Integral(x1-x2)";
		}
	}


 }
//---------------------------------------------------------------------------

void __fastcall TForceChartForm::SlopeRadioButtonClick(TObject *Sender)
{
	mainForm->LogToFile("TForceChartForm::SlopeRadioButtonClick");
	PanelButtonShow(ChartPicker->ItemIndex+1);
}
//---------------------------------------------------------------------------

void __fastcall TForceChartForm::IntegralRadioButtonClick(TObject *Sender)
{
	mainForm->LogToFile("TForceChartForm::IntegralRadioButtonClick");
	PanelButtonShow(ChartPicker->ItemIndex+1);
}
//---------------------------------------------------------------------------


void __fastcall TForceChartForm::Y1AdvEditKeyPress(TObject *Sender, System::WideChar &Key)

{
	if(Key == VK_RETURN && FirstPoint == 0 && !SlopeRadioButton->Checked && Y1AdvEdit->Text.Length() > 0){
		mainForm->LogToFile("TForceChartForm::Y1AdvEditKeyPress");
        Y1AdvEdit->Color = clWhite;
		FirstPoint = 1;
	}
}
//---------------------------------------------------------------------------

void __fastcall TForceChartForm::InvertXButtonClick(TObject *Sender)
{
	mainForm->LogToFile("TForceChartForm::InvertXButtonClick");
	ChartChart->BottomAxis->Inverted = !ChartChart->BottomAxis->Inverted;
}
//---------------------------------------------------------------------------

void __fastcall TForceChartForm::InvertYButtonClick(TObject *Sender)
{
	mainForm->LogToFile("TForceChartForm::InvertYButtonClick");
	ChartChart->LeftAxis->Inverted = !ChartChart->LeftAxis->Inverted;
}
//---------------------------------------------------------------------------



