//---------------------------------------------------------------------------

#ifndef RowConfigFrmH
#define RowConfigFrmH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include "AdvGlassButton.hpp"
#include "CurvyControls.hpp"
#include <Vcl.ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TRowFrm : public TForm
{
__published:	// IDE-managed Components
	TPanel *Panel1;
	TCurvyEdit *CurvyEdit1;
	TAdvGlassButton *TAdvGlowButton1;
	void __fastcall CurvyEdit1Change(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TRowFrm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TRowFrm *RowFrm;
//---------------------------------------------------------------------------
#endif
