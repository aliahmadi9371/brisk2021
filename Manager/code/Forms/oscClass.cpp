///---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "oscClass.h"
#include "globals.h"
#include "defines.h"
#include "mainUnit.h"
#include <Vcl.StdCtrls.hpp>
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "AdvGlassButton"
#pragma link "advmultibuttonedit"
#pragma link "AdvUpDownEdit"
#pragma link "AdvEdit"
#pragma link "CalcEdit"
#pragma link "AdvBadge"
#pragma link "VCLTee.TeeTools"
#pragma link "VCLTee.TeeComma"
#pragma link "AdvCombo"
#pragma link "AdvCircularProgress"
#pragma link "AdvGlowButton"
#pragma link "VCLTee.TeeEdit"
#pragma link "AdvLabel"
#pragma link "AdvShape"
#pragma link "AdvTrackBar"
#pragma link "CurvyControls"
#pragma resource "*.dfm"
#include "LitoFileCreatorUnit.h"
ToscForm *oscForm;
//---------------------------------------------------------------------------
__fastcall ToscForm::ToscForm(TComponent* Owner)
	: TForm(Owner)
{
	plotDnc = false;
	PiezoCounter = 0;
	firstSave = false;
}
//---------------------------------------------------------------------------

__fastcall ToscForm::~ToscForm()
{
//	if(mainForm->myUdpThread->connected_udp){
//		mainForm->myUdpThread->PowerOff();
//		b_pc_on = true;
//	}
}
//---------------------------------------------------------------------------

void __fastcall ToscForm::FormCreate(TObject *Sender)
{
	this->Hide();
	Init();
	LoadPictures();
	InitOthers();
}
//---------------------------------------------------------------------------

void ToscForm::Init()
{
    activated = false;
	bPlotInit = false;
	first = false;
	labelCounter = 0;
	TimePlot = 0;
	firstPlot = 0;
	counter = 0;
	z = 0;
	OffState = 0;

    ErrorPercent = 5;

	oscChart1->Title->Clear();
	oscChart2->Title->Clear();
	oscChart3->Title->Clear();
	oscChart4->Title->Clear();

	firstPlotfirst = false;

	enabled_playpause = false;

	in_rec_panel = false;
    FlyError = false;


	I = 0;

	PanelAddSub->Enabled = true;
	PanelPlayPuase->Enabled = true;
	PanelTimeDev->Enabled = true;
	PanelRecord->Enabled = true;

	ComboBox1->Enabled = true;
	enabled_playpause = true;


	config_DataSet_INI();
	SetChartStruct();

	pOffBut->Width = 0;
	pOffBut->Height = 0;
	pOffBut->Left = 0;
	pOffBut->Top = 0;

	pOffBut->Visible = false;
}

void ToscForm::LoadPictures()
{

	PausePic = new TGDIPPicture;
	PausePic->LoadFromFile("Resources/Images/OSC_Form/pause.png");

	PausePicHover = new TGDIPPicture;
	PausePicHover->LoadFromFile("Resources/Images/OSC_Form/pause_hover.png");

	RecPic = new TGDIPPicture;
	RecPic->LoadFromFile("Resources/Images/OSC_Form/record.png");

	RecPicHover = new TGDIPPicture;
	RecPicHover->LoadFromFile("Resources/Images/OSC_Form/record_hover.png");

}
//---------------------------------------------------------------------------

void ToscForm::config_DataSet_INI()
{


	for(int i=0; i<27; i++){
		if(AllScale || (i != 3 && i != 4 && i != 5 && i != 26)){
			my_data_set[i].data_name = OscTable[i].name;
			my_data_set[i].data_unit = OscTable[i].unit;
			my_data_set[i].data_index = OscTable[i].index;
			my_data_set[i].data_offset = OscTable[i].offset;
			my_data_set[i].data_scale = OscTable[i].scale;
			if(my_data_set[i].data_scale > 4)
				my_data_set[i].data_scale = 4;
		}
		else{
			my_data_set[i].data_name = OscTable[i].name;
			my_data_set[i].data_unit = "";
			my_data_set[i].data_index = 1;
			my_data_set[i].data_offset = 0;
			my_data_set[i].data_scale = 0;
		}
	}
	rec_time = UdpTable.record_time;


}
//---------------------------------------------------------------------------

void ToscForm::SetChartStruct()
{
	for(int i=0; i<4; i++){
		NULLDesignElements(i);

		SetDesignElements(i);

		SetChartStructValues(i);

		SetChartStructDesign(i);
	}

}
//---------------------------------------------------------------------------

void ToscForm::NULLDesignElements(int plot_number)
{
	my_plot_set[plot_number].main_Panel = NULL;
	my_plot_set[plot_number].panel_Setting = NULL;
	my_plot_set[plot_number].combo_WaveName = NULL;
	my_plot_set[plot_number].commander = NULL;
	my_plot_set[plot_number].combo_unit = NULL;
//	my_plot_set[plot_number].advedit_PanelNumber = NULL;
	my_plot_set[plot_number].calclabel_AvgValue = NULL;
	my_plot_set[plot_number].calclabel_ChgValue = NULL;
	my_plot_set[plot_number].timer_Chart = NULL;
	my_plot_set[plot_number].fastlineseries_Series = NULL;
	my_plot_set[plot_number].charttool_Cursor = NULL;
	my_plot_set[plot_number].chart_Chart = NULL;
	my_plot_set[plot_number].Counter = 0;

	myUdpDataSendClass = NULL;
}
//---------------------------------------------------------------------------

void ToscForm::SetDesignElements(int plot_number)
{
	my_plot_set[plot_number].main_Panel = (TPanel *)FindComponent("PanelChart" + IntToStr(plot_number+1));
	my_plot_set[plot_number].panel_Setting = (TPanel *)FindComponent("p"+IntToStr(plot_number+1)+"Panel");
	my_plot_set[plot_number].combo_WaveName = (TCurvyCombo *)FindComponent("p"+IntToStr(plot_number+1)+"ComboBox");
	my_plot_set[plot_number].commander = (TTeeCommander *)FindComponent("TeeCommander"+IntToStr(plot_number+1));
	my_plot_set[plot_number].combo_unit = (TComboBox *)FindComponent("ComboBox_Unit"+IntToStr(plot_number+1));
//	my_plot_set[plot_number].advedit_PanelNumber = (TAdvEdit *)FindComponent("AdvEdit"+IntToStr(plot_number+1));
//	my_plot_set[plot_number].calclabel_AvgValue = (TAdvEdit *)FindComponent("edtAvg"+IntToStr(plot_number+1));
//	my_plot_set[plot_number].calclabel_ChgValue = (TAdvEdit *)FindComponent("edtChg"+IntToStr(plot_number+1));
//	my_plot_set[plot_number].timer_Chart = (TTimer *)FindComponent("plotTimer");
	my_plot_set[plot_number].fastlineseries_Series = (TFastLineSeries *)FindComponent("Series" + IntToStr(plot_number+1));
	my_plot_set[plot_number].charttool_Cursor = (TCursorTool *)FindComponent("ChartTool" + IntToStr(plot_number+1));
	my_plot_set[plot_number].chart_Chart = (TChart *)FindComponent("oscChart" + IntToStr(plot_number+1));

	my_plot_set[plot_number].calclabel_AvgValue = (TCurvyEdit *)FindComponent("Avg"+IntToStr(plot_number+1));
	my_plot_set[plot_number].calclabel_ChgValue = (TCurvyEdit *)FindComponent("Chg"+IntToStr(plot_number+1));

	myUdpDataSendClass = new UdpDataSendClass(NULL);
}
//---------------------------------------------------------------------------

void ToscForm::SetChartStructValues(int plot_number)
{
	my_plot_set[plot_number].bool_PlotActive = false;
	my_plot_set[plot_number].int_WaveIndex = -1;
	my_plot_set[plot_number].bool_PlotPlay = true;
	my_plot_set[plot_number].bool_Created = false;
	my_plot_set[plot_number].bool_FirstStep = false;
	my_plot_set[plot_number].int_WaveIndex = -1;
	my_plot_set[plot_number].int_X = 0;
	my_plot_set[plot_number].double_Avg = 0;
	my_plot_set[plot_number].double_Chg = 0;
	my_plot_set[plot_number].double_Max = 0;
	my_plot_set[plot_number].double_Min = 0;
	my_plot_set[plot_number].double_Sum = 0;
}
//---------------------------------------------------------------------------

void ToscForm::SetChartStructDesign(int plot_number)
{
	SetEachChartShow(false,plot_number);
	SetChartForRealTime(plot_number);
	SetChartLable(plot_number);
	SetColor(plot_number);
}
//---------------------------------------------------------------------------

void ToscForm::SetEachChartShow(bool show, int plot_number)
{
	my_plot_set[plot_number].main_Panel->Visible = show;
//	my_plot_set[plot_number].chart_Chart->Visible = show;
//	my_plot_set[plot_number].chart_Chart->Title->Visible = show;
//	my_plot_set[plot_number].chart_Chart->LeftAxis->Automatic = show;
//	my_plot_set[plot_number].charttool_Cursor->Visible = show;
//	my_plot_set[plot_number].combo_WaveName->Visible = show;
	my_plot_set[plot_number].combo_unit->Visible = false;
//	my_plot_set[plot_number].advedit_PanelNumber->Visible = show;
//	my_plot_set[plot_number].calclabel_AvgValue->Visible = show;
//	my_plot_set[plot_number].calclabel_ChgValue->Visible = show;
}
//---------------------------------------------------------------------------

void ToscForm::SetChartForRealTime(int plot_number)
{
	my_plot_set[plot_number].chart_Chart->ClipPoints = false;
	my_plot_set[plot_number].chart_Chart->Title->Visible = false;
	my_plot_set[plot_number].chart_Chart->Legend->Visible = false;
	my_plot_set[plot_number].chart_Chart->LeftAxis->Automatic = true ;
	my_plot_set[plot_number].chart_Chart->LeftAxis->Axis->Width = 1;
	my_plot_set[plot_number].chart_Chart->LeftAxis->Axis->Color = clWhite;
	my_plot_set[plot_number].chart_Chart->BottomAxis->Axis->Width = 1;
	my_plot_set[plot_number].chart_Chart->BottomAxis->Axis->Color = clWhite;
	my_plot_set[plot_number].chart_Chart->BottomAxis->RoundFirstLabel = false;
	my_plot_set[plot_number].charttool_Cursor->FullRepaint = true;
	my_plot_set[plot_number].chart_Chart->View3D = false;
	my_plot_set[plot_number].chart_Chart->Canvas->ReferenceCanvas->Pen->OwnerCriticalSection = NULL;
	my_plot_set[plot_number].fastlineseries_Series->LinePen->OwnerCriticalSection = NULL;
	my_plot_set[plot_number].fastlineseries_Series->AutoRepaint = true;
	my_plot_set[plot_number].int_X = 0;
	my_plot_set[plot_number].fastlineseries_Series->XValues->Order = loNone;
	my_plot_set[plot_number].chart_Chart->Axes->FastCalc = true;
	my_plot_set[plot_number].chart_Chart->Color = TColor(loNone);
	my_plot_set[plot_number].chart_Chart->Hover->Visible = false;

//	my_plot_set[plot_number].calclabel_AvgValue->Enabled = false;
//	my_plot_set[plot_number].calclabel_ChgValue->Enabled = false;

//	my_plot_set[plot_number].calclabel_AvgValue->EditLabel->AlwaysEnable = false;
//	my_plot_set[plot_number].calclabel_ChgValue->EditLabel->AlwaysEnable = false;

//	my_plot_set[plot_number].calclabel_AvgValue->EditLabel->Enabled = false;
//	my_plot_set[plot_number].calclabel_ChgValue->EditLabel->Enabled = false;

//	my_plot_set[plot_number].calclabel_AvgValue->LabelAlwaysEnabled = true;
//	my_plot_set[plot_number].calclabel_ChgValue->LabelAlwaysEnabled = true;
}
//---------------------------------------------------------------------------

void ToscForm::SetChartLable(int plot_number)
{
//	my_plot_set[plot_number].advedit_ChartNumber->Left = 0;
//	my_plot_set[plot_number].advedit_ChartNumber->Height = 0;
}
//---------------------------------------------------------------------------

void ToscForm::SetColor(int plot_number)
{
//	my_plot_set[plot_number].combo_WaveName->Color = my_plot_set[plot_number].fastlineseries_Series->Color;
//	my_plot_set[plot_number].advedit_ChartNumber->Color = my_plot_set[plot_number].fastlineseries_Series->Color;
//	my_plot_set[plot_number].advedit_PanelNumber->Color = my_plot_set[plot_number].fastlineseries_Series->Color;
}
//---------------------------------------------------------------------------

