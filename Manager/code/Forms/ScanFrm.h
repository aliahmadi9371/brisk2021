//---------------------------------------------------------------------------

#ifndef ScanFrmH
#define ScanFrmH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include "AdvCombo.hpp"
#include "AdvEdit.hpp"
#include "AdvGlowButton.hpp"
#include "CalcEdit.hpp"
#include "CurvyControls.hpp"
#include <Vcl.ExtCtrls.hpp>

#include "AdvGlassButton.hpp"
#include "AdvPanel.hpp"
//---------------------------------------------------------------------------
class TScanPanelForm : public TForm
{
__published:	// IDE-managed Components
	TCheckBox *ContinuousCheckBox;
	TCheckBox *TwoD_CheckBox;
	TCheckBox *OneD_CheckBox;
	TPanel *Panel1;
	TPanel *Panel2;
	TPanel *Panel3;
	TPanel *Panel4;
	TPanel *Panel5;
	TPanel *Panel6;
	TPanel *Panel7;
	TCurvyCombo *AdvComboBoxResolution;
	TAdvGlowButton *OneDButton;
	TAdvGlowButton *TwoDButton;
	TAdvGlassButton *AdvEditOverScanLbl;
	TAdvGlassButton *AdvEditSpeedLbl;
	TAdvGlassButton *AdvEditCenterXLbl;
	TAdvGlassButton *AdvEditCenterYLbl;
	TAdvGlassButton *AdvEditAngleLbl;
	TAdvGlassButton *AdvEditRangeLbl;
	TAdvGlassButton *AdvComboBoxResolutionLbl;
	TCurvyEdit *AdvEditOverScan;
	TCurvyEdit *AdvEditRange;
	TCurvyEdit *AdvEditAngle;
	TCurvyEdit *AdvEditCenterY;
	TCurvyEdit *AdvEditCenterX;
	TCurvyEdit *AdvEditSpeed;
	TAdvPanel *PanelSubScan;
	TPanel *PanelLabelScan;
	TLabel *LabelScan;
	TPanel *Panel8;
	TCurvyEdit *AdvEditOffset;
	TAdvGlassButton *AdvEditOffsetLbl;
	TPanel *Panel9;
	TCurvyCombo *AdvComboBoxSelect;
	TAdvGlassButton *AdvEditSelectLbl;
	TPanel *Panel10;
	TPanel *Panel11;
	TAdvGlassButton *KiFeedbackAdvEditLbl;
	TCurvyEdit *KiFeedbackAdvEdit;
	TPanel *Panel12;
	TAdvGlassButton *KdAdvEditLbl;
	TCurvyEdit *KdAdvEdit;
	TPanel *Panel13;
	TAdvGlassButton *KpAdvEditLbl;
	TCurvyEdit *KpAdvEdit;
	TPanel *Panel14;
	TAdvGlassButton *BiasAdvEditLbl;
	TCurvyEdit *BiasAdvEdit;
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall AdvEditOverScanKeyPress(TObject *Sender, System::WideChar &Key);
	void __fastcall AdvEditSpeedKeyPress(TObject *Sender, System::WideChar &Key);
	void __fastcall AdvEditAngleKeyPress(TObject *Sender, System::WideChar &Key);
	void __fastcall AdvEditRangeKeyPress(TObject *Sender, System::WideChar &Key);
	void __fastcall AdvEditCenterXKeyPress(TObject *Sender, System::WideChar &Key);
	void __fastcall AdvEditCenterYKeyPress(TObject *Sender, System::WideChar &Key);
	void __fastcall AdvComboBoxResolutionChange(TObject *Sender);
	void __fastcall OneD_CheckBoxClick(TObject *Sender);
	void __fastcall TwoD_CheckBoxClick(TObject *Sender);
	void __fastcall OneDButtonClick(TObject *Sender);
	void __fastcall TwoDButtonClick(TObject *Sender);
	void __fastcall FormShow(TObject *Sender);
	void __fastcall AdvEditOffsetKeyPress(TObject *Sender, System::WideChar &Key);
	void __fastcall AdvComboBoxSelectChange(TObject *Sender);
	void __fastcall AdvEditOverScanChange(TObject *Sender);
	void __fastcall AdvEditSpeedChange(TObject *Sender);
	void __fastcall AdvEditCenterXChange(TObject *Sender);
	void __fastcall AdvEditCenterYChange(TObject *Sender);
	void __fastcall AdvEditAngleChange(TObject *Sender);
	void __fastcall AdvEditRangeChange(TObject *Sender);
	void __fastcall AdvEditOffsetChange(TObject *Sender);
	void __fastcall AdvComboBoxSelectKeyPress(TObject *Sender, System::WideChar &Key);
	void __fastcall KiFeedbackAdvEditKeyPress(TObject *Sender, System::WideChar &Key);
	void __fastcall KdAdvEditKeyPress(TObject *Sender, System::WideChar &Key);
	void __fastcall KpAdvEditKeyPress(TObject *Sender, System::WideChar &Key);
	void __fastcall KpAdvEditChange(TObject *Sender);
	void __fastcall KdAdvEditChange(TObject *Sender);
	void __fastcall KiFeedbackAdvEditChange(TObject *Sender);
	void __fastcall BiasAdvEditChange(TObject *Sender);
	void __fastcall BiasAdvEditKeyPress(TObject *Sender, System::WideChar &Key);








private:	// User declarations
	void __fastcall SetScan();

public:		// User declarations
	__fastcall TScanPanelForm(TComponent* Owner);


	void HighLightChanger(int Changer, bool highlight);

	void GetIniToUi();
//	void SaveToIni();

	int Resolution;
	int Angle;
	double Range;
	double OverScan;
	double Speed;
	double CenterX;
	double CenterY;
	double FlyOffset;
	double X_Range;
	double Y_Range;
	int Max_Range;
    int KdApp;
	int KpApp;
	int KiFeedback_Contact;
	int KiFeedback_NonContact;
    int BiasApp;

    int CurrentZ;

	double FlyOffset_index;
	double FlyOffset_Scale;

	double Min_Z;

	double Regression(double First , double Second , double diff );

	void X_Calibration();
	void Y_Calibration();
	void Range_Calibration();

	double Reverse_X_Calibration();
	double Reverse_Y_Calibration();
	double Reverse_Range_Calibration();


	bool One_D;
	bool Two_D;


	int LastScanChanger;

	bool start;

	void AdvEditChange(double x_center, double y_center, double range);

	void AddToHistory();
	double X_Center[10];
	double Y_Center[10];
	double XY_Range[10];

	double Center_X_um;
	double Center_Y_um;

	int HistoryIndex;
	int HistoryCount;

	void AllEditWhite();

	bool checkPermission();

};
//---------------------------------------------------------------------------
extern PACKAGE TScanPanelForm *ScanPanelForm;
//---------------------------------------------------------------------------
#endif
