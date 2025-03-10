//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "ConfigFrm.h"
#include "mainUnit.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "AdvGlowButton"
#pragma link "AdvGlassButton"
#pragma link "CurvyControls"
#pragma link "AdvWiiProgressBar"
#pragma resource "*.dfm"
TConfigForm *ConfigForm;
//---------------------------------------------------------------------------
__fastcall TConfigForm::TConfigForm(TComponent* Owner)
	: TForm(Owner)
{
	first = false;
}
//---------------------------------------------------------------------------
void __fastcall TConfigForm::CloseButtonClick(TObject *Sender)
{
	if(SaveButton->Visible){
		CloseBtn = true;
		SaveBtn = false;
		QuestionLabel->Text = " Close Configs Without Saving? ";
		Panel7->Visible = true;
		ButtonsPnl->Enabled = false;
		CentralPanel->Enabled = false;
		menuPanel->Enabled = false;
	}
	else
        PrepareToExit();

}
//---------------------------------------------------------------------------

void TConfigForm::InitValues()
{
	mainForm->LogToFile("TConfigForm::InitValues");
	for (int i = 0; i < 13; i++) {
		myConfTable[i] = NULL;
	}


	ColumnNumber = 0;
	TableNumber = 2;
	SaveBtn = false;
	CloseBtn = false;
	EditBtn = false;

}
//---------------------------------------------------------------------------

void TConfigForm::CreatObjects()
{
	mainForm->LogToFile("TConfigForm::CreatObjects");
	for (int i = 0; i < 13; i++) {
		myConfTable[i] = new TConfTable(this);
		myConfTable[i]->Parent = CentralPanel;
		myConfTable[i]->SetParentComponent(CentralPanel);
		myConfTable[i]->Height = CentralPanel->Height;
		myConfTable[i]->Width = CentralPanel->Width;
	}
}
//---------------------------------------------------------------------------

void __fastcall TConfigForm::FormShow(TObject *Sender)
{
	mainForm->LogToFile("TConfigForm::FormShow");
	if(!first){
		InitValues();
		CreatObjects();
		CloseButton->Left = ButtonsPnl->Width - CloseButton->Width - 10 ;
		EditButton->Left = CloseButton->Left - EditButton->Width - 5;
		SaveButton->Left = EditButton->Left;


		Panel7->Left = this->Width/2 - Panel7->Width/2;
		Panel7->Top = this->Height/2 - Panel7->Height/2;

		Panel2->Left = this->Width/2 - Panel2->Width/2;
		Panel2->Top = this->Height/2 - Panel2->Height/2;
		CurvyEdit3->Text = "Please Enter Username And Password";
		first = true;
		TableNumber = 2;


	}

	PickList(TableNumber);

	if(!HaveLicense)
		LicenseButton->Visible = false;
	else
		LicenseButton->Visible = true;

	AdvWiiProgressBar->Visible =  false;
	if(mainForm->AppMode == 1 || mainForm->AppMode == 5 || mainForm->AppMode == 7){
        DncButton->Visible = false;
		ColibrationButton->Top = HardwareButton->Top + HardwareButton->Height + 5;
		InfoButton->Top = ColibrationButton->Top + ColibrationButton->Height + 5;
		LicenseButton->Top = InfoButton->Top + InfoButton->Height + 5;
	}
	else{
        DncButton->Top = HardwareButton->Top + HardwareButton->Height + 5;
		DncButton->Visible = true;
		ColibrationButton->Top = DncButton->Top + DncButton->Height + 5;
		InfoButton->Top = ColibrationButton->Top + ColibrationButton->Height + 5;
		LicenseButton->Top = InfoButton->Top + InfoButton->Height + 5;
	}
}

//---------------------------------------------------------------------------

