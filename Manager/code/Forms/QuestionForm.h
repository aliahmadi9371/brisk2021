//---------------------------------------------------------------------------

#ifndef QuestionFormH
#define QuestionFormH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include "AdvGlowButton.hpp"
#include "CurvyControls.hpp"
//---------------------------------------------------------------------------
class TQFrm : public TForm
{
__published:	// IDE-managed Components
	TDBAdvGlowButton *Button2;
	TCurvyEdit *AdvEditOverScan;
	TDBAdvGlowButton *Button1;
	void __fastcall Button1Click(TObject *Sender);
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall Button2Click(TObject *Sender);
	void __fastcall FormShow(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
private:	// User declarations
public:		// User declarations
	__fastcall TQFrm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TQFrm *QFrm;
//---------------------------------------------------------------------------
#endif
