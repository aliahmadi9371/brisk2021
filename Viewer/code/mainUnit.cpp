//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "mainUnit.h"
#include "oscClass.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "AdvCircularProgress"
#pragma link "AdvOfficeStatusBar"
#pragma link "AdvOfficeStatusBarStylers"
#pragma resource "*.dfm"
TmainForm *mainForm;
//---------------------------------------------------------------------------
__fastcall TmainForm::TmainForm(TComponent* Owner)
	: TForm(Owner)
{
	bool_Created = false;
	first = false;
	lastDir = "";
	ConfigOsc();
}
//---------------------------------------------------------------------------
void __fastcall TmainForm::FormShow(TObject *Sender)
{
	if(!bool_Created){
		TRect rect = Screen->PrimaryMonitor->BoundsRect;
		mainForm->SetBounds(0,0,rect.Width(),rect.Height());

		CteateQueue();

		mainPanel->Height = rect.Height() ;

		ch1 = new ToscForm(mainPanel);
		ch1->Parent = mainPanel;
		ch1->Show();

		ch2 = new ToscForm(mainPanel);
		ch2->Parent = mainPanel;
		ch2->Show();

		ch3 = new ToscForm(mainPanel);
		ch3->Parent = mainPanel;
		ch3->Show();

		ch4 = new ToscForm(mainPanel);
		ch4->Parent = mainPanel;
		ch4->Show();

        UpdateCharts(1,true);
		bool_Created = true;
	}
}
//---------------------------------------------------------------------------
void __fastcall TmainForm::FormResize(TObject *Sender)
{

	mainForm->WindowState = wsMaximized;
    if(mainForm->WindowState == wsNormal){
		TRect rect = Screen->PrimaryMonitor->BoundsRect;
		mainForm->SetBounds(0,0,rect.Width(),rect.Height());
		mainForm->Left = 0;
		mainForm->Top = 0;
		mainForm->Width = rect.Width()/2;
		mainForm->Height = rect.Height()/2;
	}
}
//---------------------------------------------------------------------------

__fastcall TmainForm::~TmainForm()
{
	Application->Terminate();
	exit(EXIT_SUCCESS);
}
//---------------------------------------------------------------------------

void __fastcall TmainForm::button_OpenClick(TObject *Sender)
{
	Lable_Status->Caption = "    Waves Loading ...";
//	if(!first){
//		lastDir = GetCurrentDir()+ "\\data";
//		first = true;
//	}
	dialog_Open->InitialDir = lastDir;
	dialog_Open->Filter = "AFM Files (*.afm) | *.AFM";
	if(dialog_Open->Execute()){
		lastDir = dialog_Open->FileName;
		PathRemoveFileSpecA(lastDir.c_str());
		TIniFile *iniFile = new TIniFile(GetCurrentDir()+ "/viewer.ini");
		iniFile->WriteString("MAIN","last_path",lastDir);
		delete iniFile;
		if(dialog_Open->FileName == ""){
			Lable_Status->Caption = "    Waves Loaded .";
		}
		else{
			InitQueues();
			UnicodeString filename = dialog_Open->FileName;
			LoadFileToQueue(filename);
		}
	}
	else{
		mainForm->Cursor = crDefault;
		Lable_Status->Caption = "    Waves Loaded .";
		lastDir = dialog_Open->FileName;
		PathRemoveFileSpecA(lastDir.c_str());
	}
}
//---------------------------------------------------------------------------

void TmainForm::LoadFileToQueue(UnicodeString fileName)
{
//	LogToFile("TmainForm: LoadFileToQueue: ");
	TFile file;
	TByteDynArray byteArr = file.ReadAllBytes(fileName);
	int len = byteArr.Length;
	int length = len/112;
	TByteDynArray bytes;
	bytes.Length = 112;

	Length = length;
	Time = length * rec_step;
	for(int i=0; i<length; i++){
		for(int j=0; j<112; j++){
			bytes[j] = byteArr[i*112 + j];
		}
		ParsData(bytes);

	}



	if(length)
		UpdateCharts(length,false);
	else
        UpdateCharts(1,false);


	byteArr.Length = 0;
}
//---------------------------------------------------------------------------

