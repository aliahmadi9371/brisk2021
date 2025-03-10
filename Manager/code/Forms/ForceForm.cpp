//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "ForceForm.h"
#include "mainUnit.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "AdvGlassButton"
#pragma link "AdvGlowButton"
#pragma link "AdvPanel"
#pragma link "AdvWiiProgressBar"
#pragma link "CurvyControls"
#pragma link "VCLTee.TeeTools"
#pragma link "VCLTee.TeeComma"
#pragma link "VCLTee.TeeEdit"
#pragma link "htmlbtns"
#pragma resource "*.dfm"
TForceFrm *ForceFrm;
//---------------------------------------------------------------------------
__fastcall TForceFrm::TForceFrm(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TForceFrm::FormCreate(TObject *Sender)
{
	this->Hide();
	first = false;
	InitValues();

	myChartForm = new TForceChartForm(this);
}
//---------------------------------------------------------------------------

void TForceFrm::InitValues()
{
	StartX = 0;
	StartY = 0;

	dZ1 = 0;
	dZ2 = 0;

	U1 = 0;
	U2 = 0;

	Resolution = 0;
	ResolutionIndex = 0;

	CurrentZ = -1;
	CurrentU = -1;

	DelayNumber = 10;

	FsBtnState = 0;

	XInverted = false;




}
//---------------------------------------------------------------------------

void __fastcall TForceFrm::FormShow(TObject *Sender)
{
	if(!first){

		int w_this = mainForm->myMainControlPanelForm->MainPanel->Width;
		int h_this = mainForm->myMainControlPanelForm->MainPanel->Height;


		PanelSubFs->Height = h_this - 40;
		PanelSubFs->Width = w_this - 40;
		PanelSubFs->Left = 20;
		PanelSubFs->Top = 20;

		int Height = PanelSubFs->Height - PanelLabelFs->Height;

		ChartPanel->Height = (Height * 6/(double)12);

		ShowLables(-1);
		PickSeries(-1);
		first = true;

		ConfigClass();

		SetupChart();

		Panel10->Top = ChartPicker->Top;
		Panel10->Left = ChartPicker->Left - Panel10->Width;
		Panel10->BringToFront();

//		Panel11->Top = ChartChart->Top;
//		Panel11->Left = ChartChart->Left + 150;
		UnitLabel->Top = ChartChart->Top;
		UnitLabel->Left = 130;
		RadioButtonUnitZ->Top = UnitLabel->Top + 3;
		RadioButtonUnitZ->Left = UnitLabel->Left + UnitLabel->Width + 10;
		RadioButtonUnitTime->Top = RadioButtonUnitZ->Top;
		RadioButtonUnitTime->Left = RadioButtonUnitZ->Left + RadioButtonUnitZ->Width + 10 ;

		myChartForm->Height = mainForm->Height - 20;
		myChartForm->Width = mainForm->Height - 20;
		myChartForm->Top = mainForm->Height/2 - myChartForm->Height/2;
		myChartForm->Left = mainForm->Width/2 - myChartForm->Width/2;
		ForceStartTimer->Enabled = false;

//		PanelChartPicker->Hide();
	}
}
//---------------------------------------------------------------------------

void TForceFrm::SetupChart()
{
//	ChartChart->ScrollMouseButton = mbRight;
//	ChartChart->ClipPoints = false;
//	ChartChart ->Legend->Visible = false;
//	ChartChart->LeftAxis->Automatic = true;
//	ChartChart->LeftAxis->Axis->Width = 1;
//	ChartChart->BottomAxis->Axis->Width = 1;
//	ChartChart->BottomAxis->RoundFirstLabel = false;
//	ChartChart->BottomAxis->Automatic = false;
//	ChartChart->View3D = false;
//	ChartChart->Axes->FastCalc = true;
//	ChartChart->Canvas->ReferenceCanvas->Pen->OwnerCriticalSection = NULL;
//	ChartChart->Hover->Visible = false;




	TeeCommander1->ButtonZoom->Hide();
	TeeCommander1->Button3D->Hide();
	TeeCommander1->ButtonDepth->Hide();
	TeeCommander1->ButtonMove->Hide();
	TeeCommander1->ButtonNormal->Hide();
	TeeCommander1->ButtonZoom->Hide();
	TeeCommander1->ButtonPrint->Hide();
	TeeCommander1->ButtonRotate->Hide();

	TeeCommander1->ButtonSave->Align = alTop;
	TeeCommander1->ButtonCopy->Align = alTop;
	TeeCommander1->ButtonEdit->Align = alTop;

//	TeeCommander1->Align = alNone;
//	TeeCommander1->Height = 3 * TeeCommander1->ButtonSave->Height;
}
//---------------------------------------------------------------------------

void TForceFrm::ConfigClass()
{

    Max_Range = HardwareTable.Max_Range;
	StartX = ForceTable.Force_StartX_Val;

	if(StartX > Max_Range/2) StartX = Max_Range/2;
	if(StartX < -Max_Range/2) StartX = -Max_Range/2;

	StartY = ForceTable.Force_StartY_Val;

	if(StartY > Max_Range/2) StartY = Max_Range/2;
	if(StartY < -Max_Range/2) StartY = -Max_Range/2;


	dZ1 = ForceTable.Force_Z1_Val;

//	if(Z1 > 100){ Z1 = 100; iniFile->WriteInteger("FORCE_CONFIG","Force_Z1_Val",Z1);}
//	if(Z1 < 0 ){ Z1 = 0; iniFile->WriteInteger("FORCE_CONFIG","Force_Z1_Val",Z1);}

	dZ2 = ForceTable.Force_Z2_Val;
//	if(Z2 > 100){ Z2 = 100; iniFile->WriteInteger("FORCE_CONFIG","Force_Z2_Val",StartY);}
//	if(Z2 < 0 ){ Z2 = 0; iniFile->WriteInteger("FORCE_CONFIG","Force_Z2_Val",StartY);}

	U1 = ForceTable.Force_U1_Val;
	U2 = ForceTable.Force_U2_Val;

	DelayNumber = ForceTable.Force_Delay_Val;
	if(DelayNumber < 0 ){
		DelayNumber = 0;
		ForceTable.Force_Delay_Val = DelayNumber;

	}
	Delay = (DelayNumber * 1000) / (double)25; //25 ns is shortest delay time

	ResolutionIndex = ForceTable.Force_Resolution_Index;
	if(ResolutionIndex < 0 )
	{
		ResolutionIndex = 0;
		ForceTable.Force_Resolution_Index = ResolutionIndex;
	}
	if(ResolutionIndex > 5 )
	{
		 ResolutionIndex = 5;
		 ForceTable.Force_Resolution_Index = ResolutionIndex;
	}
	Resolution = GetResolution(ResolutionIndex);

	ModesIndex = ForceTable.Force_Mode_Index;
	if(ModesIndex < 0 )
	{
		 ModesIndex = 0;
		 ForceTable.Force_Mode_Index = ModesIndex;
	}
	if(ModesIndex > 7 )
	{
		 ForceTable.Force_Mode_Index = ModesIndex;
	}
	Mode = ModesIndex + 1;
	EnabledPanels(Mode);



	index = OscTable[3].index;
	scale = OscTable[3].scale;
	U_index = OscTable[17].index;
	U_Scale = OscTable[17].scale;

	Fs_C_Factor = ForceTable.TB_C_Factor;

	CFactorEdit->Text = FloatToStr(Fs_C_Factor);

	XAdvEdit->Text = FloatToStr(StartX);
	YAdvEdit->Text = FloatToStr(StartY);
	DelayAdvEdit->Text = IntToStr(DelayNumber);

	U1AdvEdit->Text = IntToStr(U1);
	U2AdvEdit->Text = IntToStr(U2);

	if(AllScale){
		Z1AdvEdit->Text = FloatToStr(dZ1);
		Z2AdvEdit->Text = FloatToStr(dZ2);
	}

	ModesAdvComboBox->ItemIndex = ModesIndex;
	ResAdvComboBox->ItemIndex = ResolutionIndex;

	U1 = U1 / ( pow10l(U_Scale*3) * U_index);
	U2 = U2 / ( pow10l(U_Scale*3) * U_index);

	dZ1 = -(int)( dZ1 / ( pow10l(scale*3) * index * 1000));
	dZ2 = -(int)( dZ2 / ( pow10l(scale*3) * index * 1000));
	checkPermission();
	X_Calibration();
	Y_Calibration();

	if(!AllScale){
		XAdvEditLbl->Caption = "X (%)";
		YAdvEditLbl->Caption = "Y (%)";
		Z1AdvEditLbl->Caption = "dZ1";
		Z2AdvEditLbl->Caption = "dZ2";
		U1AdvEditLbl->Caption = "U1";
		U2AdvEditLbl->Caption = "U2";
		Z1AdvEdit->Text = FloatToStr(-dZ1);
		Z2AdvEdit->Text = FloatToStr(-dZ2);
        XAdvEdit->Text = FloatToStr(StartX);
		YAdvEdit->Text = FloatToStr(StartY);
		U1AdvEdit->Text = FloatToStr(U1);
		U2AdvEdit->Text = FloatToStr(U2);
	}
	else{
		XAdvEditLbl->Caption = "X (�m)";
		YAdvEditLbl->Caption = "Y (�m)";
		Z1AdvEditLbl->Caption = "dZ1 (nm)";
		Z2AdvEditLbl->Caption = "dZ2 (nm)";
		U1AdvEditLbl->Caption = "U1 (mV)";
		U2AdvEditLbl->Caption = "U2 (mV)";
    }

	mainForm->myDataBase->Execute(mainForm->myDataBase->myQuery->Update("FORCE_CONFIG"));

	AllEditWhite();
}
//---------------------------------------------------------------------------

int TForceFrm::GetResolution(int res_index)
{
	mainForm->LogToFile("TForceFrm::GetResolution");
	int Resolution = 0;
	switch(res_index){
		case 0:{
		 //64
			Resolution = 64;
			break;
		}
		case 1:{
		//128
			Resolution = 128;
			break;
		}
		case 2:{
		//256
			Resolution = 256;
			break;
		}
		case 3:{
		 //512
			Resolution = 512;
			break;
		}
		case 4:{
		//1024
			Resolution = 1024;
			break;
		}
		case 5:{
		//2048
			Resolution = 2048;
			break;
		}
		default:{
			Resolution = 64;
			break;
		}
	}
	return Resolution;
}
//---------------------------------------------------------------------------

void TForceFrm::GetCurrentZ()
{
	mainForm->LogToFile("TForceFrm::GetCurrentZ : CurrentZ = " + IntToStr(CurrentZ));
//	CurrentZ = mainForm->myPiezoFrom->LastTmpZ;
}
//---------------------------------------------------------------------------

void TForceFrm::GetCurrentU()
{
	mainForm->LogToFile("TForceFrm::GetCurrentU : CurrentU = " + IntToStr(CurrentU));
//	CurrentU = mainForm->myPiezoFrom->LastTmpU;
}
//---------------------------------------------------------------------------

bool TForceFrm::checkPermission()
{
	mainForm->LogToFile("TForceFrm::checkPermission");
	bool done = true;
//	mainForm->LogToFile("CurrentZ : " + IntToStr(CurrentZ));
//	mainForm->LogToFile("dZ1 : " + FloatToStr(dZ1));
//	mainForm->LogToFile("dZ2 : " + FloatToStr(dZ2));
//	mainForm->LogToFile("CurrentZ + dZ1 : " + FloatToStr(CurrentZ + dZ1));
//	mainForm->LogToFile("CurrentZ + dZ1 + dZ2 : " + FloatToStr(CurrentZ + dZ1 + dZ2));
	if(CurrentZ < -8388608 || CurrentZ > 8388608)
		done = false;

	if( (CurrentZ + dZ1) < -8388608 || (CurrentZ + dZ1) > 8388608 )
        done = false;

	if( (CurrentZ + dZ1 + dZ2) < -8388608 || (CurrentZ + dZ1 + dZ2) > 8388608 )
		done = false;

	if(done){
		if(Z1AdvEdit->Color == clRed)
			Z1AdvEdit->Color = clWhite;
		if(Z2AdvEdit->Color == clRed)
			Z2AdvEdit->Color = clWhite;
	}
	else{
		Z1AdvEdit->Color = clRed;
		Z2AdvEdit->Color = clRed;
	}

	mainForm->LogToFile("TForceFrm::checkPermission = " + BoolToStr(done,true));
	return done;
}
//---------------------------------------------------------------------------

void TForceFrm::SetFolderNames()
{
	mainForm->LogToFile("TForceFrm::SetFolderNames");
	TDateTime dateTime;
	UnicodeString time = dateTime.CurrentDateTime().FormatString("hhMMss");
	UnicodeString date = dateTime.CurrentDateTime().FormatString("yyyymmdd");

	FsFolder = "force";
	DateFolder = date;
	TimeFolder = time;
}
//---------------------------------------------------------------------------

void __fastcall TForceFrm::RunAdvGlassButtonClick(TObject *Sender)
{
//	AllEditWhite();
	ClearSeries();

	SetFolderNames();

//	StartX =  XAdvEdit->Text.ToInt();
//	StartY =  YAdvEdit->Text.ToInt();

//	DelayNumber = DelayAdvEdit->Text.ToInt();
//	Delay = (DelayNumber * 1000) / (double)25; //25 ns is shortest delay time

//	Mode = ModesIndex + 1;
//	Resolution = GetResolution(ResolutionIndex);
//	U1 = U1AdvEdit->Text.ToInt();
//	U2 = U2AdvEdit->Text.ToInt();
//	dZ1 = Z1AdvEdit->Text.ToInt();
//	dZ2 = Z2AdvEdit->Text.ToInt();

	Start_Topo = dZ1;
	Finaldz = dZ2;

	Start_U = CurrentU + U1;
	FinalU = U2 - U1;

	FinalMode = Mode;
    FinalResolution = Resolution;
	if(Mode == 1 || Mode == 4 || Mode == 5){
		RadioButtonUnitZ->Caption = "Z";
	}
	else{
		RadioButtonUnitZ->Caption = "U";
	}

	if(checkPermission()){
		if(FsBtnState == 0 && (hid == mainForm->myUniKey->FindDongle())){
			mainForm->Forcing = true;
			mainForm->GetSecure();
			mainForm->LogToFile("ForceFrm : RunAdvGlassButtonClick : start force spectroscopy");
			EnableFsPanel(2);
			mainForm->myImageFrom->PaintBox1->Enabled = false;
			ChartPicker->Enabled = false;
			TThread::Synchronize(mainForm->myCommandCreatorThread,StartFs);

		}
		else if(FsBtnState == 1){
			EnableFsPanel(0);
            mainForm->Forcing = false;
			mainForm->GetSecure();
            mainForm->LogToFile("ForceFrm : RunAdvGlassButtonClick : stop force spectroscopy");
			ChartPicker->Enabled = true;
			mainForm->myImageFrom->PaintBox1->Enabled = true;
			TThread::Synchronize(mainForm->myCommandCreatorThread,StopFs);
		}
	}
}
//---------------------------------------------------------------------------

void __fastcall TForceFrm::StartFs()
{
	mainForm->LogToFile("TForceFrm::StartFs");
	mainForm->myTcpThread->fs_set = true;
	EnableFsPanel(1);

	FsCommand.start = false;
	FsCommand.startx = StartX;
	FsCommand.starty = StartY;
	FsCommand.resolution = Resolution;
	FsCommand.delay = Delay;
	FsCommand.mode = Mode;
	FsCommand.GOTO = 1;
	FsCommand.dz1 = 0;
	FsCommand.dz2 = 0;
	FsCommand.u1 = 0;
	FsCommand.u2 = 0;
	FsCommand.currentZ = CurrentZ;
	FsCommand.currentU = CurrentU;
	mainForm->myCommandCreatorThread->force_file = true;

//	mainForm->myCommandCreatorThread->StartStopFsClick(true, StartX, StartY, Resolution, Delay, Mode, 1, 0, 0, 0, 0, CurrentZ, CurrentU);
	while(!mainForm->myUdpThread->fs_GoTo_set){
		Application->ProcessMessages();
	}
    EnableFsPanel(2);
	ForceStartTimer->Enabled = true;

//	if(checkPermission()){
//		ForceStartTimerTimer(NULL);
//	}


}
//---------------------------------------------------------------------------


void __fastcall TForceFrm::ForceStartTimerTimer(TObject *Sender)
{

	mainForm->LogToFile("TForceFrm::ForceStartTimerTimer");
	ForceStartTimer->Enabled = false;
	mainForm->myTcpThread->fs_set = false;
//	EnableFsPanel(2);
	FsCommand.start = true;
	FsCommand.startx = StartX;
	FsCommand.starty = StartY;
	FsCommand.resolution = Resolution;
	FsCommand.delay = Delay;
	FsCommand.mode = Mode;
	FsCommand.GOTO = 0;
	FsCommand.dz1 = dZ1;
	FsCommand.dz2 = dZ2;
	FsCommand.u1 = U1;
	FsCommand.u2 = U2;
	FsCommand.currentZ = CurrentZ;
	FsCommand.currentU = CurrentU;
	mainForm->myCommandCreatorThread->force_file = true;
//	mainForm->myCommandCreatorThread->StartStopFsClick(true, StartX, StartY, Resolution, Delay, Mode, 1, dZ1, dZ2, U1, U2, CurrentZ, CurrentU);
//	EnableFsPanel(0);
}
//---------------------------------------------------------------------------

void __fastcall TForceFrm::StopFs()
{
	mainForm->LogToFile("TForceFrm::StopFs");
	mainForm->myDataBase->Execute(mainForm->myDataBase->myQuery->Update("FORCE_CONFIG"));
	mainForm->myTcpThread->fs_set = true;
	EnableFsPanel(2);
	FsCommand.start = false;
	FsCommand.startx = StartX;
	FsCommand.starty = StartY;
	FsCommand.resolution = Resolution;
	FsCommand.delay = Delay;
	FsCommand.mode = Mode;
	FsCommand.GOTO = 0;
	FsCommand.dz1 = dZ1;
	FsCommand.dz2 = dZ2;
	FsCommand.u1 = U1;
	FsCommand.u2 = U2;
	FsCommand.currentZ = CurrentZ;
	FsCommand.currentU = CurrentU;
	mainForm->myCommandCreatorThread->force_file = true;
//	mainForm->myCommandCreatorThread->StartStopFsClick(false, StartX, StartY, Resolution, Delay, Mode, 0, dZ1, dZ2, U1, U2, CurrentZ, CurrentU);
	EnableFsPanel(0);
}
//---------------------------------------------------------------------------

void __fastcall TForceFrm::XAdvEditKeyPress(TObject *Sender, System::WideChar &Key)

{
	if(Key == VK_RETURN){
		mainForm->LogToFile("TForceFrm::XAdvEditKeyPress");
		Key = 0;
//		AllEditWhite();
		XAdvEdit->Color = clWhite;
		StartX =  XAdvEdit->Text.ToDouble();
		if(AllScale){
			if(StartX < -Max_Range/2) StartX = -Max_Range/2;
			if(StartX > Max_Range/2) StartX = Max_Range/2;

			if(StartX<10 && StartX>-10){
				int X = StartX*1000;
				StartX = (double)X/1000;
			}

			XAdvEdit->Text = FloatToStr(StartX);
			XAdvEdit->Color = clWhite;

			ForceTable.Force_StartX_Val = StartX;

			X_Calibration();
		}
		else{
			if(StartX>100) StartX = 100;
			if(StartX<0) StartX = 0;

			if(StartX<10 && StartX>-10){
				int X = StartX*1000;
				StartX = (double)X/1000;
			}

			XAdvEdit->Text = FloatToStr(StartX);
			XAdvEdit->Color = clWhite;

			ForceTable.Force_StartX_Val = Reverse_X_Calibration();

		}

		mainForm->Forcing = false;
//		mainForm->GetSecure();
//		TThread::Synchronize(mainForm->myCommandCreatorThread,StopFs);

		if(checkPermission()){
			TThread::Synchronize(mainForm->myCommandCreatorThread,StopFs);
		}
	}
}
//---------------------------------------------------------------------------

void __fastcall TForceFrm::YAdvEditKeyPress(TObject *Sender, System::WideChar &Key)

{
	if(Key == VK_RETURN){
		mainForm->LogToFile("TForceFrm::YAdvEditKeyPress");
        Key = 0;
//		AllEditWhite();
		YAdvEdit->Color = clWhite;
		StartY =  YAdvEdit->Text.ToDouble();
		if(AllScale){
			if(StartY < -Max_Range/2) StartY = -Max_Range/2;
			if(StartY > Max_Range/2) StartY = Max_Range/2;

			if(StartY<10 && StartY>-10){
				int Y = StartY*1000;
				StartY = (double)Y/1000;
			}

			YAdvEdit->Text = FloatToStr(StartY);
			YAdvEdit->Color = clWhite;

			ForceTable.Force_StartY_Val = StartY;

			Y_Calibration();
		}
		else{
			if(StartY>100) StartY = 100;
			if(StartY<0) StartY = 0;
			if(StartY<10 && StartY>-10){
				int Y = StartY*1000;
				StartY = (double)Y/1000;
			}

			YAdvEdit->Text = FloatToStr(StartY);
			YAdvEdit->Color = clWhite;

			ForceTable.Force_StartY_Val = Reverse_Y_Calibration();
        }

		mainForm->Forcing = false;
//        mainForm->GetSecure();
//		TThread::Synchronize(mainForm->myCommandCreatorThread,StopFs);
		if(checkPermission()){
			TThread::Synchronize(mainForm->myCommandCreatorThread,StopFs);
		}
	}
}
//---------------------------------------------------------------------------

void __fastcall TForceFrm::DelayAdvEditKeyPress(TObject *Sender, System::WideChar &Key)

{
	if(Key == VK_RETURN){
		mainForm->LogToFile("TForceFrm::DelayAdvEditKeyPress");
        Key = 0;
//		AllEditWhite();
		DelayAdvEdit->Color = clWhite;
		DelayNumber =  DelayAdvEdit->Text.ToInt();

		ForceTable.Force_Delay_Val = DelayNumber;

		mainForm->Forcing = false;
//		mainForm->GetSecure();
		Delay = (DelayNumber * 1000) / (double)25; //25 ns is shortest delay time

		if(checkPermission()){
			TThread::Synchronize(mainForm->myCommandCreatorThread,StopFs);
		}
	}
}
//---------------------------------------------------------------------------

void __fastcall TForceFrm::U1AdvEditKeyPress(TObject *Sender, System::WideChar &Key)

{
	if(Key == VK_RETURN){
		mainForm->LogToFile("TForceFrm::U1AdvEditKeyPress");
        Key = 0;
//		AllEditWhite();
		U1AdvEdit->Color = clWhite;
		U1 = U1AdvEdit->Text.ToInt();
		if(AllScale){

			ForceTable.Force_U1_Val = U1;

			U1 = (int)(U1 / (U_index * pow10l(U_Scale * 3)));
		}
		else{

			double U1_mV = floor(U1 * U_index * pow10l(U_Scale * 3) * 1000 + 0.5) / (double)1000;
			ForceTable.Force_U1_Val = U1_mV;

		}

		if(checkPermission()){
			TThread::Synchronize(mainForm->myCommandCreatorThread,StopFs);
		}
	}
}
//---------------------------------------------------------------------------

void __fastcall TForceFrm::U2AdvEditKeyPress(TObject *Sender, System::WideChar &Key)

{
	if(Key == VK_RETURN){
		mainForm->LogToFile("TForceFrm::U2AdvEditKeyPress");
		Key = 0;
//		AllEditWhite();
		U2AdvEdit->Color = clWhite;
		U2 = U2AdvEdit->Text.ToInt();
		if(AllScale){
			ForceTable.Force_U2_Val = U2;
			U2 = (int)(U2 / (U_index * pow10l(U_Scale * 3)));
		}
		else{
			double U2_mV = floor(U2 * U_index * pow10l(U_Scale * 3) * 1000 + 0.5) / (double)1000;
			ForceTable.Force_U2_Val = U2_mV;
		}

		if(checkPermission()){
			TThread::Synchronize(mainForm->myCommandCreatorThread,StopFs);
		}
	}
}
//---------------------------------------------------------------------------

void __fastcall TForceFrm::Z1AdvEditKeyPress(TObject *Sender, System::WideChar &Key)
{
	if(Key == VK_RETURN){
		mainForm->LogToFile("TForceFrm::Z1AdvEditKeyPress");
		Key = 0;
//		AllEditWhite();
		dZ1 = Z1AdvEdit->Text.ToDouble();
		dZ1 = (int)dZ1;
		Z1AdvEdit->Text = IntToStr((int)dZ1);
		Z1AdvEdit->Color = clWhite;
//		if(Z1 < 0) Z1 = 0;
//		if(Z1 > 100) Z1 = 100;

		if(dZ1 < 0){
			Z1AdvEdit->Color = clYellow;
		}

		if(AllScale){
			ForceTable.Force_Z1_Val = dZ1;
			dZ1 = -(int)( dZ1 / ( pow10l(scale*3) * index * 1000));
		}
		else{
			double dz1_um;
			dz1_um = (dZ1 * index * pow10l(scale*3)) * 1000;
			dz1_um = (int) (dz1_um * 1000);
			dz1_um = (double)(dz1_um / 1000);

			ForceTable.Force_Z1_Val = dz1_um;
			dZ1 = -dZ1;

		}
		//		mainForm->LogToFile("TForceFrm::Z1AdvEditKeyPress : dZ1 = " + FloatToStr(dZ1));
		mainForm->Forcing = false;
//		mainForm->GetSecure();
		if(checkPermission()){
			TThread::Synchronize(mainForm->myCommandCreatorThread,StopFs);
		}
	}
}
//---------------------------------------------------------------------------

void __fastcall TForceFrm::Z2AdvEditKeyPress(TObject *Sender, System::WideChar &Key)

{
	if(Key == VK_RETURN){
		mainForm->LogToFile("TForceFrm::Z2AdvEditKeyPress");
        Key = 0;
//    	AllEditWhite();
		Z2AdvEdit->Color = clWhite;
		dZ2 = Z2AdvEdit->Text.ToDouble();
		dZ2 = (int)dZ2;
		Z2AdvEdit->Text = IntToStr((int)dZ2);
		Z2AdvEdit->Color = clWhite;
//		if(Z2 < 0) Z2 = 0;
//		if(Z2 > 100) Z2 = 100;

		if(dZ2 < 0){
			Z2AdvEdit->Color = clYellow;
		}


		if(AllScale){
			ForceTable.Force_Z2_Val = dZ2;
			dZ2 = -(int)( dZ2 / ( pow10l(scale*3) * index * 1000));
		}
		else{
			double dz2_um;
			dz2_um = (dZ2 * index * pow10l(scale*3)) * 1000;
			dz2_um = (int) (dz2_um * 1000);
			dz2_um = (double)(dz2_um / 1000);
			ForceTable.Force_Z2_Val = dz2_um;
			dZ2 = - dZ2;
        }

		if(checkPermission()){
			TThread::Synchronize(mainForm->myCommandCreatorThread,StopFs);
		}
	}
}
//---------------------------------------------------------------------------

void __fastcall TForceFrm::ResAdvComboBoxChange(TObject *Sender)
{
	mainForm->LogToFile("TForceFrm::ResAdvComboBoxChange");
    ResolutionIndex = ResAdvComboBox->ItemIndex;
	Resolution = GetResolution(ResolutionIndex);
	ForceTable.Force_Resolution_Index = ResolutionIndex;
	if(checkPermission()){
		TThread::Synchronize(mainForm->myCommandCreatorThread,StopFs);
	}
}
//---------------------------------------------------------------------------

void __fastcall TForceFrm::ModesAdvComboBoxChange(TObject *Sender)
{
	mainForm->LogToFile("TForceFrm::ModesAdvComboBoxChange");
	ModesIndex = ModesAdvComboBox->ItemIndex;
	Mode = ModesIndex + 1;
	EnabledPanels(Mode);
	ForceTable.Force_Mode_Index = ModesIndex;
	if(checkPermission()){
		TThread::Synchronize(mainForm->myCommandCreatorThread,StopFs);
	}
}
//---------------------------------------------------------------------------

void TForceFrm::ShowLables(int mode)
{
	int w = PanelSubFs->Width;
	int h = PanelSubFs->Height - PanelLabelFs->Height - ChartPanel->Height;

	int Top = PanelLabelFs->Height + ChartPanel->Height + 10;

//	ChartAdvWiiProgressBar->Width = 50;
//	ChartAdvWiiProgressBar->Height = 50;
//	ChartAdvWiiProgressBar->Visible = false;
//	ChartAdvWiiProgressBar->Left =  ChartPanel->Width/2 - ChartAdvWiiProgressBar->Width/2;
//	ChartAdvWiiProgressBar->Top =  ChartPanel->Height/2 - ChartAdvWiiProgressBar->Height/2;


//	PanelChartPicker->Left = ChartPanel->Width - PanelChartPicker->Width - 2;
//	PanelChartPicker->Top = 2;




	int l = 260;
	int p = 30;

	int left1 =  10;
	int left2 = w - 10 - 260;
	switch(mode){
		case -1:

			Panel4->Left = left1;
			Panel4->Top = Top + 10;
			Panel4->Width = l;
			Panel4->Height = p;
			Panel4->BringToFront();

			Panel5->Left = left1;
			Panel5->Top = Panel4->Top + 35;
			Panel5->Width = l;
			Panel5->Height = p;
			Panel5->BringToFront();
	//
			Panel3->Left = left1;
			Panel3->Top = Panel5->Top + 35;
			Panel3->Width = l;
			Panel3->Height = p;
			Panel3->BringToFront();
	//
			Panel1->Left = left1;
			Panel1->Top = Panel3->Top + 35;
			Panel1->Width = l;
			Panel1->Height = p;
			Panel1->BringToFront();
	//
			Panel2->Left = left1;
			Panel2->Top = Panel1->Top + 35;
			Panel2->Width = l;
			Panel2->Height = p;
			Panel2->BringToFront();
	//
			Panel11->Left = left1;
			Panel11->Top = Panel2->Top + 35;
			Panel11->Width = l;
			Panel11->Height = p;
			Panel11->BringToFront();

	//
			Panel6->Left = left2;
			Panel6->Top = Panel1->Top;
			Panel6->Width = l;
			Panel6->Height = p;
			Panel6->BringToFront();
	//
			Panel7->Left = left2;
			Panel7->Top = Panel2->Top;
			Panel7->Width = l;
			Panel7->Height = p;
			Panel7->BringToFront();
	//
			Panel8->Left = left2;
			Panel8->Top = Panel5->Top;
			Panel8->Width = l;
			Panel8->Height = p;
			Panel8->BringToFront();
	//
			Panel9->Left = left2;
			Panel9->Top = Panel3->Top;
			Panel9->Width = l;
			Panel9->Height = p;
			Panel9->BringToFront();

			Panel12->Left = left2;
			Panel12->Top = Panel4->Top;
			Panel12->Width = l;
			Panel12->Height = p;
			Panel12->BringToFront();


			PanelRunForce->Left = left2;
			PanelRunForce->Top = Panel11->Top;
			PanelRunForce->Width = 260;
			PanelRunForce->Height = 30;



			ResAdvComboBox->ItemIndex = 0;
			ModesAdvComboBox->ItemIndex = 0;
			ChartPicker->ItemIndex = 0;
			break;
		default:
			break;
	}

	UpDownBorder(RunAdvGlassButton->Appearance,false);
	EnableFsPanel(0);
	FsBtnState = 0;

}
//---------------------------------------------------------------------------

void TForceFrm::PickSeries(int series)
{
	mainForm->LogToFile("TForceFrm::PickSeries  , series = " + IntToStr(series));
	Series1->Active = false;
	Series2->Active = false;
	Series3->Active = false;
	Series4->Active = false;
	Series5->Active = false;
	Series6->Active = false;
	Series7->Active = false;
	Series8->Active = false;
	Series9->Active = false;
	Series10->Active = false;
	Series11->Active = false;
	Series12->Active = false;
	Series13->Active = false;
	Series14->Active = false;
	Series15->Active = false;
	Series16->Active = false;
	Series17->Active = false;
	Series18->Active = false;
	Series19->Active = false;
	Series20->Active = false;
	Series21->Active = false;
	Series22->Active = false;
	Series23->Active = false;
	Series24->Active = false;
	Series25->Active = false;
	Series26->Active = false;
	Series27->Active = false;
	Series28->Active = false;
	ChartChartSetting(series);

	if(RadioButtonUnitZ->Checked){
		switch(series){
			case 1:{

                Series1->Active = true;
				Series2->Active = true;
				if(AllScale)
					ChartChart->LeftAxis->Title->Caption = "Topo (nm)";
				else
					ChartChart->LeftAxis->Title->Caption = "Topo";
				break;

			}
			case 2:{
                Series4->Active = true;
				Series3->Active = true;
				if (mainForm->myTcpThread->Fs_C_Factor_Set) {
					ChartChart->LeftAxis->Title->Caption = "TB (nN)";
				}
				else{
					ChartChart->LeftAxis->Title->Caption = "TB (mV)";
				}
				break;
			}
			case 3:{
                Series6->Active = true;
				Series5->Active = true;
				ChartChart->LeftAxis->Title->Caption = "LR (mV)";
				break;

			}
			case 4:{
                Series11->Active = true;
				Series12->Active = true;
				ChartChart->LeftAxis->Title->Caption = "CmAfm (z)";
				break;
			}
			case 5:{
                Series1->Active = true;
				if(AllScale)
					ChartChart->LeftAxis->Title->Caption = "Topo-F (nm)";
				else
					ChartChart->LeftAxis->Title->Caption = "Topo-F";
				break;
			}
			case 6:{
                Series2->Active = true;
				if(AllScale)
					ChartChart->LeftAxis->Title->Caption = "Topo-B (nm)";
				else
					ChartChart->LeftAxis->Title->Caption = "Topo-B";
				break;

			}
//			case 7:{
//				Series7->Active = true;
//				ChartChart->LeftAxis->Title->Caption = "Amp_Fw(z)";
//				break;
//			}
//			case 8:{
//				Series8->Active = true;
//				ChartChart->LeftAxis->Title->Caption = "Amp_Bw(z)";
//				break;
//			}
//			case 9:{
//				Series9->Active = true;
//				ChartChart->LeftAxis->Title->Caption = "Phase_Fw(z)";
//				break;
//			}
//			case 10:{
//				Series10->Active = true;
//				ChartChart->LeftAxis->Title->Caption = "Phase_Fw(z)";
//				break;
//			}
			case 7:{
                Series3->Active = true;
				if (mainForm->myTcpThread->Fs_C_Factor_Set) {
					ChartChart->LeftAxis->Title->Caption = "TB-F (nN)";
				}
				else{
					ChartChart->LeftAxis->Title->Caption = "TB-F (mV)";
				}
				break;

			}
			case 8:{
				Series4->Active = true;
				if (mainForm->myTcpThread->Fs_C_Factor_Set) {
					ChartChart->LeftAxis->Title->Caption = "TB-B (nN)";
				}
				else{
					ChartChart->LeftAxis->Title->Caption = "TB-B (mV)";
				}
				break;

			}
			case 9:{

				Series5->Active = true;
				ChartChart->LeftAxis->Title->Caption = "LR-F (mV)";
				break;
			}
			case 10:{
                Series6->Active = true;
				ChartChart->LeftAxis->Title->Caption = "LR-B (mV)";
				break;

			}
			case 11:{
                Series11->Active = true;
				ChartChart->LeftAxis->Title->Caption = "cmAFM-F (z)";
				break;

			}
//			case 16:{
//				Series8->Active = true;
//				Series7->Active = true;
//				ChartChart->LeftAxis->Title->Caption = "Amp(z)";
//				break;
//			}
//			case 17:{
//				Series9->Active = true;
//				Series10->Active = true;
//				ChartChart->LeftAxis->Title->Caption = "Phase(z)";
//				break;
//			}
			case 12:{
                Series12->Active = true;
				ChartChart->LeftAxis->Title->Caption = "cmAFM-B (z)";
				break;

			}
			default:{
				Series1->Active = true;
				Series2->Active = true;
				if(AllScale)
					ChartChart->LeftAxis->Title->Caption = "Topo (nm)";
				else
					ChartChart->LeftAxis->Title->Caption = "Topo";
				break;
			}
		}
	}
	else{
		ChartChart->BottomAxis->Title->Caption = "Time (ms)";
		switch(series){
			case 1:{
                Series25->Active = true;
				if(AllScale)
					ChartChart->LeftAxis->Title->Caption = "Topo (nm)";
				else
					ChartChart->LeftAxis->Title->Caption = "Topo";
				break;
			}
			case 2:{
                Series26->Active = true;
				if (mainForm->myTcpThread->Fs_C_Factor_Set) {
					ChartChart->LeftAxis->Title->Caption = "TB (nN)";
				}
				else{
					ChartChart->LeftAxis->Title->Caption = "TB (mV)";
				}
				break;
			}
			case 3:{
                Series27->Active = true;
				ChartChart->LeftAxis->Title->Caption = "LR (mV)";
				break;
			}
			case 4:{
                Series28->Active = true;
				ChartChart->LeftAxis->Title->Caption = "CmAfm (t)";
				break;
			}
			case 5:{
                Series13->Active = true;
				if(AllScale)
					ChartChart->LeftAxis->Title->Caption = "Topo-F (nm)";
				else
					ChartChart->LeftAxis->Title->Caption = "Topo-F";
				break;

			}
			case 6:{
                Series14->Active = true;
				if(AllScale)
					ChartChart->LeftAxis->Title->Caption = "Topo-B (nm)";
				else
					ChartChart->LeftAxis->Title->Caption = "Topo-B";
				break;
			}
//			case 7:{
//				Series19->Active = true;
//				ChartChart->LeftAxis->Title->Caption = "Amp_Fw(t)";
//				break;
//			}
//			case 8:{
//				Series20->Active = true;
//				ChartChart->LeftAxis->Title->Caption = "Amp_Bw(t)";
//				break;
//			}
//			case 9:{
//				Series21->Active = true;
//				ChartChart->LeftAxis->Title->Caption = "Phase_Fw(t)";
//				break;
//			}
//			case 10:{
//				Series22->Active = true;
//				ChartChart->LeftAxis->Title->Caption = "Phase_Fw(t)";
//				break;
//			}
			case 7:{
                Series15->Active = true;
				if (mainForm->myTcpThread->Fs_C_Factor_Set) {
					ChartChart->LeftAxis->Title->Caption = "TB-F (nN)";
				}
				else{
					ChartChart->LeftAxis->Title->Caption = "TB-F (mV)";
				}
				break;

			}
			case 8:{
                Series16->Active = true;
				if (mainForm->myTcpThread->Fs_C_Factor_Set) {
					ChartChart->LeftAxis->Title->Caption = "TB-B (nN)";
				}
				else{
					ChartChart->LeftAxis->Title->Caption = "TB-B (mV)";
				}
				break;

			}
			case 9:{
                Series17->Active = true;
				ChartChart->LeftAxis->Title->Caption = "LR-F (mV)";
				break;

			}
			case 10:{
                Series18->Active = true;
				ChartChart->LeftAxis->Title->Caption = "LR-B (mV)";
				break;
			}
			case 11:{
                Series23->Active = true;
				ChartChart->LeftAxis->Title->Caption = "cmAFM-F (t)";
				break;

			}
//			case 16:{
//				Series8->Active = true;
//				Series7->Active = true;
//				ChartChart->LeftAxis->Title->Caption = "Amp(z)";
//				break;
//			}
//			case 17:{
//				Series9->Active = true;
//				Series10->Active = true;
//				ChartChart->LeftAxis->Title->Caption = "Phase(z)";
//				break;
//			}
			case 12:{
                Series24->Active = true;
				ChartChart->LeftAxis->Title->Caption = "cmAFM-B (t)";
				break;

			}
			default:{
				Series25->Active = true;
				if(AllScale)
					ChartChart->LeftAxis->Title->Caption = "Topo (nm)";
				else
					ChartChart->LeftAxis->Title->Caption = "Topo";
				break;
			}
		}

	}
}
//---------------------------------------------------------------------------

void TForceFrm::ChartChartSetting(int series){

	mainForm->LogToFile("TForceFrm::ChartChartSetting  , series = " + IntToStr(series));

	if(FinalMode == 1 || FinalMode == 4 || FinalMode == 5){

		if (RadioButtonUnitZ->Checked && (series == -1 || series == 5 || series == 7 || series == 9 || series == 11 || series == 1 || series == 2 || series == 3 || series == 4)) {
			ChartChart->BottomAxis->Title->Caption = "Z (nm)";
			if(!XInverted){
				if((Finaldz * index * pow10l(scale*3)) >= 0 ){
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
				if((Finaldz * index * pow10l(scale*3)) > 0){
					ChartChart->BottomAxis->Inverted = false;
				}
				else{
					ChartChart->BottomAxis->Inverted = true;
				}
			}
		}
//		else{
//			ChartChart->BottomAxis->Inverted = false;
//		}
	}
	else {
		if (RadioButtonUnitZ->Checked && (series == -1 || series == 5 || series == 7 || series == 9 || series == 11 || series == 1 || series == 2 || series == 3 || series == 4)) {
			ChartChart->BottomAxis->Title->Caption = "U (mV)";
			if(!XInverted){
				if((FinalU * U_index * pow10l(U_Scale*3)) >= 0 ){
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
				if((FinalU * U_index * pow10l(U_Scale*3)) >= 0){
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

void __fastcall TForceFrm::ChartPickerChange(TObject *Sender)
{
	PickSeries(ChartPicker->ItemIndex+1);
}
//---------------------------------------------------------------------------

void TForceFrm::ClearSeries(int series)
{
//	mainForm->LogToFile("TForceFrm::ClearSeries");
	switch(series){
		case 1:
			Series1->Clear();
			break;
		case 2:
			Series2->Clear();
			break;
		case 3:
			Series3->Clear();
			break;
		case 4:
			Series4->Clear();;
			break;
		case 5:
			Series5->Clear();
			break;
		case 6:
			Series6->Clear();
			break;
		case 7:
			Series7->Clear();
			break;
		case 8:
			Series8->Clear();
			break;
		case 9:
			Series9->Clear();
			break;
		case 10:
			Series10->Clear();
			break;
		case 11:
			Series11->Clear();
			break;
		case 12:
			Series12->Clear();
			break;
		case 13:
			Series13->Clear();
			break;
		case 14:
			Series14->Clear();
			break;
		case 15:
			Series15->Clear();
			break;
		case 16:
			Series16->Clear();
			break;
		case 17:
			Series17->Clear();
			break;
		case 18:
			Series18->Clear();
			break;
		case 19:
			Series19->Clear();
			break;
		case 20:
			Series20->Clear();
			break;
		case 21:
			Series21->Clear();
			break;
		case 22:
			Series22->Clear();
			break;
		case 23:
			Series23->Clear();
			break;
		case 24:
			Series24->Clear();
			break;
		case 25:
			Series25->Clear();
			break;
		case 26:
			Series26->Clear();
			break;
		case 27:
			Series27->Clear();
			break;
		case 28:
			Series27->Clear();
			break;

		default:
			Series1->Clear();
			break;
	}
}
//---------------------------------------------------------------------------

void TForceFrm::ClearSeries()
{
	for(int i=1; i<25; i++)
		ClearSeries(i);
}
//---------------------------------------------------------------------------

void TForceFrm::EnableFsPanel(int enabled)
{
	mainForm->LogToFile("TForceFrm::EnableFsPanel , enabled = " + IntToStr(enabled));
	switch(enabled){
		case 0:{
			FsBtnState = 0;
			RunAdvGlassButton->Enabled = true;
			RunAdvGlassButton->Caption = "Start Force Spectroscopy";
			UpDownBorder(RunAdvGlassButton->Appearance, true);
			this->Enabled = true;
			AdvGlowButton1->Enabled = true;
			Panel12->Enabled = true;

			break;
		}
		case 1:{
			FsBtnState = 1;
			RunAdvGlassButton->Enabled = true;
			RunAdvGlassButton->Caption = "Stop Force Spectroscopy";
			UpDownBorder(RunAdvGlassButton->Appearance, false);
			this->Enabled = true;
			AdvGlowButton1->Enabled = false;
			Panel12->Enabled = false;
			break;
		}
		case 2:{
			RunAdvGlassButton->Enabled = false;
			RunAdvGlassButton->Caption = "... Force Spectroscopy ...";
			UpDownBorder(RunAdvGlassButton->Appearance, true);
			this->Enabled = false;
			AdvGlowButton1->Enabled = false;
			Panel12->Enabled = false;
			break;
		}
		default:{

			break;
		}
	}
}
//---------------------------------------------------------------------------

void TForceFrm::UpDownBorder(TGlowButtonAppearance* appearance, bool UpDown)
{
	if(UpDown){
		appearance->BorderColor = TColor(0x00614438);
		appearance->BorderColorHot = TColor(0x00614438);
		appearance->BorderColorChecked = TColor(0x00614438);
		appearance->BorderColorCheckedHot = TColor(0x00614438);
		appearance->BorderColorDisabled = TColor(0x00614438);
		appearance->BorderColorFocused = TColor(0x00614438);
		appearance->BorderColorDown = TColor(0x00614438);
	}
	else{
		appearance->BorderColor = TColor(0x00F0D27D);
		appearance->BorderColorHot = TColor(0x00F0D27D0);
		appearance->BorderColorChecked = TColor(0x00F0D27D);
		appearance->BorderColorCheckedHot = TColor(0x00F0D27D);
		appearance->BorderColorDisabled = TColor(0x00F0D27D);
		appearance->BorderColorFocused = TColor(0x00F0D27D);
		appearance->BorderColorDown = TColor(0x00F0D27D);
	}
}
//---------------------------------------------------------------------------

void TForceFrm::EnabledPanels(int mode)
{
	mainForm->LogToFile("TForceFrm::EnabledPanels , mode = " + IntToStr(mode));

	Z1AdvEdit->Enabled = false;
	Z2AdvEdit->Enabled = false;
	U1AdvEdit->Enabled = false;
	U2AdvEdit->Enabled = false;
//	Panel6->Visible = false;
//	Panel7->Visible = false;
//	Panel8->Visible = false;
//	Panel9->Visible = false;
	switch(mode){
		case 1:{
			Z1AdvEdit->Enabled = true;
			Z2AdvEdit->Enabled = true;
			U1AdvEdit->Enabled = true;
//			Panel8->Visible = true;
//			Panel9->Visible = true;
			break;
		}
		case 2:{
			Z1AdvEdit->Enabled = true;
			U1AdvEdit->Enabled = true;
			U2AdvEdit->Enabled = true;
//			Panel6->Visible = true;
//			Panel7->Visible = true;
			break;
		}
		case 3:{
			Z1AdvEdit->Enabled = true;
			U1AdvEdit->Enabled = true;
			U2AdvEdit->Enabled = true;
//			Panel6->Visible = true;
//			Panel7->Visible = true;
			break;
		}
		case 4:{
			Z1AdvEdit->Enabled = true;
			Z2AdvEdit->Enabled = true;
			U1AdvEdit->Enabled = true;
//			Panel8->Visible = true;
//			Panel9->Visible = true;
			break;
		}
		case 5:{
			Z1AdvEdit->Enabled = true;
			Z2AdvEdit->Enabled = true;
			U1AdvEdit->Enabled = true;
//			Panel8->Visible = true;
//			Panel9->Visible = true;
			break;
		}
		case 6:{
			Z1AdvEdit->Enabled = true;
			U1AdvEdit->Enabled = true;
			U2AdvEdit->Enabled = true;
//			Panel6->Visible = true;
//			Panel7->Visible = true;
			break;
		}
		case 7:{
			Z1AdvEdit->Enabled = true;
			U1AdvEdit->Enabled = true;
			U2AdvEdit->Enabled = true;
//			Panel6->Visible = true;
//			Panel7->Visible = true;
			break;
		}
		case 8:{
			Z1AdvEdit->Enabled = true;
			U1AdvEdit->Enabled = true;
			U2AdvEdit->Enabled = true;
//			Panel6->Visible = true;
//			Panel7->Visible = true;
			break;
		}
		default :{
			Z1AdvEdit->Enabled = true;
			Z2AdvEdit->Enabled = true;
			U1AdvEdit->Enabled = true;
			U2AdvEdit->Enabled = true;
//			Panel8->Visible = true;
//			Panel9->Visible = true;
			break;
		}
	}
}
//---------------------------------------------------------------------------

void TForceFrm::AdvEditChange(double x, double y)
{
	mainForm->LogToFile("TForceFrm::AdvEditChange");

	// x
	if(AllScale){
		 StartX = x;
		if(StartX>Max_Range/2) StartX = Max_Range/2;
		if(StartX<-Max_Range/2) StartX = -Max_Range/2;

		if(StartX<10 && StartX>-10){
			int X = StartX*1000;
			StartX = (double)X/1000;
		}
		XAdvEdit->Text = FloatToStr(StartX);
		XAdvEdit->Color = clWhite;
		ForceTable.Force_StartX_Val = StartX;


		X_Calibration();

		// y
		StartY = y;
		if(StartY>Max_Range/2) StartY = Max_Range/2;
		if(StartY<-Max_Range/2) StartY = -Max_Range/2;

		if(StartY<10 && StartY>-10){
			int X = StartY*1000;
			StartY = (double)X/1000;
		}

		YAdvEdit->Text = StartY;
		YAdvEdit->Color = clWhite;
		ForceTable.Force_StartY_Val = StartY;
		Y_Calibration();

	}
	else{
		StartX = x;
		if(StartX>100) StartX = 100;
		if(StartX<0) StartX = 0;

		if(StartX<10 && StartX>-10){
			int X = StartX*1000;
			StartX = (double)X/1000;
		}
		XAdvEdit->Text = FloatToStr(StartX);
		XAdvEdit->Color = clWhite;
		ForceTable.Force_StartX_Val = Reverse_X_Calibration();


		// y center
		StartY = y;
		if(StartY>100) StartY = 100;
		if(StartY<0) StartY = 0;

		if(StartY<10 && StartY>-10){
			int X = StartY*1000;
			StartY = (double)X/1000;
		}

		YAdvEdit->Text = FloatToStr(StartY);
		YAdvEdit->Color = clWhite;
		ForceTable.Force_StartY_Val = Reverse_Y_Calibration();
	}



	if(checkPermission()){
		TThread::Synchronize(mainForm->myCommandCreatorThread,StopFs);
	}

}
//---------------------------------------------------------------------------

void __fastcall TForceFrm::AdvGlowButton1Click(TObject *Sender)
{
	mainForm->LogToFile("TForceFrm::AdvGlowButton1Click");
//	mainForm->myOscForm->p1PauseClick(NULL);
    Osc_PreviousState = false;
	for(int i=0; i<4; i++){
		if(mainForm->myOscForm->my_plot_set[i].bool_PlotPlay){
			Osc_PreviousState = true;
			mainForm->myOscForm->p1PauseClick(NULL);
		}
	}
	mainForm->myVideoForm->VideoGrabber1->StopPreview();
	mainForm->Enabled = false;
	mainForm->LogToFile("Start");
	myChartForm->Series1 = Series1;
	myChartForm->Series2 = Series2;
	myChartForm->Series3 = Series3;
	myChartForm->Series4 = Series4;
	myChartForm->Series5 = Series5;
	myChartForm->Series6 = Series6;
	myChartForm->Series7 = Series7;
	myChartForm->Series8 = Series8;
	myChartForm->Series9 = Series9;
	myChartForm->Series10 = Series10;
	myChartForm->Series11 = Series11;
	myChartForm->Series12 = Series12;
	myChartForm->Series13 = Series13;
	myChartForm->Series14 = Series14;
	myChartForm->Series15 = Series15;
	myChartForm->Series16 = Series16;
	myChartForm->Series17 = Series17;
	myChartForm->Series18 = Series18;
	myChartForm->Series19 = Series19;
	myChartForm->Series20 = Series20;
	myChartForm->Series21 = Series21;
	myChartForm->Series22 = Series22;
	myChartForm->Series23 = Series23;
	myChartForm->Series24 = Series24;
	myChartForm->Series25 = Series25;
	myChartForm->Series26 = Series26;
	myChartForm->Series27 = Series27;
	myChartForm->Series28 = Series28;

//	myChartForm->Series101->AssignValues(Series1);
//	myChartForm->Series102->AssignValues(Series2);

	mainForm->LogToFile("Done");

	myChartForm->PickSeries(ChartPicker->ItemIndex + 1);
	myChartForm->ChartPicker->ItemIndex = ChartPicker->ItemIndex;
	myChartForm->Show();
}
//---------------------------------------------------------------------------

void __fastcall TForceFrm::XAdvEditChange(TObject *Sender)
{
	XAdvEdit->Color = clSilver;
}
//---------------------------------------------------------------------------

void __fastcall TForceFrm::YAdvEditChange(TObject *Sender)
{
	YAdvEdit->Color = clSilver;
}
//---------------------------------------------------------------------------

void __fastcall TForceFrm::DelayAdvEditChange(TObject *Sender)
{
   DelayAdvEdit->Color = clSilver;
}
//---------------------------------------------------------------------------

void __fastcall TForceFrm::U1AdvEditChange(TObject *Sender)
{
	U1AdvEdit->Color = clSilver;
}
//---------------------------------------------------------------------------

void __fastcall TForceFrm::U2AdvEditChange(TObject *Sender)
{
	U2AdvEdit->Color = clSilver;
}
//---------------------------------------------------------------------------

void __fastcall TForceFrm::Z1AdvEditChange(TObject *Sender)
{
	 Z1AdvEdit->Color = clSilver;
}
//---------------------------------------------------------------------------

void __fastcall TForceFrm::Z2AdvEditChange(TObject *Sender)
{
	 Z2AdvEdit->Color = clSilver;
}
//---------------------------------------------------------------------------

void TForceFrm::AllEditWhite()
{
	XAdvEdit->Color = clWhite;
	YAdvEdit->Color = clWhite;
	DelayAdvEdit->Color = clWhite;
	U1AdvEdit->Color = clWhite;
	U2AdvEdit->Color = clWhite;
	Z1AdvEdit->Color = clWhite;
	Z2AdvEdit->Color = clWhite;
}
//---------------------------------------------------------------------------

void TForceFrm::X_Calibration(){
	mainForm->LogToFile("TForceFrm::X_Calibration");
	Start_X_um = StartX;
	double CenterXX = abs(StartX);
	double X1_Center = mainForm->X_Range[(int)CenterXX];
	double X2_Center = mainForm->X_Range[(int)CenterXX+1];

	if((int)CenterXX < CenterXX){
	   double diff = CenterXX - (int)CenterXX;
	   CenterXX = Regression(X1_Center,X2_Center,diff);
	}
	else{
		CenterXX = X1_Center;
	}

	if(StartX>0) StartX = 50 + CenterXX;
	else StartX = 50 - CenterXX;

//	mainForm->LogToFile("TForceFrm::X_Calibration : StartX = " + FloatToStr(StartX));
}
//---------------------------------------------------------------------------

void TForceFrm::Y_Calibration(){
	mainForm->LogToFile("TForceFrm::Y_Calibration");
	Start_Y_um = StartY;
	double CenterYY = abs(StartY);
	double Y1_Center = mainForm->Y_Range[(int)CenterYY];
	double Y2_Center = mainForm->Y_Range[(int)CenterYY+1];


	if((int)CenterYY < CenterYY){
	   double diff = CenterYY - (int)CenterYY;
	   CenterYY = Regression(Y1_Center,Y2_Center,diff);
	}
	else{
		CenterYY = Y1_Center;
	}

	if(StartY>0) StartY = 50 + CenterYY;
	else StartY = 50 - CenterYY;

//	mainForm->LogToFile("TForceFrm::Y_Calibration : StartY = " + FloatToStr(StartY));
}
//---------------------------------------------------------------------------

double TForceFrm::Regression(double First , double Second , double diff)
{
	mainForm->LogToFile("TForceFrm::Regression");
	double Final = First + (Second - First) * diff ;
	return Final;
}
//---------------------------------------------------------------------------

double TForceFrm::Reverse_X_Calibration(){

	mainForm->LogToFile("TForceFrm::Reverse_X_Calibration");
	double min_CenterX = 100;
	int new_XCenter;

	for (int i = 0; i < mainForm->Max_Range; i++) {
		if (min_CenterX > abs(abs(50 - StartX)-mainForm->X_Range[i])){
			min_CenterX = abs(abs(50 - StartX)-mainForm->X_Range[i]);
			new_XCenter = i;
		}
	}

	if(abs(50 - StartX)-mainForm->X_Range[new_XCenter] >= 0)
		min_CenterX = new_XCenter + (abs(50 - StartX) - mainForm->X_Range[new_XCenter]) / (mainForm->X_Range[new_XCenter+1] - mainForm->X_Range[new_XCenter]);
	else
		min_CenterX = new_XCenter + (abs(50 - StartX) - mainForm->X_Range[new_XCenter]) / (mainForm->X_Range[new_XCenter] - mainForm->X_Range[new_XCenter-1]);

	if(StartX < 50) min_CenterX = -min_CenterX;

	int F_new;

	F_new = min_CenterX * 1000;
	min_CenterX = (double)F_new/1000;

	return min_CenterX;
}
//---------------------------------------------------------------------------

double TForceFrm::Reverse_Y_Calibration(){
	mainForm->LogToFile("TForceFrm::Reverse_Y_Calibration");
	double min_CenterY = 100;
	int new_YCenter;


	for (int i = 0; i < mainForm->Max_Range; i++) {
		if (min_CenterY > abs(abs(50 - StartY)-mainForm->Y_Range[i])){
			min_CenterY = abs(abs(50 - StartY)-mainForm->Y_Range[i]);
			new_YCenter = i;
		}
	}

	if(abs(50 - StartY)-mainForm->Y_Range[new_YCenter] >= 0)
		min_CenterY = new_YCenter + (abs(50 - StartY) - mainForm->Y_Range[new_YCenter]) / (mainForm->Y_Range[new_YCenter+1] - mainForm->Y_Range[new_YCenter]);
	else
		min_CenterY = new_YCenter + (abs(50 - StartY) - mainForm->Y_Range[new_YCenter]) / (mainForm->Y_Range[new_YCenter] - mainForm->Y_Range[new_YCenter-1]);


	if(StartY < 50) min_CenterY = -min_CenterY;



	int F_new;

	F_new = min_CenterY * 1000;
	min_CenterY = (double)F_new/1000;

	return min_CenterY;
}

//---------------------------------------------------------------------------

void __fastcall TForceFrm::RadioButtonUnitZClick(TObject *Sender)
{
	mainForm->LogToFile("TForceFrm::RadioButtonUnitZClick");
    PickSeries(ChartPicker->ItemIndex+1);
}
//---------------------------------------------------------------------------

void __fastcall TForceFrm::RadioButtonUnitTimeClick(TObject *Sender)
{
	mainForm->LogToFile("TForceFrm::RadioButtonUnitTimeClick");
	PickSeries(ChartPicker->ItemIndex+1);
}
//---------------------------------------------------------------------------


void __fastcall TForceFrm::InvertXButtonClick(TObject *Sender)
{
	mainForm->LogToFile("TForceFrm::InvertXButtonClick");
	ChartChart->BottomAxis->Inverted = !ChartChart->BottomAxis->Inverted;
	XInverted = true;
}
//---------------------------------------------------------------------------



void __fastcall TForceFrm::InvertYButtonClick(TObject *Sender)
{
	mainForm->LogToFile("TForceFrm::InvertYButtonClick");
	ChartChart->LeftAxis->Inverted = !ChartChart->LeftAxis->Inverted;
}
//---------------------------------------------------------------------------