void ToscForm::InitOthers()
{
//	p1Pause->Visible = false;
	AdvEdit5->Visible = true;

	recording = false;

//	AdvUpDownEdit1->MaxValue = 4;
//	AdvUpDownEdit1->MinValue = 1;

//	p1Pause->Visible = true;

	b_pc_on = false;

	i_ChartCount = 0;
	i_RealChartCount = 0;

	my_plot_set[0].chart_Chart->Tag = 0;

	ComboBox1->Position = 4;


	for(int i=0; i<4; i++){
		my_plot_set[i].commander->ButtonZoom->Hide();
		my_plot_set[i].commander->Button3D->Hide();
		my_plot_set[i].commander->ButtonDepth->Hide();
		my_plot_set[i].commander->ButtonEdit->Hide();
		my_plot_set[i].commander->ButtonMove->Hide();
		my_plot_set[i].commander->ButtonNormal->Hide();
		my_plot_set[i].commander->ButtonZoom->Hide();
		my_plot_set[i].commander->ButtonPrint->Hide();
		my_plot_set[i].commander->ButtonRotate->Hide();
		my_plot_set[i].commander->ButtonCopy->Hide();
		my_plot_set[i].commander->ButtonSave->Align = alLeft;
	}

	this->Visible = true;
}
//---------------------------------------------------------------------------

void ToscForm::RunChart(bool run)
{
	plotTimer->Enabled = run;
}
//---------------------------------------------------------------------------


void __fastcall ToscForm::pOffButClick(TObject *Sender)
{
	OffTimer->Enabled = false;
	mainForm->myApproachPanelForm->fast_checkbox->Checked = false;

	if(!SaveImages){
		if(DirectoryExists(LastImagesFolderPath,true)){
			TDirectory::Delete(LastImagesFolderPath,true);
		}
	}

	if(OffState == 0){
		ApplicationTable.App_LastMode_Val = mainForm->AppMode;
		mainForm->myDataBase->Execute(mainForm->myDataBase->myQuery->Update("APPLICATION_CONFIG"));


		mainForm->ext_pnl->Caption = "please wait for exit";
		mainForm->ext_pnl->ShowCaption = true;
		mainForm->ext_pnl->BringToFront();
		mainForm->ext_pnl->Show();
//
		//	stop scanning        //hanging  file
		if(mainForm->myUdpThread->ipwUDPPort->Active && mainForm->myUdpThread->connected_udp){
			mainForm->myScanPanelForm->X_Range = 5;
            mainForm->myScanPanelForm->Y_Range = 5;
			TThread::Synchronize(mainForm->myCommandCreatorThread,StopScan);
			OffTimer->Interval = 300;
			OffTimer->Enabled = true;
			if(mainForm->AppMode == 7 )
				OffState++;
			else
				OffState+=2;
		}
		mainForm->LogToFile("oscForm : pOffButClick : stop scan");
	}

	else if(OffState == 1 ){
		if(mainForm->AppMode == 7){
			//stop Litho        //hanging  file
			if(mainForm->myUdpThread->ipwUDPPort->Active && mainForm->myUdpThread->connected_udp){
				mainForm->myLithoFrm->LithoConfigFrm->scan_x_center = 50;
				mainForm->myLithoFrm->LithoConfigFrm->scan_y_center = 50;
				mainForm->myLithoFrm->LithoConfigFrm->scan_range = 10;
				mainForm->myLithoFrm->LithoConfigFrm->litho_delay = 100;
				mainForm->myLithoFrm->LithoConfigFrm->scan_resolution = 64;
				mainForm->myLithoFrm->LithoConfigFrm->scan_speed = 5;
				mainForm->myLithoFrm->LithoConfigFrm->litho_startstop = false;
				mainForm->myLithoFrm->LithoConfigFrm->LastLithoChanger = 0;

//				myLithoThread = new LithoFileCreatorThread(true);
//				myLithoThread->Priority = tpNormal;
//				myLithoThread->FreeOnTerminate = true;
//				myLithoThread->litho_file = true;
//				myLithoThread->Start();


//				while(myLithoThread->litho_file && !myLithoThread->progress){
//					Application->ProcessMessages();
//				}

				TThread::Synchronize(mainForm->myCommandCreatorThread,mainForm->myLithoFrm->LithoConfigFrm->StartLitho);
				OffTimer->Interval = 50;
				OffTimer->Enabled = true;
				OffState++;
			}
			mainForm->LogToFile("oscForm : pOffButClick : stop litho");
		}
	}

	else if(OffState == 2 ){
		//stop approaching
		if(mainForm->myUdpThread->ipwUDPPort->Active && mainForm->myUdpThread->connected_udp){
			mainForm->myControlPanelForm->AdvBadgeButtonStopApprocheClick(NULL);
			OffTimer->Interval = 50;
			OffTimer->Enabled = true;
			OffState++;
		}
		mainForm->LogToFile("oscForm : pOffButClick : stop approach");
	}

	else if(OffState == 3 ){
		mainForm->myTcpThread->fs_set = true;
        FsCommand.start = true;
		FsCommand.startx = 100;
		FsCommand.starty = 0;
		FsCommand.resolution = 64;
		FsCommand.delay = 0;
		FsCommand.mode = 1;
		FsCommand.GOTO = 1;
		FsCommand.dz1 = 0;
		FsCommand.dz2 = 0;
		FsCommand.u1 = 0;
		FsCommand.u2 = 0;
		FsCommand.currentZ = 0;
		FsCommand.currentU = 0;
		mainForm->myCommandCreatorThread->force_file = true;
//		mainForm->myCommandCreatorThread->StartStopFsClick(true, 100, 0, 64, 0, 1, 1, 0, 0, 0, 0, 0, 0);
		while(!mainForm->myUdpThread->fs_GoTo_set)
			Application->ProcessMessages();
		mainForm->LogToFile("oscForm : GoTo (min ,min)");
		mainForm->LogToFile("oscForm : pOffButClick : stop fs");
		OffTimer->Interval = 1;
		OffTimer->Enabled = true;
		OffState++;
	}

//	if(mainForm->AppMode == 5){
//		//stop Fs        //hanging  file
//		if(mainForm->myUdpThread->ipwUDPPort->Active && mainForm->myUdpThread->connected_udp){
//			TThread::Synchronize(mainForm->myCommandCreatorThread,StopFs);
//			Sleep(50);
//		}
//		mainForm->LogToFile("oscForm : pOffButClick : stop fs");
//	}

	else if(OffState == 4 ){
		SaveOscConfig();
		//disable osc
		plotTimer->Enabled = false;
		if(mainForm->myUdpThread)
			mainForm->myUdpThread->osc = false;
		OffTimer->Interval = 10;
		OffTimer->Enabled = true;
		OffState++;
		mainForm->LogToFile("oscForm : pOffButClick : stop osc");
	}

	else if(OffState == 5 ){
	//stop camera
		mainForm->myVideoForm->VideoGrabber1->StopPreview();
		OffTimer->Interval = 10;
		OffTimer->Enabled = true;
		OffState++;
		mainForm->LogToFile("oscForm : pOffButClick : stop camera");
	}

	else if(OffState == 6 ){
	//stop sbc
		if(mainForm->myUdpThread->ipwUDPPort->Active && mainForm->myUdpThread->connected_udp){
			mainForm->myUdpThread->SendData = myUdpDataSendClass->SettingPacket(0,0,0);
			TThread::Synchronize(mainForm->myUdpThread,SendPacket);
			OffTimer->Interval = 80;
			OffTimer->Enabled = true;
			OffState++;
		}
		mainForm->LogToFile("oscForm : pOffButClick : stop sbc");
	}

	else if(OffState == 7 ){
		try{
			if(mainForm->myImagerThread){
				mainForm->myImagerThread->Terminate();
			}
			OffTimer->Interval = 10;
			OffTimer->Enabled = true;
			OffState++;
			mainForm->LogToFile("oscForm : pOffButClick : ImagerThread terminate");
		}
		catch(...){
			mainForm->LogToFile("oscForm : pOffButClick : catch ");
		}
	}

	else if(OffState == 8 ){
		if(mainForm->myCommandCreatorThread)
			mainForm->myCommandCreatorThread->Terminate();
		OffTimer->Interval = 10;
		OffTimer->Enabled = true;
		OffState++;
		mainForm->LogToFile("oscForm : pOffButClick : CommandCreatorThread terminate");
	}
	else if(OffState == 9 ){
		if(mainForm->myTcpThread)
			mainForm->myCommandCreatorThread->Terminate();
		OffTimer->Interval = 10;
		OffTimer->Enabled = true;
		OffState++;
		mainForm->LogToFile("oscForm : pOffButClick : TcpThread terminate");
	}
	else if(OffState == 10 ){
		if(mainForm->myUdpThread)
			mainForm->myUdpThread->Terminate();
		OffTimer->Interval = 10;
		OffTimer->Enabled = true;
		OffState++;
		mainForm->LogToFile("oscForm : pOffButClick : UdpThread Terminate");
	}
	else if(OffState == 11 ){
	   mainForm->ExitApp();
	   mainForm->LogToFile("oscForm : pOffButClick : ExitApp");
	}
	else {
		OffTimer->Interval = 5;
		OffTimer->Enabled = true;
	}
}
//---------------------------------------------------------------------------

void __fastcall ToscForm::StopScan()
{
    ScanCommand.start = false;
	ScanCommand.set = true;
	ScanCommand.Changer = -1;
	mainForm->myCommandCreatorThread->scan_command = true;
//	mainForm->myCommandCreatorThread->StartScanClick(false,true,-1);
}
//---------------------------------------------------------------------------

void __fastcall ToscForm::StopFs()
{
	FsCommand.start = false;
	FsCommand.startx = 0;
	FsCommand.starty = 0;
	FsCommand.resolution = 64;
	FsCommand.delay = 100;
	FsCommand.mode = 1;
	FsCommand.GOTO = 0;
	FsCommand.dz1 = 0;
	FsCommand.dz2 = 0;
	FsCommand.u1 = 0;
	FsCommand.u2 = 0;
	FsCommand.currentZ = 0;
	FsCommand.currentU = 0;
	mainForm->myCommandCreatorThread->force_file = true;
//	mainForm->myCommandCreatorThread->StartStopFsClick(0, 0, 0, 64, 100, 1, 0, 0, 0, 0, 0, 0 , 0);
}
//---------------------------------------------------------------------------

void __fastcall ToscForm::plotTimerTimer(TObject *Sender)
{
	CheckSynchronize();
	try{
//		CrossTimerTimer(NULL);
		int min = 10000;
		for(int i=0; i<27; i++){
			if(min > data_queue[i].size())
				min = data_queue[i].size();
		}

		for(int i=0; i<min; i++){
			for (int h = 0; h < 4; h++){
				int	plotIndex = my_plot_set[h].int_WaveIndex;
				if(my_plot_set[h].bool_PlotActive){
					createPlot(data_queue[plotIndex].peek(),my_data_set[plotIndex].data_name,h);
				}
				my_plot_set[h].int_X++;
				if(my_plot_set[h].int_X > current_time_dev_with){
						my_plot_set[0].chart_Chart->Tag = 1;
						my_plot_set[h].int_X = 0;
				}

			}

//			if(PiezoCounter % 3 == 0){
				if(mainForm->myPiezoFrom){
					TOPO = ( ( data_queue[03].peek() / ( pow10l(mainForm->myUdpThread->data_buffer[03].data_scale*3)) ) - mainForm->myUdpThread->data_buffer[03].data_offset)/mainForm->myUdpThread->data_buffer[03].data_index;
					int BIAS = ( (data_queue[17].peek() / ( pow10l(mainForm->myUdpThread->data_buffer[17].data_scale*3)) ) - mainForm->myUdpThread->data_buffer[17].data_offset)/mainForm->myUdpThread->data_buffer[17].data_index;

					int LIA1_X = ( ( data_queue[9].peek() / ( pow10l(mainForm->myUdpThread->data_buffer[9].data_scale*3)) ) - mainForm->myUdpThread->data_buffer[9].data_offset)/mainForm->myUdpThread->data_buffer[9].data_index;
					int LIA1_Y = ( ( data_queue[10].peek() / ( pow10l(mainForm->myUdpThread->data_buffer[10].data_scale*3)) ) - mainForm->myUdpThread->data_buffer[10].data_offset)/mainForm->myUdpThread->data_buffer[10].data_index;


					mainForm->myForceForm->CurrentZ = TOPO;
					mainForm->myScanPanelForm->CurrentZ = TOPO;

					if(mainForm->Scaning && (mainForm->AppMode == 3 || mainForm->AppMode == 4) && !FlyError){
						int Err = MAX_MAX * ErrorPercent / 100;
						if(((TOPO <= MIN_VALUE + Err) && (ScanTable.Scan_Offset_val > 0)) || ((TOPO >= MAX_VALUE - Err) && (ScanTable.Scan_Offset_val < 0))){
//							mainForm->LogToFile("*FlyError = " + BoolToStr(mainForm->myUdpThread->FlyError ,true));
							FlyError = true;
							mainForm->myControlPanelForm->DBAdvGlowButtonScanClick(NULL);
//                            ShowMessage("Please Readjust Z-Piezo position ");
//							mainForm->LogToFile("**FlyError = " + BoolToStr(mainForm->myUdpThread->FlyError ,true));
//							mainForm->LogToFile("Piezo_Z = " + IntToStr(TOPO));
//							mainForm->LogToFile("Min = " + FloatToStr(MIN_VALUE + Err));
//							mainForm->LogToFile("Max = " + FloatToStr(MAX_VALUE - Err));
						}
					}


					mainForm->myForceForm->CurrentU = BIAS;

					mainForm->myKpfmFrm->CurvyEdit1->Text = IntToStr(LIA1_X);
					mainForm->myKpfmFrm->CurvyEdit2->Text = IntToStr(LIA1_Y);
//				   mainForm->LogToFile("mainForm->myUdpThread->data_buffer[03].data_index = " + FloatToStr(mainForm->myUdpThread->data_buffer[03].data_index) );

				}
//			}
			PiezoCounter++;

			for(int z=0; z<27; z++)
				data_queue[z].dequeue();


		}
	}
	catch(Exception &exception){
		ShowMessage("plotTimerTimer Exception: " + exception.Message + " _ " + exception.StackTrace);
	}
}
//---------------------------------------------------------------------------

