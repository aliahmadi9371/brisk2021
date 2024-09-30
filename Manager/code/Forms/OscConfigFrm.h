//---------------------------------------------------------------------------

#ifndef OscConfigFrmH
#define OscConfigFrmH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include "AdvGlassButton.hpp"
#include "CurvyControls.hpp"
#include <Vcl.ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TOscConfigForm : public TForm
{
__published:	// IDE-managed Components
	TPanel *Panel1;
	TAdvGlassButton *TAdvGlowButton1;
	TCurvyEdit *CurvyEdit1;
	TCurvyEdit *CurvyEdit2;
	TCurvyEdit *CurvyEdit3;
	TCurvyEdit *CurvyEdit4;
	TCurvyEdit *CurvyEdit5;
	void __fastcall CurvyEdit1Change(TObject *Sender);
	void __fastcall CurvyEdit2Change(TObject *Sender);
	void __fastcall CurvyEdit3Change(TObject *Sender);
	void __fastcall CurvyEdit4Change(TObject *Sender);
	void __fastcall CurvyEdit5Change(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TOscConfigForm(TComponent* Owner);

	bool first;
};
//---------------------------------------------------------------------------
extern PACKAGE TOscConfigForm *OscConfigForm;
//---------------------------------------------------------------------------
#endif