void TmainForm::CteateQueue()
{
	for(int i=0; i<27; i++){
		ChartQueue[i]._size = 100000;
		ChartQueue[i].createQueue();
	}
}
//---------------------------------------------------------------------------

void TmainForm::InitQueues()
{
	for(int i=0; i<27; i++){
		ChartQueue[i]._size = 100000;
		ChartQueue[i].InitQueue();
	}
}
//---------------------------------------------------------------------------

void TmainForm::ParsData(TByteDynArray myData)
{
	ChartQueue[0 ].GetNewData( myData[3],myData[4],myData[5],myData[6],data_offset_00,data_index_00,true,false,0);

	ChartQueue[1 ].GetNewData( myData[7],myData[8],myData[9],myData[10],data_offset_01,data_index_01,true,false,1);
	ChartQueue[2 ].GetNewData( myData[11],myData[12],myData[13],myData[14],data_offset_02,data_index_02,true,false,2);
	ChartQueue[3 ].GetNewData( myData[15],myData[16],myData[17],myData[18],data_offset_03,data_index_03,true,false,3);
	ChartQueue[4 ].GetNewData( myData[19],myData[20],myData[21],myData[22],data_offset_04,data_index_04,true,false,4);
	ChartQueue[5 ].GetNewData( myData[23],myData[24],myData[25],myData[26],data_offset_05,data_index_05,true,false,5);
	ChartQueue[6 ].GetNewData( myData[28],myData[29],myData[30],myData[31],data_offset_06,data_index_06,false,true,6);
	ChartQueue[7 ].GetNewData( myData[32],myData[33],myData[34],myData[35],data_offset_07,data_index_07,true,false,7);
	ChartQueue[8 ].GetNewData( myData[36],myData[37],myData[38],myData[39],data_offset_08,data_index_08,true,false,8);
	ChartQueue[9 ].GetNewData( myData[44],myData[45],myData[46],myData[47],data_offset_09,data_index_09,false,false,9);
	ChartQueue[10].GetNewData( myData[48],myData[49],myData[50],myData[51],data_offset_10,data_index_10,false,false,10);
	ChartQueue[11].GetNewData( myData[52],myData[53],myData[54],myData[55],data_offset_11,data_index_11,false,false,11);
	ChartQueue[12].GetNewData( myData[56],myData[57],myData[58],myData[59],data_offset_12,data_index_12,false,false,12);
	ChartQueue[13].GetNewData( myData[60],myData[61],myData[62],myData[63],data_offset_13,data_index_13,false,false,13);
	ChartQueue[14].GetNewData( myData[64],myData[65],myData[66],myData[67],data_offset_14,data_index_14,false,false,14);
	ChartQueue[15].GetNewData( myData[68],myData[69],myData[70],myData[71],data_offset_15,data_index_15,false,false,15);
	ChartQueue[16].GetNewData( myData[72],myData[73],myData[74],myData[75],data_offset_16,data_index_16,false,false,16);
	ChartQueue[17].GetNewData( myData[76],myData[77],myData[78],myData[79],data_offset_17,data_index_17,true,false,17);
	ChartQueue[18].GetNewData( myData[80],myData[81],myData[82],myData[83],data_offset_18,data_index_18,true,false,18);
	ChartQueue[19].GetNewData( myData[84],myData[85],myData[86],myData[87],data_offset_19,data_index_19,true,false,19);
	ChartQueue[20].GetNewData( myData[88],myData[89],myData[90],myData[91],data_offset_20,data_index_20,true,false,20);
	ChartQueue[21].GetNewData( myData[92],myData[93],myData[94],myData[95],data_offset_21,data_index_21,true,false,21);
	ChartQueue[22].GetNewData( myData[96],myData[97],myData[98],myData[99],data_offset_22,data_index_22,true,false,22);
	ChartQueue[23].GetNewData( myData[100],myData[101],myData[102],myData[103],data_offset_23,data_index_23,true,false,23);
	ChartQueue[24].GetNewData( myData[104],myData[105],myData[106],myData[107],data_offset_24,data_index_24,true,false,24);
	ChartQueue[25].GetNewData( myData[108],myData[109],myData[110],myData[111],data_offset_25,data_index_25,true,false,25);
	ChartQueue[26].GetNewData( myData[15],myData[16],myData[17],myData[18],data_offset_26,data_index_26,true,false,26);
}
//---------------------------------------------------------------------------