void ToscForm::createPlot(double myData,UnicodeString title, int plot_number)
{
	if(my_plot_set[plot_number].bool_PlotPlay){
		int scale = returnScale(my_plot_set[plot_number].combo_unit->ItemIndex);
		DoMinMaxAvgChg(plot_number,myData);
		DoChgAvgLabel(scale,plot_number);

		if(	my_plot_set[0].chart_Chart->Tag == 1){
			my_plot_set[plot_number].fastlineseries_Series->YValues->Value[my_plot_set[plot_number].int_X] = myData;
			my_plot_set[plot_number].fastlineseries_Series->YValues->Modified = true;
			my_plot_set[plot_number].charttool_Cursor->XValue = my_plot_set[plot_number].int_X;
//			my_plot_set[plot_number].charttool_Cursor->Repaint();
		}
		else{
			my_plot_set[plot_number].fastlineseries_Series->AddXY(my_plot_set[plot_number].int_X,myData);
			my_plot_set[plot_number].charttool_Cursor->XValue = my_plot_set[plot_number].int_X;
//			my_plot_set[plot_number].charttool_Cursor->Repaint();
		}
	}
}
//---------------------------------------------------------------------------


void ToscForm::ActivatePlot(bool active, int plot_number)
{
	my_plot_set[plot_number].bool_PlotActive = active;
	if(my_plot_set[plot_number].bool_PlotActive)
	{
		if( !(my_plot_set[plot_number].bool_Created) ){
			createComboBox(my_plot_set[plot_number].combo_WaveName);
			if(my_plot_set[plot_number].int_WaveIndex == -1)
				my_plot_set[plot_number].combo_WaveName->ItemIndex = findFreePlot();
			else
				my_plot_set[plot_number].combo_WaveName->ItemIndex = my_plot_set[plot_number].int_WaveIndex;
//			mainForm->LogToFile("plot number " + IntToStr(plot_number) + "")
			my_plot_set[plot_number].int_WaveIndex = my_plot_set[plot_number].combo_WaveName->ItemIndex ;
//			mainForm->LogToFile("my_plot_set[" + IntToStr(plot_number) + "].combo_WaveName->ItemIndex = " + IntToStr(my_plot_set[plot_number].combo_WaveName->ItemIndex));
//			mainForm->LogToFile("my_plot_set[" + IntToStr(plot_number) + "].int_WaveIndex = " + IntToStr(my_plot_set[plot_number].int_WaveIndex));
			if(plot_number == 0)
				p1ComboBoxSelect(NULL);
			if(plot_number == 1)
				p2ComboBoxSelect(NULL);
			if(plot_number == 2)
				p3ComboBoxSelect(NULL);
			if(plot_number == 3)
				p4ComboBoxSelect(NULL);
			my_plot_set[plot_number].bool_Created = true;
			ShowPlot(plot_number,true);
		}
	}
	else{
		my_plot_set[plot_number].int_WaveIndex = -1;
		my_plot_set[plot_number].combo_WaveName->ItemIndex = -1;
		my_plot_set[plot_number].bool_Created = false;
		ShowPlot(plot_number,false);
	}

	p1ComboBox->ItemIndex = my_plot_set[0].int_WaveIndex;
	p2ComboBox->ItemIndex = my_plot_set[1].int_WaveIndex;
	p3ComboBox->ItemIndex = my_plot_set[2].int_WaveIndex;
	p4ComboBox->ItemIndex = my_plot_set[3].int_WaveIndex;

}
//---------------------------------------------------------------------------

void ToscForm::ShowPlot(int plot_number, bool show)
{
	my_plot_set[plot_number].main_Panel->Visible = show;
//	my_plot_set[plot_number].combo_WaveName->Visible = show;
//	my_plot_set[plot_number].advedit_PanelNumber->Visible = show;
//	my_plot_set[plot_number].calclabel_AvgValue->Visible = show;
//	my_plot_set[plot_number].calclabel_ChgValue->Visible = show;
//	my_plot_set[plot_number].chart_Chart->Visible = show;
//	my_plot_set[plot_number].charttool_Cursor->Visible = show;
//	my_plot_set[plot_number].bool_FirstStep = show;
//	my_plot_set[plot_number].panel_Setting->Visible = show;
}

void ToscForm::createComboBox(TCurvyCombo *box)
{
	box->Items->Clear();
	for(int i=0; i<27; i++){
		box->Items->Add(IntToStr(i+1) + "- " + my_data_set[i].data_name);
	}
}
//---------------------------------------------------------------------------

void __fastcall ToscForm::AdvUpDownEdit1ClickAdd(TObject *Sender)
{
//	mainForm->LogToFile("AdvUpDownEdit1ClickAdd : i_ChartCount = " + IntToStr(i_ChartCount));
	if(i_ChartCount < 4){
		i_ChartCount++;
		if(i_ChartCount == 3){
			i_ChartCount++;
//			AdvUpDownEdit1->Increment = 2;
		}
		else;
//			AdvUpDownEdit1->Increment = 1;
		if(!first){
			first = true;
			ComboBox1->Position = 4;
			ComboBox1Change(NULL);
		}
		showChart_Panels(i_ChartCount);
//		mainForm->LogToFile("AdvUpDownEdit1ClickAdd");
	}
	else{
//		AdvUpDownEdit1->Increment = 0;
		i_ChartCount = 4;
	}
//	mainForm->LogToFile("AdvUpDownEdit1ClickAdd");

	LabelAddSubEdit->Caption = IntToStr(i_ChartCount);

	p1ComboBox->ItemIndex = my_plot_set[0].int_WaveIndex;
	p2ComboBox->ItemIndex = my_plot_set[1].int_WaveIndex;
	p3ComboBox->ItemIndex = my_plot_set[2].int_WaveIndex;
	p4ComboBox->ItemIndex = my_plot_set[3].int_WaveIndex;

	for(int i=0; i<i_ChartCount; i++)
		createComboUnit(my_plot_set[i].int_WaveIndex,my_plot_set[i].combo_unit);
//	createComboUnit(my_plot_set[1].int_WaveIndex,my_plot_set[1].combo_unit);
//	createComboUnit(my_plot_set[2].int_WaveIndex,my_plot_set[2].combo_unit);
//	createComboUnit(my_plot_set[3].int_WaveIndex,my_plot_set[3].combo_unit);

	SaveOscConfig();
}
//---------------------------------------------------------------------------

void __fastcall ToscForm::AdvUpDownEdit1ClickSub(TObject *Sender)
{
	mainForm->LogToFile("AdvUpDownEdit1ClickSub : i_ChartCount = " + IntToStr(i_ChartCount));
	if(i_ChartCount > 1){
		i_ChartCount--;
		if(i_ChartCount == 3){
			i_ChartCount--;
//			AdvUpDownEdit1->Increment = 2;
		}
		else;
//			AdvUpDownEdit1->Increment = 1;

		showChart_Panels(i_ChartCount);
	}
	else{
//		AdvUpDownEdit1->Increment = 0;
		i_ChartCount = 1;
	}
	LabelAddSubEdit->Caption = IntToStr(i_ChartCount);

	p1ComboBox->ItemIndex = my_plot_set[0].int_WaveIndex;
	p2ComboBox->ItemIndex = my_plot_set[1].int_WaveIndex;
	p3ComboBox->ItemIndex = my_plot_set[2].int_WaveIndex;
	p4ComboBox->ItemIndex = my_plot_set[3].int_WaveIndex;
	for(int i=0; i<i_ChartCount; i++)
		createComboUnit(my_plot_set[i].int_WaveIndex,my_plot_set[i].combo_unit);
//	createComboUnit(my_plot_set[1].int_WaveIndex,my_plot_set[1].combo_unit);
//	createComboUnit(my_plot_set[2].int_WaveIndex,my_plot_set[2].combo_unit);
//	createComboUnit(my_plot_set[3].int_WaveIndex,my_plot_set[3].combo_unit);

	SaveOscConfig();
}
//---------------------------------------------------------------------------

int ToscForm::findFreePlot()
{
	for (int i = 0; i < 27; i++) {
		if (i != my_plot_set[0].int_WaveIndex && i != my_plot_set[1].int_WaveIndex && i != my_plot_set[2].int_WaveIndex && i != my_plot_set[3].int_WaveIndex) {
			return i;
		}
	}
	return -1;
}
//---------------------------------------------------------------------------

void ToscForm::showChart_Panels(int panels)
{
	this->Hide();
	if(panels == 0){
		pnlChart->Visible = false;
	}
	else{
		pnlChart->Visible = true;
//		PanelRight->Visible = true;
	}
	switch (panels)
	{
		case 0:{ // code to be executed if i_ChartCount = 0;
//			mainForm->LogToFile("case = " + IntToStr(0));
			ActivatePlot(false,0);
			ActivatePlot(false,1);
			ActivatePlot(false,2);
			ActivatePlot(false,3);
			showPlots(0);
			changeAllSampleRate(time_dev);
			reSizePlot();

			for(int i=0; i<4; i++){
				my_plot_set[i].fastlineseries_Series->Clear();
				my_plot_set[i].int_X = 0;
				my_plot_set[i].chart_Chart->Tag = 0;
				firstPlot = 0;
			}
			break;
		}
		case 1:{ // code to be executed if i_ChartCount = 1;
//			mainForm->LogToFile("case = " + IntToStr(1));
			ActivatePlot(true,0);
			ActivatePlot(false,1);
			ActivatePlot(false,2);
			ActivatePlot(false,3);
			showPlots(1);
			changeAllSampleRate(time_dev);
			reSizePlot();

			for(int i=0; i<4; i++){
				my_plot_set[i].fastlineseries_Series->Clear();
				my_plot_set[i].int_X = 0;
				my_plot_set[i].chart_Chart->Tag = 0;
                my_plot_set[i].combo_WaveName->ItemIndex = -1;
				firstPlot = 0;
			}
			break;
		}
		case 2:{ // code to be executed if i_ChartCount = 2;
//			mainForm->LogToFile("case = " + IntToStr(2));
			ActivatePlot(true,0);
			ActivatePlot(true,1);
			ActivatePlot(false,2);
			ActivatePlot(false,3);
			showPlots(2);
			changeAllSampleRate(time_dev);
			reSizePlot();

			for(int i=0; i<4; i++){
				my_plot_set[i].fastlineseries_Series->Clear();
				my_plot_set[i].int_X = 0;
				my_plot_set[i].chart_Chart->Tag = 0;
				firstPlot = 0;
			}
			break;
		}
		case 3:{ // code to be executed if i_ChartCount = 3;
//			mainForm->LogToFile("case = " + IntToStr(3));
			ActivatePlot(true,0);
			ActivatePlot(true,1);
			ActivatePlot(true,2);
			ActivatePlot(false,3);
			showPlots(3);
			changeAllSampleRate(time_dev);
			reSizePlot();

			for(int i=0; i<4; i++){
				my_plot_set[i].fastlineseries_Series->Clear();
				my_plot_set[i].int_X = 0;
				my_plot_set[i].chart_Chart->Tag = 0;
				firstPlot = 0;
			}
			break;
		}
		case 4:{ // code to be executed if i_ChartCount = 4;
//			mainForm->LogToFile("case = " + IntToStr(4));
			ActivatePlot(true,0);
			ActivatePlot(true,1);
			ActivatePlot(true,2);
			ActivatePlot(true,3);
			showPlots(4);
			changeAllSampleRate(time_dev);
			reSizePlot();

			for(int i=0; i<4; i++){
				my_plot_set[i].fastlineseries_Series->Clear();
				my_plot_set[i].int_X = 0;
				my_plot_set[i].chart_Chart->Tag = 0;
				firstPlot = 0;
			}
			break;
        }
	}
    Show();
}
//---------------------------------------------------------------------------

