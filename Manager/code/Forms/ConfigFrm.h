//---------------------------------------------------------------------------

#ifndef ConfigFrmH
#define ConfigFrmH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include "AdvGlowButton.hpp"
#include <Vcl.ExtCtrls.hpp>
#include "AdvGlassButton.hpp"
#include "CurvyControls.hpp"
#include "ConfigTable.h"
#include "AdvWiiProgressBar.hpp"
//---------------------------------------------------------------------------
class TConfigForm : public TForm
{
__published:	// IDE-managed Components
	TAdvGlowButton *CloseButton;
	TAdvGlowButton *SaveButton;
	TAdvGlowButton *EditButton;
	TPanel *ButtonsPnl;
	TPanel *mainPanel;
	TPanel *menuPanel;
	TAdvGlowButton *InfoButton;
	TAdvGlowButton *LicenseButton;
	TAdvGlowButton *OscChartButton;
	TAdvGlowButton *oscButton;
	TAdvGlowButton *RetractButton;
	TAdvGlowButton *MoveButton;
	TAdvGlowButton *ApproachButton;
	TAdvGlowButton *ScanButton;
	TAdvGlowButton *DncButton;
	TAdvGlowButton *StageButton;
	TAdvGlowButton *ColibrationButton;
	TAdvGlowButton *HardwareButton;
	TPanel *PanelLabel;
	TAdvGlowButton *FastApproachButton;
	TLabel *LabelMonitor;
	TPanel *CentralPanel;
	TPanel *Panel7;
	TButton *YesButton;
	TButton *NoButton;
	TCurvyEdit *QuestionLabel;
	TPanel *Panel1;
	TPanel *Panel2;
	TButton *Button1;
	TAdvGlassButton *TAdvGlowButton1;
	TAdvGlassButton *AdvGlassButton1;
	TCurvyEdit *CurvyEdit1;
	TCurvyEdit *CurvyEdit2;
	TCurvyEdit *CurvyEdit3;
	TButton *Button2;
	TAdvWiiProgressBar *AdvWiiProgressBar;
	TLabel *Label1;
	void __fastcall CloseButtonClick(TObject *Sender);
	void __fastcall FormShow(TObject *Sender);
	void __fastcall LicenseButtonClick(TObject *Sender);
	void __fastcall InfoButtonClick(TObject *Sender);
	void __fastcall OscChartButtonClick(TObject *Sender);
	void __fastcall oscButtonClick(TObject *Sender);
	void __fastcall MoveButtonClick(TObject *Sender);
	void __fastcall StageButtonClick(TObject *Sender);
	void __fastcall RetractButtonClick(TObject *Sender);
	void __fastcall ApproachButtonClick(TObject *Sender);
	void __fastcall FastApproachButtonClick(TObject *Sender);
	void __fastcall ScanButtonClick(TObject *Sender);
	void __fastcall HardwareButtonClick(TObject *Sender);
	void __fastcall DncButtonClick(TObject *Sender);
	void __fastcall ColibrationButtonClick(TObject *Sender);
	void __fastcall SaveButtonClick(TObject *Sender);
	void __fastcall YesButtonClick(TObject *Sender);
	void __fastcall Cancel(TObject *Sender);
	void __fastcall EditButtonClick(TObject *Sender);
	void __fastcall Button1Click(TObject *Sender);
	void __fastcall Button2Click(TObject *Sender);
	void __fastcall CurvyEdit2KeyPress(TObject *Sender, System::WideChar &Key);
private:	// User declarations
public:		// User declarations
	__fastcall TConfigForm(TComponent* Owner);

	TConfTable* myConfTable[13];

	void InitValues();
	void CreatObjects();
	void ReConfigProgram();
	void PrepareToExit();
	void PickList(int Table);
	int ColumnNumber;
	int TableNumber;

	bool first;
	bool SaveBtn;
	bool CloseBtn;
    bool EditBtn;



};
//---------------------------------------------------------------------------
extern PACKAGE TConfigForm *ConfigForm;
//---------------------------------------------------------------------------
#endif