void TConfigForm::PickList(int Table)
{
	switch(Table){
		case 0:
			LicenseButtonClick(NULL);
			break;
		case 1:
			InfoButtonClick(NULL);
			break;
		case 2:
			OscChartButtonClick(NULL);
			break;
		case 3:
			MoveButtonClick(NULL);
			break;
		case 4:
			StageButtonClick(NULL);
			break;
		case 5:
			RetractButtonClick(NULL);
			break;
		case 6:
			ApproachButtonClick(NULL);
			break;
		case 7:
			FastApproachButtonClick(NULL);
			break;
		case 8:
			ScanButtonClick(NULL);
			break;
		case 9:
			HardwareButtonClick(NULL);
			break;
		case 10:
			DncButtonClick(NULL);
			break;
		case 11:
			oscButtonClick(NULL);
			break;
		case 12:
			ColibrationButtonClick(NULL);
			break;
	}

}
//---------------------------------------------------------------------------

void __fastcall TConfigForm::LicenseButtonClick(TObject *Sender)
{
	mainForm->LogToFile("TConfigForm::LicenseButtonClick");
	LabelMonitor->Caption = "License";
	ColumnNumber = 3;
	myConfTable[TableNumber]->Hide();
	TableNumber = 0;
	myConfTable[TableNumber]->Show();

}
//---------------------------------------------------------------------------

void __fastcall TConfigForm::InfoButtonClick(TObject *Sender)
{
	mainForm->LogToFile("TConfigForm::InfoButtonClick");
	LabelMonitor->Caption = "Info";
	ColumnNumber = 2;
	myConfTable[TableNumber]->Hide();
	TableNumber = 1;
	myConfTable[TableNumber]->Show();
}
//---------------------------------------------------------------------------

void __fastcall TConfigForm::OscChartButtonClick(TObject *Sender)
{
	mainForm->LogToFile("TConfigForm::OscChartButtonClick");
	LabelMonitor->Caption = "Osc Chart";
	ColumnNumber = 1;
	myConfTable[TableNumber]->Hide();
	TableNumber = 2;
	myConfTable[TableNumber]->Show();
}
//---------------------------------------------------------------------------

void __fastcall TConfigForm::MoveButtonClick(TObject *Sender)
{
	mainForm->LogToFile("TConfigForm::MoveButtonClick");
	LabelMonitor->Caption = "Move";
	ColumnNumber = 3;
	myConfTable[TableNumber]->Hide();
	TableNumber = 3;
	myConfTable[TableNumber]->Show();
}
//---------------------------------------------------------------------------

void __fastcall TConfigForm::StageButtonClick(TObject *Sender)
{
	mainForm->LogToFile("TConfigForm::StageButtonClick");
	LabelMonitor->Caption = "Stage";
	ColumnNumber = 3;
	myConfTable[TableNumber]->Hide();
	TableNumber = 4;
	myConfTable[TableNumber]->Show();
}
//---------------------------------------------------------------------------

void __fastcall TConfigForm::RetractButtonClick(TObject *Sender)
{
	mainForm->LogToFile("TConfigForm::RetractButtonClick");
	LabelMonitor->Caption = "Retract";
	ColumnNumber = 3;
	myConfTable[TableNumber]->Hide();
	TableNumber = 5;
	myConfTable[TableNumber]->Show();
}
//---------------------------------------------------------------------------

void __fastcall TConfigForm::ApproachButtonClick(TObject *Sender)
{
	mainForm->LogToFile("TConfigForm::ApproachButtonClick");
	LabelMonitor->Caption = "Approach";
	ColumnNumber = 7;
	myConfTable[TableNumber]->Hide();
	TableNumber = 6;
	myConfTable[TableNumber]->Show();
}
//---------------------------------------------------------------------------

void __fastcall TConfigForm::FastApproachButtonClick(TObject *Sender)
{
	mainForm->LogToFile("TConfigForm::FastApproachButtonClick");
	LabelMonitor->Caption = "FastApproach";
	ColumnNumber = 7;
	myConfTable[TableNumber]->Hide();
	TableNumber = 7;
	myConfTable[TableNumber]->Show();
}
//---------------------------------------------------------------------------

void __fastcall TConfigForm::ScanButtonClick(TObject *Sender)
{
	mainForm->LogToFile("TConfigForm::ScanButtonClick");
	LabelMonitor->Caption = "Scan";
	ColumnNumber = 1;
	myConfTable[TableNumber]->Hide();
	TableNumber = 8;
	myConfTable[TableNumber]->Show();
}
//---------------------------------------------------------------------------