void ToscForm::showPlots(int count)
{
	switch (count)
	{
		case 0:{ // code to be executed if i_ChartCount = 0;

			PanelChart1->Visible = false;
			PanelChart2->Visible = false;
			PanelChart3->Visible = false;
			PanelChart4->Visible = false;


			break;
		}
		case 1:{ // code to be executed if i_ChartCount = 1;

			PanelChart1->Visible = true;
			PanelChart2->Visible = false;
			PanelChart3->Visible = false;
			PanelChart4->Visible = false;

			PanelChart1->Height = pnlChart->Height - 20;
			PanelChart1->Top = 10;
			PanelChart1->Width = pnlChart->Width - 20;
			PanelChart1->Left = 10;

			pPanel1->Height = 30;
			pPanel1->Width = PanelChart1->Width;
			Panel1_1->Height = PanelChart1->Height - pPanel1->Height;

			p1Panel->Width = pPanel1->Width/2;

//			AdvEdit1->Left = 1;
//			AdvEdit1->Top = 1;
//			AdvEdit1->Height = 21;
//			AdvEdit1->Width = 21;

			p1ComboBox->Left = 22;
			p1ComboBox->Top = 1;
			p1ComboBox->Height = 25;
			p1ComboBox->Width = 150;

//			edtAvg1->Left = 173 + 40;
//			edtAvg1->Top = 1;
//			edtAvg1->Height = 21;
//			edtAvg1->Width = 150;

			Panel1Avg->Left = 173 + 40;
			Panel1Avg->Top = 1;
			Panel1Avg->Height = 25;
			Panel1Avg->Width = 150;
			Avg1->Width = 117;

//			edtChg1->Left = 364 + 40;
//			edtChg1->Top = 1;
//			edtChg1->Height = 21;
//			edtChg1->Width = 150;

			Panel1Chg->Left = 364 + 40;
			Panel1Chg->Top = 1;
			Panel1Chg->Height = 25;
			Panel1Chg->Width = 150;
			Chg1->Width = 117;

			TeeCommander1->Top = -6;
			TeeCommander1->Left = 555;
			TeeCommander1->Height = 35;
			TeeCommander1->Width = 30;


			oscChart1->BottomAxis->SetMinMax(0,current_time_dev_with);

			p1ComboBox->ItemIndex = my_plot_set[0].int_WaveIndex;

			break;
		}
		case 2:{ // code to be executed if i_ChartCount = 2;

			PanelChart1->Visible = true;
			PanelChart2->Visible = true;
			PanelChart3->Visible = false;
			PanelChart4->Visible = false;

			//chart1
			PanelChart1->Height = pnlChart->Height/2 - 20;
			PanelChart1->Top = 10;
			PanelChart1->Width = pnlChart->Width - 20;
			PanelChart1->Left = 10;

			pPanel1->Height = 30;
			pPanel1->Width = PanelChart1->Width;
			Panel1_1->Height = PanelChart1->Height - pPanel1->Height;

			p1Panel->Width = pPanel1->Width/2;

//			AdvEdit1->Left = 1;
//			AdvEdit1->Top = 1;
//			AdvEdit1->Height = 21;
//			AdvEdit1->Width = 21;

			p1ComboBox->Left = 22;
			p1ComboBox->Top = 1;
			p1ComboBox->Height = 25;
			p1ComboBox->Width = 150;

//			edtAvg1->Left = 173 + 40;
//			edtAvg1->Top = 1;
//			edtAvg1->Height = 21;
//			edtAvg1->Width = 150;

			Panel1Avg->Left = 173 + 40;
			Panel1Avg->Top = 1;
			Panel1Avg->Height = 25;
			Panel1Avg->Width = 150;
			Avg1->Width = 117;

//			edtChg1->Left = 364 + 40;
//			edtChg1->Top = 1;
//			edtChg1->Height = 21;
//			edtChg1->Width = 150;

			Panel1Chg->Left = 364 + 40;
			Panel1Chg->Top = 1;
			Panel1Chg->Height = 25;
			Panel1Chg->Width = 150;
			Avg1->Width = 117;

			TeeCommander1->Top = -6;
			TeeCommander1->Left = 555;
			TeeCommander1->Height = 35;
			TeeCommander1->Width = 30;

			oscChart1->BottomAxis->SetMinMax(0,current_time_dev_with);

			//cahrt2
			PanelChart2->Height = pnlChart->Height/2 - 20;
			PanelChart2->Top = pnlChart->Height/2 + 10;
			PanelChart2->Width = pnlChart->Width - 20;
			PanelChart2->Left = 10;

			pPanel2->Height = 30;
			pPanel2->Width = PanelChart2->Width;
			Panel2_2->Height = PanelChart2->Height - pPanel2->Height;

			p2Panel->Width = pPanel2->Width/2;

//			AdvEdit2->Left = 1;
//			AdvEdit2->Top = 1;
//			AdvEdit2->Height = 21;
//			AdvEdit2->Width = 21;

			p2ComboBox->Left = 22;
			p2ComboBox->Top = 1;
			p2ComboBox->Height = 25;
			p2ComboBox->Width = 150;

//			edtAvg2->Left = 173 + 40;
//			edtAvg2->Top = 1;
//			edtAvg2->Height = 21;
//			edtAvg2->Width = 150;

			Panel2Avg->Left = 173 + 40;
			Panel2Avg->Top = 1;
			Panel2Avg->Height = 25;
			Panel2Avg->Width = 150;
			Avg2->Width = 117;

//			edtChg2->Left = 364 + 40;
//			edtChg2->Top = 1;
//			edtChg2->Height = 21;
//			edtChg2->Width = 150;

			Panel2Chg->Left = 364 + 40;
			Panel2Chg->Top = 1;
			Panel2Chg->Height = 25;
			Panel2Chg->Width = 150;
			Chg2->Width = 117;

			TeeCommander2->Top = -6;
			TeeCommander2->Left = 555;
			TeeCommander2->Height = 35;
			TeeCommander2->Width = 30;

			oscChart2->BottomAxis->SetMinMax(0,current_time_dev_with);

			p1ComboBox->ItemIndex = my_plot_set[0].int_WaveIndex;
			p2ComboBox->ItemIndex = my_plot_set[1].int_WaveIndex;

			break;
		}
		case 3:{ // code to be executed if i_ChartCount = 3;

//			PanelChart1->Visible = true;
//			PanelChart2->Visible = true;
//			PanelChart3->Visible = true;
//			PanelChart4->Visible = false;
//
//			//chart1
//			PanelChart1->Height = pnlChart->Height/2 - 20;
//			PanelChart1->Top = 10;
//			PanelChart1->Width = pnlChart->Width/2 - 20;
//			PanelChart1->Left = 10;
//
//			pPanel1->Height = 30;
//			pPanel1->Width = PanelChart1->Width;
//			Panel1_1->Height = PanelChart1->Height - pPanel1->Height;
//
////			AdvEdit1->Left = 1;
////			AdvEdit1->Top = 1;
////			AdvEdit1->Height = 21;
////			AdvEdit1->Width = 21;
//
//			p1ComboBox->Left = 22;
//			p1ComboBox->Top = 1;
//			p1ComboBox->Height = 21;
//			p1ComboBox->Width = 150;
//
//			edtAvg1->Left = 173 + 40;
//			edtAvg1->Top = 1;
//			edtAvg1->Height = 21;
//			edtAvg1->Width = 150;
//
//			edtChg1->Left = 364 + 40;
//			edtChg1->Top = 1;
//			edtChg1->Height = 21;
//			edtChg1->Width = 150;
//
//			TeeCommander1->Top = -6;
//			TeeCommander1->Left = 555;
//			TeeCommander1->Height = 35;
//			TeeCommander1->Width = 30;
//
//			oscChart1->BottomAxis->SetMinMax(0,current_time_dev_with);
//
//			//chart2
//			PanelChart2->Height = pnlChart->Height/2 - 20;
//			PanelChart2->Top = 10;
//			PanelChart2->Width = pnlChart->Width/2 - 20;
//			PanelChart2->Left = pnlChart->Width/2 + 10;
//
//			pPanel2->Height = 30;
//			pPanel2->Width = PanelChart2->Width;
//			Panel2_2->Height = PanelChart2->Height - pPanel2->Height;
//
//			p2Panel->Width = pPanel2->Width/2;
//
////			AdvEdit2->Left = 1;
////			AdvEdit2->Top = 1;
////			AdvEdit2->Height = 21;
////			AdvEdit2->Width = 21;
//
//			p2ComboBox->Left = 22;
//			p2ComboBox->Top = 1;
//			p2ComboBox->Height = 21;
//			p2ComboBox->Width = 150;
//
//			edtAvg2->Left = 173 + 40;
//			edtAvg2->Top = 1;
//			edtAvg2->Height = 21;
//			edtAvg2->Width = 150;
//
//			edtChg2->Left = 364 + 40;
//			edtChg2->Top = 1;
//			edtChg2->Height = 21;
//			edtChg2->Width = 150;
//
//			TeeCommander2->Top = -6;
//			TeeCommander2->Left = 555;
//			TeeCommander2->Height = 35;
//			TeeCommander2->Width = 30;
//
//			oscChart2->BottomAxis->SetMinMax(0,current_time_dev_with);
//
//			//chart3
//			PanelChart3->Height = pnlChart->Height/2 - 20;
//			PanelChart3->Top = pnlChart->Height/2 + 10;
//			PanelChart3->Width = pnlChart->Width/2 - 20;
//			PanelChart3->Left = 10;
//
//			pPanel3->Height = 30;
//			pPanel3->Width = PanelChart3->Width;
//			Panel3_3->Height = PanelChart3->Height - pPanel3->Height;
//
//			p3Panel->Width = pPanel3->Width/2;
//
////			AdvEdit3->Left = 1;
////			AdvEdit3->Top = 1;
////			AdvEdit3->Height = 21;
////			AdvEdit3->Width = 21;
//
//			p3ComboBox->Left = 22;
//			p3ComboBox->Top = 1;
//			p3ComboBox->Height = 21;
//			p3ComboBox->Width = 150;
//
//			edtAvg3->Left = 173 + 40;
//			edtAvg3->Top = 1;
//			edtAvg3->Height = 21;
//			edtAvg3->Width = 150;
//
//			edtChg3->Left = 364 + 40;
//			edtChg3->Top = 1;
//			edtChg3->Height = 21;
//			edtChg3->Width = 150;
//
//			TeeCommander3->Top = -6;
//			TeeCommander3->Left = 555 + 50;
//			TeeCommander3->Height = 35;
//			TeeCommander3->Width = 30;
//
//			oscChart3->BottomAxis->SetMinMax(0,current_time_dev_with);
//
//			p1ComboBox->ItemIndex = my_plot_set[0].int_WaveIndex;
//			p2ComboBox->ItemIndex = my_plot_set[1].int_WaveIndex;
//			p3ComboBox->ItemIndex = my_plot_set[2].int_WaveIndex;

			break;
		}
		case 4:{ // code to be executed if i_ChartCount = 4;
			//chart1
			PanelChart1->Height = pnlChart->Height/2 - 20;
			PanelChart1->Top = 10;
			PanelChart1->Width = pnlChart->Width/2 - 20;
			PanelChart1->Left = 10;

			pPanel1->Height = 30;
			pPanel1->Width = PanelChart1->Width;
			Panel1_1->Height = PanelChart1->Height - pPanel1->Height;

//			AdvEdit1->Left = 1;
//			AdvEdit1->Top = 1;
//			AdvEdit1->Height = 21;
//			AdvEdit1->Width = 21;

			p1ComboBox->Left = 22;
			p1ComboBox->Top = 1;
			p1ComboBox->Height = 25;
			p1ComboBox->Width = 150;

//			edtAvg1->Left = 173 + 40;
//			edtAvg1->Top = 1;
//			edtAvg1->Height = 21;
//			edtAvg1->Width = 150;

			Panel1Avg->Left = 173 + 40;
			Panel1Avg->Top = 1;
			Panel1Avg->Height = 25;
			Panel1Avg->Width = 150;
			Avg1->Width = 117;

//			edtChg1->Left = 364 + 40;
//			edtChg1->Top = 1;
//			edtChg1->Height = 21;
//			edtChg1->Width = 150;

			Panel1Chg->Left = 364 + 40;
			Panel1Chg->Top = 1;
			Panel1Chg->Height = 25;
			Panel1Chg->Width = 150;
			Chg1->Width = 117;

			TeeCommander1->Top = -6;
			TeeCommander1->Left = 555;
			TeeCommander1->Height = 35;
			TeeCommander1->Width = 30;

			oscChart1->BottomAxis->SetMinMax(0,current_time_dev_with);

			//chart2
			PanelChart2->Height = pnlChart->Height/2 - 20;
			PanelChart2->Top = 10;
			PanelChart2->Width = pnlChart->Width/2 - 20;
			PanelChart2->Left = pnlChart->Width/2 + 10;

			pPanel2->Height = 30;
			pPanel2->Width = PanelChart2->Width;
			Panel2_2->Height = PanelChart2->Height - pPanel2->Height;

			p2Panel->Width = pPanel2->Width/2;

//			AdvEdit2->Left = 1;
//			AdvEdit2->Top = 1;
//			AdvEdit2->Height = 21;
//			AdvEdit2->Width = 21;

			p2ComboBox->Left = 22;
			p2ComboBox->Top = 1;
			p2ComboBox->Height = 25;
			p2ComboBox->Width = 150;

//			edtAvg2->Left = 173 + 40;
//			edtAvg2->Top = 1;
//			edtAvg2->Height = 21;
//			edtAvg2->Width = 150;

			Panel2Avg->Left = 173 + 40;
			Panel2Avg->Top = 1;
			Panel2Avg->Height = 25;
			Panel2Avg->Width = 150;
			Avg2->Width = 117;

//			edtChg2->Left = 364 + 40;
//			edtChg2->Top = 1;
//			edtChg2->Height = 21;
//			edtChg2->Width = 150;

			Panel2Chg->Left = 364 + 40;
			Panel2Chg->Top = 1;
			Panel2Chg->Height = 25;
			Panel2Chg->Width = 150;
			Chg2->Width = 117;

			TeeCommander2->Top = -6;
			TeeCommander2->Left = 555;
			TeeCommander2->Height = 35;
			TeeCommander2->Width = 30;

			oscChart2->BottomAxis->SetMinMax(0,current_time_dev_with);

			//chart3
			PanelChart3->Height = pnlChart->Height/2 - 20;
			PanelChart3->Top = pnlChart->Height/2 + 10;
			PanelChart3->Width = pnlChart->Width/2 - 20;
			PanelChart3->Left = 10;

			pPanel3->Height = 30;
			pPanel3->Width = PanelChart3->Width;
			Panel3_3->Height = PanelChart3->Height - pPanel3->Height;

			p3Panel->Width = pPanel3->Width/2;

//			AdvEdit3->Left = 1;
//			AdvEdit3->Top = 1;
//			AdvEdit3->Height = 21;
//			AdvEdit3->Width = 21;

			p3ComboBox->Left = 22;
			p3ComboBox->Top = 1;
			p3ComboBox->Height = 25;
			p3ComboBox->Width = 150;

//			edtAvg3->Left = 173 + 40;
//			edtAvg3->Top = 1;
//			edtAvg3->Height = 21;
//			edtAvg3->Width = 150;

			Panel3Avg->Left = 173 + 40;
			Panel3Avg->Top = 1;
			Panel3Avg->Height = 25;
			Panel3Avg->Width = 150;
			Avg3->Width = 117;

//			edtChg3->Left = 364 + 40;
//			edtChg3->Top = 1;
//			edtChg3->Height = 21;
//			edtChg3->Width = 150;

			Panel3Chg->Left = 364 + 40;
			Panel3Chg->Top = 1;
			Panel3Chg->Height = 25;
			Panel3Chg->Width = 150;
			Chg3->Width = 117;

			TeeCommander3->Top = -6;
			TeeCommander3->Left = 555;
			TeeCommander3->Height = 35;
			TeeCommander3->Width = 30;

			oscChart3->BottomAxis->SetMinMax(0,current_time_dev_with);


			//chart4
			PanelChart4->Height = pnlChart->Height/2 - 20;
			PanelChart4->Top = pnlChart->Height/2 + 10;
			PanelChart4->Width = pnlChart->Width/2 - 20;
			PanelChart4->Left = pnlChart->Width/2 + 10;

			pPanel4->Height = 30;
			pPanel4->Width = PanelChart4->Width;
			Panel4_4->Height = PanelChart4->Height - pPanel4->Height;

			p4Panel->Width = pPanel4->Width/2;

//			AdvEdit4->Left = 1;
//			AdvEdit4->Top = 1;
//			AdvEdit4->Height = 21;
//			AdvEdit4->Width = 21;

			p4ComboBox->Left = 22;
			p4ComboBox->Top = 1;
			p4ComboBox->Height = 25;
			p4ComboBox->Width = 150;

//			edtAvg4->Left = 173 + 40;
//			edtAvg4->Top = 1;
//			edtAvg4->Height = 21;
//			edtAvg4->Width = 150;

			Panel4Avg->Left = 173 + 40;
			Panel4Avg->Top = 1;
			Panel4Avg->Height = 25;
			Panel4Avg->Width = 150;
			Avg4->Width = 117;

//			edtChg4->Left = 364 + 40;
//			edtChg4->Top = 1;
//			edtChg4->Height = 21;
//			edtChg4->Width = 150;

			Panel4Chg->Left = 364 + 40;
			Panel4Chg->Top = 1;
			Panel4Chg->Height = 25;
			Panel4Chg->Width = 150;
			Chg4->Width = 117;

			TeeCommander4->Top = -6;
			TeeCommander4->Left = 555;
			TeeCommander4->Height = 35;
			TeeCommander4->Width = 30;

			oscChart4->BottomAxis->SetMinMax(0,current_time_dev_with);

			p1ComboBox->ItemIndex = my_plot_set[0].int_WaveIndex;
			p2ComboBox->ItemIndex = my_plot_set[1].int_WaveIndex;
			p3ComboBox->ItemIndex = my_plot_set[2].int_WaveIndex;
			p4ComboBox->ItemIndex = my_plot_set[3].int_WaveIndex;

			break;
		}
	}
}
//---------------------------------------------------------------------------

