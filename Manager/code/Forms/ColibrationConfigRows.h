//---------------------------------------------------------------------------

#ifndef ColibrationConfigRowsH
#define ColibrationConfigRowsH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include "AdvGlassButton.hpp"
#include "CurvyControls.hpp"
#include <Vcl.ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TColibration : public TForm
{
__published:	// IDE-managed Components
	TPanel *Panel1;
	TAdvGlassButton *TAdvGlowButton1;
	TCurvyEdit *CurvyEdit1;
	TCurvyEdit *CurvyEdit2;
	void __fastcall CurvyEdit1Change(TObject *Sender);
	void __fastcall CurvyEdit2Change(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TColibration(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TColibration *Colibration;
//---------------------------------------------------------------------------
#endif