void __fastcall TConfigForm::HardwareButtonClick(TObject *Sender)
{
	mainForm->LogToFile("TConfigForm::HardwareButtonClick");
	LabelMonitor->Caption = "Hardware";
	ColumnNumber = 3;
	myConfTable[TableNumber]->Hide();
	TableNumber = 9;
	myConfTable[TableNumber]->Show();
}
//---------------------------------------------------------------------------

void __fastcall TConfigForm::DncButtonClick(TObject *Sender)
{
	mainForm->LogToFile("TConfigForm::DncButtonClick");
	LabelMonitor->Caption = "Dnc";
	ColumnNumber = 4;
	myConfTable[TableNumber]->Hide();
	TableNumber = 10;
	myConfTable[TableNumber]->Show();
}
//---------------------------------------------------------------------------

void __fastcall TConfigForm::oscButtonClick(TObject *Sender)
{
	mainForm->LogToFile("TConfigForm::oscButtonClick");
    LabelMonitor->Caption = "osc";
	ColumnNumber = 27;
	myConfTable[TableNumber]->Hide();
    TableNumber = 11;
	myConfTable[TableNumber]->Show();
}

//---------------------------------------------------------------------------

void __fastcall TConfigForm::ColibrationButtonClick(TObject *Sender)
{
	mainForm->LogToFile("TConfigForm::ColibrationButtonClick");
	LabelMonitor->Caption = "Calibration";
	ColumnNumber = 56;
	myConfTable[TableNumber]->Hide();
	TableNumber = 12;
	myConfTable[TableNumber]->Show();
}
//---------------------------------------------------------------------------



void __fastcall TConfigForm::SaveButtonClick(TObject *Sender)
{
	mainForm->LogToFile("TConfigForm::SaveButtonClick");
	SaveBtn = true;
    CloseBtn = false;
	QuestionLabel->Text = " Save New Configs ? ";
	Panel7->Visible = true;
    ButtonsPnl->Enabled = false;
	CentralPanel->Enabled = false;
	menuPanel->Enabled = false;
}
//---------------------------------------------------------------------------

