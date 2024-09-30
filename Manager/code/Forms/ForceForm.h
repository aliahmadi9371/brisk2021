//---------------------------------------------------------------------------

#ifndef ForceFormH
#define ForceFormH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include "AdvGlassButton.hpp"
#include "AdvGlowButton.hpp"
#include "AdvPanel.hpp"
#include "AdvWiiProgressBar.hpp"
#include "CurvyControls.hpp"
#include "VCLTee.TeeTools.hpp"
#include <Vcl.ExtCtrls.hpp>
#include <VCLTee.Chart.hpp>
#include <VCLTee.Series.hpp>
#include <VclTee.TeeGDIPlus.hpp>
#include <VCLTee.TeEngine.hpp>
#include <VCLTee.TeeProcs.hpp>
#include "VCLTee.TeeComma.hpp"
#include "VCLTee.TeeEdit.hpp"
#include "ForceChartFrm.h"
#include "htmlbtns.hpp"
//---------------------------------------------------------------------------
class TForceFrm : public TForm
{
__published:	// IDE-managed Components
	TPanel *FsPanel;
	TAdvPanel *PanelSubFs;
	TPanel *PanelRunForce;
	TAdvGlowButton *RunAdvGlassButton;
	TPanel *ChartPanel;
	TChart *ChartChart;
	TCurvyCombo *ChartPicker;
	TFastLineSeries *Series1;
	TFastLineSeries *Series2;
	TFastLineSeries *Series3;
	TFastLineSeries *Series4;
	TFastLineSeries *Series5;
	TFastLineSeries *Series6;
	TFastLineSeries *Series7;
	TFastLineSeries *Series8;
	TFastLineSeries *Series9;
	TFastLineSeries *Series10;
	TFastLineSeries *Series11;
	TFastLineSeries *Series12;
	TTeeCommander *TeeCommander1;
	TPanel *PanelLabelFs;
	TLabel *LabelFs;
	TPanel *Panel5;
	TAdvGlassButton *ResAdvComboBoxLbl;
	TCurvyCombo *ResAdvComboBox;
	TPanel *Panel2;
	TAdvGlassButton *YAdvEditLbl;
	TCurvyEdit *YAdvEdit;
	TPanel *Panel3;
	TAdvGlassButton *DelayAdvEditLbl;
	TCurvyEdit *DelayAdvEdit;
	TPanel *Panel8;
	TAdvGlassButton *Z1AdvEditLbl;
	TCurvyEdit *Z1AdvEdit;
	TPanel *Panel6;
	TAdvGlassButton *U1AdvEditLbl;
	TCurvyEdit *U1AdvEdit;
	TPanel *Panel7;
	TAdvGlassButton *U2AdvEditLbl;
	TCurvyEdit *U2AdvEdit;
	TPanel *Panel9;
	TAdvGlassButton *Z2AdvEditLbl;
	TCurvyEdit *Z2AdvEdit;
	TPanel *Panel4;
	TAdvGlassButton *ModesAdvComboBoxLbl;
	TCurvyCombo *ModesAdvComboBox;
	TPanel *Panel1;
	TAdvGlassButton *XAdvEditLbl;
	TCurvyEdit *XAdvEdit;
	TChartEditor *ChartEditor1;
	TPanel *Panel10;
	TAdvGlowButton *AdvGlowButton1;
	TFastLineSeries *Series13;
	TFastLineSeries *Series14;
	TFastLineSeries *Series15;
	TFastLineSeries *Series16;
	TFastLineSeries *Series17;
	TFastLineSeries *Series18;
	TFastLineSeries *Series19;
	TFastLineSeries *Series20;
	TFastLineSeries *Series21;
	TFastLineSeries *Series22;
	TFastLineSeries *Series23;
	TFastLineSeries *Series24;
	TFastLineSeries *Series25;
	TFastLineSeries *Series26;
	TFastLineSeries *Series27;
	THTMLRadioButton *RadioButtonUnitZ;
	THTMLRadioButton *RadioButtonUnitTime;
	TAdvGlassButton *UnitLabel;
	TFastLineSeries *Series28;
	TPanel *Panel11;
	TAdvGlassButton *CFactorEditLbl;
	TCurvyEdit *CFactorEdit;
	TPanel *Panel12;
	TPanel *Panel13;
	TPanel *Panel14;
	TAdvGlowButton *InvertXButton;
	TAdvGlowButton *InvertYButton;
	TTimer *ForceStartTimer;
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall FormShow(TObject *Sender);
	void __fastcall RunAdvGlassButtonClick(TObject *Sender);
	void __fastcall XAdvEditKeyPress(TObject *Sender, System::WideChar &Key);
	void __fastcall YAdvEditKeyPress(TObject *Sender, System::WideChar &Key);
	void __fastcall DelayAdvEditKeyPress(TObject *Sender, System::WideChar &Key);
	void __fastcall U1AdvEditKeyPress(TObject *Sender, System::WideChar &Key);
	void __fastcall U2AdvEditKeyPress(TObject *Sender, System::WideChar &Key);
	void __fastcall Z2AdvEditKeyPress(TObject *Sender, System::WideChar &Key);
	void __fastcall Z1AdvEditKeyPress(TObject *Sender, System::WideChar &Key);
	void __fastcall ResAdvComboBoxChange(TObject *Sender);
	void __fastcall ModesAdvComboBoxChange(TObject *Sender);
	void __fastcall ChartPickerChange(TObject *Sender);
	void __fastcall AdvGlowButton1Click(TObject *Sender);
	void __fastcall XAdvEditChange(TObject *Sender);
	void __fastcall YAdvEditChange(TObject *Sender);
	void __fastcall DelayAdvEditChange(TObject *Sender);
	void __fastcall U1AdvEditChange(TObject *Sender);
	void __fastcall U2AdvEditChange(TObject *Sender);
	void __fastcall Z1AdvEditChange(TObject *Sender);
	void __fastcall Z2AdvEditChange(TObject *Sender);
	void __fastcall RadioButtonUnitZClick(TObject *Sender);
	void __fastcall RadioButtonUnitTimeClick(TObject *Sender);
	void __fastcall InvertXButtonClick(TObject *Sender);
	void __fastcall InvertYButtonClick(TObject *Sender);
	void __fastcall ForceStartTimerTimer(TObject *Sender);



private:	// User declarations
	void __fastcall StartFs();
	void __fastcall StopFs();
public:		// User declarations
	__fastcall TForceFrm(TComponent* Owner);
	void ShowLables(int mode);
	void PickSeries(int series);
	void InitValues();
	void ConfigClass();
	void ClearSeries(int series);
	void ClearSeries();
	void GetCurrentZ();
	void GetCurrentU();