void ToscForm::refreshPlots()
{
	for(int i=0; i<4; i++){
		my_plot_set[i].double_Avg = 0;
		my_plot_set[i].double_Chg = 0;
		my_plot_set[i].double_Sum =0;

		my_plot_set[i].chart_Chart->Tag = 0;
	}
}
//---------------------------------------------------------------------------

void __fastcall ToscForm::p1PauseClick(TObject *Sender)
{
	for(int i=0; i<4; i++){
		my_plot_set[i].bool_PlotPlay = !(my_plot_set[i].bool_PlotPlay);
		if(my_plot_set[i].bool_PlotPlay){
			DBAdvGlowButtonPalyPause->Picture = PausePic;
			DBAdvGlowButtonPalyPause->Picture->Width = DBAdvGlowButtonPalyPause->Picture->Height;
			DBAdvGlowButtonPalyPause->Font->Color = clWhite;
			DBAdvGlowButtonPalyPause->Caption = "Pause Osc";

			paly_pause = true;
			MakePlayPusClicked(paly_pause);

			AdvEdit5->Enabled = true;
			ComboBox1->Enabled = true;
			my_plot_set[i].bool_FirstStep = false;
			my_plot_set[i].commander->Enabled = false;
			my_plot_set[i].fastlineseries_Series->Clear();
			my_plot_set[i].int_X = 0;
			my_plot_set[i].chart_Chart->Tag = 0;
			firstPlot = 0;
			my_plot_set[i].combo_WaveName->Enabled = true;
			my_plot_set[i].commander->Visible = false;

			enabled_playpause = true;
			enabled_addsub = true;
			enabled_timedev = true;
			enabled_rec = true;

			PanelAddSub->Enabled = true;
			PanelTimeDev->Enabled = true;
			PanelRecord->Enabled = true;
		}
		else{
			DBAdvGlowButtonPalyPause->Picture->Width = DBAdvGlowButtonPalyPause->Picture->Height;
			DBAdvGlowButtonPalyPause->Picture = PausePicHover;
			DBAdvGlowButtonPalyPause->Font->Color = TColor(0x00F0D27D);
			DBAdvGlowButtonPalyPause->Caption = "Paly Osc";

			paly_pause = false;
			MakePlayPusClicked(paly_pause);

			my_plot_set[i].commander->Enabled = true;
			AdvEdit5->Enabled = false;
			ComboBox1->Enabled = false;
			my_plot_set[i].combo_WaveName->Enabled = false;
			PanelTimeDev->Enabled = false;
			my_plot_set[i].commander->Visible = true;

			enabled_playpause = true;
			enabled_addsub = false;
			enabled_timedev = false;
			enabled_rec = false;

			PanelAddSub->Enabled = false;
			PanelTimeDev->Enabled = false;
			PanelRecord->Enabled = false;
		}
	}
	for(int i=0; i<27; i++)
		data_queue[i].initQ();
}
//---------------------------------------------------------------------------

void ToscForm::MakePlayPusClicked(bool play)
{
	if(play){
		DBAdvGlowButtonPalyPause->Appearance->BorderColor = TColor(0x00553629);
		DBAdvGlowButtonPalyPause->Appearance->BorderColorHot = TColor(0x008B6757);
		DBAdvGlowButtonPalyPause->Appearance->BorderColorChecked = TColor(0x008B6757);
		DBAdvGlowButtonPalyPause->Appearance->BorderColorCheckedHot = TColor(0x008B6757);
		DBAdvGlowButtonPalyPause->Appearance->BorderColorDisabled = TColor(0x008B6757);
		DBAdvGlowButtonPalyPause->Appearance->BorderColorDown = TColor(0x008B6757);
		DBAdvGlowButtonPalyPause->Appearance->BorderColorFocused = TColor(0x008B6757);
		DBAdvGlowButtonPalyPause->Appearance->Color = TColor(0x00553629);
		DBAdvGlowButtonPalyPause->Appearance->ColorChecked = TColor(0x008B6757);
		DBAdvGlowButtonPalyPause->Appearance->ColorCheckedTo = TColor(0x008B6757);
		DBAdvGlowButtonPalyPause->Appearance->ColorDisabled = TColor(0x008B6757);
		DBAdvGlowButtonPalyPause->Appearance->ColorDisabledTo = TColor(0x008B6757);
		DBAdvGlowButtonPalyPause->Appearance->ColorDown = TColor(0x008B6757);
		DBAdvGlowButtonPalyPause->Appearance->ColorDownTo = TColor(0x008B6757);
		DBAdvGlowButtonPalyPause->Appearance->ColorHot = TColor(0x008B6757);
		DBAdvGlowButtonPalyPause->Appearance->ColorHotTo = TColor(0x008B6757);
		DBAdvGlowButtonPalyPause->Appearance->ColorMirror = TColor(0x00553629);
		DBAdvGlowButtonPalyPause->Appearance->ColorMirrorChecked = TColor(0x008B6757);
		DBAdvGlowButtonPalyPause->Appearance->ColorMirrorCheckedTo = TColor(0x008B6757);
		DBAdvGlowButtonPalyPause->Appearance->ColorMirrorDisabled = TColor(0x008B6757);
		DBAdvGlowButtonPalyPause->Appearance->ColorMirrorDisabledTo = TColor(0x008B6757);
		DBAdvGlowButtonPalyPause->Appearance->ColorMirrorDown = TColor(0x008B6757);
		DBAdvGlowButtonPalyPause->Appearance->ColorMirrorDownTo = TColor(0x008B6757);
		DBAdvGlowButtonPalyPause->Appearance->ColorMirrorHot = TColor(0x008B6757);
		DBAdvGlowButtonPalyPause->Appearance->ColorMirrorHotTo = TColor(0x008B6757);
		DBAdvGlowButtonPalyPause->Appearance->ColorMirrorTo = TColor(0x00553629);
		DBAdvGlowButtonPalyPause->Appearance->ColorTo = TColor(0x00553629);
	}
	else{
		DBAdvGlowButtonPalyPause->Appearance->BorderColor = TColor(0x00614438);
		DBAdvGlowButtonPalyPause->Appearance->BorderColorHot = TColor(0x008B6757);
		DBAdvGlowButtonPalyPause->Appearance->BorderColorChecked = TColor(0x008B6757);
		DBAdvGlowButtonPalyPause->Appearance->BorderColorCheckedHot = TColor(0x008B6757);
		DBAdvGlowButtonPalyPause->Appearance->BorderColorDisabled = TColor(0x008B6757);
		DBAdvGlowButtonPalyPause->Appearance->BorderColorDown = TColor(0x008B6757);
		DBAdvGlowButtonPalyPause->Appearance->BorderColorFocused = TColor(0x008B6757);
		DBAdvGlowButtonPalyPause->Appearance->Color = TColor(0x00614438);
		DBAdvGlowButtonPalyPause->Appearance->ColorChecked = TColor(0x008B6757);
		DBAdvGlowButtonPalyPause->Appearance->ColorCheckedTo = TColor(0x008B6757);
		DBAdvGlowButtonPalyPause->Appearance->ColorDisabled = TColor(0x008B6757);
		DBAdvGlowButtonPalyPause->Appearance->ColorDisabledTo = TColor(0x008B6757);
		DBAdvGlowButtonPalyPause->Appearance->ColorDown = TColor(0x008B6757);
		DBAdvGlowButtonPalyPause->Appearance->ColorDownTo = TColor(0x008B6757);
		DBAdvGlowButtonPalyPause->Appearance->ColorHot = TColor(0x008B6757);
		DBAdvGlowButtonPalyPause->Appearance->ColorHotTo = TColor(0x008B6757);
		DBAdvGlowButtonPalyPause->Appearance->ColorMirror = TColor(0x00614438);
		DBAdvGlowButtonPalyPause->Appearance->ColorMirrorChecked = TColor(0x008B6757);
		DBAdvGlowButtonPalyPause->Appearance->ColorMirrorCheckedTo = TColor(0x008B6757);
		DBAdvGlowButtonPalyPause->Appearance->ColorMirrorDisabled = TColor(0x008B6757);
		DBAdvGlowButtonPalyPause->Appearance->ColorMirrorDisabledTo = TColor(0x008B6757);
		DBAdvGlowButtonPalyPause->Appearance->ColorMirrorDown = TColor(0x008B6757);
		DBAdvGlowButtonPalyPause->Appearance->ColorMirrorDownTo = TColor(0x008B6757);
		DBAdvGlowButtonPalyPause->Appearance->ColorMirrorHot = TColor(0x008B6757);
		DBAdvGlowButtonPalyPause->Appearance->ColorMirrorHotTo = TColor(0x008B6757);
		DBAdvGlowButtonPalyPause->Appearance->ColorMirrorTo = TColor(0x00614438);
		DBAdvGlowButtonPalyPause->Appearance->ColorTo = TColor(0x00614438);
	}

}
//---------------------------------------------------------------------------