void __fastcall TConfigForm::YesButtonClick(TObject *Sender)
{

	mainForm->LogToFile("TConfigForm::YesButtonClick : SaveBtn = " + BoolToStr(SaveBtn,true) + " , CloseBtn = " + BoolToStr(CloseBtn,true));
	if(SaveBtn){
		Panel7->Visible = false;
		AdvWiiProgressBar->Show();
		Label1->Visible = true;
//		AdvWiiProgressBar->Visible = true;
		for(int i = 0; i<13; i++){
			Application->ProcessMessages();
			switch(i){
				case 0:{
//					mainForm->LogToFile("TConfigForm::case 0");
//					for(int j = 0; j < 3; j++){
//						if(myConfTable[i]->myRows[j]){
//							if(j == 0){
//								LicTable.TotalTime = myConfTable[i]->myRows[j]->CurvyEdit1->Text.ToDouble();
//							}
//							else if(j == 1){
//								LicTable.WorkedTime = myConfTable[i]->myRows[j]->CurvyEdit1->Text.ToDouble();
//							}
//							else{
//								LicTable.RemainedTime = myConfTable[i]->myRows[j]->CurvyEdit1->Text.ToDouble();
//							}
//						}
//					}
//					mainForm->myDataBase->Execute(mainForm->myDataBase->myQuery->Update("LicenseTable"));
					break;
				}
				case 1:{
//					mainForm->LogToFile("TConfigForm::case 1");
					for(int j = 0; j < 2; j++){
						if(myConfTable[i]->myRows[j]){
							if(j == 0){
								InfoTable.url = myConfTable[i]->myRows[j]->CurvyEdit1->Text;
							}
							else {
								InfoTable.tel = myConfTable[i]->myRows[j]->CurvyEdit1->Text;
							}
						}
					}
					mainForm->myDataBase->Execute(mainForm->myDataBase->myQuery->Update("INFO_CONFIG"));
					break;
				}
				case 2:{
//					mainForm->LogToFile("TConfigForm::case 2");
					if(myConfTable[i]->myRows[0]){
						if(myConfTable[i]->myRows[0]->CurvyEdit1->Text == "False" || myConfTable[i]->myRows[0]->CurvyEdit1->Text == "0")
							OscChartTable.all_scale = false;
						else
							OscChartTable.all_scale = true;
					}
					mainForm->myDataBase->Execute(mainForm->myDataBase->myQuery->Update("OSC_CHART_CONFIG"));
					break;
				}
				case 3:{
//					mainForm->LogToFile("TConfigForm::case 3");
					for(int j = 0; j < 3; j++){
						if(myConfTable[i]->myRows[j]){
							if(j == 0){
								MoveTable.Coarse_StepperSpeed_Val_Slow = myConfTable[i]->myRows[j]->CurvyEdit1->Text.ToInt();
							}
							else if(j == 1){
								MoveTable.Coarse_StepperSpeed_Val_Fast = myConfTable[i]->myRows[j]->CurvyEdit1->Text.ToInt();
							}
							else{
								MoveTable.Coarse_StepperStepMicro_Val = myConfTable[i]->myRows[j]->CurvyEdit1->Text.ToInt();
							}
						}
					}
					mainForm->myDataBase->Execute(mainForm->myDataBase->myQuery->Update("COARSEMOVE_CONFIG"));
					break;
				}
				case 4:{
//					mainForm->LogToFile("TConfigForm::case 4");
					for(int j = 0; j < 3; j++){
						if(myConfTable[i]->myRows[j]){
							if(j == 0){
								StageTable.Stage_StepperSpeed_Val_Slow = myConfTable[i]->myRows[j]->CurvyEdit1->Text.ToInt();
							}
							else if(j == 1){
								StageTable.Stage_StepperSpeed_Val_Fast = myConfTable[i]->myRows[j]->CurvyEdit1->Text.ToInt();
							}
							else{
								StageTable.Stage_StepperStepMicro_Val = myConfTable[i]->myRows[j]->CurvyEdit1->Text.ToInt();
							}
						}
					}
					mainForm->myDataBase->Execute(mainForm->myDataBase->myQuery->Update("STAGE_CONFIG"));
					break;
				}
				case 5:{
//					mainForm->LogToFile("TConfigForm::case 5");
					for(int j = 0; j < 3; j++){
						if(myConfTable[i]->myRows[j]){
							if(j == 0){
								RetractTable.Ret_OneStep_Val = myConfTable[i]->myRows[j]->CurvyEdit1->Text.ToInt();
							}
							else if(j == 1){
								RetractTable.Ret_StepperSpeed_Val = myConfTable[i]->myRows[j]->CurvyEdit1->Text.ToInt();
							}
							else{
								RetractTable.Ret_StepperStepMicro_Val = myConfTable[i]->myRows[j]->CurvyEdit1->Text.ToInt();
							}
						}
					}
					mainForm->myDataBase->Execute(mainForm->myDataBase->myQuery->Update("RETRACT_CONFIG"));
					break;
				}
				case 6:{
//					mainForm->LogToFile("TConfigForm::case 6");
					for(int j = 0; j < 6; j++){
						if(myConfTable[i]->myRows[j]){
							if(j == 0){
								ApproachTable.Apr_SteperSpeed_Val_Precise = myConfTable[i]->myRows[j]->CurvyEdit1->Text.ToInt();
							}
							else if(j == 1){
								ApproachTable.Apr_SteperStepMicro_Val_Precise = myConfTable[i]->myRows[j]->CurvyEdit1->Text.ToInt();
							}
							else if(j == 2){
								ApproachTable.Apr_StepperSpeed_Val_Fast = myConfTable[i]->myRows[j]->CurvyEdit1->Text.ToInt();
							}
							else if(j == 3){
								ApproachTable.Apr_StepperStepMicro_Val_Fast = myConfTable[i]->myRows[j]->CurvyEdit1->Text.ToInt();
							}
							else if(j == 4){
								ApproachTable.Apr_StepperStep_Val = myConfTable[i]->myRows[j]->CurvyEdit1->Text.ToInt();
							}
							else if(j == 5){
								ApproachTable.Apr_BiasIndex_Val = myConfTable[i]->myRows[j]->CurvyEdit1->Text.ToInt();
							}
							else{
								ApproachTable.Apr_BiasOffset_Val = myConfTable[i]->myRows[j]->CurvyEdit1->Text.ToInt();
							}
						}
					}
					mainForm->myDataBase->Execute(mainForm->myDataBase->myQuery->Update("APPROACH_CONFIG"));
					break;
				}
				case 7:{
//					mainForm->LogToFile("TConfigForm::case 7");
					for(int j = 0; j < 6; j++){
						if(myConfTable[i]->myRows[j]){
							if(j == 0){
								FastApproachTable.Dnc_FrequencyFrom_Val = myConfTable[i]->myRows[j]->CurvyEdit1->Text.ToInt();
							}
							else if(j == 1){
								FastApproachTable.Dnc_FrequencyTo_Val = myConfTable[i]->myRows[j]->CurvyEdit1->Text.ToInt();
							}
							else if(j == 2){
								FastApproachTable.Threshold_Contact = myConfTable[i]->myRows[j]->CurvyEdit1->Text.ToInt();
							}
							else if(j == 3){
								FastApproachTable.Threshold_NonContact = myConfTable[i]->myRows[j]->CurvyEdit1->Text.ToInt();
							}
							else if(j == 4){
								FastApproachTable.Min_Amp = myConfTable[i]->myRows[j]->CurvyEdit1->Text.ToInt();
							}
							else if(j == 5){
								FastApproachTable.Max_Amp = myConfTable[i]->myRows[j]->CurvyEdit1->Text.ToInt();
							}
							else{
								FastApproachTable.Drive_Start = myConfTable[i]->myRows[j]->CurvyEdit1->Text.ToInt();
							}
						}
					}
					mainForm->myDataBase->Execute(mainForm->myDataBase->myQuery->Update("FAST_APPROACH_DNC_CONFIG"));
					break;
				}
				case 8:{
//					mainForm->LogToFile("TConfigForm::case 8");
					if(myConfTable[i]->myRows[0]){
						ScanTable.Scan_OverScan_Val = myConfTable[i]->myRows[0]->CurvyEdit1->Text.ToDouble();
					}
					mainForm->myDataBase->Execute(mainForm->myDataBase->myQuery->Update("SCAN_CONFIG"));
					break;
				}
				case 9:{
//					mainForm->LogToFile("TConfigForm::case 9");
					for(int j = 0; j < 3; j++){
						if(myConfTable[i]->myRows[j]){
							if(j == 0){
								HardwareTable.HardWare_Scanner_Type = myConfTable[i]->myRows[j]->CurvyEdit1->Text.ToInt();
							}
							else if(j == 1){
								HardwareTable.Max_Range = myConfTable[i]->myRows[j]->CurvyEdit1->Text.ToDouble();
							}
							else{
								if(myConfTable[i]->myRows[j]->CurvyEdit1->Text == "False" || myConfTable[i]->myRows[j]->CurvyEdit1->Text == "0")
									HardwareTable.LogToFile = false;
								else
									HardwareTable.LogToFile = true;
							}
						}
					}
					mainForm->myDataBase->Execute(mainForm->myDataBase->myQuery->Update("HARDWARE_TYPE"));
					break;
				}
				case 10:{
//					mainForm->LogToFile("TConfigForm::case 10");
					for(int j = 0; j < 4; j++){
						if(myConfTable[i]->myRows[j]){
							if(j == 0){
								DncTable.Dnc_FrequencyFromMin_Val = myConfTable[i]->myRows[j]->CurvyEdit1->Text.ToInt();
							}
							else if(j == 1){
								DncTable.Dnc_FrequencyToMax_Val = myConfTable[i]->myRows[j]->CurvyEdit1->Text.ToInt();
							}
							else if(j == 2){
								DncTable.Dnc_DriveIndex_Val = myConfTable[i]->myRows[j]->CurvyEdit1->Text.ToDouble();
							}
							else{
								DncTable.Dnc_DriveOffset_Val = myConfTable[i]->myRows[j]->CurvyEdit1->Text.ToDouble();
							}
						}
					}
					mainForm->myDataBase->Execute(mainForm->myDataBase->myQuery->Update("DNC_CONFIG"));
					break;
				}
				case 11:{
					mainForm->LogToFile("TConfigForm::case 11");
					for(int j = 0; j < 27; j++){
						if(myConfTable[i]->myOscConfigFrm[j]){
							OscTable[j].name = myConfTable[i]->myOscConfigFrm[j]->CurvyEdit1->Text;
							OscTable[j].index = myConfTable[i]->myOscConfigFrm[j]->CurvyEdit2->Text.ToDouble();
							OscTable[j].offset = myConfTable[i]->myOscConfigFrm[j]->CurvyEdit3->Text.ToDouble();
							OscTable[j].unit = myConfTable[i]->myOscConfigFrm[j]->CurvyEdit4->Text;
							OscTable[j].scale = myConfTable[i]->myOscConfigFrm[j]->CurvyEdit5->Text.ToInt();
						}
						mainForm->myDataBase->Execute(mainForm->myDataBase->myQuery->Update("OSC_CONFIG" , j));
					}
					break;
				}
				case 12:{
//					mainForm->LogToFile("TConfigForm::case 12");
					for(int j = 0; j < 56; j++){
						if(myConfTable[i]->myColibration[j]){
							ColibrationTable[j].X_Range = myConfTable[i]->myColibration[j]->CurvyEdit1->Text.ToDouble();
							ColibrationTable[j].Y_Range = myConfTable[i]->myColibration[j]->CurvyEdit2->Text.ToDouble();
						}
						mainForm->myDataBase->Execute(mainForm->myDataBase->myQuery->Update("Calibration" , j));
					}
					break;
				}
			}
		}

		ReConfigProgram();
		PrepareToExit();

	}
	else if(CloseBtn){
		PrepareToExit();
	}

}
//---------------------------------------------------------------------------

