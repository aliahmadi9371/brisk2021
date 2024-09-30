//---------------------------------------------------------------------------

#ifndef mainUnitH
#define mainUnitH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.Dialogs.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <VCLTee.Chart.hpp>
#include <VclTee.TeeGDIPlus.hpp>
#include <VCLTee.TeEngine.hpp>
#include <VCLTee.TeeProcs.hpp>
#include <System.Classes.hpp>
#include <System.IOUtils.hpp>
#include <VCLTee.Series.hpp>
#include <IniFiles.hpp>
#include "AdvCircularProgress.hpp"
#include <Vcl.Menus.hpp>
#include "AdvOfficeStatusBar.hpp"
#include "AdvOfficeStatusBarStylers.hpp"

#include <iostream>
#include <fstream>
using namespace std;

#include "queueClass.h"
#include "oscClass.h"
//---------------------------------------------------------------------------
class TmainForm : public TForm
{
__published:	// IDE-managed Components
	TOpenDialog *dialog_Open;
	TPanel *mainPanel;
	TMainMenu *MainMenu1;
	TMenuItem *File1;
	TMenuItem *Open1;
	TMenuItem *Exit1;
	TAdvOfficeStatusBar *AdvOfficeStatusBar1;
	TAdvOfficeStatusBarOfficeStyler *AdvOfficeStatusBarOfficeStyler1;
	TLabel *Lable_Status;
	TLabel *Label_Status1;
	void __fastcall FormShow(TObject *Sender);
	void __fastcall FormResize(TObject *Sender);
	void __fastcall button_OpenClick(TObject *Sender);
	void __fastcall Exit1Click(TObject *Sender);
	void __fastcall Open1Click(TObject *Sender);

private:	// User declarations
	bool bool_Created;

	void LoadFileToQueue(UnicodeString fileName);
	void CteateQueue();
	void InitQueues();
	void ParsData(TByteDynArray myData);
	void ConfigOsc();
	void UpdateCharts(int len, bool frist);

	double Sum1;
	double Avg1;
	double Min1;
	double Max1;
	double Chg1;

	double Sum2;
	double Avg2;
	double Min2;
	double Max2;
	double Chg2;

	double Sum3;
	double Avg3;
	double Min3;
	double Max3;
	double Chg3;

	double Sum4;
	double Avg4;
	double Min4;
	double Max4;
	double Chg4;

	ToscForm *ch1;
	ToscForm *ch2;
	ToscForm *ch3;
	ToscForm *ch4;

	int max_rec_time; //sec
    int max_rec_dots;

public:		// User declarations
	__fastcall TmainForm(TComponent* Owner);
	__fastcall ~TmainForm();

	bool first;
	AnsiString lastDir;
	double Time;
	int Length;
	double rec_step;

	queueClass ChartQueue[27];
	UnicodeString data_name_00;
	UnicodeString data_unit_00;
	double data_index_00;
	double data_offset_00;
	int data_scale_00;

	UnicodeString data_name_01;
	UnicodeString data_unit_01;
	double data_index_01;
	double data_offset_01;
	int data_scale_01;

	UnicodeString data_name_02;
	UnicodeString data_unit_02;
	double data_index_02;
	double data_offset_02;
	int data_scale_02;

	UnicodeString data_name_03;
	UnicodeString data_unit_03;
	double data_index_03;
	double data_offset_03;
	int data_scale_03;

	UnicodeString data_name_04;
	UnicodeString data_unit_04;
	double data_index_04;
	double data_offset_04;
	int data_scale_04;

	UnicodeString data_name_05;
	UnicodeString data_unit_05;
	double data_index_05;
	double data_offset_05;
	int data_scale_05;

	UnicodeString data_name_06;
	UnicodeString data_unit_06;
	double data_index_06;
	double data_offset_06;
	int data_scale_06;

	UnicodeString data_name_07;
	UnicodeString data_unit_07;
	double data_index_07;
	double data_offset_07;
	int data_scale_07;

	UnicodeString data_name_08;
	UnicodeString data_unit_08;
	double data_index_08;
	double data_offset_08;
	int data_scale_08;

	UnicodeString data_name_09;
	UnicodeString data_unit_09;
	double data_index_09;
	double data_offset_09;
	int data_scale_09;

	UnicodeString data_name_10;
	UnicodeString data_unit_10;
	double data_index_10;
	double data_offset_10;
	int data_scale_10;

	UnicodeString data_name_11;
	UnicodeString data_unit_11;
	double data_index_11;
	double data_offset_11;
	int data_scale_11;

	UnicodeString data_name_12;
	UnicodeString data_unit_12;
	double data_index_12;
	double data_offset_12;
	int data_scale_12;

	UnicodeString data_name_13;
	UnicodeString data_unit_13;
	double data_index_13;
	double data_offset_13;
	int data_scale_13;

	UnicodeString data_name_14;
	UnicodeString data_unit_14;
	double data_index_14;
	double data_offset_14;
	int data_scale_14;

	UnicodeString data_name_15;
	UnicodeString data_unit_15;
	double data_index_15;
	double data_offset_15;
	int data_scale_15;

	UnicodeString data_name_16;
	UnicodeString data_unit_16;
	double data_index_16;
	double data_offset_16;
	int data_scale_16;

	UnicodeString data_name_17;
	UnicodeString data_unit_17;
	double data_index_17;
	double data_offset_17;
	int data_scale_17;

	UnicodeString data_name_18;
	UnicodeString data_unit_18;
	double data_index_18;
	double data_offset_18;
	int data_scale_18;

	UnicodeString data_name_19;
	UnicodeString data_unit_19;
	double data_index_19;
	double data_offset_19;
	int data_scale_19;

	UnicodeString data_name_20;
	UnicodeString data_unit_20;
	double data_index_20;
	double data_offset_20;
	int data_scale_20;

	UnicodeString data_name_21;
	UnicodeString data_unit_21;
	double data_index_21;
	double data_offset_21;
	int data_scale_21;

	UnicodeString data_name_22;
	UnicodeString data_unit_22;
	double data_index_22;
	double data_offset_22;
	int data_scale_22;

	UnicodeString data_name_23;
	UnicodeString data_unit_23;
	double data_index_23;
	double data_offset_23;
	int data_scale_23;

	UnicodeString data_name_24;
	UnicodeString data_unit_24;
	double data_index_24;
	double data_offset_24;
	int data_scale_24;

	UnicodeString data_name_25;
	UnicodeString data_unit_25;
	double data_index_25;
	double data_offset_25;
	int data_scale_25;

	UnicodeString data_name_26;
	UnicodeString data_unit_26;
	double data_index_26;
	double data_offset_26;
	int data_scale_26;

	void LogToFile(AnsiString Message);
};
//---------------------------------------------------------------------------
extern PACKAGE TmainForm *mainForm;
//---------------------------------------------------------------------------
#endif