void TmainForm::UpdateCharts(int len, bool frist)
{
	double time_dots = (double)(max_rec_time * len)/max_rec_dots;
	double scale = time_dots / len;

//	Time
	scale = Time;
	if(ch1){
		ch1->X_dots = scale;
		ch1->Top = 0;
		ch1->Left = 0;
		ch1->Height = mainPanel->Height/4;
		ch1->Width = mainPanel->Width;

		ch1->Chart->Width = ch1->Width;
		ch1->Chart->Height = ch1->Height - ch1->Panel_Top->Height;
		ch1->Chart->Left = 0;
		ch1->Chart->Top = ch1->Panel_Top->Height;
		if(!frist){
			ch1->ComboBox_Wave->ItemIndex = 0;
			ch1->ComboBox_WaveChange(NULL);
		}
	}
	LogToFile("TmainForm: UpdateCharts: UpdateCharts: ch1");

	if(ch2){
		ch2->X_dots = scale;
		ch2->Top = ch1->Height;
		ch2->Left = 0;
		ch2->Height = mainPanel->Height/4;
		ch2->Width = mainPanel->Width;
		ch2->Align = alBottom;
		if(!frist){
			ch2->ComboBox_Wave->ItemIndex = 0;
			ch2->ComboBox_WaveChange(NULL);
		}
	}
	LogToFile("TmainForm: UpdateCharts: UpdateCharts: ch2");

	if(ch3){
		ch3->X_dots = scale;
		ch3->Top = ch2->Top + ch2->Height;
		ch3->Left = 0;
		ch3->Height = mainPanel->Height/4;
		ch3->Width = mainPanel->Width;
		if(!frist){
			ch3->ComboBox_Wave->ItemIndex = 0;
			ch3->ComboBox_WaveChange(NULL);
		}
	}
	LogToFile("TmainForm: UpdateCharts: UpdateCharts: ch3");

	if(ch4){
		ch4->X_dots = scale;
		ch4->Top = ch3->Top + ch3->Height;
		ch4->Left = 0;
		ch4->Height = mainPanel->Height/4;
		ch4->Width = mainPanel->Width;
		if(!frist){
			ch4->ComboBox_Wave->ItemIndex = 0;
			ch4->ComboBox_WaveChange(NULL);
		}
	}
	LogToFile("TmainForm: UpdateCharts: UpdateCharts: ch4");

	Lable_Status->Caption = "    Waves Loaded .";
}
//---------------------------------------------------------------------------





void __fastcall TmainForm::Exit1Click(TObject *Sender)
{
	Application->Terminate();
}
//---------------------------------------------------------------------------

void __fastcall TmainForm::Open1Click(TObject *Sender)
{
	button_OpenClick(NULL);
}
//---------------------------------------------------------------------------