void TConfigForm::ReConfigProgram(){

	mainForm->LogToFile("TConfigForm::ReConfigProgram");
	Application->ProcessMessages();
	mainForm->Confige();
	Application->ProcessMessages();
	mainForm->myOscForm->config_DataSet_INI();
	Application->ProcessMessages();
	for(int i=0; i<mainForm->myOscForm->i_ChartCount; i++)
		mainForm->myOscForm->createComboUnit(mainForm->myOscForm->my_plot_set[i].int_WaveIndex,mainForm->myOscForm->my_plot_set[i].combo_unit);
	mainForm->myPiezoFrom->all_scale = OscChartTable.all_scale;
	Application->ProcessMessages();
	mainForm->myTcpThread->ConfigCalss();
	Application->ProcessMessages();
	mainForm->myUdpThread->ConfigThread();
	Application->ProcessMessages();
	mainForm->myUdpThread->DataBaseSaveBuffInit();
	Application->ProcessMessages();
	mainForm->myCommandCreatorThread->myApproach->ConfigClass();
	Application->ProcessMessages();
	mainForm->myCommandCreatorThread->myDnc->GetDataFromIni();
	Application->ProcessMessages();
	mainForm->myApproachPanelForm->GetIniToUi();
	Application->ProcessMessages();
	mainForm->myDynamicCurvePanelForm->Config();
	Application->ProcessMessages();
	mainForm->myForceForm->ConfigClass();
	Application->ProcessMessages();
	mainForm->myKpfmFrm->GetIniKpfmForm();
	Application->ProcessMessages();
	mainForm->myLithoFrm->LithoConfigFrm->ConfigClass();
	Application->ProcessMessages();
	mainForm->myScanPanelForm->GetIniToUi();
	Application->ProcessMessages();
}
//---------------------------------------------------------------------------

