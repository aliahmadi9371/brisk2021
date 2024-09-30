//---------------------------------------------------------------------------

#ifndef LithoConfigPageH
#define LithoConfigPageH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include "AdvGlassButton.hpp"
#include "CurvyControls.hpp"
#include <Vcl.ExtCtrls.hpp>
#include "AdvGlowButton.hpp"
#include "AdvWiiProgressBar.hpp"
#include "LitoFileCreatorUnit.h"

//---------------------------------------------------------------------------
class TFormLithoConfig : public TForm
{
__published:	// IDE-managed Components
	TPanel *Panel6;
	TAdvGlassButton *AdvEditDelayLbl;
	TCurvyEdit *AdvEditDelay;
	TPanel *Panel1;
	TAdvGlassButton *AdvEditCenterXLbl;
	TCurvyEdit *AdvEditCenterX;
	TPanel *Panel2;
	TAdvGlassButton *AdvEditCenterYLbl;
	TCurvyEdit *AdvEditCenterY;
	TPanel *Panel3;
	TAdvGlassButton *AdvEditRangeLbl;
	TCurvyEdit *AdvEditRange;
	TPanel *Panel4;
	TCurvyCombo *AdvComboBoxResolution;
	TAdvGlassButton *AdvComboBoxResolutionLbl;
	TPanel *Panel5;
	TAdvGlassButton *AdvEditOverScanLbl;
	TCurvyEdit *AdvEditOverScan;
	TAdvGlowButton *RunAdvGlassButton;
	TAdvWiiProgressBar *AdvWiiProgressBar;
	TLabel *Label1;
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall RunAdvGlassButtonClick(TObject *Sender);
	void __fastcall FormShow(TObject *Sender);
	void __fastcall AdvEditCenterXKeyPress(TObject *Sender, System::WideChar &Key);
	void __fastcall AdvEditCenterYKeyPress(TObject *Sender, System::WideChar &Key);
	void __fastcall AdvEditRangeKeyPress(TObject *Sender, System::WideChar &Key);
	void __fastcall AdvEditDelayKeyPress(TObject *Sender, System::WideChar &Key);
	void __fastcall AdvComboBoxResolutionChange(TObject *Sender);
	void __fastcall AdvEditOverScanKeyPress(TObject *Sender, System::WideChar &Key);
	void __fastcall AdvEditCenterXChange(TObject *Sender);
	void __fastcall AdvEditCenterYChange(TObject *Sender);
	void __fastcall AdvEditRangeChange(TObject *Sender);
	void __fastcall AdvEditOverScanChange(TObject *Sender);
	void __fastcall AdvEditDelayChange(TObject *Sender);




private:	// User declarations

public:		// User declarations
	__fastcall TFormLithoConfig(TComponent* Owner);

	void __fastcall StartLitho();

	void ConfigClass();
	void InitClass();

	void HighLightChanger(int Changer, bool highlight);

	void EnabledPanels(int state);
	void UpDownBorder(TGlowButtonAppearance* appearance, bool UpDown);
	void GetResolution();


	void AllEditWhite();
    void X_Calibration();
	void Y_Calibration();
	void Range_Calibration();


	int scan_resolution;
	int scan_speed;
	int scan_overscan;
	double scan_x_center;
	double scan_y_center;
	double scan_range;
	int litho_delay;
	bool litho_startstop;
	bool litho_select;
	double scan_Yrange;
	double scan_Xrange;
	double scan_max_range;
	double CenterXX;
    double CenterYY;

	bool first;
	bool firstFirst;

	int LastLithoChanger;
	void AdvEditChange(double x, double y, double range);

	bool changeRes;

	double Regression(double First , double Second , double diff);

	LithoFileCreatorThread* myLithoThread;
};
//---------------------------------------------------------------------------
extern PACKAGE TFormLithoConfig *FormLithoConfig;
//---------------------------------------------------------------------------
#endif
