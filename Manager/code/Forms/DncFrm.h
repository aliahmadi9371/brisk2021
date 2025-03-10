//---------------------------------------------------------------------------

#ifndef DncFrmH
#define DncFrmH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <VCLTee.Chart.hpp>
#include <VCLTee.Series.hpp>
#include <VCLTee.TeEngine.hpp>
#include <VCLTee.TeeProcs.hpp>
#include "AdvEdit.hpp"
#include "AdvCombo.hpp"
#include "AdvGlassButton.hpp"

#include <IniFiles.hpp>
#include <System.SyncObjs.hpp>
#include "VCLTee.TeeTools.hpp"
#include "VCLTee.TeeComma.hpp"
#include <VclTee.TeeGDIPlus.hpp>
#include "AdvWiiProgressBar.hpp"
#include "AdvMenus.hpp"
#include <Vcl.Menus.hpp>

#include "CalcEdit.hpp"
#include "AdvGlowButton.hpp"
#include "CurvyControls.hpp"
#include "AdvPanel.hpp"
//---------------------------------------------------------------------------
class TDynamicCurveForm : public TForm
{
__published:	// IDE-managed Components
	TPanel *DncPanel;
	TChart *AmpChart;
	TPanel *AmpPanel;
	TAdvWiiProgressBar *AmpAdvWiiProgressBar;
	TFastLineSeries *AmpDncSeries;
	TColorLineTool *AmpChartToolX;
	TColorLineTool *AmpChartToolY;
	TColorBandTool *ColorBandChartTool;
	TPanel *Panel1;
	TPanel *Panel2;
	TPanel *Panel3;
	TPanel *Panel4;
	TPanel *Panel5;
	TPanel *Panel6;
	TPanel *Panel7;
	TCurvyCombo *TimeCntAdvComboBox;
	TAdvGlowButton *ContinuousButton;
	TPanel *PanelGain;
	TAdvGlowButton *AdvGlowButton100;
	TAdvGlowButton *AdvGlowButton10;
	TAdvGlowButton *AdvGlowButton1;
	TCalcLabel *CalcLabel3;
	TPanel *Panel8;
	TCurvyCombo *FromToComboBox;
	TAdvGlowButton *RunAdvGlassButton;
	TPanel *PanelRun;
	TPanel *Panel11;
	TPanel *Panel10;
	TAdvGlassButton *FromAdvEditLbl;
	TAdvGlassButton *ToAdvEditLbl;
	TAdvGlassButton *UseAdvEditLbl;
	TAdvGlassButton *SetPointAdvEditLbl;
	TAdvGlassButton *DriveAdvEditLbl;
	TAdvGlassButton *PointsAdvComboBoxLbl;
	TAdvGlassButton *TimeCntAdvComboBoxLbl;
	TAdvGlassButton *FromToComboBoxLbl;
	TAdvGlassButton *SetPAdvEditLbl;
	TAdvGlassButton *MaxAdvEditLbl;
	TCurvyCombo *PointsAdvComboBox;
	TCurvyEdit *FromAdvEdit;
	TCurvyEdit *ToAdvEdit;
	TCurvyEdit *UseAdvEdit;
	TCurvyEdit *SetPointAdvEdit;
	TCurvyEdit *DriveAdvEdit;
	TCurvyEdit *SetPAdvEdit;
	TCurvyEdit *MaxAdvEdit;
	TAdvPanel *PanelSubDnc;
	TPanel *PanelLabelDnc;
	TLabel *LabelDnc;
	TPanel *PanelSlider;
	TPanel *Panel9;
	TCurvyEdit *MaxAllAdvEdit;
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall RunAdvGlassButtonClick(TObject *Sender);
	void __fastcall SetDncAdvGlassButtonClick(TObject *Sender);
	void __fastcall AmpChartMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y);
	void __fastcall AmpChartMouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y);
	void __fastcall AmpChartClickSeries(TCustomChart *Sender, TChartSeries *Series,
          int ValueIndex, TMouseButton Button, TShiftState Shift, int X,
          int Y);
	void __fastcall AmpChartClickBackground(TCustomChart *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y);
	void __fastcall FormShow(TObject *Sender);
	void __fastcall AmpChartMouseMove(TObject *Sender, TShiftState Shift, int X, int Y);
	void __fastcall ColorBandChartToolResized(TObject *Sender);
	void __fastcall FromAdvEditKeyPress(TObject *Sender, System::WideChar &Key);
	void __fastcall ToAdvEditKeyPress(TObject *Sender, System::WideChar &Key);
	void __fastcall UseAdvEditKeyPress(TObject *Sender, System::WideChar &Key);
	void __fastcall DriveAdvEditKeyPress(TObject *Sender, System::WideChar &Key);
	void __fastcall SetPointAdvEditKeyPress(TObject *Sender, System::WideChar &Key);
	void __fastcall AmpChartClickAxis(TCustomChart *Sender, TChartAxis *Axis, TMouseButton Button,
          TShiftState Shift, int X, int Y);
	void __fastcall PointsAdvComboBoxChange(TObject *Sender);
	void __fastcall FromToComboBoxChange(TObject *Sender);
	void __fastcall AdvGlowButton1Click(TObject *Sender);
	void __fastcall AdvGlowButton10Click(TObject *Sender);
	void __fastcall AdvGlowButton100Click(TObject *Sender);
	void __fastcall ToAdvEditChange(TObject *Sender);
	void __fastcall FromAdvEditChange(TObject *Sender);
	void __fastcall UseAdvEditChange(TObject *Sender);
	void __fastcall SetPointAdvEditChange(TObject *Sender);
	void __fastcall DriveAdvEditChange(TObject *Sender);
	void __fastcall TimeCntAdvComboBoxChange(TObject *Sender);
	void __fastcall ColorBandChartToolDragging(TObject *Sender);




private:	// User declarations
	void __fastcall StartDnc();
public:		// User declarations
	__fastcall TDynamicCurveForm(TComponent* Owner);
	void EnableObjects(bool enabled);
//	void ValidateValues();
	void GetData();

	void MoveColorLineAmp(int x, int y,double* ValueX,double* ValueY,double *ValueIntercept);  //return use
	double InterpolateAmpDncSeries(double XValue);
	void UpDownBorder(TGlowButtonAppearance* appearance, bool UpDown);

	TRect rect;
	int TopLeftX;
	int TopLeftY;
	int BotRighX;
	int BotRightY;

    int DataCounter;

	bool in_dnc;
	bool start;
	bool first;

	int FromMin_Val;
	int From_Val;
	int To_Val;
	int ToMax_Val;
	int Use_Val;
	int Drive_Val;
	int PointsCount_Val;
	int SetPoint_Val;
	double TimeCnt_Val;
	int TimeCntIndex_Val;
//	int PointsCount;
	int Gain_Val;
	int Rolloff;
	int FreqStep;

    void Config();

	bool AmpDraging;

	int AmpXStart;
	int AmpYStart;

	int AmpXStop;
	int AmpYStop;

	int counterBand;

	int band1From;
	int band1To;

	int band2From;
	int band2To;

	int band3From;
	int band3To;

	int band4From;
	int band4To;

	bool contact;

	void SaveData();

	bool myfirst;


	double DriveIndex;
	double DriveOffset;

	int MainDriveVal;

	double MaxPointofUse;

	bool Gain1;
	bool Gain10;
	bool Gain100;

    void AllEditWhite();

};
//---------------------------------------------------------------------------
extern PACKAGE TDynamicCurveForm *DynamicCurveForm;
//---------------------------------------------------------------------------
#endif