void TConfigForm::PrepareToExit()
{
	mainForm->LogToFile("TConfigForm::PrepareToExit");
	Panel7->Visible = false;
    Panel2->Visible = false;
	EditBtn = false;
	CloseBtn = false;
	SaveBtn = false;
	ButtonsPnl->Enabled = true;
	CentralPanel->Enabled = true;
	menuPanel->Enabled = true;
	SaveButton->Visible = false;

	for(int j = 0; j<13; j++){
		for(int i = 0; i<56; i++){
			if(myConfTable[j]->myColibration[i])
				myConfTable[j]->myColibration[i]->Enabled = false;
		}
		for(int i = 0; i<27; i++){
			if(myConfTable[j]->myOscConfigFrm[i])
				myConfTable[j]->myOscConfigFrm[i]->Enabled = false;
		}
		for(int i = 0; i<7; i++){
			if(myConfTable[j]->myRows[i])
				myConfTable[j]->myRows[i]->Enabled = false;
		}
		myConfTable[j]->Showing = false;
	}


	CurvyEdit2->Text = "";
	Label1->Visible = false;
	AdvWiiProgressBar->Hide();
    EditButton->Visible = true;
	this->Hide();
	mainForm->Enabled = true;
	mainForm->myVideoForm->VideoGrabber1->StartPreview();
	if(mainForm->mySettingForm->Osc_PreviousState)
		mainForm->myOscForm->p1PauseClick(NULL);
	mainForm->myVideoForm->BringToFront();

}
//---------------------------------------------------------------------------