	void X_Calibration();
	void Y_Calibration();
	double Regression(double First , double Second , double diff);

	double Reverse_X_Calibration();
	double Reverse_Y_Calibration();

	void EnableFsPanel(int enabled);
	void UpDownBorder(TGlowButtonAppearance* appearance, bool UpDown);

	void SetupChart();

    void AllEditWhite();

	int GetResolution(int res_index);
	void EnabledPanels(int mode);

	double StartX;
	double StartY;

	double dZ1;
	double dZ2;

	int U1;
	int U2;

	int DelayNumber;
	int Delay;

	int Resolution;
	int Mode;

	int ResolutionIndex;
	int ModesIndex;

	int CurrentZ;
	int CurrentU;

	int Max_Range;

	double Start_X_um;
	double Start_Y_um;

	double index;
	double scale;

	double U_index;
	double U_Scale;

	bool first;

	int FsBtnState;

	bool checkPermission();

	double Finaldz;
	double Start_Topo;
	double Start_U;
	double FinalU;
	int FinalMode;
    int FinalResolution;
	bool Osc_PreviousState;
	bool XInverted;

	double Fs_C_Factor;



	void AdvEditChange(double x, double y);

	UnicodeString FsFolder;
	UnicodeString DateFolder;
	UnicodeString TimeFolder;

	void SetFolderNames();
	void ChartChartSetting(int series);


	TForceChartForm* myChartForm;
};
//---------------------------------------------------------------------------
extern PACKAGE TForceFrm *ForceFrm;
//---------------------------------------------------------------------------
#endif


