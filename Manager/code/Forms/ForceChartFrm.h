//---------------------------------------------------------------------------

#ifndef ForceChartFrmH
#define ForceChartFrmH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include "AdvGlowButton.hpp"
#include "CurvyControls.hpp"
#include "VCLTee.TeeComma.hpp"
#include "VCLTee.TeeEdit.hpp"
#include <Vcl.ExtCtrls.hpp>
#include <VCLTee.Chart.hpp>
#include <VCLTee.Series.hpp>
#include <VclTee.TeeGDIPlus.hpp>
#include <VCLTee.TeEngine.hpp>
#include <VCLTee.TeeProcs.hpp>
#include "VCLTee.TeeTools.hpp"
#include "AdvGlassButton.hpp"
#include "VCLTee.TeeSeriesRegion.hpp"
#include "htmlbtns.hpp"

#include <VCLTee.TeeThemeEditor.hpp>
#include "VCLTee.TeeSeriesBandTool.hpp"
//---------------------------------------------------------------------------
class TForceChartForm : public TForm
{
__published:	// IDE-managed Components
	TPanel *Panelbuttons;
	TAdvGlowButton *CloseButton;
	TChart *ChartChart;
	TCurvyCombo *ChartPicker;
	TChartEditor *ChartEditor1;
	TTeeCommander *TeeCommander1;
	TCursorTool *ChartTool1;
	TCursorTool *ChartTool2;
	TPanel *Panel1;
	TAdvGlassButton *X1AdvEditLbl;
	TCurvyEdit *X1AdvEdit;
	TPanel *Panel2;
	TAdvGlassButton *Y1AdvEditLbl;
	TCurvyEdit *Y1AdvEdit;
	TPanel *Panel3;
	TAdvGlassButton *Y2AdvEditLbl;
	TCurvyEdit *Y2AdvEdit;
	TPanel *Panel4;
	TAdvGlassButton *X2AdvEditLbl;
	TCurvyEdit *X2AdvEdit;
	TPanel *Panel5;
	TAdvGlassButton *dYdXAdvEditLbl;
	TCurvyEdit *dYdXAdvEdit;
	TDrawLineTool *ChartTool3;
	TFastLineSeries *Series101;
	TFastLineSeries *Series102;
	TPanel *Panel11;
	THTMLRadioButton *RadioButtonUnitZ;
	THTMLRadioButton *RadioButtonUnitTime;
	TAdvGlassButton *UnitLabel;
	TPanel *Panel6;
	TPanel *Panel7;
	TButton *YesButton;
	TButton *NoButton;
	TCurvyEdit *QuestionLabel;
	TPanel *Panel8;
	TCurvyEdit *KAdvEdit;
	TAdvGlassButton *KAdvEditLabel;
	TSeriesBandTool *ChartTool4;
	THTMLRadioButton *SlopeRadioButton;
	THTMLRadioButton *IntegralRadioButton;
	TAdvGlowButton *InvertYButton;
	TAdvGlowButton *InvertXButton;

	void __fastcall ChartPickerChange(TObject *Sender);
	void __fastcall FormCloseQuery(TObject *Sender, bool &CanClose);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall CloseButtonClic(TObject *Sender);
	void __fastcall FormShow(TObject *Sender);
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall ChartChartClickSeries(TCustomChart *Sender, TChartSeries *Series,
          int ValueIndex, TMouseButton Button, TShiftState Shift, int X,
		  int Y);
	void __fastcall RadioButtonUnitZClick(TObject *Sender);
	void __fastcall RadioButtonUnitTimeClick(TObject *Sender);
	void __fastcall ChartChartClickBackground(TCustomChart *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y);
	void __fastcall ChartTool1SnapChange(TCursorTool *Sender, int x, int y, const double XValue,
          const double YValue, TChartSeries *Series, int ValueIndex);
	void __fastcall ChartTool2SnapChange(TCursorTool *Sender, int x, int y, const double XValue,
          const double YValue, TChartSeries *Series, int ValueIndex);
	void __fastcall dYdXAdvEditKeyPress(TObject *Sender, System::WideChar &Key);
	void __fastcall YesButtonClick(TObject *Sender);
	void __fastcall NoButtonClick(TObject *Sender);
	void __fastcall KAdvEditChange(TObject *Sender);
	void __fastcall KAdvEditKeyPress(TObject *Sender, System::WideChar &Key);
	void __fastcall SlopeRadioButtonClick(TObject *Sender);
	void __fastcall IntegralRadioButtonClick(TObject *Sender);
	void __fastcall Y1AdvEditKeyPress(TObject *Sender, System::WideChar &Key);
	void __fastcall InvertXButtonClick(TObject *Sender);
	void __fastcall InvertYButtonClick(TObject *Sender);


private:	// User declarations
public:		// User declarations
	__fastcall TForceChartForm(TComponent* Owner);
	void SeriesValueLine(int x, int y,double* ValueX,double* ValueY,double *ValueIntercept,TCursorTool *charttools);
	double InterpolateSeries(double XValue);

	bool first;
	bool SameSeries;
    bool XInverted;
	void PickSeries(int series);
	void SetupChart();

	int FirstPoint;
	double Slope;
	bool SetReset;
	bool C_Factor_Set;
	double K_Factor;
    double y_bound;

	void ChartChartSetting(int series);
	void PanelButtonShow(int series);

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
	TFastLineSeries *Series28;


};
//---------------------------------------------------------------------------
extern PACKAGE TForceChartForm *ForceChartForm;
//---------------------------------------------------------------------------
#endif