void __fastcall TConfigForm::Cancel(TObject *Sender)
{
	mainForm->LogToFile("TConfigForm::Cancel");
	SaveBtn = false;
	CloseBtn = false;
	EditBtn = false;
	Panel7->Visible = false;
	Panel2->Visible = false;
	ButtonsPnl->Enabled = true;
	CentralPanel->Enabled = true;
	menuPanel->Enabled = true;
}
//---------------------------------------------------------------------------

void __fastcall TConfigForm::EditButtonClick(TObject *Sender)
{
	mainForm->LogToFile("TConfigForm::EditButtonClick");
	if(!EditBtn){
		EditBtn = true;
		ButtonsPnl->Enabled = false;
		CentralPanel->Enabled = false;
		menuPanel->Enabled = false;
		Panel2->Visible = true;
	}
}
//---------------------------------------------------------------------------

void __fastcall TConfigForm::Button1Click(TObject *Sender)
{
	mainForm->LogToFile("TConfigForm::Button1Click");
	if(CurvyEdit1->Text == "Brisk" && CurvyEdit2->Text == DBPassWord){
		for(int j = 0; j<13; j++){
			for(int i = 0; i<56; i++){
				if(myConfTable[j]->myColibration[i])
					myConfTable[j]->myColibration[i]->Enabled = true;
			}
			for(int i = 0; i<27; i++){
				if(myConfTable[j]->myOscConfigFrm[i])
					myConfTable[j]->myOscConfigFrm[i]->Enabled = true;
			}
			for(int i = 0; i<7; i++){
				if(myConfTable[j]->myRows[i])
					myConfTable[j]->myRows[i]->Enabled = true;
			}
		}
		Panel2->Visible = false;
		CurvyEdit3->Text = "Please Enter Username And Password";
        ButtonsPnl->Enabled = true;
		CentralPanel->Enabled = true;
		menuPanel->Enabled = true;
		SaveButton->Visible = true;
		EditButton->Visible = false;
	}
	else{
		CurvyEdit3->Text = "Wrong Username Or Password";
	}
}
//---------------------------------------------------------------------------

void __fastcall TConfigForm::Button2Click(TObject *Sender)
{
	mainForm->LogToFile("TConfigForm::Button2Click");
   Panel2->Visible = false;
   EditBtn = false;
   CurvyEdit3->Text = "Please Enter Username And Password";
   ButtonsPnl->Enabled = true;
   CentralPanel->Enabled = true;
   menuPanel->Enabled = true;
}
//---------------------------------------------------------------------------


void __fastcall TConfigForm::CurvyEdit2KeyPress(TObject *Sender, System::WideChar &Key)

{
	mainForm->LogToFile("TConfigForm::CurvyEdit2KeyPress");
	if(Key == VK_RETURN)
		Button1Click(NULL);
}
//---------------------------------------------------------------------------


