//---------------------------------------------------------------------------

#ifndef KpfmFormH
#define KpfmFormH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include "AdvPanel.hpp"
#include <Vcl.ExtCtrls.hpp>
#include "AdvGlowButton.hpp"
#include "AdvGlassButton.hpp"
#include "CurvyControls.hpp"
//---------------------------------------------------------------------------
class TKpfmFrm : public TForm
{
__published:	// IDE-managed Components
	TAdvPanel *PanelSubKpfm;
	TPanel *PanelLabelKpfm;
	TLabel *LabelKpfm;
	TAdvGlowButton *BiasFeedbackButton;
	TAdvGlowButton *PhaseFeedbackButton;
	TPanel *Panel1;
	TAdvGlassButton *FreqAdvEditLbl;
	TCurvyEdit *FreqAdvEdit;
	TPanel *Panel2;
	TAdvGlassButton *VoltageAdvEditLbl;
	TCurvyEdit *VoltageAdvEdit;
	TPanel *Panel4;
	TAdvGlassButton *KiAdvEditLbl;
	TCurvyEdit *KiAdvEdit;
	TPanel *Panel6;
	TAdvGlassButton *KdAdvEditLbl;
	TCurvyEdit *KdAdvEdit;
	TPanel *Panel5;
	TAdvGlassButton *KpAdvEditLbl;
	TCurvyEdit *KpAdvEdit;
	TPanel *Panel7;
	TAdvGlassButton *ThAdvEditLbl;
	TCurvyEdit *ThAdvEdit;
	TPanel *Panel3;
	TAdvGlassButton *Lia1AdvEditLbl;
	TCurvyEdit *Lia1AdvEdit;
	TAdvGlowButton *LiaButton;
	TPanel *Panel8;
	TAdvGlassButton *AdvGlassButton1;
	TCurvyEdit *CurvyEdit1;
	TPanel *Panel9;
	TAdvGlassButton *AdvGlassButton2;
	TCurvyEdit *CurvyEdit2;
	void __fastcall FormShow(TObject *Sender);
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall BiasFeedbackButtonClick(TObject *Sender);
	void __fastcall PhaseFeedbackButtonClick(TObject *Sender);
	void __fastcall FreqAdvEditKeyPress(TObject *Sender, System::WideChar &Key);
	void __fastcall VoltageAdvEditKeyPress(TObject *Sender, System::WideChar &Key);
	void __fastcall Lia1AdvEditKeyPress(TObject *Sender, System::WideChar &Key);
	void __fastcall KiAdvEditKeyPress(TObject *Sender, System::WideChar &Key);
	void __fastcall KpAdvEditKeyPress(TObject *Sender, System::WideChar &Key);
	void __fastcall KdAdvEditKeyPress(TObject *Sender, System::WideChar &Key);
	void __fastcall ThAdvEditKeyPress(TObject *Sender, System::WideChar &Key);
	void __fastcall LiaButtonClick(TObject *Sender);
	void __fastcall FreqAdvEditChange(TObject *Sender);
	void __fastcall VoltageAdvEditChange(TObject *Sender);
	void __fastcall Lia1AdvEditChange(TObject *Sender);
	void __fastcall KiAdvEditChange(TObject *Sender);
	void __fastcall KpAdvEditChange(TObject *Sender);
	void __fastcall KdAdvEditChange(TObject *Sender);
	void __fastcall ThAdvEditChange(TObject *Sender);

private:	// User declarations

    void __fastcall SendKpfm();
public:		// User declarations
	__fastcall TKpfmFrm(TComponent* Owner);
	void GetIniKpfmForm();
	void SetUiKpfmForm();

	bool first;


	bool bias;
	bool phase;
	bool lia;

	int freq;
	int voltage;
	int lia1;
	int ki;
	int kp;
	int kd;
	int th;

	byte bbias;
	byte pphase;

	void AllEditWhite();

	double Voltage_index;
	double Voltage_offset;


};
//---------------------------------------------------------------------------
extern PACKAGE TKpfmFrm *KpfmFrm;
//---------------------------------------------------------------------------
#endif