void __fastcall ToscForm::ComboBox1Change(TObject *Sender)
{
	time_dev = ComboBox1->Position;
	changeAllSampleRate(time_dev);
	reSizePlot();
	for(int i=0; i<4; i++){
		if(my_plot_set[i].fastlineseries_Series)

		my_plot_set[i].fastlineseries_Series->Clear();
		my_plot_set[i].int_X = 0;
		my_plot_set[i].chart_Chart->Tag = 0;
		firstPlot = 0;
		my_plot_set[i].double_Avg = 0;
		my_plot_set[i].double_Chg = 0;
		my_plot_set[i].double_Max = 0;
		my_plot_set[i].double_Min = 0;
		my_plot_set[i].double_Sum = 0;
	}

	p1ComboBox->ItemIndex = my_plot_set[0].int_WaveIndex;
	p2ComboBox->ItemIndex = my_plot_set[1].int_WaveIndex;
	p3ComboBox->ItemIndex = my_plot_set[2].int_WaveIndex;
	p4ComboBox->ItemIndex = my_plot_set[3].int_WaveIndex;

	createComboUnit(my_plot_set[0].int_WaveIndex,my_plot_set[0].combo_unit);
	createComboUnit(my_plot_set[1].int_WaveIndex,my_plot_set[1].combo_unit);
	createComboUnit(my_plot_set[2].int_WaveIndex,my_plot_set[2].combo_unit);
	createComboUnit(my_plot_set[3].int_WaveIndex,my_plot_set[3].combo_unit);

	SaveOscConfig();
}
//---------------------------------------------------------------------------

void __fastcall ToscForm::AdvGlassButton1Click(TObject *Sender)
{
	recording = !recording;
	if(recording){
//		p1Pause->Enabled = false;
		if(!rec_created){
			DBAdvGlowButtonRecord->Picture = RecPicHover;
			DBAdvGlowButtonRecord->Picture->Width = DBAdvGlowButtonPalyPause->Picture->Height;
			DBAdvGlowButtonRecord->Font->Color = TColor(0x00F0D27D);
			DBAdvGlowButtonRecord->Caption = L"Recording 0 sec";;
//			PanelRecord->Color = 0x008B6757;
			MakeRecordClicked(false);


//			PanelPlayPuase->Width = Image2->Width + Label2->Width;
			mainForm->myUdpThread->stop_recored = false;
			mainForm->myUdpThread->start_record = false;
			mainForm->myUdpThread->record = true;
			RecordTimer->Interval = rec_time * 1000;
			RecordTimer->Enabled = true;

			TimerRecCounter->Enabled = true;
			START = Now();
		}
	}
	else{
		DBAdvGlowButtonRecord->Picture = RecPic;
		DBAdvGlowButtonRecord->Picture->Width = DBAdvGlowButtonPalyPause->Picture->Height;
		DBAdvGlowButtonRecord->Font->Color = clWhite;
		DBAdvGlowButtonRecord->Caption = L"Record Osc";
		MakeRecordClicked(true);

		RecordTimer->Enabled = false;
		TimerRecCounter->Enabled = false;
		mainForm->myUdpThread->stop_recored = true;
	}
}
//---------------------------------------------------------------------------

void ToscForm::MakeRecordClicked(bool record)
{
	if(record){
		DBAdvGlowButtonRecord->Appearance->BorderColor = TColor(0x00553629);
		DBAdvGlowButtonRecord->Appearance->BorderColorHot = TColor(0x008B6757);
		DBAdvGlowButtonRecord->Appearance->BorderColorChecked = TColor(0x008B6757);
		DBAdvGlowButtonRecord->Appearance->BorderColorCheckedHot = TColor(0x008B6757);
		DBAdvGlowButtonRecord->Appearance->BorderColorDisabled = TColor(0x008B6757);
		DBAdvGlowButtonRecord->Appearance->BorderColorDown = TColor(0x008B6757);
		DBAdvGlowButtonRecord->Appearance->BorderColorFocused = TColor(0x008B6757);
		DBAdvGlowButtonRecord->Appearance->Color = TColor(0x00553629);
		DBAdvGlowButtonRecord->Appearance->ColorChecked = TColor(0x008B6757);
		DBAdvGlowButtonRecord->Appearance->ColorCheckedTo = TColor(0x008B6757);
		DBAdvGlowButtonRecord->Appearance->ColorDisabled = TColor(0x008B6757);
		DBAdvGlowButtonRecord->Appearance->ColorDisabledTo = TColor(0x008B6757);
		DBAdvGlowButtonRecord->Appearance->ColorDown = TColor(0x008B6757);
		DBAdvGlowButtonRecord->Appearance->ColorDownTo = TColor(0x008B6757);
		DBAdvGlowButtonRecord->Appearance->ColorHot = TColor(0x008B6757);
		DBAdvGlowButtonRecord->Appearance->ColorHotTo = TColor(0x008B6757);
		DBAdvGlowButtonRecord->Appearance->ColorMirror = TColor(0x00553629);
		DBAdvGlowButtonRecord->Appearance->ColorMirrorChecked = TColor(0x008B6757);
		DBAdvGlowButtonRecord->Appearance->ColorMirrorCheckedTo = TColor(0x008B6757);
		DBAdvGlowButtonRecord->Appearance->ColorMirrorDisabled = TColor(0x008B6757);
		DBAdvGlowButtonRecord->Appearance->ColorMirrorDisabledTo = TColor(0x008B6757);
		DBAdvGlowButtonRecord->Appearance->ColorMirrorDown = TColor(0x008B6757);
		DBAdvGlowButtonRecord->Appearance->ColorMirrorDownTo = TColor(0x008B6757);
		DBAdvGlowButtonRecord->Appearance->ColorMirrorHot = TColor(0x008B6757);
		DBAdvGlowButtonRecord->Appearance->ColorMirrorHotTo = TColor(0x008B6757);
		DBAdvGlowButtonRecord->Appearance->ColorMirrorTo = TColor(0x00553629);
		DBAdvGlowButtonRecord->Appearance->ColorTo = TColor(0x00553629);
	}
	else{
		DBAdvGlowButtonRecord->Appearance->BorderColor = TColor(0x00614438);
		DBAdvGlowButtonRecord->Appearance->BorderColorHot = TColor(0x008B6757);
		DBAdvGlowButtonRecord->Appearance->BorderColorChecked = TColor(0x008B6757);
		DBAdvGlowButtonRecord->Appearance->BorderColorCheckedHot = TColor(0x008B6757);
		DBAdvGlowButtonRecord->Appearance->BorderColorDisabled = TColor(0x008B6757);
		DBAdvGlowButtonRecord->Appearance->BorderColorDown = TColor(0x008B6757);
		DBAdvGlowButtonRecord->Appearance->BorderColorFocused = TColor(0x008B6757);
		DBAdvGlowButtonRecord->Appearance->Color = TColor(0x00614438);
		DBAdvGlowButtonRecord->Appearance->ColorChecked = TColor(0x008B6757);
		DBAdvGlowButtonRecord->Appearance->ColorCheckedTo = TColor(0x008B6757);
		DBAdvGlowButtonRecord->Appearance->ColorDisabled = TColor(0x008B6757);
		DBAdvGlowButtonRecord->Appearance->ColorDisabledTo = TColor(0x008B6757);
		DBAdvGlowButtonRecord->Appearance->ColorDown = TColor(0x008B6757);
		DBAdvGlowButtonRecord->Appearance->ColorDownTo = TColor(0x008B6757);
		DBAdvGlowButtonRecord->Appearance->ColorHot = TColor(0x008B6757);
		DBAdvGlowButtonRecord->Appearance->ColorHotTo = TColor(0x008B6757);
		DBAdvGlowButtonRecord->Appearance->ColorMirror = TColor(0x00614438);
		DBAdvGlowButtonRecord->Appearance->ColorMirrorChecked = TColor(0x008B6757);
		DBAdvGlowButtonRecord->Appearance->ColorMirrorCheckedTo = TColor(0x008B6757);
		DBAdvGlowButtonRecord->Appearance->ColorMirrorDisabled = TColor(0x008B6757);
		DBAdvGlowButtonRecord->Appearance->ColorMirrorDisabledTo = TColor(0x008B6757);
		DBAdvGlowButtonRecord->Appearance->ColorMirrorDown = TColor(0x008B6757);
		DBAdvGlowButtonRecord->Appearance->ColorMirrorDownTo = TColor(0x008B6757);
		DBAdvGlowButtonRecord->Appearance->ColorMirrorHot = TColor(0x008B6757);
		DBAdvGlowButtonRecord->Appearance->ColorMirrorHotTo = TColor(0x008B6757);
		DBAdvGlowButtonRecord->Appearance->ColorMirrorTo = TColor(0x00614438);
		DBAdvGlowButtonRecord->Appearance->ColorTo = TColor(0x00614438);
	}
}
//---------------------------------------------------------------------------

void __fastcall ToscForm::RecordTimerTimer(TObject *Sender)
{
	RecordTimer->Enabled = false;
	TimerRecCounter->Enabled = false;
	mainForm->myUdpThread->stop_recored = true;

	DBAdvGlowButtonRecord->Picture = RecPic;
	DBAdvGlowButtonRecord->Picture->Width = DBAdvGlowButtonPalyPause->Picture->Height;
	DBAdvGlowButtonRecord->Font->Color = clWhite;
	DBAdvGlowButtonRecord->Caption = L"Record Osc";
	MakeRecordClicked(true);

//	if(in_rec_panel){
//		PanelRecord->BevelOuter =  bvRaised;
//	}
//	else{
//		PanelRecord->BevelOuter =  bvNone;
//	}
//	PanelPlayPuase->Width = Image2->Width + Label2->Width;
}
//---------------------------------------------------------------------------
void __fastcall ToscForm::CrossTimerTimer(TObject *Sender)
{
	if(mainForm->myCrossForm->created){
		int X;
		int Y;
		int Z;
	//		int T;

		X = 1000 * xx * pow10l(-1 * my_data_set[0].data_scale*3);
		Y = 1000 * yy * pow10l(-1 * my_data_set[1].data_scale*3);
		Z = 1000 * zz * pow10l(-1 * my_data_set[2].data_scale*3);
	//		T = 1000 * tt * pow10l(-1 * my_data_set[6].data_scale*3);

	//		if(!(abs(X) == 1000 && abs(Y) == 1000 && abs(Z) == 1000)){
			mainForm->myCrossForm->x = X;
			mainForm->myCrossForm->y = Y;
			mainForm->myCrossForm->z = Z;
			mainForm->myCrossForm->modified_cross();
	}
//	}
}
//---------------------------------------------------------------------------

UnicodeString ToscForm::FindUnit(TComboBox * combo)
{
	int index = combo->ItemIndex;

	if(index == -1)
		return "";
	else if(index == 0)
		return "V";
	else if(index == 1)
		return "A";
	else if(index == 2)
		return "Deg";
	else if(index == 3)
		return "m";
	return "";
}
//---------------------------------------------------------------------------

int ToscForm::FindScale(double data)
{
	double data_abs = abs(data);
	long double unit = 1;

	if(data_abs >= 1)
		return 0;
	else if( (data_abs < 1) && (data_abs >= unit * 0.001) )
		return 3;
	else if( (data_abs < unit * 0.001) && (data_abs >= unit * 0.000001) )
		return 6;
	else if( (data_abs < unit * 0.000001) && (data_abs >= unit * 0.000000001) )
		return 9;
	else if( (data_abs < unit * 0.000000001) && (data_abs >= unit * 0.000000000001) )
		return 12;
	else if( (data_abs < unit * 0.000000000001) && (data_abs >= unit * 0.000000000000001) )
		return 15;
	return 0;
}
//---------------------------------------------------------------------------

