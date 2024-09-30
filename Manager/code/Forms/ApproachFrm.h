//---------------------------------------------------------------------------

#ifndef ApproachFrmH
#define ApproachFrmH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <IniFiles.hpp>
#include "AdvEdit.hpp"

#include <Vcl.ExtCtrls.hpp>
#include "CalcEdit.hpp"
#include "AdvGlassButton.hpp"
#include "CurvyControls.hpp"
#include "AdvPanel.hpp"
//---------------------------------------------------------------------------
class TApproachPanelForm : public TForm
{
__published:	// IDE-managed Components
	TCheckBox *AppCheckBox;
	TPanel *Panel1;
	TPanel *Panel2;
	TPanel *Panel3;
	TPanel *Panel4;
	TPanel *Panel5;
	TPanel *Panel6;
	TPanel *Panel7;
	TPanel *Panel8;
	TCheckBox *fast_checkbox;
	TAdvGlassButton *KiAdvEditLbl;
	TAdvGlassButton *KdAdvEditLbl;
	TAdvGlassButton *KpAdvEditLbl;
	TAdvGlassButton *BiasAdvEditLbl;
	TAdvGlassButton *StpAdvEditLbl;
	TAdvGlassButton *KiFeedbackAdvEditLbl;
	TAdvGlassButton *RefAdvEditLbl;
	TAdvGlassButton *LabelApproachStat;
	TCurvyEdit *KiAdvEdit;
	TCurvyEdit *KdAdvEdit;
	TCurvyEdit *KpAdvEdit;
	TCurvyEdit *BiasAdvEdit;
	TCurvyEdit *StpAdvEdit;
	TCurvyEdit *KiFeedbackAdvEdit;
	TCurvyEdit *RefAdvEdit;
	TCurvyEdit *EditApproachStat;
	TAdvPanel *PanelSubApproach;
	TPanel *PanelLabelApproch;
	TPanel *PanelSlider;
	TLabel *LabelApproach;

	void __fastcall FormCreate(TObject *Sender);
	void __fastcall FormShow(TObject *Sender);
	void __fastcall KiAdvEditKeyPress(TObject *Sender, System::WideChar &Key);
	void __fastcall BiasAdvEditKeyPress(TObject *Sender, System::WideChar &Key);
	void __fastcall StpAdvEditKeyPress(TObject *Sender, System::WideChar &Key);
	void __fastcall RefAdvEditKeyPress(TObject *Sender, System::WideChar &Key);
	void __fastcall KdAdvEditKeyPress(TObject *Sender, System::WideChar &Key);
	void __fastcall KpAdvEditKeyPress(TObject *Sender, System::WideChar &Key);
	void __fastcall KiFeebackAdvEditKeyPress(TObject *Sender, System::WideChar &Key);
	void __fastcall KiFeedbackAdvEditChange(TObject *Sender);
	void __fastcall KiAdvEditChange(TObject *Sender);
	void __fastcall KdAdvEditChange(TObject *Sender);
	void __fastcall StpAdvEditChange(TObject *Sender);
	void __fastcall BiasAdvEditChange(TObject *Sender);
	void __fastcall KpAdvEditChange(TObject *Sender);
	void __fastcall RefAdvEditChange(TObject *Sender);


private:	// User declarations
	TIniFile *iniFile;


public:		// User declarations
	__fastcall TApproachPanelForm(TComponent* Owner);
	void __fastcall SetApproach();
	void SettApproach();



	bool first;

	void GetIniToUi();

	int RefrenceApp;
	int KiApp_Contact;
	int KiApp_NonContact;
	int BiasApp;
	int StpApp;
	int KdApp;
	int KpApp;
	int KiFeedback_Contact;
	int KiFeedback_NonContact;

	int KiApp;
	int KiFeedBack;

	bool all_scale;

	double VoltageOffset;
	double VoltageIndex;

	double ZOffset;
	double Zindex;

	void AllEditWhite();
};
//---------------------------------------------------------------------------
extern PACKAGE TApproachPanelForm *ApproachPanelForm;
//---------------------------------------------------------------------------
#endif
