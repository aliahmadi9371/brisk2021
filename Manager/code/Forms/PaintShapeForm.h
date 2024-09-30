//---------------------------------------------------------------------------

#ifndef PaintShapeFormH
#define PaintShapeFormH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TShapeForm : public TForm
{
__published:	// IDE-managed Components
	TPaintBox *PaintBox1;
	void __fastcall FormCreate(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TShapeForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TShapeForm *ShapeForm;
//---------------------------------------------------------------------------
#endif