UnicodeString ToscForm::ShowUnit(int scale)
{
	if(scale == 0)
		return "";
	else if(scale == 3)
		return "m";
	else if(scale == 6)
		return "u";
	else if(scale == 9)
		return "n";
	else if(scale == 12)
		return "f";
	else if(scale == 15)
		return "p";
	return "";

}
//---------------------------------------------------------------------------

int ToscForm::returnScale(int index)
{
	return index * 3 ;
}
//---------------------------------------------------------------------------

UnicodeString ToscForm::FindData(TComboBox * combo)
{
//	if(combo->ItemIndex == -1)
//		return "";
//	else if(combo->ItemIndex == 0)
//		return "V";
//	else if(combo->ItemIndex == 1)
//		return "A";
//	else if(combo->ItemIndex == 2)
//		return "D";
//	else if(combo->ItemIndex == 3)
//		return "m";
	return "";
}
//---------------------------------------------------------------------------

void ToscForm::reSizePlot()
{
	oscChart1->Axes->Bottom->Items->Clear();
	oscChart2->Axes->Bottom->Items->Clear();
	oscChart3->Axes->Bottom->Items->Clear();
	oscChart4->Axes->Bottom->Items->Clear();

	current_time_dev_with = this->Width;
	current_time_dev_with =(double)current_time_dev_with/100;


	if(i_ChartCount == 1 || i_ChartCount == 2){
		current_time_dev_with = ((double)current_time_dev_with*100)/2 ;
	}
	else if(i_ChartCount == 4)
		current_time_dev_with = ((double)current_time_dev_with*100)/4 ;

	oscChart1->BottomAxis->SetMinMax(0,current_time_dev_with);
	oscChart2->BottomAxis->SetMinMax(0,current_time_dev_with);
	oscChart3->BottomAxis->SetMinMax(0,current_time_dev_with);
	oscChart4->BottomAxis->SetMinMax(0,current_time_dev_with);

	oscChart1->Axes->Bottom->Items->Automatic = false;
	oscChart2->Axes->Bottom->Items->Automatic = false;
	oscChart3->Axes->Bottom->Items->Automatic = false;
	oscChart4->Axes->Bottom->Items->Automatic = false;


	if(i_ChartCount == 1 || i_ChartCount == 2){
		if(ComboBox1->Position == 1){
			int len = (current_time_dev_with) / 100;
			for(int i=0; i< len; i++){
				oscChart1->Axes->Bottom->Items->Add( (i + 1) * 100, IntToStr((i + 1) * 1000 * 2  / 8) );
				oscChart2->Axes->Bottom->Items->Add( (i + 1) * 100, IntToStr((i + 1) * 1000 * 2  / 8) );
				oscChart3->Axes->Bottom->Items->Add( (i + 1) * 100, IntToStr((i + 1) * 1000 * 2  / 8) );
				oscChart4->Axes->Bottom->Items->Add( (i + 1) * 100, IntToStr((i + 1) * 1000 * 2  / 8) );
			}
		}
		else if(ComboBox1->Position == 2){
			int len = (current_time_dev_with) / 100;
			for(int i=0; i< len; i++){
				oscChart1->Axes->Bottom->Items->Add( (i + 1) * 100, IntToStr((i + 1) * 1000 * 2  / 4) );
				oscChart2->Axes->Bottom->Items->Add( (i + 1) * 100, IntToStr((i + 1) * 1000 * 2  / 4) );
				oscChart3->Axes->Bottom->Items->Add( (i + 1) * 100, IntToStr((i + 1) * 1000 * 2  / 4) );
				oscChart4->Axes->Bottom->Items->Add( (i + 1) * 100, IntToStr((i + 1) * 1000 * 2  / 4) );
			}
		}
		else if(ComboBox1->Position == 3){
			int len = (current_time_dev_with) / 100;
			for(int i=0; i< len; i++){
				oscChart1->Axes->Bottom->Items->Add( (i + 1) * 100, IntToStr((i + 1) * 1000 * 2  / 2) );
				oscChart2->Axes->Bottom->Items->Add( (i + 1) * 100, IntToStr((i + 1) * 1000 * 2  / 2) );
				oscChart3->Axes->Bottom->Items->Add( (i + 1) * 100, IntToStr((i + 1) * 1000 * 2  / 2) );
				oscChart4->Axes->Bottom->Items->Add( (i + 1) * 100, IntToStr((i + 1) * 1000 * 2  / 2) );
			}
		}
		else if(ComboBox1->Position == 4){
			int len = (current_time_dev_with) / 100;
			for(int i=0; i< len; i++){
				oscChart1->Axes->Bottom->Items->Add( (i + 1) * 100, IntToStr((i + 1) * 1000 * 2  / 1) );
				oscChart2->Axes->Bottom->Items->Add( (i + 1) * 100, IntToStr((i + 1) * 1000 * 2  / 1) );
				oscChart3->Axes->Bottom->Items->Add( (i + 1) * 100, IntToStr((i + 1) * 1000 * 2  / 1) );
				oscChart4->Axes->Bottom->Items->Add( (i + 1) * 100, IntToStr((i + 1) * 1000 * 2  / 1) );
			}
		}
	}
	else if(i_ChartCount == 4){
		if(ComboBox1->Position == 1){
			int len = (current_time_dev_with) / 100;
			for(int i=0; i< len; i++){
				oscChart1->Axes->Bottom->Items->Add( (i + 1) * 100, IntToStr((i + 1) * 1000 * 2  / 4) );
				oscChart2->Axes->Bottom->Items->Add( (i + 1) * 100, IntToStr((i + 1) * 1000 * 2  / 4) );
				oscChart3->Axes->Bottom->Items->Add( (i + 1) * 100, IntToStr((i + 1) * 1000 * 2  / 4) );
				oscChart4->Axes->Bottom->Items->Add( (i + 1) * 100, IntToStr((i + 1) * 1000 * 2  / 4) );
			}
		}
		else if(ComboBox1->Position == 2){
			int len = (current_time_dev_with) / 100;
			for(int i=0; i< len; i++){
				oscChart1->Axes->Bottom->Items->Add( (i + 1) * 100, IntToStr((i + 1) * 1000 * 2  / 2) );
				oscChart2->Axes->Bottom->Items->Add( (i + 1) * 100, IntToStr((i + 1) * 1000 * 2  / 2) );
				oscChart3->Axes->Bottom->Items->Add( (i + 1) * 100, IntToStr((i + 1) * 1000 * 2  / 2) );
				oscChart4->Axes->Bottom->Items->Add( (i + 1) * 100, IntToStr((i + 1) * 1000 * 2  / 2) );
			}
		}
		else if(ComboBox1->Position == 3){
			int len = (current_time_dev_with) / 100;
			for(int i=0; i< len; i++){
				oscChart1->Axes->Bottom->Items->Add( (i + 1) * 100, IntToStr((i + 1) * 1000 * 2  / 1) );
				oscChart2->Axes->Bottom->Items->Add( (i + 1) * 100, IntToStr((i + 1) * 1000 * 2  / 1) );
				oscChart3->Axes->Bottom->Items->Add( (i + 1) * 100, IntToStr((i + 1) * 1000 * 2  / 1) );
				oscChart4->Axes->Bottom->Items->Add( (i + 1) * 100, IntToStr((i + 1) * 1000 * 2  / 1) );
			}
		}
		else if(ComboBox1->Position == 4){
			int len = (current_time_dev_with) / 100;
			for(int i=0; i< len; i++){
				oscChart1->Axes->Bottom->Items->Add( (i + 1) * 100, IntToStr((i + 1) * 1000 * 2  * 2) );
				oscChart2->Axes->Bottom->Items->Add( (i + 1) * 100, IntToStr((i + 1) * 1000 * 2  * 2) );
				oscChart3->Axes->Bottom->Items->Add( (i + 1) * 100, IntToStr((i + 1) * 1000 * 2  * 2) );
				oscChart4->Axes->Bottom->Items->Add( (i + 1) * 100, IntToStr((i + 1) * 1000 * 2  * 2) );
			}
		}
	}

	oscChart1->Axes->Bottom->LabelsFormat->Color = clWhite;
	oscChart2->Axes->Bottom->LabelsFormat->Color = clWhite;
	oscChart3->Axes->Bottom->LabelsFormat->Color = clWhite;
	oscChart4->Axes->Bottom->LabelsFormat->Color = clWhite;
}
//---------------------------------------------------------------------------

void ToscForm::createComboUnit(int index, TComboBox *combo)
{
	combo->Clear();
	combo->Items->Add("  " + my_data_set[index].data_unit);
	combo->Items->Add(" m" + my_data_set[index].data_unit);
	combo->Items->Add(" u" + my_data_set[index].data_unit);
	combo->Items->Add(" n" + my_data_set[index].data_unit);
	combo->Items->Add(" p" + my_data_set[index].data_unit);
	combo->Items->Add(" f" + my_data_set[index].data_unit);
	combo->ItemIndex = my_data_set[index].data_scale;
}
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------

void ToscForm::DoMinMaxAvgChg(int plot_number,double myData)
{
	if(my_plot_set[plot_number].int_X == 0){
		 my_plot_set[plot_number].double_Max = myData;
		 my_plot_set[plot_number].double_Min = my_plot_set[plot_number].double_Max;
		 my_plot_set[plot_number].double_Sum = 0 ;
	}
	else
		my_plot_set[plot_number].double_Avg = (myData + my_plot_set[plot_number].double_Avg)/2;

	if(my_plot_set[plot_number].double_Min > myData)
		my_plot_set[plot_number].double_Min = myData;
	if(my_plot_set[plot_number].double_Max < myData)
		my_plot_set[plot_number].double_Max = myData;
	my_plot_set[plot_number].double_Chg = my_plot_set[plot_number].double_Max - my_plot_set[plot_number].double_Min;
}
//---------------------------------------------------------------------------

void ToscForm::DoChgAvgLabel(int scale,int plot_number)
{
	if(my_plot_set[plot_number].Counter % 5 == 0){
        //	if(scale != 0){
	//		my_plot_set[plot_number].double_Chg = pow10l(scale) * my_plot_set[plot_number].double_Chg;
	//	}
	my_plot_set[plot_number].calclabel_ChgValue->Text = FormatFloat("#0.0##",my_plot_set[plot_number].double_Chg) + my_plot_set[plot_number].combo_unit->Text;

//	if(scale != 0)
//		my_plot_set[plot_number].double_Avg = pow10l(scale) * my_plot_set[plot_number].double_Avg;
	my_plot_set[plot_number].calclabel_AvgValue->Text = FormatFloat("#0.0#",my_plot_set[plot_number].double_Avg) + my_plot_set[plot_number].combo_unit->Text;

	}
	my_plot_set[plot_number].Counter++;

}
//---------------------------------------------------------------------------

void ToscForm::ChangeCombo(int plot_number)
{
	int tmp = my_plot_set[plot_number].combo_WaveName->ItemIndex;
//	mainForm->LogToFile("tmp = " + IntToStr(tmp));
	bool bChanged = true;
	if(plot_number == 0){
		if( (tmp == my_plot_set[0].int_WaveIndex) ||
			(tmp == my_plot_set[1].int_WaveIndex) ||
			(tmp == my_plot_set[2].int_WaveIndex) ||
			 (tmp == my_plot_set[3].int_WaveIndex)){
				my_plot_set[0].combo_WaveName->ItemIndex = my_plot_set[0].int_WaveIndex;
				bChanged = false ;
		}
	}
	else if(plot_number == 1){
		if( (tmp == my_plot_set[0].int_WaveIndex) ||
			(tmp == my_plot_set[1].int_WaveIndex) ||
			(tmp == my_plot_set[2].int_WaveIndex) ||
			(tmp == my_plot_set[3].int_WaveIndex)){
				my_plot_set[1].combo_WaveName->ItemIndex = my_plot_set[1].int_WaveIndex;
				bChanged = false ;
		}
	}
	else if(plot_number == 2){
		if( (tmp == my_plot_set[0].int_WaveIndex) ||
			(tmp == my_plot_set[1].int_WaveIndex) ||
			(tmp == my_plot_set[2].int_WaveIndex) ||
			(tmp == my_plot_set[3].int_WaveIndex)){
				my_plot_set[2].combo_WaveName->ItemIndex = my_plot_set[2].int_WaveIndex;
				bChanged = false ;
		}
	}
	else if(plot_number == 3){
		if( (tmp == my_plot_set[0].int_WaveIndex) ||
			(tmp == my_plot_set[1].int_WaveIndex) ||
			(tmp == my_plot_set[2].int_WaveIndex) ||
			(tmp == my_plot_set[3].int_WaveIndex)){
				my_plot_set[3].combo_WaveName->ItemIndex = my_plot_set[3].int_WaveIndex;
				bChanged = false ;
		}
	}

	if(bChanged){
		my_plot_set[plot_number].int_WaveIndex = tmp;
		my_plot_set[plot_number].combo_WaveName->ItemIndex = tmp;
		my_plot_set[plot_number].double_Avg = 0;
		my_plot_set[plot_number].double_Chg = 0;
		my_plot_set[plot_number].double_Max = 0;
		my_plot_set[plot_number].double_Min = 0;
		my_plot_set[plot_number].double_Sum = 0;
		for(int i=0; i<4 ; i++){
			my_plot_set[i].fastlineseries_Series->Clear();
			my_plot_set[i].chart_Chart->Tag = 0;
			firstPlot = 0;
			my_plot_set[i].int_X = 0;


		}
		createComboUnit(tmp,my_plot_set[plot_number].combo_unit);
	}
}
//---------------------------------------------------------------------------

