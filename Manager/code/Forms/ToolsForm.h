//---------------------------------------------------------------------------

#ifndef ToolsFormH
#define ToolsFormH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include "AdvGlowButton.hpp"
#include "AdvSelectors.hpp"
#include "AdvGlassButton.hpp"
#include "CurvyControls.hpp"
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.Buttons.hpp>
//---------------------------------------------------------------------------
class TToolsFrm : public TForm
{
__published:	// IDE-managed Components
	TAdvGlowButton *CloseButton;
	TPanel *PanelTools;
	TCurvyCombo *AdvComboBoxTools;
	TAdvGlassButton *AdvComboBoxToolsLbl;
	TPanel *PanelColor;
	TAdvGlassButton *AdvEditColorLbl;
	TCurvyEdit *AdvEditColor;
	TPanel *PanelWidth;
	TAdvGlassButton *AdvEditWidthLbl;
	TCurvyEdit *AdvEditWidth;
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall CloseButtonClick(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall FormCloseQuery(TObject *Sender, bool &CanClose);
	void __fastcall FormShow(TObject *Sender);
	void __fastcall AdvEditColorChange(TObject *Sender);
	void __fastcall AdvComboBoxToolsChange(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TToolsFrm(TComponent* Owner);

    bool first;
};
//---------------------------------------------------------------------------
extern PACKAGE TToolsFrm *ToolsFrm;
//---------------------------------------------------------------------------
#endif
