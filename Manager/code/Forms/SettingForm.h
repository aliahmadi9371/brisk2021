//---------------------------------------------------------------------------

#ifndef SettingFormH
#define SettingFormH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include "AdvGlassButton.hpp"
#include <Vcl.ExtCtrls.hpp>
#include "CalcEdit.hpp"
#include "AdvGlowButton.hpp"
#include "AdvEdit.hpp"
#include "AdvPanel.hpp"
#include "ConfigFrm.h"
//---------------------------------------------------------------------------
class TSettingFrm : public TForm
{
__published:	// IDE-managed Components
	TPanel *PanelIp;
	TPanel *PanelMode;
	TAdvGlassButton *BriskModeEditLbl;
	TAdvGlassButton *BriskIpLbl;
	TAdvGlassButton *BriskModeEdit;
	TAdvGlassButton *BriskIp;
	TAdvPanel *PanelSubMonitor;
	TPanel *PanelLabelMonitor;
	TLabel *LabelMonitor;
	TAdvPanel *ConfigButtonPanel;
	TAdvGlowButton *ConfigButton;
	TTimer *Timer1;
	TPanel *PanelID;
	TAdvGlassButton *ClientIDEditLbl;
	TAdvGlassButton *ClientIDEdit;
	TPanel *PanelVersion;
	TAdvGlassButton *SoftwareVersionEditLbl;
	TAdvGlassButton *SoftwareVersionEdit;
	void __fastcall pOffButClick(TObject *Sender);
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall FormShow(TObject *Sender);
	void __fastcall ConfigButtonClick(TObject *Sender);
	void __fastcall FormKeyPress(TObject *Sender, System::WideChar &Key);
	void __fastcall Timer1Timer(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TSettingFrm(TComponent* Owner);
	TConfigForm* myConfigForm;
	bool first;
	bool password;

	System::WideChar input;
	void Check();
	bool Osc_PreviousState;

	bool ShowConf;
};
//---------------------------------------------------------------------------
extern PACKAGE TSettingFrm *SettingFrm;
//---------------------------------------------------------------------------
#endif