void ToscForm::changeAllSampleRate(int time)
{
	if(i_ChartCount == 1 || i_ChartCount == 2){
        for(int i=0; i<27; i++)
		if(time == 1)
			data_queue[i].ChangeSampleRate(16);
		else if(time == 2)
			data_queue[i].ChangeSampleRate(8);
		else if(time == 3)
			data_queue[i].ChangeSampleRate(4);
		else if(time == 4)
			data_queue[i].ChangeSampleRate(2);
	}
	else if(i_ChartCount == 4){
		for(int i=0; i<27; i++)
		if(time == 1)
			data_queue[i].ChangeSampleRate(8);
		else if(time == 2)
			data_queue[i].ChangeSampleRate(4);
		else if(time == 3)
			data_queue[i].ChangeSampleRate(2);
		else if(time == 4)
			data_queue[i].ChangeSampleRate(1);
	}

}
//---------------------------------------------------------------------------

void __fastcall ToscForm::TimerRecCounterTimer(TObject *Sender)
{
	TDateTime NOWDIF = START - Now();
	DBAdvGlowButtonRecord->Caption = L"Recording " + NOWDIF.FormatString("ss")+  L" sec";
//	PanelPlayPuase->Width = Image2->Width + Label2->Width;
}
//---------------------------------------------------------------------------

void __fastcall ToscForm::p1ComboBoxSelect(TObject *Sender)
{
	ChangeCombo(0);
	SaveOscConfig();

	p1ComboBox->Refresh();
}
//---------------------------------------------------------------------------

void __fastcall ToscForm::p2ComboBoxSelect(TObject *Sender)
{
	ChangeCombo(1);
	SaveOscConfig();

	p2ComboBox->Refresh();
}
//---------------------------------------------------------------------------

void __fastcall ToscForm::p3ComboBoxSelect(TObject *Sender)
{
	ChangeCombo(2);
	SaveOscConfig();

	p3ComboBox->Refresh();
}
//---------------------------------------------------------------------------

void __fastcall ToscForm::p4ComboBoxSelect(TObject *Sender)
{
	ChangeCombo(3);
	SaveOscConfig();

	p4ComboBox->Refresh();
}
//---------------------------------------------------------------------------

void __fastcall ToscForm::SendPacket()
{
	mainForm->myUdpThread->SendBytes();
}
//---------------------------------------------------------------------------

void ToscForm::SaveOscConfig()
{
	if(firstSave){

//		mainForm->LogToFile("SaveOscConfig : osc1_index = " + IntToStr(my_plot_set[0].int_WaveIndex));
//		mainForm->LogToFile("SaveOscConfig : osc2_index = " + IntToStr(my_plot_set[1].int_WaveIndex));
//		mainForm->LogToFile("SaveOscConfig : osc3_index = " + IntToStr(my_plot_set[2].int_WaveIndex));
//		mainForm->LogToFile("SaveOscConfig : osc4_index = " + IntToStr(my_plot_set[3].int_WaveIndex));
//		mainForm->LogToFile("SaveOscConfig : timedev = " + IntToStr(ComboBox1->Position));
		OscChartTable.osc1 = my_plot_set[0].int_WaveIndex;
		OscChartTable.osc2 = my_plot_set[1].int_WaveIndex;
		OscChartTable.osc3 = my_plot_set[2].int_WaveIndex;
		OscChartTable.osc4 = my_plot_set[3].int_WaveIndex;
		OscChartTable.timedev = ComboBox1->Position;
		mainForm->myDataBase->Execute(mainForm->myDataBase->myQuery->Update("OSC_CHART_CONFIG"));
	}
	else
		firstSave = true;
}
//---------------------------------------------------------------------------

void ToscForm::LoadOscConfig()
{



	int osc1_index = OscChartTable.osc1;
	int osc2_index = OscChartTable.osc2;
	int osc3_index = OscChartTable.osc3;
	int osc4_index = OscChartTable.osc4;
	int timedev = OscChartTable.timedev;


//	mainForm->LogToFile("LoadOscConfig : osc1_index = " + IntToStr(osc1_index));
//	mainForm->LogToFile("LoadOscConfig : osc2_index = " + IntToStr(osc2_index));
//	mainForm->LogToFile("LoadOscConfig : osc3_index = " + IntToStr(osc3_index));
//	mainForm->LogToFile("LoadOscConfig : osc4_index = " + IntToStr(osc4_index));
//	mainForm->LogToFile("LoadOscConfig : timedev = " + IntToStr(timedev));

	if(osc1_index < 0 || osc1_index > 26) osc1_index = 0;
	if(osc2_index < 0 || osc2_index > 26) osc2_index = -1;
	if(osc3_index < 0 || osc3_index > 26) osc3_index = -1;
	if(osc4_index < 0 || osc4_index > 26) osc4_index = -1;

//	mainForm->LogToFile("LoadOscConfig : osc1_index after modification1 = " + IntToStr(osc1_index));
//	mainForm->LogToFile("LoadOscConfig : osc2_index after modification1 = " + IntToStr(osc2_index));
//	mainForm->LogToFile("LoadOscConfig : osc3_index after modification1 = " + IntToStr(osc3_index));
//	mainForm->LogToFile("LoadOscConfig : osc4_index after modification1 = " + IntToStr(osc4_index));

	if(timedev > 4 || timedev < 0)
		timedev = 4;

	if( ( (osc1_index >= 0) && (osc1_index == osc2_index) ) || ( (osc1_index >= 0) && (osc1_index == osc3_index) ) || ( (osc1_index >= 0) && (osc1_index == osc4_index) ) ){
		mainForm->LogToFile("LoadOscConfig : fault 1");
		osc1_index = 0;
		osc2_index = -1;
		osc3_index = -1;
		osc4_index = -1;
	}
//	mainForm->LogToFile("LoadOscConfig : osc1_index after modification2 = " + IntToStr(osc1_index));
//	mainForm->LogToFile("LoadOscConfig : osc2_index after modification2 = " + IntToStr(osc2_index));
//	mainForm->LogToFile("LoadOscConfig : osc3_index after modification2 = " + IntToStr(osc3_index));
//	mainForm->LogToFile("LoadOscConfig : osc4_index after modification2 = " + IntToStr(osc4_index));

	if( ( (osc2_index >= 0) && (osc2_index == osc3_index) ) || ( (osc2_index >= 0) && (osc2_index == osc4_index) ) ){
		mainForm->LogToFile("LoadOscConfig : fault 2");
		osc1_index = 0;
		osc2_index = -1;
		osc3_index = -1;
		osc4_index = -1;
	}
//	mainForm->LogToFile("LoadOscConfig : osc1_index after modification3 = " + IntToStr(osc1_index));
//	mainForm->LogToFile("LoadOscConfig : osc2_index after modification3 = " + IntToStr(osc2_index));
//	mainForm->LogToFile("LoadOscConfig : osc3_index after modification3 = " + IntToStr(osc3_index));
//	mainForm->LogToFile("LoadOscConfig : osc4_index after modification3 = " + IntToStr(osc4_index));

	if( ( (osc3_index >= 0) && (osc3_index == osc4_index) ) ){
		mainForm->LogToFile("LoadOscConfig : fault 3");
		osc1_index = 0;
		osc2_index = -1;
		osc3_index = -1;
		osc4_index = -1;
	}
//	mainForm->LogToFile("LoadOscConfig : osc1_index after modification = " + IntToStr(osc1_index));
//	mainForm->LogToFile("LoadOscConfig : osc2_index after modification = " + IntToStr(osc2_index));
//	mainForm->LogToFile("LoadOscConfig : osc3_index after modification = " + IntToStr(osc3_index));
//	mainForm->LogToFile("LoadOscConfig : osc4_index after modification = " + IntToStr(osc4_index));

	int counter = 0;
	if(osc1_index != -1)
		counter++;
	if(osc2_index != -1)
		counter++;
	if(osc3_index != -1)
		counter++;
	if(osc4_index != -1)
		counter++;

	if(counter == 3)
		counter = 4;

	i_ChartCount = counter;
	ComboBox1->Position = timedev;

	LabelAddSubEdit->Caption = IntToStr(i_ChartCount);

	my_plot_set[0].int_WaveIndex = osc1_index;
	my_plot_set[1].int_WaveIndex = osc2_index;
	my_plot_set[2].int_WaveIndex = osc3_index;
	my_plot_set[3].int_WaveIndex = osc4_index;

	SaveOscConfig();

//	mainForm->LogToFile("LoadOscConfig : my_plot_set[0].int_WaveIndex = " + IntToStr(my_plot_set[0].int_WaveIndex));
//	mainForm->LogToFile("LoadOscConfig : my_plot_set[1].int_WaveIndex = " + IntToStr(my_plot_set[1].int_WaveIndex));
//	mainForm->LogToFile("LoadOscConfig : my_plot_set[2].int_WaveIndex = " + IntToStr(my_plot_set[2].int_WaveIndex));
//	mainForm->LogToFile("LoadOscConfig : my_plot_set[3].int_WaveIndex = " + IntToStr(my_plot_set[3].int_WaveIndex));

	first = true;
	ComboBox1Change(NULL);
	showChart_Panels(i_ChartCount);

	p1ComboBox->ItemIndex = my_plot_set[0].int_WaveIndex;
	p2ComboBox->ItemIndex = my_plot_set[1].int_WaveIndex;
	p3ComboBox->ItemIndex = my_plot_set[2].int_WaveIndex;
	p4ComboBox->ItemIndex = my_plot_set[3].int_WaveIndex;
}
//---------------------------------------------------------------------------

void __fastcall ToscForm::FormShow(TObject *Sender)
{
	PanelBot->Height = this->Height/13;

	if(PanelBot->Height < 40)
		PanelBot->Height = 40;


	PanelAddSub->Width = (PanelBot->Width/13) * 2;
//	DBAdvGlowButtonSub->Width = PanelAddSub->Height;
//	DBAdvGlowButtonAdd->Width = PanelAddSub->Height;

	PanelPlayPuase->Width = (PanelBot->Width/13) * 3;
	DBAdvGlowButtonPalyPause->Width = PanelPlayPuase->Width/2;
	DBAdvGlowButtonPalyPause->Height = PanelPlayPuase->Height;
	DBAdvGlowButtonPalyPause->Top = 0;
	DBAdvGlowButtonPalyPause->Left = PanelPlayPuase->Width/2 - DBAdvGlowButtonPalyPause->Width/2;

	PanelTimeDev->Width = (PanelBot->Width/13) * 5;

	PanelRecord->Width = (PanelBot->Width/13) * 3;
	DBAdvGlowButtonRecord->Width = PanelRecord->Width/2;
	DBAdvGlowButtonRecord->Height = PanelRecord->Height;
	DBAdvGlowButtonRecord->Top = 0;
	DBAdvGlowButtonRecord->Left = PanelRecord->Width/2 - DBAdvGlowButtonRecord->Width/2;

	AdvEdit5->Width = (PanelTimeDev->Width/4) * 1;
	ComboBox1->Width = (PanelTimeDev->Width/4) * 3 - 20;


	paly_pause = true;
	DBAdvGlowButtonPalyPause->Picture->Width = DBAdvGlowButtonPalyPause->Picture->Height;
	DBAdvGlowButtonPalyPause->Picture = PausePic;
	DBAdvGlowButtonPalyPause->Font->Color = clWhite;
	DBAdvGlowButtonPalyPause->Caption = "Pause Osc";
	paly_pause = true;
	PanelPlayPuase->BevelOuter = bvNone;


	DBAdvGlowButtonRecord->Picture = RecPic;
	DBAdvGlowButtonRecord->Picture->Width = DBAdvGlowButtonPalyPause->Picture->Height;
	DBAdvGlowButtonRecord->Font->Color = clWhite;
	DBAdvGlowButtonRecord->Caption = L"Record Osc";
	enabled_rec = true;
}
//---------------------------------------------------------------------------




void __fastcall ToscForm::OffTimerTimer(TObject *Sender)
{
	pOffButClick(NULL);
}
//---------------------------------------------------------------------------

void __fastcall ToscForm::piezoTimerTimer(TObject *Sender)
{
	mainForm->myPiezoFrom->ModifyPiezo(TOPO);
}
//---------------------------------------------------------------------------