void TmainForm::ConfigOsc()
{
	TIniFile *iniFile = new TIniFile(GetCurrentDir()+ "/viewer.ini");

	max_rec_time = iniFile->ReadInteger("MAIN","max_record_time",10);

	max_rec_time = max_rec_time * 1000;
	max_rec_dots = 38800;

	data_name_00 = iniFile->ReadString("OSC_CONFIG_00","name","");
	data_name_01 = iniFile->ReadString("OSC_CONFIG_01","name","");
	data_name_02 = iniFile->ReadString("OSC_CONFIG_02","name","");
	data_name_03 = iniFile->ReadString("OSC_CONFIG_03","name","");
	data_name_04 = iniFile->ReadString("OSC_CONFIG_04","name","");
	data_name_05 = iniFile->ReadString("OSC_CONFIG_05","name","");
	data_name_06 = iniFile->ReadString("OSC_CONFIG_06","name","");
	data_name_07 = iniFile->ReadString("OSC_CONFIG_07","name","");
	data_name_08 = iniFile->ReadString("OSC_CONFIG_08","name","");
	data_name_09 = iniFile->ReadString("OSC_CONFIG_09","name","");
	data_name_10 = iniFile->ReadString("OSC_CONFIG_10","name","");
	data_name_11 = iniFile->ReadString("OSC_CONFIG_11","name","");
	data_name_12 = iniFile->ReadString("OSC_CONFIG_12","name","");
	data_name_13 = iniFile->ReadString("OSC_CONFIG_13","name","");
	data_name_14 = iniFile->ReadString("OSC_CONFIG_14","name","");
	data_name_15 = iniFile->ReadString("OSC_CONFIG_15","name","");
	data_name_16 = iniFile->ReadString("OSC_CONFIG_16","name","");
	data_name_17 = iniFile->ReadString("OSC_CONFIG_17","name","");
	data_name_18 = iniFile->ReadString("OSC_CONFIG_18","name","");
	data_name_19 = iniFile->ReadString("OSC_CONFIG_19","name","");
	data_name_20 = iniFile->ReadString("OSC_CONFIG_20","name","");
	data_name_21 = iniFile->ReadString("OSC_CONFIG_21","name","");
	data_name_22 = iniFile->ReadString("OSC_CONFIG_22","name","");
	data_name_23 = iniFile->ReadString("OSC_CONFIG_23","name","");
	data_name_24 = iniFile->ReadString("OSC_CONFIG_24","name","");
	data_name_25 = iniFile->ReadString("OSC_CONFIG_25","name","");
	data_name_26 = iniFile->ReadString("OSC_CONFIG_26","name","");

	data_unit_00 = iniFile->ReadString("OSC_CONFIG_00","unit","");
	data_unit_01 = iniFile->ReadString("OSC_CONFIG_01","unit","");
	data_unit_02 = iniFile->ReadString("OSC_CONFIG_02","unit","");
	data_unit_03 = iniFile->ReadString("OSC_CONFIG_03","unit","");
	data_unit_04 = iniFile->ReadString("OSC_CONFIG_04","unit","");
	data_unit_05 = iniFile->ReadString("OSC_CONFIG_05","unit","");
	data_unit_06 = iniFile->ReadString("OSC_CONFIG_06","unit","");
	data_unit_07 = iniFile->ReadString("OSC_CONFIG_07","unit","");
	data_unit_08 = iniFile->ReadString("OSC_CONFIG_08","unit","");
	data_unit_09 = iniFile->ReadString("OSC_CONFIG_09","unit","");
	data_unit_10 = iniFile->ReadString("OSC_CONFIG_10","unit","");
	data_unit_11 = iniFile->ReadString("OSC_CONFIG_11","unit","");
	data_unit_12 = iniFile->ReadString("OSC_CONFIG_12","unit","");
	data_unit_13 = iniFile->ReadString("OSC_CONFIG_13","unit","");
	data_unit_14 = iniFile->ReadString("OSC_CONFIG_14","unit","");
	data_unit_15 = iniFile->ReadString("OSC_CONFIG_15","unit","");
	data_unit_16 = iniFile->ReadString("OSC_CONFIG_16","unit","");
	data_unit_17 = iniFile->ReadString("OSC_CONFIG_17","unit","");
	data_unit_18 = iniFile->ReadString("OSC_CONFIG_18","unit","");
	data_unit_19 = iniFile->ReadString("OSC_CONFIG_19","unit","");
	data_unit_20 = iniFile->ReadString("OSC_CONFIG_20","unit","");
	data_unit_21 = iniFile->ReadString("OSC_CONFIG_21","unit","");
	data_unit_22 = iniFile->ReadString("OSC_CONFIG_22","unit","");
	data_unit_23 = iniFile->ReadString("OSC_CONFIG_23","unit","");
	data_unit_24 = iniFile->ReadString("OSC_CONFIG_24","unit","");
	data_unit_25 = iniFile->ReadString("OSC_CONFIG_25","unit","");
	data_unit_26 = iniFile->ReadString("OSC_CONFIG_26","unit","");

	data_index_00 = iniFile->ReadFloat("OSC_CONFIG_00","index",1);
	data_index_01 = iniFile->ReadFloat("OSC_CONFIG_01","index",1);
	data_index_02 = iniFile->ReadFloat("OSC_CONFIG_02","index",1);
	data_index_03 = iniFile->ReadFloat("OSC_CONFIG_03","index",1);
	data_index_04 = iniFile->ReadFloat("OSC_CONFIG_04","index",1);
	data_index_05 = iniFile->ReadFloat("OSC_CONFIG_05","index",1);
	data_index_06 = iniFile->ReadFloat("OSC_CONFIG_06","index",1);
	data_index_07 = iniFile->ReadFloat("OSC_CONFIG_07","index",1);
	data_index_08 = iniFile->ReadFloat("OSC_CONFIG_08","index",1);
	data_index_09 = iniFile->ReadFloat("OSC_CONFIG_09","index",1);
	data_index_10 = iniFile->ReadFloat("OSC_CONFIG_10","index",1);
	data_index_11 = iniFile->ReadFloat("OSC_CONFIG_11","index",1);
	data_index_12 = iniFile->ReadFloat("OSC_CONFIG_12","index",1);
	data_index_13 = iniFile->ReadFloat("OSC_CONFIG_13","index",1);
	data_index_14 = iniFile->ReadFloat("OSC_CONFIG_14","index",1);
	data_index_15 = iniFile->ReadFloat("OSC_CONFIG_15","index",1);
	data_index_16 = iniFile->ReadFloat("OSC_CONFIG_16","index",1);
	data_index_17 = iniFile->ReadFloat("OSC_CONFIG_17","index",1);
	data_index_18 = iniFile->ReadFloat("OSC_CONFIG_18","index",1);
	data_index_19 = iniFile->ReadFloat("OSC_CONFIG_19","index",1);
	data_index_20 = iniFile->ReadFloat("OSC_CONFIG_20","index",1);
	data_index_21 = iniFile->ReadFloat("OSC_CONFIG_21","index",1);
	data_index_22 = iniFile->ReadFloat("OSC_CONFIG_22","index",1);
	data_index_23 = iniFile->ReadFloat("OSC_CONFIG_23","index",1);
	data_index_24 = iniFile->ReadFloat("OSC_CONFIG_24","index",1);
	data_index_25 = iniFile->ReadFloat("OSC_CONFIG_25","index",1);
	data_index_26 = iniFile->ReadFloat("OSC_CONFIG_26","index",1);

	data_offset_00 = iniFile->ReadFloat("OSC_CONFIG_00","offset",0);
	data_offset_01 = iniFile->ReadFloat("OSC_CONFIG_01","offset",0);
	data_offset_02 = iniFile->ReadFloat("OSC_CONFIG_02","offset",0);
	data_offset_03 = iniFile->ReadFloat("OSC_CONFIG_03","offset",0);
	data_offset_04 = iniFile->ReadFloat("OSC_CONFIG_04","offset",0);
	data_offset_05 = iniFile->ReadFloat("OSC_CONFIG_05","offset",0);
	data_offset_06 = iniFile->ReadFloat("OSC_CONFIG_06","offset",0);
	data_offset_07 = iniFile->ReadFloat("OSC_CONFIG_07","offset",0);
	data_offset_08 = iniFile->ReadFloat("OSC_CONFIG_08","offset",0);
	data_offset_09 = iniFile->ReadFloat("OSC_CONFIG_09","offset",0);
	data_offset_10 = iniFile->ReadFloat("OSC_CONFIG_10","offset",0);
	data_offset_11 = iniFile->ReadFloat("OSC_CONFIG_11","offset",0);
	data_offset_12 = iniFile->ReadFloat("OSC_CONFIG_12","offset",0);
	data_offset_13 = iniFile->ReadFloat("OSC_CONFIG_13","offset",0);
	data_offset_14 = iniFile->ReadFloat("OSC_CONFIG_14","offset",0);
	data_offset_15 = iniFile->ReadFloat("OSC_CONFIG_15","offset",0);
	data_offset_16 = iniFile->ReadFloat("OSC_CONFIG_16","offset",0);
	data_offset_17 = iniFile->ReadFloat("OSC_CONFIG_17","offset",0);
	data_offset_18 = iniFile->ReadFloat("OSC_CONFIG_18","offset",0);
	data_offset_19 = iniFile->ReadFloat("OSC_CONFIG_19","offset",0);
	data_offset_20 = iniFile->ReadFloat("OSC_CONFIG_20","offset",0);
	data_offset_21 = iniFile->ReadFloat("OSC_CONFIG_21","offset",0);
	data_offset_22 = iniFile->ReadFloat("OSC_CONFIG_22","offset",0);
	data_offset_23 = iniFile->ReadFloat("OSC_CONFIG_23","offset",0);
	data_offset_24 = iniFile->ReadFloat("OSC_CONFIG_24","offset",0);
	data_offset_25 = iniFile->ReadFloat("OSC_CONFIG_25","offset",0);
	data_offset_26 = iniFile->ReadFloat("OSC_CONFIG_26","offset",0);

	data_scale_00 = iniFile->ReadInteger("OSC_CONFIG_00","scale",0);
	data_scale_01 = iniFile->ReadInteger("OSC_CONFIG_01","scale",0);
	data_scale_02 = iniFile->ReadInteger("OSC_CONFIG_02","scale",0);
	data_scale_03 = iniFile->ReadInteger("OSC_CONFIG_03","scale",0);
	data_scale_04 = iniFile->ReadInteger("OSC_CONFIG_04","scale",0);
	data_scale_05 = iniFile->ReadInteger("OSC_CONFIG_05","scale",0);
	data_scale_06 = iniFile->ReadInteger("OSC_CONFIG_06","scale",0);
	data_scale_07 = iniFile->ReadInteger("OSC_CONFIG_07","scale",0);
	data_scale_08 = iniFile->ReadInteger("OSC_CONFIG_08","scale",0);
	data_scale_09 = iniFile->ReadInteger("OSC_CONFIG_09","scale",0);
	data_scale_10 = iniFile->ReadInteger("OSC_CONFIG_10","scale",0);
	data_scale_11 = iniFile->ReadInteger("OSC_CONFIG_11","scale",0);
	data_scale_12 = iniFile->ReadInteger("OSC_CONFIG_12","scale",0);
	data_scale_13 = iniFile->ReadInteger("OSC_CONFIG_13","scale",0);
	data_scale_14 = iniFile->ReadInteger("OSC_CONFIG_14","scale",0);
	data_scale_15 = iniFile->ReadInteger("OSC_CONFIG_15","scale",0);
	data_scale_16 = iniFile->ReadInteger("OSC_CONFIG_16","scale",0);
	data_scale_17 = iniFile->ReadInteger("OSC_CONFIG_17","scale",0);
	data_scale_18 = iniFile->ReadInteger("OSC_CONFIG_18","scale",0);
	data_scale_19 = iniFile->ReadInteger("OSC_CONFIG_19","scale",0);
	data_scale_20 = iniFile->ReadInteger("OSC_CONFIG_20","scale",0);
	data_scale_21 = iniFile->ReadInteger("OSC_CONFIG_21","scale",0);
	data_scale_22 = iniFile->ReadInteger("OSC_CONFIG_22","scale",0);
	data_scale_23 = iniFile->ReadInteger("OSC_CONFIG_23","scale",0);
	data_scale_24 = iniFile->ReadInteger("OSC_CONFIG_24","scale",0);
	data_scale_25 = iniFile->ReadInteger("OSC_CONFIG_25","scale",0);
	data_scale_26 = iniFile->ReadInteger("OSC_CONFIG_26","scale",0);

	rec_step = iniFile->ReadFloat("MAIN","rec_step",1);
	lastDir = iniFile->ReadString("MAIN","last_path","");

	delete  iniFile;
}
//---------------------------------------------------------------------------

void TmainForm::LogToFile(AnsiString Message)
{
//	Message = "Debug Brisk - " + TDateTime::CurrentDateTime().FormatString("yyyymmdd-hh:MM:ss.zzz") + " - " + Message;
	OutputDebugStringA(Message.c_str());
}
//---------------------------------------------------------------------------




